#ifndef BUFFAPPLICATION_H
#define BUFFAPPLICATION_H

#include "Event.h"

class Buff;

class BuffApplication: public Event {
public:
    BuffApplication(const float, Buff*);

    virtual void act(void) override;
protected:
private:
    Buff* buff;
};


#endif // BUFFAPPLICATION_H
