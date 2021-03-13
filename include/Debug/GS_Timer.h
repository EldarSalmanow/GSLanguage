#ifndef GSLANGUAGE_GS_TIMER_H
#define GSLANGUAGE_GS_TIMER_H

#include <string>

#include "GS_TimerBase.h"

#include "GS_TimerResults.h"

namespace Debug {

    template<typename... _ArgumentsType>
    class GS_Timer;

    /**
     * Class for measuring the execution time of a function
     * @tparam _Result Measured function result
     * @tparam _ArgumentsType Input argument types
     */
    template<typename _Result, typename... _ArgumentsType>
    class GS_Timer<_Result(_ArgumentsType...)> : protected _GS_Timer_Base<_Result(_ArgumentsType...)> {
    public:

        /**
         * Constructor for GS_Timer
         * @param function Time measurement function
         */
        GS_Timer(std::function<_Result(_ArgumentsType...)> function) {
            _GS_Timer_Base<_Result(_ArgumentsType...)>::_function = function;
        }

        /**
         * Function for starting input function and calculating runtime
         * @param message Message for printing information about function
         * @param arguments Input argument types
         * @return Measured function result
         */
        _Result runtime(std::string message, _ArgumentsType... arguments) {
            std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

            _Result result = this->_function(arguments...);

            std::chrono::system_clock::time_point end = std::chrono::system_clock::now();

            std::chrono::duration<double> time = end - start;

            GS_TimerResults::addTimerResult("\n" + message + ": " + std::to_string(time.count()) + " seconds." + "\n");

            return result;
        }
    };

    /**
     * Class for measuring the execution time of a function (class for void _Result type)
     * @tparam _ArgumentsType Input argument types
     */
    template<typename... _ArgumentsType>
    class GS_Timer<void(_ArgumentsType...)> : protected _GS_Timer_Base<void(_ArgumentsType...)> {
    public:

        /**
         * Constructor for GS_Timer
         * @param function Time measurement function
         */
        GS_Timer(std::function<void(_ArgumentsType...)> function) {
            _GS_Timer_Base<void(_ArgumentsType...)>::_function = function;
        }

        /**
         * Function for starting input function and calculating runtime
         * @param message Message for printing information about function
         * @param arguments Input argument types
         */
        void runtime(std::string message, _ArgumentsType... arguments) {
            std::chrono::system_clock::time_point start = std::chrono::system_clock::now();

            this->_function(arguments...);

            std::chrono::system_clock::time_point end = std::chrono::system_clock::now();

            std::chrono::duration<double> time = end - start;

            GS_TimerResults::addTimerResult("\n" + message + ": " + std::to_string(time.count()) + " seconds." + "\n");

            return;
        }
    };

}

#endif //GSLANGUAGE_GS_TIMER_H
