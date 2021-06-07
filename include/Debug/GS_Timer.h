#ifndef GSLANGUAGE_GS_TIMER_H
#define GSLANGUAGE_GS_TIMER_H

#include <chrono>
#include <vector>

#include <CrossPlatform/GS_PlatformTypes.h>
#include <Debug/GS_Debug.h>

namespace Debug {

    /**
     *
     */
    class GS_Timer {
    public:

        /**
         *
         */
        using clock = std::chrono::steady_clock;

        /**
         *
         */
        using time_point = std::chrono::time_point<clock>;

        /**
         *
         */
        using duration = std::chrono::microseconds;

        /**
         *
         */
        using measuringResult = GSString;

        /**
         *
         */
        using measuringResults = std::vector<measuringResult>;

    public:

        /**
         *
         */
        GS_Timer() = default;

    public:

        /**
         *
         */
        GSVoid start();

        /**
         *
         */
        GSVoid stop();

        /**
         *
         * @return
         */
        duration result();

        /**
         *
         * @param result
         */
        GSVoid addResult(const measuringResult &result);

        /**
         *
         * @return
         */
        measuringResults getResults();

        /**
         *
         * @return
         */
        GSVoid printResults();

    private:

        /**
         *
         */
        clock _clock;

        /**
         *
         */
        time_point _startTimePoint;

        /**
         *
         */
        time_point _endTimePoint;

        /**
         *
         */
        measuringResults _results;
    };

}

#endif //GSLANGUAGE_GS_TIMER_H
