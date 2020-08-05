#include <iostream>
#include <string>
#include <sstream>

#include "chrononaut.h"
#include "inventory.h"
#include "populationCentre.h"
#include "driverClasses.h"

using namespace std;

// g++ -o AAT ass2.cpp driverClasses.cpp chrononaut.cpp inventory.cpp populationCentre.cpp


int main(int argc, char *argv[])
{
	
	srand(time(0));
	
	if(argc != 3)
	{
		std::cerr << "Program terminated" << std::endl;
		std::cerr << "Insufficient arguments to run program." << std::endl;
		exit(0);
	}
	
	if(atoi(argv[1]) > 5 || atoi(argv[1]) <= 0)
	{
		std::cerr << "Program terminated" << std::endl;
		std::cerr << "Max Artifacts allowed must be < 5 and > 0." << std::endl;
		exit(0);
	}
	
	if(atoi(argv[2]) < 1)
	{
		std::cerr << "Program terminated" << std::endl;
		std::cerr << "Max Jumps must be greater than 0." << std::endl;
		exit(0);
	}
	
	// User input
	int totalArtifacts = atoi(argv[1]);
	int totalJumps = atoi(argv[2]);
	int totalYearsToSearch = 10;

	
	// Inventory
	Artifact a1("Zoidbringer", "A Demonic device capable of opening a portal between our \nreality and the Zetherealm.");
	Artifact a2("Djonns Hammer", "A mythically powerfull weapon, a remnant of the war with\nthe gods. This weapon suppossably struck down the titan Guerix. ");
	Artifact a3("Calling Stones", "Two indiviuduals can communicate with eachother no \nmatter the distance while each holding a stone.");
	Artifact a4("Silla Bird", "The end of several civilizations have been attributed to \nthe corruption this petrified bird carries.");
	Artifact a5("Ester's Map", "A map which tells the holder the direction to travel for \nendless riches - on a side note: insanity follows.");
	
	
	// Chronoteam
	ChronoTeam chronoTeam;
	
	chronoTeam.getInventory()->loadArtifact(a1);
	chronoTeam.getInventory()->loadArtifact(a2);
	chronoTeam.getInventory()->loadArtifact(a3);
	chronoTeam.getInventory()->loadArtifact(a4);
	chronoTeam.getInventory()->loadArtifact(a5);
	chronoTeam.getInventory()->nextArtifact();	// Initialise first Artifact
	

	// Events
	EventFactory eventFactory;
	
	// Program variables
	int yearsSearched = 1;
	int jumpsMade = 1;
	int outcome = 0;

	// Program
	
	std::cout << "|----------------------------------------------|" << std::endl;
	std::cout << "|---*-*-*-*-- An Adventure in Time --*-*-*-*---|" << std::endl;
	std::cout << "|----------------------------------------------|\n" << std::endl;
	
	chronoTeam.displayTeam();
	
	std::cout << "\nThe door slammed open, snapping everyone in the room to attention."
		<< "\nAdmiral Frost strode heavily into the room and planted himself at the centre of the half-circle"
		<< "\noperational table."
		<< "\n'Welcome to the mission briefing. You have all been selected for this mission for your"
		<< "\noutstanding performance in your respective fields.. and lord knows we need the best'."
		<< "\nThe admiral's intense gaze wavered for a moment, Drake could of sworn he saw frustration"
		<< "\nand maybe event.. regret? in his eyes. The moment passed and that familiar fervor"
		<< "\nreglazed Frost's features."
		
		<< "\n\n'Let us not waste breath' he growled, 'We have collected intel on a variety of powerful"
		<< "\nArtefacts that could shape the future of the human race, undoubtably'."
		<< "\nAstra shifted uncomfortably in her chair, visably unnerved by Frost's demeanour."
		
		<< "\n\n'Long story short, we need information on these artefacts. If we are to understand their true powe.."
		<< "\n'You seek to use them for your own means!', Astra stood up quickly, her chair skidding backwards."
		<< "\n'Astra please, if you only understood the danger these items posed to our way of life..'."
		<< "\n\nThe door swang open again as a well dressed man ushered himself up to Frost's side and whispered"
		<< "\nsomething into his ear before leaving abruptly"
		<< "\n'It would seem we are out of time, please make you way to launch bay, The WormH-Engine has fully charged, "
		<< "\nDrake, I trust you are prepared to lead these men.'"
		<< "\nHe nodded."
		<< "\n'Good, you will be briefed on each Artefact prior to launch, I trust you all understand the importance"
		<< "\nof a successfull mission'. Frost met each crew member's eyes before pivoting on his heel and"
		<< "\nstriding out of the room."
		
		<< "\n\nMinutes later, the crew were in the launch room, Drake felt it more a cold dark closet."
		<< "\nAn overly ecstatic scientist with thick-rimmed glasses was making the final touches on the engine,"
		<< "\nmuttering to himself, '..keep your arms and legs inside the ride at all times -uhum', he paused"
		<< "\nas if waiting for laughter. The room was deathly silent. His grin grew wider."
		<< "\n'Don't fret, you will be back in moment!'."
		<< "\nAstra looked ready to punch the man." << std::endl;
	

	while (chronoTeam.getInventory()->getCurrentArtifact() < totalArtifacts) // Artifact Cycle -----------------------------
	{
		if(chronoTeam.getInventory()->getCurrentArtifact() > 0)
			chronoTeam.resetPopCentre();	// Initialise Population Centre to metropolis
		
		// introduce artefact
		std::cout << "\n'Indeed the mission!', The scientist coughed."
			<< "\nHe handed Drake a dishevelled scrap of paper, scribble at the top and a hastily drawn picture below,"
			<< "\n\n    ---- The Objective ----\n" << std::endl;
		chronoTeam.getInventory()->displayArtifactInfo();

		outcome = 0;	// Reset
		jumpsMade = 1;	// Reset

		std::cout << "\nAn ominous sense of Deja-vu washed over Drake, 'this feels... familiar..'."
			<< "\nBefore anyone else had a chance to speak, the very fabric of time split apart in front of the"
			<< "\ncrew's eyes. Immediately followed by a deafening roar, The rift shimmered, reflected and"
			<< "\nrefracted light all at once, it was nauseating to observe."
			<< "\n'GO GO GO!' the scientist screamed, 'and don't forget your god-damn sci-fi pet!!'."
			<< "\n\nOne by one, the crew stepped into the void." 
		<< "\n\n\n                      --~~ZZeeoowwWW~~--\n" << std::endl;
		
		while (jumpsMade <= totalJumps)		// Jump Cycle --------------------------------------------------
		{
			chronoTeam.chronoJump(chronoTeam.getInventory()->getClue());	// ChronoJump  
			
			// Display Header Info
			std::cout << "\n_____________________________________________________________________________________________" << std::endl;
			std::cout << "\n______ARTIFACT: " << chronoTeam.getInventory()->getArtifactName() << "_________CHRONO-JUMP SITE #" 
			<< jumpsMade << " ____________YEAR " << chronoTeam.getPopCentre()->getYear() 
			<< "______________" << std::endl;
			std::cout << "\n________WHERE: " << chronoTeam.getPopCentre()->getName() << "___________POPULATION: " << chronoTeam.getPopCentre()->getPopulation() << "______"
				<< "_______TECH: " << chronoTeam.getPopCentre()->getTechName() << "____________\n" << std::endl;
			chronoTeam.getPopCentre()->displayTechEraInfo();
			
			yearsSearched = 1;	// reset
			
			std::cout << "Drake pointed to a patch of even grassland outside the centre,"
				<< "\n'Let's set up base over there and start searching for info'. The crew nodded." << std::endl;
			
			while(yearsSearched <= totalYearsToSearch)	// Search Years
			{
				std::cout << "\n-------------- SEARCH YEAR #" << yearsSearched;
				chronoTeam.searchYear();
				outcome = eventFactory.generateEvent(chronoTeam, yearsSearched);
				
				yearsSearched++;
				
				if(outcome == 2 || outcome == 1)	// Break cases
					break;
				
				if(chronoTeam.getInventory()->getPercentFound() == 1)
					break;
				
				if(eventFactory.searchComplete())
				{
					std::cout << "\n           ! - Jump Site Complete - !"
						<< "\n\nThe crew had successfully acquired this site's information and jump clue."
						<< "\n'Onwards and upwards!...  or backwards.. or inwards, whichever way time moves..'"
						<< "\n\n'Okay team, we found what we came for, let's prep the WormH-Engine for temporal shift.'"
						<< "\nBy early evening, the crew was packed and had initiated Chronojump protocol." << std::endl;
					break;
				}
			}
			
			if(outcome == 2 || outcome == 1)	// 2 - Jump engineer has died, end story | 1 - Artefact is fake, end run through
				break;
				
			if(chronoTeam.getInventory()->getPercentFound() == 1)	// 100% info found
			{
				std::cout << "\n'Woah what a mission!' " << chronoTeam.getSpeaker() << " announced."
					<< "\nThey all agreed. Thankfully, the search for information about the " << chronoTeam.getInventory()->getArtifactName()
					<< "\nhad been gruelling, but it was now over. Drake wasted no time getting the crew organised and"
					<< "\ncalibrating the WormH-Engine to take them back to 2525."
					<< "\nIt would be good to get home, Drake thought, even if it was only for a moment."
					<< "\n\nSeveral hours later, the familiar warm buzz of Scio-Electronic decompression was splitting apart"
					<< "\nThe very electrons of the crew's existance, warping them back to 2525."
					<< "\nNobody was excited to see that mad scientist again." << std::endl;
				
				break;	// Finish searching for this Artifact
			}
	
			jumpsMade++;
		}
		
		if(chronoTeam.getInventory()->getPercentFound() != 1)	// info not all found found
		{
			std::cout << "\nThe crew hadn't found all the required information but due to the circumstances"
				<< "\nof this mission, they had to end the search and continue back to 2525" << std::endl;
		}
		
		if(outcome == 2)	// 2 - Jump engineer has died, end story
			break;
			
		// Chance for Jump engineer to improve skill every chronoJump
		int jumpLvlUp = rand() % 20 + 1;
		if(jumpLvlUp == 1)
			chronoTeam.levelUp("Drake");
		
		chronoTeam.getInventory()->nextArtifact();	// Shift to next Artefact
		
		std::cout << "\n  ---====###%%%%% ---> BACK TO THE PRESENT." << std::endl;
	}
	
	if(outcome != 2)
	{
		std::cout << "\n\n---------------------------------------------------------------------------\n"
			<< "________________ 2525 - Present Day - Post Mission Meeting ________________"
			<< "\n---------------------------------------------------------------------------\n"
			<< "\nThe mission was a success."
			<< "\n\nAdmiral Frost, stood at stiff attention, no emotion clouded his face."
			<< "\n'My highest compliments to you and your crew, I understand that this mission"
			<< "\ntook a heavy toll' he paused, a brief moment of silence for the temporal carnage"
			<< "\nthat this mission no doubt caused."
			<< "\n'Please have your mission report on my desk by the morning, I'll see you all on Monday'."
			<< "\nAnd with that, Frost saluted the crew and left the room."
			<< "\n\n'Screw that guy' " << chronoTeam.getSpeaker() << " said."
			<< "\nThe rest of the crew nodded." << std::endl;
	}
	
	if(outcome == 2)
	{
		std::cout << "\nDrake's Time-team was lost in action, thier team unaccounted for."
		<< "\nLuckily, our recent team was able to triangulate thier last temporal whereabouts"
		<< "\nand track their last recorded information readings down."
		<< "\nThe crews final report was as follows:" << std::endl;
	}
	
	std::cout << "\n---------------------------------------------------------------------"
		<< "\n                       MISSION REPORT                              "
		<< "\n---------------------------------------------------------------------" << std::endl;

	chronoTeam.missionReport();
	
}

