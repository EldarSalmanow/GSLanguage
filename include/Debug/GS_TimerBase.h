#ifndef GSLANGUAGE_GS_TIMERBASE_H
#define GSLANGUAGE_GS_TIMERBASE_H

#include <chrono>
#include <functional>
#include <iostream>

namespace Debug {

    template<typename _Result, typename... _ArgumentsType>
    class _GS_Timer_Base;

    /**
     * Base class for GS_Timer
     * @tparam _Result Measured function result
     * @tparam _ArgumentsType Input argument types
     */
    template<typename _Result, typename... _ArgumentsType>
    class _GS_Timer_Base<_Result(_ArgumentsType...)> {
    protected:

        /**
         * Time measurement function
         */
        std::function<_Result(_ArgumentsType...)> _function;
    };

}

#endif //GSLANGUAGE_GS_TIMERBASE_H
