#ifndef TESTSPELL_H
#define TESTSPELL_H

#include <QString>
#include <QDebug>

class Engine;
class Equipment;
class EquipmentDb;
class CombatRoll;
class Faction;
class Target;
class Race;
class Character;

class TestSpell {
public:
    TestSpell(EquipmentDb *equipment_db, QString spell_under_test);

    void set_up_general();
    void tear_down_general();

    void given_no_previous_damage_dealt();
    void given_a_guaranteed_white_hit();
    void given_a_guaranteed_white_glancing_blow();
    void given_a_guaranteed_white_crit();
    void given_a_guaranteed_white_miss();
    void given_a_guaranteed_white_dodge();
    void given_a_guaranteed_white_parry();
    void given_a_guaranteed_white_block();
    void given_a_guaranteed_melee_ability_crit();
    void given_a_guaranteed_melee_ability_hit();
    void given_a_guaranteed_melee_ability_miss();
    void given_a_guaranteed_melee_ability_dodge();
    void given_a_guaranteed_melee_ability_parry();
    void given_a_guaranteed_melee_ability_block();
    void given_300_weapon_skill_mh();
    void given_305_weapon_skill_mh();
    void given_310_weapon_skill_mh();
    void given_315_weapon_skill_mh();
    void given_300_weapon_skill_oh();
    void given_305_weapon_skill_oh();
    void given_310_weapon_skill_oh();
    void given_315_weapon_skill_oh();
    void given_a_mainhand_weapon_with_100_min_max_dmg();
    void given_a_mainhand_weapon_with_3_speed();
    void given_a_mainhand_weapon_with_2_speed();
    void given_no_mainhand();
    void given_no_offhand();
    void given_an_offhand_weapon_with_100_min_max_dmg();
    void given_an_offhand_weapon_with_3_speed();
    void given_an_offhand_weapon_with_2_speed();
    void given_1000_melee_ap();
    void given_target_has_0_armor();
    void given_engine_priority_at(const double priority);

    void when_running_queued_events_until(const double priority);

    void then_damage_dealt_is(const int damage);
    void then_next_event_is(const QString &name);
    void then_next_event_is(const QString &name, const QString &priority);

protected:
    EquipmentDb* equipment_db;
    Character* pchar;
    Race* race;
    QString spell_under_test;

    void set_melee_special_table_for_hit(const int wpn_skill);
    void set_melee_special_table_for_crit(const int wpn_skill);
    void set_melee_special_table_for_miss(const int wpn_skill);
    void set_melee_special_table_for_dodge(const int wpn_skill);
    void set_melee_special_table_for_parry(const int wpn_skill);
    void set_melee_special_table_for_block(const int wpn_skill);

    void set_melee_auto_table_for_hit(const int wpn_skill);
    void set_melee_auto_table_for_glancing(const int wpn_skill);
    void set_melee_auto_table_for_crit(const int wpn_skill);
    void set_melee_auto_table_for_miss(const int wpn_skill);
    void set_melee_auto_table_for_dodge(const int wpn_skill);
    void set_melee_auto_table_for_parry(const int wpn_skill);
    void set_melee_auto_table_for_block(const int wpn_skill);
};

#endif // TESTSPELL_H
