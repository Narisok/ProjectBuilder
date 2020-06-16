#ifndef _FILEBUILDER_HPP_
#define _FILEBUILDER_HPP_

#include "parser.hpp"

enum class sysCallType
{
    compiling,
    linking
};

std::string get_system_call(sysCallType call_type, std::filesystem::path output_path,const std::vector<std::filesystem::path> &files_);


void build_file(std::filesystem::path file, std::filesystem::path build_path);

void link_all_files(std::filesystem::path build_path, std::string output_file_name);

#endif //_FILEBUILDER_HPP_

