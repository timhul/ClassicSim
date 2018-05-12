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

    QString get_name() const;
    virtual float get_cooldown();
    float get_last_used();
    float get_next_use() const;
    bool is_ready() const;
    bool is_available(const int) const;
    bool is_enabled() const;
    bool cooldown_less_than(const float) const;
    bool cooldown_greater_than(const float) const;

    virtual void increase_effect_via_talent();
    virtual void decrease_effect_via_talent();

    virtual void increase_spell_rank();
    virtual void decrease_spell_rank();

    int perform(const int);

    void reset();
    virtual void reset_effect();
    virtual void periodic_effect();

protected:
    virtual int spell_effect(const int) = 0;
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

    void add_spell_cd_event(void) const;
    void add_gcd_event(void) const;
    void add_fail_stats(QString) const;
    void add_success_stats(QString, const int damage_dealt) const;
    void add_success_stats(QString, const int, const int) const;
    void add_proc_stats(const int value, QString title) const;

    void increment_miss();
    void increment_full_resist();

    void increment_dodge();
    void increment_parry();
    void increment_full_block();

    void increment_partial_resist();
    void increment_partial_block();
    void increment_partial_block_crit();

    void increment_glancing();
    void increment_hit();
    void increment_crit();

    void add_partial_resist_dmg(const int);
    void add_partial_block_dmg(const int);
    void add_partial_block_crit_dmg(const int);
    void add_glancing_dmg(const int);
    void add_hit_dmg(const int);
    void add_crit_dmg(const int);

private:
};

#endif // SPELL_H
