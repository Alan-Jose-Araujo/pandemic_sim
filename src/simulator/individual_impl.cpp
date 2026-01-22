/**
 * @file individual_impl.cpp
 * @author Alan José <alanjsdelima@gmail.com>
 * @date 2026-01-22
 */

#include "simulator/individual.hpp"

namespace Simulator
{
    Individual::Individual(IndividualState initialState)
    : currentState(initialState) {}

    void Individual::setCurrentState(IndividualState newState)
    {
        currentState = newState;
    }

    IndividualState Individual::getIndividualState()
    {
        return currentState;
    }
};