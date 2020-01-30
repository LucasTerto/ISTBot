//=================================================================================================
//                    Copyright (C) 2017 Olivier Mallet - All Rights Reserved                      
//=================================================================================================

#ifndef GALGO_H
#define GALGO_H

//================================================================================================= 

#include <map>
#include <utility> 
#include <algorithm>
#include <functional>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <limits>
#include <memory>
#include <numeric>
#include <random>
#include <sstream>
#include <stdexcept>
#include <string>
#include <tuple>
#include <type_traits>
#include <vector>
#include <climits>
#include <cmath>
#include <cstring>

/*-------------------------------------------------------------------------------------------------*/


#ifdef _OPENMP 
  #include <omp.h>
  // getting maximum number of threads available
  static const int MAX_THREADS = omp_get_max_threads();
#endif

/*-------------------------------------------------------------------------------------------------*/

/*#include "GeneticAlgorithm.hpp"
#include "Evolution.hpp"
#include "Population.hpp"
#include "Individual.hpp"
#include "Hash.hpp"
#include "ProtossHash.hpp"
#include "ZergHash.hpp"
#include "TerranHash.hpp"
#include "EnemyHash.hpp"*/

//================================================================================================= 

#endif

