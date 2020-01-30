//=================================================================================================
//                    Copyright (C) 2017 Olivier Mallet - All Rights Reserved                      
//=================================================================================================

#ifndef GENETICALGORITHM_CPP
#define GENETICALGORITHM_CPP

#include "../header/GeneticAlgorithm.hpp"
#include "../header/Population.hpp"
#include "../header/Evolution.hpp"

namespace galgo {

	Hash* EnemyHash::populationEnemyHash;
	// constructor
	GeneticAlgorithm::GeneticAlgorithm(int popsize, int nbgen, int output)
	{
		this->nbgen = nbgen;
		this->popsize = popsize;
		this->matsize = popsize;
		//this->tntsize = popsize/4;
		this->output = output;
		Selection = RWS;
		// cross-over method initialized to 1-point cross-over                                
		CrossOver = P2XO;
		// mutation method initialized to single-point mutation 
		Mutation = UNM;
	}
	/*-------------------------------------------------------------------------------------------------*/

	void GeneticAlgorithm::init(std::string enemyRace, std::string myRace, std::vector<BWAPI::UnitType> units)
	{
		populationHash = EnemyHash::getPopulationHashInstance(enemyRace, myRace);
		pop = new Population(*this);
		std::map<BWAPI::UnitType, int> *totalCounter = populationHash->getTotalCounterMap();
		std::pair <std::multimap<int, int>::iterator, std::multimap<int, int>::iterator> ret;
		std::multimap<int, int> counterHash = populationHash->getCounterHash();
		std::multimap<int, int> owncounterHash = populationHash->getOwnUnitsCounterHash();
		
		//this->weight = std::min(std::max((float)units.size() / 200.0f, 0.10f), 0.90f); //max unit number is 200
		this->weight = 0.75f; //max unit number is 200
		this->normalize = (float)(200*units.size())/(float)populationHash->getMaxCost(); //200*units.size() is the highest possible counters value
		//initiate counter calculation for each unit possible
		for (int i = 0; i < units.size(); i++) {
			ret = counterHash.equal_range(units[i].getID());
			for (std::multimap<int, int>::iterator it = ret.first; it != ret.second; it++) {
				//it->second = myUnit
				totalCounter->at(it->second) += 1;
			}

			for (std::multimap<int, int>::iterator it = owncounterHash.begin(); it != owncounterHash.end(); it++) {
				if (it->second == units[i].getID()) {
					//it->first = enemyUnit
					totalCounter->at(it->first) -= 1;
				}
			}
		}
		int i = 1; // index 0 already initialized if using null unit
		std::vector<BWAPI::UnitType>* positiveMap = populationHash->getPositiveUnitHash();

		for (std::map<BWAPI::UnitType, int>::iterator it = totalCounter->begin(); it != totalCounter->end(); it++) {
			if (it->second > 2) {
				positiveMap->push_back(it->first);
				i++;
			}
		}
		if (i > 0) populationHash->setHashSize(i);
	}

	/*-------------------------------------------------------------------------------------------------*/

	// run genetic algorithm
	std::map<BWAPI::UnitType, int> GeneticAlgorithm::run(std::string enemyRace, std::string myRace, std::vector<BWAPI::UnitType> units)
	{

		this->init(enemyRace, myRace, units);
		clock_t tStart = clock();

		// initializing population
		if (output > 0) {
			std::cout << "\n Running Genetic Algorithm...\n";
			std::cout << " ----------------------------\n";
		}

		// creating population
		pop->creation();
		// initializing best result and previous best result
		float bestResult = pop->getBestValue();
		float prevBestResult = 0;
		// outputting results 
		if (output > 0) print(tStart, nogen);

		// starting population evolution
		for (nogen = 1; nogen <= nbgen; ++nogen) {
			// evolving population
			pop->evolution();
			this->mutrate -= 0.4f / (float)this->nbgen;
			// getting best current result
			bestResult = pop->getBestValue();
			// outputting results
			if (output > 1) print(tStart, nogen);
			// checking convergence
			if (tolerance != 0.0) {
				if (fabs(bestResult - prevBestResult) < fabs(tolerance)) {
					break;
				}
				prevBestResult = bestResult;
			}
		}

		print(tStart, nogen);
		return getMapResult(result()->param);
	}

	/*-------------------------------------------------------------------------------------------------*/
	const std::shared_ptr<Individual> GeneticAlgorithm::result() const
	{
		return pop->getBestIndividual();
	}

	/*-------------------------------------------------------------------------------------------------*/
	std::map<BWAPI::UnitType, int> GeneticAlgorithm::getMapResult(std::vector<int> param)
	{
		auto positiveHash = this->populationHash->getPositiveUnitHash();
		std::map <BWAPI::UnitType, int> counts;
		for (int i = 0; i < param.size(); ++i)
		{
			BWAPI::UnitType strIndex = positiveHash->at(param[i]);
			if (strIndex != BWAPI::UnitTypes::None.getID()) {
				std::map<BWAPI::UnitType, int>::iterator it(counts.find(strIndex));
				if (it != counts.end()) {
					counts[strIndex]++;
				}
				else {
					counts[strIndex] = 1;
				}
			}
		}
		return counts;
	}

	/*-------------------------------------------------------------------------------------------------*/
	void GeneticAlgorithm::print(clock_t tStart, int nogen) const {
		if (output > 0){
			std::cout << "Best Fitness : " << this->pop->individuals[0]->fitness << std::endl;
			std::cout << "Time taken : " << (double)(clock() - tStart) / CLOCKS_PER_SEC << std::endl;
			std::cout << "Best Fitness : " << this->pop->individuals[0]->fitness << "       Gen #: " << nogen <<std::endl;
			std::cout << "Second Best Fitness : " << this->pop->individuals[1]->fitness << std::endl;
			//counters table
			std::cout << "Counters Table:" << std::endl;
			auto *myMap = this->populationHash->getTotalCounterMap();
			for (auto it = populationHash->getTotalCounterMap()->cbegin(); it != myMap->cend(); ++it) {
				std::cout << it->first << " -> " << it->second << std::endl;
			}

			//Best Individual
			std::cout << "Best Individual:" << std::endl;
			auto bestIndividual = pop->individuals[0]->getParam();
			std::map<BWAPI::UnitType, int> counts;
			for (int i = 0; i < bestIndividual.size(); ++i)
			{
				std::map<BWAPI::UnitType, int>::iterator it(counts.find(this->populationHash->getPositiveUnitHash()->at(bestIndividual[i])));
				if (it != counts.end()) {
					it->second++;
				}
				else {
					counts.insert(std::pair<BWAPI::UnitType, int>(this->populationHash->getPositiveUnitHash()->at(bestIndividual[i]), 1));
				}
			}
			//best individual //count number of occurrences instead of printing the whole individual
			for (auto it = counts.cbegin(); it != counts.cend(); ++it) {
				std::cout << it->first.getName() << " -> " << it->second << std::endl;
			}
			std::cout << "----------------------------------------------------------------------------------------" << std::endl;

		}
	}

	//=================================================================================================

}


#endif
