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

void KStation::vivodKS(const KStation& K)
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
}

void KStation::vivodMapKS(unordered_map <int, KStation> MK)
{
	for (const auto& pair : MK)
	{
		cout << pair.first << "\n"
			<< "�������� ��: " << pair.second.Name << "\n"
			<< "���������� �����: " << pair.second.NWorkshops << "\n"
			<< "���������� ����� � ������" << pair.second.WorkingWorkshops << "\n"
			<< "����������� �������������" << pair.second.Efficiency << "\n";
	}
}

void KStation::sohranenieKS(ofstream& f, unordered_map <int, KStation> MK, const int& id, KStation& item)
{
	f << id << "\n"
		<< item.Name << "\n"
		<< item.NWorkshops << "\n"
		<< item.WorkingWorkshops << "\n"
		<< item.Efficiency << "\n";
}

void KStation::readKS(ifstream& in, unordered_map <int, KStation>& MK)
{
	KStation K;
	in >> K.id;
	getline(in, K.Name);
	in >> K.NWorkshops;
	in >> K.WorkingWorkshops;
	in >> K.Efficiency;
	MK.insert({ K.id, K});
}

KStation KStation::AddNewKS(KStation& K)
{
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
	vivodKS(K);
	return K;
}

void KStation::EditKS(KStation& K)
{
	if (K.Name.empty())
	{
		cout << "��� ��������� �� ��� ��������������" << endl;
	}
	else
	{
		cout << "������� ���������� ���������� �����:\n";
		K.WorkingWorkshops = getInRange(0, K.NWorkshops);
		vivodKS(K);
	}

}