//=================================================================================================
//                    Copyright (C) 2017 Olivier Mallet - All Rights Reserved                      
//=================================================================================================

#ifndef GENETICALGORITHM_HPP
#define GENETICALGORITHM_HPP

#include "Hash.hpp"
#include <ctime>
#include "Randomize.hpp"
#include "EnemyHash.hpp"
#include "Individual.hpp"

namespace galgo {// Mersenne Twister 19937 pseudo-random number generator
	class Population;
	//=================================================================================================
	class GeneticAlgorithm
	{

	private:
		Population *pop = nullptr;             // population of chromosomes

	public:
		Hash * populationHash;	  // init func will initialize it
	// selection method initialized to roulette wheel selection                                   
		void(*Selection)(Population&);
		// cross-over method initialized to 1-point cross-over                                
		void(*CrossOver)(const Population&, std::shared_ptr<galgo::Individual>&, std::shared_ptr<galgo::Individual>&);
		// mutation method initialized to single-point mutation 
		void(*Mutation)(std::shared_ptr<galgo::Individual>&);
		// adaptation to constraint(s) method                                        
		//void(*Adaptation)(Population<T>&) = nullptr;

		double covrate = .60;   // cross-over rate
		double mutrate = .50;   // mutation rate   
		double SP = 1.5;        // selective pressure for RSP selection method 
		double tolerance = 0.0; // terminal condition (inactive if equal to zero)

		int elitpop = 3;   // elit population size
		int matsize;       // mating pool size, set to popsize by default
		int tntsize = 10;  // tournament size
		int genstep = 10;  // generation step for outputting results
		int precision = 5; // precision for outputting results
		int popsize;   // population size
		int nbgen;     // number of generations
		int nogen = 0; // numero of generation
		int nbparam;   // number of parameters to be estimated
		float weight = 0; //variable weight for fitness depending on the number of enemy units (number of enemy units/max units)
		float normalize = 0; //variable to normalize counter and cost variables

						   // constructor
		GeneticAlgorithm(int popsize, int nbgen, int output);
		// run genetic algorithm
		std::map<BWAPI::UnitType, int> run(std::string enemyRace, std::string myRace, std::vector<BWAPI::UnitType> units);
		std::map<BWAPI::UnitType, int> getMapResult(std::vector<int> param);

		const std::shared_ptr<Individual> result() const;

	private:
		int nbbit;     // total number of bits per chromosome
		int output;   // control if results must be outputted

		// print results for each new generation
		void print(clock_t tStart, int nogen) const;
		void init(std::string enemyRace, std::string myRace, std::vector<BWAPI::UnitType> units);
	};
}

#endif
