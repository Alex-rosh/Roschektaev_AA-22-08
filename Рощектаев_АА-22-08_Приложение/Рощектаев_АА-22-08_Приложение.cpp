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
	f << "Pipeline_flag" << "\n"
		<< item.Name << "\n"
		<< item.Length << "\n"
		<< item.Diameter << "\n"
		<< item.Repairing << "\n";
}

void vivodMapKS(unordered_map <int, KStation> MK)
{
	for (auto& [id, item] : MK)
	{
		cout << "ID: " << id << "\n"
			<< "Название КС: " << item.Name << "\n"
			<< "Количество цехов: " << item.NWorkshops << "\n"
			<< "Количество цехов в работе: " << item.WorkingWorkshops << "\n"
			<< "Коэффициент эффективности: " << item.Efficiency << "\n";
	}
}

void sohranenieKS(ofstream& f, unordered_map <int, KStation> MK, const int& id, KStation& item)
{
	f << "KStation_flag" << "\n"
		<< item.Name << "\n"
		<< item.NWorkshops << "\n"
		<< item.WorkingWorkshops << "\n"
		<< item.Efficiency << "\n";
}

unordered_map <int, Pipeline> readPipes(unordered_map <int, Pipeline>& MP, string iFileName)
{
	ifstream in(iFileName);
	if (in.is_open()) {
		while (!in.eof())
		{
			string flag;
			in >> flag;
			if (flag == "Pipeline_flag")
			{
				Pipeline P;
				P.readPipe(in);
				MP.insert({ P.getPipeID(), P });
			}
		}
		cout << "Данные загружены" << endl;
	}
	in.close();
	return MP;
}

unordered_map <int, KStation> readKSs(unordered_map <int, KStation>& MK, string iFileName)
{
	ifstream in(iFileName);
	if (in.is_open()) {
		while (!in.eof())
		{
			string flag;
			in >> flag;
			if (flag == "KStation_flag")
			{
				KStation K;
				K.readKS(in);
				MK.insert({ K.getKSID(), K });
			}
		}
	}
	in.close();
	return MK;
}

void sohraneniePipes(unordered_map <int, Pipeline> MP, string iFileName)
{
	ofstream f;
	f.open(iFileName, ios::out);
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

void sohranenieKSs(unordered_map <int, KStation> MK, string iFileName)
{
	ofstream f;
	f.open(iFileName, ios::app);
	if (f.is_open())
	{
		f << MK.size() << endl;
		if (!MK.size() == 0)
		{
			for (auto& [id, item] : MK)
			{
				sohranenieKS(f, MK, id, item);
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

//void PipeSearch(unordered_map<int, Pipeline>& MP)
//{
//	cout << "Enter the search parameter: \n"
//		<< "1 - find pipe by IDs; \n"
//		<< "2 - find pipe by the repair\n";
//	if (getInRange(1, 2) == 1)
//	{
//		int pID;
//		cout << "Enter pipe IDs: ";
//		getCorrect(pID);
//		for (int i : findPipeByFilter(MP, Pipeline::checkByID, pID))
//		{
//			MP[i].vivodPipe();
//		}
//	}
//	else
//	{
//		int repair;
//		cout << "Enter marker of repair: ";
//		repair = getInRange(0, 1);
//		for (int i : findPipeByFilter(MP, Pipeline::checkByRepair, repair))
//		{
//			MP[i].vivodPipe();
//		}
//	}
//}

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
			cout << "Введите имя файла: ";
			string iFileName;
			cin >> ws;
			getline(cin, iFileName);
			iFileName = iFileName + ".txt";
			readPipes(MP, iFileName);
			readKSs(MK, iFileName);
		}
			break;
		case 7:
		{
			cout << "Введите имя файла: ";
			string iFileName;
			cin >> ws;
			getline(cin, iFileName);
			iFileName = iFileName + ".txt";
			sohraneniePipes(MP, iFileName);
			sohranenieKSs(MK, iFileName);
		}
			break;
		case 8:
			deleteOnePipe(MP);
			break;
		case 9:
			deleteOneKS(MK);
			break;
		case 10:

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