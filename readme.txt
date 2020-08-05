
Readme

Compile Instructions:

	g++ -o AAT ass2.cpp driverClasses.cpp chrononaut.cpp inventory.cpp populationCentre.cpp

Run Program

	./AAT n m


where n is the number of artefacts to be traced, and m is the number of jumps to be made for each
artefact. The value of n should be in the range 1 to 5 inclusive. The value of m should be in the range 1
to 10 inclusive.



1. deleted growth modifier from my town copy constructor, resulting in a 'too high' rate of populaiton shrink.
during that period.

growthModifier = 0.004;

2.