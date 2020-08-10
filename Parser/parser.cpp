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

map<string,string> Parser::flags = {};

map<string,string> Parser::get_aliases() noexcept
{
    map<string,string> aliases;    
    for(auto &flag : supported_flags)
        for(auto alias : flag.aliases)
            aliases[alias] = flag.name;
    return aliases;
}

void Parser::parse(int argc, char** argv) noexcept
{
    map<string, vector<string>> rawFlags;

    map<string,string> aliases = Parser::get_aliases();
    string UNDEFINED_PARAMETERS = "UNDEFINED_PARAMETERS";
    string UNDEFINED_FLAGS = "UNDEFINED_FLAGS";
    string flagName(UNDEFINED_PARAMETERS);

    for(auto i = 1; i < argc; ++i)
    {
        string argument = argv[i];
        
        if (argument[0] == '-') {
            auto search = aliases.find(argument.substr(1));

            if (search == aliases.end()) {
                rawFlags[UNDEFINED_FLAGS].push_back(argument);
                flagName = UNDEFINED_PARAMETERS;
                continue; 
            }

            flagName = search->second;
        } else {
            rawFlags[flagName].push_back(argument);
        }
    }

    for(auto iter = rawFlags.begin(); iter != rawFlags.end(); ++iter)
    {
        cout << iter->first << ": ";
        for(auto a : iter->second)
            cout << a << ' ';
        cout << endl;
    }
}