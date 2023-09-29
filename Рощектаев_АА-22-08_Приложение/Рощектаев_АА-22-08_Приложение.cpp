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

void vivodPipe(const Pipe& N)
{
	cout << "Название трубы: " << N.Name << "\n" << "Длина трубы: " << N.Length <<
		"\n" << "Диаметр трубы: " << N.Diameter << "\n" << "Состояние трубы: " << N.Repairing << "\n";
}

void vivodKS(const KS& K)
{
	cout << "Название КС: " << K.Name << "\n" << "Количество цехов: " << K.NWorkshops <<
		"\n" << "Количество цехов в работе: " << K.WorkingWorkshops << "\n" << "Коэффициент эффективности: " << K.Efficiency << "\n";
}

void sohranenie(const Pipe& N, const KS& K)
{
	string S;
	S = N.Name + " " + to_string(N.Length) + " " + to_string(N.Diameter) + " " + to_string(N.Repairing) + "\n";
	string SS;
	SS = K.Name + " " + to_string(K.NWorkshops) + " " + to_string(K.WorkingWorkshops) + " " + to_string(K.Efficiency) + "\n";
	ofstream f;
	f.open("save.txt", ios::out);
	if (f.is_open())
	{
		f << "Pipes" << "\n";
		f << N.Name << "\n";
		f << N.Length << "\n";
		f << N.Diameter << "\n";
		f << N.Repairing << "\n";
		f << "KS" << "\n";
		f << K.Name << "\n";
		f << K.NWorkshops << "\n";
		f << K.WorkingWorkshops << "\n";
		f << K.Efficiency << "\n";
	}
	f.close();
	cout << "Изменения сохранены в файл" << endl;
}

Pipe readPipe()
{
	Pipe N;
	string flag;
	ifstream in("save.txt");
	if (in.is_open()) {
		getline(in, flag);
		while (!flag.empty())
		{
			if (flag == "Pipes")
			{
				getline(in, N.Name);
				in >> N.Length;
				in >> N.Diameter;
				in >> N.Repairing;
			}
			getline(in, flag);
		}
	}
	in.close();
	return N;
}

KS readKS()
{
	KS K;
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
	return K;
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
			while (cin.get() != '\n');//!!!!
		}
		else break;
	}
	return sost;
}

Pipe AddNewPipe()
{	
	Pipe N;
	cout << "Добавление новой трубы\n" << "Введите название трубы:\n";
	cin >> ws;
	getline(cin, N.Name);
	cout << "Введите длину трубы:\n";
	N.Length = proverka();
	cout << "Введите диаметр трубы:\n";
	N.Diameter = proverka();
	N.Repairing = sost();
	cout << "Проверьте корректность введённых данных:\n";
	vivodPipe(N);
	return N;
}

KS AddNewKS()
{
	KS K;
	cout << "Добавление новой КС\n" << "Введите название КС:\n";
	cin >> K.Name;
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

void FullView(const Pipe& N, const KS& K)
{
	int variant;
	cout << "Выберите действие" << endl;
	cout << "1. Вывести список труб" << endl;
	cout << "2. Вывести список КС" << endl;
	variant = proverka();
	switch (variant) {
	case 1:
		vivodPipe(N);
		break;
	case 2:
		vivodKS(K);
		break;
	}
}

Pipe EditPipe(Pipe& N)
{
	N.Repairing = sost();
	vivodPipe(N);
	return N;
}

KS EditKS(KS& K)
{
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
	return K;
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
	Pipe N;
	KS K;
	int variant;
	variant = 1;
	do {
		int variant = print_menu();

		switch (variant) {
		case 1:
			N = AddNewPipe();
			break;
		case 2:
			K = AddNewKS();
			break;
		case 3:
			FullView(N, K);
			break;
		case 4:
			N = EditPipe(N);
			break;
		case 5:
			K = EditKS(K);
			break;
		case 6:
			N = readPipe();
			K = readKS();
			break;
		case 7:
			sohranenie(N, K);
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