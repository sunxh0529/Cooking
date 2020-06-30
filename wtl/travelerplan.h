#ifndef TRAVELERPLAN_H
#define TRAVELERPLAN_H

#include "timetable.h"
#include "schedule.h"

#include <vector>
#include <QDateTime>
#include <QDate>
#include <QTime>
#include <cmath>
#include <cfloat>
#include <map>
#include <queue>
#include <set>
#include <iostream>
#include <utility>

const double h = 0.5;//设置启发函数

class TravelerPlan
{
public:
    int id, strategy;
    int origin, destination;

//    startTime 加入旅客的时间
//    ddlTime 限制的最大时间
//    usedTime 已经使用的时间
//    totalTime 行程的总时间 = 到达时间 - startTime
    QDateTime startTime, deadlineTime, usedTime, totalTime;

    TravelerPlan(int, QDateTime, QDateTime, int, int, int);
    std::vector<TimeTable> getPlan();
    QDateTime getCityArrivalDateTime(int);
    QDateTime getCityDepartureDateTime(int);

private:
    std::vector<TimeTable> plan;//旅客的最优路径
    std::vector<QDateTime> time;//旅客到达每个城市的时间

    std::vector<TimeTable> AStar(std::vector<bool> &, std::vector<QDateTime>&);
    std::vector<TimeTable> SPFA(std::vector<bool> &,std::vector<QDateTime>&);
    std::vector<TimeTable> DijkstraHeap(std::vector<bool>& , std::vector<QDateTime>&);
    std::vector<TimeTable> Dijkstra(std::vector<bool> &, std::vector<QDateTime>&);
    void MakePlan(int, const std::vector<TimeTable>&, std::vector<TimeTable> &);
    void UpdateAdjacents(int, std::vector<double>& , std::vector<bool>&,std::vector<TimeTable>&);
    QDateTime CalculateTime();
    QDateTime TotalDateTime();

    double minDanger;//最小风险
    QDateTime minTime;//最少时间，策略2*
};

#endif // TRAVELERPLAN_H
