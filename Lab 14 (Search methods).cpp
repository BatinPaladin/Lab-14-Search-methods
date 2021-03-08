#include <iostream>
#include <fstream>
#include <string>
using namespace std;
struct Directory {
	string data;
};
int ReadFile(Directory book[], ifstream& file) {
	string CurrentLine;
	int index = 0;
	while (!file.eof()) {
		getline(file, CurrentLine);
		book[index].data = CurrentLine;
		index++;
	}
	return index;
};
void WriteDirectory(Directory book[], int N) {
	for (int i = 0; i < N; i++) {
		cout << book[i].data << endl;
	}
};
bool DirectSearch(string row, string key) {
	int LengthRow = row.length(), LengthKey = key.length();
	for (int i = 0; i < LengthRow - LengthKey + 1; i++) {
		for (int j = 0; j < LengthKey; j++) {
			if (key[j] != row[i + j]) {
				j = LengthKey;
			}
			else if (j == LengthKey - 1) {
				return true;
			}
		}
	}
	return false;
};
bool KnuthMorrisPratt(string row, string key) {
	int LengthRow = row.length(), LengthKey = key.length(), IndexRow = 0, IndexKey = 0, i = 1, j = 0;
	int* array = new int[LengthKey];
	array[0] = 0;
	for (int c = 0; c < LengthKey; c++)
	{
		if (key[i] == key[j]) {
			array[i] = j + 1;
			i++;
			j++;
		}
		else if (j == 0) {
			array[i] = 0;
			i++;
		}
		else {
			j = array[j - 1]; 
		}
	}
	while (IndexRow < LengthRow)
	{
		if (row[IndexRow] == key[IndexKey])
		{
			IndexRow++;
			IndexKey++;
			if (IndexKey == LengthKey) {
				return true;
			}
		}
		if (row[IndexRow] != key[IndexKey])
		{
			if (IndexKey == 0) {
				IndexRow++;
			}
			else {
				IndexKey = array[IndexKey - 1];
			}
		}
	}
	return false;
};
bool BoyerMoore(string row, string key) {
	int LengthRow = row.length(), LengthKey = key.length();
	int array[256];
	for (int i = 0; i < 256; i++) {
		array[i] = LengthKey;
	}
	for (int i = LengthKey - 2; i >= 0; i--) {
		if (array[int(unsigned char(key[i]))] == LengthKey) {
			array[int(unsigned char(key[i]))] = LengthKey - i - 1;
		}
	}
	int KeyPosition = LengthKey - 1;
	while (KeyPosition < LengthRow) {
		if (key[LengthKey - 1] != row[KeyPosition]) {
			KeyPosition += array[int(unsigned char(row[KeyPosition]))];
		}
		else {
			for (int i = LengthKey - 1; i >= 0; i--) {
				if (key[i] != row[KeyPosition - LengthKey + i + 1]) {
					KeyPosition += array[int(unsigned char(row[KeyPosition]))];
					i = -1;
				}
				else if (i == 0) {
					return true;
				}
			}
		}
	}
	return false;
}
void SwitchSearchMetod(int quantity, Directory book[]) {
	int MethodNumber = -1;
	bool otvet = false;
	int index = 0;
	string key;
	while ((MethodNumber < 0) || (MethodNumber > 4)) {
		cout << "\nВведите номер метода поиска подстроки в строке\n\n0 - метод прямого поиска\n1 - метод Кнута-Мориса-Пратта\n2 - метод Бойера-Мура\n\nВаш выбор: ";
		cin >> MethodNumber;
		switch (MethodNumber) {
		case (0):
			cout << "\nВы выбрали метод прямого поиска\n";
			cout << "\nВведите номер искомого телефона: ";
			cin >> key;
			while ((index < quantity) && (otvet == false)) {
				otvet = DirectSearch(book[index].data, key);
				if (otvet == true) {
					cout << "\nРезультат поиска:\n" << book[index].data << endl;
				}
				index++;
			}
			if (otvet == false) {
				cout << "\nПоиск не выдал результатов\n";
			}
			break;
		case (1):
			cout << "\nВы выбрали метод Кнута-Мориса-Прата\n";
			cout << "\nВведите номер искомого телефона: ";
			cin >> key;
			while ((index < quantity) && (otvet == false)) {
				otvet = KnuthMorrisPratt(book[index].data, key);
				if (otvet == true) {
					cout << "\nРезультат поиска:\n" << book[index].data << endl;
				}
				index++;
			}
			if (otvet == false) {
				cout << "\nПоиск не принес результатов!\nТакого номера нет в массиве!\n";
			}
			break;
		case (2):
			cout << "\nВы выбрали метод Бойера-Мура\n";
			cout << "\nВведите номер искомого телефона: ";
			cin >> key;
			while ((index < quantity) && (otvet == false)) {
				otvet = BoyerMoore(book[index].data, key);
				if (otvet == true) {
					cout << "\nРезультат поиска:\n" << book[index].data << endl;
				}
				index++;
			}
			if (otvet == false) {
				cout << "\nПоиск не принес результатов!\nТакого номера нет в массиве!\n";
			}
			break;
		default: cout << "\nВведён не номер метода поиска!\n";
			break;
		}
	}
};
int main()
{
	system("chcp 1251");
	ifstream inputfile("F1.txt");
	if (inputfile.is_open()) {
		Directory book[100];
		int quantity = ReadFile(book, inputfile);
		cout << "\nМассив данных:\n\n";
		WriteDirectory(book, quantity);
		inputfile.close();
		SwitchSearchMetod(quantity, book);
	}
	else {
		cout << "Ошибка! Не удалось открыть файл F1.txt.\n";
	}
	system("pause");
	return 0;
}