#ifndef OBSERVER_H
#define OBSERVER_H

/**
 * @brief The Observer class is an implementation of an observer from the observer pattern.
 * Observes a subject until it notifies the observer.
 */
class Observer {
    public:
        /**
         * @brief Observer constructor.
         */
        Observer() = default;

        /**
         * @brief Observer destructor.
         */
        virtual ~Observer() = default;

        /**
         * @brief Update observer when subject notifies.
         * @param value Value sent by subject.
         */
        virtual void update(int value) = 0;
};

#endif // OBSERVER_H
