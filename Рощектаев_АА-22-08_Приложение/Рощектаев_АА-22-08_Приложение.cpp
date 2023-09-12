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

void AddNewPipe()
{	
	Pipe N;
	cout << "Добавление новой трубы\n" << "Введите название трубы:\n";
	cin >> N.Name;
	while (true)
	{
		cout << "Введите длину трубы:\n";
		cin >> N.Length;
		if (!cin)
		{
			cout << "Введите, пожалуйста, число\n";
			cin.clear();
			while (cin.get() != '\n');
		}
		else break;
	}
	while (true)
	{
		cout << "Введите диаметр трубы:\n";
		cin >> N.Diameter;
		if (!cin)
		{
			cout << "Введите, пожалуйста, число\n";
			cin.clear();
			while (cin.get() != '\n');
		}
		else break;
	}
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
		f.open("save.txt", ios::app);
		if (f.is_open())
		{
			f << N.Name << " " << N.Length << " " << N.Diameter << " " << N.Repairing << endl;
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
	while (true)
	{
		cout << "Введите количество цехов:\n";
		cin >> K.NWorkshops;
		if (!cin)
		{
			cout << "Введите, пожалуйста, число\n";
			cin.clear();
			while (cin.get() != '\n');
		}
		else break;
	}
	while (true)
	{
		cout << "Введите количество работающих цехов:\n";
		cin >> K.WorkingWorkshops;
		if (!cin)
		{
			cout << "Введите, пожалуйста, число\n";
			cin.clear();
			while (cin.get() != '\n');
		}
		else break;
	}
	while (true)
	{
		cout << "Введите коэффициент эффективности:\n";
		cin >> K.Efficiency;
		if (!cin)
		{
			cout << "Введите, пожалуйста, число\n";
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
		f.open("saveKS.txt", ios::app);
		if (f.is_open())
		{
			f << K.Name << " " << K.NWorkshops << " " << K.WorkingWorkshops << " " << K.Efficiency << endl;
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

int print_menu() {
	system("cls");
	int variant;
	cout << "Выберите действие" << endl;
	cout << "1. Добавить трубу" << endl;
	cout << "2. Добавить КС" << endl;
	cout << "3. Просмотр всех объектов" << endl;
	cout << "4. Редактировать трубу" << endl;
	cout << "5. Редактировать КС" << endl;
	cout << "6. Сохранить" << endl;
	cout << "7. Загрузить" << endl;
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
			//Чтение и вывод всех объектов
			break;
		case 4:
			//Редактирование трубы
			break;
		case 5:
			//Редактирование КС
			break;
		case 6:
			//Сохранение в файл;
			break;
		case 7:
			//Загрузка из файла;
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
	//AddNewPipe();
	//AddNewKS();
	menu_choice();
	return 0;
}