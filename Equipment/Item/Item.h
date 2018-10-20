#ifndef ITEM_H
#define ITEM_H

#include <QString>
#include <QMap>
#include <QVector>
#include <assert.h>
#include "ItemNamespace.h"
#include "ItemStatsEnum.h"
#include "ProcInfo.h"
#include "EnchantName.h"
#include "MagicSchools.h"

class Enchant;
class Stats;
class Character;
class Proc;

int get_slot_int(const QString& slot_string);

class Item {
public:
    Item(QString _name, QVector<QPair<QString, QString>> _stats, QMap<QString, QString> _info,
         QVector<QMap<QString, QString>> _procs = {});
    Item(const Item* item);
    virtual ~Item();

    virtual int get_item_slot(void) const;
    int get_item_type(void) const;
    virtual int get_weapon_slot(void) const;

    void apply_equip_effect(Character*, const int eq_slot);
    void remove_equip_effect(const int eq_slot);

    QString get_name(void) const;
    QString get_value(const QString& key) const;
    QString get_base_stat_tooltip() const;
    QString get_equip_effect_tooltip() const;
    QString get_weapon_side_name(const int eq_slot) const;

    const Stats* get_stats() const;
    void set_stat(const QString& key, const QString& value);
    void set_stats(const QVector<QPair<QString, QString>> &stats);

    int get_stat_value_via_flag(const ItemStats) const;

    bool has_enchant() const;
    void apply_enchant(EnchantName::Name enchant_name, Character *pchar);
    void clear_enchant();
    QString get_enchant_name() const;
    QString get_enchant_effect() const;
    EnchantName::Name get_enchant_enum_value() const;

protected:
    QString name;
    QString patch;
    QString source;
    QString quality;
    QMap<QString, QString> info;
    QVector<QString> base_tooltip_stats;
    QVector<QString> equip_effects_tooltip_stats;
    QVector<QMap<QString, QString>> procs_map;
    QVector<QPair<QString, QString>> stats_key_value_pairs;
    QMap<int, QVector<Proc*>> proc_map;
    QMap<ItemStats, int> item_stat_values;
    Stats* stats;
    Enchant* enchant;

    void set_procs(QVector<QMap<QString, QString>>& procs, Character *pchar, const int eq_slot);

    int slot{};
    int item_type{};
    void set_item_slot(const QMap<QString, QString>& info);
    void set_item_type(const QMap<QString, QString>& info);
    int get_type_int(const QString& type_string);
    void unsupported_stat(const QString& stat);
    QString get_tooltip(const QVector<QString>&) const;

    void add_default_melee_proc_sources(QVector<ProcInfo::Source>& proc_sources, const int eq_slot);
    MagicSchool get_magic_school(const QString& name);

private:
};

#endif // ITEM_H
