#include "engine.hpp"


#include <algorithm>
#include <iostream>

static std::default_random_engine generator(std::random_device{}());
static std::uniform_real_distribution<float> realDistribution(0,1);
static int NUMBER_OF_GENES(5);

Engine::Engine(const unsigned int populationSize, const float target)
: m_newPopulation()
{
	std::cout << "This batch will be composed of " << populationSize
			<< " individuals of " << NUMBER_OF_GENES 
			<< " genes and target the number " 
			<< target << std::endl;
	m_population.reserve(populationSize);
	for (unsigned int i = 0; i < populationSize; ++i)
	{
		m_population.push_back(Chromosome(NUMBER_OF_GENES, target));
	}
}
Engine::~Engine() {}
	
void Engine::printAdult()
{
	std::for_each(m_population.begin(), m_population.end(), [](const Chromosome& c) {std::cout << c << std::endl;});
}

void Engine::printChildren()
{
	std::for_each(m_newPopulation.begin(), m_newPopulation.end(), [](const Chromosome& c) {std::cout << c << std::endl;});
}

void Engine::makeNewGeneration()
{
	while(m_newPopulation.size() < m_population.size())
	{
  		selection();
  		//std::cout << "\n==========================================\n\n";
  		crossover();
  		//std::cout << "\n==========================================\n\n";
  		mutate();
	}
	std::for_each(m_newPopulation.begin(), m_newPopulation.end(), [](Chromosome& c) {c.calculateFitness();});
	m_population.clear();
	std::copy(m_newPopulation.begin(), m_newPopulation.end(), std::back_inserter(m_population));
	m_newPopulation.clear();
}

std::pair<bool, Chromosome> Engine::hasSolution()
{
	for (auto const c : m_population)
	{
		if (9999 <= c.getFitness())
		{
			return std::make_pair(true, c);
		}
	}
	return std::make_pair(false, Chromosome());
}

struct compareProba
{
	const float convert(const Chromosome& c) const
	{
		return c.m_probability;
	}
	const float convert(const float& f) const
	{
		return f;
	}
	template<typename T1, typename T2>
	bool operator()(const T1& t1, const T2& t2)
	{
		return convert(t1) < convert(t2);
	}
};

void Engine::selection()
{
	//Find sum of fitnesses
	float sum = std::accumulate(std::next(m_population.begin()), 
				    m_population.end(), 
				    m_population[0].getFitness(), 
				    [](float a, const Chromosome& b){return a + b.getFitness();});
	//Generate linear probability
	float cumulateProb(0.0f);
	std::for_each(m_population.begin(), 
			m_population.end(), 
			[&](Chromosome& b) {b.m_probability = cumulateProb + b.getFitness() / sum; cumulateProb = b.m_probability;});
	//DEBUG
	//std::for_each(m_population.begin(), 
	//		m_population.end(), 
	//		[](const Chromosome& b){std::cout << b.m_probability << " - ";});
	//std::cout << std::endl;

	//Generate two rand between 0 and 1 and get selected parent.
	std::vector<Chromosome>::iterator first, second;
	float rand = realDistribution(generator);
	first = std::lower_bound(m_population.begin(), m_population.end(), rand, compareProba());
	//std::cout << "rand value " << rand << " => " << *first << std::endl;
	do
	{
		rand = realDistribution(generator);
		second = std::lower_bound(m_population.begin(), m_population.end(), rand, compareProba());
	}while(first == second);
	//std::cout << "rand value " << rand << " => " << *second << std::endl;

	m_newPopulation.insert(m_newPopulation.begin(), *first);
	m_newPopulation.insert(m_newPopulation.begin(), *second);
}

void Engine::crossover()
{
	//Uniform crossover
	
	if (realDistribution(generator) > 0.7f) //70% of the time crossover is performed
	{
		//std::cout << "No crossover performed" << std::endl;
		return;
	}
	
	for (auto i = 0; i < NUMBER_OF_GENES; ++i)
	{
		if (realDistribution(generator) < 0.5f) //50% of the time a swap occured
		{
			//std::cout << "Have to swap at position " << i << " -> " 
			//		<< geneValue.valueAsText[*m_newPopulation[0].getGeneAt(i)] << " and " 
			//		<< geneValue.valueAsText[*m_newPopulation[1].getGeneAt(i)] << std::endl;
			std::iter_swap(m_newPopulation[0].getGeneAt(i), m_newPopulation[1].getGeneAt(i));
		}
	}
}

void Engine::mutate()
{
	m_newPopulation[0].mutate();
	m_newPopulation[1].mutate();
}
