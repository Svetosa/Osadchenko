#pragma once
#include <iostream>
#include <string>
#include <unordered_set>
#include <sstream>
#include <fstream>
using namespace std;
class CS {
public:
	int index;
	string name;
	int quantity;
	int work_workshop;
	float efect_cs;

	CS(int index, const string& name, int quantity, int work_workshop, float efect_cs)
		: index(index), name(name), quantity(quantity), work_workshop(work_workshop), efect_cs(efect_cs) {}

	bool operator==(const CS& other) const {
		return index == other.index && name == other.name && quantity == other.quantity && work_workshop == other.work_workshop && efect_cs == other.efect_cs;
	}

	struct Hash {
		size_t operator()(const CS& cs) const {
			return hash<int>()(cs.index) ^ hash<string>()(cs.name) ^ hash<int>()(cs.quantity) ^ hash<int>()(cs.work_workshop) ^ hash<float>()(cs.efect_cs);
		}
	};
};


