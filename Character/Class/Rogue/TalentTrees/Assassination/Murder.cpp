#include "Murder.h"

#include "Character.h"
#include "CharacterStats.h"
#include "Target.h"

Murder::Murder(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Murder", "2ML", "Assets/spell/Spell_shadow_deathscream.png", 2)
{
    QString base_str = "Increases all damage caused against Humanoid, Giant, Beast and Dragonkin targets by %1%.";
    initialize_rank_descriptions(base_str, 1, 1);
}

Murder::~Murder() = default;

void Murder::apply_rank_effect() {
    pchar->get_stats()->increase_dmg_vs_type(Target::CreatureType::Beast, 0.01);
    pchar->get_stats()->increase_dmg_vs_type(Target::CreatureType::Dragonkin, 0.01);
    pchar->get_stats()->increase_dmg_vs_type(Target::CreatureType::Giant, 0.01);
    pchar->get_stats()->increase_dmg_vs_type(Target::CreatureType::Humanoid, 0.01);
}

void Murder::remove_rank_effect() {
    pchar->get_stats()->decrease_dmg_vs_type(Target::CreatureType::Beast, 0.01);
    pchar->get_stats()->decrease_dmg_vs_type(Target::CreatureType::Dragonkin, 0.01);
    pchar->get_stats()->decrease_dmg_vs_type(Target::CreatureType::Giant, 0.01);
    pchar->get_stats()->decrease_dmg_vs_type(Target::CreatureType::Humanoid, 0.01);
}
