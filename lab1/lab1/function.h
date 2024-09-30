#pragma once
#include <string>
using namespace std;

struct truba {
	string kilometr_mark = ""; //Километровая отметка(название)
	unsigned int length = 0; //Длина трубы
	unsigned int diameter = 0; //Диаметр трубы
	bool Remote;
};
struct compr_station {
	string cs_name = ""; //Название КС
	int workshop = 0; // Кол-во цехов
	int operation_workshop = 0; // Кол-во цехов работе
	int effectiveness = 0; //Эффективность
};
void add_truba(truba& t);
void add_cs(compr_station&cs);
void all_objects(truba& t, compr_station& cs);
void edit_pipe(truba& t);
void edit_cs(compr_station&cs);
void save(truba& t, compr_station& cs);
void upload(truba& t, compr_station& cs);

