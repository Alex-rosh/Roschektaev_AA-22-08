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
	void readPipe(ifstream& in);
	static Pipeline AddNewPipe();
	void EditPipe();
	static void sohraneniePipe(ofstream& f, Pipeline& item);

	friend std::ostream& operator << (std::ostream& out, const Pipeline& x);
};