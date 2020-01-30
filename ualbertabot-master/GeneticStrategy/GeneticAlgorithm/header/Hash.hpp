//=================================================================================================
//                    Copyright (C) 2018 Lucas Silva - All Rights Reserved                      
//=================================================================================================

#ifndef MYHASH_H
#define MYHASH_H
#include "BWAPI.h"

namespace galgo {

	class Hash {
	protected:
		std::vector<BWAPI::UnitType> myUnitPopulation;
		std::vector<BWAPI::UnitType> positiveUnits;
		std::map<int, int> myCostMap;
		std::multimap<int, int> counterMap;
		std::multimap<int, int> ownCountersMap;
		std::map<BWAPI::UnitType, int> totalCounterMap;
		int hashSize;
		int maxCost;
	public:
		virtual ~Hash() {};
		const int getHashSize() { return hashSize; };
		const void setHashSize(int size) { hashSize = size; };
		const int getMaxCost() { return maxCost; };
		const std::vector<BWAPI::UnitType> getUnitHash() { return myUnitPopulation; };
		std::vector<BWAPI::UnitType>* getPositiveUnitHash() { return &positiveUnits; };
		const std::multimap<int, int> getCounterHash() { return counterMap; };
		const std::multimap<int, int> getOwnUnitsCounterHash() { return ownCountersMap; };
		const std::map<int, int> getOwnCostHash() { return myCostMap; };
		std::map<BWAPI::UnitType, int>* getTotalCounterMap() { return &totalCounterMap; };
	};
}

#endif
