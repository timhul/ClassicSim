#ifndef TARGET_H
#define TARGET_H

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
};


#endif // TARGET_H
