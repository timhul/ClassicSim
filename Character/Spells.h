#ifndef SPELLS_H
#define SPELLS_H

#include <QObject>
#include <QVector>

class Berserking;
class BloodFury;
class Character;
class Spell;
class MainhandAttack;
class OffhandAttack;

static const bool NO_RELINK = false;

class Spells: public QObject {
    Q_OBJECT

public:
    Spells(Character* pchar, QObject* parent = nullptr);
    virtual ~Spells();

    void activate_racials();
    void deactivate_racials();

    void add_spell(Spell* spell, bool relink=true);
    void remove_spell(Spell* spell);

    Spell* get_spell_by_name(const QString& spell_name) const;

    void reset();

    virtual void start_attack();
    virtual void mh_auto_attack(const int);
    virtual void oh_auto_attack(const int);
    virtual void add_next_mh_attack(void);
    virtual void add_next_oh_attack(void);

    void prepare_set_of_combat_iterations();

    virtual MainhandAttack* get_mh_attack() const;
    virtual OffhandAttack* get_oh_attack() const;

    Berserking* get_berserking() const;
    BloodFury* get_blood_fury() const;

protected:
    Character* pchar;
    QVector<Spell*> spells;

    MainhandAttack* mh_attack{};
    OffhandAttack* oh_attack{};

    Berserking* berserking;
    BloodFury* blood_fury;

    int next_instance_id;

private:
};

#endif // SPELLS_H
