#pragma once

#include <QMap>
#include <QString>
#include <QVector>

class Buff;
class Character;
class ClassStatistics;
class Engine;
class SimSettings;

namespace InstanceID {
    static const int INACTIVE = -1;
    static const int INITIAL_ID = 0;
}

class RaidControl {
public:
    RaidControl(SimSettings* sim_settings);
    ~RaidControl();

    void assign_character_to_group(Character* pchar);

    void apply_party_buff(Buff* buff, const int party);
    void remove_party_buff(Buff* buff, const int party);

    void apply_raid_buff(Buff* buff);
    void remove_raid_buff(Buff* buff);

    int next_instance_id();

    void register_shared_party_buff(Buff* buff, const int party);
    Buff* get_shared_party_buff(const QString& buff_name, const int party) const;

    void register_shared_raid_buff(Buff* buff);
    Buff* get_shared_raid_buff(const QString& buff_name) const;

    ClassStatistics* get_statistics() const;
    ClassStatistics* relinquish_ownership_of_statistics();

    Engine* get_engine() const;

private:
    int instance_id {InstanceID::INITIAL_ID};

    ClassStatistics* raid_statistics;
    SimSettings* settings;
    Engine* engine;

    QVector<QVector<Character*>> group_members;

    QMap<QString, Buff*> shared_raid_buffs;
    QVector<QMap<QString, Buff*>> shared_party_buffs;
};
