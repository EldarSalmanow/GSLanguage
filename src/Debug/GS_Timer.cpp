#include <GS_Timer.h>

namespace Debug {

    GSVoid GS_Timer::start() {
        _startTimePoint = _clock.now();
    }

    GSVoid GS_Timer::stop() {
        _endTimePoint = _clock.now();
    }

    GS_Timer::duration GS_Timer::result() {
        return std::chrono::duration_cast<GS_Timer::duration>(_endTimePoint - _startTimePoint);
    }

    GSVoid GS_Timer::addResult(const GS_Timer::measuringResult &result) {
        _results.emplace_back(result);
    }

    GS_Timer::measuringResults GS_Timer::getResults() {
        return _results;
    }

    GSVoid GS_Timer::printResults() {
        Platform::GS_CrossPlatform::setConsoleColor(Platform::ConsoleColor::GREEN);

        for (auto &result : _results) {
            std::cout << result << std::endl;
        }

        Platform::GS_CrossPlatform::resetConsoleColor();
    }

}