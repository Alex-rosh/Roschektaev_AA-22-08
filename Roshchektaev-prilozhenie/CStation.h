#pragma once
#include <cstdint>
#include <string>

class CStation
{
	uint32_t stationID;
public:

	static uint32_t newStationID;

	std::string name;
	uint32_t numOfWorkshops, numOfWorkingWorkshops, efficiency;
	bool connection;

	friend std::ostream& operator << (std::ostream& out, const CStation& x);
	friend std::istream& operator >> (std::istream& in, CStation& x);
    friend std::ofstream& operator << (std::ofstream& out, CStation& x);
	friend std::ifstream& operator >> (std::ifstream& in, CStation& x);

	CStation();

	uint32_t getStationID();

	void createLink();

	void clearLink();

	bool linked();
};

