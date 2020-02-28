#include "EssenceOfTheRed.h"

#include "Resource.h"

EssenceOfTheRed::EssenceOfTheRed(Character* _pchar) :
    PeriodicResourceGainSpell("Essence of the Red",
                              "Assets/spell/Spell_fire_lavaspawn.png",
                              _pchar,
                              RestrictedByGcd::No,
                              1.0,
                              180,
                              QVector<QPair<ResourceType, unsigned>>(
                                  {{ResourceType::Mana, 500}, {ResourceType::Rage, 20}, {ResourceType::Energy, 50}})) {
    this->enabled = false;
    this->start_of_combat_spell = true;
}

void EssenceOfTheRed::perform_start_of_combat() {
    perform();
}
