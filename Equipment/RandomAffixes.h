#pragma once

#include <QMap>
#include <QString>
#include <QXmlStreamReader>

#include "ItemStatsEnum.h"

class RandomAffix;

class RandomAffixes
{
public:
    RandomAffixes();
    ~RandomAffixes();
    bool read_random_affixes(const QString& xml_file_path);
    RandomAffix * get_affix(unsigned id) const;

private:
    bool random_affixes_file_handler(QXmlStreamReader& reader);
    void add_stat_to_map(const QString &type, const QString &value, QMap<ItemStats, unsigned> &map);

private:
    QMap<unsigned, RandomAffix*> random_affixes_db;
};

