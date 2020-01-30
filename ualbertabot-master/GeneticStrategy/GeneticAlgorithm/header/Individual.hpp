//=================================================================================================
//                    Copyright (C) 2017 Olivier Mallet - All Rights Reserved                      
//=================================================================================================

#ifndef INDIVIDUAL_HPP
#define INDIVIDUAL_HPP

#include <memory>
#include <iostream>
#include <vector>
#include <map>

namespace galgo {

//=================================================================================================
class GeneticAlgorithm;
class Individual
{
public:
	// constructor
	Individual(GeneticAlgorithm& ga);
   // copy constructor
	Individual(Individual& rhs);
   // create new chromosome 
   void create();
   // initialize chromosome
   void initialize();
   // updates fitness
   int Objective(Individual* individual);
   // evaluate chromosome 
   void evaluate(); 
   // reset chromosome
   void reset();
   // set or replace kth gene by a new one
   void setGene(int k);
   // initialize or replace kth gene by a know value
   void initGene(int k, int value);
   // flip an existing chromosome bit
   void flipBit(int pos);
   // initialize or replace a portion of bits with a portion of another chromosome
   void setPortion(Individual& x, int start, int end);
   // get parameter value(s) from chromosome
    std::vector<int>& getParam() ;
   // return chromosome size in number of bits
   int size() ;
   // return number of chromosome bits to mutate
   int mutrate() ;
   // return number of genes in chromosome
   int nbgene() ;
   // return numero of generation this chromosome belongs to
   int nogen() ;

public:
	std::vector<int> param;                     // estimated parameter(s)
	GeneticAlgorithm * ptr = nullptr; // pointer to genetic algorithm
   float fitness;                                // chromosome fitness, objective function(s) result that can be modified (adapted to constraint(s), set to positive values, etc...)
private:
   int numgen;                               // numero of generation
   int maxRand;
   static const int maxUnitNumber = 200; //max number of units
};

/*-------------------------------------------------------------------------------------------------*/
}

#endif