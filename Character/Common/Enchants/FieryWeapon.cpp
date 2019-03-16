
#include "FieryWeapon.h"
#include "InstantSpellAttack.h"
#include "ItemNamespace.h"
#include "Character.h"
#include "Spells.h"
#include "MagicSchools.h"

FieryWeapon::FieryWeapon(Character* pchar, const QString& weapon_identifier, const int weapon) :
    ProcPPM("Fiery Weapon " + weapon_identifier, "Assets/misc/Spell_holy_greaterheal.png", weapon, 6.0, 0.0, QVector<Proc*>(),
            QVector<ProcInfo::Source>(), pchar),
    fiery_weapon_attack(new InstantSpellAttack(pchar, name, "Assets/misc/Spell_holy_greaterheal.png", MagicSchool::Fire, 40, 40))
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

    pchar->get_spells()->add_spell(fiery_weapon_attack);
}

FieryWeapon::~FieryWeapon() {
    pchar->get_spells()->remove_spell(fiery_weapon_attack);
    fiery_weapon_attack->disable();
    delete fiery_weapon_attack;
}

void FieryWeapon::proc_effect() {
    fiery_weapon_attack->perform();
}
