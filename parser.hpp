#ifndef _PARSER_HPP_
#define _PARSER_HPP_

#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <utility>
#include <filesystem>
#include <algorithm>
#include <cctype>

#include "show_time.hpp"

void parse_arguments(int argc, char ** argv);

//std::filesystem::path -> output parent path
//std::string           -> output file name
std::pair<std::filesystem::path, std::string> & get_output_path_and_name();

std::vector<std::filesystem::path> & get_files_to_build();

std::set<std::string> & get_compiler_flags();

bool force_rebuild();

#endif //_PARSER_HPP_

