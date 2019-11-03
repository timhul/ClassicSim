#include "Vigor.h"

#include "Energy.h"
#include "Rogue.h"

Vigor::Vigor(Rogue* rogue, TalentTree* tree_) :
    Talent(rogue, tree_, "Vigor", "7ML", "Assets/spell/Spell_nature_earthbindtotem.png", 1),
    rogue(rogue)
{
    QString base_str = "Increases your maximum Energy by 10.";
    rank_descriptions.insert(0, base_str);
    rank_descriptions.insert(1, base_str);
}

void Vigor::apply_rank_effect() {
    rogue->get_energy()->max_energy_bonus += 10;
    rogue->get_energy()->reset_resource();
}

void Vigor::remove_rank_effect() {
    rogue->get_energy()->max_energy_bonus -= 10;
    rogue->get_energy()->reset_resource();
}
