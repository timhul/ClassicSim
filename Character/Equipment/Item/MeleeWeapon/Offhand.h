#ifndef OFFHAND_H
#define OFFHAND_H

#include "Item.h"

class Offhand: public Item {
public:
    int get_item_type() const override;
protected:
private:
};

#endif // OFFHAND_H
