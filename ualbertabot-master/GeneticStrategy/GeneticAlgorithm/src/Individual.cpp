//=================================================================================================
//                    Copyright (C) 2017 Olivier Mallet - All Rights Reserved                      
//=================================================================================================

#ifndef INDIVIDUAL_CPP
#define INDIVIDUAL_CPP

#include "../header/Individual.hpp"
#include <bitset>
#include "../header/GeneticAlgorithm.hpp"

namespace galgo {
	/*-------------------------------------------------------------------------------------------------*/

	// constructor
	Individual::Individual(GeneticAlgorithm& ga)
	{
		param.resize(ga.nbparam);
		ptr = &ga;
		numgen = ga.nogen;
		maxRand = ga.populationHash->getHashSize();
	}

	/*-------------------------------------------------------------------------------------------------*/

	// copy constructor
	Individual::Individual(Individual& rhs)
	{
		param = rhs.param;
		ptr = rhs.ptr;
		// re-initializing fitness to its original value
		fitness = rhs.fitness;
		numgen = rhs.numgen;
		maxRand = rhs.maxRand;
	}

	/*-------------------------------------------------------------------------------------------------*/

	// create new chromosome
	void Individual::create()
	{
		param.clear();
		int unitNumber = 0;
		//ptr->populationHash->myUnitPopulationSize;//modulo defenido por este valor
	 //percorrer ciclo ate numero maximo de unidades (200)
	 //criar radom numbered unit
		for (int i = 0; i < maxUnitNumber; i++) {
			unitNumber = rand() % (int)((1 - ptr->weight)*maxRand + maxRand);
			param.push_back(unitNumber >= maxRand ? 0 : unitNumber);
			//unitNumber = rand() % (maxRand);
			//param.push_back(unitNumber);

		}
	}

	void Individual::initialize()
	{
		if (param.size() <= 0) {
			this->create();
		}
	}

	/*-------------------------------------------------------------------------------------------------*/

	//checks cost and counters to return individual fitness
	int Individual::Objective(Individual* individual)
	{
		float costValue = 0;
		float counterValue = 0;
		Hash * popHash = individual->ptr->populationHash;
		std::vector<BWAPI::UnitType> *myPop = popHash->getPositiveUnitHash();
		std::map<int, int> myCostMap = popHash->getOwnCostHash();
		std::map<BWAPI::UnitType, int>* totalCounterMap = popHash->getTotalCounterMap();
		BWAPI::UnitType unitID;
		//this value will be gotten from the bot, using BWAPI
		//change values to test
		int unitCounter = 0;
		for (int i = 0; i < individual->param.size(); i++) {
			int unitIndex = individual->param[i];
			if (unitIndex > 0) {
				unitID = myPop->at(unitIndex).getID();
				costValue += myCostMap.find(unitID.getID())->second;
				counterValue += totalCounterMap->find(unitID)->second;
				
			}
		}
		counterValue = counterValue * this->ptr->weight;
		costValue = (this->ptr->populationHash->getMaxCost() - costValue) * (1 - this->ptr->weight) * this->ptr->normalize;
		//return (float)totalCounter* this->ptr->weight * totalCost* (1 - this->ptr->weight) * this->ptr->normalize;
		return counterValue + costValue;
	}

	/*-------------------------------------------------------------------------------------------------*/
	// evaluate chromosome fitness
	void Individual::evaluate()
	{
		fitness = Objective(this);
	}

	/*-------------------------------------------------------------------------------------------------*/

	// reset chromosome
	void Individual::reset()
	{
		param.clear();
		//total = 0.0;
		fitness = 0.0;
	}

	/*-------------------------------------------------------------------------------------------------*/

	// set or replace kth gene by a new one
	void Individual::setGene(int k)
	{
#ifndef NDEBUG
		if (k < 0 || k >= ptr->nbparam) {
			throw std::invalid_argument("Error: in galgo::Individual<T>::setGene(int), argument cannot be outside interval [0,nbparam-1], please amend.");
		}
#endif


		param[k] = rand() % maxRand;
	}

	/*-------------------------------------------------------------------------------------------------*/

	// initialize or replace kth gene by a know value
	void Individual::initGene(int k, int x)
	{
#ifndef NDEBUG
		if (k < 0 || k >= ptr->nbparam) {
			throw std::invalid_argument("Error: in galgo::Individual<T>::initGene(int), first argument cannot be outside interval [0,nbparam-1], please amend.");
		}
#endif

		param[k] = x;
	}

	/*-------------------------------------------------------------------------------------------------*/

	// get parameter value(s) from chromosome
	std::vector<int>& Individual::getParam()
	{
		return param;
	}

	/*-------------------------------------------------------------------------------------------------*/

	// return chromosome size in number of bits
	int Individual::size()
	{
		return param.size();
	}

	/*-------------------------------------------------------------------------------------------------*/

	// return mutation rate
	int Individual::mutrate()
	{
		return ptr->mutrate;
	}

	/*-------------------------------------------------------------------------------------------------*/

	// return number of genes in chromosome
	int Individual::nbgene()
	{
		return ptr->nbparam;
	}

	/*-------------------------------------------------------------------------------------------------*/

	// return numero of generation this chromosome belongs to
	int Individual::nogen()
	{
		return numgen;
	}

	// initialize or replace a portion of bits with a portion of another chromosome (from position start to position end included)
	void Individual::setPortion(Individual& x, int start, int end)
	{
#ifndef NDEBUG
		if (start > param.size()) {
			throw std::out_of_range("Error: in galgo::Chromosome<T>::setPortion(const Chromosome<T>&, int, int), second argument cannot be greater than chromosome size.");
		}
#endif

		//param.replace(start, end - start + 1, x.chr, start, end - start + 1);
		std::copy_n(param.begin() + start, end - start, x.param.begin() + start);
	}

	void Individual::flipBit(int pos) {
		int itoFlip = floor(pos / 4);
		int bittoFlip = pos % 4;
		int ntoFlip = param[itoFlip];
		std::bitset<4> binary = std::bitset< 4 >(ntoFlip).flip(bittoFlip); // string conversion
		int mutated = (int)(binary.to_ullong());
		param[itoFlip] = mutated < ptr->populationHash->getHashSize() ? mutated : ptr->populationHash->getHashSize() - 1;
	}
}
#endif