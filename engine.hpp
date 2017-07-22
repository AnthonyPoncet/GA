#include "chromosome.hpp"

class Engine
{
public:
	Engine(const unsigned int populationSize, const float target);
	~Engine();
	
	void printAdult();
	void printChildren();
	void makeNewGeneration();
	std::pair<bool, Chromosome> hasSolution();

private:
	void selection();
	void crossover();
	void mutate();

private:
	std::vector<Chromosome> m_population;
	std::vector<Chromosome> m_newPopulation;
};

