#include <string>
#include <vector>
#include <fstream>

#ifndef _SCRIPTRUNNER_H_
#define _SCRIPTRUNNER_H_

class ScriptRunner
{
    std::string *mSource;
    std::string *mRunDirectory;
    
public:
    ScriptRunner(const std::string script = "") :
    mSource(new std::string(script)),
    mRunDirectory(new std::string("")){}
    
    ScriptRunner(const ScriptRunner&rhs) :
    mSource(new std::string(*(rhs.mSource))),
    mRunDirectory(new std::string(*(rhs.mRunDirectory))){}
    
    virtual ~ScriptRunner() {
        delete mRunDirectory;
        delete mSource;
    }
    
    ScriptRunner &operator=(const ScriptRunner &rhs)
    {
        if(this != &rhs)
        {
            *mSource = *rhs.mSource;
        }
        return *this;
    }
    ScriptRunner &operator=(const std::string &rhs)
    {
        *mSource = rhs;
        
        return *this;
    }
    operator std::string() const {return *mSource;}
    
    void run(const std::string &script_code = "")
    {
        if(script_code == std::string(""))
        {
            run_internal(*mSource);
        }
        else
        {
            run_internal(script_code);
        }
    }
    
    void setRunDirectory(const std::string &runDirectory)
    {
        *mRunDirectory = runDirectory;
    }
    
    const std::string &getRunDirectory(const std::string &runDirectory)const
    {
        return *mRunDirectory;
    }
protected:
    virtual void run_internal(const std::string &script_code);
    
};

#endif
