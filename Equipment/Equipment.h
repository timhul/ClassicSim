#pragma once

#include <QString>
#include <QVector>

#include "EnchantName.h"

class Character;
class EquipmentDb;
class Item;
class Projectile;
class Quiver;
class RandomAffix;
class RandomAffixes;
class SetBonusControl;
class Stats;
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
    Weapon* get_ranged() const;
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
    Projectile* get_projectile() const;
    Quiver* get_quiver() const;

    void set_mainhand(const int item_id, RandomAffix* random_affix = nullptr);
    void set_offhand(const int item_id, RandomAffix* random_affix = nullptr);
    void set_ranged(const int item_id, RandomAffix* random_affix = nullptr);
    void set_head(const int item_id, RandomAffix* random_affix = nullptr);
    void set_neck(const int item_id, RandomAffix* random_affix = nullptr);
    void set_shoulders(const int item_id, RandomAffix* random_affix = nullptr);
    void set_back(const int item_id, RandomAffix* random_affix = nullptr);
    void set_chest(const int item_id, RandomAffix* random_affix = nullptr);
    void set_wrist(const int item_id, RandomAffix* random_affix = nullptr);
    void set_gloves(const int item_id, RandomAffix* random_affix = nullptr);
    void set_belt(const int item_id, RandomAffix* random_affix = nullptr);
    void set_legs(const int item_id, RandomAffix* random_affix = nullptr);
    void set_boots(const int item_id, RandomAffix* random_affix = nullptr);
    void set_ring1(const int item_id, RandomAffix* random_affix = nullptr);
    void set_ring2(const int item_id, RandomAffix* random_affix = nullptr);
    void set_trinket1(const int item_id);
    void set_trinket2(const int item_id);
    void set_caster_offhand(const int item_id, RandomAffix* random_affix = nullptr);
    void set_relic(const int item_id);
    void set_projectile(const int item_id);
    void set_quiver(const int idem_id);

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
    void clear_projectile();
    void clear_quiver();

    void reequip_items();
    void clear_items_not_available_for_faction();
    void clear_item_id_if_equipped_in_any_slot(const int item_id);
    SetBonusControl* get_set_bonus_control() const;

    void equip(Item*& current, Item* next, const int eq_slot);
    void unequip(Item*& item, const int eq_slot);

    void equip(Weapon*& current, Weapon* next, const int eq_slot);
    void unequip(Weapon*& weapon, const int eq_slot);

    void equip(Projectile*& current, Projectile* next, const int eq_slot);
    void unequip(Projectile*& current, const int eq_slot);

    void equip(Quiver*& current, Quiver* next, const int eq_slot);
    void unequip(Quiver*& current, const int eq_slot);

    void druid_bear_form_switch_to_paws();
    void druid_cat_form_switch_to_claws();
    void druid_switch_to_normal_weapon();

private:
    int setup_index;
    Character* pchar;

    // Databases
    EquipmentDb* db;
    RandomAffixes* random_affixes;
    SetBonusControl* set_bonuses;

    // Equipments
    Weapon* mainhand;
    Weapon* offhand;
    Weapon* ranged;
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
    Projectile* projectile;
    Quiver* quiver;

    Weapon* druid_form_mh_storage {nullptr};
    Weapon* druid_form_oh_storage {nullptr};
    EnchantName::Name mh_enchant {EnchantName::Name::NoEnchant};
    EnchantName::Name mh_temp_enchant {EnchantName::Name::NoEnchant};

    QVector<Stats*> stats_from_equipped_gear;
    QVector<QVector<int>> item_setups;
    QVector<QVector<int>> item_affixes;
    QVector<QVector<EnchantName::Name>> item_enchants;
    QVector<QVector<EnchantName::Name>> item_temp_enchants;

    static const int NO_EQUIPPED_ITEM = -1;

    int get_stored_item_id_for_slot(const int equipment_slot) const;
    int get_stored_random_affix_id_for_slot(const int equipment_slot) const;
    void apply_current_enchants();
    void store_current_enchants();
    EnchantName::Name get_current_enchant_enum_value(Item* item) const;
    EnchantName::Name get_current_temp_enchant_enum_value(Weapon* weapon) const;
};
