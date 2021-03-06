#ifndef _SYSTEMCALL_HPP_
#define _SYSTEMCALL_HPP_

#include "logger.hpp"
#include "parser.hpp"

enum class sysCallType
{
      compiling
    , linking

    // , compiling_static_lib
    // , compiling_dynamic_lib
    // , linking_static_lib
    // , linking_dynamic_lib
};

void system_call(sysCallType call_type, std::filesystem::path output_path,const std::vector<std::filesystem::path>& files_, std::string & stream_);

#endif //_SYSTEMCALL_HPP_

