#include <iostream>
#include <windows.h>
#include <fstream>

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
	cout << "Введите длину трубы:\n";
	cin >> N.Length;
	cout << "Введите диаметр трубы:\n";
	cin >> N.Diameter;
	cout << "Выберите состояние трубы, где 0 - труба работает, 1 - труба находится в состоянии ремонта.\n";
	cin >> N.Repairing;
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
	cout << "Введите количество цехов:\n";
	cin >> K.NWorkshops;
	cout << "Введите количество работающих цехов:\n";
	cin >> K.WorkingWorkshops;
	cout << "Введите коэффициент эффективности:\n";
	cin >> K.Efficiency;
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

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	AddNewPipe();
	AddNewKS();
	return 0;
}