#ifndef SUBJECT_H
#define SUBJECT_H

#include "observer.h"

#include "vector"

/**
 * @brief The Subject class is an implementation of an subject from the observer pattern.
 * Notifies all its observers when an event occurs.
 */
class Subject{
    public:
         /**
         * @brief Subject constructor.
         */
        Subject();

        /**
         * @brief List of observers of this subject.
         */
        std::vector<Observer*> observers;

        /**
         * @brief Add an observer to this subject.
         * @param observer Observer to be added.
         */
        void addObserver(Observer* observer);

        /**
         * @brief Notify al observers.
         * @param value Code to send to observers.
         */
        void notify(int value);

};

#endif // SUBJECT_H
