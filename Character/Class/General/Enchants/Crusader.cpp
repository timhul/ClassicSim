
#include "Crusader.h"
#include "Character.h"
#include "ActiveBuffs.h"
#include "HolyStrength.h"
#include "ItemNamespace.h"

Crusader::Crusader(Character* pchar, const QString& weapon_identifier, const int weapon) :
    ProcPPM("Holy Strength " + weapon_identifier, weapon, 1.0, 0.0, QVector<Proc*>(),
            QVector<ProcInfo::Source>(),
            pchar),
    holy_strength(new HolyStrength(pchar, weapon_identifier))
{
    assert(weapon == EnchantSlot::MAINHAND || weapon == EnchantSlot::OFFHAND);

    switch (weapon) {
    case EnchantSlot::MAINHAND:
        proc_sources.append({ProcInfo::Source::MainhandSpell, ProcInfo::Source::MainhandSwing});
        break;
    case EnchantSlot::OFFHAND:
        proc_sources.append({ProcInfo::Source::OffhandSpell, ProcInfo::Source::OffhandSwing});
        break;
    }

    holy_strength->enable_buff();
}

Crusader::~Crusader() {
    holy_strength->disable_buff();
    delete holy_strength;
}

void Crusader::proc_effect() {
    holy_strength->apply_buff();
}
