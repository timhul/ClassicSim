#ifndef RESOURCE_H
#define RESOURCE_H

enum ResourceType {
    Mana = 0,
    Rage = 1,
    Energy = 2
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

#endif // RESOURCE_H
