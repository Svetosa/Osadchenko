#pragma once
#include <iostream>
#include <string>
#include <unordered_set>
#include <stdexcept>
using namespace std;
class Pipe {
public:
	int index;
	string name;
	int length;                 
	int diameter;             
	bool repairStatus;

	Pipe(int index, const string& name, int length, int diameter, bool repairStatus)
		: index(index), name(name), length(length), diameter(diameter), repairStatus(repairStatus) {}

	bool operator==(const Pipe& other) const {
		return index == other.index && name == other.name && length == other.length && diameter == other.diameter && repairStatus == other.repairStatus;
	}

	struct Hash {
		size_t operator()(const Pipe& p) const {
			return hash<int>()(p.index) ^ hash<string>()(p.name) ^ hash<int>()(p.length) ^ hash<int>()(p.diameter) ^ hash<bool>()(p.repairStatus);
		}
	};
};


