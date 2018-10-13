#ifndef SIMSETTINGS_H
#define SIMSETTINGS_H

class SimSettings {
public:
    SimSettings();

    void set_combat_length(const int);
    void set_combat_iterations(const int);

    int get_combat_length() const;
    int get_combat_iterations() const;

private:
    int combat_length;
    int combat_iterations;
};

#endif // SIMSETTINGS_H
