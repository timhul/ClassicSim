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

    bool is_set_item(const int item_id) const;
    QString get_set_name(const int item_id) const;
    QVector<QPair<QString, bool>> get_item_names_in_set(const int item_id) const;
    QVector<QPair<QString, bool>> get_set_bonus_tooltips(const int item_id) const;
    int get_num_equipped_pieces_for_set(const QString& set_name) const;

private:
    EquipmentDb* equipment_db;
    Character* pchar;

    QMap<int, QString> current_set_items;
    QMap<int, QString> possible_set_items;
    QMap<QString, QVector<QPair<int, QString>>> set_bonus_tooltips;
};

#endif // SETBONUSCONTROL_H
