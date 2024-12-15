#include "pipe.h"
#include "cs.h"
#include "function.h"
#include "structure.h"

#include <iomanip>
#include <sstream>
#include <fstream>
#include <string>
#include <unordered_set>
#include <iostream>
#include <chrono>
#include <iomanip>
#include <ctime>
#include <algorithm>
using namespace std;

int index_p = 0;
int index_cs = 0;
unordered_set<Pipe, Pipe::Hash> pipes;
unordered_set<CS, CS::Hash> css;
unordered_set<Connection, Connection::Hash> connections;



void loggir(const string& message) {
	static string filename;
	if (filename.empty()) {
		auto now = chrono::system_clock::now();
		auto time_t_now = chrono::system_clock::to_time_t(now);
		char timeBuffer[26];
		ctime_s(timeBuffer, sizeof(timeBuffer), &time_t_now);
		string Time = timeBuffer;
		Time.erase(remove(Time.begin(), Time.end(), '\n'), Time.end());
		replace(Time.begin(), Time.end(), ' ', '_');
		replace(Time.begin(), Time.end(), ':', '-');

		ostringstream filePath;
		filePath << "logs/" << Time << ".txt";
		filename = filePath.str();
	}
	ofstream logFile(filename, ios::app);
	logFile << message << endl;
	logFile.close();
}

void pipeadd() {
	++index_p;
	bool repairStatus;
	string name = getInput<string>("Введите имя трубы: ", 1, 1);
	if (name == "0") return;
	int length = getInput<int>("Введите в метрах длину трубы: ", 1, INT_MAX);
	int diameter = getInput<int>("Введите в миллиметрах диаметр трубы: ", 1, INT_MAX);
	int status = getInput<int>("Введите характеристику в ремонте: ('Требует ремонта'- 1, 'Не требует ремонта' - 0): ", 0, 1);
	repairStatus = (status == 1);

	Pipe newPipe(index_p, name, length, diameter, repairStatus);
	auto result = pipes.insert(newPipe);
	if (result.second) {
		cout << "Труба успешно добавлена :)" << endl;
	}
	else {
		cout << "Ошибка :(! Труба с таким именем и характеристиками уже добавлена" << endl;
	}
}

void addCS() {
	++index_cs;
	string name = getInput<string>("Введите имя КС: ", 0, 0);
	if (name == "0") return;
	int quantity = getInput<int>("Введите общее количество цехов: ", 1, INT_MAX);
	int work_workshop = getInput<int>("Введите количество работающих цехов: ", 0, quantity);
	float efect_cs = work_workshop * 100.0f / quantity;

	CS newCS(index_cs, name, quantity, work_workshop, efect_cs);
	auto result = css.insert(newCS);
	if (result.second) {
		cout << "КС успешно добавлена :)" << endl;
	}
	else {
		cout << "Ошибка :(\n! КС с таким именем и характеристиками уже добавлена" << endl;
	}
}
void Print() {
	cout << "Трубы" << endl << endl;
	vector<Pipe> sortedPipes(pipes.begin(), pipes.end());
	sort(sortedPipes.begin(), sortedPipes.end(), [](const Pipe& a, const Pipe& b) {
		return a.index < b.index;
		});

	for (const auto& pipe : sortedPipes) {
		cout << "Индекс: " << pipe.index << endl;
		cout << "Имя: " << pipe.name << endl;
		cout << "Длина: " << pipe.length << " м" << endl;
		cout << "Диаметр: " << pipe.diameter << " мм" << endl;
		cout << "Ремонт: " << (pipe.repairStatus ? "Да" : "Нет") << endl;
		cout << string(50, '-') << endl;
	}
	cout << endl <<endl;
	cout << "КС" << endl << endl;
	cout << string(50, '-') << endl;
	vector<CS> sortedCS(css.begin(), css.end());
	sort(sortedCS.begin(), sortedCS.end(), [](const CS& a, const CS& b) {
		return a.index < b.index;
		});

	for (const auto& cs : sortedCS) {
		cout << "Индекс: " << cs.index << endl;
		cout << "Имя: " << cs.name << endl;
		cout << "Цехов: " << cs.quantity << endl;
		cout << "Рабочих: " << cs.work_workshop << endl;
		cout << "Эффект.: " << cs.efect_cs << "%" << endl;
		cout << string(50, '-') << endl;
	}
}


void save() {
	string fileName = getInput<string>("Имя файла ", 1, 1);
	ofstream outFile(fileName);
	if (outFile.is_open()) {
		if (pipes.size() == 0) {
			outFile << "Трубы не добавлены:(";
		}
		else {
			for (const auto& pipe : pipes) {
				outFile << "Pipe\n";
				outFile << pipe.index << "\n";
				outFile << pipe.name << "\n";
				outFile << pipe.length << "\n";
				outFile << pipe.diameter << "\n";
				outFile << (pipe.repairStatus ? "Требует ремонта" : "Не требует ремонта") << "\n";
				outFile << "---------------------------------------\n";
			}
		}

		if (css.size() == 0) {
			outFile << "КС не добавлены :(";
		}
		else {
			for (const auto& cs : css) {
				outFile << "CS\n";
				outFile << cs.index << "\n";
				outFile << cs.name << "\n";
				outFile << cs.quantity << "\n";
				outFile << cs.work_workshop << "\n";
				outFile << cs.efect_cs << "\n";
				outFile << "--------------------------------------\n";
			}
			outFile.close();
			cout << "Трубы и КС успешно сохранены в файл" << endl;
		}
	}
	else {
		cout << "Ошбка открытия файла" << endl;
	}
}


void load() {
	string fileName = getInput<string>("Имя файла, из которого будем выгружать данные:\n", 1, 1);
	if (fileName == "" || fileName == "0") return;
	ifstream inFile(fileName);
	if (!inFile.is_open()) {
		cout << "Файл не найден" << endl;
		return;
	}
	string str;

	int ind;
	int quantity;
	int work_workshop;
	bool repairStatus;
	string name;
	int length;
	int diameter;
	{
		while (!inFile.eof()) {
			getline(inFile, str);
			if (str == "КС не добавлены :(") {
				cout << "В файле нет кс" << endl;
				continue;
			}
			if (str == "Трубы не добавлены:(") {
				cout << "В файле нет труб" << endl;
				continue;
			}
			if (str == "Pipe") {
				getline(inFile, str);
				if (validateInput(str, ind, 1, INT_MAX)) {
					ind = stoi(str);
					if (ind <= index_p) {
						ind = ++index_p;
					}
					else {
						index_p = ind;
					}
				}
				else {
					return;
				}
				getline(inFile, str);
				if (validateInput(str, name, 1, 1)) {
					name = str;
				}
				else {
					return;
				}
				getline(inFile, str);
				if (validateInput(str, length, 1, INT_MAX)) {
					length = stoi(str);
				}
				else {
					return;
				}
				getline(inFile, str);
				if (validateInput(str, diameter, 1, INT_MAX)) {
					diameter = stoi(str);
				}
				else {
					return;
				}
				getline(inFile, str);
				if (validateInput(str, str, 1, 1) && str == "Требует ремонта") {
					repairStatus = true;
				}
				else if (validateInput(str, str, 1, 1) && str == "Не требует ремонта") {
					repairStatus = false;
				}
				getline(inFile, str);
				Pipe newPipe(ind, name, length, diameter, repairStatus);
				pipes.insert(newPipe);
			}
			else if (str == "CS") {
				getline(inFile, str);
				if (validateInput(str, ind, 1, INT_MAX)) {
					ind = stoi(str);
					if (ind <= index_cs) {
						ind = ++index_cs;
					}
					else {
						index_cs = ind;
					}
				}
				else {
					return;
				}
				getline(inFile, str);
				if (validateInput(str, name, 1, 1)) {
					name = str;
				}
				else {
					return;
				}
				getline(inFile, str);
				if (validateInput(str, quantity, 1, INT_MAX)) {
					quantity = stoi(str);
				}
				else {
					return;
				}
				getline(inFile, str);
				if (validateInput(str, work_workshop, 1, quantity)) {
					work_workshop = stoi(str);
				}
				else {
					return;
				}
				getline(inFile, str);
				float efect_cs = work_workshop * 100.0f / quantity;
				CS newCS(ind, name, quantity, work_workshop, efect_cs);
				css.insert(newCS);
				getline(inFile, str);
			}
		}
		inFile.close();
		cout << "Данные успешно загружены" << endl;
	}
}

void filter() {
	Print();
	cout << "Поиск:\n"
		<< "1 - трубы по имени\n"
		<< "2 - трубы по статусу ремонта\n"
		<< "3 - КС по имени\n"
		<< "4 - КС по проценту незадействованных цехов\n"
		<< "0 - выход" << endl;
	int choice = getInput<int>("Выберите команду: ", 0, 4);
	unordered_set<int> selectedIndices;
	switch (choice) {
	case 1: {
		string name = getInput<string>("Введите имя трубы: ", 1, 1);
		cout << endl << "Результаты поиска труб по имени: \"" << name << "\":" << endl << endl;
		bool found = false;
		for (const auto& pipe : pipes) {
			if (pipe.name.find(name) != string::npos) {  // Ищем вхождение подстроки
				found = true;
				cout << "Индекс: " << pipe.index << endl;
				cout << "Имя трубы: " << pipe.name << endl;
				cout << "Длина: " << pipe.length << " м" << endl;
				cout << "Диаметр: " << pipe.diameter << " мм" << endl;
				cout << "Статус ремонта: " << (pipe.repairStatus ? "Требует ремонта" : "Не требует ремонта") << endl;
				cout << "---------------------------------------" << endl;
				selectedIndices.insert(pipe.index);
			}
		}
		if (!found) {
			cout << "Трубы с таким именем не найдены." << endl;
		}
		break;
	}
	case 2: {
		int status = getInput<int>("Введите статус ремонта (1 - требует ремонта, 0 - не требует ремонта): ", 0, 1);
		bool repairStatus = (status == 1 ? true : false);
		cout << endl << "Результаты поиска труб по статусу \"" << (repairStatus ? "Требует ремонта" : "Не требует ремонта") << "\":" << endl << endl;
		bool found = false;
		for (const auto& pipe : pipes) {
			if (pipe.repairStatus == repairStatus) {
				found = true;
				cout << "Индекс: " << pipe.index << endl;
				cout << "Имя трубы: " << pipe.name << endl;
				cout << "Длина: " << pipe.length << " м" << endl;
				cout << "Диаметр: " << pipe.diameter << " мм" << endl;
				cout << "Статус ремонта: " << (pipe.repairStatus ? "Требует ремонта" : "Не требует ремонта") << endl;
				cout << "---------------------------------------" << endl;
				selectedIndices.insert(pipe.index);
			}
		}
		if (!found) {
			cout << "Трубы с указанным статусом не найдены." << endl;
		}
		break;
	}
	case 3: {
		string name = getInput<string>("Введите имя КС: ", 1, 1);
		cout << endl << "Результаты поиска КС по имени: \"" << name << "\":" << endl << endl;
		bool found = false;
		for (const auto& cs : css) {
			if (cs.name.find(name) != string::npos) {  // Ищем вхождение подстроки
				found = true;
				cout << "Индекс: " << cs.index << endl;
				cout << "Имя КС: " << cs.name << endl;
				cout << "Количество цехов: " << cs.quantity << endl;
				cout << "Рабочие цехи: " << cs.work_workshop << endl;
				cout << "Эффективность: " << cs.efect_cs << "%" << endl;
				cout << "--------------------------------------" << endl;
				selectedIndices.insert(cs.index);
			}
		}
		if (!found) {
			cout << "КС с таким именем не найдены." << endl;
		}
		break;
	}
	case 4: {
		float percentage = getInput<float>("Введите минимальный процент незадействованных цехов: ", 0, 100);
		cout << endl << "Результаты поиска КС с процентом незадействованных цехов >= " << percentage << "%:" << endl << endl;
		bool found = false;
		for (const auto& cs : css) {
			float unusedPercentage = 100.0f - cs.efect_cs;
			if (unusedPercentage >= percentage) {
				found = true;
				cout << "Индекс: " << cs.index << endl;
				cout << "Имя КС: " << cs.name << endl;
				cout << "Количество цехов: " << cs.quantity << endl;
				cout << "Рабочие цехи: " << cs.work_workshop << endl;
				cout << "Эффективность: " << cs.efect_cs << "%" << endl;
				cout << "Незадействованные цехи: " << unusedPercentage << "%" << endl;
				cout << "--------------------------------------" << endl;
				selectedIndices.insert(cs.index);
			}
		}
		if (!found) {
			cout << "КС с указанным процентом незадействованных цехов не найдены." << endl;
		}
		break;
	}
	case 0:
		return;
	}


	cout << "\nВыберите действие для найденных объектов:\n"
		<< "1 - Редактировать все\n"
		<< "2 - Удалить все\n"
		<< "3 - Редактировать по индексам\n"
		<< "4 - Удалить по индексам\n"
		<< "0 - Выйти\n";
	int action = getInput<int>("Ваш выбор: ", 0, 4);
	cout << endl;
	if (action == 0) return;

	if (action == 3 || action == 4) {
		cout << "Введите индексы для обработки (разделите пробелами, например: 1 2 3): ";
		string input;
		selectedIndices.clear();
		getline(cin, input);
		stringstream ss(input);
		int index;
		while (ss >> index) {
			selectedIndices.insert(index);
		}

		if (selectedIndices.empty()) {
			cout << "Не выбрано ни одного индекса." << endl;
			return;
		}
	}

	if (action == 1 || action == 3) { // Редактирование
		for (const auto& idx : selectedIndices) {
			auto pipeIt = find_if(pipes.begin(), pipes.end(), [&](const Pipe& pipe) { return pipe.index == idx; });
			auto csIt = find_if(css.begin(), css.end(), [&](const CS& cs) { return cs.index == idx; });

			if (pipeIt != pipes.end() && (choice == 1 || choice == 2)) {
				Pipe updatedPipe = *pipeIt;
				updatedPipe.repairStatus = !updatedPipe.repairStatus; // Пример изменения статуса
				pipes.erase(pipeIt);
				pipes.insert(updatedPipe);
				cout << "Труба с индексом " << idx << " обновлена." << endl;
			}

			if (csIt != css.end() && (choice == 3 || choice == 4)) {
				CS updatedCS = *csIt;
				updatedCS.work_workshop = getInput<int>("Новое количество работающих цехов для КС с индексом " + to_string(idx) + ": ", 0, updatedCS.quantity);
				updatedCS.efect_cs = updatedCS.work_workshop * 100.0f / updatedCS.quantity;
				css.erase(csIt);
				css.insert(updatedCS);
				cout << "КС с индексом " << idx << " обновлена." << endl;
			}
		}
	}
	else if (action == 2 || action == 4) {
		for (const auto& idx : selectedIndices) {
			auto pipeIt = find_if(pipes.begin(), pipes.end(), [&](const Pipe& pipe) { return pipe.index == idx; });
			auto csIt = find_if(css.begin(), css.end(), [&](const CS& cs) { return cs.index == idx; });

			if (pipeIt != pipes.end() && (choice == 1 || choice == 2)) {
				pipes.erase(pipeIt);
				cout << "Труба с индексом " << idx << " удалена." << endl;
			}

			if (csIt != css.end() && (choice == 3 || choice == 4)) {
				css.erase(csIt);
				cout << "КС с индексом " << idx << " удалена." << endl;
			}
		}
	}
}

void addConnection() {
	if (css.empty() || pipes.empty()) {
		cout << "Невозможно создать соединение: нет доступных КС или труб." << endl;
		return;
	}

	int csInput = getInput<int>("Введите индекс входной КС: ", 1, index_cs);
	int pipeIndex = getInput<int>("Введите индекс трубы: ", 1, index_p);
	int csOutput = getInput<int>("Введите индекс выходной КС: ", 1, index_cs);

	// Проверка существования КС и трубы
	auto csInputIt = find_if(css.begin(), css.end(), [&](const CS& cs) { return cs.index == csInput; });
	auto pipeIt = find_if(pipes.begin(), pipes.end(), [&](const Pipe& p) { return p.index == pipeIndex; });
	auto csOutputIt = find_if(css.begin(), css.end(), [&](const CS& cs) { return cs.index == csOutput; });

	if (csInputIt == css.end() || pipeIt == pipes.end() || csOutputIt == css.end()) {
		cout << "Ошибка: Один из индексов не существует." << endl;
		return;
	}

	Connection newConnection(csInput, pipeIndex, csOutput);
	auto result = connections.insert(newConnection);
	if (result.second) {
		cout << "Соединение успешно создано." << endl;
	}
	else {
		cout << "Ошибка: Такое соединение уже существует." << endl;
	}
}

void printConnections() {
	if (connections.empty()) {
		cout << "Нет соединений." << endl;
		return;
	}

	cout << "Список соединений:" << endl;
	for (const auto& connection : connections) {
		cout << "КС вход: " << connection.csInput
			<< " -> Труба: " << connection.pipe
			<< " -> КС выход: " << connection.csOutput << endl;
	}
}
