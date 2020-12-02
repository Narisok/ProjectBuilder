#include <PBheader>

#include "Global"

using parser::Flag;

namespace Global
{
    /*
     * Supported flags global variable
     */
    vector<Flag> Parser::Supported_Flags {
        Flag{
            .name = "compiler",
            .aliases = {"compiler"},
            .default_values = {"g++"},
            .max_count = 1
        }
        , Flag{
            .name = "build directory",
            .aliases = {"build_dir"},
            .default_values = {"Build"},
            .max_count = 1,
            .process = [](string arg)->any {
                return make_any<fs::path>(move(arg));
            }
        }
        , Flag{
            .name = "output path",
            .aliases = {"out", "o"},
            .default_values = {"Build/Output/exec.app"},
            .max_count = 1,
            .process = [](string arg)->any {
                return make_any<fs::path>(move(arg));
            }
        }
        , Flag{
            .name = "compiler flags",
            .aliases = {"compiler_flags", "flags"},
            .default_values = {
                "-std=c++2a", 
                "-Wall",
                "-Wextra",
                "-Wpedantic",
                "-Wsign-promo",
                "-Wold-style-cast",
                "-Woverloaded-virtual" ,
                "-Wnon-virtual-dtor" ,
                "-Wfloat-equal" ,
                "-Wshadow=compatible-local" ,
                "-Wno-dangling-else",
                "-Wno-unused"
            },
            .process = [](string arg)->any {
                return make_any<string>('-' + move(arg) + ' ');
            }
        }
    };


    /*
     * Other global variable
     */
}