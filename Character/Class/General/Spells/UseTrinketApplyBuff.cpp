
#include "UseTrinketApplyBuff.h"
#include "Character.h"
#include "Spells.h"
#include "Buff.h"

UseTrinketApplyBuff::UseTrinketApplyBuff(Character* pchar,
                                         const QString &name,
                                         const QString &icon,
                                         const int cooldown,
                                         Buff* buff) :
    Spell(name, icon, pchar, false, cooldown, 0),
    buff(buff)
{
    this->enabled = false;
    pchar->get_spells()->add_spell(this);
    buff->enable_buff();
}

UseTrinketApplyBuff::~UseTrinketApplyBuff() {
    buff->disable_buff();
    pchar->get_spells()->remove_spell(this);

    delete buff;
}

void UseTrinketApplyBuff::spell_effect() {
    buff->apply_buff();
}
