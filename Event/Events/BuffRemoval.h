#ifndef BUFFREMOVAL_H
#define BUFFREMOVAL_H

#include "Event.h"

class Buff;

class BuffRemoval: public Event {
public:
    BuffRemoval(Buff* buff, const double timestamp, const int iteration);

    void act(void) override;

private:
    Buff* buff;
    int iteration;
};

#endif // BUFFREMOVAL_H
