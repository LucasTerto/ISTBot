//=================================================================================================
//                    Copyright (C) 2017 Olivier Mallet - All Rights Reserved                      
//=================================================================================================

#ifndef RUN_FILE
#define RUN_FILE

#include "../header/GeneticAlgorithm.hpp"


int main()
{
	// initializing parameters lower and upper bounds
	// an initial value can be added inside the initializer list after the upper bound
	//galgo::Parameter<double> par1({0.0,1.0});
	// galgo::Parameter<double> par2({0.0,13.0}); //13 has to be map size - 1
	// here both parameter will be encoded using 16 bits the default value inside the template declaration
	// this value can be modified but has to remain between 1 and 64

	//enemy class name to initialize the units
	std::string enemyClass = "Protoss";//should get the name through bwapi
	std::string myClass = "Zerg";//should get the name through bwapi
	std::vector<BWAPI::UnitType> enemyUnits = { BWAPI::UnitTypes::Protoss_Zealot.getID(), BWAPI::UnitTypes::Protoss_Dragoon.getID(), BWAPI::UnitTypes::Protoss_Reaver.getID(), BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Protoss_Archon.getID() };

	// initiliazing genetic algorithm
	galgo::GeneticAlgorithm ga(200,100, 0);

	// running genetic algorithm
	ga.run(enemyClass, myClass, enemyUnits);
}
#endif