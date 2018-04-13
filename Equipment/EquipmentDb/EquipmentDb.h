#ifndef EQUIPMENTDB_H
#define EQUIPMENTDB_H

#include <QObject>
#include <QFile>
#include <QXmlStreamReader>
#include <QVector>
#include <QVersionNumber>

class Item;
class MeleeWeapon;

class EquipmentDb: public QObject {
public:
    EquipmentDb(QObject* parent = 0);

    ~EquipmentDb();

    MeleeWeapon* get_melee_weapon(const QString &name);
    Item* get_ranged(const QString &name);
    Item* get_head(const QString &name);
    Item* get_neck(const QString &name);
    Item* get_shoulders(const QString &name);
    Item* get_back(const QString &name);
    Item* get_chest(const QString &name);
    Item* get_wrist(const QString &name);
    Item* get_gloves(const QString &name);
    Item* get_belt(const QString &name);
    Item* get_legs(const QString &name);
    Item* get_boots(const QString &name);
    Item* get_ring1(const QString &name);
    Item* get_ring2(const QString &name);
    Item* get_trinket1(const QString &name);
    Item* get_trinket2(const QString &name);

    void set_patch(const QString &current_patch);
    bool item_valid_for_current_patch(const QString &item_patch);

    const QVector<Item *> &get_mh_slot_items() const;
    const QVector<Item *> &get_slot_items(const QString &slot) const;

    void add_melee_weapon(MeleeWeapon* wpn);

protected:
private:
    void read_equipment_files();

    QVersionNumber current_patch;

    void set_weapons(QVector<Item*> &mixed_items);
    void set_items(QVector<Item*> &mixed_items, QVector<Item *> &sorted, const int slot);

    void set_patch_for_slot(QVector<Item*> &total_slot_items, QVector<Item*> &patch_slot_items);

    QVector<Item*> mh_slot_items;
    QVector<Item*> current_patch_mh_slot_items;

    QVector<Item*> oh_slot_items;
    QVector<Item*> current_patch_oh_slot_items;

    QVector<Item*> helms;
    QVector<Item*> current_patch_helms;

    QVector<QVector<Item*>> all_slots_items;

};

#endif // EQUIPMENTDB_H
