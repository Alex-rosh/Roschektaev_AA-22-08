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
	void vivodKS();
	void readKS(ifstream& in);
	static KStation AddNewKS();
	void EditKS();
	int getKSID() const;
};

template<typename T>
using Filter1 = bool(*)(const KStation& s, T parameter);

//bool checkByName(const KStation& s, string parameter)
//{
//    return s.Name == parameter;
//}
//
//bool checkByNotWorkingWorkshops(const KStation& s, double parameter)
//{
//    return (double((s.NWorkshops - s.WorkingWorkshops) * 100) / s.NWorkshops) >= parameter;
//}

template<typename T>
vector<int> findStationByFilter(unordered_map<int, KStation>& mS, Filter1<T> f, T parameter)
{
    vector<int> result;

    for (auto& [sID, s] : mS)
    {
        if (f(s, parameter))
        {
            result.push_back(s.getStationID());
        }
    }

    if (result.empty())
    {
        cout << "There are no pipes wuth this parameter\n";
    }

    return result;
}