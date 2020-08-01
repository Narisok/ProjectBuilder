#include "pch.hpp"

#include "systemCall.hpp"

using namespace std;
namespace fs = filesystem;

void system_call(sysCallType call_type, fs::path output_path,const vector<fs::path>& files_, string & stream_)
{
    string systemCall("2>&1 g++ -fdiagnostics-color=always ");
    
    for(auto &a : get_compiler_flags())
        systemCall += a + ' ';
    
    
    switch (call_type)
    {
    case sysCallType::compiling:
        if(dynamic_library()) systemCall += "-fPIC ";

        for(auto &a : get_include_path())
            systemCall += '\'' + a.string() + "' ";
        
    break;

    case sysCallType::linking:
        if(static_library())
        {
            systemCall = string("ar rcs ") + "'" + output_path.string() + "' ";
            for(auto &_file_path : files_)
                systemCall += '\'' + _file_path.string() + "' ";
            goto Call;
        }
        if(dynamic_library()) systemCall += "-shared ";

        systemCall += get_linker_compiler_flag() + ' ';
        for(auto &a : get_libs_path())
            systemCall += '\'' + a.string() + "' ";
        
    break;
    }
    

    for(auto &_file_path : files_)
        systemCall += '\'' + _file_path.string() + "' ";

    switch (call_type)
    {
    case sysCallType::compiling:
        systemCall += "-c ";
    break;

    case sysCallType::linking:
        for(auto &_lib : get_libs())
            systemCall += _lib + ' ';
    break;
    }

    systemCall += "-o '" + output_path.string() + '\'';


 Call:
    FILE *cmd = popen(systemCall.c_str(),"r");
    char buff[4096];

    while(!feof(cmd))
        if(fgets(buff,4096,cmd) != NULL) stream_ += buff;

    pclose(cmd);
}