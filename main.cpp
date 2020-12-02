#include <PBheader>

#include "Parser/parser.hpp"

using parser::Parser;

struct mod
{
    vector<string> aliases = {"a1", "a2", "a3"};
};
template<class T>
concept test = 
    requires {
        &T::push_back;
    };


int main(int args_count, char**args_values)
{
    auto start = high_resolution_clock::now();


    

    auto end = high_resolution_clock::now();
    auto time_count = (end - start).count();

    return 0;
}