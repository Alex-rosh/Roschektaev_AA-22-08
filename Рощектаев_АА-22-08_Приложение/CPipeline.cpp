#include "HPipe.h"
#include "Proverka.h"
#include <iostream>
#include <string>

using namespace std;

int Pipeline::newPipeID = 0;

Pipeline::Pipeline()
{
	id = ++newPipeID;
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

void Pipeline::vivodMapPipe(unordered_map <int, Pipeline> MP)
{
	for (const auto& pair : MP)
	{
		cout << "ID: " << pair.first << "\n"
			<< "Название трубы: " << pair.second.Name << "\n"
			<< "Длина трубы: " << pair.second.Length << "\n"
			<< "Диаметр трубы: " << pair.second.Diameter << "\n"
			<< "Состояние трубы: " << pair.second.Repairing << "\n";
	}
}

void Pipeline::sohraneniePipe(unordered_map <int, Pipeline> MP)
{
	ofstream f;
	f.open("save.txt", ios::out);
	if (f.is_open())
	{
		f << MP.size() << endl;
		if (!MP.size() == 0)
		{
			for (auto& [id, item] : MP)
			{
				f << id << "\n"
					<< item.Name << "\n"
					<< item.Length << "\n"
					<< item.Diameter << "\n"
					<< item.Repairing << "\n";
			}
		}
		else if (MP.size() == 0)
		{
			f << 0 << endl;
		}
	}
	f.close();
	cout << "Изменения сохранены в файл" << endl;
}

void Pipeline::readPipe(ifstream in, unordered_map <int, Pipeline> MP)
{
	Pipeline P;
	getline(in, P.Name);
	in >> P.Length;
	in >> P.Diameter;
	in >> P.Repairing;
	MP.insert({ P.getPipeID(), P });
}

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