#ifndef _FILEBUILDER_HPP_
#define _FILEBUILDER_HPP_

#include "parser.hpp"

void build_file(std::filesystem::path file, std::filesystem::path build_path);

void link_all_files(std::filesystem::path build_path, std::string output_file_name);

#endif //_FILEBUILDER_HPP_

