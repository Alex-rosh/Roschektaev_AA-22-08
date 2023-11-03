#pragma once
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <string>
#include "Proverka.h"

using namespace std;

class KStation
{
	int id;
	static int newPipeID;
public:
	string Name;
	int NWorkshops;
	int WorkingWorkshops;
	double Efficiency;
	KStation();
	void vivodKS();
	//void static readKS(ifstream& in, unordered_map <int, KStation>& MK);
	static KStation AddNewKS();
	void EditKS();
	int getKSID() const;
};

