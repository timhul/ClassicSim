#ifndef BUFFREMOVAL_H
#define BUFFREMOVAL_H

#include "Event.h"

class Buff;

class BuffRemoval: public Event {
public:
    BuffRemoval(Buff*, const float);

    virtual void act(void) override;
protected:
private:
    Buff* buff;
};


#endif // BUFFREMOVAL_H
