#include <parser.hpp>


void ParseArguments(ParameterBag& bag, int argc, char**argv)
{
    std::string key("no_key");
    std::vector<std::string> values;
    for(int i = 1; i < argc; ++i) {
        std::string argument = argv[i];

        try {
            if(argument.at(0) == '-') {
                //primary arg
                bag.addParameter(std::make_pair(std::move(key), std::move(values)));

                if(argument.at(1) != '-' && argument.size() > 2) {
                    key = argument.substr(0,2);
                    values.emplace_back(argument.substr(2));
                } else {
                    key = std::move(argument);
                }
            } else {
                //sub arg
                values.emplace_back(std::move(argument));
            }
        } catch (const std::out_of_range& ex) {
            //nu pizdec
            values.emplace_back(std::move(argument));
        }
    }
    bag.addParameter(std::make_pair(std::move(key), std::move(values)));
}