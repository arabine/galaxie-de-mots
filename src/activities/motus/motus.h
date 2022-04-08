#ifndef MOTUS_H
#define MOTUS_H

#include <string>
#include <vector>
#include <random>

class Motus
{
public:
    Motus();

    void Initialize();

    /**
     * @brief TestWord
     * @param word le mot à tester
     *
     * Pour chaque lettre du mot, on retourne la codification suivante :
     *   0: la lettre n'est pas dans le mot à trouver
     *   1: bon mais mal placé
     *   2: bon et bien placé
     *
     * @return le statut de chaque lettre
     */
    std::string TestWord(const std::string &word) const;
    std::string GetTry(int32_t i) const;
    bool IsTryValidated(int32_t i) const;

    std::string GetWord() const { return mCurrentWord; }

    uint32_t GetNbLines() const;
    uint32_t GetNbLetters() const;

    bool IsEnd() const { return mIsEnd; }
    bool IsWin() const { return mWin; }

    void AppendLetter(char c);
    void RemoveLast();
    void Submit(std::string &message);

private:
    std::string mCurrentWord;
    uint32_t mCurrentTryIndex;
    uint32_t mCurrentLetterCounter;
    bool mWin;
    bool mIsEnd;

    std::vector<std::string> mTries;
    std::vector<bool> mValidated;
    bool IsSubmitValid(std::string &message) const;
    std::string GetNewWordToGuess();
};

#endif // MOTUS_H
