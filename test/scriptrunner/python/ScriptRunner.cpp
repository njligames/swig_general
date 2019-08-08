
#include "ScriptRunner.h"
#include <Python.h>

static std::vector<std::string> split(const char *str, char c = ' ')
{
    std::vector<std::string> result;
    
    do
    {
        const char *begin = str;
        
        while(*str != c && *str)
            str++;
        
        result.push_back(std::string(begin, str));
    } while (0 != *str++);
    
    return result;
}

static std::vector<std::string> lines(const std::string &code)
{
    return split(code.c_str(), '\n');
}

void ScriptRunner::run_internal(const std::string &script_code)
{
    Py_Initialize();
    
    /*
     import sys
     sys.path.insert(0, '/Users/james.folk/work/evr-internals-api/test/python/macOS/')
    */
    
    PyRun_SimpleString("import sys");
    const std::string setPath("sys.path.insert(0, '" + *mRunDirectory + "')");
    PyRun_SimpleString(setPath.c_str());
    
    std::vector<std::string> string_vector = lines(script_code);
    
    for(auto i = 0; i < string_vector.size(); i++)
    {
        std::replace(string_vector[i].begin(), string_vector[i].end(), '\r', ' ');
        std::replace(string_vector[i].begin(), string_vector[i].end(), '\n', ' ');
        
        PyRun_SimpleString(string_vector[i].c_str());
    }
    
    Py_Finalize();
}
