#include "AngerManagement.h"
#include "AngerManagementTalent.h"
#include "CharacterStats.h"
#include "ItemNamespace.h"
#include "Warrior.h"
#include "WarriorSpells.h"

AngerManagementTalent::AngerManagementTalent(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Anger Management", "3ML", "Assets/spell/Spell_holy_blessingofstamina.png", 1),
    warr(dynamic_cast<Warrior*>(pchar))
{
    QString base_str = "Increases the time required for your rage to decay while out of combat by 30%.";
    rank_descriptions.insert(0, base_str);
    rank_descriptions.insert(1, base_str);
}

AngerManagementTalent::~AngerManagementTalent() = default;

void AngerManagementTalent::apply_rank_effect() {
    auto* spells = dynamic_cast<WarriorSpells*>(warr->get_spells());
    spells->add_pre_combat_spell(spells->get_anger_management());
}

void AngerManagementTalent::remove_rank_effect() {
    auto* spells = dynamic_cast<WarriorSpells*>(warr->get_spells());
    spells->remove_pre_combat_spell(spells->get_anger_management());
}
