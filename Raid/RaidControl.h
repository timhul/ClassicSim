#pragma once

#include <QMap>
#include <QString>
#include <QVector>

class Buff;
class Character;
class ClassStatistics;
class Engine;
class PartyBuff;
class SharedDebuff;
class SimSettings;
class Target;

namespace InstanceID {
    static const int INACTIVE = -1;
    static const int INITIAL_ID = 0;
}

class RaidControl {
public:
    RaidControl(SimSettings* sim_settings);
    ~RaidControl();

    QPair<int, int> auto_assign_character_to_group(Character* pchar);
    void assign_character_to_place(Character* pchar, const int party, const int member);

    void apply_party_buff(PartyBuff* buff, const int party);
    void remove_party_buff(PartyBuff* buff, const int party);

    int next_instance_id();

    void register_shared_party_buff(Buff* buff, const int party);
    Buff* get_shared_party_buff(const QString& buff_name, const int party) const;

    void register_shared_raid_buff(SharedDebuff* buff);
    Buff* get_shared_raid_buff(const QString& buff_name) const;

    void reset();
    void prepare_set_of_combat_iterations();

    ClassStatistics* get_statistics() const;
    ClassStatistics* relinquish_ownership_of_statistics();
    Engine* get_engine() const;
    Target* get_target() const;
    SimSettings* get_sim_settings() const;

private:
    int instance_id {InstanceID::INITIAL_ID};

    ClassStatistics* raid_statistics;
    SimSettings* settings;
    Engine* engine;
    Target* target;

    QVector<QVector<Character*>> group_members;

    QMap<QString, Buff*> shared_raid_buffs;
    QVector<QMap<QString, Buff*>> shared_party_buffs;
};
