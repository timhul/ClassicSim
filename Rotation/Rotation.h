#pragma once

#include <QMap>
#include <QVector>

#include "AttackMode.h"
#include "Resource.h"

class Buff;
class CastingTimeRequirer;
class Character;
class RotationExecutor;
class Spell;

class Rotation {
public:
    Rotation(QString class_name);
    ~Rotation();

    void run_precombat_actions();
    void perform_rotation() const;
    void prepare_set_of_combat_iterations();
    void finish_set_of_combat_iterations();

    void set_name(const QString& name);
    void set_description(const QString& desc);
    void add_precombat_spell(const QString& spell_name);
    void add_precast_spell(const QString& spell_name);
    void add_executor(RotationExecutor* executor);
    bool try_set_attack_mode(const QString& value);

    QString get_class() const;
    QString get_name() const;
    QString get_description() const;
    AttackMode get_attack_mode() const;

    void link_spells(Character* pchar);
    void link_precast_spell();
    void link_precombat_spells();
    bool add_conditionals(RotationExecutor*);

    QVector<RotationExecutor*> active_executors;
    QVector<RotationExecutor*> all_executors;
    QVector<Spell*> precombat_spells;
    Spell* precast_spell {nullptr};
    double get_time_required_to_run_precombat();

    void dump();

private:
    Character* pchar;
    QString class_name;
    QString name;
    QString description;
    AttackMode attack_mode;
    QVector<QString> precombat_spell_names;
    QString precast_spell_name;

    ResourceType get_resource_from_string(const QString& resource) const;
};
