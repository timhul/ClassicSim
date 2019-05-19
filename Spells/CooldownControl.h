#pragma once

class Character;
class Engine;

class CooldownControl {
public:
    CooldownControl(Character* pchar, double base);

    double get_cooldown_remaining() const;
    double get_next_use() const;
    void reset();
    void prepare_set_of_combat_iterations();
    void add_spell_cd_event() const;
    void add_gcd_event() const;

    Character* pchar;
    Engine* engine;

    double base;
    double last_used;
};
