#ifndef EQUIPMENTDB_H
#define EQUIPMENTDB_H

#include <QObject>
#include <QFile>
#include <QXmlStreamReader>
#include <QVector>

class MeleeWeapon;

class EquipmentDb: public QObject {
public:
    EquipmentDb(QObject* parent = 0);

    ~EquipmentDb();

protected:
private:
    void read_equipment_file(const QString &path);
    void weapon_file_handler(QXmlStreamReader &reader);

    void info_element_reader(const QXmlStreamAttributes &attrs, QMap<QString, QString> &item);
    void dmg_range_element_reader(const QXmlStreamAttributes &attrs, QMap<QString, QString> &item);
    void class_restriction_element_reader(const QXmlStreamAttributes &attrs, QMap<QString, QString> &item);
    void stats_element_reader(QXmlStreamReader &reader, QMap<QString, QString> &item);
    void proc_element_reader(QXmlStreamReader &reader, QVector<QMap<QString, QString>> &procs);

    void add_mandatory_attr(const QXmlStreamAttributes &attrs, const QString& attr, QMap<QString, QString> &item);
    void add_attr(const QXmlStreamAttributes &attrs, const QString& attr, QMap<QString, QString> &item);

    void create_item(QMap<QString, QString> &item, QVector<QMap<QString, QString>> &procs);

    void create_melee_weapon(QMap<QString, QString> &item, QVector<QMap<QString, QString>> &procs);
    void create_ranged_weapon(QMap<QString, QString> &item, QVector<QMap<QString, QString>> &procs);

    void add_onehand_weapon(MeleeWeapon* weapon);
    void add_twohand_weapon(MeleeWeapon* weapon);

    void extract_info(QMap<QString, QString> &item, QMap<QString, QString> &info);
    void extract_stats(QMap<QString, QString> &item, QMap<QString, QString> &stats);

    void extract(QVector<QString> handled_keys, QMap<QString, QString> &source, QMap<QString, QString> &target);

    void warn_remaining_keys(QMap<QString, QString> &item);

    int get_weapon_type(const QString &type);

    QVector<MeleeWeapon*> onehand_axes;
    QVector<MeleeWeapon*> onehand_swords;
    QVector<MeleeWeapon*> onehand_maces;
    QVector<MeleeWeapon*> onehand_fists;
    QVector<MeleeWeapon*> onehand_daggers;
    QVector<MeleeWeapon*> onehand_weapons;

    QVector<MeleeWeapon*> twohand_weapons;

};

#endif // EQUIPMENTDB_H
