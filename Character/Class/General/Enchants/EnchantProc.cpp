
#include "Character.h"
#include "EnchantProc.h"
#include "Crusader.h"
#include "FieryWeapon.h"
#include "WindfuryTotemAttack.h"
#include "ItemNamespace.h"

EnchantProc::EnchantProc(EnchantName::Name enchant, Character *pchar, const int slot) :
    Enchant(enchant, get_name_from_enum_weapon(enchant), get_effect_from_enum_weapon(enchant)),
    pchar(pchar)
{
    QString identifier = slot == EnchantSlot::MAINHAND ? "Mainhand" : "Offhand";

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

QString get_name_from_enum_weapon(EnchantName::Name enchant) {
    switch (enchant) {
    case EnchantName::Crusader:
        return "Crusader";
    case EnchantName::FieryWeapon:
        return "Fiery Weapon";
    case EnchantName::WindfuryTotem:
        return "Windfury Totem";
    default:
        assert(false);
    }

    return "<Missing proc enchant name>";
}

QString get_effect_from_enum_weapon(EnchantName::Name enchant) {
    return get_name_from_enum_weapon(enchant);
}
