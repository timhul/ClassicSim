#pragma once

#include <QMap>
#include <QVector>

#include "AttackMode.h"

class AutoShot;
class Berserking;
class BloodFury;
class Buff;
class Character;
class CooldownControl;
class DemonicRune;
class DragonbreathChili;
class MainhandAttack;
class ManaPotion;
class NightDragonsBreath;
class OffhandAttack;
class Rotation;
class Spell;
class SpellRankGroup;

static const bool RELINK_ROTATION = true;

class CharacterSpells {
public:
    CharacterSpells(Character* pchar);
    virtual ~CharacterSpells();

    void activate_racials();
    void deactivate_racials();

    void add_spell_group(const QVector<Spell*> spell_group, const bool relink = false);
    void remove_spell(Spell* spell);

    void add_start_of_combat_spell(Spell* spell);
    void remove_start_of_combat_spell(Spell* spell);
    void run_start_of_combat_spells();

    SpellRankGroup* get_spell_rank_group_by_name(const QString& spell_name) const;
    Buff* get_buff_by_name(const QString& name) const;

    void reset();

    void start_attack();
    void stop_attack();
    virtual void start_pet_attack();
    bool is_melee_attacking() const;
    bool is_ranged_attacking() const;

    void set_attack_mode(const AttackMode attack_mode);
    AttackMode get_attack_mode() const;
    Rotation* get_rotation();
    void set_rotation(Rotation*);
    void relink_spells();
    void perform_rotation();

    virtual void mh_auto_attack(const int iteration);
    virtual void oh_auto_attack(const int iteration);
    virtual void ranged_auto_attack(const int iteration);
    virtual void add_next_mh_attack();
    virtual void add_next_oh_attack();
    virtual void add_next_ranged_attack();

    bool cast_in_progress() const;
    unsigned start_cast();
    void complete_cast(const unsigned cast_id);

    void prepare_set_of_combat_iterations();

    virtual MainhandAttack* get_mh_attack() const;
    virtual OffhandAttack* get_oh_attack() const;
    virtual AutoShot* get_auto_shot() const;

    DragonbreathChili* get_dragonbreath_chili() const;

protected:
    Character* pchar;
    Rotation* rotation;
    bool cast_is_in_progress;
    unsigned id_of_cast_in_progress;
    AttackMode attack_mode;
    bool attack_mode_active;
    QVector<Spell*> spells;
    QVector<Spell*> start_of_combat_spells;
    QMap<QString, CooldownControl*> cooldown_controls;
    QMap<QString, SpellRankGroup*> spell_rank_groups;

    MainhandAttack* mh_attack{};
    OffhandAttack* oh_attack{};

    Berserking* berserking {nullptr};
    BloodFury* blood_fury;

    DemonicRune* demonic_rune;
    ManaPotion* mana_potion;
    NightDragonsBreath* night_dragons_breath;
    DragonbreathChili* dragonbreath_chili;

    CooldownControl* new_cooldown_control(const QString& spell_name, const double cooldown);

private:
    void start_melee_attack();
    void add_spell(Spell* spell, bool relink=true);
};
