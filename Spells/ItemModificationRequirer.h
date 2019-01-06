#ifndef ITEMMODIFICATIONREQUIRER_H
#define ITEMMODIFICATIONREQUIRER_H

#include <QSet>

class ItemModificationRequirer {
public:
    ItemModificationRequirer(const QSet<int>& item_ids);
    virtual ~ItemModificationRequirer() = default;

    void activate_item_modification(const int item_id);
    void deactivate_item_modification(const int item_id);

protected:
    const QSet<int> item_ids;

    virtual void activate_item_effect(const int item_id) = 0;
    virtual void deactivate_item_effect(const int item_id) = 0;
};

#endif // ITEMMODIFICATIONREQUIRER_H
