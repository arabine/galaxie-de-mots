/**
 * MIT License
 * Copyright (c) 2019 Anthony Rabine
 */

#ifndef OBSERVER_H
#define OBSERVER_H

#include <list>
#include <algorithm>
#include <cstdint>

template <class T>
class Observer
{
public:
    Observer(std::uint8_t mask = 0xFFU)
        : mMask(mask)
    {

    }
    void SetMask(std::uint8_t mask) { mMask = mask; }
    std::uint8_t GetMask() { return mMask; }

    virtual void Update(const T &info) = 0;

private:
    std::uint8_t mMask;
};

template <class T>
class Subject
{

public:
    void Attach(Observer<T> &observer)
    {
        mList.push_back(&observer);
    }

    void Detach(Observer<T> &observer)
    {
        mList.remove(&observer);
    }

    void Notify(const T &info, std::uint8_t flags = 0xFFU)
    {
        for (typename std::list< Observer<T> *>::iterator it = mList.begin(); it != mList.end(); ++it)
        {
            if (((*it)->GetMask() & flags) != 0U)
            {
                (*it)->Update(info);
            }
        }
    }

    void Clear() { mList.clear(); }

private:
    std::list< Observer<T> *> mList;
};


#endif // OBSERVER_H

//=============================================================================
// End of file Observer.h
//=============================================================================
