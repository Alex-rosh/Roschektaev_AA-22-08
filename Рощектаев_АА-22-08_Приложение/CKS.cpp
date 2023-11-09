#include "HKS.h"
#include "Proverka.h"
#include <iostream>
#include <string>


using namespace std;

int KStation::newKSID = 100;

std::ostream& operator << (std::ostream& out, const KStation& K)
{
	cout << "Название КС: " << K.Name << "\n" << "Количество цехов: " << K.NWorkshops <<
		"\n" << "Количество цехов в работе: " << K.WorkingWorkshops << "\n" << "Коэффициент эффективности: " << K.Efficiency << "\n";
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
		cout << "Нет доступных КС для взаимодействия" << endl;
	}
	else
	{
		cout << "Название КС: " << Name << "\n" << "Количество цехов: " << NWorkshops <<
			"\n" << "Количество цехов в работе: " << WorkingWorkshops << "\n" << "Коэффициент эффективности: " << Efficiency << "\n";
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
	K.vivodKS();
	return K;
}

void KStation::EditKS()
{
	if (Name.empty())
	{
		cout << "Нет доступных КС для взаимодействия" << endl;
	}
	else
	{
		cout << "Введите количество работающих цехов, число не должно превышать " << NWorkshops << ":\n";
		WorkingWorkshops = getInRange(0, NWorkshops);
		vivodKS();
	}

}