#include <PBheader>

#include "parser.hpp"

vector<flag> Parser::supported_flags = {
    flag{
        .name = "compiler",
        .aliases = {"compiler"},
        .default_values = {"g++"},
        .max_count = 1,
        .get_flags = [](vector<string> & vec)->string{
            return vec[0];
        }
    }
    , flag{
        .name = "build directory",
        .aliases = {"build_dir", "out_dir", "out", "o"},
        .default_values = {"Build"},
        .max_count = 1,
        .get_flags = [](vector<string> & vec)->string{
            return vec[0];
        }
    }
};