#ifndef ITEM_H
#define ITEM_H

#include <QString>
#include <QMap>
#include <QVector>
#include <assert.h>
#include "ItemNamespace.h"
#include "ItemStatsEnum.h"

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

    void apply_equip_effect(Character*, const int eq_slot);
    void remove_equip_effect(const int eq_slot);

    QString get_name(void) const;
    QString get_value(const QString& key) const;
    QString get_base_stat_tooltip() const;
    QString get_equip_effect_tooltip() const;

    const Stats* get_stats() const;
    void set_stat(const QString& key, const QString& value);
    void set_stats(const QVector<QPair<QString, QString>> &stats);

    int get_stat_value_via_flag(const ItemStats) const;

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

    void set_procs(QVector<QMap<QString, QString>>& procs, Character *pchar, const int eq_slot);
    bool proc_info_complete(QMap<QString, QString> & proc);

    int slot{};
    int item_type{};
    void set_item_slot(const QMap<QString, QString>& info);
    void set_item_type(const QMap<QString, QString>& info);
    int get_type_int(const QString& type_string);
    void unsupported_stat(const QString& stat);
    QString get_tooltip(const QVector<QString>&) const;

private:
};

#endif // ITEM_H
