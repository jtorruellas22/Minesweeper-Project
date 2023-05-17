#include "Extra.h"
vector<char> Extra::readFile(int test_board)
{
	string name = "boards/testboard" + std::to_string(test_board) + ".brd";
	vector<char> mines;
	ifstream file(name);

	if (file.is_open()) {
		char value;
		for (int i = 0; i < 16; i++) {
			for (int j = 0; j < 25; j++) {
				file.get(value);
				mines.push_back(value);
			}
			file.ignore(1);
		}
		file.close();
	}
	return mines;
}

vector<int> Extra::counter(int number)
{
	vector<int> numbers;


	if (number < -99) {
		numbers.push_back(10);
		numbers.push_back(9);
		numbers.push_back(9);
	}


	else if (number < -9) {
		numbers.push_back(10);
		int temp = (number * -1) / 10;
		numbers.push_back(temp);
		temp = (number * -1) % 10;
		numbers.push_back(temp);
	}

	else if (number < 0) {
		numbers.push_back(10);
		numbers.push_back(0);
		numbers.push_back(number * -1);
	}

	
	else if (number < 10) {
		numbers.push_back(0);
		numbers.push_back(0);
		numbers.push_back(number);
	}

	
	else if (number < 100) {
		numbers.push_back(0);
		int temp = number / 10;
		numbers.push_back(temp);
		temp = number % 10;
		numbers.push_back(temp);
	}


	return numbers;
}