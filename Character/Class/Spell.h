#ifndef SPELL_H
#define SPELL_H

#include <QString>
#include <QVector>
#include <algorithm>
#include "Engine.h"
#include "CombatRoll.h"
#include "CooldownReady.h"
#include "AttackResult.h"
#include "assert.h"

class Character;
class StatisticsSpell;

namespace SpellStatus {
    static const int INACTIVE = -1;
    static const int INITIAL_ID = 0;
}

namespace RestrictedByGcd {
    static const bool Yes = true;
    static const bool No = false;
}

class Spell {
public:
    Spell(const QString& name,
          const QString& icon,
          Character* pchar,
          bool restricted_by_gcd,
          double cooldown,
          int resource_cost);

    virtual ~Spell();

    QString get_name() const;
    double get_base_cooldown();
    double get_last_used();
    double get_next_use() const;
    bool is_ready() const;
    virtual bool is_available() const;
    bool is_enabled() const;
    void enable();
    void disable();

    double get_cooldown_remaining() const;

    virtual void increase_spell_rank();
    virtual void decrease_spell_rank();

    void perform();
    virtual void perform_periodic();

    void reset();
    virtual void prepare_set_of_combat_iterations();
    StatisticsSpell* get_statistics_for_spell() const;

    int get_instance_id() const;
    void set_instance_id(const int);

protected:
    virtual void spell_effect() = 0;
    virtual void enable_spell_effect();
    virtual void disable_spell_effect();
    virtual void reset_effect();
    virtual void prepare_set_of_combat_iterations_spell_specific();
    virtual bool is_ready_spell_specific() const;

    const QString name;
    const QString icon;
    Character* pchar;
    Engine* engine;
    CombatRoll* roll;
    StatisticsSpell* statistics_spell;

    bool restricted_by_gcd;
    double cooldown;
    double last_used;
    int resource_cost;
    int spell_rank;
    int instance_id;
    bool enabled;

    void add_spell_cd_event(void) const;
    void add_gcd_event(void) const;

    void increment_miss();
    void increment_full_resist();

    void increment_dodge();
    void increment_parry();
    void increment_full_block();

    void add_partial_resist_dmg(const int, const int resource_cost, const double execution_time);
    void add_partial_block_dmg(const int, const int resource_cost, const double execution_time);
    void add_partial_block_crit_dmg(const int, const int resource_cost, const double execution_time);
    void add_glancing_dmg(const int, const int resource_cost, const double execution_time);
    void add_hit_dmg(const int, const int resource_cost, const double execution_time);
    void add_crit_dmg(const int, const int resource_cost, const double execution_time);

    double damage_after_modifiers(const double damage) const;
};

#endif // SPELL_H
