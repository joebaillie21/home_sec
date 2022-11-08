#include <string>
#include <vector>
using namespace std;

#ifndef _HOMESEC_H
#define _HOMESEC_H


class HomeEvent
{
    public:
    HomeEvent();
    virtual void Print(int room);
    string GetTime();
    int GetEventId();
    int GetSensorId();
    int GetSensorValue();
    virtual void SetData(int room, string time, int eventId, int sensorId, int sensorValue);
    protected:
    string timeStamp;
    int eventId;
    int sensorId;
    int sensorValue;
};

class TemperatureEvent: public HomeEvent
{
    public:
    const int minTemp = 50;
    const int maxTemp = 110;
    void Print(int room);
    void SetData(int room, string time, int eventId, int sensorId, int sensorValue);
};

class COEvent: public HomeEvent
{
    public:
    const int maxCO = 3000;
    void Print(int room);
    void SetData(int room, string time, int eventId, int sensorId, int sensorValue);
};

class IntruderEvent: public HomeEvent
{
    public:
    void Print(int room);
    void SetData(int room, string time, int eventId, int sensorId, int sensorValue);
};

class EventNode
{
    public:
        EventNode();
        ~EventNode();
        EventNode* pNextNode;
        HomeEvent* pEvent;
};

class EventList
{
    public:
    EventList();
    ~EventList();
    void AddEvent(EventNode* p);
    int TrimList(int keep);
    int GetEventCount();
    void PrintEvents(int roomId);
    protected:
    void PrintList();//Useful for debug
    EventNode* pEvents;
    int totalEvents;
};

#endif
