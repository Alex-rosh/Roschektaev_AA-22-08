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
		cout << "Нет доступных КС для взаимодействия" << endl;
	}
	else
	{
		cout << "Название КС: " << K.Name << "\n" << "Количество цехов: " << K.NWorkshops <<
			"\n" << "Количество цехов в работе: " << K.WorkingWorkshops << "\n" << "Коэффициент эффективности: " << K.Efficiency << "\n";
	}
}

void KStation::vivodMapKS(unordered_map <int, KStation> MK)
{
	for (const auto& pair : MK)
	{
		cout << pair.first << "\n"
			<< "Название КС: " << pair.second.Name << "\n"
			<< "Количество цехов: " << pair.second.NWorkshops << "\n"
			<< "Количество цехов в работе" << pair.second.WorkingWorkshops << "\n"
			<< "Коэффициент эффективности" << pair.second.Efficiency << "\n";
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
	cout << "Добавление новой КС\n" << "Введите название КС:\n";
	cin >> ws;
	getline(cin, K.Name);
	cout << "Введите количество цехов:\n";
	getCorrect(K.NWorkshops);
	cout << "Введите количество работающих цехов:\n";
	K.WorkingWorkshops = getInRange(0, K.NWorkshops);
	cout << "Введите коэффициент эффективности:\n";
	getCorrect(K.Efficiency);
	cout << "Проверьте корректность введённых данных:\n";
	vivodKS(K);
	return K;
}

void KStation::EditKS(KStation& K)
{
	if (K.Name.empty())
	{
		cout << "Нет доступных КС для взаимодействия" << endl;
	}
	else
	{
		cout << "Введите количество работающих цехов:\n";
		K.WorkingWorkshops = getInRange(0, K.NWorkshops);
		vivodKS(K);
	}

}