#ifndef TIMETABLE_H
#define TIMETABLE_H

#include <QTime>
#include <vector>
#include <QDebug>

class TimeTable
{
public:
    TimeTable();
    TimeTable(int, int, QString, QTime, QTime, int);
    int from, to, vehicle;
    double cost;
    QString num;
    QTime begin, end;
    std::vector<double> riskVehicle = {2.0,5.0,9.0};
    std::vector<double> riskCity = {0.2,0.5,0.9,0.2,0.5,0.9,0.2,0.5,0.9,0.2,0.5,0.9};
};

#endif // TIMETABLE_H
