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
	void sohraneniePipe(unordered_map <int, Pipeline> MP);
	void readPipe(ifstream in, unordered_map <int, Pipeline> MP);
	Pipeline AddNewPipe();
	void EditPipe(Pipeline& P);
};



