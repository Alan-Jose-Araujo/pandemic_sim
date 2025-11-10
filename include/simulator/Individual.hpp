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
#include <map>

namespace simulator
{

    class Individual
    {

        private:

            int state;

        public:

            static std::map<std::string, int> valid_states;

            Individual(std::string state);

            void set_state(std::string state);

            void set_state(int state);

            int get_state();

    };
    

};

#endif // INDIVIDUAL_H