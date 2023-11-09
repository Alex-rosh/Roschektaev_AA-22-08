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
vector<int> findPipeByFilter(unordered_map<int, Pipeline>& mP, Filter2<T> f, T parameter)
{
	vector<int> result;

	for (auto& [pID, p] : mP)
	{
		if (f(p, parameter))
		{
			result.push_back(p.getPipeID());
		}
	}

	if (result.empty())
	{
		cout << "Трубы с такими параметрами не найдены\n";
	}

	return result;
}


template<typename T>
using Filter1 = bool(*)(const KStation& s, T parameter);

bool checkByName(const KStation& s, string parameter)
{
	return s.Name == parameter;
}

bool checkByNotWorkingWorkshops(const KStation& s, double parameter)
{
	return (double((s.NWorkshops - s.WorkingWorkshops) * 100) / s.NWorkshops) >= parameter;
}

template<typename T>
vector<int> findStationByFilter(unordered_map<int, KStation>& mS, Filter1<T> f, T parameter)
{
	vector<int> result;

	for (auto& [sID, s] : mS)
	{
		if (f(s, parameter))
		{
			result.push_back(s.getKSID());
		}
	}

	if (result.empty())
	{
		cout << "КС с такими параметрами не найдены\n";
	}

	return result;
}

vector<int> PipeSearch(unordered_map<int, Pipeline>& MP)
{
	vector<int> result{};
	cout << "Выберите параметры поиска: \n"
		<< "1 - Найти трубу по ID; \n"
		<< "2 - Найти трубу по состоянию\n";
	if (getInRange(1, 2) == 1)
	{
		int pID;
		cout << "Введите ID трубы: ";
		getCorrect(pID);
		for (int i : findPipeByFilter(MP, checkByID, pID))
		{
			cout << MP[i];
			cout << "\n";
		}
		result = findPipeByFilter(MP, checkByID, pID);
	}
	else
	{
		int repair;
		cout << "Введите состояние трубы: ";
		repair = getInRange(0, 1);
		for (int i : findPipeByFilter(MP, checkByRepair, repair))
		{
			cout << MP[i];
		}
		result = findPipeByFilter(MP, checkByRepair, repair);
	}
	return result;
}

void KSSearch(unordered_map<int, KStation>& MK)
{
	cout << "Выберите параметры поиска: \n"
		<< "1 - Найти КС по названию; \n"
		<< "2 - Найти КС по проценту не рабочих цехов\n";
	if (getInRange(1, 2) == 1)
	{
		string name;
		cout << "Введите название КС: ";
		cin >> name;
		for (int i : findStationByFilter(MK, checkByName, name))
		{
			cout << MK[i];
		}
	}
	else
	{
		double percent;
		cout << "Введите процент не рабочих цехов: ";
		getCorrect(percent);
		for (int i : findStationByFilter(MK, checkByNotWorkingWorkshops, percent))
		{
			cout << MK[i];
		}
	}
}

void PacketEditPipe(unordered_map<int, Pipeline>& mP)
{
	vector<int> allResult;
	allResult = PipeSearch(mP);

	cout << "Выберите параметры редактирования: \n"
		<< "1 - редактировать все найденные трубы; \n"
		<< "2 - редактировать определённые найденные трубы\n";
	if (getInRange(1, 2) == 1)
	{
		cout << "Выберите состояние труб: \n"
			<< "1 - все трубы работают; \n"
			<< "2 - все трубы в ремонте\n";
		if (getInRange(1, 2) == 1)
		{
			for (auto& id : allResult)
				mP[id].Repairing = 1;
		}
		else
		{
			for (auto& id : allResult)
				mP[id].Repairing = 0;
		}
	}
	else
	{
		vector <int> someResult;
		while (true)
		{
			cout << "Введите ID редактируемой трубы или 0 для продолжения: ";
			int i;
			i = getInRange(0, *max_element(allResult.begin(), allResult.end()));
			if (i)
			{
				if (mP.find(i) == mP.end())
					cout << "Труба с таким ID не найдена\n";
				else
					someResult.push_back(i);
			}
			else
				break;
		}

		cout << "Выберите состояние труб: \n"
			<< "1 - все трубы работают; \n"
			<< "2 - все трубы в ремонте\n";
		if (getInRange(1, 2) == 1)
		{
			for (auto& id : someResult)
				mP[id].Repairing = 1;
		}
		else
		{
			for (auto& id : someResult)
				mP[id].Repairing = 0;
		}
	}
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
	cout << "10. Поиск по трубам" << endl;
	cout << "11. Поиск по КС" << endl;
	cout << "12. Пакетное редактирование" << endl;
	cout << "0. Выход" << endl;
	cout << ">>> ";
	variant = getInRange(0, 12);
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
			PipeSearch(MP);
			break;
		case 11:
			KSSearch(MK);
			break;
		case 12:
			PacketEditPipe(MP);
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