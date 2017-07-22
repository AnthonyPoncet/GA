#include "gene.hpp"

#include <iostream>
#include <algorithm>

class Chromosome
{
public:
	Chromosome();
	Chromosome(const int numberOfgenes, const float target);
	~Chromosome();
	
	void calculateFitness();
	void mutate();
	const float getFitness() const;
	std::vector<GeneValue::Value>::iterator getGeneAt(const int pos);
	
	friend std::ostream& operator<<(std::ostream& os, const Chromosome& c);
	friend bool operator==(const Chromosome& l, const Chromosome& r)
	{
		if (l.m_genes.size() != r.m_genes.size()) return false;
		for (auto i = 0; i < l.m_genes.size(); ++i) 
		{
			if (l.m_genes[i] != r.m_genes[i]) return false;
		}
		return true;
	}
	friend bool operator<(const Chromosome& l, const Chromosome& r)
	{
		if (l.m_genes.size() != r.m_genes.size()) return false;
		for (auto i = 0; i < l.m_genes.size(); ++i) 
		{
			if (l.m_genes[i] < r.m_genes[i])
			{
				return true;
			} else if (l.m_genes[i] > r.m_genes[i]) {
				return false;
			}
		}
		return false;
	}

public:
	float m_probability;

private:
	void generate(const int numberOfgenes);
	
private:
	std::vector<GeneValue::Value> m_genes;
	float m_result;
	float m_fitness;
	float m_target;
};

inline std::ostream& operator<<(std::ostream& os, const Chromosome& c)
{
	auto format = [&](const GeneValue::Value& n) {os << geneValue.valueAsText[n] << " ";};
	std::for_each(c.m_genes.begin(), c.m_genes.end(), format);
	//os << "-> " << c.m_result << " -> " << c.m_fitness; //TODO: debug purpose
	return os;
}

