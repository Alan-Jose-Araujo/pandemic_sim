#include "../../include/simulator/Individual.hpp"

namespace simulator
{

    Individual::Individual(std::string)
    : state(state)
    {}

    void Individual::set_state(std::string state)
    {
        this->state = state;
    }

    std::string Individual::get_state()
    {
        return this->state;
    }

};