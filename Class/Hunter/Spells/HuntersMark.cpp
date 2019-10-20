#include "HuntersMark.h"

#include <cmath>

#include "Character.h"
#include "CooldownControl.h"
#include "HuntersMarkBuff.h"

HuntersMark::HuntersMark(Character* pchar, HuntersMarkBuff* hunters_mark) :
    Spell("Hunter's Mark",
          "Assets/ability/Ability_hunter_snipershot.png",
          pchar,
          new CooldownControl(pchar, 0.0),
          RestrictedByGcd::Yes,
          ResourceType::Mana,
          60),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Improved Hunter's Mark", 5, DisabledAtZero::No)}),
    hunters_mark(hunters_mark),
    imp_hunters_mark_ranks({1.0, 1.03, 1.06, 1.09, 1.12, 1.15}),
    base_ranged_ap_bonus(110)
{
    hunters_mark_bonus = base_ranged_ap_bonus;
}

HuntersMark::~HuntersMark() {
    delete cooldown;
}

void HuntersMark::spell_effect() {
    cooldown->add_gcd_event();
    pchar->lose_mana(get_resource_cost());

    hunters_mark->cancel_buff();
    hunters_mark->ap_bonus = hunters_mark_bonus;
    hunters_mark->apply_buff();
}

void HuntersMark::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Improved Hunter's Mark")
        hunters_mark_bonus = static_cast<unsigned>(round(static_cast<double>(base_ranged_ap_bonus) * imp_hunters_mark_ranks[curr]));
}

void HuntersMark::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Improved Hunter's Mark")
        hunters_mark_bonus = static_cast<unsigned>(round(static_cast<double>(base_ranged_ap_bonus) * imp_hunters_mark_ranks[curr]));
}

