#ifndef SUBJECT_H
#define SUBJECT_H
#include <vector>
class Observer;

class Subject {
    std::vector<Observer*> observers;
    public:
        Subject();
        void attach( Observer *o );
        void detach( Observer *o );
        virtual void notifyObservers();
        virtual ~Subject() = 0;
};

#endif