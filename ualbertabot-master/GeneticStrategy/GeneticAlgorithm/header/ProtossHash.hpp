//=================================================================================================
//                    Copyright (C) 2018 Lucas Silva - All Rights Reserved                      
//=================================================================================================

#ifndef PROTOSSHASH_H
#define PROTOSSHASH_H

namespace galgo {
	class ProtossHash : public Hash{
	public:
		ProtossHash(std::string enemyRaceName) {
			hashSize = 15;
			//hashSize = 14;
			maxCost = 120000;
			positiveUnits.push_back(BWAPI::UnitTypes::None);
			myUnitPopulation.push_back(BWAPI::UnitTypes::None);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Protoss_Zealot);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Protoss_Dragoon);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Protoss_High_Templar);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Protoss_Dark_Templar);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Protoss_Reaver);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Protoss_Archon);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Protoss_Dark_Archon);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Protoss_Observer);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Protoss_Shuttle);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Protoss_Scout);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Protoss_Carrier);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Protoss_Arbiter);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Protoss_Corsair);
			myUnitPopulation.push_back(BWAPI::UnitTypes::Protoss_Probe);

			totalCounterMap[BWAPI::UnitTypes::None] = 0;
			totalCounterMap[BWAPI::UnitTypes::Protoss_Probe] = 0;
			totalCounterMap[BWAPI::UnitTypes::Protoss_Zealot] = 0;
			totalCounterMap[BWAPI::UnitTypes::Protoss_Dragoon] = 0;
			totalCounterMap[BWAPI::UnitTypes::Protoss_High_Templar] = 0;
			totalCounterMap[BWAPI::UnitTypes::Protoss_Dark_Templar] = 0;
			totalCounterMap[BWAPI::UnitTypes::Protoss_Archon] = 0;
			totalCounterMap[BWAPI::UnitTypes::Protoss_Dark_Archon] = 0;
			totalCounterMap[BWAPI::UnitTypes::Protoss_Reaver] = 0;
			totalCounterMap[BWAPI::UnitTypes::Protoss_Scout] = 0;
			totalCounterMap[BWAPI::UnitTypes::Protoss_Corsair] = 0;
			totalCounterMap[BWAPI::UnitTypes::Protoss_Carrier] = 0;
			totalCounterMap[BWAPI::UnitTypes::Protoss_Arbiter] = 0;
			totalCounterMap[BWAPI::UnitTypes::Protoss_Observer] = 0;
			totalCounterMap[BWAPI::UnitTypes::Protoss_Shuttle] = 0;


			myCostMap[BWAPI::UnitTypes::None.getID()] = 0;
			myCostMap[BWAPI::UnitTypes::Protoss_Probe.getID()] = 50;
			myCostMap[BWAPI::UnitTypes::Protoss_Zealot.getID()] = 100;
			myCostMap[BWAPI::UnitTypes::Protoss_Dragoon.getID()] = 175;
			myCostMap[BWAPI::UnitTypes::Protoss_High_Templar.getID()] = 200;
			myCostMap[BWAPI::UnitTypes::Protoss_Dark_Templar.getID()] = 225;
			myCostMap[BWAPI::UnitTypes::Protoss_Archon.getID()] = 400;
			myCostMap[BWAPI::UnitTypes::Protoss_Dark_Archon.getID()] = 450;
			myCostMap[BWAPI::UnitTypes::Protoss_Reaver.getID()] = 300;
			myCostMap[BWAPI::UnitTypes::Protoss_Scout.getID()] = 400;
			myCostMap[BWAPI::UnitTypes::Protoss_Corsair.getID()] = 250;
			myCostMap[BWAPI::UnitTypes::Protoss_Carrier.getID()] = 600;
			myCostMap[BWAPI::UnitTypes::Protoss_Arbiter.getID()] = 450;
			myCostMap[BWAPI::UnitTypes::Protoss_Observer.getID()] = 100;
			myCostMap[BWAPI::UnitTypes::Protoss_Shuttle.getID()] = 200;

			if (enemyRaceName.compare("Protoss") == 0) {
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Probe.getID(), BWAPI::UnitTypes::Protoss_Probe.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Zealot.getID(), BWAPI::UnitTypes::Protoss_Zealot.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Zealot.getID(), BWAPI::UnitTypes::Protoss_Reaver.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Zealot.getID(), BWAPI::UnitTypes::Protoss_Scout.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Zealot.getID(), BWAPI::UnitTypes::Protoss_Carrier.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Zealot.getID(), BWAPI::UnitTypes::Protoss_Dark_Templar.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dragoon.getID(), BWAPI::UnitTypes::Protoss_Zealot.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dragoon.getID(), BWAPI::UnitTypes::Protoss_High_Templar.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dragoon.getID(), BWAPI::UnitTypes::Protoss_Reaver.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_High_Templar.getID(), BWAPI::UnitTypes::Protoss_Reaver.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_High_Templar.getID(), BWAPI::UnitTypes::Protoss_Dark_Templar.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_High_Templar.getID(), BWAPI::UnitTypes::Protoss_Dark_Archon.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dark_Templar.getID(), BWAPI::UnitTypes::Protoss_Observer.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Protoss_Reaver.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Protoss_Dark_Archon.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dark_Archon.getID(), BWAPI::UnitTypes::Protoss_Reaver.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dark_Archon.getID(), BWAPI::UnitTypes::Protoss_Dark_Archon.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Reaver.getID(), BWAPI::UnitTypes::Protoss_Dark_Templar.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Reaver.getID(), BWAPI::UnitTypes::Protoss_High_Templar.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Reaver.getID(), BWAPI::UnitTypes::Protoss_Scout.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Reaver.getID(), BWAPI::UnitTypes::Protoss_Carrier.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Scout.getID(), BWAPI::UnitTypes::Protoss_Dragoon.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Scout.getID(), BWAPI::UnitTypes::Protoss_Corsair.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Scout.getID(), BWAPI::UnitTypes::Protoss_Carrier.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Corsair.getID(), BWAPI::UnitTypes::Protoss_Corsair.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Corsair.getID(), BWAPI::UnitTypes::Protoss_Dark_Archon.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Carrier.getID(), BWAPI::UnitTypes::Protoss_Corsair.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Carrier.getID(), BWAPI::UnitTypes::Protoss_High_Templar.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Carrier.getID(), BWAPI::UnitTypes::Protoss_Dragoon.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Arbiter.getID(), BWAPI::UnitTypes::Protoss_Observer.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Arbiter.getID(), BWAPI::UnitTypes::Protoss_Dark_Archon.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Arbiter.getID(), BWAPI::UnitTypes::Protoss_High_Templar.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Shuttle.getID(), BWAPI::UnitTypes::Protoss_Corsair.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Observer.getID(), BWAPI::UnitTypes::Protoss_Dark_Archon.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Observer.getID(), BWAPI::UnitTypes::Protoss_Dragoon.getID()));

				ownCountersMap = counterMap;
			}
			else if (enemyRaceName.compare("Terran") == 0) {
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_SCV.getID(), BWAPI::UnitTypes::Protoss_High_Templar.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_SCV.getID(), BWAPI::UnitTypes::Protoss_Reaver.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Marine.getID(), BWAPI::UnitTypes::Protoss_Zealot.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Marine.getID(), BWAPI::UnitTypes::Protoss_Dragoon.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Marine.getID(), BWAPI::UnitTypes::Protoss_High_Templar.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Marine.getID(), BWAPI::UnitTypes::Protoss_Reaver.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Firebat.getID(), BWAPI::UnitTypes::Protoss_Dragoon.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Firebat.getID(), BWAPI::UnitTypes::Protoss_Dragoon.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Firebat.getID(), BWAPI::UnitTypes::Protoss_High_Templar.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Firebat.getID(), BWAPI::UnitTypes::Protoss_Dark_Templar.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Firebat.getID(), BWAPI::UnitTypes::Protoss_Reaver.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Medic.getID(), BWAPI::UnitTypes::Protoss_Reaver.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Medic.getID(), BWAPI::UnitTypes::Protoss_Dark_Archon.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Ghost.getID(), BWAPI::UnitTypes::Protoss_Zealot.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Vulture.getID(), BWAPI::UnitTypes::Protoss_Dragoon.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Vulture.getID(), BWAPI::UnitTypes::Protoss_Scout.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Vulture.getID(), BWAPI::UnitTypes::Protoss_Carrier.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Vulture.getID(), BWAPI::UnitTypes::Protoss_Arbiter.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Vulture.getID(), BWAPI::UnitTypes::Protoss_Corsair.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Vulture.getID(), BWAPI::UnitTypes::Protoss_Observer.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID(), BWAPI::UnitTypes::Protoss_Corsair.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID(), BWAPI::UnitTypes::Protoss_Arbiter.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID(), BWAPI::UnitTypes::Protoss_Carrier.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID(), BWAPI::UnitTypes::Protoss_Reaver.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID(), BWAPI::UnitTypes::Protoss_Dark_Templar.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID(), BWAPI::UnitTypes::Protoss_Corsair.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID(), BWAPI::UnitTypes::Protoss_Arbiter.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID(), BWAPI::UnitTypes::Protoss_Carrier.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID(), BWAPI::UnitTypes::Protoss_Reaver.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID(), BWAPI::UnitTypes::Protoss_Dark_Templar.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Goliath.getID(), BWAPI::UnitTypes::Protoss_Dark_Templar.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Goliath.getID(), BWAPI::UnitTypes::Protoss_Reaver.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Goliath.getID(), BWAPI::UnitTypes::Protoss_Zealot.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Goliath.getID(), BWAPI::UnitTypes::Protoss_Dragoon.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Wraith.getID(), BWAPI::UnitTypes::Protoss_Dragoon.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Wraith.getID(), BWAPI::UnitTypes::Protoss_Scout.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Dropship.getID(), BWAPI::UnitTypes::Protoss_Corsair.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Valkyrie.getID(), BWAPI::UnitTypes::Protoss_Dragoon.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Valkyrie.getID(), BWAPI::UnitTypes::Protoss_Arbiter.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Valkyrie.getID(), BWAPI::UnitTypes::Protoss_Scout.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Science_Vessel.getID(), BWAPI::UnitTypes::Protoss_Dark_Archon.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Battlecruiser.getID(), BWAPI::UnitTypes::Protoss_Dark_Archon.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Battlecruiser.getID(), BWAPI::UnitTypes::Protoss_Arbiter.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Terran_Battlecruiser.getID(), BWAPI::UnitTypes::Protoss_Dragoon.getID()));

				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Probe.getID(), BWAPI::UnitTypes::Terran_Vulture.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Zealot.getID(), BWAPI::UnitTypes::Terran_Firebat.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Zealot.getID(), BWAPI::UnitTypes::Terran_Medic.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Zealot.getID(), BWAPI::UnitTypes::Terran_Vulture.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dragoon.getID(), BWAPI::UnitTypes::Terran_Marine.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dragoon.getID(), BWAPI::UnitTypes::Terran_Medic.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dragoon.getID(), BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dragoon.getID(), BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_High_Templar.getID(), BWAPI::UnitTypes::Terran_Science_Vessel.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_High_Templar.getID(), BWAPI::UnitTypes::Terran_Battlecruiser.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_High_Templar.getID(), BWAPI::UnitTypes::Terran_Vulture.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dark_Templar.getID(), BWAPI::UnitTypes::Terran_Science_Vessel.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dark_Templar.getID(), BWAPI::UnitTypes::Terran_Vulture.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Terran_Science_Vessel.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Terran_Vulture.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dark_Archon.getID(), BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dark_Archon.getID(), BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dark_Archon.getID(), BWAPI::UnitTypes::Terran_Battlecruiser.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Reaver.getID(), BWAPI::UnitTypes::Terran_Ghost.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Reaver.getID(), BWAPI::UnitTypes::Terran_Battlecruiser.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Scout.getID(), BWAPI::UnitTypes::Terran_Goliath.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Scout.getID(), BWAPI::UnitTypes::Terran_Valkyrie.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Corsair.getID(), BWAPI::UnitTypes::Terran_Valkyrie.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Corsair.getID(), BWAPI::UnitTypes::Terran_Battlecruiser.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Corsair.getID(), BWAPI::UnitTypes::Terran_Goliath.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Carrier.getID(), BWAPI::UnitTypes::Terran_Ghost.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Carrier.getID(), BWAPI::UnitTypes::Terran_Battlecruiser.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Carrier.getID(), BWAPI::UnitTypes::Terran_Wraith.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Carrier.getID(), BWAPI::UnitTypes::Terran_Goliath.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Arbiter.getID(), BWAPI::UnitTypes::Terran_Science_Vessel.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Arbiter.getID(), BWAPI::UnitTypes::Terran_Goliath.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Shuttle.getID(), BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Observer.getID(), BWAPI::UnitTypes::Terran_Siege_Tank_Siege_Mode.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Shuttle.getID(), BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Observer.getID(), BWAPI::UnitTypes::Terran_Siege_Tank_Tank_Mode.getID()));
			}
			else {
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Drone.getID(), BWAPI::UnitTypes::Protoss_High_Templar.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Drone.getID(), BWAPI::UnitTypes::Protoss_Reaver.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Drone.getID(), BWAPI::UnitTypes::Protoss_Carrier.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Overlord.getID(), BWAPI::UnitTypes::Protoss_Corsair.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Overlord.getID(), BWAPI::UnitTypes::Protoss_Scout.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Overlord.getID(), BWAPI::UnitTypes::Protoss_Dragoon.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Zergling.getID(), BWAPI::UnitTypes::Protoss_Zealot.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Zergling.getID(), BWAPI::UnitTypes::Protoss_High_Templar.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Zergling.getID(), BWAPI::UnitTypes::Protoss_Dark_Templar.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Hydralisk.getID(), BWAPI::UnitTypes::Protoss_Zealot.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Hydralisk.getID(), BWAPI::UnitTypes::Protoss_Reaver.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Hydralisk.getID(), BWAPI::UnitTypes::Protoss_High_Templar.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Hydralisk.getID(), BWAPI::UnitTypes::Protoss_Dark_Templar.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Ultralisk.getID(), BWAPI::UnitTypes::Protoss_Archon.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Ultralisk.getID(), BWAPI::UnitTypes::Protoss_Dark_Archon.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Lurker.getID(), BWAPI::UnitTypes::Protoss_Archon.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Lurker.getID(), BWAPI::UnitTypes::Protoss_Dark_Archon.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Lurker.getID(), BWAPI::UnitTypes::Protoss_Zealot.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Lurker.getID(), BWAPI::UnitTypes::Protoss_High_Templar.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Lurker.getID(), BWAPI::UnitTypes::Protoss_Dragoon.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Mutalisk.getID(), BWAPI::UnitTypes::Protoss_Arbiter.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Mutalisk.getID(), BWAPI::UnitTypes::Protoss_High_Templar.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Mutalisk.getID(), BWAPI::UnitTypes::Protoss_Dark_Templar.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Mutalisk.getID(), BWAPI::UnitTypes::Protoss_Corsair.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Devourer.getID(), BWAPI::UnitTypes::Protoss_Archon.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Devourer.getID(), BWAPI::UnitTypes::Protoss_Dragoon.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Scourge.getID(), BWAPI::UnitTypes::Protoss_Corsair.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Scourge.getID(), BWAPI::UnitTypes::Protoss_Scout.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Scourge.getID(), BWAPI::UnitTypes::Protoss_Dragoon.getID()));
				counterMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Zerg_Lurker.getID(), BWAPI::UnitTypes::Protoss_Observer.getID()));

				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Zealot.getID(), BWAPI::UnitTypes::Zerg_Mutalisk.getID()));
				//ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Zealot.getID(), BWAPI::UnitTypes::Zerg_Zergling.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Zealot.getID(), BWAPI::UnitTypes::Zerg_Hydralisk.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Zealot.getID(), BWAPI::UnitTypes::Zerg_Lurker.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dragoon.getID(), BWAPI::UnitTypes::Zerg_Zergling.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dragoon.getID(), BWAPI::UnitTypes::Zerg_Mutalisk.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dragoon.getID(), BWAPI::UnitTypes::Zerg_Defiler.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dragoon.getID(), BWAPI::UnitTypes::Zerg_Queen.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_High_Templar.getID(), BWAPI::UnitTypes::Zerg_Queen.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_High_Templar.getID(), BWAPI::UnitTypes::Zerg_Zergling.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_High_Templar.getID(), BWAPI::UnitTypes::Zerg_Ultralisk.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_High_Templar.getID(), BWAPI::UnitTypes::Zerg_Mutalisk.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dark_Templar.getID(), BWAPI::UnitTypes::Zerg_Queen.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dark_Templar.getID(), BWAPI::UnitTypes::Zerg_Defiler.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dark_Templar.getID(), BWAPI::UnitTypes::Zerg_Hydralisk.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dark_Templar.getID(), BWAPI::UnitTypes::Zerg_Mutalisk.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Zerg_Guardian.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Archon.getID(), BWAPI::UnitTypes::Zerg_Hydralisk.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Dark_Archon.getID(), BWAPI::UnitTypes::Zerg_Mutalisk.getID())); // only works with good micromanagement
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Reaver.getID(), BWAPI::UnitTypes::Zerg_Mutalisk.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Reaver.getID(), BWAPI::UnitTypes::Zerg_Ultralisk.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Corsair.getID(), BWAPI::UnitTypes::Zerg_Devourer.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Corsair.getID(), BWAPI::UnitTypes::Zerg_Hydralisk.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Corsair.getID(), BWAPI::UnitTypes::Zerg_Overlord.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Corsair.getID(), BWAPI::UnitTypes::Zerg_Scourge.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Carrier.getID(), BWAPI::UnitTypes::Zerg_Devourer.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Carrier.getID(), BWAPI::UnitTypes::Zerg_Scourge.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Arbiter.getID(), BWAPI::UnitTypes::Zerg_Scourge.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Arbiter.getID(), BWAPI::UnitTypes::Zerg_Mutalisk.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Arbiter.getID(), BWAPI::UnitTypes::Zerg_Queen.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Arbiter.getID(), BWAPI::UnitTypes::Zerg_Guardian.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Arbiter.getID(), BWAPI::UnitTypes::Zerg_Devourer.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Arbiter.getID(), BWAPI::UnitTypes::Zerg_Overlord.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Shuttle.getID(), BWAPI::UnitTypes::Zerg_Scourge.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Shuttle.getID(), BWAPI::UnitTypes::Zerg_Lurker.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Observer.getID(), BWAPI::UnitTypes::Zerg_Scourge.getID()));
				ownCountersMap.insert(std::pair<int, int>(BWAPI::UnitTypes::Protoss_Observer.getID(), BWAPI::UnitTypes::Zerg_Hydralisk.getID()));
			}
		};
	};
}

#endif
