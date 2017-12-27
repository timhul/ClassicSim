#ifndef MAINHAND_H
#define MAINHAND_H

#include "Item.h"

class Mainhand: public Item {
public:
    int get_item_type() const override;
protected:
private:
};

#endif // MAINHAND_H
