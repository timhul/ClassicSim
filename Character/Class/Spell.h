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

class Spell {
public:
    Spell(QString _name,
          Engine* _eng,
          Character* _pchar,
          CombatRoll* _roll,
          float _cd,
          int _cost) :
        name(_name),
        engine(_eng),
        pchar(_pchar),
        roll(_roll),
        cooldown(_cd),
        last_used(0 - _cd),
        resource_cost(_cost),
        rank_talent(0),
        rank_spell(0)
    {}

    virtual ~Spell() {}

    QString get_name() const;
    float get_cooldown();
    float get_last_used();
    float get_next_use() const;
    bool is_ready() const;
    bool is_available(const int) const;
    bool is_enabled() const;
    bool cooldown_less_than(const float) const;
    bool cooldown_greater_than(const float) const;

    virtual void increase_effect_via_talent();
    virtual void decrease_effect_via_talent();

    int perform(const int);

    void reset();
    virtual void reset_effect();

protected:
    virtual int spell_effect(const int) = 0;
    const QString name;
    Engine* engine;
    Character* pchar;
    CombatRoll* roll;
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
private:
};

#endif // SPELL_H
