#ifndef TARGET_H
#define TARGET_H

#include <QMap>
#include <QString>

class Target {
public:
    enum CreatureType {
        Beast = 0,
        Demon,
        Dragonkin,
        Elemental,
        Giant,
        Humanoid,
        Mechanical,
        Undead
    };

    Target(int target_lvl);

    int get_lvl(void) const;
    void set_lvl(int);

    int get_defense(void) const;

    QString get_creature_type() const;
    void set_creature_type(const QString& target);

    bool is_beast() const;
    bool is_demon() const;
    bool is_dragonkin() const;
    bool is_elemental() const;
    bool is_giant() const;
    bool is_humanoid() const;
    bool is_mechanical() const;
    bool is_undead() const;

protected:
private:
    int target_lvl;
    CreatureType target_type;
    QMap<QString, CreatureType> string_to_creature_type;
    QMap<CreatureType, QString> creature_type_strings;
};


#endif // TARGET_H
