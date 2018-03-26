
#include "BoomingVoice.h"
#include "Character.h"

BoomingVoice::BoomingVoice(Character *pchar) :
    Talent(pchar, "Booming Voice", "1ML", "Assets/warrior/fury/tier1/Spell_nature_purge.png", 5)
{
    QString base_str = "Increases the area of effect and duration of your Battle Shout and Demoralizing Shout by %1%.";
    initialize_rank_descriptions(base_str, 10, 10);
}

BoomingVoice::~BoomingVoice() {

}

void BoomingVoice::apply_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}

void BoomingVoice::remove_rank_effect() {
    // TODO: Decide how rank effects work for this talent.
}
