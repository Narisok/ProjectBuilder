#ifndef _FILEBUILDER_HPP_
#define _FILEBUILDER_HPP_

#include "pch.hpp"
#include "parser.hpp"
#include "logger.hpp"




atomic<bool> & has_error_files();
atomic<bool> & has_warning_files();

std::pair<resultState,int64_t>  build_file(std::filesystem::path file, std::filesystem::path build_path, std::string & stream_);

std::pair<resultState,int64_t> link_all_files(std::filesystem::path build_path, std::filesystem::path output_file_path, std::string & stream_);

void thread_build_file(const std::vector<std::filesystem::path> * files_pool, std::filesystem::path build_path);

#endif //_FILEBUILDER_HPP_

