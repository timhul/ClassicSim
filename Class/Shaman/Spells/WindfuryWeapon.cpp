#include "WindfuryWeapon.h"

#include "CooldownControl.h"
#include "Equipment.h"
#include "NoEffectSelfBuff.h"
#include "Shaman.h"
#include "Utils/Check.h"
#include "Weapon.h"
#include "WindfuryWeaponProc.h"

WindfuryWeapon::WindfuryWeapon(Shaman* pchar, const int spell_rank) :
    Spell("Windfury Weapon", "Assets/spell/Spell_nature_cyclone.png", pchar, new CooldownControl(pchar, 0.0), RestrictedByGcd::Yes, ResourceType::Mana, 0, spell_rank),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Elemental Weapons", 3, DisabledAtZero::No)}),
    buff(new NoEffectSelfBuff(pchar, 300, QString("Windfury Weapon (rank %1)").arg(spell_rank), "Assets/spell/Spell_nature_cyclone.png", Hidden::No)),
    proc(new WindfuryWeaponProc(pchar, spell_rank))
{
    buff->link_proc_application(proc);
    buff->link_proc_expiration(proc);

    switch (spell_rank) {
    case 1:
        resource_cost = 90;
        level_req = 30;
        break;
    case 2:
        resource_cost = 115;
        level_req = 40;
        break;
    case 3:
        resource_cost = 140;
        level_req = 50;
        break;
    case 4:
        resource_cost = 165;
        level_req = 60;
        break;
    default:
        check(false, QString("%1 does not support rank %2").arg(name).arg(spell_rank).toStdString());
    }

    buff->enable_buff();
}

WindfuryWeapon::~WindfuryWeapon() {
    if (buff->is_enabled())
        buff->disable_buff();
    if (proc->is_enabled())
        proc->disable();

    delete buff;
    delete proc;
    delete cooldown;
}

Proc* WindfuryWeapon::get_proc() const {
    return this->proc;
}

void WindfuryWeapon::prepare_set_of_combat_iterations_spell_specific() {
    proc->prepare_set_of_combat_iterations();
}

void WindfuryWeapon::spell_effect() {
    pchar->get_equipment()->get_mainhand()->clear_temporary_enchant();
    buff->apply_buff();
    pchar->lose_mana(resource_cost);
}

void WindfuryWeapon::increase_talent_rank_effect(const QString& talent_name, const int) {
    proc->increase_talent_rank(proc, talent_name);
}

void WindfuryWeapon::decrease_talent_rank_effect(const QString& talent_name, const int) {
    proc->decrease_talent_rank(proc, talent_name);
}
