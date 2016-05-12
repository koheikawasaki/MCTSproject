#ifndef MCTS
#define MCTS

namespace MCTS
{
struct ComputeOptions
{
	int max_iterations;
	double max_time;
	bool verbose;
	ComputeOptions() :
		max_iterations(10000),
		max_time(-1.0), // default is no time limit.
		verbose(false)
	{ }
};
 template<typename State>
   typename State::Move compute_move(const State root_state,
                                  const ComputeOptions options = ComputeOptions());
}

#include <algorithm>
#include <cstdlib>
#include <future>
#include <iomanip>
#include <iostream>
#include <map>
#include <memory>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

 
