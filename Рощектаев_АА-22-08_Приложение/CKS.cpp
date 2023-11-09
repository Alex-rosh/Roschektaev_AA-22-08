#include "HKS.h"
#include "Proverka.h"
#include <iostream>
#include <string>


using namespace std;

int KStation::newKSID = 100;

std::ostream& operator << (std::ostream& out, const KStation& K)
{
	cout << "�������� ��: " << K.Name << "\n" << "���������� �����: " << K.NWorkshops <<
		"\n" << "���������� ����� � ������: " << K.WorkingWorkshops << "\n" << "����������� �������������: " << K.Efficiency << "\n";
	return out;
}

KStation::KStation()
{
	id = newKSID++;
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

void KStation::readKS(ifstream& in)
{
	in >> ws;
	getline(in, Name);
	in >> NWorkshops;
	in >> WorkingWorkshops;
	in >> Efficiency;
}

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
		cout << "������� ���������� ���������� �����, ����� �� ������ ��������� " << NWorkshops << ":\n";
		WorkingWorkshops = getInRange(0, NWorkshops);
		vivodKS();
	}

}