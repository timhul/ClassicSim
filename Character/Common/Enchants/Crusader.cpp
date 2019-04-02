#include "Crusader.h"

#include "Character.h"
#include "EnabledBuffs.h"
#include "HolyStrength.h"
#include "ItemNamespace.h"
#include "Utils/Check.h"

Crusader::Crusader(Character* pchar, const QString& weapon_identifier, const int weapon) :
    ProcPPM("Holy Strength " + weapon_identifier, "Assets/spell/Spell_holy_blessingofstrength.png", weapon, 1.0, 0.0, QVector<Proc*>(),
            QVector<ProcInfo::Source>(),
            pchar),
    holy_strength(new HolyStrength(pchar, weapon_identifier))
{
    switch (weapon) {
    case EnchantSlot::MAINHAND:
        proc_sources.append({ProcInfo::Source::MainhandSpell, ProcInfo::Source::MainhandSwing});
        break;
    case EnchantSlot::OFFHAND:
        proc_sources.append({ProcInfo::Source::OffhandSpell, ProcInfo::Source::OffhandSwing});
        break;
    default:
        check(false, "Reached end of switch");
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
