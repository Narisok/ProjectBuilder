#pragma once

#include <PBheader>

#include <Global>
#include "flag.hpp"

namespace parser
{

    class Parser
    {
    public:
        explicit Parser(const vector<string>& args);

        Parser(const Parser&) = delete;
        Parser(Parser&&);
    
    public:
        Parser& operator=(const Parser&) = delete;
        Parser& operator=(Parser&&) = delete;

    public:
        template<flag::Flag T_Flag>
        inline decay_t<T_Flag>::return_type get(T_Flag && flag);

    private:

    };


    template<flag::Flag T_Flag>
    decay_t<T_Flag>::return_type Parser::get(T_Flag && flag)
    {
        for(auto a : flag.getAliases())
            cout << a << endl;
    }

}