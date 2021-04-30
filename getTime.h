#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std::chrono;

high_resolution_clock::time_point getMilliCount();
high_resolution_clock::time_point start;

duration<double, std::milli>
getMilliSpan(high_resolution_clock::time_point);

duration<double, std::milli> milliSecondsElapsed;

