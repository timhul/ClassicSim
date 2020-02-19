#include "DamageMetersModel.h"

#include "NumberCruncher.h"

bool max_dps(const RaidMemberResult* lhs, const RaidMemberResult* rhs) {
    return lhs->dps > rhs->dps;
}

DamageMetersModel::DamageMetersModel(NumberCruncher* statistics_source, QObject* parent) :
    QAbstractListModel(parent), statistics_source(statistics_source) {}

DamageMetersModel::~DamageMetersModel() {
    for (const auto& result : player_results)
        delete result;
}

void DamageMetersModel::update_statistics() {
    if (!player_results.empty()) {
        beginResetModel();

        for (const auto& result : player_results)
            delete result;

        player_results.clear();
        endResetModel();
    }

    beginInsertRows(QModelIndex(), 0, rowCount());
    player_results = statistics_source->player_results.toList();
    endInsertRows();

    layoutAboutToBeChanged();
    std::sort(player_results.begin(), player_results.end(), max_dps);
    this->max_recorded_dps = player_results[0]->dps;
    layoutChanged();
}

int DamageMetersModel::rowCount(const QModelIndex& parent) const {
    Q_UNUSED(parent);
    return player_results.count();
}

QVariant DamageMetersModel::data(const QModelIndex& index, int role) const {
    if (index.row() < 0 || index.row() >= player_results.count())
        return QVariant();

    const RaidMemberResult* result = player_results[index.row()];

    if (role == DamageRoles::NameRole)
        return result->player_name;
    if (role == DamageRoles::DpsRole)
        return QString::number(result->dps, 'f', 2);
    if (role == DamageRoles::DpsRatioRole)
        return result->dps / max_recorded_dps * 100;
    if (role == DamageRoles::DpsRatioStringRole)
        return QString::number(result->dps / max_recorded_dps * 100, 'f', 2);
    if (role == DamageRoles::ClassColor)
        return result->class_color;
    if (role == DamageRoles::PlaceRole)
        return index.row() + 1;

    return QVariant();
}

QHash<int, QByteArray> DamageMetersModel::roleNames() const {
    QHash<int, QByteArray> roles;
    roles[DamageRoles::NameRole] = "_name";
    roles[DamageRoles::DpsRole] = "_dps";
    roles[DamageRoles::DpsRatioRole] = "_dpsratio";
    roles[DamageRoles::DpsRatioStringRole] = "_dpsratiostring";
    roles[DamageRoles::ClassColor] = "_classcolor";
    roles[DamageRoles::PlaceRole] = "_place";

    return roles;
}
