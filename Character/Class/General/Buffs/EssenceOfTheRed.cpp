
#include "EssenceOfTheRed.h"
#include "Character.h"
#include "CharacterStats.h"
#include "ResourceGain.h"
#include "PeriodicResourceGainSpell.h"

EssenceOfTheRed::EssenceOfTheRed(Character* pchar):
    Buff(pchar, "Essence of the Red", 180, 0),
    spell(new PeriodicResourceGainSpell(name,
                                        pchar,
                                        false, 0.0, 1.0, duration,
                                        QMap<Resource, unsigned>({{Resource::Mana, 500},
                                                                  {Resource::Rage, 20},
                                                                  {Resource::Energy, 50}
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
