#ifndef APPLICATION_H
#define APPLICATION_H

#include "database.h"
#include "i_application.h"

class Application : public IApplication
{
public:
    Application();

    virtual std::string GetRandomWord(int nbLetters) override;
    virtual bool IsWordExists(const std::string &word) override;
    virtual bool GetDefinition(const std::string &mot, std::string &sens, std::string &categorie) override;

private:
    DataBase mDb;
};

#endif // APPLICATION_H
