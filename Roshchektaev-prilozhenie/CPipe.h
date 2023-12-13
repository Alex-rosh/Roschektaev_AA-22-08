#pragma once
#include <cstdint>
#include <iostream>
#include <set>

class CPipe
{
	uint32_t pipeID;
public:	

	static uint32_t newPipeID;

	double length, diameter;
	uint32_t repair, inStationID, outStationID;

	friend std::ostream& operator << (std::ostream& out, const CPipe& x);
	friend std::istream& operator >> (std::istream& in, CPipe& x);
	friend std::ofstream& operator << (std::ofstream& out, const CPipe& );
	friend std::ifstream& operator >> (std::ifstream& in, CPipe& x);

	CPipe();

	uint32_t getPipeID() const;

	void link(uint32_t, uint32_t);\

	void clearLink();

	bool linked() const;

	bool canBeUsed() const;

	void showLink() const;

	uint32_t getProductivity() const;
};