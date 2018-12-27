#ifndef SIMSETTINGS_H
#define SIMSETTINGS_H

#include <QSet>
#include <QVersionNumber>

#include "Rulesets.h"
#include "SimOption.h"

class Character;
class RulesetControl;

class SimSettings {
public:
    SimSettings();
    ~SimSettings();

    QString get_patch() const;
    void set_patch(const QString& patch);

    void set_combat_length(const int);
    void set_combat_iterations_full_sim(const int);
    void set_combat_iterations_quick_sim(const int);

    int get_combat_iterations_quick_sim() const;

    int get_combat_length() const;
    int get_combat_iterations_full_sim() const;

    int get_num_threads_current() const;
    int get_num_threads_max() const;
    void set_num_threads(const int);

    void add_sim_option(SimOption::Name);
    void set_sim_options(const QSet<SimOption::Name>&);
    void remove_sim_option(SimOption::Name);
    bool option_active(SimOption::Name) const;
    QSet<SimOption::Name> get_active_options() const;

    void use_ruleset(const Ruleset, Character*);
    Ruleset get_ruleset() const;

    double get_execute_threshold() const;
    void set_execute_threshold(const double);
    void reset_execute_threshold();

private:
    QVersionNumber current_patch;
    int combat_length;

    int combat_iterations_quick_sim;
    int combat_iterations_full_sim;
    int num_threads;
    double execute_threshold;
    RulesetControl* ruleset_control;

    QSet<SimOption::Name> sim_options;
};

#endif // SIMSETTINGS_H
