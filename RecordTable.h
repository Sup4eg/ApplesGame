#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include "Math.h"
#include "Constants.h"

namespace ApplesGame {

  using namespace sf;
  using namespace std;

  //game over text
  struct Header {
	Text text;

	const Text::Style style = Text::Bold;
	const Color color = Color::White;
	const int size = 27;
	const string str = "The record table!";
	const Position2D position{60.f, 60.f};
  };

  struct TableCol {

	//shape
	RectangleShape shape{Vector2f(130.f, 30.f)};
	const Position2D position{ 60.f, 110.f };
	const float marginX = 140.f;
	const float marginY = 40.f;
	const Color colColor = Color(150, 50, 250);
	const Color colBorderColor = Color(250, 150, 100);
	const float colBorderWidth = 5.f;


	//text
	Text text;
	Font font;
	const Text::Style textStyle = Text::Italic;
	const Color textColor = Color::White;
	const int textSize = 15;

	//value
	string value = "";


	TableCol& operator= (const TableCol& tableCol) {
	  if (this == &tableCol) {
		return *this;
	  }

	  shape = tableCol.shape;
	  value = tableCol.value;
	  font = tableCol.font;
	  return *this;
	}
  };

  struct TableRow {
	const int colsNumber = 2;
	vector<TableCol> cols;

	TableRow& operator= (const TableRow& tableRow) {
	  if (this == &tableRow) {
		return *this;
	  }

	  cols = tableRow.cols;
	  return *this;
	}
  };

  struct Table {

	const vector<string> playerNames = { "Kirill", "Dima", "Vasia", "Best player", "Sup4eg", "No name1", "No name2" };

	//5 - 20 players
	const int rowsNumber = getRandomNumber(5, 10);
	vector<TableRow> rows;
  };

  struct Background {
	sf::RectangleShape background;
	sf::Color color = sf::Color::Blue;
  };

  struct RecordTable {

	Header header;
	Background bgc;
	Table table;
  };

  struct Game;

  void initRecordTable(RecordTable& recordTable, const Font& font);
  void drawRecordTable(RecordTable& table, RenderWindow& window);
  TableRow& findRowIf(vector<TableRow>& rows, string searchValue);

  //usage only this file
  static void initHeader(Header& header, const Font& font);
  static void initBgc(Background& bgc);
  static void initTableValues(Table& table, const Font& font);
  static void sortRows(vector<TableRow>& rows);
  static void drawTable(Table& table, RenderWindow& window);
}

