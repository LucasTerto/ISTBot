//=================================================================================================
//                    Copyright (C) 2018 Lucas Silva - All Rights Reserved                      
//=================================================================================================

#ifndef ENEMYHASH_H
#define ENEMYHASH_H

#include "ProtossHash.hpp"
#include "TerranHash.hpp"
#include "ZergHash.hpp"

namespace galgo {
	
	class EnemyHash {
	private:
		static Hash * populationEnemyHash;

		EnemyHash() {

		}

		EnemyHash(std::string enemyRaceName, std::string myRaceName) {
			if (myRaceName.compare("Protoss") == 0) {
				populationEnemyHash = new ProtossHash(enemyRaceName);
			}
			else if (myRaceName.compare("Terran") == 0) {
				populationEnemyHash = new TerranHash(enemyRaceName);
			}
			else {
				populationEnemyHash = new ZergHash(enemyRaceName);
			}
		}

	public:
		static Hash* getPopulationHashInstance(std::string enemyRaceName, std::string myRaceName) {
			if (populationEnemyHash == NULL) {
				EnemyHash(enemyRaceName, myRaceName);
			}
			return populationEnemyHash;
		}

		/*std::string getCounterHashValue(std::string unitName, bool enemyUnit) {
			std::multimap<std::string, std::string> map = enemyUnit ? populationEnemyHash->getCounterHash() : populationEnemyHash->getOwnUnitsCounterHash();
			return map[unitName].;
		}

		int getUnitCost(std::string unitName, bool enemyUnit) {
			std::multimap<std::string, int> map = enemyUnit ? populationEnemyHash->getCostHash() : populationEnemyHash->getOwnCostHash();
			return map[unitName];
		}*/

		
		/*bool isUnitACounter(std::string enemyUnit, std::string possibleCounter) {
			//no need to verify if the value exists (all units are gonna be here)	
			std::map<std::string, int> map = enemyHash->getEnemyHash();
			return map[myRaceName];
		}*/
	};
}

#endif
