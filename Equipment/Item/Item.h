#ifndef ITEM_H
#define ITEM_H

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
class Spell;
class Stats;

int get_slot_int(const QString& slot_string);

class Item: public PhaseRequirer {
public:
    Item(QString name,
         int item_id,
         Content::Phase phase,
         QMap<QString, QString> info,
         QVector<QPair<QString, QString>> stats,
         QVector<QMap<QString, QString>> procs = {},
         QVector<QMap<QString, QString>> use = {},
         QVector<QString> item_modifications = {});
    Item(const Item* item);
    virtual ~Item();

    int get_item_id() const;
    int get_item_slot() const;
    int get_item_type() const;
    virtual int get_weapon_slot() const;

    void apply_equip_effect(Character*, const int eq_slot);
    void remove_equip_effect();

    QString get_name() const;
    QString get_value(const QString& key) const;
    QString get_base_stat_tooltip() const;
    QString get_equip_effect_tooltip() const;
    QString get_weapon_side_name(const int eq_slot) const;

    const Stats* get_stats() const;
    void set_stat(const QString& key, const QString& value);
    void set_stats(const QVector<QPair<QString, QString>> &stats);

    unsigned get_stat_value_via_flag(const ItemStats) const;

    bool has_enchant() const;
    void apply_enchant(EnchantName::Name enchant_name, Character *pchar);
    void clear_enchant();
    QString get_enchant_name() const;
    QString get_enchant_effect() const;
    EnchantName::Name get_enchant_enum_value() const;

    bool available_for_faction(AvailableFactions::Name faction) const;
    bool available_for_class(const QString& class_name) const;

protected:
    Character* pchar;
    QString name;
    QString source;
    QString quality;
    QString icon;
    AvailableFactions::Name valid_faction;
    QSet<QString> class_restrictions;
    QMap<QString, QString> info;
    QVector<QString> base_tooltip_stats;
    QVector<QString> equip_effects_tooltip_stats;
    QVector<QMap<QString, QString>> procs_map;
    QVector<QMap<QString, QString>> use_map;
    QVector<QPair<QString, QString>> stats_key_value_pairs;
    QVector<Proc*> active_procs;
    QVector<Spell*> use_spells;
    QVector<QString> item_modifications;
    QMap<ItemStats, unsigned> item_stat_values;
    Stats* stats;
    Enchant* enchant;

    void set_uses();
    void set_procs(const int eq_slot);
    void call_item_modifications(const bool activate = true) const;
    void call_modifications_by_specific_name(const QString& name, const bool activate) const;
    void call_spell_modifications(const QString& spell_name, const bool activate) const;
    void call_buff_modifications(const QString& buff_name, const bool activate) const;

    int slot;
    int item_type;
    const int item_id;
    void set_item_slot(const QMap<QString, QString>& info);
    void set_item_type(const QMap<QString, QString>& info);
    void set_class_restrictions(const QMap<QString, QString>& info);
    void set_faction();
    int get_type_int(const QString& type_string);
    void unsupported_stat(const QString& stat);
    QString get_tooltip(const QVector<QString>&) const;

    void add_default_proc_sources(QVector<ProcInfo::Source>& proc_sources, const int eq_slot);
    MagicSchool get_magic_school(const QString& name);
};

#endif // ITEM_H
