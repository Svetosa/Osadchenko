#include "function.h"
#include <iostream>
#include <fstream>
#include <conio.h>

int proverka() {
	int number;
	while (true) {
		cin >> number;
		if (cin.good() && number >= 0)
		{
			return number;
		}
		else {
			cout << "Mistake. Enter the number and try again :  ";
		}
		cin.clear(); // очистка неправильного ввода
		cin.ignore(10000, '\n');
	}
}

string check_name() {
	string name;
	while (true) {
		getline(cin, name);
		if (cin.good())
		{
			return name;
		}
		else {
			cout << "Mistake. Enter the name without spaces :  ";
		}
		cin.clear(); // очистка неправильного ввода
		cin.ignore(10000, '\n');
	}
}

void add_truba(truba& t)
{
	system("cls");
	//https://metanit.com/cpp/tutorial/5.8.php
	cout << "            PIPE : " << endl << endl;
	cout << "Enter the name of the pipe: ";
	t.kilometr_mark = check_name();
	cout << "Enter the length of the pipe:  ";
	t.length = proverka();
	cout << "Enter the pipe diameter: ";
	t.diameter = proverka();
	cout << "Does the pipe need repair? (y or n) ";
	char B;
	while (true) {
		cin >> B;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (B == 'y' || B == 'n') {
			if (B == 'y') {
				t.Remote = false;
			}
			else {
				t.Remote = true;
			}
			break;
		}
		else {
			cout << "You didn't enter y or n. Try again :  ";
		}
	}
}

void add_cs(compr_station& cs)
{
	system("cls");
	cout << "          COMPRESSOR STATION : " << endl;
	cout << endl << "Enter the name of the compression station : ";
	//getline(cin, cs.cs_name);
	cs.cs_name = check_name();
	cout << "Enter the number of workshops: ";
	cs.workshop = proverka();
	cout << "Enter the number of workshops in operation : ";
	while (true) {
		cs.operation_workshop = proverka();
		if (cs.operation_workshop <= cs.workshop) {
			break;
		}
		else {
			cout << "The number of workshops cannot exceed the number of workshops  ";
		}
	}

	cout << "Enter the compressor station efficiency : ";
	cs.effectiveness = proverka();
}

void all_objects(truba& t, compr_station& cs)
{
	system("cls");
	cout << "          PIPE : " << endl;
	cout << endl << "Pipe name : ";
	if (t.kilometr_mark == "") {
		cout << "No information found" << endl;
	}
	else {
		cout << t.kilometr_mark << endl;
	}


	cout << "Pipe length: ";
	if (t.length == 0) {
		cout << "No information found" << endl;
	}
	else {
		cout << t.length << endl;
	}


	cout << "Pipe diameter: ";
	if (t.diameter == 0) {
		cout << "No information found" << endl;
	}
	else {
		cout << t.diameter << endl;
	}

	cout << "Is repair required ?  ";

	if (t.Remote) {
		cout << " yes";
	}
	else {
		cout << " no";
	}

	cout << endl << endl << "         COMPRESSOR STATION : " << endl;

	cout << endl << "Name CS : ";
	if (cs.cs_name == "") {
		cout << "No information found" << endl;
	}
	else {
		cout << cs.cs_name << endl;
	}

	cout << "Number of workshops : ";
	if (cs.workshop == 0) {
		cout << "There are no workshops" << endl;
	}
	else {
		cout << cs.workshop << endl;
	}

	cout << "Number of operating workshops : ";
	if (cs.operation_workshop == 0) {
		cout << "There are no working workshops" << endl;
	}
	else {
		cout << cs.operation_workshop << endl;
	}

	cout << "Effectiveness : ";
	if (cs.effectiveness == 0) {
		cout << "No information found" << endl;
	}
	else {
		cout << cs.effectiveness << endl;
	}
	cin.ignore();
}

void edit_pipe(truba& t)
{
	system("cls");
	cout << "            EDIT PIPE" << endl;
	cout << endl << "Is the pipe under repair (y or n)?  ";
	//char B;
	//cin >> B;
	//cin.ignore(numeric_limits<streamsize>::max(), '\n');
	//if (B == 'y'){
	//    t.Remote = true;
	//}
	//else {
	//    t.Remote = false;
	//}


	char B;
	while (true) {
		cin >> B;
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (B == 'y' || B == 'n') {
			if (B == 'y') {
				t.Remote = true;
			}
			else {
				t.Remote = false;
			}
			break;
		}
		else {
			cout << "You didn't enter y or n. Try again :  ";
		}
	}
}

void edit_cs(compr_station& cs)
{
	system("cls");
	cout << "            EDIT CS" << endl;
	cout << endl << "Number of workshops : ";
	cs.operation_workshop = proverka();
}

void save(truba& t, compr_station& cs)
{
	system("cls");
	ofstream file("lab1.txt");
	if (file.is_open()) {
		file << "          PIPE : " << endl;
		file << endl << "Pipe name : ";
		if (t.kilometr_mark == "") {
			file << "No information found" << endl;
		}
		else {
			file << t.kilometr_mark << endl;
		}


		file << "Pipe length: ";
		if (t.length == 0) {
			file << "No information found" << endl;
		}
		else {
			file << t.length << endl;
		}


		file << "Pipe diameter: ";
		if (t.diameter == 0) {
			file << "No information found" << endl;
		}
		else {
			file << t.diameter << endl;
		}

		file << "Is repair required ?  ";

		if (t.Remote) {
			file << " yes";
		}
		else {
			file << " no";
		}

		file << endl << endl << "        COMPRESSOR STATION : " << endl << endl;

		file << "Name CS : ";
		if (cs.cs_name == "") {
			file << "No information found" << endl;
		}
		else {
			file << cs.cs_name << endl;
		}

		file << "Number of workshops : ";
		if (cs.workshop == 0) {
			file << "No information found" << endl;
		}
		else {
			file << cs.workshop << endl;
		}

		file << "Number of operating workshops : ";
		if (cs.operation_workshop == 0) {
			file << "No information found" << endl;
		}
		else {
			file << cs.operation_workshop << endl;
		}

		file << "Effectiveness : ";
		if (cs.effectiveness == 0) {
			file << "No information found" << endl;
		}
		else {
			file << cs.effectiveness << endl;
		}
	}
	cout << "The information is written to a file" << endl;
	cin.ignore();

}

void upload(truba& t, compr_station& cs)
{
	system("cls");
	ifstream file("lab1.txt");
	if (!file) {
		cerr << "File opening error" << endl;
		return;
	}
	if (file.peek() == EOF) {//https://www.studyplan.dev/pro-cpp/input-streams/q/use-of-peek-method
		cout << "There is no data in the file" << endl;
		return;
	}
	string str;
	getline(file, str);
	if (str == "          PIPE : ") {
		getline(file, str);
		getline(file, str);
		t.kilometr_mark = str.substr(12);
		try {
			getline(file, str);
			t.length = stoi(str.substr(13));
		}
		catch (const invalid_argument& e) {
			std::cerr << "Length is not a number" << std::endl;
		}

		try {
			getline(file, str);
			t.diameter = stoi(str.substr(15));
		}
		catch (const invalid_argument& e) {
			std::cerr << "The diameter is not a number" << std::endl;
		}
		getline(file, str);
		if (str == "Is repair required ?   yes") {
			t.Remote = true;
		}
		else {
			t.Remote = false;
		}

		getline(file, str);
		getline(file, str);
		getline(file, str);
		getline(file, str);
		cs.cs_name = str.substr(10);
		try {
			getline(file, str);
			cs.workshop = stoi(str.substr(22));
		}
		catch (const invalid_argument& e) {
			std::cerr << "The number of workshops is not a number" << std::endl;
		}

		try {
			getline(file, str);
			cs.operation_workshop = stoi(str.substr(31));
		}
		catch (const invalid_argument& e) {
			std::cerr << "The number of workshops is not a number" << std::endl;
		}

		try {
			getline(file, str);
			cs.effectiveness = stoi(str.substr(16));
		}
		catch (const invalid_argument& e) {
			std::cerr << "Efficiency is not a number" << std::endl;
		}
	}
	else {
		getline(file, str);
		getline(file, str);

		cs.cs_name = str.substr(10);

		try {
			getline(file, str);
			cs.workshop = stoi(str.substr(22));
		}
		catch (const invalid_argument& e) {
			std::cerr << "The number of workshops is not a number" << std::endl;
		}

		try {
			getline(file, str);
			cs.operation_workshop = stoi(str.substr(31));
		}
		catch (const invalid_argument& e) {
			std::cerr << "The number of workshops is not a number" << std::endl;
		}

		try {
			getline(file, str);
			cs.effectiveness = stoi(str.substr(16));
		}
		catch (const invalid_argument& e) {
			std::cerr << "Efficiency is not a number" << std::endl;
		}

		getline(file, str);
		getline(file, str);
		getline(file, str);

		t.kilometr_mark = str.substr(12);
		try {
			getline(file, str);
			t.length = stoi(str.substr(13));
		}
		catch (const invalid_argument& e) {
			std::cerr << "Length is not a number" << std::endl;
		}

		try {
			getline(file, str);
			t.diameter = stoi(str.substr(15));
		}
		catch (const invalid_argument& e) {
			std::cerr << "The diameter is not a number" << std::endl;
		}
		getline(file, str);
		if (str == "Is repair required ?   yes") {
			t.Remote = true;
		}
		else {
			t.Remote = false;
		}
	}
	file.close();

}





