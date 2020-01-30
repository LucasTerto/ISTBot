//=================================================================================================
//                    Copyright (C) 2018 Lucas Silva - All Rights Reserved                      
//=================================================================================================

#ifndef ZERGHASH_H
#define ZERGHASH_H

namespace galgo {
	class ZergHash : public Hash {
	public:
		ZergHash(std::string enemyRaceName) {
			//init population map
			hashSize = 14; //with null unit
			//hashSize = 13;
			maxCost = 120000;
			positiveUnits.push_back(BWAPI::UnitTypes::None);
			myUnitPopulation.push_back(BWAPI::UnitTypes::None);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Zerg_Drone);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Zerg_Zergling);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Zerg_Hydralisk);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Zerg_Lurker);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Zerg_Ultralisk);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Zerg_Defiler);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Zerg_Broodling);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Zerg_Overlord);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Zerg_Mutalisk);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Zerg_Scourge);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Zerg_Queen);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Zerg_Guardian);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Zerg_Devourer);

			totalCounterMap[BWAPI::UnitTypes::None] = 0;
			totalCounterMap[BWAPI::UnitTypes::Zerg_Drone] = 0;
			totalCounterMap[BWAPI::UnitTypes::Zerg_Zergling] = 0;
			totalCounterMap[BWAPI::UnitTypes::Zerg_Hydralisk] = 0;
			totalCounterMap[BWAPI::UnitTypes::Zerg_Lurker] = 0;
			totalCounterMap[BWAPI::UnitTypes::Zerg_Ultralisk] = 0;
			totalCounterMap[BWAPI::UnitTypes::Zerg_Defiler] = 0;
			totalCounterMap[BWAPI::UnitTypes::Zerg_Broodling] = 0;
			totalCounterMap[BWAPI::UnitTypes::Zerg_Overlord] = 0;
			totalCounterMap[BWAPI::UnitTypes::Zerg_Mutalisk] = 0;
			totalCounterMap[BWAPI::UnitTypes::Zerg_Scourge] = 0;
			totalCounterMap[BWAPI::UnitTypes::Zerg_Queen] = 0;
			totalCounterMap[BWAPI::UnitTypes::Zerg_Guardian] = 0;
			totalCounterMap[BWAPI::UnitTypes::Zerg_Devourer] = 0;

			myCostMap[BWAPI::UnitTypes::None.getID()] = 0;
			myCostMap[BWAPI::UnitTypes::Zerg_Drone.getID()] = 50;
			myCostMap[BWAPI::UnitTypes::Zerg_Zergling.getID()] = 100;
			myCostMap[BWAPI::UnitTypes::Zerg_Hydralisk.getID()] = 175;
			myCostMap[BWAPI::UnitTypes::Zerg_Lurker.getID()] = 200;
			myCostMap[BWAPI::UnitTypes::Zerg_Ultralisk.getID()] = 225;
			myCostMap[BWAPI::UnitTypes::Zerg_Defiler.getID()] = 400;
			myCostMap[BWAPI::UnitTypes::Zerg_Broodling.getID()] = 450;
			myCostMap[BWAPI::UnitTypes::Zerg_Overlord.getID()] = 300;
			myCostMap[BWAPI::UnitTypes::Zerg_Mutalisk.getID()] = 400;
			myCostMap[BWAPI::UnitTypes::Zerg_Scourge.getID()] = 250;
			myCostMap[BWAPI::UnitTypes::Zerg_Queen.getID()] = 600;
			myCostMap[BWAPI::UnitTypes::Zerg_Guardian.getID()] = 450;
			myCostMap[BWAPI::UnitTypes::Zerg_Devourer.getID()] = 100;

			if (enemyRaceName.compare("Protoss") == 0) {
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Probe.getID(), BWAPI::UnitTypes::Zerg_Mutalisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Probe.getID(), BWAPI::UnitTypes::Zerg_Zergling.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Probe.getID(), BWAPI::UnitTypes::Zerg_Hydralisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Probe.getID(), BWAPI::UnitTypes::Zerg_Lurker.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Zealot.getID(), BWAPI::UnitTypes::Zerg_Mutalisk.getID()));
				//counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Zealot.getID(), BWAPI::UnitTypes::Zerg_Zergling.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Zealot.getID(), BWAPI::UnitTypes::Zerg_Hydralisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Zealot.getID(), BWAPI::UnitTypes::Zerg_Lurker.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dragoon.getID(), BWAPI::UnitTypes::Zerg_Zergling.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dragoon.getID(), BWAPI::UnitTypes::Zerg_Mutalisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dragoon.getID(), BWAPI::UnitTypes::Zerg_Defiler.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dragoon.getID(), BWAPI::UnitTypes::Zerg_Queen.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_High_Templar.getID(), BWAPI::UnitTypes::Zerg_Queen.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_High_Templar.getID(), BWAPI::UnitTypes::Zerg_Zergling.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_High_Templar.getID(), BWAPI::UnitTypes::Zerg_Ultralisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_High_Templar.getID(), BWAPI::UnitTypes::Zerg_Mutalisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dark_Templar.getID(), BWAPI::UnitTypes::Zerg_Queen.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dark_Templar.getID(), BWAPI::UnitTypes::Zerg_Defiler.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dark_Templar.getID(), BWAPI::UnitTypes::Zerg_Hydralisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dark_Templar.getID(), BWAPI::UnitTypes::Zerg_Mutalisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Zerg_Guardian.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Zerg_Hydralisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dark_Archon.getID(), BWAPI::UnitTypes::Zerg_Mutalisk.getID())); // only works with good micromanagement
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Reaver.getID(), BWAPI::UnitTypes::Zerg_Mutalisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Reaver.getID(), BWAPI::UnitTypes::Zerg_Ultralisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Corsair.getID(), BWAPI::UnitTypes::Zerg_Devourer.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Corsair.getID(), BWAPI::UnitTypes::Zerg_Hydralisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Corsair.getID(), BWAPI::UnitTypes::Zerg_Overlord.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Corsair.getID(), BWAPI::UnitTypes::Zerg_Scourge.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Carrier.getID(), BWAPI::UnitTypes::Zerg_Devourer.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Carrier.getID(), BWAPI::UnitTypes::Zerg_Scourge.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Arbiter.getID(), BWAPI::UnitTypes::Zerg_Scourge.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Arbiter.getID(), BWAPI::UnitTypes::Zerg_Mutalisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Arbiter.getID(), BWAPI::UnitTypes::Zerg_Queen.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Arbiter.getID(), BWAPI::UnitTypes::Zerg_Guardian.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Arbiter.getID(), BWAPI::UnitTypes::Zerg_Devourer.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Arbiter.getID(), BWAPI::UnitTypes::Zerg_Overlord.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Shuttle.getID(), BWAPI::UnitTypes::Zerg_Scourge.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Shuttle.getID(), BWAPI::UnitTypes::Zerg_Lurker.getID()));

				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Drone.getID(), BWAPI::UnitTypes::Protoss_High_Templar.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Drone.getID(), BWAPI::UnitTypes::Protoss_Reaver.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Drone.getID(), BWAPI::UnitTypes::Protoss_Carrier.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Overlord.getID(), BWAPI::UnitTypes::Protoss_Corsair.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Overlord.getID(), BWAPI::UnitTypes::Protoss_Scout.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Overlord.getID(), BWAPI::UnitTypes::Protoss_Dragoon.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Zergling.getID(), BWAPI::UnitTypes::Protoss_Zealot.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Zergling.getID(), BWAPI::UnitTypes::Protoss_High_Templar.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Zergling.getID(), BWAPI::UnitTypes::Protoss_Dark_Templar.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Hydralisk.getID(), BWAPI::UnitTypes::Protoss_Zealot.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Hydralisk.getID(), BWAPI::UnitTypes::Protoss_Reaver.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Hydralisk.getID(), BWAPI::UnitTypes::Protoss_High_Templar.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Hydralisk.getID(), BWAPI::UnitTypes::Protoss_Dark_Templar.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Ultralisk.getID(), BWAPI::UnitTypes::Protoss_Archon.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Ultralisk.getID(), BWAPI::UnitTypes::Protoss_Dark_Archon.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Lurker.getID(), BWAPI::UnitTypes::Protoss_Archon.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Lurker.getID(), BWAPI::UnitTypes::Protoss_Dark_Archon.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Lurker.getID(), BWAPI::UnitTypes::Protoss_Zealot.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Lurker.getID(), BWAPI::UnitTypes::Protoss_High_Templar.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Lurker.getID(), BWAPI::UnitTypes::Protoss_Dragoon.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Mutalisk.getID(), BWAPI::UnitTypes::Protoss_Arbiter.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Mutalisk.getID(), BWAPI::UnitTypes::Protoss_High_Templar.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Mutalisk.getID(), BWAPI::UnitTypes::Protoss_Dark_Templar.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Mutalisk.getID(), BWAPI::UnitTypes::Protoss_Corsair.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Devourer.getID(), BWAPI::UnitTypes::Protoss_Archon.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Devourer.getID(), BWAPI::UnitTypes::Protoss_Dragoon.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Scourge.getID(), BWAPI::UnitTypes::Protoss_Corsair.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Scourge.getID(), BWAPI::UnitTypes::Protoss_Scout.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Scourge.getID(), BWAPI::UnitTypes::Protoss_Dragoon.getID()));
			}
			else if (enemyRaceName.compare("Terran") == 0) {
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_SCV.getID(), BWAPI::UnitTypes::Zerg_Mutalisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_SCV.getID(), BWAPI::UnitTypes::Zerg_Lurker.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Marine.getID(), BWAPI::UnitTypes::Zerg_Lurker.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Marine.getID(), BWAPI::UnitTypes::Zerg_Hydralisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Marine.getID(), BWAPI::UnitTypes::Zerg_Zergling.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Firebat.getID(), BWAPI::UnitTypes::Zerg_Hydralisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Firebat.getID(), BWAPI::UnitTypes::Zerg_Ultralisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Firebat.getID(), BWAPI::UnitTypes::Zerg_Lurker.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Firebat.getID(), BWAPI::UnitTypes::Zerg_Mutalisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Medic.getID(), BWAPI::UnitTypes::Zerg_Queen.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Medic.getID(), BWAPI::UnitTypes::Zerg_Lurker.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Medic.getID(), BWAPI::UnitTypes::Zerg_Guardian.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Ghost.getID(), BWAPI::UnitTypes::Zerg_Overlord.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Vulture.getID(), BWAPI::UnitTypes::Zerg_Guardian.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Vulture.getID(), BWAPI::UnitTypes::Zerg_Mutalisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Vulture.getID(), BWAPI::UnitTypes::Zerg_Lurker.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Vulture.getID(), BWAPI::UnitTypes::Zerg_Hydralisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID(), BWAPI::UnitTypes::Zerg_Zergling.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID(), BWAPI::UnitTypes::Zerg_Hydralisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID(), BWAPI::UnitTypes::Zerg_Mutalisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID(), BWAPI::UnitTypes::Zerg_Lurker.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID(), BWAPI::UnitTypes::Zerg_Zergling.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID(), BWAPI::UnitTypes::Zerg_Hydralisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID(), BWAPI::UnitTypes::Zerg_Mutalisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID(), BWAPI::UnitTypes::Zerg_Lurker.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Goliath.getID(), BWAPI::UnitTypes::Zerg_Zergling.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Goliath.getID(), BWAPI::UnitTypes::Zerg_Hydralisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Goliath.getID(), BWAPI::UnitTypes::Zerg_Mutalisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Wraith.getID(), BWAPI::UnitTypes::Zerg_Devourer.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Wraith.getID(), BWAPI::UnitTypes::Zerg_Hydralisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Wraith.getID(), BWAPI::UnitTypes::Zerg_Overlord.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Dropship.getID(), BWAPI::UnitTypes::Zerg_Scourge.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Dropship.getID(), BWAPI::UnitTypes::Zerg_Lurker.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Valkyrie.getID(), BWAPI::UnitTypes::Zerg_Scourge.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Valkyrie.getID(), BWAPI::UnitTypes::Zerg_Hydralisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Valkyrie.getID(), BWAPI::UnitTypes::Zerg_Devourer.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Science_Vessel.getID(), BWAPI::UnitTypes::Zerg_Scourge.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Battlecruiser.getID(), BWAPI::UnitTypes::Zerg_Hydralisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Battlecruiser.getID(), BWAPI::UnitTypes::Zerg_Mutalisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Battlecruiser.getID(), BWAPI::UnitTypes::Zerg_Devourer.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Battlecruiser.getID(), BWAPI::UnitTypes::Zerg_Defiler.getID()));


				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Drone.getID(), BWAPI::UnitTypes::Terran_Wraith.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Overlord.getID(), BWAPI::UnitTypes::Terran_Wraith.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Overlord.getID(), BWAPI::UnitTypes::Terran_Goliath.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Overlord.getID(), BWAPI::UnitTypes::Terran_Marine.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Overlord.getID(), BWAPI::UnitTypes::Terran_Valkyrie.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Zergling.getID(), BWAPI::UnitTypes::Terran_Marine.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Zergling.getID(), BWAPI::UnitTypes::Terran_Firebat.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Zergling.getID(), BWAPI::UnitTypes::Terran_Medic.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Zergling.getID(), BWAPI::UnitTypes::Terran_Science_Vessel.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Zergling.getID(), BWAPI::UnitTypes::Terran_Wraith.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Zergling.getID(), BWAPI::UnitTypes::Terran_Battlecruiser.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Zergling.getID(), BWAPI::UnitTypes::Terran_Valkyrie.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Hydralisk.getID(), BWAPI::UnitTypes::Terran_Science_Vessel.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Hydralisk.getID(), BWAPI::UnitTypes::Terran_Marine.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Hydralisk.getID(), BWAPI::UnitTypes::Terran_Medic.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Hydralisk.getID(), BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Hydralisk.getID(), BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Hydralisk.getID(), BWAPI::UnitTypes::Terran_Battlecruiser.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Ultralisk.getID(), BWAPI::UnitTypes::Terran_Science_Vessel.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Ultralisk.getID(), BWAPI::UnitTypes::Terran_Battlecruiser.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Ultralisk.getID(), BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Ultralisk.getID(), BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Ultralisk.getID(), BWAPI::UnitTypes::Terran_Marine.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Ultralisk.getID(), BWAPI::UnitTypes::Terran_Firebat.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Lurker.getID(), BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Lurker.getID(), BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Lurker.getID(), BWAPI::UnitTypes::Terran_Science_Vessel.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Mutalisk.getID(), BWAPI::UnitTypes::Terran_Marine.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Mutalisk.getID(), BWAPI::UnitTypes::Terran_Medic.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Devourer.getID(), BWAPI::UnitTypes::Terran_Marine.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Devourer.getID(), BWAPI::UnitTypes::Terran_Goliath.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Devourer.getID(), BWAPI::UnitTypes::Terran_Battlecruiser.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Guardian.getID(), BWAPI::UnitTypes::Terran_Wraith.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Guardian.getID(), BWAPI::UnitTypes::Terran_Valkyrie.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Guardian.getID(), BWAPI::UnitTypes::Terran_Goliath.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Scourge.getID(), BWAPI::UnitTypes::Terran_Goliath.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Scourge.getID(), BWAPI::UnitTypes::Terran_Wraith.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Scourge.getID(), BWAPI::UnitTypes::Terran_Valkyrie.getID()));
			}
			else {
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Drone.getID(), BWAPI::UnitTypes::Zerg_Mutalisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Drone.getID(), BWAPI::UnitTypes::Zerg_Queen.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Overlord.getID(), BWAPI::UnitTypes::Zerg_Mutalisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Overlord.getID(), BWAPI::UnitTypes::Zerg_Hydralisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Overlord.getID(), BWAPI::UnitTypes::Zerg_Scourge.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Zergling.getID(), BWAPI::UnitTypes::Zerg_Zergling.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Zergling.getID(), BWAPI::UnitTypes::Zerg_Hydralisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Zergling.getID(), BWAPI::UnitTypes::Zerg_Lurker.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Zergling.getID(), BWAPI::UnitTypes::Zerg_Mutalisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Zergling.getID(), BWAPI::UnitTypes::Zerg_Guardian.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Hydralisk.getID(), BWAPI::UnitTypes::Zerg_Zergling.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Hydralisk.getID(), BWAPI::UnitTypes::Zerg_Lurker.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Hydralisk.getID(), BWAPI::UnitTypes::Zerg_Guardian.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Ultralisk.getID(), BWAPI::UnitTypes::Zerg_Defiler.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Ultralisk.getID(), BWAPI::UnitTypes::Zerg_Queen.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Ultralisk.getID(), BWAPI::UnitTypes::Zerg_Zergling.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Lurker.getID(), BWAPI::UnitTypes::Zerg_Hydralisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Lurker.getID(), BWAPI::UnitTypes::Zerg_Overlord.getID()));

				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Defiler.getID(), BWAPI::UnitTypes::Zerg_Defiler.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Broodling.getID(), BWAPI::UnitTypes::Zerg_Broodling.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Mutalisk.getID(), BWAPI::UnitTypes::Zerg_Defiler.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Mutalisk.getID(), BWAPI::UnitTypes::Zerg_Hydralisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Scourge.getID(), BWAPI::UnitTypes::Zerg_Scourge.getID()));
				//counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Scourge.getID(), "Zerg_Mutalisk + Zerg_Guardian"));//combination of units, see how!!
				//counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Scourge.getID(), "Zerg_Hydralisk + Zerg_Devourer"));//combination of units, see how!!
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Queen.getID(), BWAPI::UnitTypes::Zerg_Queen.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Queen.getID(), BWAPI::UnitTypes::Zerg_Zergling.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Queen.getID(), BWAPI::UnitTypes::Zerg_Drone.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Guardian.getID(), BWAPI::UnitTypes::Zerg_Hydralisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Guardian.getID(), BWAPI::UnitTypes::Zerg_Defiler.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Devourer.getID(), BWAPI::UnitTypes::Zerg_Hydralisk.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Devourer.getID(), BWAPI::UnitTypes::Zerg_Scourge.getID()));

				ownCountersMap = counterMap;
			}
		};
	};
}
#endif
