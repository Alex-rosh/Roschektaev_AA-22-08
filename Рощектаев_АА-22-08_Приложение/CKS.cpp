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

void KStation::sohranenieKS(unordered_map <int, KStation> MK)
{
	ofstream f;
	f.open("save.txt", ios::app);
	if (f.is_open())
	{
		if (!MK.size() == 0)
		{
			for (const auto& pair : MK)
			{
				f << MK.size() << endl;
				f << pair.first << "\n"
					<< pair.second.Name << "\n"
					<< pair.second.NWorkshops << "\n"
					<< pair.second.WorkingWorkshops << "\n"
					<< pair.second.Efficiency << "\n";
			}
		}
		else if (MK.size() == 0)
		{
			f << 0 << endl;
		}
	}
	f.close();
	cout << "��������� ��������� � ����" << endl;
}

unordered_map <int, KStation> KStation::readKS()
{
	unordered_map <int, KStation> MK;
	KStation K;
	int id;
	ifstream in("save.txt");
	if (in.is_open()) {
		int countKS;
		in >> countKS;
		while (countKS--)
		{
			in >> id;
			getline(in, K.Name);
			in >> K.NWorkshops;
			in >> K.WorkingWorkshops;
			in >> K.Efficiency;
			MK.insert({ id, K });
		}
	}
	in.close();
	return MK;
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