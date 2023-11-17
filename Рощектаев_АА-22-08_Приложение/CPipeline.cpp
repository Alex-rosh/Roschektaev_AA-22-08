#include "HPipe.h"
#include "Proverka.h"
#include <iostream>
#include <string>

using namespace std;

int Pipeline::newPipeID = 0;

std::ostream& operator << (std::ostream& out, const Pipeline& P)
{
	if (P.Name.empty())
	{
		cout << "��� ��������� ���� ��� ��������������" << endl;
	}
	else
	{
		cout << "�������� �����: " << P.Name << "\n" << "����� �����: " << P.Length <<
			"\n" << "������� �����: " << P.Diameter << "\n" << "��������� �����: " << P.Repairing << "\n";
	}
	return out;
}

Pipeline::Pipeline()
{
	id = newPipeID++;
}

int Pipeline::getPipeID() const
{
	return id;
}

void Pipeline::readPipe(ifstream& in)
{
	getline(in >> ws, Name);
	in >> Length;
	in >> Diameter;
	in >> Repairing;
}

Pipeline Pipeline::AddNewPipe()
{
	Pipeline P;
	cout << "���������� ����� �����\n" << "������� �������� �����:\n";
	P.Name = readLine();
	cout << "������� ����� �����:\n";
	getCorrect(P.Length);
	cout << "������� ������� �����:\n";
	getCorrect(P.Diameter);
	cout << "�������� ��������� �����, ��� 0 - ����� ��������, 1 - ����� ��������� � ��������� �������.\n";
	P.Repairing = getInRange(0, 1);
	cout << "��������� ������������ �������� ������:\n";
	cout << P;
	return P;
}

void Pipeline::EditPipe()
{
	if (Name.empty())
	{
		cout << "��� ��������� ���� ��� ��������������" << endl;
	}
	else
	{
		cout << "�������� ��������� �����, ��� 0 - ����� ��������, 1 - ����� ��������� � ��������� �������." << "\n";
		Repairing = getInRange(0, 1);
		cout << "����� ������� ���������������";
	}
}

void Pipeline::sohraneniePipe(ofstream& f, Pipeline& item)
{
	f << "Pipeline_flag" << "\n"
		<< item.Name << "\n"
		<< item.Length << "\n"
		<< item.Diameter << "\n"
		<< item.Repairing << "\n";
}