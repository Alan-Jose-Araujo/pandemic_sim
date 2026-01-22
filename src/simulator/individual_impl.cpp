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

    void Individual::setCurrentState(IndividualState value)
    {
        currentState = value;
    }

    IndividualState Individual::getIndividualState() const
    {
        return currentState;
    }
};