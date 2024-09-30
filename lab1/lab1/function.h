#pragma once
#include <string>
using namespace std;

struct truba {
	string kilometr_mark = ""; //������������ �������(��������)
	unsigned int length = 0; //����� �����
	unsigned int diameter = 0; //������� �����
	bool Remote;
};
struct compr_station {
	string cs_name = ""; //�������� ��
	int workshop = 0; // ���-�� �����
	int operation_workshop = 0; // ���-�� ����� ������
	int effectiveness = 0; //�������������
};
void add_truba(truba& t);
void add_cs(compr_station&cs);
void all_objects(truba& t, compr_station& cs);
void edit_pipe(truba& t);
void edit_cs(compr_station&cs);
void save(truba& t, compr_station& cs);
void upload(truba& t, compr_station& cs);

