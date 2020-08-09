#ifndef _PARSER_HPP_
#define _PARSER_HPP_

#include <pch>

#include "show_time.hpp"

void parse_arguments(int argc, char ** argv);

//std::filesystem::path(1) -> output parent path
//std::filesystem::path(2) -> output file name
const std::pair<std::filesystem::path, std::filesystem::path> & get_output_path_and_name();

const std::vector<std::filesystem::path> & get_files_to_build();

const std::set<std::string> & get_compiler_flags();

const std::set<std::string> & get_linker_flags();
std::string get_linker_compiler_flag();

const std::vector<std::string> & get_libs();

const std::vector<std::filesystem::path>& get_libs_path();

const std::vector<std::filesystem::path>& get_include_path();

bool force_rebuild();
bool static_library();
bool dynamic_library();

#endif //_PARSER_HPP_

