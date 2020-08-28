#ifndef SUBJECT_H
#define SUBJECT_H

#include "observer.h"

#include "vector"

class Subject
{
public:
    Subject();

    ~Subject();

    std::vector<Observer*> observers;

    void addObserver(Observer* observer);

    void notify();

    void notify(int value);

};

#endif // SUBJECT_H
