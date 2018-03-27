#ifndef TALENTS_H
#define TALENTS_H

#include <QObject>

#include "TalentTree.h"

class Talents: public QObject {
    Q_OBJECT
public:
    Talents(QObject* parent = 0);

    ~Talents();

    Q_PROPERTY(int talentPointsRemaining READ get_talent_points_remaining NOTIFY talentsUpdated)

    Q_INVOKABLE QString getIcon(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE bool showPosition(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE bool showBottomArrow(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE bool showRightArrow(const QString tree_position, const QString talent_position) const;

    Q_INVOKABLE QString getBottomArrow(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE QString getRightArrow(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE bool bottomChildAvailable(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE bool bottomChildActive(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE bool rightChildAvailable(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE bool rightChildActive(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE bool isActive(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE bool isAvailable(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE bool isMaxed(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE bool hasTalentPointsRemaining() const;
    Q_INVOKABLE QString getRank(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE QString getMaxRank(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE void incrementRank(const QString tree_position, const QString talent_position);
    Q_INVOKABLE void decrementRank(const QString tree_position, const QString talent_position);
    Q_INVOKABLE QString getRequirements(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE QString getCurrentRankDescription(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE QString getNextRankDescription(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE int getTreePoints(const QString tree_position) const;
    Q_INVOKABLE QString getTreeName(const QString tree_position) const;
    Q_INVOKABLE QString getTalentName(const QString tree_position, const QString talent_position) const;
    Q_INVOKABLE void maxRank(const QString tree_position, const QString talent_position);
    Q_INVOKABLE void minRank(const QString tree_position, const QString talent_position);

    Q_INVOKABLE void clearTree(const QString tree_position);

    void set_talent_tree(const QString &tree_position, TalentTree* tree);

    int get_talent_points_remaining() const;

Q_SIGNALS:
    void talentsUpdated();


private:
    QMap<QString, TalentTree*> talent_trees;

    int talent_points_remaining;
};

#endif // TALENTS_H
