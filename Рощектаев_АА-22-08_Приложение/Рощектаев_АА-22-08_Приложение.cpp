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
	int RepairingWorkshops;
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
		"\n" << "Диаметр трубы: " << N.Diameter << "\n" << "Состояние трубы: " << N.Repairing;
}

int main()
{
	SetConsoleOutputCP(1251);
	SetConsoleCP(1251);
	AddNewPipe();
	return 0;
}