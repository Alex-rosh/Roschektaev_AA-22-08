#include "HPipe.h"
#include "Proverka.h"
#include <iostream>
#include <string>

using namespace std;

int Pipeline::newPipeID = 0;

Pipeline::Pipeline()
{
	id = newPipeID++;
}

int Pipeline::getPipeID() const
{
	return id;
}

void Pipeline::setPipeID(int Pipeid)
{
	id = Pipeid;
}

void Pipeline::vivodPipe()
{
	if (Name.empty())
	{
		cout << "��� ��������� ���� ��� ��������������" << endl;
	}
	else
	{
		cout << "�������� �����: " << Name << "\n" << "����� �����: " << Length <<
			"\n" << "������� �����: " << Diameter << "\n" << "��������� �����: " << Repairing << "\n";
	}
}

void Pipeline::vivodMapPipe(unordered_map <int, Pipeline> MP)
{
	for (auto& [id, item] : MP)
	{
		cout << "ID: " << id << "\n"
			<< "�������� �����: " << item.Name << "\n"
			<< "����� �����: " << item.Length << "\n"
			<< "������� �����: " << item.Diameter << "\n"
			<< "��������� �����: " << item.Repairing << "\n";
	}
}

void Pipeline::sohraneniePipe(ofstream& f, unordered_map <int, Pipeline> MP, const int &id, Pipeline &item)
{
	f << id << "\n"
		<< item.Name << "\n"
		<< item.Length << "\n"
		<< item.Diameter << "\n"
		<< item.Repairing << "\n";
}

void Pipeline::readPipe(ifstream& in, Pipeline& P)
{
	in >> P.id;
	P.setPipeID(P.id);
	getline(in, P.Name);
	in >> P.Length;
	in >> P.Diameter;
	in >> P.Repairing;
}

Pipeline Pipeline::AddNewPipe(Pipeline& P)
{
	cout << "���������� ����� �����\n" << "������� �������� �����:\n";
	cin >> ws;
	getline(cin, P.Name);
	cout << "������� ����� �����:\n";
	getCorrect(P.Length);
	cout << "������� ������� �����:\n";
	getCorrect(P.Diameter);
	cout << "�������� ��������� �����, ��� 0 - ����� ��������, 1 - ����� ��������� � ��������� �������.\n";
	P.Repairing = getInRange(0, 1);
	cout << "��������� ������������ �������� ������:\n";
	P.vivodPipe();
	return P;
}

void Pipeline::EditPipe(Pipeline& P)
{
	if (P.Name.empty())
	{
		cout << "��� ��������� ���� ��� ��������������" << endl;
	}
	else
	{
		P.Repairing = getInRange(0, 1);
		vivodPipe();
	}
}