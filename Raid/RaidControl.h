#pragma once

#include <QVector>

class Buff;
class Character;

namespace InstanceID {
    static const int INACTIVE = -1;
    static const int INITIAL_ID = 0;
}

class RaidControl {
public:
    void apply_raid_buff(Buff* buff);
    void apply_party_buff(Buff* buff, const int party);

    void remove_raid_buff(Buff* buff);
    void remove_party_buff(Buff* buff, const int party);

    int next_instance_id();

private:
    int instance_id {InstanceID::INITIAL_ID};

    QVector<QVector<Character*>> group_members;
};
