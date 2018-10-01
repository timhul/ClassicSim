
#include "BoomingVoice.h"
#include "BattleShoutBuff.h"
#include "Warrior.h"

BoomingVoice::BoomingVoice(Character *pchar, TalentTree* tree) :
    Talent(pchar, tree, "Booming Voice", "1ML", "Assets/warrior/fury/tier1/Spell_nature_purge.png", 5)
{
    QString base_str = "Increases the area of effect and duration of your Battle Shout and Demoralizing Shout by %1%.";
    initialize_rank_descriptions(base_str, 10, 10);
}

BoomingVoice::~BoomingVoice() = default;

void BoomingVoice::apply_rank_effect() {
    dynamic_cast<Warrior*>(pchar)->get_battle_shout_buff()->increase_effect_via_booming_voice();
}

void BoomingVoice::remove_rank_effect() {
    dynamic_cast<Warrior*>(pchar)->get_battle_shout_buff()->decrease_effect_via_booming_voice();
}
