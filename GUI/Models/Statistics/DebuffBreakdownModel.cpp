
#include "NumberCruncher.h"
#include "DebuffBreakdownModel.h"
#include "StatisticsBuff.h"

DebuffBreakdownModel::DebuffBreakdownModel(NumberCruncher* statistics_source) :
    BuffBreakdownModel(statistics_source)
{}

void DebuffBreakdownModel::add_statistics() {
    statistics_source->merge_buff_stats(buff_stats, true);
}
