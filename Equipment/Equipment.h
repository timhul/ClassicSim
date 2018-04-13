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
    void set_ranged(const QString &name);
    void set_head(const QString &name);
    void set_neck(const QString &name);
    void set_shoulders(const QString &name);
    void set_back(const QString &name);
    void set_chest(const QString &name);
    void set_wrist(const QString &name);
    void set_gloves(const QString &name);
    void set_belt(const QString &name);
    void set_legs(const QString &name);
    void set_boots(const QString &name);
    void set_ring1(const QString &name);
    void set_ring2(const QString &name);
    void set_trinket1(const QString &name);
    void set_trinket2(const QString &name);
    void set_caster_offhand(const QString &name);
    void set_relic(const QString &name);

    void clear_mainhand();
    void clear_offhand();
    void clear_ranged();
    void clear_head();
    void clear_neck();
    void clear_shoulders();
    void clear_back();
    void clear_chest();
    void clear_wrist();
    void clear_gloves();
    void clear_belt();
    void clear_legs();
    void clear_boots();
    void clear_ring1();
    void clear_ring2();
    void clear_trinket1();
    void clear_trinket2();
    void clear_caster_offhand();
    void clear_relic();

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
