
#include "common.h"


std::string replaceStringAll(std::string str, const std::string &old, const std::string &new_s)
{
    if(!old.empty())
    {
        size_t pos = str.find(old);
        while ((pos = str.find(old, pos)) != std::string::npos) {
            str = str.replace(pos, old.length(), new_s);
            pos += new_s.length();
        }
    }
    return str;
}
