#ifndef BUFFREMOVAL_H
#define BUFFREMOVAL_H

#include "Event.h"

class Buff;

class BuffRemoval: public Event {
public:
    BuffRemoval(Buff*, const double, const int);

    virtual void act(void) override;
protected:
private:
    Buff* buff;
    int iteration;
};


#endif // BUFFREMOVAL_H
