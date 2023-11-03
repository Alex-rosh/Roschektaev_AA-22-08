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
	void vivodMapPipe(unordered_map <int, Pipeline> MP);
	void static sohraneniePipe(ofstream& f, unordered_map <int, Pipeline> MP, const int &id, Pipeline& item);
	void static readPipe(ifstream& in, Pipeline& P);
	Pipeline AddNewPipe(Pipeline& P);
	void EditPipe(Pipeline& P);
	void setPipeID(int);
};



