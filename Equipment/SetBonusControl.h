#pragma once

#include <QMap>

class Character;
class EquipmentDb;
class Proc;

enum class ItemStats: int;

class SetBonusControl {
public:
    SetBonusControl(EquipmentDb* equipment_db, Character* pchar);
    ~SetBonusControl();

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

    QMap<QString, Proc*> active_procs;
    QMap<int, QString> current_set_items;
    QMap<int, QString> possible_set_items;
    QMap<QString, QVector<QPair<int, QString>>> set_bonus_tooltips;
    QMap<QString, QMap<int, QPair<ItemStats, unsigned>>> set_bonus_effects;

    void activate_warrior_r10_pvp_set_bonuses(const int num_pieces);
    void deactivate_warrior_r10_pvp_set_bonuses(const int num_pieces);

    void activate_warrior_r13_pvp_set_bonuses(const int num_pieces);
    void deactivate_warrior_r13_pvp_set_bonuses(const int num_pieces);

    void activate_paladin_r10_pvp_set_bonuses(const int num_pieces);
    void deactivate_paladin_r10_pvp_set_bonuses(const int num_pieces);

    void activate_paladin_r13_pvp_set_bonuses(const int num_pieces);
    void deactivate_paladin_r13_pvp_set_bonuses(const int num_pieces);

    void activate_hunter_r10_pvp_set_bonuses(const int num_pieces);
    void deactivate_hunter_r10_pvp_set_bonuses(const int num_pieces);

    void activate_hunter_r13_pvp_set_bonuses(const int num_pieces);
    void deactivate_hunter_r13_pvp_set_bonuses(const int num_pieces);

    void activate_arathi_basin_physical_set_bonuses(const int num_pieces);
    void deactivate_arathi_basin_physical_set_bonuses(const int num_pieces);

    void activate_spell_rank_group(const QString& spell_name, const QString& set_name, const int num_pieces);
    void deactivate_spell_rank_group(const QString& spell_name, const QString& set_name, const int num_pieces);
};
