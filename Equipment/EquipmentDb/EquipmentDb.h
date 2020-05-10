#pragma once

#include <QFile>
#include <QMap>
#include <QObject>
#include <QVector>
#include <QVersionNumber>
#include <QXmlStreamReader>

#include "ContentPhase.h"

class EnchantInfo;
class Item;
class Projectile;
class Quiver;
class Weapon;

class EquipmentDb : public QObject {
public:
    EquipmentDb(QObject* parent = nullptr);

    ~EquipmentDb();

    Weapon* get_melee_weapon(const int item_id) const;
    Weapon* get_ranged(const int item_id) const;
    Item* get_head(const int item_id) const;
    Item* get_neck(const int item_id) const;
    Item* get_shoulders(const int item_id) const;
    Item* get_back(const int item_id) const;
    Item* get_chest(const int item_id) const;
    Item* get_wrist(const int item_id) const;
    Item* get_gloves(const int item_id) const;
    Item* get_belt(const int item_id) const;
    Item* get_legs(const int item_id) const;
    Item* get_boots(const int item_id) const;
    Item* get_ring(const int item_id) const;
    Item* get_trinket(const int item_id) const;
    Item* get_caster_offhand(const int item_id) const;
    Item* get_relic(const int item_id) const;
    Item* get_shield(const int item_id) const;
    Projectile* get_projectile(const int item_id) const;
    Quiver* get_quiver(const int item_id) const;

    Item* get_item(const int item_id) const;

    void set_content_phase(const Content::Phase current_phase);

    const QVector<Item*>& get_slot_items(const int slot) const;

    QString get_name_for_item_id(const int item_id) const;

    void add_melee_weapon(Weapon* wpn);
    void add_ranged(Weapon* wpn);
    void add_ring(Item* ring);

    EnchantInfo* enchant_info;

private:
    Content::Phase current_phase;

    void read_equipment_files();
    void set_phase_for_slot(QVector<Item*>& total_slot_items, QVector<Item*>& phase_slot_items);
    Item* get_item(const QVector<Item*>& list, const int item_id) const;
    void take_weapons_from_given_items(QVector<Item*>& mixed_items);
    void take_items_of_slot_from_given_items(QVector<Item*>& mixed_items, QVector<Item*>& sorted, const int slot);
    void delete_items(QVector<Item*>*);
    void add_item_id(Item* item);
    void add_druid_cat_form_claws();
    void add_druid_bear_form_paws();

    QVector<Item*> mh_slot_items;
    QVector<Item*> current_phase_mh_slot_items;

    QVector<Item*> oh_slot_items;
    QVector<Item*> current_phase_oh_slot_items;

    QVector<Item*> ranged_items;
    QVector<Item*> current_phase_ranged_items;

    QVector<Item*> helms;
    QVector<Item*> current_phase_helms;

    QVector<Item*> amulets;
    QVector<Item*> current_phase_amulets;

    QVector<Item*> shoulders;
    QVector<Item*> current_phase_shoulders;

    QVector<Item*> backs;
    QVector<Item*> current_phase_backs;

    QVector<Item*> chests;
    QVector<Item*> current_phase_chests;

    QVector<Item*> wrists;
    QVector<Item*> current_phase_wrists;

    QVector<Item*> gloves;
    QVector<Item*> current_phase_gloves;

    QVector<Item*> belts;
    QVector<Item*> current_phase_belts;

    QVector<Item*> legs;
    QVector<Item*> current_phase_legs;

    QVector<Item*> boots;
    QVector<Item*> current_phase_boots;

    QVector<Item*> rings;
    QVector<Item*> current_phase_rings;

    QVector<Item*> trinkets;
    QVector<Item*> current_phase_trinkets;

    QVector<Item*> projectiles;
    QVector<Item*> current_phase_projectiles;

    QVector<Item*> relics;
    QVector<Item*> current_phase_relics;

    QVector<Item*> quivers;
    QVector<Item*> current_phase_quivers;

    QVector<Item*> shields;
    QVector<Item*> current_phase_shields;

    QVector<QVector<Item*>*> all_slots_items;

    QMap<int, Item*> item_id_to_item;
};
