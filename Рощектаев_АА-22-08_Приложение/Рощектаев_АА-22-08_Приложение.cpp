#include <iostream>
#include <windows.h>

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
	string Name;
	int Length;
	int Diameter;
	bool Repairing;
	cout << "Добавление новой трубы\n" << "Введите название трубы:\n";
	cin >> Name;
	cout << "Введите длину трубы:\n";
	cin >> Length;
	cout << "Введите диаметр трубы:\n";
	cin >> Diameter;
	cout << "Выберите состояние трубы, где 0 - труба работает, 1 - труба находится в состоянии ремонта.\n";
	cin >> Repairing;
	Pipe N = { Name, Length, Diameter, Repairing };
	cout << "Проверьте корректность введённых данных:\n" << "Название трубы: " << N.Name << "\n" << "Длина трубы: " << N.Length <<
		"\n" << "Диаметр трубы: " << N.Diameter << "\n" << "Состояние трубы: " << N.Repairing << "\n";
	cout << "Сохраняем? [Y/n]\n";
	string sohr;
	cin >> sohr;
}

void AddNewKS()
{
	string Name;
	int NWorkshops;
	int WorkingWorkshops;
	double Efficiency;
	cout << "Добавление новой КС\n" << "Введите название КС:\n";
	cin >> Name;
	cout << "Введите количество цехов:\n";
	cin >> NWorkshops;
	cout << "Введите количество работающих цехов:\n";
	cin >> WorkingWorkshops;
	cout << "Введите коэффициент эффективности:\n";
	cin >> Efficiency;
	KS K = { Name, NWorkshops, WorkingWorkshops, Efficiency };
	cout << "Проверьте корректность введённых данных:\n" << "Название КС: " << K.Name << "\n" << "Количество цехов: " << K.NWorkshops <<
		"\n" << "Количество цехов в работе: " << K.WorkingWorkshops << "\n" << "Коэффициент эффективности: " << K.Efficiency << "\n";
	cout << "Сохраняем? [Y/n]\n";
	string sohr;
	cin >> sohr;
}

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	AddNewPipe();
	AddNewKS();
	return 0;
}