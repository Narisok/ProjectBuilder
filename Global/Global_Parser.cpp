#include <PBheader>

#include "Global"

using parser::Flag;

namespace Global
{
    pair<bool, map<string, string>> Parser::alias_to_name{false,{}};

    void Parser::parse_flags()
    {
        if(alias_to_name.first == false)
            for(auto & flag : Parser::Supported_Flags)
                for(auto & alias : flag.aliases)
                    alias_to_name.second[alias] = flag.name;
    }

    string Parser::AliasToName(const string & alias)
    {
        parse_flags();
        return alias_to_name.second.at(alias);
    }

    bool Parser::AliasHasName(const string & alias)
    {
        parse_flags();
        return alias_to_name.second.find(alias) != alias_to_name.second.end();
    }

    Flag Parser::FlagFromName(const string & name)
    {
        static map<string, Flag> flag_from_name;
        if(flag_from_name.size() == 0)
            for(auto & flag : Parser::Supported_Flags)
                flag_from_name[flag.name] = flag;
            
        return flag_from_name.at(name);
    }
}