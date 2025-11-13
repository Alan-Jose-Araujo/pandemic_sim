#include "../../include/simulator/Individual.hpp"

namespace simulator
{

    std::map<std::string, int> Individual::valid_states = { {"healthy", 0}, {"sick", 1}, {"dead", 2}, {"immune", 3} };

    Individual::Individual(std::string state)
    : state(Individual::valid_states[state])
    {}

    void Individual::set_state(std::string state)
    {
        this->state = Individual::valid_states[state];
    }

    void Individual::set_state(int state)
    {
        this->state = state;
    }

    int Individual::get_state()
    {
        return this->state;
    }

};