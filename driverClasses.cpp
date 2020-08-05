#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "driverClasses.h"
#include "chrononaut.h"

std::string static const to_string(double x)
{
	std::ostringstream oss;
	oss << x;
	return oss.str();
}

std::string static const to_string(int x)
{
	std::ostringstream oss;
	oss << x;
	return oss.str();
}

// ChronoTeam functions

void ChronoTeam::chronoJump(int clue)
{
	shiftCentreBackwards(p, clue);
}

void ChronoTeam::resetPopCentre()
{
	p = new Metropolis("Metropolis", 2360000000UL);
}

void ChronoTeam::displayTeam()
{
	std::cout << "\nThe selected team of Chrononauts:" << std::endl;
	for(int i = 0; i < crew.size(); i++)
	{
		crew[i].displayChronoInfo();
	}
}

ChronoTeam::ChronoTeam()
{
	selectTeam();
	p = new Metropolis("Metropolis", 2360000000UL);
	inv = new Inventory();
}

ChronoTeam::~ChronoTeam()
{
	delete p;
}

void ChronoTeam::searchYear() 
{	
	(*p)++; 
	incrementAge();
}

void ChronoTeam::incrementAge()
{
	for(int i = 0; i < crew.size(); i++)
	{
		if(crew[i].getName() != "")
			crew[i].incrementAge();
	}
}

void ChronoTeam::levelUp(std::string name)
{
	for(int i = 0; i < crew.size(); i++)
	{
		if(crew[i].getName() == name)
			crew[i].abilityLevelUp();
	}
}

void ChronoTeam::missionReport()
{
	std::string status;
	std::string name;
	std::string spec;
	
	// Crew reporting
	printf("%-12s%-16s%-12s%-8s%-14s%-12s\n", "Name", "Position", "Ability", "Age", "Travel Age", "Status");
	printf("%s\n","---------------------------------------------------------------------");
	for(int i = 0; i < crew.size(); i++)
	{
		name = crew[i].getName();	// Redaction of information
		if(name == "")
			name = "**********";
		
		spec = crew[i].getSpecialty();
		if(spec == "")
			spec = "**********";
		
		status = "Alive";
		if(crew[i].getName() == "")
			status = "N/A";
		
		printf("%-12s%-16s%-12d%-8d%-14d%-12s\n", name.c_str(), spec.c_str(), crew[i].getAbilityLevel(), crew[i].getAge(), crew[i].getTravelAge(), status.c_str());
	}

	std::cout << "\nNote: Due to the confidential nature of the this mission,"
	<< "\n      redaction has occurred to protect the identity of those lost in time." << std::endl;
	
	// Information reporting
	inv->displayInfoList();
	
	// Major Event Report
	printf("\n%s\n", "---------------------------------------------------------------------");
	std::cout << "Major Event Report" << std::endl;
	printf("%s\n", "---------------------------------------------------------------------");
	for(int i = 0; i < majorEvents.size(); i++)
	{
		std::cout << majorEvents[i] << std::endl;
	}
}

std::string ChronoTeam::findSpecialist(std::string specialist)
{
	for (int i = 0; i < crew.size(); i++)
	{
		if (crew[i].getSpecialty() == specialist)
		{
			return crew[i].getName();
		}
	}
	// No specialist found/alive
	return "";
}

Chrononaut ChronoTeam::getChrononaut(std::string specialist)	// Find chrononaut based on specialty
{
	for (int i = 0; i < crew.size(); i++)
	{
		if (crew[i].getSpecialty() == specialist)
		{
			return crew[i];
		}
	}
}

std::string ChronoTeam::getSpeaker()
{
	int choice = rand() % 4;
	while(crew[choice].getName() == "")
	{
		choice = rand() % 4 + 1;
	}
	return crew[choice].getName();
}

void ChronoTeam::recordMajorEvent(std::string majEvnt)
{
	majorEvents.push_back(majEvnt);
}

void ChronoTeam::findInformation(double infoPerc)
{
	inv->findInfoBlock(infoPerc, p->getYear());
}

void ChronoTeam::findClue(int _clue)
{
	inv->findClue(_clue);
}

void ChronoTeam::selectTeam()
{
	Specialty* s1 = new Specialty("Jump engineer");
	Specialty* s2 = new Specialty("Doctor");
	Specialty* s3 = new Specialty("Historian");
	Specialty* s4 = new Specialty("Security");
	
	
	crew.push_back(Chrononaut(s1, "Drake", "Carter", 32));
	crew.push_back(Chrononaut(s2, "Astra", "Lancell", 27));
	crew.push_back(Chrononaut(s3, "Boris", "Eldritch", 47));
	crew.push_back(Chrononaut(s4, "Felix", "Starburn", 29));

	// Random Pet Choice
	int petChoice = rand() % 3 + 1;
	if (petChoice == 1)
	{
		Specialty* s5 = new Specialty("Spacegoat");
		crew.push_back(Chrononaut(s5, "Goaty", "the Spacegoat", 66));
	}
	else if (petChoice == 2)
	{
		Specialty* s5 = new Specialty("Timewarper");
		crew.push_back(Chrononaut(s5, "Yoghurt", "the Time-Turtle", 867));
	}
	else
	{
		Specialty* s5 = new Specialty("Dark Arts");
		crew.push_back(Chrononaut(s5, "Peep", "the Ghost", 66));
	}
}

std::string ChronoTeam::hasDied()	// Doesn't include goaty
{
	int dead = rand() % 4;	// 0 - 3
	while(crew[dead].getName() == "")
	{
		dead = rand() % 4;
	}
	std::string memberName = crew[dead].getName();
	crew[dead].hasDied();
	return memberName;
}

void ChronoTeam::goatyDied()
{
	crew[4].hasDied();
}

PopulationCentre* ChronoTeam::getPopCentre() { return p; }
Inventory* ChronoTeam::getInventory() { return inv; }


	// Eventfactory & functions

EventFactory::EventFactory()
{
	foundClue = false;
	foundInfo = false;
}

bool EventFactory::searchComplete()
{
	if(foundClue == true && foundInfo == true)	// Found info and clue for jump location
	{
		foundClue = false;	// Reset for next jump site
		foundInfo = false;

		return true;
	}
	return false;	// Still searching
}

double EventFactory::generateInfoBlock()
{
	double found = (rand() % 30 + 11);
	return found / 100;	// 10-40% information find 
}

int EventFactory::generateClue()
{
	return rand() % 500 + 1;	// Random jump distance between 0 - 500
}

int EventFactory::generateEvent(ChronoTeam &chronoTeam, int searchNumber)
{
	int evnt = rand() % 20 + 1;
	std::string year = to_string(chronoTeam.getPopCentre()->getYear());

	// Increasing chance of finding clue & artifact
	if(!searchComplete())
	{
		int bonusFindChance = 1 * searchNumber;   // 2-20
		int findRand = rand() % 20 + 1;
		if(findRand < bonusFindChance )
		{
			if(!foundInfo)
				evnt = 1;
			
			if(!foundClue)
				evnt = 2;
		}
		// Find info and clue by the end of the 10 year search
		if(searchNumber == 9 && !foundInfo)
			evnt = 1;
		
		if(searchNumber == 10 && !foundClue)
			evnt = 2;
	}

	switch(evnt)
	{
		case 1:	// Find information
			if (foundInfo == true)
			{
				std::cout << "\nJust another quiet year of searching." << std::endl;
				break;
			}

			std::cout << "\n'Look!', " << chronoTeam.getSpeaker() << " called out as the temporal scanner in thier hands started flashing and beeping."
				<< "\nA holographic image hazed into existance in front of the scanner and immediately the time-team started scribbling down"
				<< "\nnotes on the mirage-like video playing out in front of them."
				<< "\n'Nice work guys', Drake remarked. 'This is exactly the information we were looking for, lets "
				<< "\nget it recorded and get back to the jump site'." 
				<< "\n\nFOUND: Information" << std::endl;

			
			if (chronoTeam.findSpecialist("Historian") != "")	// Historian increases info amount
			{
				double bonusInfo = (chronoTeam.getChrononaut("Historian").getAbilityLevel()) * .03;
				chronoTeam.findInformation((generateInfoBlock() + bonusInfo));
			}
			else
			{
				chronoTeam.findInformation(generateInfoBlock());
			}

			std::cout << "COLLECTED: " << (chronoTeam.getInventory()->getPercentFound() * 100) << "%" << std::endl;
			foundInfo = true;
			break;
			
		case 2:	// Find clue
			if (foundClue == true)
			{
				std::cout << "\nJust another quiet year of searching." << std::endl;
				break;
			}
		
			std::cout << "\n'A jump clue!', " << chronoTeam.getSpeaker() << " said, scrying through the dusty parchments."
				<< "\n'This should point us in the direction of the next block of information." << std::endl;
			if (chronoTeam.findSpecialist("Spacegoat") != "")
				std::cout << "'Bahh', grunted Goaty, quietly chewing on the previous clue." << std::endl;
			chronoTeam.findClue(generateClue());
			std::cout << "\nFOUND: Jump Clue" << std::endl;
			foundClue = true;
			break;
			
		case 3: // Discover artifact is fake
			evnt = rand() % 10 + 1;
			if (evnt == 1)
			{
				std::cout << "\nThe crew shuddered as " << chronoTeam.getSpeaker() << " stepped back from the various stacks of paper and objects"
					<< "\nlittering the workbench. 'I can't believe it... '"
					<< "\nThe Trials, dangers and loss that the crew had encountered on their mission had been for nothing,"
					<< "\nThe Artifact was a fake."
					<< "\n\nA sullen mood encompassed the crew as preperations were made to depart back to 2525." << std::endl;
				
				chronoTeam.recordMajorEvent(year + " - " + "Discovered artefact was a fake.");
				return 1;	// *************** Artifact is a fake, finish run through.
			}
			else
			{
				std::cout << "\nJust another quiet year of searching." << std::endl;
			}
			break;
			
		case 4:	// Illness - plague
			std::cout << "\nAs the crew exited their lodgings they were met with a startling site."
				<< "\nthe local populace had sickened terribly, their skin hung limp and vile black rashes had broken out all over"
				<< "\ntheir bodies. A putrid smell clung to the air."
				<< "\n'Looks like a plague of some kind' " << chronoTeam.getSpeaker() << " exclaimed, 'We best fall back and quarantine ourselves'." << std::endl;
			
			evnt = rand() % 5 + 1;
			if (evnt == 1)	// Chance of chrononaut getting sick
			{
				std::string died = chronoTeam.hasDied();
				std::cout << "Before sunrise the following morning a faint groaning could be heard from the back room of the Sanctech shelter."
					<< "\nIt wasnt until several hours later when the crew awoke and began the morning routine that they"
					<< "\nfound the body."
					<< "\n\n" << died << " was dead."
					<< "\nThe body was covered in those all-too-familiar blackened scars, the bed was soaked with sweat"
					<< "\nand scent of death burdened the room." << std::endl;
				if(chronoTeam.findSpecialist("Jump engineer") != "")	
				{
					std::cout << "\n'Burn the body' Drake grimaced."
						<< "\n'Lets find this information and get out of this god-forsaken place'." << std::endl;
					chronoTeam.recordMajorEvent(year + " - " + died + " was killed by a plague.");
				}
				else	// Jump Engineer has died
				{
					if (chronoTeam.findSpecialist("Timewarper") != "" && chronoTeam.getChrononaut("Timewarper").getAbilityLevel() > 3)
					{
						std::cout << "\nYoghurt the time turtle had a realization as he stared at the rotting husk of the crews captain"
							<< "\nHe realized that if the captain is unable to take the crew home, then he would never get to visit"
							<< "\nhis beloved turtle family again."
							<< "\nThis was unacceptable."
							<< "\nSo he focused, and he focused hard. Time around Yoghurt appeared to slow, The air became thick like molassas"
							<< "\nHe focused harder, until sound ceased to exist and the world stopped."
							<< "\nHARDER he thought, throwing his bulky mental capabilities against the wall of time, cracking the metaphysical"
							<< "\nconstraints."
							<< "\nLike a thunderclap, the world came rushing back into perspective, except it was in fact the day before."
							<< "\nYoghurt smiled as he bumped into Drakes foot as he paced around the control room."
							<< "\nThis simple disturbance would alter the time space continuum fractionally, ensuring that Drake no longer"
							<< "\nAte his dinner outside, preventing his death."
							<< "\nYoghurt was hero."
							<< "\nHe also died peacefully, later that day." << std::endl;
						chronoTeam.getChrononaut("Timewarper").hasDied();
						chronoTeam.recordMajorEvent(year + " - " + "The valiant turtle Yoghurt sacrificed himself to save Drake.");
						// Yoghurt death, record as major event
					}
					else
					{
						std::cout << "'Thats it then' " << chronoTeam.getSpeaker() << " announced, 'Drake is dead and he was the only one"
							<< "\nwho knew how to operate the WormH-Engine. Lets work on finding a cure for this plague before it gets us too'"
							<< "\n\nAnd so the crew of chrononauts spent the rest of their lives trapped in the past, a mission in vain." << std::endl;
						chronoTeam.recordMajorEvent(year + " - " + "Drake was killed by a plague.");
						return 2; // *************** Jump Engineer has died, game over.
					}
				}
			}
			
			if(chronoTeam.findSpecialist("Dark Arts") != "")	// Ghost makes plagues worse
			{
				double plagueDmg = ((chronoTeam.getChrononaut("Dark Arts").getAbilityLevel() * 0.02) + 0.03);
				chronoTeam.getPopCentre()->populationDeath(plagueDmg);
				plagueDmg = plagueDmg * 100;
				chronoTeam.recordMajorEvent(year + " - " + "Plague killed " + to_string(plagueDmg) + "% of the population.");
				chronoTeam.getChrononaut("Dark Arts").abilityLevelUp();
			}
			else
			{
				chronoTeam.getPopCentre()->populationDeath(0.03);
				chronoTeam.recordMajorEvent(year + " - " + "Plague killed 3% of the population.");
			}

			break;
			
		case 5:	// Skirmish - War
			std::cout << "\n" << chronoTeam.getSpeaker() << " took a long hard look at the civTech schematics open on the hovScreen"
				<< "\n'Looks like aggression levels in the local populace is much higher than normal, with a strong indication of"
				<< "\nprimal conflict occurring'."
				<< "\n'We knew this might happen, the " << chronoTeam.getPopCentre()->getTechName() << " era is rich "
				<< "\nwith battle history. Best we get prepared'"
				<< "\n\nWhat followed was a brutal and bloody massacre, many of the local populace died" << std::endl;
				
			if(chronoTeam.findSpecialist("Security") != "")
			{
				std::cout << "'Thank god " << chronoTeam.findSpecialist("Security") << " was here, I could of sworn we weren't going to"
					<< "\nmake it back to the shelter' " << chronoTeam.getSpeaker() << " voiced through husky breaths."
					<< "\n'Everyone keep on your toes and we will get through this' " << chronoTeam.findSpecialist("Security") << " encouraged." << std::endl;
			}
			else
			{
				std::string died = chronoTeam.hasDied();
				std::cout << "\n" << died << " was covered in blood."
				<< "'Somebody get me some towels!!' " << chronoTeam.getSpeaker() << " yelled. 'I can't stop the bleeding'"
				<< "\nBy the time medical supplies had been fetched, the body lay motionless, eyes glassy and empty" << std::endl;
				if(chronoTeam.findSpecialist("Jump engineer") != "")
				{
					std::cout << "'Dammit', Drake growled as he cracked the wall with his fist. 'Not another one..'" << std::endl;
					chronoTeam.recordMajorEvent(year + " - " + died + " died during war.");
				}
				else // Jump Engineer has died
				{
					std::cout << "'Thats it then' " << chronoTeam.getSpeaker() << " announced, 'Drake is dead and he was the only one"
					<< "\nwho knew how to operate the WormH-Engine. Lets work on finding a cure for this plague before it gets us too'"
					<< "\n\nAnd so the crew of chrononauts spent the rest of their lives trapped in the past,"
					<< "\na mission in vain." << std::endl;
					chronoTeam.recordMajorEvent(year + " - " + "Drake died during war.");
					return 2;	// *************** Jump Engineer has died, game over.
				}
			}
			chronoTeam.recordMajorEvent(year + " - " + "War killed 1% of the population.");
			chronoTeam.getPopCentre()->increaseTechLvl();
			chronoTeam.getPopCentre()->populationDeath(.01);
			break;
			
		case 6:	// Technological Advancements
			std::cout << "\n'Historians called this a golden age for intellectual advancement' " << chronoTeam.getSpeaker() << " announced."
				<< "\n'We may even bare witness to a technological breakthrough'."
				<< "\nIt was an enlightening period for the local populace and many technological advancements were made." << std::endl;
			chronoTeam.getPopCentre()->increaseTechLvl();
			break;
			
		case 7:	//Social Revolution
			evnt = rand() % 3 + 1;
			if(evnt == 1)
			{
				std::cout << "\nOver the course of this year the time team witnessed a 'Proletarian revolution' in the"
				<< "\nlocal populace. It was a period of great greed and even greater anger. The lower classes were"
				<< "\nsick of being opressed and finally decided to fight back."
				<< "\nA small percentage of the rich were murdered and the power balance shifted for the greater good." << std::endl;
				chronoTeam.getPopCentre()->populationDeath(.002);
				chronoTeam.recordMajorEvent(year + " - " + "Social Revolution occurred, 2% of population died.");
			}
			else if(evnt == 2)
			{
				std::cout << "\nDuring the year the Chrononauts observed a 'Non-Violent Revolution' in the form of protests"
				<< "\nand civil resistance in an attempt to dislodge the authoritarian regime."
				<< "\nOverall the population benefitted from the movement and the land prospered" << std::endl;
				
				chronoTeam.getPopCentre()->applyYearlyGrowth();	// Prosperity causes bonus growth
			}
			else
			{
				std::cout << "\nJust another quiet year of searching." << std::endl;
			}
			break;
			
		case 8:		// Interactions between time-team and locals
			evnt = rand() % 3 + 1;
			if(evnt == 1)	// Locals steal chrononaut information
			{
				std::cout << "\n" << chronoTeam.getSpeaker() << " looked up from the holo-screen as " << chronoTeam.getSpeaker() << " jogged"
					<< "\nin the front door of the campsite, 'you guys aren't gunna believe this'."
					<< "\nMoments later everyone was crowded around the rear side of the Sanctech shelter. A large portion of the"
					<< "\npanelling had been removed, exposed wires hanging loosely from where the cryoshift turbine had once been."
					<< "\nA general stunned silence was broken only by the occasional spark escaping the severed wiring."
					<< "\n'Hope you guys didnt need the Air-con any time soon' " << chronoTeam.getSpeaker() << " mused." << std::endl;
				if (chronoTeam.findSpecialist("Spacegoat") != "")
				{
					std::cout << "'Bahh', smirked Goaty." << std::endl;
					chronoTeam.getChrononaut("Spacegoat").abilityLevelUp();	// Chaos befits the goat
				}	
				chronoTeam.getPopCentre()->increaseTechLvl();	
					
			}
			else if(evnt == 2 && chronoTeam.findSpecialist("Doctor") != "")	// Doctor heals local boy
			{
				std::cout << "\nThe next morning the crew were awoken by a urgent banging on the exterior of the shelter."
					<< "\n'PLEASE HELP!', a womans voice rang out, 'my boy!, hes been in an accident!!'." << std::endl;
				if (chronoTeam.findSpecialist("Security") != "")
					std::cout << "\n" << chronoTeam.findSpecialist("Security") << " charged his plasma rifle, 'just in case', he winked." << std::endl;
				if (chronoTeam.findSpecialist("Doctor") != "" && chronoTeam.getChrononaut("Doctor").getAbilityLevel() > 3)
				{
					std::cout << "\n'I'm a doctor, quick, bring your son up into the Med-bay', " << chronoTeam.findSpecialist("Doctor") << " exclaimed."
						<< "\nThe surgery went well, thanks to the futuristic medicine available and the boy survived" << std::endl;
				}
				else
				{
					std::cout << "\nThe crew did what they could but the boy was deemed unsavable."
						<< "\nLater on, when the woman had left, the crew found an old book sitting in the Med-bay."
						<< "\n'Must of been hers.. 'A brief history of the " << chronoTeam.getPopCentre()->getTechName() << " age.'" << std::endl;

					if (chronoTeam.findSpecialist("Historian") != "")
					{
						chronoTeam.getChrononaut("Historian").abilityLevelUp();	// The book has some insightful historical information
						std::cout << "The historian gleamed some insightful information from the woman's book.";
					}
				}	
			}
			else	// Spacegoat gets hunted
			{
				if (chronoTeam.findSpecialist("Spacegoat") != "")
				{
					std::cout << "\n'Has anyone seen that bloody goat around lately?' " << chronoTeam.getSpeaker() << " asked."
						<< "\nLittle did the crew know, Goaty had been planted as an undercover agent for the forces of chaos in"
						<< "\nthe year 2525. \nHis mission: Collect and confer sensitive information about the artifacts"
						<< "\nand WormH-Engine technology."
						<< "\nSafe to say, his sinister plot had come to an unexpected end when some of the local "
						<< "\nhunters had captured him and turned him into a delightful stew. "
						<< "\nRest in peace you evil goat." << std::endl;
					chronoTeam.goatyDied();
					chronoTeam.recordMajorEvent(year + " - " + "The Spacegoat was killed by hungry locals.");
				}
				else
				{
					std::cout << "\nThe crew spent the year searching uninterrupted." << std::endl;
				}
			}
			break;
			
		case 9:		// Chrononaut specific event
			if(chronoTeam.getPopCentre()->hasFunctionality("Blacksmith"))	// horseshoes for goaty
			{
				if (chronoTeam.findSpecialist("Spacegoat") != "")
				{
					std::cout << "'Bahhhhhhhhhhh', roared Goaty."
						<< "\n'Jesus alright alright, we will go get you some new shoes. Let me just coordinate the GPS to find the local"
						<< "\nBlacksmith...'"
						<< "\nGoaty got some dope new shoes." << std::endl;
					chronoTeam.getChrononaut("Spacegoat").abilityLevelUp();
				}
				else if(chronoTeam.findSpecialist("Dark Arts") != "")	// Ghost skill level up
				{
					std::cout << "\n'Woah check out this creepy talisman I bought at the blacksmith!', " << chronoTeam.getSpeaker() << " seemed"
						<< "\necstatic. 'Jeez that things creepy'."
						<< "\nPeep the ghost started flying around the room enthusiastically..." << std::endl;
					chronoTeam.levelUp("Dark Arts");
				}
				break;
			}

			if (chronoTeam.getPopCentre()->hasFunctionality("Consciousness Sim"))	// Turtle town
			{
				if (chronoTeam.findSpecialist("Timewarper") != "")	// Turtle town
				{
					std::cout << "\nYoghurt the turtle was a deep thinker."
						<< "\nA deep thinker indeed. Often he would lose himself in thought for hours, days even before he would snap"
						<< "\nback to reality and immediately forget the powerful realizations he had experienced."
						<< "\nThis is why he was so excited to find the Consciousness Simulator in town accepted all species."
						<< "\nHe would stroll in, upload his mental wireframe and stroll out 10 minutes later with days worth of"
						<< "\nconscious observations....     reviewing this material on the other hand, would take hours, days even.." << std::endl;
					chronoTeam.levelUp("Timewarper");
						chronoTeam.levelUp("Dark Arts");
				}
				break;
			}
			
			if(chronoTeam.getPopCentre()->hasFunctionality("Mercenary Agency"))	// More ammo
			{
				std::cout << "\n'Wouldn't hurt to have a little more firepower for this mission, wouldn't you say?'" 
					<< "\nThe crew agreed readily as they ducked into the Mercenary Agency to buy a few more guns." << std::endl;
				chronoTeam.getChrononaut("Security").abilityLevelUp();
				break;
			}
			
			if(chronoTeam.getPopCentre()->hasFunctionality("Mercenary Agency"))	// More ammo
			{
				std::cout << "\n'Wouldn't hurt to have a little more firepower for this mission, wouldn't you say?'" 
					<< "\nThe crew agreed readily as they ducked into the Mercenary Agency to buy a few more guns." << std::endl;
				chronoTeam.getChrononaut("Security").abilityLevelUp();
				break;
			}
			
			if(chronoTeam.getPopCentre()->hasFunctionality("Nano-Medicine"))	// Better healthcare
			{
				std::cout << "\n'We better grab a few more Medkits for the trip' " << chronoTeam.getSpeaker() << " suggested." 
					<< "\n'Chances are we are going to encounter a few threats and id rather be safe than sorry'." << std::endl;
				if(chronoTeam.findSpecialist("Doctor") != "")
					chronoTeam.getChrononaut("Doctor").abilityLevelUp();
				break;
			}
			
			if(chronoTeam.getPopCentre()->hasFunctionality("Military Camp"))	// Angry locals
			{
				std::cout << "\n'Shit, the army is onto us..  they think we are aliens or something' " << chronoTeam.getSpeaker() << " wheezed as they came running" 
					<< "\nthrough the door. 'Guns up!' Drake yelled, calling everyone to action." << std::endl;
				if(chronoTeam.findSpecialist("Security") != "" && chronoTeam.getChrononaut("Security").getAbilityLevel() > 3)
				{
					std::cout << chronoTeam.findSpecialist("Security") << " slid past the window on his knee, ridle rattling as he sprayed troops with lazers"
						<< "\n'Come get some!!', he chirped, obviously enjoying the situation."
						<< "\nIt wasn't long before all was quiet once more, the area secure."
						<< "\n'Lets get the Sanctech shelter packed up and redeployed on the other side of time, run the active mirrorflague this time' Drake ordered" << std::endl;
						break;
				}
				else	// Army scores a blow againts the time-team
				{
					std::cout << "\nWhen the artillary had finished blasting, one of the crew wasn't responding over the commset" << std::endl;
					if(chronoTeam.findSpecialist("Doctor") != "" && chronoTeam.getChrononaut("Doctor").getAbilityLevel() > 3)
					{
						std::cout << "\n'Got them on their back!' " << chronoTeam.findSpecialist("Doctor") << " yelled, blood covering her hands"
							<< "\nFzzzrt, the stimFix buzzed as it injected the nano-elixer into the patients veins"
							<< "\n'That should do it, he should be alright' " << chronoTeam.findSpecialist("Doctor") << " said as she stepped back, hands shaking." << std::endl;
							break;
					}
					else
					{
						std::string died = chronoTeam.hasDied();
						std::cout << died << "'s body was found, mangled on the grass outside the shelter."
							<< "\n'Damn this place, these people are monsters..' " << chronoTeam.getSpeaker() << " breathed." << std::endl;
						if(chronoTeam.findSpecialist("Jump engineer") == "")
						{
							std::cout << "\n'We better get used to them guys.. we aren't going anywhere now that Drake is dead." << std::endl;
							return 2;	// *************** Jump Engineer has died, game over.
						}
						chronoTeam.recordMajorEvent(year + " - " + died + " was killed by local armed forces.");
						break;
					}
				}
				break;
			}
			
		case 10:
			if(chronoTeam.getPopCentre()->hasFunctionality("WitchDoctor"))
			{
				std::cout << "\nA strange mist came over the land.."
					<< "\n'What the hell?' " << chronoTeam.getSpeaker() << " said, as everyone suddenly felt the"
					<< "\nchill of winter still the air. The fog became so thick that the crew could barely even see"
					<< "\none another."
					<< "\n'Stay together everyone!' a voice echoed through the mist, nobody was able to place the "
					<< "\nspeaker..  faintly in the distance, the sound of rattling bones caught everyones attention"
					<< "\n" << chronoTeam.getSpeaker() << " spun around, 'Jesus that is creepy!'" << std::endl;
					
				if(chronoTeam.findSpecialist("Dark Arts") != "" && chronoTeam.getChrononaut("Dark Arts").getAbilityLevel() > 3)
				{
					std::cout << "\nPeep floated gently through the mist, finding comfort in its opacity"
						<< "\nA small wooden shack phased into vision."
						<< "\nA very tall, gangly figure holding a staff of wood stood on the porch, watching Peep"
						<< "\n'I have something for you', it's voice grated against the silence like coarse gravel under-foot"
						<< "\nHe handed Peep a scrap of parchment,"
						<< "\nwritten upon it was the entirety of the information that the crew had sought to find"
						<< "\n'A balance must be kept', the tall figure groaned"
						<< "\n\nThe mist Faded away leaving Peep standing once more, right beside the crew.."
						<< "\nexcept Felix was missing." << std::endl;
					
					chronoTeam.getChrononaut("Security").hasDied();	// Felix went missing
					chronoTeam.recordMajorEvent(year + " - " + "Felix dissappeared into the mist. Never to be seen again.");
					chronoTeam.findInformation(1);	// The parchment contains all infomation
					chronoTeam.recordMajorEvent(year + " - " + "A terrifying Witchdoctor gave Peep all the info for this Artifact.");
					
				}
				else
				{
					std::cout << "\nMoments later, the mist subsided, evaporating as if they had never even been there." << std::endl;
				}	
			}
			
		default:
			std::cout << "\nThe crew spent the year searching uninterrupted." << std::endl;
			break;
	}
	return 0;	// *************** The Mission continues
}

