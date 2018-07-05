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

class Spell {
public:
    Spell(QString _name, Engine* _eng, Character* _pchar, CombatRoll* _roll, float _cd, int _cost);

    virtual ~Spell();

    StatisticsSpell* get_statistics_for_spell() const;

    QString get_name() const;
    // TODO: Rename to get_base_cooldown()
    virtual float get_cooldown();
    float get_last_used();
    float get_next_use() const;
    bool is_ready() const;
    virtual bool is_available() const;
    bool is_enabled() const;

    float get_cooldown_remaining() const;

    // TODO: Remove these two functions (replaced by get_cooldown_remaining())
    bool cooldown_less_than(const float) const;
    bool cooldown_greater_than(const float) const;

    virtual void increase_effect_via_talent();
    virtual void decrease_effect_via_talent();

    virtual void increase_spell_rank();
    virtual void decrease_spell_rank();

    void perform();

    void reset();
    virtual void reset_effect();
    virtual void periodic_effect();

protected:
    virtual void spell_effect() = 0;
    const QString name;
    Engine* engine;
    Character* pchar;
    CombatRoll* roll;
    StatisticsSpell* statistics;

    float cooldown;
    float last_used;
    int resource_cost;
    int rank_talent;
    int rank_spell;
    bool enabled_by_talent;

    void add_spell_cd_event(void) const;
    void add_gcd_event(void) const;

    void increment_miss();
    void increment_full_resist();

    void increment_dodge();
    void increment_parry();
    void increment_full_block();

    void add_partial_resist_dmg(const int);
    void add_partial_block_dmg(const int);
    void add_partial_block_crit_dmg(const int);
    void add_glancing_dmg(const int);
    void add_hit_dmg(const int);
    void add_crit_dmg(const int);

private:
};

#endif // SPELL_H
