#include "chromosome.hpp"


#include <algorithm>
#include <cmath>
#include <iostream>
#include <random>

GeneValue geneValue;
static std::default_random_engine generator(std::random_device{}());
static std::uniform_int_distribution<int> num_distribution(1,9);
static std::uniform_int_distribution<int> operator_distribution(10,13);
static std::uniform_real_distribution<float> realDistribution(0,1);

Chromosome::Chromosome()
: m_probability(0.0f)
, m_genes()
, m_result(0.0f)
, m_fitness(0.0f)
{}

Chromosome::Chromosome(int numberOfgenes, const float target)
: m_result(0.0f)
, m_probability(0.0f)
, m_target(target)
{
	if (numberOfgenes % 2 == 0)
	{
		std::cout << "Number of genes should be odd: moving from " << numberOfgenes << " to " << numberOfgenes+1 << std::endl;
		++numberOfgenes; 
	}
	m_genes.reserve(numberOfgenes);
	generate(numberOfgenes); 
	calculateFitness();
}

Chromosome::~Chromosome() {}

const float Chromosome::getFitness() const {return m_fitness;}	

void Chromosome::mutate() 
{
	//Uniform mutation
	for (auto gene : m_genes)
	{
		if (realDistribution(generator) < (1/m_genes.size())) //1/number of gene of the time, a gene mutate
		{
			std::cout << geneValue.valueAsText[gene] << " mutate to ";
			if (GeneValue::NUMBER == geneValue.valueType[gene])
			{
				gene = static_cast<GeneValue::Value>(num_distribution(generator));
			} else {
				gene = static_cast<GeneValue::Value>(operator_distribution(generator));
			}
			std::cout << gene << std::endl;
		}
	}
}

void Chromosome::generate(const int numberOfgenes)
{
	//number of genes is greater or equals to 1
	m_genes.push_back(static_cast<GeneValue::Value>(num_distribution(generator)));
	for (unsigned int i = 1; i < numberOfgenes; i+=2)
	{
		m_genes.push_back(static_cast<GeneValue::Value>(operator_distribution(generator)));
		m_genes.push_back(static_cast<GeneValue::Value>(num_distribution(generator)));
	}
}

void Chromosome::calculateFitness() 
{
	//1/(expected-result) 
	//TODO: cast the gene to float 
	
	m_result = 0.0f;

	GeneValue::Value oldValue(GeneValue::PLUS);
	for (auto gene : m_genes)
	{
		switch (geneValue.valueType[gene])
		{
		case GeneValue::NUMBER:
		{
			switch (oldValue)
	               	{
	               	case GeneValue::PLUS: 
	               		m_result += gene;
	                    	break;
	                case GeneValue::MINUS: 
	                	m_result -= gene;
	                	break;
	                case GeneValue::MULTIPLY: 
	                	m_result *= gene;
	                	break;
	                case GeneValue::DIVIDE: 
	                	m_result /= gene;
	                	break;
	                default:
				std::cerr << "Cannot retrieve operator" << std::endl; 
				break;
	                }
			break;
		}
		case GeneValue::OPERATOR:
		{
			oldValue = gene;
		}
		}
	}
	if (m_target == m_result)
	{
		//In case we found the target number, return big value
		m_fitness = 9999.0f;
	} else {
		m_fitness = 1.0/ std::abs(m_target-m_result);
	}
}

std::vector<GeneValue::Value>::iterator Chromosome::getGeneAt(const int pos)
{
	//TODO: Verify that pos is in range
	return m_genes.begin() + pos;
}
	
