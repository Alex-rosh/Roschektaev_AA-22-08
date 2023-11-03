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
		cout << "Нет доступных КС для взаимодействия" << endl;
	}
	else
	{
		cout << "Название КС: " << Name << "\n" << "Количество цехов: " << NWorkshops <<
			"\n" << "Количество цехов в работе: " << WorkingWorkshops << "\n" << "Коэффициент эффективности: " << Efficiency << "\n";
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
		cout << "Введите количество работающих цехов:\n";
		WorkingWorkshops = getInRange(0, NWorkshops);
		vivodKS();
	}

}