/**
 * MIT License
 * Copyright (c) 2019 Anthony Rabine
 */

#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <variant>
#include <string>
#include "sqlite3.h"
#include "gfx-engine.h"

/*****************************************************************************/
class DataBase
{
public:
    DataBase();
    ~DataBase();

    // Local SQLite Database Helpers
    bool Open(const std::string &fileName);
    void Close();
    std::string Query(const std::string &query, std::vector<std::vector<Value> > &results);
    bool Exec(const std::string &query);
    bool BeginTransaction();
    bool Rollback();
    bool EndTransaction();
    bool Vacuum();
private:
    sqlite3 *mDb;
};


#endif // DATABASE_H

//=============================================================================
// End of file DataBase.h
//=============================================================================
