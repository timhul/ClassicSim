#include "Vigor.h"

#include "Energy.h"
#include "Rogue.h"

Vigor::Vigor(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Vigor", "7ML", "Assets/spell/Spell_nature_earthbindtotem.png", 1),
    rogue(dynamic_cast<Rogue*>(pchar))
{
    QString base_str = "Increases your maximum Energy by 10.";
    rank_descriptions.insert(0, base_str);
    rank_descriptions.insert(1, base_str);
}

Vigor::~Vigor() = default;

void Vigor::apply_rank_effect() {
    rogue->get_energy()->max += 10;
    rogue->get_energy()->reset_resource();
}

void Vigor::remove_rank_effect() {
    rogue->get_energy()->max -= 10;
    rogue->get_energy()->reset_resource();
}
