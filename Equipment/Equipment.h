#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <QString>
#include <QVector>

class Character;
class Item;
class Stats;
class EquipmentDb;
class Weapon;

class Equipment {
public:
    Equipment(EquipmentDb* equipment_db, Character* = nullptr);
    ~Equipment();

    void set_character(Character*);
    void change_setup(const int);

    bool is_dual_wielding(void);

    const Stats* get_stats() const;
    Weapon* get_mainhand(void);
    Weapon* get_offhand(void);
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

    void clear_items_not_available_on_patch();
    EquipmentDb *get_db() const;

    void equip(QVector<Item *> &current, Item*& next, const int eq_slot);
    void unequip(QVector<Item *> &item, const int eq_slot);

    void equip(QVector<Weapon *> &current, Weapon*& next, const int eq_slot);
    void unequip(QVector<Weapon *> &weapon, const int eq_slot);

protected:
private:
    int setup_index;
    EquipmentDb* db;
    Character* pchar;
    QVector<Stats*> stats_from_equipped_gear;
    QVector<Weapon*> mainhand;
    QVector<Weapon*> offhand;
    QVector<Item*> ranged;
    QVector<Item*> head;
    QVector<Item*> neck;
    QVector<Item*> shoulders;
    QVector<Item*> back;
    QVector<Item*> chest;
    QVector<Item*> wrist;
    QVector<Item*> gloves;
    QVector<Item*> belt;
    QVector<Item*> legs;
    QVector<Item*> boots;
    QVector<Item*> ring1;
    QVector<Item*> ring2;
    QVector<Item*> trinket1;
    QVector<Item*> trinket2;
    QVector<Item*> caster_offhand;
    QVector<Item*> relic;

    void add_proc_effects_from_current_setup();
    void remove_proc_effects_from_current_setup();

    void add_proc_effect_from_item(Item*, const int eq_slot);
    void remove_proc_effect_from_item(Item*, const int eq_slot);
};

#endif // EQUIPMENT_H
