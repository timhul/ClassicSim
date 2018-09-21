#ifndef EQUIPMENTDB_H
#define EQUIPMENTDB_H

#include <QObject>
#include <QFile>
#include <QXmlStreamReader>
#include <QVector>
#include <QVersionNumber>

class Item;
class Weapon;

class EquipmentDb: public QObject {
public:
    EquipmentDb(QObject* parent = nullptr);

    ~EquipmentDb();

    Weapon* get_melee_weapon(const QString &name);
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
    Item* get_ring(const QString &name);
    Item* get_trinket(const QString &name);

    void set_patch(const QString &current_patch);
    bool item_valid_for_current_patch(const QString &item_patch);

    const QVector<Item *> &get_slot_items(const int slot) const;

    void add_melee_weapon(Weapon* wpn);
    void add_ring(Item* ring);

protected:
private:
    void read_equipment_files();

    Item* get_item(const QVector<Item*> &list, const QString &name);

    QVersionNumber current_patch;

    void set_weapons(QVector<Item*> &mixed_items);
    void set_items(QVector<Item*> &mixed_items, QVector<Item *> &sorted, const int slot);

    void set_patch_for_slot(QVector<Item*> &total_slot_items, QVector<Item*> &patch_slot_items);

    void delete_items(QVector<Item *> *);

    QVector<Item*> mh_slot_items;
    QVector<Item*> current_patch_mh_slot_items;

    QVector<Item*> oh_slot_items;
    QVector<Item*> current_patch_oh_slot_items;

    QVector<Item*> ranged_items;
    QVector<Item*> current_patch_ranged_items;

    QVector<Item*> helms;
    QVector<Item*> current_patch_helms;

    QVector<Item*> amulets;
    QVector<Item*> current_patch_amulets;

    QVector<Item*> shoulders;
    QVector<Item*> current_patch_shoulders;

    QVector<Item*> backs;
    QVector<Item*> current_patch_backs;

    QVector<Item*> chests;
    QVector<Item*> current_patch_chests;

    QVector<Item*> wrists;
    QVector<Item*> current_patch_wrists;

    QVector<Item*> gloves;
    QVector<Item*> current_patch_gloves;

    QVector<Item*> belts;
    QVector<Item*> current_patch_belts;

    QVector<Item*> legs;
    QVector<Item*> current_patch_legs;

    QVector<Item*> boots;
    QVector<Item*> current_patch_boots;

    QVector<Item*> rings;
    QVector<Item*> current_patch_rings;

    QVector<Item*> trinkets;
    QVector<Item*> current_patch_trinkets;

    QVector<QVector<Item*>*> all_slots_items;

};

#endif // EQUIPMENTDB_H
