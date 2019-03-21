#include "SwordSpecialization.h"

#include "Character.h"
#include "CharacterStats.h"
#include "Equipment.h"
#include "ItemNamespace.h"
#include "ProcInfo.h"
#include "Utils/Check.h"
#include "Weapon.h"

SwordSpecialization::SwordSpecialization(Character* pchar) :
    Proc("Sword Specialization", "Assets/items/Inv_sword_27.png", 0.0, 0, QVector<Proc*>(),
         QVector<ProcInfo::Source>({ProcInfo::Source::MainhandSpell, ProcInfo::Source::MainhandSwing,
                                    ProcInfo::Source::OffhandSpell, ProcInfo::Source::OffhandSwing}),
         pchar),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Sword Specialization", 5, DisabledAtZero::Yes)}),
    warr(pchar)
{
    this->enabled = false;
    this->talent_ranks = {0, 1, 2, 3, 4, 5};
}

SwordSpecialization::~SwordSpecialization() = default;

void SwordSpecialization::proc_effect() {
    warr->run_extra_mh_attack();
}

void SwordSpecialization::increase_talent_rank_effect(const QString&, const int curr) {
    proc_range = talent_ranks[curr] * 100;
}

void SwordSpecialization::decrease_talent_rank_effect(const QString&, const int curr) {
    proc_range = talent_ranks[curr] * 100;
}

bool SwordSpecialization::proc_specific_conditions_fulfilled() const {
    switch (curr_proc_source) {
    case ProcInfo::Source::MainhandSpell:
    case ProcInfo::Source::MainhandSwing:
        return weapon_is_sword(warr->get_stats()->get_equipment()->get_mainhand());
    case ProcInfo::Source::OffhandSpell:
    case ProcInfo::Source::OffhandSwing:
        return weapon_is_sword(warr->get_stats()->get_equipment()->get_offhand());
    default:
        check(false, "Reached end of switch");
        return false;
    }
}

bool SwordSpecialization::weapon_is_sword(Weapon* weapon) const {
    if (weapon == nullptr)
        return false;

    int weapon_type = weapon->get_weapon_type();

    return weapon_type == WeaponTypes::SWORD || weapon_type == WeaponTypes::TWOHAND_SWORD;
}
