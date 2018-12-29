#ifndef SETBONUSCONTROL_H
#define SETBONUSCONTROL_H

#include <QMap>

class Character;
class EquipmentDb;

class SetBonusControl {
public:
    SetBonusControl(EquipmentDb* equipment_db, Character* pchar);
    ~SetBonusControl() = default;

    void equip_item(const int item_id);
    void unequip_item(const int item_id);

private:
    EquipmentDb* equipment_db;
    Character* pchar;

    QMap<int, QString> current_set_items;
    QMap<int, QString> possible_set_items;
    QMap<QString, QMap<int, QString>> set_bonus_tooltips;

    int get_num_equipped_pieces_for_set(const QString& set_name) const;
};

#endif // SETBONUSCONTROL_H
