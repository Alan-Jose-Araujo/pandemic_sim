/**
 * Individual.hpp
 * @author Alan José <alanjsdelima@gmail.com>
 *
 * The individual is a component from population matrix, it has a property called state
 * that can assume some values, it will be used to run the state transitions.
 */

#ifndef INDIVIDUAL_H
#define INDIVIDUAL_H

#include <string>

namespace simulator
{

    class Individual
    {

        private:

            std::string state;

        public:

            Individual(std::string state);

            void set_state(std::string state);

            std::string get_state();

    };
    

};

#endif // INDIVIDUAL_H