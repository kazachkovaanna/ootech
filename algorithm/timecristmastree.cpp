#include "timecristmastree.h"

TimeCristmasTree::TimeCristmasTree(const TimeActivityDiagram& diagram)
    : _diagram(diagram)
{
}

QTime TimeCristmasTree::time(TimeActivityDiagram::iterator start, TimeActivityDiagram::iterator stop, QList<TimeActivityDiagram::iterator> visited)
{
    if (start == stop)
        return QTime();

    visited.append(start);
    //    QTime time = (*start)->data() + time(++start, stop, visited);
}
