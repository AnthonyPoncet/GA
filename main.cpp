#include "engine.hpp"

#include <iostream>

static int NUM(0);

static std::pair<int, Chromosome> oneBatch()
{
  	std::cout << "\n==========================================" << std::endl;
	std::cout << "run " << NUM << std::endl; ++NUM;
  	std::cout << "==========================================" << std::endl;
	Engine myEngine(100, 42);
 	
	for (auto i = 0; i < 100; ++i)
	{ 
		std::pair<bool, Chromosome> result = myEngine.hasSolution();
		if (result.first)
		{
			std::cout << "Got a solution in " << i+1 << " turn(s): " << result.second << std::endl;
			return std::make_pair(i+1, result.second);
		}
  		myEngine.makeNewGeneration();
	}
	std::pair<bool, Chromosome> result = myEngine.hasSolution();
	if (result.first)
	{
		std::cout << "Got a solution in 100 turns: " << result.second << std::endl;
		return std::make_pair(100, result.second);
	} else {
		std::cout << "No solution found" << std::endl;
		return std::make_pair(0, Chromosome());
	}
}

int main()
{
	int numberOfSucess(0);
	std::map<Chromosome, std::vector<bool> > results;
	for (auto i = 0; i < 100; ++i)
	{
		std::pair<bool, Chromosome> out = oneBatch();
		if (out.first != 0)
		{
			++numberOfSucess;
			auto found = results.find(out.second);
			if (results.end() != found)
			{
				results[out.second].push_back(out.first);
			} else {
				std::vector<bool> res = {out.first};
				results[out.second] = res;
			}
		} else {
			
		}
	}
  	std::cout << "\n==========================================" << std::endl;
	std::cout << "Found solution " << numberOfSucess << " times on 100" << std::endl;
	std::for_each(
		results.begin(), 
		results.end(), 
		[](const std::pair<Chromosome, std::vector<bool> >& c) {std::cout << c.first << " has been found " << c.second.size() << " times"<< std::endl;});
	return 42;
}
