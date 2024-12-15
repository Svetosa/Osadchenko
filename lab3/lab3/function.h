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
				cout << "�� ������ �� �����, ���������� ����� :)" << endl << endl;
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
				cout << "�� ������ �� �����, ���������� ����� :)" << endl << endl;
				continue;
			}

			bool isValid = true;
			for (char c : input) {
				if (!isdigit(c)) {
					cout << "������� ������������ �����, ��������� ����� :)" << endl << endl;
					isValid = false;
					break;
				}
			}
			if (isValid) {
				try {
					if (input[0] == '0' && input.size() > 1) {
						cout << "����� �� ����� ���������� � 0, ���������� ����� :)" << endl << endl;
						continue;
					}
					result = stoi(input);
					if (min <= result && result <= max) {
						return result;
					}
					else {
						cout << "������� �������� ��������, ���������� ����� :)" << endl << endl;
					}
				}
				catch (const invalid_argument& e) {
					cout << "������ ����� ����� " << endl << endl;
				}
				catch (const out_of_range& e) {
					cout << "����� ��� ��������� �������� " << endl << endl;
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
				cout << "�� ������ �� �����, ��������� �����" << endl << endl;
				continue;
			}

			try {
				size_t pos;
				result = stof(input, &pos);
				if (pos < input.size()) {
					cout << "������: ������������ ���� ����� � ��������� ������" << endl << endl;
				}
				else if (result < min || result > max) {
					cout << "����� ��� ����������� ���������" << min << " - " << max << ")." << endl << endl;
				}
				else {
					return result;
				}
			}
			catch (const invalid_argument&) {
				cout << "������ ����� ����� � ��������� ������" << endl << endl;
			}
			catch (const out_of_range&) {
				cout << "����� ��� ��������� ��������" << endl << endl;
			}
		}
	}
}

template<typename T>
bool validateInput(const string& input, T& result, int min, int max) {
	if constexpr (is_same<T, string>::value) {
		if (input.empty()) {
			cout << "������: ������ �����." << endl;
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
				cout << "������: ������������ ���� �����." << endl;
				return false;
			}
			if (value < min || value > max) {
				cout << "������: �������� ��� ���������" << endl;
				return false;
			}
			result = value;
			return true;
		}
		catch (const invalid_argument&) {
			cout << "������: ������������ ���� �����." << endl;
			return false;
		}
		catch (const out_of_range&) {
			cout << "������: �������� ��� ��������� int." << endl;
			return false;
		}
	}
	else if constexpr (is_same<T, double>::value) {
		try {
			size_t pos;
			double value = stod(input, &pos);
			if (pos < input.size()) {
				cout << "������: ������������ ���� ����� � ��������� ������." << endl;
				return false;
			}
			if (value < min || value > max) {
				cout << "������: �������� ��� ���������" << endl;
				return false;
			}
			result = value;
			return true;
		}
		catch (const invalid_argument&) {
			cout << "������: ������������ ���� ����� � ��������� ������." << endl;
			return false;
		}
		catch (const out_of_range&) {
			cout << "������: �������� ��� ��������� double." << endl;
			return false;
		}
	}
	return false;
}
