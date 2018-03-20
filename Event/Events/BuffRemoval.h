#ifndef BUFFREMOVAL_H
#define BUFFREMOVAL_H

#include "Event.h"

class Buff;

class BuffRemoval: public Event {
public:
    BuffRemoval(Buff*, const float, const int);

    virtual void act(void) override;
protected:
private:
    Buff* buff;
    int iteration;
};


#endif // BUFFREMOVAL_H
