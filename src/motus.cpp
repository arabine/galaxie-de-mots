#include "motus.h"

Motus::Motus()
{
    mCurrentWord = "TIERS";
}

void Motus::Initialize()
{
    std::string triedWord;

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

bool Motus::IsSubmitValid() const
{
    bool valid = true;

    // Le mot de doit pas contenir d'espace
    for (int i = 0; i < mTries.at(mCurrentTryIndex).size(); i++)
    {
        if (mTries.at(mCurrentTryIndex)[i] == ' ')
        {
            valid = false;
        }
    }

    // FIXME: le mot doit exister au dictionnaire

    return valid;
}

void Motus::Submit()
{
    if (mCurrentTryIndex < GetNbLines())
    {
        if (IsSubmitValid())
        {
            mValidated[mCurrentTryIndex] = true;
            mCurrentTryIndex++;
            mCurrentLetterCounter = 0;
        }
    }
}
