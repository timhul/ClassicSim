#pragma once

#include <QVector>

#include "Item.h"
#include "Random.h"

class Weapon : public Item {
public:
    Weapon(QString name,
           int item_id,
           Content::Phase phase,
           int type,
           int weapon_slot,
           unsigned min,
           unsigned max,
           double speed,
           EnchantInfo* enchant_info,
           QMap<QString, QString> info = {},
           QVector<QPair<QString, QString>> stats = {},
           QVector<QMap<QString, QString>> procs = {},
           QVector<QMap<QString, QString>> uses = {},
           QVector<QString> special_equip_effects = {},
           QSet<int> mutex_item_ids = {},
           QVector<int> random_affixes = {});
    Weapon(const Weapon* weapon);

    ~Weapon() override;

    int get_weapon_slot() const override;
    int get_weapon_type() const;
    unsigned get_min_dmg() const;
    unsigned get_max_dmg() const;
    unsigned get_random_dmg() const;
    double get_base_weapon_speed() const;
    double get_wpn_dps() const;
    QString get_weapon_type_string() const;
    bool is_2hand() const;

    bool has_temporary_enchant() const;
    void apply_enchant(EnchantName::Name enchant_name, Character* pchar, const int weapon_slot);
    void apply_temporary_enchant(EnchantName::Name enchant_name, Character* pchar, const int enchant_slot);
    void clear_temporary_enchant();
    void enable_druid_form_enchants(Character* pchar, const EnchantName::Name enchant_name, const EnchantName::Name temp_enchant_name);
    void disable_druid_form_enchants();
    void clear_windfury();
    QString get_temporary_enchant_effect() const;
    EnchantName::Name get_temporary_enchant_enum_value() const;
    QString get_temporary_enchant_unique_name() const;

    Enchant* get_temporary_enchant() const;

private:
    Random* random;
    int weapon_type;
    int weapon_slot;
    unsigned min_dmg;
    unsigned max_dmg;
    double weapon_speed;
    Enchant* temporary_enchant;
};
