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




Motus::Motus(IEvent &event)
    : mEvent(event)
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
    mValidated.clear();
    for (int i = 0; i < GetNbLines(); i++)
    {
        mTries.push_back(triedWord);
        mValidated.push_back(false);
    }

    mCurrentTryIndex = 0;
    mCurrentLetterCounter = 0;
    mWin = false;
    mIsEnd = false;

    mEvent.InitializeGame();
}

std::string Motus::TestWord(const std::string &word) const
{
    std::string code;
    code.reserve(word.size());
    code.assign(word.size(), '0');

    std::string wordToGuess = mCurrentWord; // copie en local car on va la modifier

    // Une première boucle est nécessaire pour tester les lettres bonnes et bien placées
    for (int i = 0; i < word.size(); i++)
    {
        if (mCurrentWord[i] == word[i])
        {
            // la lettre existe et bien placée
            code[i] = '2';
            // On retire la lettre du mot à deviner
            // Comme ça les mal placées seront bien déterminées en cas de même lettre multiple dans le mot
            wordToGuess[i] = ' ';
        }
    }

    // La deuxième boucle indique les lettres mal placées
    for (int i = 0; i < word.size(); i++)
    {
        if (code[i] != '2')
        {
            if (wordToGuess.find(word[i]) != std::string::npos )
            {
                // La lettre existe quelque part ailleurs dans le mot
                code[i] = '1';
                wordToGuess[i] = ' ';
            }
        }
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
    if ((mCurrentLetterCounter < GetNbLetters()) && (mCurrentTryIndex < GetNbLines()) && !mWin)
    {
        mTries.at(mCurrentTryIndex)[mCurrentLetterCounter] = toupper(c);
        mCurrentLetterCounter++;

        mEvent.AppendLetter(c);
    }
}

void Motus::RemoveLast()
{
    if (mCurrentLetterCounter > 0)
    {
        mTries.at(mCurrentTryIndex)[mCurrentLetterCounter - 1] = ' ';
        mCurrentLetterCounter--;

        mEvent.RemoveLast();
    }
}

bool Motus::IsSubmitValid() const
{
    bool valid = true;
    std::string w = mTries.at(mCurrentTryIndex);

    // Le mot de doit pas contenir d'espace
    for (int i = 0; i < w.size(); i++)
    {
        if (w[i] == ' ')
        {
            valid = false;
            mEvent.Message("Veuillez entrer un mot de 5 lettres");
            break;
        }
    }

    // le mot doit exister au dictionnaire
    if (valid)
    {
        bool found = false;
        for (int i = 0; i < nbWords5Letters; i++)
        {
            if (lexique_5_letters[i].word == w)
            {
                found = true;
                break;
            }
        }
        if (!found)
        {
            valid = false;
            mEvent.Message("Le mot " + w + " n'existe pas dans le dictionnaire");
        }
    }

    return valid;
}

void Motus::Submit()
{
    if (mCurrentTryIndex < GetNbLines())
    {
        if (IsSubmitValid())
        {
            mValidated[mCurrentTryIndex] = true;

            std::string word = GetTry(mCurrentTryIndex);
            std::string codage = TestWord(word);

            int counter = 0;
            for (int i = 0; i < codage.size(); i++)
            {
                if (codage[i] == '2')
                {
                    counter++;
                }
            }

            mEvent.Validate(codage);

            // Prepare next line (or end of game)
            mCurrentTryIndex++;
            mCurrentLetterCounter = 0;

            // Condition de victoire ou d'échec
            if (counter == GetNbLetters())
            {
                mIsEnd = true;
                mWin = true;
            }
            else if (mCurrentTryIndex == GetNbLines())
            {
                mIsEnd = true;
                mWin = false;
            }

            if (mIsEnd)
            {
                if (mWin)
                {
                    mEvent.Message(mTextWin);
                }
                else
                {
                    mEvent.Message(mTextLost + mCurrentWord);
                }
            }
        }
    }
}
