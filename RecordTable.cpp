#include "RecordTable.h"
#include "Constants.h"
#include "Math.h"
#include "Game.h"
#include "Constants.h"

namespace ApplesGame {

  using namespace std;

  void initRecordTable(RecordTable& recordTable, const Font& font)
  {
	initHeader(recordTable.header, font);
	initBgc(recordTable.bgc);
	initTableValues(recordTable.table, font);
  }

  void drawRecordTable(RecordTable& table, sf::RenderWindow& window)
  {
	window.draw(table.bgc.background);
	window.draw(table.header.text);
	drawTable(table.table, window);
  }

  void drawTable(Table& table, RenderWindow& window)
  {
	//sort array here before draw
	sortRows(table.rows);

	for (auto row = begin(table.rows); row != end(table.rows); ++row) {
	  int rowNumber = int(row - begin(table.rows));
	  for (auto col = begin(row->cols); col != end(row->cols); ++col) {
		int colNumber = int(col - begin(row->cols));
		col->shape.setPosition(col->position.x + (col->marginX * colNumber), col->position.y + (col->marginY * rowNumber));
		col->shape.setFillColor(col->colColor);
		col->shape.setOutlineColor(col->colBorderColor);
		col->shape.setOutlineThickness(col->colBorderWidth);

		col->text.setFont(col->font);
		col->text.setCharacterSize(col->textSize);
		col->text.setStyle(col->textStyle);
		col->text.setFillColor(col->textColor);
		col->text.setString(col->value);
		setTextRelativeOrigin(col->text, col->shape.getSize().x, col->shape.getSize().y);
		col->text.setPosition(col->shape.getPosition().x, col->shape.getPosition().y);
	  }
	}

	for (const auto& row : table.rows) {
	  for (const auto& col : row.cols) {
		window.draw(col.shape);
		window.draw(col.text);
	  }
	}
  }

  TableRow& findRowIf(vector<TableRow>& rows, string searchValue) {
	//small count of rows, linear search is okay here
	for (TableRow& row : rows) {
	  if (row.cols[0].value == searchValue) {
		return row;
	  }
	}
	//no player means error
	exit(0);
  }

  void sortRows(vector<TableRow>& rows)
  {
	//use merge sort here
	if (rows.size() > 1) {
	  int mid = (int) rows.size() / 2;

	  //slice vectors
	  vector<TableRow> lefthalf(rows.begin(), rows.begin() + mid);
	  vector<TableRow> righthalf(rows.begin() + mid, rows.begin() + rows.size());

	  sortRows(lefthalf);
	  sortRows(righthalf);

	  unsigned int i = 0, j = 0, k = 0;

	  while (i < lefthalf.size() && j < righthalf.size()) {
		//sort by score here
		int score1 = stoi(lefthalf[i].cols[1].value);
		int score2 = stoi(righthalf[j].cols[1].value);
		if (score1 <= score2) {
		  rows[k] = lefthalf[i];
		  ++i;
		}
		else {
		  rows[k] = righthalf[j];
		  ++j;
		}
		++k;
	  }

	  while (i < lefthalf.size()) {
		rows[k] = lefthalf[i];
		++i;
		++k;
	  }

	  while (j < righthalf.size()) {
		rows[k] = righthalf[j];
		++j;
		++k;
	  }
	}
  }

  void initHeader(Header& header, const Font& font)
  {

	header.text.setFont(font);
	header.text.setCharacterSize(header.size);
	header.text.setStyle(header.style);
	header.text.setFillColor(header.color);
	header.text.setString(header.str);
	header.text.setPosition(header.position.x, header.position.y);

  }

  void initBgc(Background& bgc)
  {
	bgc.background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGTH));
	bgc.background.setFillColor(bgc.color);
	bgc.background.setPosition(0.f, 0.f);
  }

  void initTableValues(Table& table, const Font& font)
  {

	table.rows.resize(table.rowsNumber);

	//last index for player row
	for (auto row = begin(table.rows); row != end(table.rows); ++row) {
	  int nameIndex = getRandomNumber(0, (int)table.playerNames.size() - 1);
	  int rowNumber = int(row - begin(table.rows));
	  row->cols.resize(row->colsNumber);
	  for (auto col = begin(row->cols); col != end(row->cols); ++col) {
		int colNumber = int(col - begin(row->cols));
		col->value = (colNumber == 1 ? to_string(getRandomNumber(0, 30)) : table.playerNames[nameIndex]);
		col->font = font;
	  }
	}

	//0 index - player
	table.rows[0].cols[0].value = "Player1";
	table.rows[0].cols[1].value = "0";
  }

}


