#include "HPipe.h"
#include "Proverka.h"
#include <iostream>
#include <string>

using namespace std;

int Pipeline::newPipeID = 0;

Pipeline::Pipeline()
{
	id = newPipeID++;
}

int Pipeline::getPipeID() const
{
	return id;
}


void Pipeline::vivodPipe()
{
	if (Name.empty())
	{
		cout << "Нет доступных труб для взаимодействия" << endl;
	}
	else
	{
		cout << "Название трубы: " << Name << "\n" << "Длина трубы: " << Length <<
			"\n" << "Диаметр трубы: " << Diameter << "\n" << "Состояние трубы: " << Repairing << "\n";
	}
}

//void Pipeline::readPipe(ifstream& in)
//{
//	in >> id;
//	getline(in, Name);
//	in >> Length;
//	in >> Diameter;
//	in >> Repairing;
//}

Pipeline Pipeline::AddNewPipe()
{
	Pipeline P;
	cout << "Добавление новой трубы\n" << "Введите название трубы:\n";
	cin >> ws;
	getline(cin, P.Name);
	cout << "Введите длину трубы:\n";
	getCorrect(P.Length);
	cout << "Введите диаметр трубы:\n";
	getCorrect(P.Diameter);
	cout << "Выберите состояние трубы, где 0 - труба работает, 1 - труба находится в состоянии ремонта.\n";
	P.Repairing = getInRange(0, 1);
	cout << "Проверьте корректность введённых данных:\n";
	P.vivodPipe();
	return P;
}

void Pipeline::EditPipe()
{
	if (Name.empty())
	{
		cout << "Нет доступных труб для взаимодействия" << endl;
	}
	else
	{
		Repairing = getInRange(0, 1);
		vivodPipe();
	}
}