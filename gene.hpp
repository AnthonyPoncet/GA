#ifndef INCLUDE_GENE_HPP
#define INCLUDE_GENE_HPP

#include <map>
#include <string>
#include <vector>

struct GeneValue
{
	enum Value
	{
		ZERO    = 0b0000,
               	ONE     = 0b0001,
                TWO     = 0b0010,
                THREE   = 0b0011,
                FOUR    = 0b0100,
                FIVE    = 0b0101,
                SIX     = 0b0110,
                SEVEN   = 0b0111,
                EIGHT   = 0b1000,
                NINE    = 0b1001,
                PLUS    = 0b1010,
                MINUS   = 0b1011,
		MULTIPLY= 0b1100,
                DIVIDE  = 0b1101
	};
	
	enum Type
	{
	    NUMBER,
	    OPERATOR,
	};
	
	std::map<Value,Type> valueType = {{Value::ZERO, Type::NUMBER}, 
	                                    {Value::ONE, Type::NUMBER},
	                                    {Value::TWO, Type::NUMBER},
	                                    {Value::THREE, Type::NUMBER},
	                                    {Value::FOUR, Type::NUMBER},
	                                    {Value::FIVE, Type::NUMBER},
	                                    {Value::SIX, Type::NUMBER},
	                                    {Value::SEVEN, Type::NUMBER},
	                                    {Value::EIGHT, Type::NUMBER},
	                                    {Value::NINE, Type::NUMBER},
	                                    {Value::PLUS, Type::OPERATOR},
	                                    {Value::MINUS, Type::OPERATOR},
	                                    {Value::MULTIPLY, Type::OPERATOR},
	                                    {Value::DIVIDE, Type::OPERATOR}};
	
	std::vector<std::string> valueAsText = {"ZERO", "ONE", "TWO", "THREE", "FOUR", "FIVE", "SIX", "SEVEN", "EIGHT", "NINE", "PLUS", "MINUS", "MULTIPLY", "DIVIDE"};
};

extern GeneValue geneValue;

#endif
