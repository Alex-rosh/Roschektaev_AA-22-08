#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <unordered_map>
#include "HKS.h"
#include "HPipe.h"
#include "Proverka.h"


using namespace std;

unordered_map <int, Pipeline> readPipes(unordered_map <int, Pipeline>& MP)
{
	ifstream in("save.txt");
	if (in.is_open()) {
		int countPipe;
		in >> countPipe;
		while (countPipe--)
		{
			//Pipeline::readPipe(in, P);
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
			KStation::readKS(in, MK);
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
				Pipeline::sohraneniePipe(f, MP, id, item);
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
				KStation::sohranenieKS(f, MK, id, item);
			}
		}
	}
	f.close();
	cout << "Изменения сохранены в файл" << endl;
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
		P.vivodMapPipe(MP);
		break;
	case 2:
		K.vivodMapKS(MK);
		break;
	case 3:
		P.vivodMapPipe(MP);
		K.vivodMapKS(MK);
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
	cout << "0. Выход" << endl;
	cout << ">>> ";
	variant = getInRange(0, 7);
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
			MP.insert({ P.getPipeID(), P.AddNewPipe(P) });
			break;
		}
		case 2:
		{
			KStation K;
			MK.insert({ K.getKSID(), K.AddNewKS(K) });
			break;
		}
		case 3:
			FullView(MP, MK);
			break;
		case 4:
			//EditPipe(P);
			break;
		case 5:
			//EditKS(K);
			break;
		case 6:
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
					P.setPipeID(iddd);
					getline(in, P.Name);
					in >> P.Length;
					in >> P.Diameter;
					in >> P.Repairing;
					MP.insert({ P.getPipeID(), P });
					
				}
				cout << "Данные загружены" << endl;
			}
			in.close();
			//readKSs(MK);
		}
			break;
		case 7:
			sohraneniePipes(MP);
			sohranenieKSs(MK);
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