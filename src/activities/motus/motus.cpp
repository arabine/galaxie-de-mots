#include "motus.h"

Motus::Motus(IGameEvent &event, IApplication &app)
    : mEvent(event)
    , mApp(app)
{
    mCurrentWord = "SABLE";
}

std::string Motus::GetNewWordToGuess()
{
    return mApp.GetRandomWord(mNbLettes);
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

    mEvent.NewGame();
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
            size_t pos = wordToGuess.find(word[i]);
            if (pos != std::string::npos )
            {
                // La lettre existe quelque part ailleurs dans le mot
                code[i] = '1';
                wordToGuess[pos] = ' ';
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

std::string Motus::GetLastWord() const
{
    std::string lastWord;

    if (mCurrentTryIndex < mTries.size())
    {
        lastWord = mTries.at(mCurrentTryIndex);
    }

    return lastWord;
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
        valid = mApp.IsWordExists(w);

        if (!valid)
        {
            mEvent.Message("Le mot " + w + " n'existe pas dans le dictionnaire");
        }
    }

    return valid;
}

void Motus::Submit()
{
    if ((mCurrentTryIndex < GetNbLines()) && !mIsEnd)
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
