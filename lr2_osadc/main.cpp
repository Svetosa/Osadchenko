#include <iostream>
#include <string>
#include <unordered_set>
#include <chrono>
#include <type_traits>
#include <limits>
#include <cctype>

#include "pipe.h"
#include "cs.h"
#include "function.h"

using namespace std;



void menu()
{
	cout << "        Меню: " << endl;
	cout << " 1. Добавить трубу" << endl;
	cout << " 2. Добавить КС" << endl;
	cout << " 3. Вывести объекты" << endl;
	cout << " 4. Сохранение" << endl;
	cout << " 5. Загрузить" << endl;
    cout << " 6. Редактирование по фильтрам" << endl;
	cout << " 0. Выход" << endl << endl;
}


int main()
{
	setlocale(LC_ALL, "ru");
	menu();

	int choice;
	while (true)
	{
		choice = getInput<int>("Команда ", 0, 10);
		system("cls");
		switch (choice)
		{
		case 1:
			pipeadd();
			break;
		case 2:
			addCS();
			break;
		case 3:
			Print();
			break;
		case 4:
			save();
			break;
		case 5:
			load();
			break;
		case 6:
			filter();
            break;
		case 0:
			cout << "Выход " << endl;
			return 0;
		}
		cout << "Нажмите Enter";
		cin.ignore(10000, '\n');
		cerr << endl;
		system("cls");
		menu();
	}
	return 0;
}


