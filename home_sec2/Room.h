#include <string>
#include <vector>
#include "HomeSecurity.h"
using namespace std;

#ifndef _ROOM_H
#define _ROOM_H
class Room
{
    public:
    Room();
    ~Room();
    void LoadData(vector<string>);
    void PrintEvents(string time, int sensorId, int eventType);
    int GetRoomId();
    void SetRoomId(int _roomId);
    void AddEvent(EventNode* p);
    void TrimEvents(int keep, string time);
    protected:
    EventList eventList; //list of events
    int roomId;
};

class RoomNode
{

    public:
        RoomNode();
        ~RoomNode();
        RoomNode* pNextNode;//Pointer to next room
        Room* pRoom; //This room
};

class RoomList
{
    public:
    RoomList();
    ~RoomList();
    RoomNode* FindRoom(int roomId);
    RoomNode* AddRoom(int roomId);
    protected:
    RoomNode* pRoomHead;
};

#endif
