#include "Common.h"
#include "StrategyManager.h"
#include "UnitUtil.h"

using namespace UAlbertaBot;

// constructor
StrategyManager::StrategyManager() 
	: _selfRace(BWAPI::Broodwar->self()->getRace())
	, _enemyRace(BWAPI::Broodwar->enemy()->getRace())
    , _emptyBuildOrder(BWAPI::Broodwar->self()->getRace())
	, _ga(galgo::GeneticAlgorithm(200, 100, 0))
{

}

// get an instance of this
StrategyManager & StrategyManager::Instance() 
{
	static StrategyManager instance;
	return instance;
}

const int StrategyManager::getScore(BWAPI::Player player) const
{
	return player->getBuildingScore() + player->getKillScore() + player->getRazingScore() + player->getUnitScore();
}

const BuildOrder & StrategyManager::getOpeningBookBuildOrder() const
{
    auto buildOrderIt = _strategies.find(Config::Strategy::StrategyName);

    // look for the build order in the build order map
	if (buildOrderIt != std::end(_strategies))
    {
        return (*buildOrderIt).second._buildOrder;
    }
    else
    {
        UAB_ASSERT_WARNING(false, "Strategy not found: %s, returning empty initial build order", Config::Strategy::StrategyName.c_str());
        return _emptyBuildOrder;
    }
}

const bool StrategyManager::shouldExpandNow() const
{
	// if there is no place to expand to, we can't expand
	if (MapTools::Instance().getNextExpansion() == BWAPI::TilePositions::None)
	{
        BWAPI::Broodwar->printf("No valid expansion location");
		return false;
	}

	size_t numDepots    = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Terran_Command_Center)
                        + UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Protoss_Nexus)
                        + UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Hatchery)
                        + UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Lair)
                        + UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Hive);
	int frame           = BWAPI::Broodwar->getFrameCount();
    int minute          = frame / (24*60);

	// if we have a ton of idle workers then we need a new expansion
	if (WorkerManager::Instance().getNumIdleWorkers() > 10)
	{
		return true;
	}

    // if we have a ridiculous stockpile of minerals, expand
    if (BWAPI::Broodwar->self()->minerals() > 3000)
    {
        return true;
    }

    // we will make expansion N after array[N] minutes have passed
    std::vector<int> expansionTimes = {5, 10, 20, 30, 40 , 50};

    for (size_t i(0); i < expansionTimes.size(); ++i)
    {
        if (numDepots < (i+2) && minute > expansionTimes[i])
        {
            return true;
        }
    }

	return false;
}

void StrategyManager::addStrategy(const std::string & name, Strategy & strategy)
{
    _strategies[name] = strategy;
}

bool StrategyManager::hasEnemyUnitsChanged(std::vector<BWAPI::UnitType> unitsVector) {
	if (unitsVector.size() < 1) return false;
	if (_enemyUnitsVector.size() < 1) {
		return true;
	}
	//has room for improvement, testing only
	if (_enemyUnitsVector.size() >= unitsVector.size()) {
		return false;
	}
	for (int i = 0; i < _enemyUnitsVector.size(); i++) {
		if (_enemyUnitsVector[i].getID() != unitsVector[i].getID()) {
			return true;
		}
	}
	return false;
}


std::map<BWAPI::UnitType, int> StrategyManager::getNewBuildOrderGoal(){
	BWAPI::Race myRace = BWAPI::Broodwar->self()->getRace();
	BWAPI::Race enemyRace = BWAPI::Broodwar->enemy()->getRace();
	std::vector<BWAPI::UnitType> currentUnitsVector;
	for (BWAPI::Unit unit : BWAPI::Broodwar->enemy()->getUnits())
	{
		if (unit->isVisible() && !unit->getType().isBuilding()) {
			currentUnitsVector.push_back(unit->getType());
		}
	}
	if (hasEnemyUnitsChanged(currentUnitsVector)) {
		_enemyUnitsVector = currentUnitsVector;
	}
	else {
		return std::map<BWAPI::UnitType, int>();
	}
	writeEnemyUnits(_enemyUnitsVector);
	return this->_ga.run(BWAPI::Broodwar->enemy()->getRace().getName(), BWAPI::Broodwar->self()->getRace().getName(), _enemyUnitsVector);
}

void StrategyManager::writeEnemyUnits(std::vector<BWAPI::UnitType> _enemyUnitsVector) {
	std::string enemyString = "Enemy Units: \n";
	for (int i = 0; i < _enemyUnitsVector.size(); i++) {
		enemyString = enemyString + _enemyUnitsVector[i].getName() + " ";
	}
	writeToFile(enemyString);
}

const MetaPairVector StrategyManager::getBuildOrderGoal()
{
    BWAPI::Race myRace = BWAPI::Broodwar->self()->getRace();
	std::map<BWAPI::UnitType, int> goalMap = getNewBuildOrderGoal();
	MetaPairVector goal = MetaPairVector();

	const clock_t begin_time = clock();
	// do something
	
    if (myRace == BWAPI::Races::Protoss)
    {
		goal = getProtossGABuildOrderGoal(goalMap);
		writeToFile(getTimeString(std::to_string(float(clock() - begin_time) / CLOCKS_PER_SEC)));
    }
    else if (myRace == BWAPI::Races::Terran)
	{
		goal = getTerranGABuildOrderGoal(goalMap);
		writeToFile(getTimeString(std::to_string(float(clock() - begin_time) / CLOCKS_PER_SEC)));
	}
    else if (myRace == BWAPI::Races::Zerg)
	{
		goal = getZergGABuildOrderGoal(goalMap);
		writeToFile(getTimeString(std::to_string(float(clock() - begin_time) / CLOCKS_PER_SEC)));
	}
    return goal;
}

std::string StrategyManager::getTimeString(std::string time) {
	time = "\n------------------------------------------------------------------------------------------------------\nTime: " + time;
	return time;
}

MetaPairVector StrategyManager::getBuildingsNeeded(MetaPairVector goal, int numWorkers) {
	int hasSpawningPool = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Spawning_Pool);
	int hasHydraliskDen = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Hydralisk_Den);
	int hasExtractor = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Extractor);
	int hasEvolutionChamber = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Evolution_Chamber);
	int hasCreepColony = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Creep_Colony);
	int hasSunkerColony = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Sunken_Colony);
	int hasSporeColony = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Spore_Colony);
	int hasLair = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Lair);
	int hasQueensNest = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Queens_Nest);
	int hasSpire = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Spire);
	int hasHive = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Hive);
	int hasGreaterSpire = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Greater_Spire);
	int hasNydusCanal = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Nydus_Canal);
	int hasUltraliskCavern = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Ultralisk_Cavern);
	int hasDefilerMound = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Defiler_Mound);

		//depending on units we need to add buildings to buildOrder
		//some buildings work best while having duplicates (need a logic for this) (not all buildings just a few) //hydralisk den //colonies // hive //etc...
	for (int i = 0; i < goal.size(); i++) {
		if (goal.at(i).first.getName().compare(BWAPI::UnitTypes::Zerg_Defiler.getName()) == 0) {
			//add 1 to buildings needed
			hasSpawningPool++;
			hasLair++;
			hasQueensNest++;
			hasHive++;
			hasDefilerMound++;
			hasExtractor++;
		}
		else if (goal.at(i).first.getName().compare(BWAPI::UnitTypes::Zerg_Ultralisk.getName()) == 0) {
			hasSpawningPool++;
			hasLair++;
			hasQueensNest++;
			hasHive++;
			hasUltraliskCavern++;
			hasExtractor++;
		}
		else if (goal.at(i).first.getName().compare(BWAPI::UnitTypes::Zerg_Queen.getName()) == 0) {
			hasSpawningPool++;
			hasLair++;
			hasQueensNest++;
			hasExtractor++;
		}
		else if (goal.at(i).first.getName().compare(BWAPI::UnitTypes::Zerg_Devourer.getName()) == 0) {
			hasSpawningPool++;
			hasLair++;
			hasQueensNest++;
			hasHive++;
			hasSpire++;
			hasGreaterSpire++;
			hasExtractor++;
		}
		else if (goal.at(i).first.getName().compare(BWAPI::UnitTypes::Zerg_Guardian.getName()) == 0) {
			hasSpawningPool++;
			hasLair++;
			hasQueensNest++;
			hasHive++;
			hasSpire++;
			hasGreaterSpire++;
			hasExtractor++;
		}
		else if (goal.at(i).first.getName().compare(BWAPI::UnitTypes::Zerg_Mutalisk.getName()) == 0) {
			hasSpawningPool++;
			hasLair++;
			hasSpire++;
			hasExtractor++;
		}
		else if (goal.at(i).first.getName().compare(BWAPI::UnitTypes::Zerg_Scourge.getName()) == 0) {
			hasSpawningPool++;
			hasLair++;
			hasSpire++;
			hasExtractor++;
		}
		else if (goal.at(i).first.getName().compare(BWAPI::UnitTypes::Zerg_Lurker.getName()) == 0) {
			hasSpawningPool++;
			hasHydraliskDen++;
			hasLair++;
			hasExtractor++;
		}
		else if (goal.at(i).first.getName().compare(BWAPI::UnitTypes::Zerg_Hydralisk.getName()) == 0) {
			hasSpawningPool++;
			hasHydraliskDen++;
		}
		else if (goal.at(i).first.getName().compare(BWAPI::UnitTypes::Zerg_Zergling.getName()) == 0) {
			hasSpawningPool++;
		}
	}
	//if > 0 add to build order buildings needed
	//how to add upgrades?
	if (hasCreepColony > 0) {
		goal.push_back(MetaPair(BWAPI::UnitTypes::Zerg_Creep_Colony, 1));
	}
	if (hasDefilerMound > 0) {
		goal.push_back(MetaPair(BWAPI::UnitTypes::Zerg_Defiler_Mound, 1));
	}
	if (hasEvolutionChamber > 0) {
		goal.push_back(MetaPair(BWAPI::UnitTypes::Zerg_Evolution_Chamber, 1));
	}
	if (hasExtractor > 0) {
		goal.push_back(MetaPair(BWAPI::UnitTypes::Zerg_Drone, numWorkers < 8 ? 8 : numWorkers));
		goal.push_back(MetaPair(BWAPI::UnitTypes::Zerg_Extractor, 1));
	}
	if (hasGreaterSpire > 0) {
		goal.push_back(MetaPair(BWAPI::UnitTypes::Zerg_Greater_Spire, 1));
	}
	if (hasHive > 0) {
		goal.push_back(MetaPair(BWAPI::UnitTypes::Zerg_Hive, 1));
	}
	if (hasHydraliskDen > 0) {
		goal.push_back(MetaPair(BWAPI::UnitTypes::Zerg_Hydralisk_Den, 1));
	}
	if (hasLair > 0) {
		goal.push_back(MetaPair(BWAPI::UnitTypes::Zerg_Lair, 1));
	}
	if (hasNydusCanal > 0) {
		goal.push_back(MetaPair(BWAPI::UnitTypes::Zerg_Nydus_Canal, 1));
	}
	if (hasQueensNest > 0) {
		goal.push_back(MetaPair(BWAPI::UnitTypes::Zerg_Queens_Nest, 1));
	}
	if (hasSpawningPool > 0) {
		goal.push_back(MetaPair(BWAPI::UnitTypes::Zerg_Spawning_Pool, 1));
	}
	if (hasSpire > 0) {
		goal.push_back(MetaPair(BWAPI::UnitTypes::Zerg_Spire, 1));
	}
	if (hasSporeColony > 0) {
		goal.push_back(MetaPair(BWAPI::UnitTypes::Zerg_Spore_Colony, 1));
	}
	if (hasSunkerColony > 0) {
		goal.push_back(MetaPair(BWAPI::UnitTypes::Zerg_Sunken_Colony, 1));
	}
	if (hasUltraliskCavern > 0) {
		goal.push_back(MetaPair(BWAPI::UnitTypes::Zerg_Ultralisk_Cavern, 1));
	}
	return goal;
}

MetaPairVector StrategyManager::getProtossGABuildOrderGoal(std::map<BWAPI::UnitType, int> goalMap)
{
	// the goal to return
	MetaPairVector goal;

	int numZealots = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Protoss_Zealot);
	int numPylons = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Protoss_Pylon);
	int numDragoons = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Protoss_Dragoon);
	int numProbes = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Protoss_Probe);
	int numNexusCompleted = BWAPI::Broodwar->self()->completedUnitCount(BWAPI::UnitTypes::Protoss_Nexus);
	int numNexusAll = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Protoss_Nexus);
	int numCyber = BWAPI::Broodwar->self()->completedUnitCount(BWAPI::UnitTypes::Protoss_Cybernetics_Core);
	int numCannon = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Protoss_Photon_Cannon);
	int numScout = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Protoss_Corsair);
	int numReaver = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Protoss_Reaver);
	int numDarkTeplar = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Protoss_Dark_Templar);

	for (auto it = goalMap.cbegin(); it != goalMap.cend(); ++it) {
			goal.push_back(MetaPair(it->first, it->second));
		
	}
	// add observer to the goal if the enemy has cloaked units
	if (InformationManager::Instance().enemyHasCloakedUnits())
	{
		goal.push_back(MetaPair(BWAPI::UnitTypes::Protoss_Robotics_Facility, 1));

		if (BWAPI::Broodwar->self()->completedUnitCount(BWAPI::UnitTypes::Protoss_Robotics_Facility) > 0)
		{
			goal.push_back(MetaPair(BWAPI::UnitTypes::Protoss_Observatory, 1));
		}
		if (BWAPI::Broodwar->self()->completedUnitCount(BWAPI::UnitTypes::Protoss_Observatory) > 0)
		{
			goal.push_back(MetaPair(BWAPI::UnitTypes::Protoss_Observer, 1));
		}
	}

	// if we want to expand, insert a nexus into the build order
	if (shouldExpandNow())
	{
		goal.push_back(MetaPair(BWAPI::UnitTypes::Protoss_Nexus, numNexusAll + 1));
	}
	
	//get units by reference and add to goal
	return getBuildingsNeeded(goal, 0);
}

const MetaPairVector StrategyManager::getProtossBuildOrderGoal() const
{
	// the goal to return
	MetaPairVector goal;

	int numZealots          = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Protoss_Zealot);
    int numPylons           = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Protoss_Pylon);
	int numDragoons         = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Protoss_Dragoon);
	int numProbes           = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Protoss_Probe);
	int numNexusCompleted   = BWAPI::Broodwar->self()->completedUnitCount(BWAPI::UnitTypes::Protoss_Nexus);
	int numNexusAll         = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Protoss_Nexus);
	int numCyber            = BWAPI::Broodwar->self()->completedUnitCount(BWAPI::UnitTypes::Protoss_Cybernetics_Core);
	int numCannon           = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Protoss_Photon_Cannon);
    int numScout            = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Protoss_Corsair);
    int numReaver           = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Protoss_Reaver);
    int numDarkTeplar       = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Protoss_Dark_Templar);

    if (Config::Strategy::StrategyName == "Protoss_ZealotRush")
    {
        goal.push_back(MetaPair(BWAPI::UnitTypes::Protoss_Zealot, numZealots + 8));

        // once we have a 2nd nexus start making dragoons
        if (numNexusAll >= 2)
        {
            goal.push_back(MetaPair(BWAPI::UnitTypes::Protoss_Dragoon, numDragoons + 4));
        }
    }
    else if (Config::Strategy::StrategyName == "Protoss_DragoonRush")
    {
        goal.push_back(MetaPair(BWAPI::UnitTypes::Protoss_Dragoon, numDragoons + 6));
    }
    else if (Config::Strategy::StrategyName == "Protoss_Drop")
    {
        if (numZealots == 0)
        {
            goal.push_back(MetaPair(BWAPI::UnitTypes::Protoss_Zealot, numZealots + 4));
            goal.push_back(MetaPair(BWAPI::UnitTypes::Protoss_Shuttle, 1));
        }
        else
        {
            goal.push_back(MetaPair(BWAPI::UnitTypes::Protoss_Zealot, numZealots + 8));
        }
    }
    else if (Config::Strategy::StrategyName == "Protoss_DTRush")
    {
        goal.push_back(MetaPair(BWAPI::UnitTypes::Protoss_Dark_Templar, numDarkTeplar + 2));

        // if we have a 2nd nexus then get some goons out
        if (numNexusAll >= 2)
        {
            goal.push_back(MetaPair(BWAPI::UnitTypes::Protoss_Dragoon, numDragoons + 4));
        }
    }
    else
    {
        UAB_ASSERT_WARNING(false, "Unknown Protoss Strategy Name: %s", Config::Strategy::StrategyName.c_str());
    }

    // if we have 3 nexus, make an observer
    if (numNexusCompleted >= 3)
    {
        goal.push_back(MetaPair(BWAPI::UnitTypes::Protoss_Observer, 1));
    }
    
    // add observer to the goal if the enemy has cloaked units
	if (InformationManager::Instance().enemyHasCloakedUnits())
	{
		goal.push_back(MetaPair(BWAPI::UnitTypes::Protoss_Robotics_Facility, 1));
		
		if (BWAPI::Broodwar->self()->completedUnitCount(BWAPI::UnitTypes::Protoss_Robotics_Facility) > 0)
		{
			goal.push_back(MetaPair(BWAPI::UnitTypes::Protoss_Observatory, 1));
		}
		if (BWAPI::Broodwar->self()->completedUnitCount(BWAPI::UnitTypes::Protoss_Observatory) > 0)
		{
			goal.push_back(MetaPair(BWAPI::UnitTypes::Protoss_Observer, 1));
		}
	}

    // if we want to expand, insert a nexus into the build order
	if (shouldExpandNow())
	{
		goal.push_back(MetaPair(BWAPI::UnitTypes::Protoss_Nexus, numNexusAll + 1));
	}

	return goal;
}

MetaPairVector StrategyManager::getTerranGABuildOrderGoal(std::map<BWAPI::UnitType, int> goalMap)
{
	// the goal to return
	std::vector<MetaPair> goal;

	int numWorkers = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Terran_SCV);
	int numCC = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Terran_Command_Center);
	int numMarines = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Terran_Marine);
	int numMedics = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Terran_Medic);
	int numWraith = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Terran_Wraith);
	int numVultures = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Terran_Vulture);
	int numGoliath = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Terran_Goliath);
	int numTanks = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode)
		+ UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode);
	int numBay = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Terran_Engineering_Bay);

	for (auto it = goalMap.cbegin(); it != goalMap.cend(); ++it) {
		if (it->first == BWAPI::UnitTypes::Terran_SCV) {
			numWorkers += it->second;
			goal.push_back(std::pair<MetaType, int>(BWAPI::UnitTypes::Terran_SCV, numWorkers));
		}
		else {
			numWorkers += it->second;
			goal.push_back(std::pair<MetaType, int>(BWAPI::UnitTypes::Terran_Marine, it->second));
		}
	}
	if (shouldExpandNow())
	{
		goal.push_back(std::pair<MetaType, int>(BWAPI::UnitTypes::Terran_Command_Center, numCC + 1));
		goal.push_back(std::pair<MetaType, int>(BWAPI::UnitTypes::Terran_SCV, numWorkers + 10));
	}

	return getBuildingsNeeded(goal, 0);
}

const MetaPairVector StrategyManager::getTerranBuildOrderGoal() const
{
	// the goal to return
	std::vector<MetaPair> goal;

    int numWorkers      = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Terran_SCV);
    int numCC           = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Terran_Command_Center);            
    int numMarines      = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Terran_Marine);
	int numMedics       = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Terran_Medic);
	int numWraith       = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Terran_Wraith);
    int numVultures     = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Terran_Vulture);
    int numGoliath      = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Terran_Goliath);
    int numTanks        = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode)
                        + UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode);
    int numBay          = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Terran_Engineering_Bay);

    if (Config::Strategy::StrategyName == "Terran_MarineRush")
    {
	    goal.push_back(std::pair<MetaType, int>(BWAPI::UnitTypes::Terran_Marine, numMarines + 8));

        if (numMarines > 5)
        {
            goal.push_back(std::pair<MetaType, int>(BWAPI::UnitTypes::Terran_Engineering_Bay, 1));
        }
    }
    else if (Config::Strategy::StrategyName == "Terran_4RaxMarines")
    {
	    goal.push_back(std::pair<MetaType, int>(BWAPI::UnitTypes::Terran_Marine, numMarines + 8));
    }
    else if (Config::Strategy::StrategyName == "Terran_VultureRush")
    {
        goal.push_back(std::pair<MetaType, int>(BWAPI::UnitTypes::Terran_Vulture, numVultures + 8));

        if (numVultures > 8)
        {
            goal.push_back(std::pair<MetaType, int>(BWAPI::TechTypes::Tank_Siege_Mode, 1));
            goal.push_back(std::pair<MetaType, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode, 4));
        }
    }
    else if (Config::Strategy::StrategyName == "Terran_TankPush")
    {
        goal.push_back(std::pair<MetaType, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode, 6));
        goal.push_back(std::pair<MetaType, int>(BWAPI::UnitTypes::Terran_Goliath, numGoliath + 6));
        goal.push_back(std::pair<MetaType, int>(BWAPI::TechTypes::Tank_Siege_Mode, 1));
    }
    else
    {
        BWAPI::Broodwar->printf("Warning: No build order goal for Terran Strategy: %s", Config::Strategy::StrategyName.c_str());
    }



    if (shouldExpandNow())
    {
        goal.push_back(std::pair<MetaType, int>(BWAPI::UnitTypes::Terran_Command_Center, numCC + 1));
        goal.push_back(std::pair<MetaType, int>(BWAPI::UnitTypes::Terran_SCV, numWorkers + 10));
    }

	return goal;
}

void StrategyManager::writeToFile(std::string string) {
	_outputResult = _outputResult + string + "\n------------------------------------------------------------------------------------------------------------------------------\n";



}
std::string StrategyManager::getBuildOrderString(std::map<BWAPI::UnitType, int> goalMap) {
	std::string boString = "MyUnits: ";
	for (auto it = goalMap.cbegin(); it != goalMap.cend(); ++it) {
		boString = boString + it->first.getName() + " -> " + std::to_string( it->second) + "\n";
	}
	return boString;
}

MetaPairVector StrategyManager::getZergGABuildOrderGoal(std::map<BWAPI::UnitType, int> goalMap)
{
	if (goalMap.empty()) return _oldGoal;
	// the goal to return
	writeToFile(getBuildOrderString(goalMap));
	std::vector<MetaPair> goal;
	//buildings have to be added too
	int numWorkers = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Drone);
	int numCC = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Hatchery)
		+ UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Lair)
		+ UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Hive);
	int numMutas = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Mutalisk);
	int numDrones = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Drone);
	int zerglings = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Zergling);
	int numHydras = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Hydralisk);
	int numScourge = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Scourge);
	int numGuardians = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Guardian);
	
	int hasSpawningPool = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Spawning_Pool);
	int hasHydraliskDen = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Hydralisk_Den);
	int hasExtractor = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Extractor);
	int hasEvolutionChamber = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Evolution_Chamber);
	int hasCreepColony = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Creep_Colony);
	int hasSunkerColony = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Sunken_Colony);
	int hasSporeColony = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Spore_Colony);
	int hasLair = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Lair);
	int hasQueensNest = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Queens_Nest);
	int hasSpire = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Spire);
	int hasHive = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Hive);
	int hasGreaterSpire = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Greater_Spire);
	int hasNydusCanal = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Nydus_Canal);
	int hasUltraliskCavern = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Ultralisk_Cavern);
	int hasDefilerMound = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Defiler_Mound);

	for (auto it = goalMap.cbegin(); it != goalMap.cend(); ++it) {
		//in workers case the number of current workers has to be added to the goal
		if (it->first.getID() == BWAPI::UnitTypes::Zerg_Drone.getID()) {
			numWorkers += it->second;
			goal.push_back(std::pair<MetaType, int>(it->first, numWorkers ));
		}
		else {
			goal.push_back(std::pair<MetaType, int>(it->first, it->second));
		}

	}

	if (shouldExpandNow())
	{
		goal.push_back(std::pair<MetaType, int>(BWAPI::UnitTypes::Zerg_Hatchery, numCC + 1));
		goal.push_back(std::pair<MetaType, int>(BWAPI::UnitTypes::Zerg_Drone, numWorkers + 10));
	}

	_oldGoal = getBuildingsNeeded(goal, numWorkers);
	return _oldGoal;
}

const MetaPairVector StrategyManager::getZergBuildOrderGoal() const
{
	// the goal to return
	std::vector<MetaPair> goal;
	
    int numWorkers      = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Drone);
    int numCC           = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Hatchery)
                        + UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Lair)
                        + UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Hive);
	int numMutas        = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Mutalisk);
    int numDrones       = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Drone);
    int zerglings       = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Zergling);
	int numHydras       = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Hydralisk);
    int numScourge      = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Scourge);
    int numGuardians    = UnitUtil::GetAllUnitCount(BWAPI::UnitTypes::Zerg_Guardian);

	int mutasWanted = numMutas + 6;
	int hydrasWanted = numHydras + 6;

    if (Config::Strategy::StrategyName == "Zerg_ZerglingRush")
    {
        goal.push_back(std::pair<MetaType, int>(BWAPI::UnitTypes::Zerg_Zergling, zerglings + 6));
    }
    else if (Config::Strategy::StrategyName == "Zerg_2HatchHydra")
    {
        goal.push_back(std::pair<MetaType, int>(BWAPI::UnitTypes::Zerg_Hydralisk, numHydras + 8));
        goal.push_back(std::pair<MetaType, int>(BWAPI::UpgradeTypes::Grooved_Spines, 1));
        goal.push_back(std::pair<MetaType, int>(BWAPI::UnitTypes::Zerg_Drone, numDrones + 4));
    }
    else if (Config::Strategy::StrategyName == "Zerg_3HatchMuta")
    {
        goal.push_back(std::pair<MetaType, int>(BWAPI::UnitTypes::Zerg_Hydralisk, numHydras + 12));
        goal.push_back(std::pair<MetaType, int>(BWAPI::UnitTypes::Zerg_Drone, numDrones + 4));
    }
    else if (Config::Strategy::StrategyName == "Zerg_3HatchScourge")
    {
        if (numScourge > 40)
        {
            goal.push_back(std::pair<MetaType, int>(BWAPI::UnitTypes::Zerg_Hydralisk, numHydras + 12));
        }
        else
        {
            goal.push_back(std::pair<MetaType, int>(BWAPI::UnitTypes::Zerg_Scourge, numScourge + 12));
        }

        
        goal.push_back(std::pair<MetaType, int>(BWAPI::UnitTypes::Zerg_Drone, numDrones + 4));
    }

    if (shouldExpandNow())
    {
        goal.push_back(std::pair<MetaType, int>(BWAPI::UnitTypes::Zerg_Hatchery, numCC + 1));
        goal.push_back(std::pair<MetaType, int>(BWAPI::UnitTypes::Zerg_Drone, numWorkers + 10));
    }

	return goal;
}

void StrategyManager::readResults()
{
    if (!Config::Modules::UsingStrategyIO)
    {
        return;
    }

    std::string enemyName = BWAPI::Broodwar->enemy()->getName();
    std::replace(enemyName.begin(), enemyName.end(), ' ', '_');

    std::string enemyResultsFile = Config::Strategy::ReadDir + enemyName + ".txt";
    
    std::string strategyName;
    int wins = 0;
    int losses = 0;

    FILE *file = fopen ( enemyResultsFile.c_str(), "r" );
    if ( file != nullptr )
    {
        char line [ 4096 ]; /* or other suitable maximum line size */
        while ( fgets ( line, sizeof line, file ) != nullptr ) /* read a line */
        {
            std::stringstream ss(line);

            ss >> strategyName;
            ss >> wins;
            ss >> losses;

            //BWAPI::Broodwar->printf("Results Found: %s %d %d", strategyName.c_str(), wins, losses);

            if (_strategies.find(strategyName) == _strategies.end())
            {
                //BWAPI::Broodwar->printf("Warning: Results file has unknown Strategy: %s", strategyName.c_str());
            }
            else
            {
                _strategies[strategyName]._wins = wins;
                _strategies[strategyName]._losses = losses;
            }
        }

        fclose ( file );
    }
    else
    {
        //BWAPI::Broodwar->printf("No results file found: %s", enemyResultsFile.c_str());
    }
}

void StrategyManager::writeResults()
{
    if (!Config::Modules::UsingStrategyIO)
    {
        return;
    }

    std::string enemyName = BWAPI::Broodwar->enemy()->getName();
    std::replace(enemyName.begin(), enemyName.end(), ' ', '_');

    std::string enemyResultsFile = "D:/Estudo/Tese_Dissertation/Testes/TestResutsTese" + enemyName + ".txt";

    std::stringstream ss;


    ss << _outputResult << "\n";

    Logger::LogOverwriteToFile(enemyResultsFile, ss.str());
}

void StrategyManager::onEnd(const bool isWinner)
{
    if (!Config::Modules::UsingStrategyIO)
    {
        return;
    }

    if (isWinner)
    {
        _strategies[Config::Strategy::StrategyName]._wins++;
    }
    else
    {
        _strategies[Config::Strategy::StrategyName]._losses++;
    }

    writeResults();
}

void StrategyManager::setLearnedStrategy()
{
    // we are currently not using this functionality for the competition so turn it off 
    return;

    if (!Config::Modules::UsingStrategyIO)
    {
        return;
    }

    const std::string & strategyName = Config::Strategy::StrategyName;
    Strategy & currentStrategy = _strategies[strategyName];

    int totalGamesPlayed = 0;
    int strategyGamesPlayed = currentStrategy._wins + currentStrategy._losses;
    double winRate = strategyGamesPlayed > 0 ? currentStrategy._wins / static_cast<double>(strategyGamesPlayed) : 0;

    // if we are using an enemy specific strategy
    if (Config::Strategy::FoundEnemySpecificStrategy)
    {        
        return;
    }

    // if our win rate with the current strategy is super high don't explore at all
    // also we're pretty confident in our base strategies so don't change if insufficient games have been played
    if (strategyGamesPlayed < 5 || (strategyGamesPlayed > 0 && winRate > 0.49))
    {
        BWAPI::Broodwar->printf("Still using default strategy");
        return;
    }

    // get the total number of games played so far with this race
    for (auto & kv : _strategies)
    {
        Strategy & strategy = kv.second;
        if (strategy._race == BWAPI::Broodwar->self()->getRace())
        {
            totalGamesPlayed += strategy._wins + strategy._losses;
        }
    }

    // calculate the UCB value and store the highest
    double C = 0.5;
    std::string bestUCBStrategy;
    double bestUCBStrategyVal = std::numeric_limits<double>::lowest();
    for (auto & kv : _strategies)
    {
        Strategy & strategy = kv.second;
        if (strategy._race != BWAPI::Broodwar->self()->getRace())
        {
            continue;
        }

        int sGamesPlayed = strategy._wins + strategy._losses;
        double sWinRate = sGamesPlayed > 0 ? currentStrategy._wins / static_cast<double>(strategyGamesPlayed) : 0;
        double ucbVal = C * sqrt( log( (double)totalGamesPlayed / sGamesPlayed ) );
        double val = sWinRate + ucbVal;

        if (val > bestUCBStrategyVal)
        {
            bestUCBStrategy = strategy._name;
            bestUCBStrategyVal = val;
        }
    }

    Config::Strategy::StrategyName = bestUCBStrategy;
}