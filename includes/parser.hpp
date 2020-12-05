#include <map>
#include <string>
#include <vector>
#include <iostream>


struct ParameterBag
{
 using Container = std::map<std::string, std::vector<std::string>>;

public:
    inline void addParameter(Container::value_type value) {
        auto iter = parameters.find(value.first);
        if(iter != parameters.end()) {
            for( auto & a : value.second) {
                iter->second.emplace_back(std::move(a));
            }
        } else {
            parameters.insert(std::move(value));
        }
    }

    inline Container::node_type fetchParameter(Container::key_type key) {
        return parameters.extract(key);
    }

    inline void test_print() {
        std::cout << "Parameter bag: ||>\n";
        for(auto value : parameters) {
            std::cout << ">" << value.first << "<" << ": ";
            for(auto a : value.second) {
                std::cout << "|" << a << "| ";
            }
            std::cout << '\n';
        }
    }

private:
    Container parameters;
};


void ParseArguments(ParameterBag& bag, int argc, char**argv);