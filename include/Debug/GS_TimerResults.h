#ifndef GSLANGUAGE_GS_TIMERRESULTS_H
#define GSLANGUAGE_GS_TIMERRESULTS_H

#include "../Compiler/Util/GS_CrossPlatform.h"

#include "GS_Timer.h"

namespace Debug {

    /**
     * Class for containing timer results before profiling
     */
    class GS_TimerResults {
    public:

        /**
         * Printing results
         */
        static void printTimerResults() {
            Platform::GS_CrossPlatform::setConsoleColor(Platform::GS_CrossPlatform::BLACK, Platform::GS_CrossPlatform::GREEN);

            std::cout << timerResults;

            Platform::GS_CrossPlatform::setConsoleColor(Platform::GS_CrossPlatform::BLACK, Platform::GS_CrossPlatform::LIGHT_GRAY);
        }

        /**
         * Getter for results
         * @return
         */
        static std::string getTimerResults() {
            return timerResults;
        }

        /**
         * Adding result
         * @param result
         */
        static void addTimerResult(std::string result) {
            timerResults += result;
        }

    private:

        /**
         * Timer results
         */
        inline static std::string timerResults;

    };

}

#endif //GSLANGUAGE_GS_TIMERRESULTS_H
