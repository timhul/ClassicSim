#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "Item.h"

class Equipment {
public:
    Item* get_mainhand(void) { return mainhand; }
    Item* get_offhand(void) { return offhand; }
    Item* get_ranged(void) { return ranged; }
    Item* get_head(void) { return head; }
    Item* get_neck(void) {  return neck; }
    Item* get_shoulders(void) { return shoulders; }
    Item* get_back(void) { return back; }
    Item* get_chest(void) { return chest; }
    Item* get_wrist(void) { return wrist; }
    Item* get_gloves(void) { return gloves; }
    Item* get_belt(void) { return belt; }
    Item* get_legs(void) { return legs; }
    Item* get_boots(void) { return boots; }
    Item* get_ring1(void) { return ring1; }
    Item* get_ring2(void) { return ring2; }
    Item* get_trinket1(void) { return trinket1; }
    Item* get_trinket2(void) { return trinket2; }
protected:
private:
    Item* mainhand;
    Item* offhand;
    Item* ranged;
    Item* head;
    Item* neck;
    Item* shoulders;
    Item* back;
    Item* chest;
    Item* wrist;
    Item* gloves;
    Item* belt;
    Item* legs;
    Item* boots;
    Item* ring1;
    Item* ring2;
    Item* trinket1;
    Item* trinket2;
};

#endif // EQUIPMENT_H
