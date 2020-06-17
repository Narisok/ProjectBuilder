#include "fileBuilder.hpp"


using namespace std;
namespace fs = filesystem;

using namespace chrono;

int main(int args_count, char**args_values)
{
    auto start = high_resolution_clock::now();
    cout << "Build start ..." << endl;

    parse_arguments(args_count, args_values);
 
    auto &[out_build_path,out_exec_path] = get_output_path_and_name();

    for(auto &a : get_files_to_build())
    try{
        build_file(a,out_build_path);
    }catch(string str) {cerr << str << endl;}catch(const std::exception &ex){cerr << ex.what() << endl;}

    try{
        link_all_files(out_build_path,out_exec_path);
    }catch(string str) {cerr << str << endl;}catch(const std::exception &ex){cerr << ex.what() << endl;}
    
    auto end = high_resolution_clock::now();
    auto time_count = (end - start).count();
    
    cout << "Build tooks: " << time_to_string(time_count) << endl;
    
    return 0;
}