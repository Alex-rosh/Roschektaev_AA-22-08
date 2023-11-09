#pragma once
#include <unordered_map>
#include <fstream>
#include <string>
#include <iostream>
#include "Proverka.h"

using namespace std;

class Pipeline
{
	int id;
	static int newPipeID;
public:
	std::string Name;
	int Length;
	int Diameter;
	bool Repairing;
	Pipeline();
	
	int getPipeID() const;
	void vivodPipe();
	void readPipe(ifstream& in);
	static Pipeline AddNewPipe();
	void EditPipe();
	/*bool checkByID(const Pipeline& p, int parameter);
	bool checkByRepair(const Pipeline& p, int parameter);*/
};

template<typename T>
using Filter2 = bool(*)(const Pipeline& p, T parameter);

//bool checkByID(const Pipeline& p, int parameter)
//{
//    return p.getPipeID() >= parameter;
//}
//
//bool checkByRepair(const Pipeline& p, int parameter)
//{
//    return p.Repairing == parameter;
//}

template<typename T>
vector<int> findPipeByFilter(unordered_map<int, Pipeline>& mP, Filter2<T> f, T parameter)
{
    vector<int> result;

    for (auto& [pID, p] : mP)
    {
        if (f(p, parameter))
        {
            result.push_back(p.getPipeID());
        }
    }

    if (result.empty())
    {
        cout << "There are no pipes wuth this parameter\n";
    }

    return result;
}