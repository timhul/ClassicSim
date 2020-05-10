#pragma once

#include <QMap>
#include <QSet>
#include <QString>
#include <QVector>

#include "AvailableFactions.h"
#include "EnchantName.h"
#include "ItemNamespace.h"
#include "ItemStatsEnum.h"
#include "MagicSchools.h"
#include "PhaseRequirer.h"
#include "ProcInfo.h"

class Character;
class Enchant;
class Proc;
class RandomAffix;
class Spell;
class Stats;

int get_slot_int(const QString& slot_string);

class Item : public PhaseRequirer {
public:
    Item(QString name,
         const int item_id,
         Content::Phase phase,
         EnchantInfo* enchant_info,
         QMap<QString, QString> info,
         QVector<QPair<QString, QString>> stats,
         QVector<QMap<QString, QString>> procs = {},
         QVector<QMap<QString, QString>> use = {},
         QVector<QString> item_modifications = {},
         QVector<QString> special_equip_effects = {},
         QSet<int> mutex_item_ids = {},
         QVector<int> random_affixes = {});
    Item(const Item* item);
    virtual ~Item();

    int get_item_slot() const;
    int get_item_type() const;
    virtual int get_weapon_slot() const;

    void apply_equip_effect(Character*, const int eq_slot);
    void remove_equip_effect();

    void enable_proc_effects();
    void disable_proc_effects();

    QString get_value(const QString& key) const;
    QString get_base_stat_tooltip() const;
    QString get_equip_effect_tooltip() const;
    QString get_weapon_side_name(const int eq_slot, const QString& display_name) const;

    const Stats* get_stats() const;
    void set_stat(const QString& key, const QString& value);
    void set_stats(const QVector<QPair<QString, QString>>& stats);

    unsigned get_stat_value_via_flag(const ItemStats) const;

    bool has_enchant() const;
    void apply_enchant(EnchantName::Name enchant_name, Character* pchar);
    void clear_enchant();
    QString get_enchant_effect() const;
    QString get_enchant_unique_name() const;
    EnchantName::Name get_enchant_enum_value() const;
    Enchant* get_enchant() const;

    // Random affixes
    bool can_have_random_affix() const;
    bool has_random_affix() const;
    RandomAffix* get_random_affix() const;
    QVector<int> get_possible_random_affixes() const;
    void set_random_affix(RandomAffix* affix);

    bool available_for_faction(AvailableFactions::Name faction) const;
    bool available_for_class(const QString& class_name) const;

    const QString base_name;
    QString name;
    const int item_id;

protected:
    Character* pchar;
    QString source;
    QString quality;
    QString icon;
    AvailableFactions::Name valid_faction;
    QSet<QString> class_restrictions;
    QMap<QString, QString> info;
    QVector<QString> base_tooltip_stats;
    QVector<QString> equip_effects_tooltip_stats;
    QVector<QString> special_equip_effects;
    QVector<QMap<QString, QString>> procs_map;
    QVector<QMap<QString, QString>> use_map;
    QVector<QPair<QString, QString>> stats_key_value_pairs;
    QVector<Proc*> active_procs;
    QVector<Spell*> use_spells;
    QVector<QString> item_modifications;
    QSet<int> mutex_item_ids;
    QMap<ItemStats, unsigned> item_stat_values;
    Stats* stats;
    EnchantInfo* enchant_info;
    Enchant* enchant;

    // Random affixes
    RandomAffix* random_affix;
    QVector<int> possible_random_affixes;

    void set_uses();
    void set_procs(const int eq_slot);
    void call_item_modifications(const bool activate = true) const;
    void call_modifications_by_specific_name(const QString& name, const bool activate) const;
    void call_spell_modifications(const QString& spell_name, const bool activate) const;
    void call_buff_modifications(const QString& buff_name, const bool activate) const;
    void clear_mutex_ids();

    int slot;
    int item_type;
    void set_item_slot(const QMap<QString, QString>& info);
    void set_item_type(const QMap<QString, QString>& info);
    void set_class_restrictions(const QMap<QString, QString>& info);
    void set_faction();
    int get_type_int(const QString& type_string);
    void unsupported_stat(const QString& stat);
    QString get_tooltip(const QVector<QString>&) const;

    void add_default_proc_sources(QVector<ProcInfo::Source>& proc_sources, const int eq_slot);
    void add_proc_sources_from_map(QVector<ProcInfo::Source>& proc_sources, const QMap<QString, QString>& proc_map, const int eq_slot);
    MagicSchool get_magic_school(const QString& name);
};
