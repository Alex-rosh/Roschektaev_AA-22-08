#include "CStation.h"
#include <iostream>
#include <fstream>
#include "Utils.h"

uint32_t CStation::newStationID = 0;

std::istream& operator >> (std::istream& in, CStation& x)
{
    std::cout << "Add the parameters of the compressor station:\nname, number of workshops, number of working workshops, efficiency \n";
    std::cout << "Name:\n";
    in >> std::ws;
    getline(in, x.name);
    std::cout << "Number of workshops:\n";
    getCorrect(x.numOfWorkshops);
    std::cout << "Number of working workshops:\n";
    x.numOfWorkingWorkshops = (getInRange(0, x.numOfWorkshops));
    x.efficiency = (x.numOfWorkingWorkshops * 100) / (x.numOfWorkshops);
    return in;
}
 
std::ofstream& operator << (std::ofstream& out, CStation& x)
{
    out << x.stationID << std::endl << x.name << std::endl << x.numOfWorkshops << std::endl
        << x.numOfWorkingWorkshops << std::endl << x.efficiency << std::endl << x.connection;
    return out;
}

std::ifstream& operator>>(std::ifstream& in, CStation& x)
{
    in >> x.stationID;
    in >> std::ws;
    getline(in, x.name);
    in >> x.numOfWorkshops;
    in >> x.numOfWorkingWorkshops;
    in >> x.efficiency;
    in >> x.connection;
    return in;
}

std::ostream& operator << (std::ostream& out, const CStation& x)
{
    out << "Station:\n";
    out << "ID: " << x.stationID << " Name: " << x.name << " Number of workshops: " << x.numOfWorkshops << std::endl
        << "Number of working workshops: " << x.numOfWorkingWorkshops << " Efficiency: " << x.efficiency << std::endl
        << "Connection: " << x.connection << std::endl;
    return out;
}

CStation::CStation()
{
    stationID = ++newStationID;
    name = "Unknown";
    numOfWorkshops = 10;
    numOfWorkingWorkshops = 10;
    efficiency = 100;
    connection = false;
}

uint32_t CStation::getStationID()
{
    return stationID;
}

void CStation::createLink()
{
    if (!connection)
        connection = true;
}

void CStation::clearLink()
{
    connection = false;
}

bool CStation::linked()
{
    return connection;
}
