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
	void vivodKS(const KStation& K);
	void vivodMapKS(unordered_map <int, KStation> MK);
	void sohranenieKS(unordered_map <int, KStation> MK);
	unordered_map <int, KStation> readKS();
	KStation AddNewKS();
	void EditKS(KStation& K);
	int getKSID() const;
};

