#ifndef APPLICATION_H
#define APPLICATION_H

#include "database.h"

class Application
{
public:
    Application();

    std::string GetRandomWord(int nbLetters);

private:
    DataBase mDb;
};

#endif // APPLICATION_H
