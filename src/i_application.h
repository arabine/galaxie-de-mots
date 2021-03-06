#ifndef I_APPLICATION_H
#define I_APPLICATION_H

#include <string>

class IApplication
{
public:
    virtual ~IApplication() {

    }

    virtual std::string GetRandomWord(int nbLetters) = 0;
    virtual bool IsWordExists(const std::string &word) = 0;
    virtual bool GetDefinition(const std::string &mot, std::string &sens, std::string &categorie) = 0;

};

#endif // I_APPLICATION_H
