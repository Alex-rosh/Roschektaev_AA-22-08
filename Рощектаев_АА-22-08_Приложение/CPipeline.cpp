#include "HPipe.h"
#include "Proverka.h"
#include <iostream>
#include <string>

using namespace std;

int Pipeline::newPipeID = 0;

std::ostream& operator << (std::ostream& out, const Pipeline& P)
{
	cout << "�������� �����: " << P.Name << "\n" << "����� �����: " << P.Length <<
		"\n" << "������� �����: " << P.Diameter << "\n" << "��������� �����: " << P.Repairing << "\n";
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

void Pipeline::readPipe(ifstream& in)
{
	in >> ws;
	getline(in, Name);
	in >> Length;
	in >> Diameter;
	in >> Repairing;
}

Pipeline Pipeline::AddNewPipe()
{
	Pipeline P;
	cout << "���������� ����� �����\n" << "������� �������� �����:\n";
	cin >> ws;
	getline(cin, P.Name);
	cerr << P.Name << "\n";
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
		vivodPipe();
	}
}