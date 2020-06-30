#include "travelerplan.h"
#include "log.h"

std::vector<double> riskVehicle = {2.0,5.0,9.0};
std::vector<double> riskCity = {0.2,0.5,0.9,0.2,0.5,0.9,0.2,0.5,0.9,0.2,0.5,0.9};

TravelerPlan::TravelerPlan(int id, QDateTime startTime, QDateTime deadlineTime,
                           int strategy, int origin, int destination):
    id(id), strategy(strategy), origin(origin), destination(destination),
    startTime(startTime), deadlineTime(deadlineTime), usedTime(QDateTime(QDate(1, 1, 1), QTime(0, 0, 0, 0))),
    time(12, QDateTime(QDate(7999, 12, 31), QTime(23, 59, 59))),minDanger(0x7FFFFFFF),
    minTime(QDateTime(QDate(7999, 12, 31), QTime(23, 59, 59)))
{
    std::vector<bool> visited(12, false);//是否遍历过

    //根据不同的策略选择不同的算法
    if(strategy == 0)//无时间限制-风险最小（策略0）
        plan = DijkstraHeap(visited, time);
    else if(strategy == 1)
    {
        std::vector<QDateTime> tempTime(12, QDateTime(QDate(7999, 12, 31), QTime(23, 59, 59)));
        std::vector<double> tempDanger(12);
        std::vector<TimeTable> path;
        tempTime[origin] = startTime;//到达起点的时间 = 添加旅客的时间

//        DFS(origin, path, visited, tempTime, tempDanger);
    }
//    totalTime = TotalDateTime();
}

//std::vector<TimeTable> TravelerPlan::AStar(std::vector<bool> &visited, std::vector<QDateTime>& time)
//{
//    //将地图生成为网格图


//    typedef std::priority_queue <double,std::vector<int>,std::greater<int>> pq;//优先队列
//    pq q;//升序队列
//    std::vector<double> danger(12, DBL_MAX);
//    std::vector<TimeTable> path(12);
//    QDateTime currentTime = startTime;//加入旅客时间

//    time[origin] = currentTime;//到达起点的时间 = 加入旅客的时间
//    visited[origin] = true;//起点已访问
//    danger[origin] = h;//初始点的风险值初始化为启发函数h（便于处理先写常函数）

//    int city = origin;
//    std::set<int>open, close;
//    open.insert(city);
//    while(!open.empty())
//    {
//        UpdateAdjacents(city, danger, visited, path);
//    }
//}

std::vector<TimeTable> TravelerPlan::SPFA(std::vector<bool> &visited,std::vector<QDateTime>&time)
{
    std::vector<double> danger(12,DBL_MAX);
    std::vector<TimeTable> path(12);
    QDateTime currentTime = startTime;
    time[origin] = currentTime;

    std::queue<int> q;
    q.push(origin), danger[origin] = 0, visited[origin] = true;

    while(!q.empty())
    {
        int now = q.front(); q.pop(); visited[now] = false;//可重复入队列
        UpdateAdjacents(now, danger, visited, path);
    }
    std::vector<TimeTable> plan;
    MakePlan(destination, path, plan);
    return plan;
}

std::vector<TimeTable> TravelerPlan::Dijkstra(std::vector<bool> &visited, std::vector<QDateTime>& time)
{
    std::vector<double> danger(12, DBL_MAX);//记录起点到每个点的风险
    std::vector<TimeTable> path(12);

    QDateTime currentTime = startTime;//加入旅客时间
    time[origin] = currentTime;//到达起点的时间 = 加入旅客的时间
    visited[origin] = true;//起点已访问
    danger[origin] = 0;//
    int city = origin;
    while(true)
    {
        UpdateAdjacents(city, danger, visited, path);
        city = -1;
        double min = DBL_MAX;

        //寻找未访问点的最小权值
        for(std::vector<double>::size_type ix = 0; ix != danger.size(); ++ix)
        {
            if(!visited[ix] && min > danger[ix])
            {
                min = danger[ix];
                city = ix;
            }
        }
        if(city == -1) break;
        visited[city] = true;
    }
    qDebug() << "Loop finish...";
    std::vector<TimeTable> plan;
    MakePlan(destination, path, plan);
    qDebug() <<"Makeplan finish...";

    return plan;
}

std::vector<TimeTable> TravelerPlan::DijkstraHeap(std::vector<bool> &visited, std::vector<QDateTime>& time)
{
    std::vector<double> danger{12,DBL_MAX}; danger[origin]=0;
    std::vector<TimeTable> path(12);
    QDateTime currentTime = startTime; time[origin] = currentTime;
    std::priority_queue<std::pair<double, int> > q;//first 为风险，second为边的终点
    q.push({-danger[origin],origin});
    while(!q.empty())
    {
        int now = q.top().second; q.pop();
        if(visited[now]) continue;
        visited[now] = true;
        UpdateAdjacents(now, danger, visited, path);//更新danger、time、path
    }
    std::vector<TimeTable> plan;
    MakePlan(destination, path, plan);
    return plan;
}

void TravelerPlan::MakePlan(int city, const std::vector<TimeTable>& path, std::vector<TimeTable> &plan)
{
    if(path[city].from == -1)
        return;
    if(city != origin)
    {
        MakePlan(path[city].from, path, plan);
        plan.push_back(path[city]);
        qDebug() << path[city].from << path[city].num <<path[city].to;
    }
    qDebug() <<"MakePlan";
}

//更新danger、time 和 path
void TravelerPlan::UpdateAdjacents(int city, std::vector<double>& danger, std::vector<bool>& visited,
                                   std::vector<TimeTable>& path)
{
    typedef std::multimap<int, TimeTable>::size_type sz_type;
    sz_type entries = Schedule::database.count(city);

    std::multimap<int, TimeTable>::iterator iter = Schedule::database.find(city);
    for(sz_type cnt = 0; cnt < entries; ++cnt, ++iter)
    {
        //cost += 起点城市的等待时间
        iter->second.cost += riskCity[iter->second.from] * ((iter->second.begin.hour()
              - time[iter->second.from].time().hour() + 24) % 24);
        if(!visited[iter->second.to] && danger[iter->second.to] > danger[city] + iter->second.cost)
        {
            danger[iter->second.to] = danger[city] + iter->second.cost;

            //SPFA时解开以下注释
//            visited[iter->second.to] = true; q.push(iter->second.to);//要把SPFA中的队列q作为参数传入

            //添加path
            path[iter->second.to] = iter->second;

            //判断航班是否跨天
            bool span;
            if(iter->second.begin <= iter->second.end) span = false;//航班没跨天
            else span = true;

            //更新日期
            QDate timeDate = time[iter->second.from].date();//记录起点城市的到达时间
            if(!span && time[iter->second.from].time() <= iter->second.begin)//航班没跨天 + 等待没跨天
                time[iter->second.to] = QDateTime(timeDate, iter->second.end);
            else if(!span && time[iter->second.from].time() > iter->second.begin)//航班没跨天 + 等待跨天
                time[iter->second.to] = QDateTime(timeDate.addDays(1), iter->second.end);
            else if(span && time[iter->second.from].time() <= iter->second.begin)//航班跨天 + 等待没跨天
                time[iter->second.to] = QDateTime(timeDate.addDays(1), iter->second.end);
            else if(!span && time[iter->second.from].time() <= iter->second.begin)//航班跨天 + 等待跨天
                time[iter->second.to] = QDateTime(timeDate.addDays(2), iter->second.end);
        }
    }
}

