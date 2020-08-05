#ifndef CHRONONAUT_H
#define CHRONONAUT_H

#include <string>

class Specialty {
	
	private:
	std::string name;
	int abilityLevel;
	double specMod;
	
	public:
	Specialty(std::string _name);
	std::string getName();
	int getAbilityLevel();
	void abilityLevelUp();
	void hasDied();
};

class ChronoTraveller {
	
	protected:
	std::string fName;
	std::string lName;
	int age;
	int travelAge;
	
	public:
	ChronoTraveller(std::string, std::string, int);	
	virtual ~ChronoTraveller();
	virtual void displayChronoInfo();
};


class Chrononaut : public ChronoTraveller {
	
	private:
	Specialty* specialty;
	
	public:
	Chrononaut(Specialty*, std::string, std::string, int);	
	void abilityLevelUp();
	void displayChronoInfo();
	void hasDied();
	void incrementAge();
	int getAbilityLevel();
	int getAge();
	int getTravelAge();
	std::string getName();
	std::string getSpecialty();
};

#endif 	// CHRONONAUT_H

