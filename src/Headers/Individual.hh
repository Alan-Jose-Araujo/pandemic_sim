#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include "State.hh"

/**
 * The individual is a component of the population.
 */
class Individual {

    public:
    
        State state;

        Individual(State initialState = State::healthy) : state(initialState) {}

};

#endif