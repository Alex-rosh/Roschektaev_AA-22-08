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
	static int newKSID;
public:
	string Name;
	int NWorkshops;
	int WorkingWorkshops;
	double Efficiency;
	KStation();
	void readKS(ifstream& in);
	static KStation AddNewKS();
	void EditKS();
	int getKSID() const;
	static void sohranenieKS(ofstream& f, KStation& item);
	friend std::ostream& operator << (std::ostream& out, const KStation& x);
};