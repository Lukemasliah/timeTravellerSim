#ifndef DRIVERCLASSES_H
#define DRIVERCLASSES_H

#include <vector>
#include <string>
#include "chrononaut.h"
#include "populationCentre.h"
#include "inventory.h"

std::string static const to_string(double x);
std::string static const to_string(int x);

class ChronoTeam {
	
	private:
	std::vector<Chrononaut> crew;
	PopulationCentre* p;
	Inventory* inv;
	std::vector<std::string> majorEvents;
	
	public:
	ChronoTeam();
	~ChronoTeam();
	void chronoJump(int);
	void searchYear();
	void incrementAge();
	void levelUp(std::string name);
	void selectTeam();
	void missionReport();
	void displayTeam();
	void recordMajorEvent(std::string);
	void findInformation(double);
	void findClue(int);
	void resetPopCentre();
	std::string hasDied();
	void goatyDied();
	Inventory* getInventory();
	std::string findSpecialist(std::string);
	Chrononaut getChrononaut(std::string);	
	std::string getSpeaker();
	PopulationCentre* getPopCentre();
};

class EventFactory {
	
	private:
	bool foundClue;
	bool foundInfo;
	
	public:
	EventFactory();
	int generateEvent(ChronoTeam &, int);	// returns various integers based on event outcomes
	int generateClue();
	bool searchComplete();
	double generateInfoBlock();
};


#endif 	// DRIVERCLASSES_H

