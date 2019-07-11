#include "Consecration.h"

#include "CharacterStats.h"
#include "CooldownControl.h"
#include "Paladin.h"
#include "PeriodicDamageSpell.h"
#include "Utils/Check.h"

Consecration::Consecration(Paladin* pchar,
                           CooldownControl* cooldown_control,
                           const int spell_rank) :
    Spell("Consecration", "Assets/spell/Spell_holy_innerfire.png", pchar, cooldown_control, RestrictedByGcd::Yes, ResourceType::Mana, 0, spell_rank),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Consecration", 1, DisabledAtZero::Yes)})
{
    this->enabled = false;

    unsigned full_duration_dmg = 0;
    switch (spell_rank) {
    case 1:
        full_duration_dmg = 64;
        resource_cost = 135;
        break;
    case 2:
        full_duration_dmg = 120;
        resource_cost = 235;
        break;
    case 3:
        full_duration_dmg = 192;
        resource_cost = 320;
        break;
    case 4:
        full_duration_dmg = 280;
        resource_cost = 435;
        break;
    case 5:
        full_duration_dmg = 384;
        resource_cost = 565;
        break;
    default:
        check(false, QString("%1 does not support rank %2").arg(name).arg(spell_rank).toStdString());
    }

    cons_dot_1 = new PeriodicDamageSpell(QString("Consecration 1 (rank %1)").arg(spell_rank), "Assets/spell/Spell_holy_innerfire.png", pchar,
                                         RestrictedByGcd::No, MagicSchool::Holy, 2.0, 8, full_duration_dmg, resource_cost,
                                         pchar->global_cooldown(), 0.33);
    cons_dot_2 = new PeriodicDamageSpell(QString("Consecration 2 (rank %1)").arg(spell_rank), "Assets/spell/Spell_holy_innerfire.png", pchar,
                                         RestrictedByGcd::No, MagicSchool::Holy, 2.0, 8, full_duration_dmg, resource_cost,
                                         pchar->global_cooldown(), 0.33);

    cons_dot_1->disable();
    cons_dot_2->disable();
}

Consecration::~Consecration() {
    delete cons_dot_1;
    delete cons_dot_2;
}

bool Consecration::is_rank_learned() const {
    switch (spell_rank) {
    case 1:
        return pchar->get_clvl() >= 20;
    case 2:
        return pchar->get_clvl() >= 30;
    case 3:
        return pchar->get_clvl() >= 40;
    case 4:
        return pchar->get_clvl() >= 50;
    case 5:
        return pchar->get_clvl() >= 60;
    }

    check(false, QString("%1::is_rank_learned() failed for rank %2").arg(name).arg(spell_rank).toStdString());
    return false;
}

void Consecration::spell_effect() {
    pchar->lose_mana(get_resource_cost());
    cooldown->add_gcd_event();

    if (!cons_dot_1->is_active())
        cons_dot_1->perform();
    else
        cons_dot_2->perform();
}

void Consecration::reset_effect() {

}

void Consecration::increase_talent_rank_effect(const QString&, const int) {
    cons_dot_1->enable();
    cons_dot_2->enable();
}

void Consecration::decrease_talent_rank_effect(const QString&, const int) {
    cons_dot_1->disable();
    cons_dot_2->disable();
}

void Consecration::prepare_set_of_combat_iterations_spell_specific() {
    cons_dot_1->prepare_set_of_combat_iterations();
    cons_dot_2->prepare_set_of_combat_iterations();
}
