#pragma once
#include <chrono>

class Time
{
	static std::chrono::time_point<std::chrono::system_clock> start_time;
	static std::chrono::time_point<std::chrono::system_clock> last_frame_time;

	static std::chrono::duration<double> app_time;
	static std::chrono::duration<double> delta_time;
public:
	// Returns the amount of time since the app started. In seconds.
	static double AppTime();
	// Returns the amount of time since the last frame. In seconds.
	static double DeltaTime();
private:
	friend class App;
	static void StartTime();
	static void StartFrame();
};