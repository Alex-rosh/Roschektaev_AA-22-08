#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <unordered_map>
#include "HKS.h"
#include "HPipe.h"
#include "Proverka.h"


using namespace std;

unordered_map <int, Pipeline> Pipeline::readPipes()
{
	unordered_map <int, Pipeline> MP;
	ifstream in("save.txt");
	if (in.is_open()) {
		int countPipe;
		in >> countPipe;
		while (countPipe--)
		{
			Pipeline::readPipe(in, MP);
		}
		cout << "Данные загружены" << endl;
	}
	return MP;
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
	getCorrect(variant);
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
			MP.insert({ P.getPipeID(), P.AddNewPipe() });
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
			//EditPipe(P);
			break;
		case 5:
			//EditKS(K);
			break;
		case 6:
			//MP = P.readPipe();
			//MK = K.readKS();
			break;
		case 7:
			//P.sohraneniePipe(MP);
			//K.sohranenieKS(MK);
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