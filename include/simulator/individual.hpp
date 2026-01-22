/**
 * @file individual.hpp
 * @brief A population member with health-state.
 * @author Alan José <alanjsdelima@gmail.com>
 * @date 2026-01-22
 */

#pragma once

namespace Simulator
{
    enum class IndividualState
    {
        Healthy = 0,
        Isolated = 1,
        Sick = 2,
        Dead = 3,
        Immune = 4,
    };

    class Individual
    {
    private:
        IndividualState currentState;

    public:
        Individual(IndividualState initialState);

        void setCurrentState(IndividualState value);

        IndividualState getIndividualState() const;
    };
};