#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

#include <NII/json>

#include <parser.hpp>


struct A 
{
    std::string str;
};

int main(int argc, char**argv)
{
    ParameterBag parameterBag;

    ParseArguments(parameterBag, argc, argv);

    parameterBag.test_print();

    // std::vector<std::string> vec, vec1;
    // vec.push_back("onehuontehneth");

    // for(auto & a : vec) {
    //     vec1.emplace_back(std::move(a));
    // } 

    // std::cout << "VEC:" << std::endl;
    // for(auto  a : vec) {
    //     std::cout << '\t' << a << std::endl;
    // } 

    // std::cout << "VEC1:" << std::endl;
    // for(auto  a : vec1) {
    //     std::cout << '\t' << a << std::endl;
    // } 

    nii::json::json json;
    
    std::fstream ifstream("test.json");

    std::cout << "Is file open: " << ifstream.is_open() << std::endl;
    

    std::string str((std::istreambuf_iterator<char>(ifstream)), (std::istreambuf_iterator<char>()));
    std::stringstream stream;

    stream << ifstream.rdbuf();

    std::cout << "STR:" << str << std::endl;
    try
    {
        json = str;
    
    
    }
    catch(const char*error_mess)
    {
        std::cerr << error_mess << '\n';
    }
    
    std::cout << json.serialize() << std::endl;

    return 0;
}