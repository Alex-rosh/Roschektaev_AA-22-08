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

void Pipeline::setPipeID(int Pipeid)
{
	id = Pipeid;
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

void Pipeline::vivodMapPipe(unordered_map <int, Pipeline> MP)
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

void Pipeline::sohraneniePipe(ofstream& f, unordered_map <int, Pipeline> MP, const int &id, Pipeline &item)
{
	f << id << "\n"
		<< item.Name << "\n"
		<< item.Length << "\n"
		<< item.Diameter << "\n"
		<< item.Repairing << "\n";
}

void Pipeline::readPipe(ifstream& in, Pipeline& P)
{
	in >> P.id;
	P.setPipeID(P.id);
	getline(in, P.Name);
	in >> P.Length;
	in >> P.Diameter;
	in >> P.Repairing;
}

Pipeline Pipeline::AddNewPipe(Pipeline& P)
{
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

void Pipeline::EditPipe(Pipeline& P)
{
	if (P.Name.empty())
	{
		cout << "Нет доступных труб для взаимодействия" << endl;
	}
	else
	{
		P.Repairing = getInRange(0, 1);
		vivodPipe();
	}
}