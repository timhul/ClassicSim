#pragma once

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

enum class RestrictedByGcd : bool {
    Yes = true,
    No = false,
};

enum class SpellStatus: int {
    Available = 0,
    BuffInactive,
    CastInProgress,
    InBattleStance,
    InBerserkerStance,
    InDefensiveStance,
    InCasterForm,
    InBearForm,
    InCatForm,
    InMoonkinForm,
    IncorrectWeaponType,
    InsufficientComboPoints,
    InsufficientResources,
    NotEnabled,
    NotInExecuteRange,
    OnCooldown,
    OnGCD,
    OnStanceCooldown,
    OnFormCooldown,
    OnTrinketCooldown,
    OvercapResource,
};

class Spell {
public:
    Spell(QString name,
          QString icon,
          Character* pchar,
          CooldownControl* cooldown_control,
          const RestrictedByGcd restricted_by_gcd,
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
    virtual void perform_start_of_combat();

    void reset();
    virtual void prepare_set_of_combat_iterations();

    int get_instance_id() const;
    void set_instance_id(const int);

    void increase_resource_cost_modifier(const int change);
    void decrease_resource_cost_modifier(const int change);

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

    const RestrictedByGcd restricted_by_gcd;
    const ResourceType resource_type;
    unsigned resource_cost;
    double resource_cost_mod {1.0};
    QVector<int> resource_cost_mod_changes;
    const int spell_rank;
    unsigned level_req {60};
    int instance_id;
    bool enabled;

    void increment_miss();
    void increment_full_resist();
    void increment_dodge();
    void increment_parry();
    void increment_full_block();

    void add_partial_block_dmg(const int damage, const double resource_cost, const double execution_time);
    void add_partial_block_crit_dmg(const int damage, const double resource_cost, const double execution_time);
    void add_glancing_dmg(const int damage, const double resource_cost, const double execution_time);
    void add_hit_dmg(const int damage, const double resource_cost, const double execution_time);
    void add_spell_hit_dmg(const int damage, const double resource_cost, const double execution_time, const int resist_result);
    void add_crit_dmg(const int damage, const double resource_cost, const double execution_time);
    void add_spell_crit_dmg(const int damage, const double resource_cost, const double execution_time, const int resist_result);

    double damage_after_modifiers(const double damage) const;
    double get_partial_resist_dmg_modifier(const int resist_result) const;
};
