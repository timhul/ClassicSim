
#include "Crusader.h"
#include "Character.h"
#include "ActiveBuffs.h"
#include "HolyStrength.h"

Crusader::Crusader(Character* pchar, const int weapon) :
    ProcPPM("Holy Strength", weapon, 1.0, 0.0, QVector<Proc*>(),
            QVector<ProcInfo::Source>(),
            pchar),
    holy_strength(new HolyStrength(pchar))
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
}

Crusader::~Crusader() {
    delete holy_strength;
}

void Crusader::proc_effect() {
    return holy_strength->apply_buff();
}
