#pragma once
#include "item/item.h"
#include <memory>
#include <QGraphicsScene>
#include "item/machining.h"
#include "item/checkout.h"
#include "item/finished_product.h"

using constructor = std::unique_ptr<item> (*) (item* parent);

inline std::unique_ptr<item> make_item (const QString& classname, QPointF pos)
{
    using up_item = std::unique_ptr<item>;
    using item_maker = up_item (*) (QPointF);

    static std::map<QString, item_maker> type_map
    {
        {"加工", [] (QPointF p)->up_item { return machining::make (p, Qt::black); }},
        {"检验", [] (QPointF p)->up_item { return checkout::make (p, Qt::black); }}
//        {"产成品", [] (QPointF p)->up_item { return finished_product::make (p, Qt::black); }}

    };

    auto found = type_map.find(classname);
    if (found == type_map.end() or found->second == nullptr)
    {
        return nullptr;
    }

    return (found->second) (pos);
}

