#ifndef _TIME_HPP_
#define _TIME_HPP_

#include <pch>

using namespace std;
using namespace chrono;

inline string time_to_string(int64_t time_count)
{
    auto time_hours = time_count / 1000000000 / 60 / 60 % 24;
    auto time_minutes = time_count / 1000000000 / 60 % 60;
    auto time_seconds = time_count / 1000000000 % 60;
    auto time_milliseconds = time_count / 1000000 % 1000;
    auto time_microseconds = time_count / 1000 % 1000;

    string time;

    if(time_hours > 0) goto SHOW_hours;
    if(time_minutes > 0) goto SHOW_minutes;
    if(time_seconds > 0) goto SHOW_seconds;
    if(time_milliseconds > 0) goto SHOW_milliseconds;
    goto SHOW_microseconds;
    
    

 SHOW_hours:
    time += to_string(time_hours) + "h ";
 SHOW_minutes:
    time += to_string(time_minutes) + "min ";
 SHOW_seconds:
    time += to_string(time_seconds) + "sec " ;
 SHOW_milliseconds:
    time += to_string(time_milliseconds) + "ms ";

 SHOW_microseconds:
    time += to_string(time_microseconds) + "µs";

    return time;
}

#endif //_TIME_HPP_