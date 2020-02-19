#pragma once

enum class ResourceType : int
{
    Mana,
    Rage,
    Energy,
    Focus
};

class Resource {
public:
    virtual ~Resource() = default;

    virtual void gain_resource(const unsigned) = 0;
    virtual void lose_resource(const unsigned) = 0;
    virtual void reset_resource() = 0;

protected:
    unsigned current;
    unsigned max;
};
