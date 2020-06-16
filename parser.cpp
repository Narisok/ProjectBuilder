#include "parser.hpp"


using namespace std;
namespace fs = filesystem;

enum class flags
{
    output_folder,

    compiler_flags,
    files_to_build,
    folders_to_build,
    libs,
    libs_path,
    include_path,

    force_rebuild,
    
    none
};

map<flags,vector<string>> Flags_Values = {
      {flags::output_folder,{}}

    , {flags::compiler_flags,{}}
    , {flags::files_to_build,{}}
    , {flags::folders_to_build,{}}
    , {flags::libs,{}}
    , {flags::libs_path,{}}
    , {flags::include_path,{}}

    , {flags::force_rebuild,{}}
};

map<string,flags> Flag_Names = {
      {"-output_folder",    flags::output_folder}
    , {"-out",              flags::output_folder}
    , {"-o",                flags::output_folder}

    , {"-flags",            flags::compiler_flags}

    , {"-files",            flags::files_to_build }

    , {"-folders",          flags::folders_to_build}

    , {"-libs",             flags::libs}
    , {"-l",                flags::libs}

    , {"-libs_path",        flags::libs_path}
    , {"-L",                flags::libs_path}

    , {"-include_path",     flags::include_path}
    , {"-I",                flags::include_path}

    , {"-force_rebuild",    flags::force_rebuild}
    , {"-f",                flags::force_rebuild}
};

map<flags,bool> Enabled_Flags = {
      {flags::force_rebuild, false}
};


void parse_arguments(int argc, char ** argv)
{
    flags selected_flag{flags::none};
    for(int i = 1; i < argc; ++i)
    {
        string cur_arg = argv[i];
        if(*cur_arg.begin() == '-')
        {
            if(Flag_Names.contains(cur_arg)) selected_flag = Flag_Names[cur_arg];
            else {selected_flag = flags::none; cerr << "Bad flag \">" << cur_arg << "<\"" << endl;}
            if(Enabled_Flags.contains(selected_flag)) Enabled_Flags[selected_flag] = true;
        }
        else
        {
            if(selected_flag != flags::none) Flags_Values[selected_flag].push_back(cur_arg);
            else cerr << "Bad option \">" << cur_arg << "<\"" << endl;
        }
    }
}

const set<string>& get_compiler_flags()
{
    static set<string> compiler_flags{};
    static bool compiler_flags_parsed = false;

    if(compiler_flags_parsed) return compiler_flags;


    for(auto &a : Flags_Values[flags::compiler_flags])
        compiler_flags.insert(std::move( a.insert(0,1,'-') ));

    compiler_flags_parsed = true;
    return compiler_flags;
}

const pair<fs::path, string>& get_output_path_and_name()
{
    static pair<fs::path, string> result{};
    static bool get_out_path_parsed = false;

    if(get_out_path_parsed) return result;

    fs::path out_path;
    string out_name;

    auto iter = Flags_Values[flags::output_folder].begin();
    if(iter != Flags_Values[flags::output_folder].end())
    {
        out_path = (*iter);
        out_name = out_path.filename();

        //If out_name has only spaces
        if( all_of(out_name.cbegin(), out_name.cend(), [](const char ch)->bool{return isspace(ch);}) )
            out_name = "a.out";

        out_path = out_path.parent_path();
    }
    else { out_name = "a.out"; }
    
    out_path /= "Build";

    bool isDebug = get_compiler_flags().contains("-g");
    if(isDebug) out_path /= "Debug";
    else out_path /= "Release";

    // if(!fs::exists(out_path))
    //     if(!fs::create_directories(out_path))
    //         throw string("ERROR: can't create directory >>") + out_path.string();

    result.first = std::move(out_path);
    result.second = std::move(out_name);

    get_out_path_parsed = true;
    return result;
}

const vector<fs::path>& get_files_to_build()
{
    static vector<fs::path> Files_to_Build = {};
    static bool Files_to_Build_parsed = false;

    if(Files_to_Build_parsed) return Files_to_Build;

    for(auto &file_ : Flags_Values[flags::files_to_build])
    {
        Files_to_Build.emplace_back(file_);
    }

    for(auto &folder_ : Flags_Values[flags::folders_to_build])
    {
        if(!fs::exists(folder_)) throw string("Error: folder doen't exist >>") + folder_;

        for(auto &entry_ : fs::recursive_directory_iterator(folder_))
        {
            // if(entry_.is_regular_file())
            // {
            auto extension_ = entry_.path().extension();
            if(extension_ == ".c" || extension_ == ".cpp")
                Files_to_Build.emplace_back(entry_.path());
            // }
        }
    }

    Files_to_Build_parsed = true;
    return Files_to_Build;
}

const vector<string>& get_libs()
{
    static vector<string> libs = {};
    static bool get_libs_parsed = false;

    if(get_libs_parsed) return libs;
    
    for(auto &a : Flags_Values[flags::libs])
        libs.push_back("-l" + move(a));
    
    get_libs_parsed = true;
    return libs;
}

bool force_rebuild()
{
    return Enabled_Flags[flags::force_rebuild];
}