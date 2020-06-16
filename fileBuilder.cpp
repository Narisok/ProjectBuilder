#include "fileBuilder.hpp"

using namespace std;
namespace fs = filesystem;

string get_system_call(sysCallType type_, fs::path out_,const vector<fs::path>& files_)
{
    string systemCall("g++ ");
    for(auto &a : get_compiler_flags())
        systemCall += a + ' ';

    for(auto &_file_path : files_)
        systemCall += _file_path.string() + ' ';

    switch (type_)
    {
    case sysCallType::compiling:
        systemCall += "-c ";
    break;
    
    case sysCallType::linking:
        for(auto &_lib : get_libs())
            systemCall += _lib + ' ';
    break;
    }

    systemCall += "-o " + out_.string();
    return systemCall;
}

void build_file(fs::path file_, fs::path path_)
{
    auto time_start = high_resolution_clock::now();
    cout << "Compiling file " << file_  << "..." << endl;

    for(auto &a : file_.parent_path())
        path_ /= a;
    
    path_ /= file_.stem().string() + ".o";
    // string systemCall;

    if(fs::exists(path_))
    {
        if(!force_rebuild() && fs::last_write_time(path_) > fs::last_write_time(file_))
            goto EXIT;
    }
    else 
    {
        fs::create_directories(path_.parent_path());
    }

    system( get_system_call(sysCallType::compiling, path_, {file_}).c_str() );

 EXIT:
    auto time_end = high_resolution_clock::now();
    cout << "\t>>it tooks: " << time_to_string((time_end - time_start).count()) << endl;
}

void link_all_files(fs::path path_, string out)
{
    auto time_start = high_resolution_clock::now();
    cout << "Linking..." << endl;

    vector<fs::path> files_to_link;
    for(auto &p : fs::recursive_directory_iterator(path_))
        if(p.path().extension() == ".o")
           files_to_link.push_back( p.path());

    path_ /= out;

    system( get_system_call(sysCallType::linking, path_, files_to_link).c_str() );

    auto time_end = high_resolution_clock::now();
    cout << "\t>>it tooks: " << time_to_string((time_end - time_start).count()) << endl;
}