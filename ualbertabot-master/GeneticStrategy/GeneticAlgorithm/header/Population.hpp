//=================================================================================================
//                    Copyright (C) 2017 Olivier Mallet - All Rights Reserved                      
//=================================================================================================

#ifndef POPULATION_HPP
#define POPULATION_HPP

#include "Individual.hpp"
#include <iostream>
#include <vector>
#include <map>

namespace galgo {

	class GeneticAlgorithm;

	class Population
	{

	public:
		// constructors
		Population() {}
		Population(GeneticAlgorithm &ga);
		void evolution();
		int getSumFitness();
		// create a population of chromosomes
		void creation();
		std::shared_ptr<Individual> getBestIndividual();
		float getBestValue();
		// select element at position pos in current population and copy it into mating population
		void select(int pos);
		GeneticAlgorithm *ptr = nullptr;
		std::vector<std::shared_ptr<Individual>> individuals;
		std::vector<std::shared_ptr<Individual>> newpop;
		std::vector<std::shared_ptr<Individual>> matpop;
		int nbrcrov;                              // number of cross-over
		int matidx;


	private:
		// elitism => saving best chromosomes in new population
		void elitism();
		// create new population from recombination of the old one
		void recombination();
		// complete new population randomly
		void completion();
		// update population (adapting, sorting)
		void updating();
		const std::shared_ptr<Individual>& operator[](int pos) const;
	};


}
#endif


