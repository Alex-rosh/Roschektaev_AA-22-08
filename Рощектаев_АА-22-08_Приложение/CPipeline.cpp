#include "HPipe.h"
#include "Proverka.h"
#include <iostream>
#include <string>

using namespace std;

int Pipeline::newPipeID = 0;

Pipeline::Pipeline()
{
	id = ++newPipeID;
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

void Pipeline::vivodMapPipe(unordered_map <int, Pipeline> MP)
{
	for (const auto& pair : MP)
	{
		cout << "ID: " << pair.first << "\n"
			<< "�������� �����: " << pair.second.Name << "\n"
			<< "����� �����: " << pair.second.Length << "\n"
			<< "������� �����: " << pair.second.Diameter << "\n"
			<< "��������� �����: " << pair.second.Repairing << "\n";
	}
}

void Pipeline::sohraneniePipe(unordered_map <int, Pipeline> MP)
{
	ofstream f;
	f.open("save.txt", ios::out);
	if (f.is_open())
	{
		f << MP.size() << endl;
		if (!MP.size() == 0)
		{
			for (auto& [id, item] : MP)
			{
				f << id << "\n"
					<< item.Name << "\n"
					<< item.Length << "\n"
					<< item.Diameter << "\n"
					<< item.Repairing << "\n";
			}
		}
		else if (MP.size() == 0)
		{
			f << 0 << endl;
		}
	}
	f.close();
	cout << "��������� ��������� � ����" << endl;
}

void Pipeline::readPipe(ifstream in, unordered_map <int, Pipeline> MP)
{
	Pipeline P;
	getline(in, P.Name);
	in >> P.Length;
	in >> P.Diameter;
	in >> P.Repairing;
	MP.insert({ P.getPipeID(), P });
}

Pipeline Pipeline::AddNewPipe()
{
	Pipeline P;
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