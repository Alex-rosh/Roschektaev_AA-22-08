#include <iostream>
#include <windows.h>
#include <fstream>
#include <string>
#include <cstring>

using namespace std;

struct Pipe
{
	char Name[10];
	int Length;
	int Diameter;
	bool Repairing;
};

struct KS
{
	char Name[10];
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

void AddNewPipe()
{	
	Pipe N;
	cout << "Добавление новой трубы\n" << "Введите название трубы:\n";
	cin >> N.Name;
	cout << "Введите длину трубы:\n";
	N.Length = proverka();
	cout << "Введите диаметр трубы:\n";
	N.Diameter = proverka();
	while (true)
	{
		cout << "Выберите состояние трубы, где 0 - труба работает, 1 - труба находится в состоянии ремонта.\n";
		cin >> N.Repairing;
		if (!cin || (N.Repairing != 1 && N.Repairing != 0))
		{
			cout << "Введите, пожалуйста, 0 или 1\n";
			cin.clear();
			while (cin.get() != '\n');
		}
		else break;
	}
	cout << "Проверьте корректность введённых данных:\n" << "Название трубы: " << N.Name << "\n" << "Длина трубы: " << N.Length <<
		"\n" << "Диаметр трубы: " << N.Diameter << "\n" << "Состояние трубы: " << N.Repairing << "\n";
	cout << "Сохраняем? [Y/n]\n";
	string sohr;
	cin >> sohr;
	if (sohr == "Y") {
		ofstream f;
		f.open("save.txt", ios::out | ios::binary);
		if (f.is_open())
		{
			f.write((char*)&N, sizeof(Pipe));
		}
		f.close();
		cout << "Изменения сохранены в файл" << endl;
	}
	else if (sohr == "n") {
		cout << "Давайте введём данные заново\n";
		AddNewPipe();
	}
	else {
		cout << "Я вас не понимаю.\n";
	}
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
	cout << "Проверьте корректность введённых данных:\n" << "Название КС: " << K.Name << "\n" << "Количество цехов: " << K.NWorkshops <<
		"\n" << "Количество цехов в работе: " << K.WorkingWorkshops << "\n" << "Коэффициент эффективности: " << K.Efficiency << "\n";
	cout << "Сохраняем? [Y/n]\n";
	string sohr;
	cin >> sohr;
	if (sohr == "Y") {
		ofstream f;
		f.open("saveKS.txt", ios::out | ios::binary);
		if (f.is_open())
		{
			f.write((char*)&K, sizeof(KS));
		}
		f.close();
		cout << "Изменения сохранены в файл" << endl;
	}
	else if (sohr == "n") {
		cout << "Давайте введём данные заново\n";
		AddNewKS();
	}
	else {
		cout << "Я вас не понимаю.\n";
	}
}

void FullView()
{
	Pipe N;
	cout << "Список всех труб:\n";
	ifstream in("save.txt", ios::in | ios::binary);
	if (in.is_open()) {
		in.read((char*)&N, sizeof(Pipe));
		cout << N.Name << " " << N.Length << " " << N.Diameter << " " << N.Repairing << endl;
	}
	in.close();

	KS K;
	cout << "Список всех КС:\n";
	ifstream inn("saveKS.txt", ios::in | ios::binary);
	if (inn.is_open()) {
		inn.read((char*)&K, sizeof(KS));
		cout << K.Name << " " << K.NWorkshops << " " << K.WorkingWorkshops << " " << K.Efficiency << endl;
	}
	inn.close();
}

void EditPipe()
{
	Pipe N;
	cout << "Список всех труб:\n";
	ifstream in("save.txt", ios::in | ios::binary);
	if (in.is_open()) {
		in.read((char*)&N, sizeof(Pipe));
		cout << N.Name << " " << N.Length << " " << N.Diameter << " " << N.Repairing << endl;
	}
	in.close();

	int pos;
	cout << "Выберите трубу:\n";
	cin >> pos;

	while (true)
	{
		cout << "Выберите состояние трубы, где 0 - труба работает, 1 - труба находится в состоянии ремонта.\n";
		cin >> N.Repairing;
		if (!cin || (N.Repairing != 1 && N.Repairing != 0))
		{
			cout << "Введите, пожалуйста, 0 или 1\n";
			cin.clear();
			while (cin.get() != '\n');
		}
		else break;
	}
	cout << "Проверьте корректность введённых данных:\n" << "Название трубы: " << N.Name << "\n" << "Длина трубы: " << N.Length <<
		"\n" << "Диаметр трубы: " << N.Diameter << "\n" << "Состояние трубы: " << N.Repairing << "\n";
	cout << "Сохраняем? [Y/n]\n";
	string sohr;
	cin >> sohr;

	if (sohr == "Y") {

		ofstream Fout;
		Fout.open("save.txt", ios::out | ios::binary);

		if (Fout.is_open())
		{
			Fout.write((char*)&N, sizeof(Pipe));
		}
		Fout.close();
		cout << "Редактирование прошло успешно\n";
	}
	else if (sohr == "n") {
		cout << "Повторите редактирование\n";
		EditPipe();
	}
	else {
		cout << "Я вас не понимаю.\n";
	}
}

void EditKS()
{
	KS K;
	cout << "Список всех КС:\n";
	ifstream inn("saveKS.txt", ios::in | ios::binary);
	if (inn.is_open()) {
		inn.read((char*)&K, sizeof(KS));
		cout << K.Name << " " << K.NWorkshops << " " << K.WorkingWorkshops << " " << K.Efficiency << endl;
	}
	inn.close();

	int pos;
	cout << "Выберите КС:\n";
	cin >> pos;

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
	cout << "Проверьте корректность введённых данных:\n" << "Название КС: " << K.Name << "\n" << "Количество цехов: " << K.NWorkshops <<
		"\n" << "Количество цехов в работе: " << K.WorkingWorkshops << "\n" << "Коэффициент эффективности: " << K.Efficiency << "\n";
	cout << "Сохраняем? [Y/n]\n";
	string sohr;
	cin >> sohr;

	if (sohr == "Y") {

		ofstream Fout;
		Fout.open("saveKS.txt", ios::out | ios::binary);

		if (Fout.is_open())
		{
			Fout.write((char*)&K, sizeof(KS));
		}
		Fout.close();
		cout << "Редактирование прошло успешно\n";
	}
	else if (sohr == "n") {
		cout << "Повторите редактирование\n";
		EditKS();
	}
	else {
		cout << "Я вас не понимаю.\n";
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