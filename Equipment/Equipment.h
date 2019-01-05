#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <QString>
#include <QVector>

class Character;
class Item;
class SetBonusControl;
class Stats;
class EquipmentDb;
class Weapon;

class Equipment {
public:
    Equipment(EquipmentDb* equipment_db, Character* pchar);
    ~Equipment();

    void change_setup(const int);
    void unequip_all();

    bool is_dual_wielding();

    const Stats* get_stats() const;
    Weapon* get_mainhand() const;
    Weapon* get_offhand() const;
    Item* get_ranged() const;
    Item* get_head() const;
    Item* get_neck() const;
    Item* get_shoulders() const;
    Item* get_back() const;
    Item* get_chest() const;
    Item* get_wrist() const;
    Item* get_gloves() const;
    Item* get_belt() const;
    Item* get_legs() const;
    Item* get_boots() const;
    Item* get_ring1() const;
    Item* get_ring2() const;
    Item* get_trinket1() const;
    Item* get_trinket2() const;
    Item* get_caster_offhand() const;
    Item* get_relic() const;

    void set_mainhand(const int item_id);
    void set_offhand(const int item_id);
    void set_ranged(const int item_id);
    void set_head(const int item_id);
    void set_neck(const int item_id);
    void set_shoulders(const int item_id);
    void set_back(const int item_id);
    void set_chest(const int item_id);
    void set_wrist(const int item_id);
    void set_gloves(const int item_id);
    void set_belt(const int item_id);
    void set_legs(const int item_id);
    void set_boots(const int item_id);
    void set_ring1(const int item_id);
    void set_ring2(const int item_id);
    void set_trinket1(const int item_id);
    void set_trinket2(const int item_id);
    void set_caster_offhand(const int item_id);
    void set_relic(const int item_id);

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

    void reequip_items();
    void clear_items_not_available_for_faction();
    SetBonusControl* get_set_bonus_control() const;

    void equip(Item*& current, Item* next, const int eq_slot);
    void unequip(Item*& item, const int eq_slot);

    void equip(Weapon*& current, Weapon* next, const int eq_slot);
    void unequip(Weapon*& weapon, const int eq_slot);

private:
    int setup_index;
    EquipmentDb* db;
    Character* pchar;
    SetBonusControl* set_bonuses;
    QVector<Stats*> stats_from_equipped_gear;
    QVector<QVector<int>> item_setups;
    Weapon* mainhand;
    Weapon* offhand;
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

    static const int NO_EQUIPPED_ITEM = -1;

    int get_stored_item_id_for_slot(const int equipment_slot) const;
};

#endif // EQUIPMENT_H
