#ifndef ADD_RANDOM_FOOD_ARGS_HPP
#define ADD_RANDOM_FOOD_ARGS_HPP

#include "Area.hpp"
#include "Foods.hpp"

class Foods;
class Area;

struct AddRandomFoodArgs
{
	Foods *foods;
	Area *area;
};

#endif // !ADD_RANDOM_FOOD_ARGS_HPP
