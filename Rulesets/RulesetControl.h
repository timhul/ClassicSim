#pragma once

#include "Rulesets.h"

class Character;
class SimSettings;

class RulesetControl {
public:
    RulesetControl();

    void use_ruleset(Ruleset, Character*, SimSettings* sim_settings);
    Ruleset get_active_ruleset() const;

private:
    Ruleset active_ruleset;

    void use_vaelastrasz_ruleset(Character*, SimSettings* sim_settings);
    void remove_vaelastrasz_ruleset(Character*, SimSettings* sim_settings);
};
