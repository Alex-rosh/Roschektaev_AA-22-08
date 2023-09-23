#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <cstring>

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
	while (true)
	{
		cin >> x;
		if (!cin || (x < 0))
		{
			cout << "Введите, пожалуйста, число\n";
			cin.clear();
			while (cin.get() != '\n');
		}
		else break;
	}
	return x;
}

void vivodPipe(Pipe N)
{
	cout << "Проверьте корректность введённых данных:\n" << "Название трубы: " << N.Name << "\n" << "Длина трубы: " << N.Length <<
		"\n" << "Диаметр трубы: " << N.Diameter << "\n" << "Состояние трубы: " << N.Repairing << "\n";
}

void vivodKS(KS K)
{
	cout << "Проверьте корректность введённых данных:\n" << "Название КС: " << K.Name << "\n" << "Количество цехов: " << K.NWorkshops <<
		"\n" << "Количество цехов в работе: " << K.WorkingWorkshops << "\n" << "Коэффициент эффективности: " << K.Efficiency << "\n";
}

void sohrPipe(Pipe N)
{
	cout << "Сохраняем? [Да/Нет]\n";
	string sohr;
	cin >> sohr;
	string S;
	S = N.Name + " " + to_string(N.Length) + " " + to_string(N.Diameter) + " " + to_string(N.Repairing) + "\n";
	if (sohr == "Да") {
		ofstream f;
		f.open("save.txt", ios::out);
		if (f.is_open())
		{
			f << S;
		}
		f.close();
		cout << "Изменения сохранены в файл" << endl;
	}
	else if (sohr == "Нет") {
		return;
	}
	else {
		cout << "Я вас не понимаю.\n";
	}
}

void sohrKS(KS K)
{
	cout << "Сохраняем? [Да/Нет]\n";
	string sohr;
	cin >> sohr;
	string S;
	S = K.Name + " " + to_string(K.NWorkshops) + " " + to_string(K.WorkingWorkshops) + " " + to_string(K.Efficiency) + "\n";
	if (sohr == "Да") {
		ofstream f;
		f.open("saveKS.txt", ios::out);
		if (f.is_open())
		{
			f << S;
		}
		f.close();
		cout << "Изменения сохранены в файл" << endl;
	}
	else if (sohr == "Нет") {
		return;
	}
	else {
		cout << "Я вас не понимаю.\n";
	}
}

Pipe readPipe()
{
	Pipe N;
	cout << "Список всех труб:\n";
	ifstream in("save.txt");
	if (in.is_open()) {
		in >> N.Name >> N.Length >> N.Diameter >> N.Repairing;
	}
	in.close();
	cout << N.Name << " " << N.Length << " " << N.Diameter << " " << N.Repairing << endl;
	return N;
}

KS readKS()
{
	KS K;
	cout << "Список всех КС:\n";
	ifstream in("saveKS.txt");
	if (in.is_open()) {
		in >> K.Name >> K.NWorkshops >> K.WorkingWorkshops >> K.Efficiency;
		cout << K.Name << " " << K.NWorkshops << " " << K.WorkingWorkshops << " " << K.Efficiency << endl;
	}
	in.close();
	return K;
}

bool sost()
{
	Pipe N;
	while (true)
	{
		cout << "Выберите состояние трубы, где 0 - труба работает, 1 - труба находится в состоянии ремонта.\n";
		cin >> N.Repairing;
		if (!cin)
		{
			cout << "Введите, пожалуйста, 0 или 1\n";
			cin.clear();
			while (cin.get() != '\n');
		}
		else break;
	}
	return N.Repairing;
}

void AddNewPipe()
{	
	Pipe N;
	cout << "Добавление новой трубы\n" << "Введите название трубы:\n";
	cin >> N.Name;
	cout << "Введите длину трубы:\n";
	N.Length = proverka();
	cout << "Введите диаметр трубы:\n";
	N.Diameter = proverka();
	N.Repairing = sost();
	vivodPipe(N);
	sohrPipe(N);
}

void AddNewKS()
{
	KS K;
	cout << "Добавление новой КС\n" << "Введите название КС:\n";
	cin >> K.Name;
	cout << "Введите количество цехов:\n";
	K.NWorkshops = proverka();
	cout << "Введите количество работающих цехов:\n";
	K.WorkingWorkshops = proverka();
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
	vivodKS(K);
	sohrKS(K);
}

void FullView()
{
	readPipe();

	readKS();
}

void EditPipe()
{
	Pipe N;
	N = readPipe();
	N.Repairing = sost();
	vivodPipe(N);
	sohrPipe(N);
}

void EditKS()
{
	KS K;
	K = readKS();
	while (true)
	{
		cout << "Введите количество работающих цехов.\n";
		cin >> K.WorkingWorkshops;
		if (!cin || K.WorkingWorkshops > K.NWorkshops || K.WorkingWorkshops < 0)
		{
			cout << "Введите, пожалуйста, корректное число\n";
			cin.clear();
			while (cin.get() != '\n');
		}
		else break;
	}
	vivodKS(K);
	sohrKS(K);
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
	cout << "0. Выход" << endl;
	cout << ">>> ";
	cin >> variant;
	return variant;
}

int menu_choice()
{	
	int variant;
	variant = 1;
	do {
		int variant = print_menu();

		switch (variant) {
		case 1:
			AddNewPipe();
			break;
		case 2:
			AddNewKS();
			break;
		case 3:
			FullView();
			break;
		case 4:
			EditPipe();
			break;
		case 5:
			EditKS();
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

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	menu_choice();
	return 0;
}