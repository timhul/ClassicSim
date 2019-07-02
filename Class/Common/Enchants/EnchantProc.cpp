#include "EnchantProc.h"

#include "Character.h"
#include "Crusader.h"
#include "FieryWeapon.h"
#include "GenericSpellProc.h"
#include "InstantSpellAttack.h"
#include "ItemNamespace.h"
#include "Utils/Check.h"
#include "WindfuryTotemAttack.h"

EnchantProc::EnchantProc(EnchantName::Name enchant, Character *pchar, const int slot) :
    Enchant(enchant),
    pchar(pchar)
{
    QString identifier = slot == EnchantSlot::MAINHAND ? QString("(MH)") : QString("(OH)");

    switch (enchant) {
    case EnchantName::Crusader:
        proc = new class Crusader(pchar, identifier, slot);
        break;
    case EnchantName::FieryWeapon:
        proc = new class FieryWeapon(pchar, identifier, slot);
        break;
    case EnchantName::WindfuryTotem:
        proc = new WindfuryTotemAttack(pchar);
        break;
    case EnchantName::ShadowOil: {
        Spell* spell = new InstantSpellAttack(pchar, "Shadow Oil", "Assets/spell/Spell_shadow_shadowbolt.png", MagicSchool::Shadow, 48, 56, 0.56);

        QVector<ProcInfo::Source> sources;
        if (slot == EnchantSlot::MAINHAND)
            sources = {ProcInfo::MainhandSwing, ProcInfo::MainhandSpell};
        else
            sources = {ProcInfo::OffhandSwing};

        proc = new GenericSpellProc(pchar, "Shadow Oil", "Assets/spell/Spell_shadow_shadowbolt.png", sources, 0.15, spell);
        }
        break;
    default:
        check(false, "EnchantProc constructor reached end of switch");
    }

    proc->enable_proc();
}

EnchantProc::~EnchantProc() {
    proc->disable_proc();
    delete proc;
}
