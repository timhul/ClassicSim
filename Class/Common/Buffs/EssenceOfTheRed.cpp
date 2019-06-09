#include "EssenceOfTheRed.h"

#include "Character.h"
#include "CharacterStats.h"
#include "PeriodicResourceGainSpell.h"
#include "ResourceGain.h"

EssenceOfTheRed::EssenceOfTheRed(Character* pchar):
    SelfBuff(pchar, "Essence of the Red", "Assets/spell/Spell_fire_lavaspawn.png", 180, 0),
    spell(new PeriodicResourceGainSpell(name,
                                        "Assets/spell/Spell_fire_lavaspawn.png",
                                        pchar,
                                        false, 0.0, 1.0, duration,
                                        QVector<QPair<ResourceType, unsigned>>({{ResourceType::Mana, 500},
                                                                                {ResourceType::Rage, 20},
                                                                                {ResourceType::Energy, 50}
                                                                               })
                                        ))
{}

EssenceOfTheRed::~EssenceOfTheRed() {
    delete spell;
}

void EssenceOfTheRed::buff_effect_when_applied() {
    spell->perform();
}

void EssenceOfTheRed::buff_effect_when_removed() {
}

void EssenceOfTheRed::prepare_set_of_combat_iterations_spell_specific() {
    spell->prepare_set_of_combat_iterations();
}
