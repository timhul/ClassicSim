#include "EnchantProc.h"

#include "Character.h"
#include "Crusader.h"
#include "FieryWeapon.h"
#include "ItemNamespace.h"
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
    default:
        assert(false);
    }

    proc->enable_proc();
}

EnchantProc::~EnchantProc() {
    proc->disable_proc();
    delete proc;
}
