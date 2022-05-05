/**
 * MIT License
 * Copyright (c) 2019 Anthony Rabine
 */

#include <cctype>
#include <iostream>
#include <string>
#include <sstream>
#include "xlog.h"
#include "database.h"

/*****************************************************************************/
DataBase::DataBase()
    : mDb(nullptr)
{

}
/*****************************************************************************/
DataBase::~DataBase()
{
    Close();
}
/*****************************************************************************/
void DataBase::Close()
{
    if (mDb != nullptr)
    {
        sqlite3_close(mDb);
        mDb = nullptr;
    }
}
/*****************************************************************************/
bool DataBase::Open(const std::string &fileName)
{
    bool valid = false;

    int rc = sqlite3_open(fileName.c_str(), &mDb);
    if (rc == 0)
    {
        valid = true;
    }
    else
    {
        LOG_ERROR("Impossible d'ouvrir la BDD");
    }
    return valid;
}
/*****************************************************************************/
std::string DataBase::Query(const std::string &query, std::vector<std::vector<Value> > &results)
{
    sqlite3_stmt *statement;
    std::string error;

    if (sqlite3_prepare_v2(mDb, query.c_str(), -1, &statement, nullptr) == SQLITE_OK)
    {
        int cols = sqlite3_column_count(statement);

        while (true)
        {
            int result = sqlite3_step(statement);
            if (result == SQLITE_ROW)
            {
                std::vector<Value> values;

                for (int col = 0; col < cols; col++)
                {
                    int type = sqlite3_column_type(statement, col);

                    // Limitation here: we only support integer and strings
                    if (type == SQLITE_INTEGER)
                    {
                        std::int32_t intVal = sqlite3_column_int(statement, col);
                        values.push_back(intVal);
                    }
                    else if (type == SQLITE_TEXT)
                    {
                        std::string strVal(reinterpret_cast<const char *>(sqlite3_column_text(statement, col)));
                        values.push_back(strVal);
                    }
                    else if (type == SQLITE_FLOAT)
                    {
                        double dblVal = sqlite3_column_double(statement, col);
                        values.push_back(dblVal);
                    }
                    else
                    {
                        // Not supported, push invalid value
                        Value invalid;
                        values.push_back(invalid);
                    }
                }
                results.push_back(values);
            }
            else
            {
                break;
            }
        }
        sqlite3_finalize(statement);
    }
    std::string errmsg = sqlite3_errmsg(mDb);
    if (errmsg != "not an error")
    {
        error = query + " " + errmsg;
    }

    return error;
}

bool DataBase::Exec(const std::string &query)
{
    return sqlite3_exec(mDb, query.c_str(), nullptr, nullptr, nullptr) == SQLITE_OK;
}

bool DataBase::BeginTransaction()
{
    // 'db' is the pointer you got from sqlite3_open*
    return sqlite3_exec(mDb, "BEGIN TRANSACTION;", nullptr, nullptr, nullptr) == SQLITE_OK;
}

bool DataBase::Rollback()
{
    return sqlite3_exec(mDb, "ROLLBACK TRANSACTION;", nullptr, nullptr, nullptr) == SQLITE_OK;
}

bool DataBase::EndTransaction()
{
    // Any (modifying) SQL commands executed here are not committed until at the you call:
    return sqlite3_exec(mDb, "END TRANSACTION;", nullptr, nullptr, nullptr) == SQLITE_OK;
}

bool DataBase::Vacuum()
{
    return sqlite3_exec(mDb, "VACUUM;", nullptr, nullptr, nullptr) == SQLITE_OK;
}


//=============================================================================
// End of file DataBase.cpp
//=============================================================================
