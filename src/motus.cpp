#include "motus.h"
#include <random>

struct Lexique {
    const char* word;
    double occurence;
};

#include "lexique_5_letters.inc"

static const uint32_t nbWords5Letters = sizeof(lexique_5_letters) / sizeof(Lexique);


// Returns random integer in closed range [low, high].
class UniformRandomInt
{
    std::random_device _rd{};
    std::mt19937 _gen{_rd()};
    std::uniform_int_distribution<int> _dist;

    public:
        UniformRandomInt() {
            set(1, 10);
        }
        UniformRandomInt(int low, int high) {
            set(low, high);
        }

        // Set the distribution parameters low and high.
        void set(int low, int high) {
            std::uniform_int_distribution<int>::param_type param(low, high);
            _dist.param(param);
        }

        // Get random integer.
        int get() {
            return _dist(_gen);
        }
};




Motus::Motus()
{
    mCurrentWord = "TIERS";
}

std::string Motus::GetNewWordToGuess()
{
    UniformRandomInt rng(0, nbWords5Letters - 1);
    int index = rng.get();
    return lexique_5_letters[index].word;
}

void Motus::Initialize()
{
    std::string triedWord;

    mCurrentWord = GetNewWordToGuess();

    for (int i = 0; i < GetNbLetters(); i++)
    {
        triedWord.push_back(' ');
    }

    mTries.clear();
    for (int i = 0; i < GetNbLines(); i++)
    {
        mTries.push_back(triedWord);
        mValidated.push_back(false);
    }

    mCurrentTryIndex = 0;
    mCurrentLetterCounter = 0;
}

std::string Motus::TestWord(const std::string &word) const
{
    std::string code;

    int idx = 0;
    for (auto &c : word)
    {
        if (mCurrentWord.find(c) != std::string::npos )
        {
            // la lettre existe
            if (mCurrentWord[idx] == c)
            {
                code.push_back('2');
            }
            else
            {
                code.push_back('1');
            }
        }
        else
        {
            code.push_back('0');
        }
        idx++;
    }

    return code;
}

std::string Motus::GetTry(int32_t i) const
{
    std::string triedWord;
    for (int i = 0; i < GetNbLetters(); i++)
    {
        triedWord.push_back(' ');
    }

    if (i < mTries.size())
    {
        triedWord = mTries[i];
    }
    return triedWord;
}

bool Motus::IsTryValidated(int32_t i) const
{
    if (i < mValidated.size())
    {
        return mValidated[i];
    }
    else
    {
        return false;
    }
}

uint32_t Motus::GetNbLines() const
{
    return 6;
}

uint32_t Motus::GetNbLetters() const
{
    return 5;
}

void Motus::AppendLetter(char c)
{
    if ((mCurrentLetterCounter < GetNbLetters()) && (mCurrentTryIndex < GetNbLines()))
    {
        mTries.at(mCurrentTryIndex)[mCurrentLetterCounter] = c;
        mCurrentLetterCounter++;
    }
}

void Motus::RemoveLast()
{
    if (mCurrentLetterCounter > 0)
    {
        mTries.at(mCurrentTryIndex)[mCurrentLetterCounter - 1] = ' ';
        mCurrentLetterCounter--;
    }
}

bool Motus::IsSubmitValid(std::string &message) const
{
    bool valid = true;
    // Le mot de doit pas contenir d'espace
    for (int i = 0; i < mTries.at(mCurrentTryIndex).size(); i++)
    {
        if (mTries.at(mCurrentTryIndex)[i] == ' ')
        {
            valid = false;
            message = "Veuillez entrer un mot de 5 lettres";
            break;
        }
    }

    // le mot doit exister au dictionnaire
    if (valid)
    {
        bool found = false;
        for (int i = 0; i < nbWords5Letters; i++)
        {
            if (lexique_5_letters[i].word == mTries.at(mCurrentTryIndex))
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            valid = false;
            message = "Le mot n'existe pas dans le dictionnaire";
        }
    }

    return valid;
}

bool Motus::Submit(std::string &message)
{
    if (mCurrentTryIndex < GetNbLines())
    {
        if (IsSubmitValid(message))
        {
            mValidated[mCurrentTryIndex] = true;
            mCurrentTryIndex++;
            mCurrentLetterCounter = 0;
        }
    }
}
