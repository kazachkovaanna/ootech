#ifndef TIMECRISTMASTREE_H
#define TIMECRISTMASTREE_H

#include <QTime>

#include "activitydiagram.h"
#include "activityitem.h"

class TimeCristmasTree
{
    using TimeActivityDiagram = ActivityDiagram<ActivityItem<int> >;

public:
    TimeCristmasTree(const TimeActivityDiagram& diagram);

    inline QTime time()
    {
        return time(_diagram.begin(), _diagram.end());
    }

protected:
    QTime time(TimeActivityDiagram::iterator start, TimeActivityDiagram::iterator stop,
        QList<TimeActivityDiagram::iterator> visited = QList<TimeActivityDiagram::iterator>());

protected:
    TimeActivityDiagram _diagram;
};

#endif // TIMECRISTMASTREE_H
