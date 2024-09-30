#include "function.h"
#include <iostream>

int main()
{
	truba t;
	compr_station cs;
	while (true) {
		char c;
		cout << endl << "           MENU" << endl;
		cout << endl << "1. Add a pipe " << endl;
		cout << "2. Add a comprassion station " << endl;
		cout << "3. View all objects " << endl;
		cout << "4. Edit the pipe " << endl;
		cout << "5. Edit the CS" << endl;
		cout << "6. Save " << endl;
		cout << "7. Upload " << endl;
		cout << "0. Exit " << endl;
		cout << endl << "Enter the number :  ";
		cin >> c;
		cin.ignore(10000, '\n');
		switch (c) {
		case '1':
			add_truba(t);
			break;
		case '2':
			add_cs(cs);
			break;
		case '3':
			all_objects(t, cs);
			break;
		case '4':
			edit_pipe(t);
			break;
		case '5':
			edit_cs(cs);
			break;
		case '6':
			save(t, cs);
			break;
		case '7':
			cout << '7' << endl;
			upload(t, cs);
			break;
		case '0':
			exit(0);
			break;
		default:
			cout << "enter a number from 1 to 7 and try again\n";
			break;
		}

		cout << "\nTo continue, click enter";
		cin.ignore(10000, '\n');
		system("cls");

	}



};