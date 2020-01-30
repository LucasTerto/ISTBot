//=================================================================================================
//                    Copyright (C) 2017 Olivier Mallet - All Rights Reserved                      
//=================================================================================================

#ifndef EVOLUTION_HPP
#define EVOLUTION_HPP

#include "GeneticAlgorithm.hpp"
#include "Population.hpp"

// In this header, the user can define his own selection, cross-over, mutation and adaptation to 
// constraint(s) methods by respecting the function declaration template

//=================================================================================================

// SELECTION METHODS

/*-------------------------------------------------------------------------------------------------*/

// proportional roulette wheel selection
	void RWS(galgo::Population& x)
	{
		// computing fitness sum
		float fitsum = x.getSumFitness();

		// selecting mating population
		for (int i = 0, end = x.ptr->matsize; i < end; i++) {
			// generating a random fitness sum in [0,fitsum)
			int fsum = galgo::uniform<int>(0, fitsum);

			int j = 0;
			while (fsum >= 0.0) {
				fsum -= x.individuals[j]->fitness;
				j++;
			}
			// selecting element
			x.select(j - 1);
		}
	}

	/*-------------------------------------------------------------------------------------------------*/

	// stochastic universal sampling selection
	void SUS(galgo::Population& x)
	{
	   // adjusting all fitness to positive values
	   //x.adjustFitness();
	   // computing fitness sum
	   int fitsum = x.getSumFitness();

	   int matsize = x.ptr->matsize;
	   // computing interval size
	   float dist = (float)fitsum / matsize;
	   // initializing pointer
	   float ptr = galgo::uniform<float>(0.0, dist);

	   // selecting mating population
	   for (int i = 0; i < matsize; ++i) {

		  int j = 0;
		  int fsum = 0;

		  while (fsum <= ptr) {
			 #ifndef NDEBUG
			 if (j == x.ptr->popsize) {
				throw std::invalid_argument("Error: in SUS(galgo::Population<T>&) index j cannot be equal to population size.");
			 }
			 #endif
			 fsum += x.individuals[j]->fitness;
			 j++;
		  }
		  // selecting element
		  x.select(j - 1);

		  // incrementing pointer
		  ptr += dist;
	   }
	}

	/*-------------------------------------------------------------------------------------------------*/

	// classic linear rank-based selection
	void RNK(galgo::Population& x)
	{
	   int popsize = x.ptr->popsize;
	   static std::vector<int> rank(popsize);
	   static int ranksum;

	   // this will only be run at the first generation
	   if (x.ptr->nogen == 1) {
		  int n = popsize + 1;
		  // generating ranks from highest to lowest
		  std::generate_n(rank.begin(), popsize, [&n]()->int{return --n;});
		  // computing sum of ranks
		  ranksum = .5 * popsize * (popsize + 1);
	   }

	   // selecting mating population
	   for (int i = 0, end = x.ptr->matsize; i < end; ++i) {
		  // generating a random rank sum in [1,ranksum)
		  int rsum = galgo::uniform<int>(1, ranksum);

		  int j = 0;
		  while (rsum > 0) {
			 #ifndef NDEBUG
			 if (j == popsize) {
				throw std::invalid_argument("Error: in RNK(galgo::Population<T>&) index j cannot be equal to population size.");
			 }
			 #endif
			 rsum -= rank[j];
			 j++;
		  }
		  // selecting element
		  x.select(j - 1);
	   }
	}

	/*-------------------------------------------------------------------------------------------------*/

	// linear rank-based selection with selective pressure
	void RSP(galgo::Population& x)
	{
	   int popsize = x.ptr->popsize;
	   static std::vector<int> rank(popsize);
	   static int ranksum;

	   // this will only be run at the first generation
	   if (x.ptr->nogen == 1) {
		  // initializing ranksum
		  ranksum = 0.0;
		  // generating ranks from highest to lowest
		  for (int i = 0; i < popsize; ++i) {
			 rank[i] = 2 - x.ptr->SP + 2 * (x.ptr->SP - 1) * (popsize - i) / popsize;
			 ranksum += rank[i];
		  }
	   }

	   // selecting mating population
	   for (int i = 0, end = x.ptr->matsize; i < end; ++i) {
		  // generating a random rank sum in [0,ranksum)
		  int rsum = galgo::uniform<int>(0.0, ranksum);

		  int j = 0;
		  while (rsum >= 0.0) {
			 #ifndef NDEBUG
			 if (j == popsize) {
				throw std::invalid_argument("Error: in RSP(galgo::Population<T>&) index j cannot be equal to population size.");
			 }
			 #endif
			 rsum -= rank[j];
			 j++;
		  }
		  // selecting element
		  x.select(j - 1);
	   }
	}

	/*-------------------------------------------------------------------------------------------------*/

	// tournament selection
	void TNT(galgo::Population& x)
	{
	   int popsize = x.ptr->popsize;
	   int tntsize = x.ptr->tntsize;

	   // selecting mating population
	   for (int i = 0, end = x.ptr->matsize; i < end; ++i) {
		  // selecting randomly a first element
		  int bestIdx = galgo::uniform<int>(0, popsize);
		  float bestFit = x.individuals[bestIdx]->fitness;

		  // starting tournament
		  for (int j = 1; j < tntsize; ++j) {

			 int idx = galgo::uniform<int>(0, popsize);
			 float fit = x.individuals[idx]->fitness;

			 if (fit > bestFit) {
				bestFit = fit;
				bestIdx = idx;
			 }
		  }
		  // selecting element
		  x.select(bestIdx);
	   }
	}

	/*-------------------------------------------------------------------------------------------------*/

	// transform ranking selection
	void TRS(galgo::Population& x)
	{
	   static float c;
	   // (re)initializing when running new GA
	   if (x.ptr->nogen == 1) {
		  c = 0.2;
	   }
	   int popsize = x.ptr->popsize;
	   // generating a random set of popsize values on [0,1)
	   std::vector<float> r(popsize);
	   std::for_each(r.begin(), r.end(), [](float& z)->float {z = galgo::proba(galgo::rng); return z; });
	   // sorting them from highest to lowest
	   std::sort(r.begin(),r.end(),[](float z1, float z2)->bool{return z1 > z2;});
	   // transforming population fitness
	   auto it = x.individuals.begin();
	   std::for_each(r.begin(),r.end(),[&it,popsize](float z)->void{(*it)->fitness = ceil((popsize - popsize*exp(-c*z))/(1 - exp(-c))); it++;});

	   // updating c for next generation
	   //c = c + 0.1; // arithmetic transition
	   c = c * 1.1; // geometric transition
	   // computing fitness sum
	   float fitsum = x.getSumFitness();

	   // selecting mating population
	   for (int i = 0, end = x.ptr->matsize; i < end; ++i) {
		  // generating a random fitness sum in [0,fitsum)
		  int fsum = galgo::uniform<int>(0, fitsum);

		  int j = 0;
		  while (fsum >= 0) {
			 #ifndef NDEBUG
			 if (j == popsize) {
				throw std::invalid_argument("Error: in TRS(galgo::Population<T>&) index j cannot be equal to population size.");
			 }
			 #endif
			 fsum -= x.individuals[j]->fitness;
			 j++;
		  }
		  // selecting element
		  x.select(j - 1);
	   }
	}

	/*-------------------------------------------------------------------------------------------------*/

	// CROSS-OVER METHODS

	/*-------------------------------------------------------------------------------------------------*/

	// one-point random cross-over of 2 chromosomes
	void P1XO(const galgo::Population& x, std::shared_ptr<galgo::Individual>& chr1, std::shared_ptr<galgo::Individual>& chr2)
	{
		// choosing randomly 2 chromosomes from mating population
		int idx1 = galgo::uniform(0, x.ptr->matsize);
		int idx2 = galgo::uniform(0, x.ptr->matsize);
		// choosing randomly a position for cross-over
		int pos = galgo::uniform(0, chr1->size());
		// transmitting portion of bits to new chromosomes
		chr1->setPortion(*x.matpop[idx1], 0, pos);
		chr2->setPortion(*x.matpop[idx2], 0, pos);
		chr1->setPortion(*x.matpop[idx2], pos + 1, chr1->size());
		chr2->setPortion(*x.matpop[idx1], pos + 1, chr1->size());
	}

	/*-------------------------------------------------------------------------------------------------*/

	// two-point random cross-over of 2 chromosomes
	void P2XO(const galgo::Population& x, std::shared_ptr<galgo::Individual>& chr1, std::shared_ptr<galgo::Individual>& chr2)
	{
	   // choosing randomly 2 chromosomes from mating population
	   int idx1 = galgo::uniform<int>(0, x.ptr->matsize);
	   int idx2 = galgo::uniform<int>(0, x.ptr->matsize);
	   // choosing randomly 2 positions for cross-over
	   int pos1 = galgo::uniform<int>(0, chr1->size());
	   int pos2 = galgo::uniform<int>(0, chr1->size());
	   // ordering these 2 random positions
	   int m = std::min(pos1,pos2);
	   int M = std::max(pos1,pos2);
	   // transmitting portion of bits new chromosomes
	   chr1->setPortion(*x.matpop[idx1], 0, m);
	   chr2->setPortion(*x.matpop[idx2], 0, m);
	   chr1->setPortion(*x.matpop[idx2], m + 1, M);
	   chr2->setPortion(*x.matpop[idx1], m + 1, M);
	   chr1->setPortion(*x.matpop[idx1], M + 1, chr1->size());
	   chr2->setPortion(*x.matpop[idx2], M + 1, chr2->size());
	}

	/*-------------------------------------------------------------------------------------------------*/

	// uniform random cross-over of 2 chromosomes
	/*void UXO(const galgo::Population& x, std::shared_ptr<galgo::Individual>& chr1, std::shared_ptr<galgo::Individual>& chr2)
	{
	   // choosing randomly 2 chromosomes from mating population
	   int idx1 = ::uniform<int>(0, x.ptr->matsize);
	   int idx2 = ::uniform<int>(0, x.ptr->matsize);

	   for (int j = 0; j < chr1->param.size()*4; ++j) {
		  // choosing 1 of the 2 chromosomes randomly
		  if (::proba(::rng) < 0.50) {
			 // adding its jth bit to new chromosome
			 chr1->addBit(x.individuals[idx1]->getBit(j));
			 chr2->addBit(x.individuals[idx2]->getBit(j));
		  } else {
			 // adding its jth bit to new chromosomes
			 chr1->addBit(x.individuals[idx2]->getBit(j));
			 chr2->addBit(x.individuals[idx1]->getBit(j));
		  }
	   }
	}*/

	/*-------------------------------------------------------------------------------------------------*/

	// MUTATION METHODS

	/*-------------------------------------------------------------------------------------------------*/

	// boundary mutation: replacing a chromosome gene by its lower or upper bound
	/*void BDM(galgo::CHR<T>& chr)
	{
	   T mutrate = chr->mutrate();

	   if (mutrate == 0.0) return;

	   // getting chromosome lower bound(s)
	   const std::vector<T>& lowerBound = chr->lowerBound();
	   // getting chromosome upper bound(s)
	   const std::vector<T>& upperBound = chr->upperBound();

	   // looping on number of genes
	   for (int i = 0; i < chr->nbgene(); ++i) {
		  // generating a random probability
		  if (galgo::proba(galgo::rng) <= mutrate) {
			 // generating a random probability
			 if (galgo::proba(galgo::rng) < .5) {
				// replacing ith gene by lower bound
				chr->initGene(i, lowerBound[i]);
			 } else {
				// replacing ith gene by upper bound
				chr->initGene(i, upperBound[i]);
			 }
		  }
	   }
	}*/

	/*-------------------------------------------------------------------------------------------------*/

	// single point mutation: flipping a chromosome bit
	void SPM(std::shared_ptr<galgo::Individual>& chr)
	{
		double mutrate = chr->ptr->mutrate;

		if (mutrate == 0.0) return;

		// looping on chromosome bits
		for (int i = 0; i < chr->param.size() * 4; i++) {
			// generating a random probability
			if (galgo::proba(galgo::rng) <= mutrate) {
				// flipping ith bit
				chr->flipBit(i);
			}
		}
	}

	/*-------------------------------------------------------------------------------------------------*/

	// uniform mutation: replacing a chromosome gene by a new one
	void UNM(std::shared_ptr<galgo::Individual>& chr)
	{
	   float mutrate = chr->mutrate();

	   if (mutrate == 0.0) return;

	   // looping on number of genes
	   for (int i = 0; i < chr->nbgene(); ++i) {
		  // generating a random probability
		  if (galgo::proba(galgo::rng) <= mutrate) {
			 // replacing ith gene by a new one
			 chr->setGene(i);
		  }
	   }
	}

	/*-------------------------------------------------------------------------------------------------*/

	// ADAPTATION TO CONSTRAINT(S) METHODS

	/*-------------------------------------------------------------------------------------------------*/

	// adapt population to genetic algorithm constraint(s)
	/*void DAC(galgo::Population& x)
	{
	   // getting worst population objective function total result
	   T worstTotal = x.getWorstTotal();

	   for (auto it = x.begin(), end = x.end(); it != end; ++it) {
		  // computing element constraint value(s)
		  const std::vector<T>& cst = (*it)->getConstraint();
		  // adapting fitness if any constraint violated
		  if (std::any_of(cst.cbegin(), cst.cend(), [](T x)->bool{return x >= 0.0;})) {
			 (*it)->fitness = worstTotal - std::accumulate(cst.cbegin(), cst.cend(), 0.0);
		  }
	   }
	}
	*/
	//================================================================================================= 
#endif
