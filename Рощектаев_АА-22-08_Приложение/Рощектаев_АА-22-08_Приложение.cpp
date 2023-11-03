#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <unordered_map>
#include "HKS.h"
#include "HPipe.h"
#include "Proverka.h"


using namespace std;


void vivodMapPipe(unordered_map <int, Pipeline> MP)
{
	for (auto& [id, item] : MP)
	{
		cout << "ID: " << id << "\n"
			<< "Название трубы: " << item.Name << "\n"
			<< "Длина трубы: " << item.Length << "\n"
			<< "Диаметр трубы: " << item.Diameter << "\n"
			<< "Состояние трубы: " << item.Repairing << "\n";
	}
}

void sohraneniePipe(ofstream& f, unordered_map <int, Pipeline> MP, const int& id, Pipeline& item)
{
	f << id << "\n"
		<< item.Name << "\n"
		<< item.Length << "\n"
		<< item.Diameter << "\n"
		<< item.Repairing << "\n";
}

void vivodMapKS(unordered_map <int, KStation> MK)
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

void sohranenieKS(ofstream& f, unordered_map <int, KStation> MK, const int& id, KStation& item)
{
	f << id << "\n"
		<< item.Name << "\n"
		<< item.NWorkshops << "\n"
		<< item.WorkingWorkshops << "\n"
		<< item.Efficiency << "\n";
}

unordered_map <int, Pipeline> readPipes(unordered_map <int, Pipeline>& MP)
{
	ifstream in("save.txt");
	if (in.is_open()) {
		int countPipe;
		in >> countPipe;
		while (countPipe--)
		{
			Pipeline P;
			int iddd;
			in >> iddd;
			getline(in, P.Name);
			in >> P.Length;
			in >> P.Diameter;
			in >> P.Repairing;
			MP.insert({ P.getPipeID(), P });
		}
		cout << "Данные загружены" << endl;
	}
	in.close();
	return MP;
}

void readKSs(unordered_map <int, KStation>& MK)
{
	ifstream in("save.txt");
	if (in.is_open()) {
		int countKS;
		in >> countKS;
		while (countKS--)
		{
			//KStation::readKS(in, MK);
		}
	}
	in.close();
}

void sohraneniePipes(unordered_map <int, Pipeline> MP)
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
				sohraneniePipe(f, MP, id, item);
			}
		}
	}
	f.close();
	cout << "Изменения сохранены в файл" << endl;
}

void sohranenieKSs(unordered_map <int, KStation> MK)
{
	ofstream f;
	f.open("save.txt", ios::app);
	if (f.is_open())
	{
		f << MK.size() << endl;
		if (!MK.size() == 0)
		{
			for (auto& [id, item] : MK)
			{
				//KStation::sohranenieKS(f, MK, id, item);
			}
		}
	}
	f.close();
	cout << "Изменения сохранены в файл" << endl;
}

Pipeline& selectPipe(unordered_map<int, Pipeline>& MP)
{
	cout << "Enter pipe ID: ";
	int userID;
	getCorrect(userID);
	while (MP.find(userID) == MP.end())
	{
		cout << "Error! There is no pipe with this id\n";
		cout << "Enter pipe ID: ";
		getCorrect(userID);
	}
	return MP[userID];
}

void deleteOnePipe(unordered_map<int, Pipeline>& MP)
{
	Pipeline p = selectPipe(MP);
	MP.erase(p.getPipeID());
	cout << "Pipe removed!" << endl;
}


KStation& selectStation(unordered_map<int, KStation>& MK)
{
	cout << "Enter station ID: ";
	int userID;
	getCorrect(userID);
	while (MK.find(userID) == MK.end())
	{
		cout << "Error! There is no station with this id\n";
		cout << "Enter station ID: ";
		getCorrect(userID);
	}
	return MK[userID];
}

void deleteOneKS(unordered_map<int, KStation>& MK)
{
	KStation s = selectStation(MK);
	MK.erase(s.getKSID());
	cout << "Station removed!" << endl;
}

template<typename T>
using Filter2 = bool(*)(const Pipeline& p, T parameter);

bool checkByID(const Pipeline& p, int parameter)
{
	return p.getPipeID() >= parameter;
}

bool checkByRepair(const Pipeline& p, int parameter)
{
	return p.Repairing == parameter;
}

template<typename T>
vector<uint32_t> findPipeByFilter(unordered_map<int, Pipeline>& MP, Filter2<T> f, T parameter)
{
	vector<uint32_t> result;

	for (auto& [pID, p] : MP)
	{
		if (f(p, parameter))
		{
			result.push_back(p.getPipeID());
		}
	}

	if (result.empty())
	{
		cout << "There are no pipes wuth this parameter\n";
	}

	return result;
}


void FullView(unordered_map <int, Pipeline> MP, unordered_map <int, KStation> MK)
{
	int variant;
	Pipeline P;
	KStation K;
	cout << "Выберите действие" << endl;
	cout << "1. Вывести список труб" << endl;
	cout << "2. Вывести список КС" << endl;
	cout << "3. Вывести все имеющиеся данные" << endl;
	getCorrect(variant);
	switch (variant) {
	case 1:
		vivodMapPipe(MP);
		break;
	case 2:
		vivodMapKS(MK);
		break;
	case 3:
		vivodMapPipe(MP);
		vivodMapKS(MK);
		break;
	}
}

int print_menu() {
	system("cls");
	int variant;
	cout << "Выберите действие" << endl;
	cout << "1. Добавить трубу" << endl;
	cout << "2. Добавить КС" << endl;
	cout << "3. Просмотр всех объектов" << endl;
	cout << "4. Редактировать трубу" << endl;
	cout << "5. Редактировать КС" << endl;
	cout << "6. Загрузить данные" << endl;
	cout << "7. Сохранить данные" << endl;
	cout << "8. Удалить трубу" << endl;
	cout << "9. Удалить станцию" << endl;
	cout << "0. Выход" << endl;
	cout << ">>> ";
	variant = getInRange(0, 9);
	return variant;
}

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	int variant;
	variant = 1;
	unordered_map <int, Pipeline> MP;
	unordered_map <int, KStation> MK;

	do {
		int variant = print_menu();

		switch (variant) {
		case 1:
		{
			Pipeline P;
			MP.insert({ P.getPipeID(), Pipeline::AddNewPipe() });
			break;
		}
		case 2:
		{
			KStation K;
			MK.insert({ K.getKSID(), K.AddNewKS() });
			break;
		}
		case 3:
			FullView(MP, MK);
			break;
		case 4:
			selectPipe(MP).EditPipe();
			break;
		case 5:
			selectStation(MK).EditKS();
			break;
		case 6:
		{
			//readPipes(MP);
			//readKSs(MK);
		}
			break;
		case 7:
			sohraneniePipes(MP);
			sohranenieKSs(MK);
			break;
		case 8:
			deleteOnePipe(MP);
			break;
		case 9:
			deleteOneKS(MK);
			break;
		case 0:
			cout << "Выход из программы..." << endl;
			exit(EXIT_SUCCESS);
			break;
		}
		if (variant != 0)
			system("pause");
	} while (variant != 0);
	return 0;
}