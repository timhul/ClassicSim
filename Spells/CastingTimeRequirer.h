#pragma once

#include <limits>

class Character;
class Engine;

enum class SuppressibleCast : bool
{
    Yes,
    No,
};

class CastingTimeRequirer {
public:
    CastingTimeRequirer(Character* caster, const SuppressibleCast suppressible_cast, const unsigned casting_time_ms);
    virtual ~CastingTimeRequirer() = default;

    double get_cast_time() const;

    void complete_cast();
    static double spell_coefficient_from_casting_time(const unsigned casting_time_ms, const unsigned level_req);

protected:
    Character* caster;
    Engine* engine;
    const SuppressibleCast suppressible_cast;
    unsigned casting_time_ms {std::numeric_limits<unsigned>::max()};
    unsigned cast_id {std::numeric_limits<unsigned>::max()};

    void start_cast();

    virtual void reset_effect();
    virtual void complete_cast_effect() = 0;
};
