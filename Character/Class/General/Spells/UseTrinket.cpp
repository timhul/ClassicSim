
#include "UseTrinket.h"
#include "Character.h"
#include "Spells.h"
#include "Buff.h"
#include "Proc.h"

UseTrinket::UseTrinket(Character* pchar,
                       const QString &name,
                       const QString &icon,
                       const int cooldown,
                       Buff* buff,
                       Proc *proc) :
    Spell(name, icon, pchar, false, cooldown, 0),
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
}

void UseTrinket::spell_effect() {
    buff->apply_buff();

    pchar->start_trinket_cooldown(buff->time_left());
}

bool UseTrinket::is_ready_spell_specific() const {
    return !pchar->on_trinket_cooldown();
}
