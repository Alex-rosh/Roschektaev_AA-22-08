#include "HKS.h"
#include "Proverka.h"
#include <iostream>
#include <string>


using namespace std;

int KStation::newKSID = 100;

std::ostream& operator << (std::ostream& out, const KStation& K)
{
	if (K.Name.empty())
	{
		cout << "��� ��������� �� ��� ��������������" << endl;
	}
	else
	{
		cout << "�������� ��: " << K.Name << "\n" << "���������� �����: " << K.NWorkshops <<
			"\n" << "���������� ����� � ������: " << K.WorkingWorkshops << "\n" << "����������� �������������: " << K.Efficiency << "\n";
	}
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

void KStation::readKS(ifstream& in)
{
	getline(in >> ws, Name);
	in >> NWorkshops;
	in >> WorkingWorkshops;
	in >> Efficiency;
}

KStation KStation::AddNewKS()
{
	KStation K;
	cout << "���������� ����� ��\n" << "������� �������� ��:\n";
	K.Name = readLine();
	cout << "������� ���������� �����:\n";
	getCorrect(K.NWorkshops);
	cout << "������� ���������� ���������� �����:\n";
	K.WorkingWorkshops = getInRange(0, K.NWorkshops);
	cout << "������� ����������� �������������:\n";
	getCorrect(K.Efficiency);
	cout << "��������� ������������ �������� ������:\n";
	cout << K;
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
		cout << "�� ������� ���������������";
	}

}

void KStation::sohranenieKS(ofstream& f, KStation& item)
{
	f << "KStation_flag" << "\n"
		<< item.Name << "\n"
		<< item.NWorkshops << "\n"
		<< item.WorkingWorkshops << "\n"
		<< item.Efficiency << "\n";
}