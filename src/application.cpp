#include "application.h"

Application::Application()
{

#ifdef ANDROID
    std::string path = "/data/data/eu.d8s.galaxie/databases/lexique.db";
#else
    std::string path = "db/lexique.db";
#endif

    mDb.Open(path);
}

std::string Application::GetRandomWord(int nbLetters)
{
    std::string word;

    std::vector<std::vector<Value> > results;
    std::string res = mDb.Query("SELECT motupp FROM lexique WHERE lettres=" + std::to_string(nbLetters) + " ORDER BY RANDOM() LIMIT 1;", results);

    if (res.size() == 0)
    {
        // pas d'erreur
        if (results.size() >= 1)
        {
            if (results[0].size() >= 1)
            {
                try
                {
                     word = std::get<std::string>(results[0][0]);
                }
                catch (const std::bad_variant_access& ex)
                {
                    std::cout << ex.what() << '\n' << std::endl;
                }
            }
        }
    }
    else
    {
        std::cout << "[APP] " << res << std::endl;
    }

    return word;
}

bool Application::GetDefinition(const std::string &mot, std::string &sens, std::string &categorie)
{
    bool success = false;

    std::vector<std::vector<Value> > results;
    std::string res = mDb.Query("SELECT sens, categorie FROM lexique WHERE motupp='" + mot + "';", results);

    if (res.size() == 0)
    {
        // pas d'erreur
        if (results.size() >= 1)
        {
            if (results[0].size() >= 2)
            {
                try
                {
                     sens = std::get<std::string>(results[0][0]);
                     categorie = std::get<std::string>(results[0][1]);
                     success = true;
                }
                catch (const std::bad_variant_access& ex)
                {
                    std::cout << ex.what() << '\n' << std::endl;
                }
            }
        }
    }
    else
    {
        std::cout << "[APP] " << res << std::endl;
    }

    return success;
}


bool Application::IsWordExists(const std::string &word)
{
    bool exists = false;

    std::vector<std::vector<Value> > results;
    std::string res = mDb.Query("SELECT * FROM lexique WHERE motupp='" + word + "';", results);

    if (res.size() == 0)
    {
        // pas d'erreur
        if (results.size() >= 1)
        {
            if (results[0].size() >= 1)
            {
                exists = true;
            }
        }
    }
    else
    {
        std::cout << "[APP] " << res << std::endl;
    }

    return exists;
}
