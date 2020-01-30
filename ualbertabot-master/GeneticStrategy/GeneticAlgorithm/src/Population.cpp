//=================================================================================================
//                    Copyright (C) 2017 Olivier Mallet - All Rights Reserved                      
//=================================================================================================

#ifndef POPULATION_CPP
#define POPULATION_CPP

#include "../header/Population.hpp"
#include "../header/GeneticAlgorithm.hpp"
//#include "../header/Randomize.hpp"


namespace galgo {

	/*-------------------------------------------------------------------------------------------------*/

	Population::Population(GeneticAlgorithm& ga) {
		ptr = &ga;
		nbrcrov = floor(ptr->covrate * (ptr->popsize - ptr->elitpop));
		// adjusting nbrcrov (must be an even number)
		if (nbrcrov % 2 != 0) nbrcrov -= 1;
		// for convenience, we add elitpop to nbrcrov
		nbrcrov += ptr->elitpop;
		// allocating memory
		individuals.resize(ptr->popsize);
		matpop.resize(ptr->matsize);
	}

	int Population::getSumFitness()
	{
		int totalFitness = 0;
		for (int i = 0; i < individuals.size(); i++) {
			totalFitness += individuals[i]->fitness;
		}
		return totalFitness;
	}

	/**************************************************************************************************/
	void Population::select(int pos)
	{
		matpop[matidx] = individuals[pos];
		matidx++;
	}


	// create a population of chromosomes
	void Population::creation()
	{
		int start = 0;
		// initializing first chromosome
		if (individuals.empty()) {
			individuals[0] = std::make_shared<Individual>(*ptr);
			individuals[0]->initialize();
			individuals[0]->evaluate();
			start++;
		}
		// getting the rest
#ifdef _OPENMP 
#pragma omp parallel for num_threads(MAX_THREADS)
#endif
		for (int i = start; i < ptr->popsize; i++) {
			individuals[i] = std::make_shared<Individual>(*ptr);
			individuals[i]->create();
			individuals[i]->evaluate();
		}
		// updating population
		this->updating();
	}

	std::shared_ptr<Individual> Population::getBestIndividual() {
		return individuals[0];
	}

	float Population::getBestValue() {
		return this->getBestIndividual()->fitness;
	}
	/*-------------------------------------------------------------------------------------------------*/

	// population evolution (selection, recombination, completion, mutation), get next generation
	void Population::evolution()
	{
		matidx = 0;
		// selecting mating population
		ptr->Selection(*this);
		// applying elitism if required
		this->elitism();//3
		// crossing-over mating population
		this->recombination();
		// completing new population
		this->completion();
		// moving new population into current population for next generation
		individuals = std::move(newpop);
		// updating population
		this->updating();
	}

	/*-------------------------------------------------------------------------------------------------*/

	// elitism => saving best chromosomes in new population, making a copy of each elit chromosome
	void Population::elitism()
	{
		// (re)allocating new population
		newpop.clear();
		newpop.resize(ptr->popsize);

		if (ptr->elitpop > 0) {
			// copying elit chromosomes into new population
			std::transform(individuals.cbegin(), individuals.cend(), newpop.begin(), [](const std::shared_ptr<galgo::Individual>& chr)->std::shared_ptr<galgo::Individual> {return std::make_shared<Individual>(*chr); });
		}
	}

	/*-------------------------------------------------------------------------------------------------*/

	// create new population from recombination of the old one
	void Population::recombination()
	{
		// creating a new population by cross-over
#ifdef _OPENMP 
#pragma omp parallel for num_threads(MAX_THREADS)
#endif
		for (int i = ptr->elitpop; i < nbrcrov; i = i + 2) {
			// initializing 2 new chromosome
			//newpop[i] = std::make_shared<Individual>(*ptr);// TODO:: LUCAS REVER ISTO
			//newpop[i + 1] = std::make_shared<Individual>(*ptr);
			// crossing-over mating population to create 2 new chromosomes
			ptr->CrossOver(*this, newpop[i], newpop[i + 1]);
			// mutating new chromosomes
			ptr->Mutation(newpop[i]);
			ptr->Mutation(newpop[i + 1]);
			// evaluating new chromosomes
			newpop[i]->evaluate();
			newpop[i + 1]->evaluate();
		}
	}


	void Population::completion()
	{
#ifdef _OPENMP 
#pragma omp parallel for num_threads(MAX_THREADS)
#endif
		for (int i = nbrcrov; i < ptr->popsize; i++) {
			// selecting chromosome randomly from mating population
			newpop[i] = std::make_shared<Individual>(*matpop[uniform<int>(0, ptr->matsize)]);
			// mutating chromosome
			ptr->Mutation(newpop[i]);
			// evaluating chromosome
			newpop[i]->evaluate();
		}
	}

	void Population::updating()
	{
		// sorting chromosomes from best to worst fitness
		std::sort(individuals.begin(), individuals.end(), [](std::shared_ptr<Individual>& chr1, std::shared_ptr<Individual>& chr2)->bool {return chr1->fitness > chr2->fitness; });
	}

	const std::shared_ptr<Individual>& Population::operator[](int pos) const
	{
#ifndef NDEBUG
		if (pos > ptr->matsize - 1) {
			throw std::invalid_argument("Error: in galgo::Population<T>::operator[](int), exceeding mating population memory.");
		}
#endif

		return matpop[pos];
	}
}
#endif


