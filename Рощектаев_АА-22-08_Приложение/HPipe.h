#pragma once
#include <unordered_map>
#include <fstream>
#include <string>
#include <iostream>
#include "Proverka.h"

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
	//void readPipe(ifstream& in);
	static Pipeline AddNewPipe();
	void EditPipe();
};