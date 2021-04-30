#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std::chrono;

high_resolution_clock::time_point
getMilliCount()
{

return high_resolution_clock::now();

}
 
duration<double, std::milli>
getMilliSpan(high_resolution_clock::time_point t1)
{

  high_resolution_clock::time_point t2 = high_resolution_clock::now();

  duration<double, std::milli> time_span = t2 - t1;

  return time_span;

}


