#include <iostream>
#include <string>
#include <vector>
#include "populationCentre.h"

// TechnologicalEra Functions

// Declaration of techEras
const std::string TechnologicalEra::techEras[5] = {"Ancient", "Stone Age", "Bronze Age", "Industrial", "Information Age"};

TechnologicalEra::TechnologicalEra() {}	// Starts at level 4 -> metropolis

std::string TechnologicalEra::getName(int lvl) 
{ 
	return techEras[lvl]; 
}

void TechnologicalEra::displayTechEraInfo(int lvl)
{
	std::cout << "\nOur heroes gazed around blankly, it was a strange time indeed." << std::endl;
	std::cout <<  "It appears that that the WormH-Engine has dumped us straight in the " << techEras[lvl] << " time period." << std::endl;
}

// PopulationCentre Functions

int PopulationCentre::getPopulation() const { return population; }
int PopulationCentre::getCentreLevel() const { return centreLevel; }
int PopulationCentre::getTechLevel() const { return techLevel; }
std::string PopulationCentre::getName() const { return name; }
int PopulationCentre::getYear() { return crntYear; }
TechnologicalEra* PopulationCentre::getTechEra() const { return techEra; }
std::vector<std::string> PopulationCentre::getFunctionality() const { return functionality; }

PopulationCentre::PopulationCentre(std::string _name, unsigned long _population, int techLvl)
	: name(_name), population(_population), techLevel(techLvl) {}

PopulationCentre& PopulationCentre::operator++(int a)
{
	crntYear++;
	applyYearlyGrowth();
	return *this;
}

void PopulationCentre::increaseTechLvl()
{
	if(techLevel < 4)
		techLevel += 1;
}

void PopulationCentre::decreaseTechLvl()
{
	if(techLevel > 0)
		techLevel -= 1;
}

std::string PopulationCentre::getTechName()
{
	return techEra->getName(techLevel);
}
	
void PopulationCentre::displayTechEraInfo()
{
	techEra->displayTechEraInfo(techLevel);
}

void PopulationCentre::updateYear(int yearsToShift)
{
	crntYear -= yearsToShift;
}

void PopulationCentre::populationDeath(double perc)	// percentage of population that died
{
	population -= (population * perc);
}

void PopulationCentre::applyChronoPopShrink(int yearDiff)
{
	for(int i = 0; i < yearDiff; i++)
	{
		population -= (population * growthModifier);
	}
}

void PopulationCentre::applyYearlyGrowth()
{
	population += (population * (growthModifier + (getTechLevel() * 0.0004)));
}

void PopulationCentre::setFunctionality()
{
	int cLvl = getCentreLevel();
	int arraySize;

	if(cLvl == 5)
	{
		std::string funcList[] = {"Nano-Medicine", "Robo-Production", "Mercenary Agency", "Scientia Compendium", "Consciousness Simulator"};
		arraySize = sizeof(funcList) / sizeof(std::string);
		functionality.insert(functionality.end(), &funcList[0], &funcList[arraySize]);
	}
	if(cLvl == 4)
	{
		std::string funcList[] = {"Hospital", "Factory", "Military Camp", "Library"};
		arraySize = sizeof(funcList) / sizeof(std::string);
		functionality.insert(functionality.end(), &funcList[0], &funcList[arraySize]);
	}
	if(cLvl == 3)
	{
		std::string funcList[] = {"Triage", "Blacksmith", "Barracks"};
		arraySize = sizeof(funcList) / sizeof(std::string);
		functionality.insert(functionality.end(), &funcList[0], &funcList[arraySize]);
	}
	if(cLvl == 2)
	{
		std::string funcList[] = {"Herbalist", "Craftsman"};
		arraySize = sizeof(funcList) / sizeof(std::string);
		functionality.insert(functionality.end(), &funcList[0], &funcList[arraySize]);
	}
	if(cLvl == 1)
	{
		std::string funcList[] = {"Witch-Doctor"};
		arraySize = sizeof(funcList) / sizeof(std::string);
		functionality.insert(functionality.end(), &funcList[0], &funcList[arraySize]);
	}
}

bool PopulationCentre::hasFunctionality(std::string building)
{
	for (int i = 0; i < functionality.size(); i++)
	{
		if (functionality[i] == building)
			return true;
		else
			return false;
	}
}

//	Calc whether or not to convert popC object   if remainingYears > 0 = convert
int PopulationCentre::shiftAndConvert(int yearsToShift)
{
	int yearsToNextCentre = (crntYear - lowerYearRange);
	
	if(yearsToShift > yearsToNextCentre)
	{
		applyChronoPopShrink(yearsToNextCentre);
		return (yearsToShift - yearsToNextCentre);	// return the remaining years to shift
	}
	else
	{
		applyChronoPopShrink(yearsToShift);
		updateYear(yearsToShift);
		return 0;	// No need to convert PopCentre		
	}
}

void PopulationCentre::displayFunctionality() const 
{
	std::cout << "\nCentre Functionality:";
	for(std::vector<std::string>::const_iterator i = functionality.begin(); i != functionality.end(); i++)
	{
		std::cout << "   " << *i;
	}
	std::cout << std::endl;
}

void PopulationCentre::displayCentreInfo()
{
	std::cout << "'Looks like some kind of " << name << " to me.' Drake surmised." << std::endl;
	std::cout << "\nThe WormH-Engine began to buzz as it started spitting out a detailed report of \nthe local timescape," << std::endl;
	std::cout << "\nbzzzzrt! zzititit.." << std::endl;
	std::cout << "-- ScaNninG CenTRE LoCaliTy....     FOUND: " << name << "." << std::endl;
	std::cout << "-- thE YEar iS " << crntYear << "." << std::endl;
	std::cout << "-- The cuRRENT AProxiMAte PopULAtioN is " << population << " H. sAPiens-" << std::endl;
	std::cout << "-- zzrt!?\n" << std::endl;
	techEra->displayTechEraInfo(techLevel);
}

// Metropolis Functions

Metropolis::Metropolis(std::string _name, unsigned long _population)
	: PopulationCentre(_name, _population, 4) 
{
	centreLevel = 5;
	crntYear = 2525;
	lowerYearRange = 2000;
	upperYearRange = 2800;
	growthModifier = 0.0125;
	setFunctionality();		// Insert functionality for related Pop Centre Level	
}

// City Functions

City::City(const PopulationCentre& other)
	: PopulationCentre("City", other.getPopulation(), other.getTechLevel()) 
{
	centreLevel = 4;
	crntYear = 1999;
	lowerYearRange = 1500;
	upperYearRange = 1999;
	growthModifier = 0.010;
	decreaseTechLvl();
	setFunctionality();		// Insert functionality for related Pop Centre Level	
	delete& other;
}

// Town Functions

Town::Town(const PopulationCentre& other)
	: PopulationCentre("Town", other.getPopulation(), other.getTechLevel()) 
{
	centreLevel = 3;
	crntYear = 1499;
	lowerYearRange = 1000;
	upperYearRange = 1499;
	growthModifier = 0.003;
	decreaseTechLvl();
	setFunctionality();		// Insert functionality for related Pop Centre Level
	delete& other;	
}

// Village Functions

Village::Village(const PopulationCentre& other)
	: PopulationCentre("Village", other.getPopulation(), other.getTechLevel()) 
{
	centreLevel = 2;
	crntYear = 999;
	lowerYearRange = 500;
	upperYearRange = 999;
	growthModifier = 0.0018;
	decreaseTechLvl();
	setFunctionality();		// Insert functionality for related Pop Centre Level
	delete& other;
}

// Hamlet Functions

Hamlet::Hamlet(const PopulationCentre& other)
	: PopulationCentre("Hamlet", other.getPopulation(), other.getTechLevel()) 
{
	centreLevel = 1;
	crntYear = 499;
	lowerYearRange = -1000;	// Anything older will be considered a hamlet.
	upperYearRange = 499;
	growthModifier = 0.001;
	decreaseTechLvl();
	setFunctionality();	// Insert functionality for related Pop Centre Level	
	delete& other;
}

void shiftCentreBackwards(PopulationCentre* &p, int years)
{
	std::cout << "\nThe air around the Engine began to shimmer as the very fabric of reality tore open in front of "
	<< "\nthe Time-team. They stepped through the rift in space, shifting them " << years << " years into the past." << std::endl;

	while(years != 0)
	{
		int cLvl = p->getCentreLevel();
		years = p->shiftAndConvert(years);
		
		switch(cLvl)
		{
			case 5:
				if(years != 0)
					p = new City(*p);
					
				break;
			
			case 4:
				if(years != 0)
					p = new Town(*p);
				
				break;
				
			case 3:
				if(years != 0)
					p = new Village(*p);
				
				break;
				
			case 2:
				if(years != 0)
					p = new Hamlet(*p);
				
				break;
				
			case 1:
				break;
				
			default:
				std::cout << "invalid centre level" << std::endl;
				break;
		}
	}
}

