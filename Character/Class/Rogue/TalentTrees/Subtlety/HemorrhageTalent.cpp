#include "HemorrhageTalent.h"

#include "Hemorrhage.h"
#include "Rogue.h"
#include "RogueSpells.h"

HemorrhageTalent::HemorrhageTalent(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Hemorrhage", "5RR", "Assets/spell/Spell_shadow_lifedrain.png", 1),
    hemorrhage(dynamic_cast<RogueSpells*>(dynamic_cast<Rogue*>(pchar)->get_spells())->get_hemorrhage())
{
    QString base_str = "An instant strike that damages the opponent and causes the target to hemorrhage, increasing any Physical damage dealt to the target by up to 3. Lasts 30 charges or 15 sec. Awards 1 combo point.";
    rank_descriptions.insert(0, base_str);
    rank_descriptions.insert(1, base_str);
}

HemorrhageTalent::~HemorrhageTalent() = default;

void HemorrhageTalent::apply_rank_effect() {
    hemorrhage->increase_talent_rank(hemorrhage, name);
}

void HemorrhageTalent::remove_rank_effect() {
    hemorrhage->decrease_talent_rank(hemorrhage, name);
}
