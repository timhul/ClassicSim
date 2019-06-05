#ifndef SPELL_H
#define SPELL_H

#include <algorithm>
#include <QString>
#include <QVector>

#include "PhysicalAttackResult.h"
#include "MagicAttackResult.h"
#include "Resource.h"

class Character;
class CombatRoll;
class CooldownReady;
class Engine;
class CooldownControl;
class StatisticsSpell;

namespace SpellID {
    static const int INACTIVE = -1;
    static const int INITIAL_ID = 0;
}

namespace RestrictedByGcd {
    static const bool Yes = true;
    static const bool No = false;
}

enum class SpellStatus: int {
    Available = 0,
    BuffInactive,
    CastInProgress,
    InBattleStance,
    InBerserkerStance,
    InDefensiveStance,
    IncorrectWeaponType,
    InsufficientComboPoints,
    InsufficientResources,
    NotEnabled,
    NotInExecuteRange,
    OnCooldown,
    OnGCD,
    OnStanceCooldown,
    OnTrinketCooldown,
    OvercapResource,
};

class Spell {
public:
    Spell(QString name,
          QString icon,
          Character* pchar,
          CooldownControl* cooldown_control,
          bool restricted_by_gcd,
          const ResourceType resource_type,
          const unsigned resource_cost,
          const int spell_rank = 1);

    virtual ~Spell() = default;
    friend bool operator== (const Spell& lhs, const Spell& rhs);

    QString get_name() const;
    QString get_icon() const;

    double get_base_cooldown() const;
    double get_cooldown_remaining() const;
    double get_last_used() const;
    double get_next_use() const;
    double get_resource_cost() const;
    SpellStatus get_spell_status() const;

    void enable();
    void disable();
    bool is_enabled() const;
    virtual bool is_rank_learned() const;

    int get_spell_rank() const;
    static const int MAX_RANK = 0;

    void perform();
    virtual void perform_periodic();
    virtual void perform_start_of_combat();

    void reset();
    virtual void prepare_set_of_combat_iterations();

    int get_instance_id() const;
    void set_instance_id(const int);

protected:
    virtual void spell_effect() = 0;
    virtual void enable_spell_effect();
    virtual void disable_spell_effect();
    virtual void reset_effect();
    virtual void prepare_set_of_combat_iterations_spell_specific();
    virtual SpellStatus is_ready_spell_specific() const;

    const QString name;
    QString icon;
    Character* pchar;
    Engine* engine;
    CombatRoll* roll;
    CooldownControl* cooldown;
    StatisticsSpell* statistics_spell;

    bool restricted_by_gcd;
    const ResourceType resource_type;
    unsigned resource_cost;
    const int spell_rank;
    unsigned level_req {60};
    int instance_id;
    bool enabled;

    void increment_miss();
    void increment_full_resist();
    void increment_dodge();
    void increment_parry();
    void increment_full_block();

    void add_partial_resist_dmg(const int damage, const double resource_cost, const double execution_time);
    void add_partial_block_dmg(const int damage, const double resource_cost, const double execution_time);
    void add_partial_block_crit_dmg(const int damage, const double resource_cost, const double execution_time);
    void add_glancing_dmg(const int damage, const double resource_cost, const double execution_time);
    void add_hit_dmg(const int damage, const double resource_cost, const double execution_time);
    void add_crit_dmg(const int damage, const double resource_cost, const double execution_time);

    double damage_after_modifiers(const double damage) const;
    double get_partial_resist_dmg_modifier(const int resist_result) const;
};

#endif // SPELL_H
