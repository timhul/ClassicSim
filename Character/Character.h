#ifndef CHARACTER_H
#define CHARACTER_H

#include <QString>
#include <QMap>
#include <QObject>

class Race;
class Engine;
class Equipment;
class TalentTree;

class Character: public QObject {
    Q_OBJECT

public:
    Character(Race*, Engine*, Equipment*, QObject* parent = 0);

    Race* get_race(void);
    virtual QString get_name() const = 0;

    Q_INVOKABLE QString getIcon(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE bool showPosition(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE bool isActive(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE bool isAvailable(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE bool isMaxed(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE QString getRank(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE QString getMaxRank(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE void incrementRank(const QString tree_position, const QString talent_position);
    Q_INVOKABLE void decrementRank(const QString tree_position, const QString talent_position);
    Q_INVOKABLE int getTreePoints(const QString tree_position) const;
    Q_INVOKABLE void maxRank(const QString tree_position, const QString talent_position);
    Q_INVOKABLE void minRank(const QString tree_position, const QString talent_position);

    virtual void rotation(void) = 0;
    virtual void mh_auto_attack(const int) = 0;
    virtual void oh_auto_attack(const int) = 0;

    virtual int get_strength_modifier() const = 0;
    virtual int get_agility_modifier() const = 0;
    virtual int get_stamina_modifier() const = 0;
    virtual int get_intellect_modifier() const = 0;
    virtual int get_spirit_modifier() const = 0;

    int get_strength();
    int get_agility();
    int get_stamina();
    int get_intellect();
    int get_spirit();
    float get_hit_chance(void) const;
    float get_crit_chance(void) const;
    int get_clvl(void) const;
    void set_clvl(const int&);
    Engine* get_engine(void) const;
    Equipment* get_equipment(void) const;
    bool is_dual_wielding(void);
    bool is_melee_attacking(void) const;
    void start_attack(void);
    void stop_attack(void);
    bool action_ready(void) const;
    virtual float global_cooldown() const;

    int get_mh_dmg();
    int get_oh_dmg();

    int get_mh_wpn_skill();
    int get_oh_wpn_skill();
    int get_ranged_wpn_skill();

    virtual int get_melee_ap();

    virtual void increase_hit(float);
    virtual void increase_crit(float);
    virtual void increase_attack_speed(float);

    virtual void decrease_hit(float);
    virtual void decrease_crit(float);
    virtual void decrease_attack_speed(float);

    float get_mh_wpn_speed();
    float get_oh_wpn_speed();

Q_SIGNALS:
    void talentsUpdated();

protected:
    Race* race;
    Engine* engine;
    Equipment* equipment;
    int STR;
    int AGI;
    int STAM;
    int INT;
    int SPI;
    int melee_ap;
    int ranged_ap;
    float percent_hit;
    float percent_crit;
    float percent_attack_speed;
    int clvl;
    bool melee_attacking;
    float last_action;
    QMap<QString, TalentTree*> talent_trees;

    int max_talent_points;

    virtual void add_next_mh_attack(void);
    virtual void add_next_oh_attack(void);

    virtual void initialize_talents() = 0;
private:
};

#endif // CHARACTER_H
