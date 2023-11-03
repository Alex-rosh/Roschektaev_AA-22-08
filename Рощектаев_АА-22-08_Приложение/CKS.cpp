#include "HKS.h"
#include "Proverka.h"
#include <iostream>
#include <string>

using namespace std;

int KStation::newPipeID = 0;

KStation::KStation()
{
	id = newPipeID++;
}

int KStation::getKSID() const
{
	return id;
}

void KStation::vivodKS()
{
	if (Name.empty())
	{
		cout << "��� ��������� �� ��� ��������������" << endl;
	}
	else
	{
		cout << "�������� ��: " << Name << "\n" << "���������� �����: " << NWorkshops <<
			"\n" << "���������� ����� � ������: " << WorkingWorkshops << "\n" << "����������� �������������: " << Efficiency << "\n";
	}
}

//void KStation::readKS(ifstream& in, unordered_map <int, KStation>& MK)
//{
//	KStation K;
//	in >> K.id;
//	getline(in, K.Name);
//	in >> K.NWorkshops;
//	in >> K.WorkingWorkshops;
//	in >> K.Efficiency;
//	MK.insert({ K.id, K});
//}

KStation KStation::AddNewKS()
{
	KStation K;
	cout << "���������� ����� ��\n" << "������� �������� ��:\n";
	cin >> ws;
	getline(cin, K.Name);
	cout << "������� ���������� �����:\n";
	getCorrect(K.NWorkshops);
	cout << "������� ���������� ���������� �����:\n";
	K.WorkingWorkshops = getInRange(0, K.NWorkshops);
	cout << "������� ����������� �������������:\n";
	getCorrect(K.Efficiency);
	cout << "��������� ������������ �������� ������:\n";
	K.vivodKS();
	return K;
}

void KStation::EditKS()
{
	if (Name.empty())
	{
		cout << "��� ��������� �� ��� ��������������" << endl;
	}
	else
	{
		cout << "������� ���������� ���������� �����:\n";
		WorkingWorkshops = getInRange(0, NWorkshops);
		vivodKS();
	}

}