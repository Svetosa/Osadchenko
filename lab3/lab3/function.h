void pipeadd();
void Print();
void loggir(const string& message);
void addCS();
void save();
void load();
void filter();
void addConnection();
void printConnections();

template<typename T>
T getInput(string str, int min, int max) {
	string input;
	T result;
	if constexpr (is_same<T, string>::value) {
		while (true) {
			cout << str;
			getline(cin, input);
			loggir(input);
			if (input.empty()) {
				cout << "Вы ничего не ввели, попробуйте снова :)" << endl << endl;
				continue;
			}
			result = input;
			return result;
		}
	}
	else if constexpr (is_same<T, int>::value) {
		while (true) {
			cout << str;
			getline(cin, input);
			loggir(input);
			if (input.empty()) {
				cout << "Вы ничего не ввели, попробуйте снова :)" << endl << endl;
				continue;
			}

			bool isValid = true;
			for (char c : input) {
				if (!isdigit(c)) {
					cout << "Введено неправильное число, повторите снова :)" << endl << endl;
					isValid = false;
					break;
				}
			}
			if (isValid) {
				try {
					if (input[0] == '0' && input.size() > 1) {
						cout << "Число не может начинаться с 0, попробуйте снова :)" << endl << endl;
						continue;
					}
					result = stoi(input);
					if (min <= result && result <= max) {
						return result;
					}
					else {
						cout << "введено неверное значение, попробуйте снова :)" << endl << endl;
					}
				}
				catch (const invalid_argument& e) {
					cout << "Ошибка ввода числа " << endl << endl;
				}
				catch (const out_of_range& e) {
					cout << "Число вне диапазона значений " << endl << endl;
				}
			}
		}
	}
	else if constexpr (is_same<T, float>::value || is_same<T, double>::value) {
		while (true) {
			cout << str;
			getline(cin, input);
			loggir(input);
			if (input.empty()) {
				cout << "Вы ничего не ввели, попробйте снова" << endl << endl;
				continue;
			}

			try {
				size_t pos;
				result = stof(input, &pos);
				if (pos < input.size()) {
					cout << "Ошибка: некорректный ввод числа с плавающей точкой" << endl << endl;
				}
				else if (result < min || result > max) {
					cout << "Число вне допустимого диапазона" << min << " - " << max << ")." << endl << endl;
				}
				else {
					return result;
				}
			}
			catch (const invalid_argument&) {
				cout << "Ошибка ввода числа с плавающей точкой" << endl << endl;
			}
			catch (const out_of_range&) {
				cout << "Число вне диапазона значений" << endl << endl;
			}
		}
	}
}

template<typename T>
bool validateInput(const string& input, T& result, int min, int max) {
	if constexpr (is_same<T, string>::value) {
		if (input.empty()) {
			cout << "Ошибка: строка пуста." << endl;
			return false;
		}
		result = input;
		return true;
	}
	else if constexpr (is_same<T, int>::value) {
		try {
			size_t pos;
			int value = stoi(input, &pos);
			if (pos < input.size()) {
				cout << "Ошибка: некорректный ввод числа." << endl;
				return false;
			}
			if (value < min || value > max) {
				cout << "Ошибка: значение вне диапазона" << endl;
				return false;
			}
			result = value;
			return true;
		}
		catch (const invalid_argument&) {
			cout << "Ошибка: некорректный ввод числа." << endl;
			return false;
		}
		catch (const out_of_range&) {
			cout << "Ошибка: значение вне диапазона int." << endl;
			return false;
		}
	}
	else if constexpr (is_same<T, double>::value) {
		try {
			size_t pos;
			double value = stod(input, &pos);
			if (pos < input.size()) {
				cout << "Ошибка: некорректный ввод числа с плавающей точкой." << endl;
				return false;
			}
			if (value < min || value > max) {
				cout << "Ошибка: значение вне диапазона" << endl;
				return false;
			}
			result = value;
			return true;
		}
		catch (const invalid_argument&) {
			cout << "Ошибка: некорректный ввод числа с плавающей точкой." << endl;
			return false;
		}
		catch (const out_of_range&) {
			cout << "Ошибка: значение вне диапазона double." << endl;
			return false;
		}
	}
	return false;
}
