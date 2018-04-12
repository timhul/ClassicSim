#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include "Item.h"
#include "MeleeWeapon.h"

class EquipmentDb;

class Equipment {
public:
    Equipment();
    ~Equipment();

    bool is_dual_wielding(void);

    MeleeWeapon* get_mainhand(void);
    MeleeWeapon* get_offhand(void);
    Item* get_ranged(void);
    Item* get_head(void);
    Item* get_neck(void);
    Item* get_shoulders(void);
    Item* get_back(void);
    Item* get_chest(void);
    Item* get_wrist(void);
    Item* get_gloves(void);
    Item* get_belt(void);
    Item* get_legs(void);
    Item* get_boots(void);
    Item* get_ring1(void);
    Item* get_ring2(void);
    Item* get_trinket1(void);
    Item* get_trinket2(void);
    Item* get_caster_offhand(void);
    Item* get_relic(void);

    void set_mainhand(const QString &name);
    void set_offhand(const QString &name);
    void set_ranged(Item*);
    void set_head(Item*);
    void set_neck(Item*);
    void set_shoulders(Item*);
    void set_back(Item*);
    void set_chest(Item*);
    void set_wrist(Item*);
    void set_gloves(Item*);
    void set_belt(Item*);
    void set_legs(Item*);
    void set_boots(Item*);
    void set_ring1(Item*);
    void set_ring2(Item*);
    void set_trinket1(Item*);
    void set_trinket2(Item*);
    void set_caster_offhand(Item*);
    void set_relic(Item*);

    void patch_changed();
    EquipmentDb *get_db() const;

protected:
private:
    EquipmentDb* db;
    MeleeWeapon* mainhand;
    MeleeWeapon* offhand;
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
    Item* caster_offhand;
    Item* relic;
};

#endif // EQUIPMENT_H
