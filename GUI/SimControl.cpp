
#include "Character.h"
#include "ClassStatistics.h"
#include "CombatRoll.h"
#include "EncounterEnd.h"
#include "EncounterStart.h"
#include "SimControl.h"
#include "SimSettings.h"

SimControl::SimControl(SimSettings* sim_settings) :
    sim_settings(sim_settings)
{}

void SimControl::run_sim(Character* pchar) {
    pchar->get_statistics()->reset_statistics();
    pchar->get_engine()->prepare();
    pchar->get_combat_roll()->drop_tables();

    for (int i = 0; i < sim_settings->get_combat_iterations(); ++i) {
        auto* start_event = new EncounterStart(pchar);
        auto* end_event = new EncounterEnd(pchar->get_engine(), pchar, sim_settings->get_combat_length());

        pchar->get_engine()->add_event(end_event);
        pchar->get_engine()->add_event(start_event);
        pchar->get_engine()->run();
    }

    pchar->get_engine()->reset();
}
