#ifndef TWOHANDER_H
#define TWOHANDER_H

#include "Item.h"

class TwoHander: public Item {
public:
    int get_item_type() const override;
protected:
private:
};

#endif // TWOHANDER_H
