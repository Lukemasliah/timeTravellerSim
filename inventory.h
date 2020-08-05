#ifndef INVENTORY_H
#define INVENTORY_H

#include <string>
#include <vector>

class Artifact {
	
	private:
	std::string name;
	std::string description;
	int estimatedSourceTime;
	
	public:
	Artifact(std::string, std::string);
	std::string getName();
	std::string getDescription();
	int getEstimatedSourceTime();
};

class InfoBlock {
	
	private:
	double infoPercent;
	int timeFound;
	std::string name;
	
	public:
	InfoBlock(double, int, std::string);
	int getYear() const;
	double getPercent() const;
	std::string getName() const;
};

class Inventory {
	
	private:
	double percentFound;
	int clue;
	int crntArtifact;
	std::vector<Artifact> artifactList;
	std::vector<InfoBlock> infoList;		// Contains each infoBlock with numeric identity attached
	
	public:
	Inventory();
	void findInfoBlock(double, int);
	void findClue(int);
	int getClue();
	int getCurrentArtifact();
	std::string getArtifactName();
	void loadArtifact(Artifact);
	double getPercentFound();
	void nextArtifact();
	void displayInfoList();
	void displayArtifactInfo();
};



#endif //INVENTORY_H
