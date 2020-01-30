#pragma once

#include "Common.h"
#include "BWTA.h"
#include "BuildOrderQueue.h"
#include "InformationManager.h"
#include "WorkerManager.h"
#include "BuildOrder.h"
#include <iostream>
#include <fstream>
#include "D:\Estudo\Tese_Dissertation\ualbertabot-master\GeneticStrategy\GeneticAlgorithm\header\GeneticAlgorithm.hpp"

namespace UAlbertaBot
{
typedef std::pair<MetaType, size_t> MetaPair;
typedef std::vector<MetaPair> MetaPairVector;

struct Strategy
{
    std::string _name;
    BWAPI::Race _race;
    int         _wins;
    int         _losses;
    BuildOrder  _buildOrder;

    Strategy()
        : _name("None")
        , _race(BWAPI::Races::None)
        , _wins(0)
        , _losses(0)
    {
    
    }

    Strategy(const std::string & name, const BWAPI::Race & race, const BuildOrder & buildOrder)
        : _name(name)
        , _race(race)
        , _wins(0)
        , _losses(0)
        , _buildOrder(buildOrder)
    {
    
    }
};

class StrategyManager 
{
	StrategyManager();

	BWAPI::Race							_selfRace;
	BWAPI::Race							_enemyRace;
    std::map<std::string, Strategy>		_strategies;
    int									_totalGamesPlayed;
    const BuildOrder					_emptyBuildOrder;
	galgo::GeneticAlgorithm				_ga;
	std::vector<BWAPI::UnitType>		_enemyUnitsVector;
	MetaPairVector						_oldGoal;
	std::string							_outputResult;

	        void						writeResults();
	const	int							getScore(BWAPI::Player player) const;
	const	double						getUCBValue(const size_t & strategy) const;
	const	bool						shouldExpandNow() const;
			bool						hasEnemyUnitsChanged(std::vector<BWAPI::UnitType> unitsVector);
			MetaPairVector				getBuildingsNeeded(MetaPairVector goalVector, int numWorkers);
    const	MetaPairVector				getProtossBuildOrderGoal() const;
	const	MetaPairVector				getTerranBuildOrderGoal() const;
	const	MetaPairVector				getZergBuildOrderGoal() const;
			MetaPairVector				getProtossGABuildOrderGoal(std::map<BWAPI::UnitType, int> goalMap);
			MetaPairVector				getTerranGABuildOrderGoal(std::map<BWAPI::UnitType, int> goalMap);
			MetaPairVector				getZergGABuildOrderGoal(std::map<BWAPI::UnitType, int> goalMap);

public:
    
	static	StrategyManager &			Instance();
	std::string			getTimeString(std::string time);
	std::string getBuildOrderString(std::map<BWAPI::UnitType, int> goalMap);
	void								writeEnemyUnits(std::vector<BWAPI::UnitType> _enemyUnitsVector);
			void						writeToFile(std::string string);
			void						onEnd(const bool isWinner);
            void						addStrategy(const std::string & name, Strategy & strategy);
			std::map<BWAPI::UnitType, int>	getNewBuildOrderGoal();
            void						setLearnedStrategy();
            void						readResults();
	const	bool						regroup(int numInRadius);
	const	bool						rushDetected();
	const	int							defendWithWorkers();
	const	MetaPairVector				getBuildOrderGoal();
	const	BuildOrder &				getOpeningBookBuildOrder() const;
};
}