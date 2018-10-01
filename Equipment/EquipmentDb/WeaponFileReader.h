#ifndef WEAPONFILEREADER_H
#define WEAPONFILEREADER_H

#include "ItemFileReader.h"

class WeaponFileReader: public ItemFileReader {
public:
    void weapon_file_handler(QXmlStreamReader &reader, QVector<Item*> &items);

protected:
private:

    void dmg_range_element_reader(const QXmlStreamAttributes &attrs, QMap<QString, QString> &item);
    void create_melee_weapon(QVector<Item*> &items, QMap<QString, QString> &item_map, QVector<QPair<QString, QString>> &stats, QVector<QMap<QString, QString>> &procs);
    void create_ranged_weapon(QVector<Item*> &items, QMap<QString, QString> &item, QVector<QPair<QString, QString>> &stats, QVector<QMap<QString, QString>> &procs);
    int get_weapon_type(const QString &type);
    QString get_type_string(const QString &slot, const QString &type);

};

#endif // WEAPONFILEREADER_H
