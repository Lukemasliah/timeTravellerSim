#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include "inventory.h"


// Infoblock Functions

InfoBlock::InfoBlock(double _perc, int year, std::string artName)
{
	infoPercent = _perc;
	timeFound = year;
	name = artName;
}

double InfoBlock::getPercent() const { return infoPercent; }
int InfoBlock::getYear() const { return timeFound; }
std::string InfoBlock::getName() const { return name; }

// Artifact Functions

Artifact::Artifact(std::string _name, std::string _desc)
{
	name = _name;
	description = _desc;
	estimatedSourceTime = (rand() % 1000 + 1);	// First jump distance is between 1-1000 years
}

std::string Artifact::getName() { return name; }
std::string Artifact::getDescription() { return description; } 
int Artifact::getEstimatedSourceTime() { return estimatedSourceTime; }

// Inventory Functions

Inventory::Inventory()
{
	percentFound = 0;
	clue = 0;
	crntArtifact = -1;
}

void Inventory::loadArtifact(Artifact artifact)
{
	artifactList.push_back(artifact);
}

void Inventory::displayArtifactInfo()
{
	std::cout << "Artefact: " << artifactList[crntArtifact].getName() << ", known for its mysterious power." << std::endl;
	std::cout << "Description:  " << artifactList[crntArtifact].getDescription() << std::endl;
	std::cout << "Information last recorded: " << (2525 - artifactList[crntArtifact].getEstimatedSourceTime()) << "." << std::endl;
}

void Inventory::findInfoBlock(double newInfo, int year)
{
	percentFound += newInfo;
	if(percentFound > 1)	// Max info is 1 = 100%
		percentFound = 1;
	
	InfoBlock info(newInfo, year, artifactList[crntArtifact].getName());
	infoList.push_back(info);
	//infoList.push_back(to_string(crntArtifact) + "   " + to_string(newInfo) + "%    " + to_string(year) + "    " + );
}

void Inventory::findClue(int _clue)
{
	clue = _clue;
}

int Inventory::getClue()
{
	return clue;
}

int Inventory::getCurrentArtifact() { return crntArtifact; }
double Inventory::getPercentFound() { return percentFound; }

void Inventory::displayInfoList()
{	
	printf("\n%s", "Artefact Information Source Report");
	printf("\n%s\n", "---------------------------------------------------------------------");
	printf("%-16s%-8s%-6s%\n", "Artefact", "Found", "Year");
	printf("%s\n", "---------------------------------------------------------------------");
	for(int i = 0; i < infoList.size(); i++)
	{
		double perc = (infoList[i].getPercent() * 100);
		printf("%-16s%-2.0f%-6s%-6d\n", infoList[i].getName().c_str(), perc, "%", infoList[i].getYear());
	} 
}

void Inventory::nextArtifact()
{
	crntArtifact++;
	clue = artifactList[crntArtifact].getEstimatedSourceTime();
	percentFound = 0;
}

std::string Inventory::getArtifactName()
{
	return artifactList[crntArtifact].getName();
}



