#include "subject.h"

Subject::Subject()
{
    this->observers = std::vector<Observer*>();
}

Subject::~Subject()
{
    for(Observer* observer : this->observers) {
        delete observer;
    }
}

void Subject::addObserver(Observer* observer)
{
    this->observers.push_back(observer);
}

void Subject::notify()
{
    for(Observer* observer : this->observers) {
        observer->update();
    }
}

void Subject::notify(int value)
{
    for(Observer* observer : this->observers) {
        observer->update(value);
    }
}
