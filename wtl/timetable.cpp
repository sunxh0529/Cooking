#include "timetable.h"
#include "log.h"

TimeTable::TimeTable()
{
    this->from = -1;
}

TimeTable::TimeTable(int from, int to, QString num, QTime begin, QTime end, int vehicle)
{
    this->from = from;
    this->to = to;
    this->num = num;
    this->begin = begin;
    this->end = end;

    //交通风险值

//    qDebug()<<"begin = "<<begin;
//    qDebug()<<"end = "<<end;
    double tempHour = (end.hour()-begin.hour() + 24) % 24;


    this->cost = riskCity[from] * riskVehicle[vehicle] * tempHour;

//    qDebug()<<"num = "<<num;
//    qDebug()<<"riskCity[from] = "<<riskCity[from];
//    qDebug()<<"riskVehicle[vehicle] = "<<riskVehicle[vehicle];
//    qDebug()<<"tempHour = "<<tempHour;
//    qDebug()<<"this->cost = "<< this->cost <<endl;

    this->vehicle = vehicle;
//    qDebug() << from << to << num << begin << end << vehicle;
}

