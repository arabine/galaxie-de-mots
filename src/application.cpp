#include "application.h"

Application::Application()
{
    mDb.Open("db/lexique.db");
}

std::string Application::GetRandomWord(int nbLetters)
{
    std::string word;

    std::vector<std::vector<Value> > results;
    std::string res = mDb.Query("SELECT mot FROM lexique WHERE lettres=" + std::to_string(nbLetters) + " ORDER BY RANDOM() LIMIT 1;", results);

    if (res.size() == 0)
    {
        // pas d'erreur
        if (results.size() >= 1)
        {
            if (results[0].size() >= 1)
            {
                try {
                     word = std::get<std::string>(results[0][0]);
                } catch (const std::bad_variant_access& ex) {
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
