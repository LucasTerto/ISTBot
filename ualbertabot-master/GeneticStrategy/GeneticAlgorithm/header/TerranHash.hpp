//=================================================================================================
//                    Copyright (C) 2018 Lucas Silva - All Rights Reserved                      
//=================================================================================================

#ifndef TERRANHASH_H
#define TERRANHASH_H

namespace galgo {
	class TerranHash : public Hash {
	public:
		TerranHash(std::string enemyRaceName) {
			hashSize = 15; //with null unit
			//hashSize = 14;
			maxCost = 140000;
			positiveUnits.push_back(BWAPI::UnitTypes::None);
			myUnitPopulation.push_back(BWAPI::UnitTypes::None);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Terran_Marine);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Terran_Firebat);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Terran_Medic);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Terran_Ghost);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Terran_Vulture);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Terran_Goliath);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Terran_Wraith);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Terran_Dropship);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Terran_Science_Vessel);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Terran_Battlecruiser);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Terran_Valkyrie);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Terran_SCV);

			totalCounterMap[BWAPI::UnitTypes::None] = 0;
			totalCounterMap[BWAPI::UnitTypes::Terran_Marine] = 0;
			totalCounterMap[BWAPI::UnitTypes::Terran_Firebat] = 0;
			totalCounterMap[BWAPI::UnitTypes::Terran_Medic] = 0;
			totalCounterMap[BWAPI::UnitTypes::Terran_Ghost] = 0;
			totalCounterMap[BWAPI::UnitTypes::Terran_Vulture] = 0;
			totalCounterMap[BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode] = 0;
			totalCounterMap[BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode] = 0;
			totalCounterMap[BWAPI::UnitTypes::Terran_Goliath] = 0;
			totalCounterMap[BWAPI::UnitTypes::Terran_Wraith] = 0;
			totalCounterMap[BWAPI::UnitTypes::Terran_Dropship] = 0;
			totalCounterMap[BWAPI::UnitTypes::Terran_Science_Vessel] = 0;
			totalCounterMap[BWAPI::UnitTypes::Terran_Battlecruiser] = 0;
			totalCounterMap[BWAPI::UnitTypes::Terran_Valkyrie] = 0;
			totalCounterMap[BWAPI::UnitTypes::Terran_SCV] = 0;

			myCostMap[BWAPI::UnitTypes::None.getID()] = 0;
			myCostMap[BWAPI::UnitTypes::Terran_Marine.getID()] = 50;
			myCostMap[BWAPI::UnitTypes::Terran_Firebat.getID()] = 75;
			myCostMap[BWAPI::UnitTypes::Terran_Medic.getID()] = 75;
			myCostMap[BWAPI::UnitTypes::Terran_Ghost.getID()] = 100;
			myCostMap[BWAPI::UnitTypes::Terran_Vulture.getID()] = 75;
			myCostMap[BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID()] = 300;
			myCostMap[BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID()] = 300;
			myCostMap[BWAPI::UnitTypes::Terran_Goliath.getID()] = 150;
			myCostMap[BWAPI::UnitTypes::Terran_Wraith.getID()] = 250;
			myCostMap[BWAPI::UnitTypes::Terran_Dropship.getID()] = 200;
			myCostMap[BWAPI::UnitTypes::Terran_Science_Vessel.getID()] = 225;
			myCostMap[BWAPI::UnitTypes::Terran_Battlecruiser.getID()] = 700;
			myCostMap[BWAPI::UnitTypes::Terran_Valkyrie.getID()] = 375;
			myCostMap[BWAPI::UnitTypes::Terran_SCV.getID()] = 50;

			if (enemyRaceName.compare("Protoss") == 0) {
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Probe.getID(), BWAPI::UnitTypes::Terran_Vulture.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Zealot.getID(), BWAPI::UnitTypes::Terran_Firebat.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Zealot.getID(), BWAPI::UnitTypes::Terran_Medic.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Zealot.getID(), BWAPI::UnitTypes::Terran_Vulture.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dragoon.getID(), BWAPI::UnitTypes::Terran_Marine.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dragoon.getID(), BWAPI::UnitTypes::Terran_Medic.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dragoon.getID(), BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dragoon.getID(), BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_High_Templar.getID(), BWAPI::UnitTypes::Terran_Science_Vessel.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_High_Templar.getID(), BWAPI::UnitTypes::Terran_Battlecruiser.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_High_Templar.getID(), BWAPI::UnitTypes::Terran_Vulture.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dark_Templar.getID(), BWAPI::UnitTypes::Terran_Science_Vessel.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dark_Templar.getID(), BWAPI::UnitTypes::Terran_Vulture.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Terran_Science_Vessel.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Terran_Vulture.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dark_Archon.getID(), BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dark_Archon.getID(), BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dark_Archon.getID(), BWAPI::UnitTypes::Terran_Battlecruiser.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Reaver.getID(), BWAPI::UnitTypes::Terran_Ghost.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Reaver.getID(), BWAPI::UnitTypes::Terran_Battlecruiser.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Scout.getID(), BWAPI::UnitTypes::Terran_Goliath.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Scout.getID(), BWAPI::UnitTypes::Terran_Valkyrie.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Corsair.getID(), BWAPI::UnitTypes::Terran_Valkyrie.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Corsair.getID(), BWAPI::UnitTypes::Terran_Battlecruiser.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Corsair.getID(), BWAPI::UnitTypes::Terran_Goliath.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Carrier.getID(), BWAPI::UnitTypes::Terran_Ghost.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Carrier.getID(), BWAPI::UnitTypes::Terran_Battlecruiser.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Carrier.getID(), BWAPI::UnitTypes::Terran_Wraith.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Carrier.getID(), BWAPI::UnitTypes::Terran_Goliath.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Arbiter.getID(), BWAPI::UnitTypes::Terran_Science_Vessel.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Arbiter.getID(), BWAPI::UnitTypes::Terran_Goliath.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Shuttle.getID(), BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Shuttle.getID(), BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID()));


				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_SCV.getID(), BWAPI::UnitTypes::Protoss_High_Templar.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_SCV.getID(), BWAPI::UnitTypes::Protoss_Reaver.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Marine.getID(), BWAPI::UnitTypes::Protoss_Zealot.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Marine.getID(), BWAPI::UnitTypes::Protoss_Dragoon.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Marine.getID(), BWAPI::UnitTypes::Protoss_High_Templar.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Marine.getID(), BWAPI::UnitTypes::Protoss_Reaver.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Firebat.getID(), BWAPI::UnitTypes::Protoss_Dragoon.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Firebat.getID(), BWAPI::UnitTypes::Protoss_Dragoon.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Firebat.getID(), BWAPI::UnitTypes::Protoss_High_Templar.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Firebat.getID(), BWAPI::UnitTypes::Protoss_Dark_Templar.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Firebat.getID(), BWAPI::UnitTypes::Protoss_Reaver.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Medic.getID(), BWAPI::UnitTypes::Protoss_Reaver.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Medic.getID(), BWAPI::UnitTypes::Protoss_Dark_Archon.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Ghost.getID(), BWAPI::UnitTypes::Protoss_Zealot.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Vulture.getID(), BWAPI::UnitTypes::Protoss_Dragoon.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Vulture.getID(), BWAPI::UnitTypes::Protoss_Scout.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Vulture.getID(), BWAPI::UnitTypes::Protoss_Carrier.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Vulture.getID(), BWAPI::UnitTypes::Protoss_Arbiter.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Vulture.getID(), BWAPI::UnitTypes::Protoss_Corsair.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID(), BWAPI::UnitTypes::Protoss_Corsair.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID(), BWAPI::UnitTypes::Protoss_Arbiter.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID(), BWAPI::UnitTypes::Protoss_Carrier.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID(), BWAPI::UnitTypes::Protoss_Reaver.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID(), BWAPI::UnitTypes::Protoss_Dark_Templar.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID(), BWAPI::UnitTypes::Protoss_Corsair.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID(), BWAPI::UnitTypes::Protoss_Arbiter.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID(), BWAPI::UnitTypes::Protoss_Carrier.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID(), BWAPI::UnitTypes::Protoss_Reaver.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID(), BWAPI::UnitTypes::Protoss_Dark_Templar.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Goliath.getID(), BWAPI::UnitTypes::Protoss_Dark_Templar.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Goliath.getID(), BWAPI::UnitTypes::Protoss_Reaver.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Goliath.getID(), BWAPI::UnitTypes::Protoss_Zealot.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Goliath.getID(), BWAPI::UnitTypes::Protoss_Dragoon.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Wraith.getID(), BWAPI::UnitTypes::Protoss_Dragoon.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Wraith.getID(), BWAPI::UnitTypes::Protoss_Scout.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Dropship.getID(), BWAPI::UnitTypes::Protoss_Corsair.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Valkyrie.getID(), BWAPI::UnitTypes::Protoss_Dragoon.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Valkyrie.getID(), BWAPI::UnitTypes::Protoss_Arbiter.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Valkyrie.getID(), BWAPI::UnitTypes::Protoss_Scout.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Science_Vessel.getID(), BWAPI::UnitTypes::Protoss_Dark_Archon.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Battlecruiser.getID(), BWAPI::UnitTypes::Protoss_Dark_Archon.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Battlecruiser.getID(), BWAPI::UnitTypes::Protoss_Arbiter.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Battlecruiser.getID(), BWAPI::UnitTypes::Protoss_Dragoon.getID()));
			}
			else if (enemyRaceName.compare("Terran") == 0) {
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_SCV.getID(), BWAPI::UnitTypes::Terran_Wraith.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_SCV.getID(), BWAPI::UnitTypes::Terran_Vulture.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Marine.getID(), BWAPI::UnitTypes::Terran_Marine.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Marine.getID(), BWAPI::UnitTypes::Terran_Medic.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Marine.getID(), BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Marine.getID(), BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Firebat.getID(), BWAPI::UnitTypes::Terran_Goliath.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Firebat.getID(), BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Firebat.getID(), BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Medic.getID(), BWAPI::UnitTypes::Terran_Science_Vessel.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Ghost.getID(), BWAPI::UnitTypes::Terran_Science_Vessel.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Vulture.getID(), BWAPI::UnitTypes::Terran_Wraith.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Vulture.getID(), BWAPI::UnitTypes::Terran_Battlecruiser.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Vulture.getID(), BWAPI::UnitTypes::Terran_Goliath.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID(), BWAPI::UnitTypes::Terran_Ghost.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID(), BWAPI::UnitTypes::Terran_Wraith.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID(), BWAPI::UnitTypes::Terran_Science_Vessel.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID(), BWAPI::UnitTypes::Terran_Battlecruiser.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID(), BWAPI::UnitTypes::Terran_Valkyrie.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID(), BWAPI::UnitTypes::Terran_Ghost.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID(), BWAPI::UnitTypes::Terran_Wraith.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID(), BWAPI::UnitTypes::Terran_Science_Vessel.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID(), BWAPI::UnitTypes::Terran_Battlecruiser.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID(), BWAPI::UnitTypes::Terran_Valkyrie.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Goliath.getID(), BWAPI::UnitTypes::Terran_Marine.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Goliath.getID(), BWAPI::UnitTypes::Terran_Marine.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Goliath.getID(), BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Goliath.getID(), BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Wraith.getID(), BWAPI::UnitTypes::Terran_Valkyrie.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Wraith.getID(), BWAPI::UnitTypes::Terran_Goliath.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Dropship.getID(), BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Dropship.getID(), BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Valkyrie.getID(), BWAPI::UnitTypes::Terran_Battlecruiser.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Valkyrie.getID(), BWAPI::UnitTypes::Terran_Wraith.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Valkyrie.getID(), BWAPI::UnitTypes::Terran_SCV.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Valkyrie.getID(), BWAPI::UnitTypes::Terran_Goliath.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Science_Vessel.getID(), BWAPI::UnitTypes::Terran_Marine.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Science_Vessel.getID(), BWAPI::UnitTypes::Terran_Goliath.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Science_Vessel.getID(), BWAPI::UnitTypes::Terran_Wraith.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Science_Vessel.getID(), BWAPI::UnitTypes::Terran_Ghost.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Science_Vessel.getID(), BWAPI::UnitTypes::Terran_Medic.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Battlecruiser.getID(), BWAPI::UnitTypes::Terran_Goliath.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Battlecruiser.getID(), BWAPI::UnitTypes::Terran_Wraith.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Battlecruiser.getID(), BWAPI::UnitTypes::Terran_Battlecruiser.getID()));

				ownCountersMap = counterMap;
			}
			else {
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Drone.getID(), BWAPI::UnitTypes::Terran_Wraith.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Overlord.getID(), BWAPI::UnitTypes::Terran_Wraith.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Overlord.getID(), BWAPI::UnitTypes::Terran_Goliath.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Overlord.getID(), BWAPI::UnitTypes::Terran_Marine.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Overlord.getID(), BWAPI::UnitTypes::Terran_Valkyrie.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Zergling.getID(), BWAPI::UnitTypes::Terran_Marine.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Zergling.getID(), BWAPI::UnitTypes::Terran_Firebat.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Zergling.getID(), BWAPI::UnitTypes::Terran_Medic.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Zergling.getID(), BWAPI::UnitTypes::Terran_Science_Vessel.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Zergling.getID(), BWAPI::UnitTypes::Terran_Wraith.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Zergling.getID(), BWAPI::UnitTypes::Terran_Battlecruiser.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Zergling.getID(), BWAPI::UnitTypes::Terran_Valkyrie.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Hydralisk.getID(), BWAPI::UnitTypes::Terran_Science_Vessel.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Hydralisk.getID(), BWAPI::UnitTypes::Terran_Marine.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Hydralisk.getID(), BWAPI::UnitTypes::Terran_Medic.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Hydralisk.getID(), BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Hydralisk.getID(), BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Hydralisk.getID(), BWAPI::UnitTypes::Terran_Battlecruiser.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Ultralisk.getID(), BWAPI::UnitTypes::Terran_Science_Vessel.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Ultralisk.getID(), BWAPI::UnitTypes::Terran_Battlecruiser.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Ultralisk.getID(), BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Ultralisk.getID(), BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Ultralisk.getID(), BWAPI::UnitTypes::Terran_Marine.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Ultralisk.getID(), BWAPI::UnitTypes::Terran_Firebat.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Lurker.getID(), BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Lurker.getID(), BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Lurker.getID(), BWAPI::UnitTypes::Terran_Science_Vessel.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Mutalisk.getID(), BWAPI::UnitTypes::Terran_Marine.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Mutalisk.getID(), BWAPI::UnitTypes::Terran_Medic.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Devourer.getID(), BWAPI::UnitTypes::Terran_Marine.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Devourer.getID(), BWAPI::UnitTypes::Terran_Goliath.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Devourer.getID(), BWAPI::UnitTypes::Terran_Battlecruiser.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Guardian.getID(), BWAPI::UnitTypes::Terran_Wraith.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Guardian.getID(), BWAPI::UnitTypes::Terran_Valkyrie.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Guardian.getID(), BWAPI::UnitTypes::Terran_Goliath.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Scourge.getID(), BWAPI::UnitTypes::Terran_Goliath.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Scourge.getID(), BWAPI::UnitTypes::Terran_Wraith.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Scourge.getID(), BWAPI::UnitTypes::Terran_Valkyrie.getID()));

				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_SCV.getID(), BWAPI::UnitTypes::Zerg_Mutalisk.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_SCV.getID(), BWAPI::UnitTypes::Zerg_Lurker.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Marine.getID(), BWAPI::UnitTypes::Zerg_Lurker.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Marine.getID(), BWAPI::UnitTypes::Zerg_Hydralisk.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Marine.getID(), BWAPI::UnitTypes::Zerg_Zergling.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Firebat.getID(), BWAPI::UnitTypes::Zerg_Hydralisk.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Firebat.getID(), BWAPI::UnitTypes::Zerg_Ultralisk.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Firebat.getID(), BWAPI::UnitTypes::Zerg_Lurker.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Firebat.getID(), BWAPI::UnitTypes::Zerg_Mutalisk.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Medic.getID(), BWAPI::UnitTypes::Zerg_Queen.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Medic.getID(), BWAPI::UnitTypes::Zerg_Lurker.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Medic.getID(), BWAPI::UnitTypes::Zerg_Guardian.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Ghost.getID(), BWAPI::UnitTypes::Zerg_Overlord.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Vulture.getID(), BWAPI::UnitTypes::Zerg_Guardian.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Vulture.getID(), BWAPI::UnitTypes::Zerg_Mutalisk.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Vulture.getID(), BWAPI::UnitTypes::Zerg_Lurker.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Vulture.getID(), BWAPI::UnitTypes::Zerg_Hydralisk.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID(), BWAPI::UnitTypes::Zerg_Zergling.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID(), BWAPI::UnitTypes::Zerg_Hydralisk.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID(), BWAPI::UnitTypes::Zerg_Mutalisk.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID(), BWAPI::UnitTypes::Zerg_Lurker.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID(), BWAPI::UnitTypes::Zerg_Zergling.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID(), BWAPI::UnitTypes::Zerg_Hydralisk.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID(), BWAPI::UnitTypes::Zerg_Mutalisk.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID(), BWAPI::UnitTypes::Zerg_Lurker.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Goliath.getID(), BWAPI::UnitTypes::Zerg_Zergling.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Goliath.getID(), BWAPI::UnitTypes::Zerg_Hydralisk.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Goliath.getID(), BWAPI::UnitTypes::Zerg_Mutalisk.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Wraith.getID(), BWAPI::UnitTypes::Zerg_Devourer.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Wraith.getID(), BWAPI::UnitTypes::Zerg_Hydralisk.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Wraith.getID(), BWAPI::UnitTypes::Zerg_Overlord.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Dropship.getID(), BWAPI::UnitTypes::Zerg_Scourge.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Dropship.getID(), BWAPI::UnitTypes::Zerg_Lurker.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Valkyrie.getID(), BWAPI::UnitTypes::Zerg_Scourge.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Valkyrie.getID(), BWAPI::UnitTypes::Zerg_Hydralisk.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Valkyrie.getID(), BWAPI::UnitTypes::Zerg_Devourer.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Science_Vessel.getID(), BWAPI::UnitTypes::Zerg_Scourge.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Battlecruiser.getID(), BWAPI::UnitTypes::Zerg_Hydralisk.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Battlecruiser.getID(), BWAPI::UnitTypes::Zerg_Mutalisk.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Battlecruiser.getID(), BWAPI::UnitTypes::Zerg_Devourer.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Battlecruiser.getID(), BWAPI::UnitTypes::Zerg_Defiler.getID()));
			}
		};
	};
}
#endif
