#include "Time.h"
#include <assert.h>

std::chrono::time_point<std::chrono::system_clock> Time::start_time;
std::chrono::time_point<std::chrono::system_clock> Time::last_frame_time;
std::chrono::duration<double> Time::app_time;
std::chrono::duration<double> Time::delta_time;
#if _DEBUG
static bool initialized = false;
#endif

double Time::AppTime()
{
    assert(initialized);
    return app_time.count();
}

double Time::DeltaTime()
{
    assert(initialized);
    return delta_time.count();
}

void Time::StartTime()
{
#if _DEBUG
    initialized = true;
#endif

    const auto now = std::chrono::system_clock::now();
    start_time = now;
    last_frame_time = now;
#if _DEBUG
    app_time   = std::chrono::duration<double>(0.0);
    delta_time = std::chrono::duration<double>(0.0);
#endif
}

void Time::StartFrame()
{
    auto now = std::chrono::system_clock::now();

    app_time   = now - start_time;
    delta_time = now - last_frame_time;
     
    last_frame_time = now;
}
