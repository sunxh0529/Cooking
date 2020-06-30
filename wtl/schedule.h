#ifndef SCHEDULE_H
#define SCHEDULE_H

#include "timetable.h"

#include <vector>
#include <map>
#include <utility>
#include <algorithm>
#include <QString>
#include <QObject>
#include <QDateTime>
#include <QFile>
#include <QTextStream>
#include <QDebug>

class Schedule
{
public:
    Schedule();
    static int CityToNum(QString);//城市名字换为数字
    static std::multimap<int, TimeTable> database;//存航班表
};

#endif // SCHEDULE_H
