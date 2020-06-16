#include "fileBuilder.hpp"

using namespace std;
namespace fs = filesystem;

void build_file(fs::path file_, fs::path path_)
{
    auto time_start = high_resolution_clock::now();
    cout << "building file " << file_  << "..." << endl;

    for(auto &a : file_.parent_path())
        path_ /= a;
    
    path_ /= file_.stem().string() + ".o";
    string systemCall;

    if(fs::exists(path_))
    {
        if(!force_rebuild() && fs::last_write_time(path_) > fs::last_write_time(file_))
            goto EXIT;
    }
    else 
    {
        fs::create_directories(path_.parent_path());
    }


    systemCall += "g++ -c ";
    for(auto &a : get_compiler_flags())
    {
        systemCall += a + ' ';
    }
    systemCall += file_.string() + " -o " + path_.string();

    system(systemCall.c_str());

 EXIT:
    auto time_end = high_resolution_clock::now();
    cout << "\t>>it tooks: " << time_to_string((time_end - time_start).count()) << endl;
}

void link_all_files(fs::path path_, string out)
{
    auto time_start = high_resolution_clock::now();
    cout << "Linking..." << endl;
    string systemCall;

    systemCall += "g++ ";
    for(auto &a : get_compiler_flags())
    {
        systemCall += a + ' ';
    }

    for(auto &p : fs::recursive_directory_iterator(path_))
        if(p.path().extension() == ".o")
           systemCall += p.path().string() + ' ';

    path_ /= out;

    systemCall += " -o " + path_.string();

    system(systemCall.c_str());

    auto time_end = high_resolution_clock::now();
    cout << "\t>>it tooks: " << time_to_string((time_end - time_start).count()) << endl;
}