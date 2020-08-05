#ifndef POPULATION_H
#define POPULATION_H

#include <string>
#include <vector>

class TechnologicalEra {
	
	private:
	int techLevel;	// 0-4, coincides with TechAge enums
	static const std::string techEras[];	// Names of the Eras
	
	public:
	TechnologicalEra();
	std::string getName(int);
	void displayTechEraInfo(int);
};

class PopulationCentre {
	
	protected:
	std::string name;
	int crntYear;
	unsigned long population;
	int centreLevel;
	int lowerYearRange;
	int upperYearRange;
	double growthModifier;
	std::vector<std::string> functionality;
	int techLevel;
	TechnologicalEra* techEra;
	
	public:
	PopulationCentre(std::string, unsigned long, int);
	virtual ~PopulationCentre() {}
	PopulationCentre& operator++(int a);	// Shift popcentre forwards year by year
	void applyChronoPopShrink(int);		// Recieves the 'difference' in years of the jump.
	void applyYearlyGrowth();
	std::string getName() const;
	int getPopulation() const;
	int getCentreLevel() const;
	int getTechLevel() const;
	void increaseTechLvl();
	void decreaseTechLvl();
	std::string getTechName();
	void displayTechEraInfo();
	TechnologicalEra* getTechEra() const;
	std::vector<std::string> getFunctionality() const;
	bool hasFunctionality(std::string);	// used to search and find whether functionality exists
	int shiftAndConvert(int);	// Input how many years to shift
	void updateYear(int);
	int getYear();
	void setFunctionality();
	void displayFunctionality() const;
	void populationDeath(double);	// Percent of population that died
	virtual void displayCentreInfo();
};

class Metropolis : public PopulationCentre {
	
	public:
	Metropolis(std::string, unsigned long);
	~Metropolis() {}
};

class City : public PopulationCentre {
	
	public:
	City(const PopulationCentre&);	
	~City() {}
};

class Town : public PopulationCentre {
	
	public:
	Town(const PopulationCentre&);	
	~Town() {}
};

class Village : public PopulationCentre {
	
	public:
	Village(const PopulationCentre&);	
	~Village() {}
};

class Hamlet : public PopulationCentre {
	
	public:
	Hamlet(const PopulationCentre&);	
	~Hamlet() {}
};

void shiftCentreBackwards(PopulationCentre* &p, int years);


#endif	//POPULATION_H

