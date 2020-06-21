#ifndef _SYSTEMCALL_HPP_
#define _SYSTEMCALL_HPP_

#include "logger.hpp"
#include "parser.hpp"

enum class sysCallType
{
    compiling,
    linking
};

void system_call(sysCallType call_type, std::filesystem::path output_path,const std::vector<std::filesystem::path>& files_, std::string & stream_);

#endif //_SYSTEMCALL_HPP_

