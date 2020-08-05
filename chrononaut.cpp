#include <iostream>
#include <string>
#include "chrononaut.h"


// Specialty Functions

Specialty::Specialty(std::string _name)
		:name(_name), abilityLevel(1), specMod(1) {};
		
std::string Specialty::getName() { return name; }
int Specialty::getAbilityLevel() { return abilityLevel; } 
void Specialty::abilityLevelUp() { abilityLevel += 1; }
void Specialty::hasDied() { name = ""; }


// ChronoTraveller Functions

ChronoTraveller::ChronoTraveller(std::string _fName, std::string _lName, int _age)
		: fName(_fName), lName(_lName), age(_age), travelAge(0) {};
		
ChronoTraveller::~ChronoTraveller(){};

void ChronoTraveller::displayChronoInfo()
{
	std::cout << "\n" << fName << " " << lName << " is a " << age << " year old ";
}


// Chrononaut Functions

Chrononaut::Chrononaut(Specialty* _specialty, std::string _fName, std::string _lName, int _age)
		: specialty(_specialty), ChronoTraveller(_fName, _lName, _age) {};

void Chrononaut::abilityLevelUp() { specialty->abilityLevelUp(); }
int Chrononaut::getAbilityLevel() { return specialty->getAbilityLevel(); }
int Chrononaut::getAge() { return age; }
int Chrononaut::getTravelAge() { return travelAge; }

void Chrononaut::displayChronoInfo()
{
	ChronoTraveller::displayChronoInfo();
	std::cout << specialty->getName() << "." << std::endl;
}

void Chrononaut::incrementAge()
{
	travelAge += 1;
}

void Chrononaut::hasDied()
{
	fName = "";
	specialty->hasDied();
}

std::string Chrononaut::getName() { return fName; }
std::string Chrononaut::getSpecialty() { return specialty->getName(); }

