#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>


using namespace std;

struct Pipe
{
	string Name;
	int Length;
	int Diameter;
	bool Repairing;
};

struct KS
{
	string Name;
	int NWorkshops;
	int WorkingWorkshops;
	double Efficiency;
};

int proverka()
{
	int x;
	while ((cin >> x).fail() || std::cin.peek() != '\n' || x < 0)
	{
		cout << "Повторите ввод числа:" << endl;
		cin.clear();
		cin.ignore(1000, '\n');
	}
	return x;
}

void vivodPipe(const Pipe& P)
{
	if (P.Name.empty())
	{
		cout << "Нет доступных труб для взаимодействия" << endl;
	}
	else
	{
		cout << "Название трубы: " << P.Name << "\n" << "Длина трубы: " << P.Length <<
			"\n" << "Диаметр трубы: " << P.Diameter << "\n" << "Состояние трубы: " << P.Repairing << "\n";
	}
}

void vivodKS(const KS& K)
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

void sohraneniePipe(const Pipe& P)
{
	ofstream f;
	f.open("save.txt", ios::out);
	if (f.is_open() && !P.Name.empty())
	{
		f << "Pipes" << "\n";
		f << P.Name << "\n";
		f << P.Length << "\n";
		f << P.Diameter << "\n";
		f << P.Repairing << "\n";
	}
	f.close();
	cout << "Изменения сохранены в файл" << endl;
}

void sohranenieKS(const KS& K)
{
	ofstream f;
	f.open("save.txt", ios::app);
	if (f.is_open() && !K.Name.empty())
	{
		f << "KS" << "\n";
		f << K.Name << "\n";
		f << K.NWorkshops << "\n";
		f << K.WorkingWorkshops << "\n";
		f << K.Efficiency << "\n";
	}
	f.close();
	cout << "Изменения сохранены в файл" << endl;
}

void readPipe(Pipe& P)
{
	string flag;
	ifstream in("save.txt");
	if (in.is_open()) {
		getline(in, flag);
		while (!flag.empty())
		{
			if (flag == "Pipes")
			{
				getline(in, P.Name);
				in >> P.Length;
				in >> P.Diameter;
				in >> P.Repairing;
			}
			getline(in, flag);
		}
	}
	in.close();
}

void readKS(KS& K)
{
	string flag;
	ifstream in("save.txt");
	if (in.is_open()) {
		getline(in, flag);
		while (!flag.empty())
		{
			if (flag == "KS")
			{
				getline(in, K.Name);
				in >> K.NWorkshops;
				in >> K.WorkingWorkshops;
				in >> K.Efficiency;
			}
			getline(in, flag);
		}
	}
	in.close();
}

bool sost()
{
	bool sost;
	while (true)
	{
		cout << "Выберите состояние трубы, где 0 - труба работает, 1 - труба находится в состоянии ремонта.\n";
		cin >> sost;
		if (!cin)
		{
			cout << "Введите, пожалуйста, 0 или 1\n";
			cin.clear();
			cin.ignore(1000, '\n');
		}
		else break;
	}
	return sost;
}

Pipe AddNewPipe()
{	
	Pipe P;
	cout << "Добавление новой трубы\n" << "Введите название трубы:\n";
	cin >> ws;
	getline(cin, P.Name);
	cout << "Введите длину трубы:\n";
	P.Length = proverka();
	cout << "Введите диаметр трубы:\n";
	P.Diameter = proverka();
	P.Repairing = sost();
	cout << "Проверьте корректность введённых данных:\n";
	vivodPipe(P);
	return P;
}

KS AddNewKS()
{
	KS K;
	cout << "Добавление новой КС\n" << "Введите название КС:\n";
	cin >> ws;
	getline(cin, K.Name);
	cout << "Введите количество цехов:\n";
	K.NWorkshops = proverka();
	cout << "Введите количество работающих цехов:\n";
	while (true)
	{
		cout << "Введите количество работающих цехов:\n";
		cin >> K.WorkingWorkshops;
		if (!cin || K.WorkingWorkshops < 0 || K.WorkingWorkshops > K.NWorkshops)
		{
			cout << "Введите, пожалуйста, корректное число\n";
			cin.clear();
			while (cin.get() != '\n');
		}
		else break;
	}
	while (true)
	{
		cout << "Введите коэффициент эффективности:\n";
		cin >> K.Efficiency;
		if (!cin || K.Efficiency < 0)
		{
			cout << "Введите, пожалуйста, корректное число\n";
			cin.clear();
			while (cin.get() != '\n');
		}
		else break;
	}
	cout << "Проверьте корректность введённых данных:\n";
	vivodKS(K);
	return K;
}

void FullView(const Pipe& P, const KS& K)
{
	int variant;
	cout << "Выберите действие" << endl;
	cout << "1. Вывести список труб" << endl;
	cout << "2. Вывести список КС" << endl;
	cout << "3. Вывести все имеющиеся данные" << endl;
	variant = proverka();
	switch (variant) {
	case 1:
		vivodPipe(P);
		break;
	case 2:
		vivodKS(K);
		break;
	case 3:
		vivodPipe(P);
		vivodKS(K);
		break;
	}
}

void EditPipe(Pipe& P)
{
	if (P.Name.empty())
	{
		cout << "Нет доступных труб для взаимодействия" << endl;
	}
	else
	{
		P.Repairing = sost();
		vivodPipe(P);
	}
}

void EditKS(KS& K)
{
	if (K.Name.empty())
	{
		cout << "Нет доступных КС для взаимодействия" << endl;
	}
	else
	{
		while (true)
		{
			cout << "Введите количество работающих цехов.\n";
			cin >> K.WorkingWorkshops;
			if (!cin || K.WorkingWorkshops > K.NWorkshops || K.WorkingWorkshops < 0)
			{
				cout << "Введите, пожалуйста, корректное число, оно не должно превышать " << K.NWorkshops << endl;
				cin.clear();
				cin.ignore(1000, '\n');
			}
			else break;
		}
		vivodKS(K);
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
	variant = proverka();
	return variant;
}

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	Pipe P;
	KS K;
	int variant;
	variant = 1;
	do {
		int variant = print_menu();

		switch (variant) {
		case 1:
			P = AddNewPipe();
			break;
		case 2:
			K = AddNewKS();
			break;
		case 3:
			FullView(P, K);
			break;
		case 4:
			EditPipe(P);
			break;
		case 5:
			EditKS(K);
			break;
		case 6:
			readPipe(P);
			readKS(K);
			break;
		case 7:
			sohraneniePipe(P);
			sohranenieKS(K);
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