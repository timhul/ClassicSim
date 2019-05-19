#include "UseTrinket.h"

#include "Buff.h"
#include "Character.h"
#include "CharacterSpells.h"
#include "CooldownControl.h"
#include "Proc.h"

UseTrinket::UseTrinket(Character* pchar,
                       const QString &name,
                       const QString &icon,
                       const int cooldown,
                       Buff* buff,
                       Proc *proc) :
    Spell(name, icon, pchar, new CooldownControl(pchar, cooldown), RestrictedByGcd::No, ResourceType::Rage, 0),
    buff(buff),
    proc(proc)
{
    this->enabled = false;
    pchar->get_spells()->add_spell(this);
    buff->enable_buff();

    if (proc != nullptr)
        proc->enable_proc();
}

UseTrinket::~UseTrinket() {
    buff->disable_buff();

    if (proc != nullptr)
        proc->disable_proc();

    pchar->get_spells()->remove_spell(this);

    delete buff;
    delete proc;
    delete cooldown;
}

void UseTrinket::spell_effect() {
    cooldown->add_spell_cd_event();

    buff->apply_buff();

    pchar->start_trinket_cooldown(buff->time_left());
}

SpellStatus UseTrinket::is_ready_spell_specific() const {
    return pchar->on_trinket_cooldown() ? SpellStatus::OnTrinketCooldown : SpellStatus::Available;
}
