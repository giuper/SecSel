#include <iostream>
#include <ctime>
#include <ratio>
#include <chrono>

using namespace std::chrono;


high_resolution_clock::time_point getMilliCount();
duration<double, std::milli> getMilliSpan(high_resolution_clock::time_point t1);

high_resolution_clock::time_point start;
duration<double, std::milli> time_span;

int main ()
{
 
  //high_resolution_clock::time_point t1 = high_resolution_clock::now();
  start = getMilliCount();
 
  std::cout << "printing out 1000 stars...\n";
  for (int i=0; i<1000; ++i) std::cout << "*";
  std::cout << std::endl;
 
  //high_resolution_clock::time_point t2 = high_resolution_clock::now();
  //duration<double, std::milli> time_span = t2 - t1;
  time_span = getMilliSpan(start);
 
  std::cout << "It took me " << time_span.count() << " milliseconds.";
  std::cout << std::endl;
 
  return 0;
}

