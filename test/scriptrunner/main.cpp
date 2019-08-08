#include "ScriptRunner.h"

#include <string>
#include <fstream>
#include <iostream>

using namespace std;

#ifdef SWIGPYTHON
#define MAIN (TEST_DIRECTORY"/main.py")
#endif

static std::string retrieveScriptContent(const std::string &scriptFile)
{
    std::string script("");
    
    std::ifstream ifs (scriptFile.c_str(), std::ifstream::in);
    
    char c = ifs.get();
    
    while (ifs.good())
    {
        script += c;
        c = ifs.get();
    }
    
    ifs.close();
    
    return script;
}

int main(int nArg, const char *cArg[])
{
    const std::string script(retrieveScriptContent(MAIN));
    ScriptRunner myOb(script);
    myOb.setRunDirectory(TEST_DIRECTORY);
    myOb.run();
    
    return 0;
}


