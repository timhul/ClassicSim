#pragma once

#include "PeriodicResourceGainSpell.h"

class EssenceOfTheRed : public PeriodicResourceGainSpell {
public:
    EssenceOfTheRed(Character* _pchar);

    void perform_start_of_combat() override;
};
