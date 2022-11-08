#include "Room.h"
#include <iostream>

Room::Room()
{
	//Stage 1
	roomId = 0;
	eventList = EventList();
}


Room::~Room()
{
    //Stage 1 not sure how to do, might save for a later part of the project
}

void Room::SetRoomId(int _roomId){
	this->roomId = _roomId;
}

int Room::GetRoomId()
{
    return roomId;
}

//Adds an event to the event list for this room
void Room::AddEvent(EventNode* p)
{
    //Stage 1
    eventList.AddEvent(p);
}

//Given a vector (array of strings) of data, in the prescribed format, adds the event and other info
//Based on the sensor type, create the appropriate event
//or, if it is not a sensor type (a command), process the command
void Room::LoadData(vector<string> data)
{
    //ROOM,SID,HH:MM:SS,TYPE[,VALUE]
    //Room = Room #, SID = Sensor ID (a number), 
    //HH:MM:SS=Timestamp as string, Type=SensorType,Value=numeric value of sensor

    //Stage 1
    //Input 0 = room
    //Input 1 = Sensor ID
    //Input 2 = Time
    //Input 3 = Type of event (1 = temp, 2 = CO, 3 = Intruder)
    //Input 4 = temp or CO reading, only exists if input 4 is 1 or 2
    //stoi(str) gives integer value of string

    //Make EventNode
    //Make event
    //set EventNode event to created event
    //break
    EventNode * eventN = new EventNode();
    int _roomId = stoi(data[0]);
    int sensorId = stoi(data[1]);
    string timeStamp = data[2];
    int eventId = stoi(data[3]);
    switch(eventId){
	    case 1:
		    {
		    int sensorValue = stoi(data[4]);
		    TemperatureEvent * event = new TemperatureEvent();
		    event->SetData(_roomId, timeStamp, eventId, sensorId, sensorValue);
		    eventN->pEvent = event;
		    eventList.AddEvent(eventN);
		    break;
		    }
	    case 2: 
		    {
		    int sensorValue = stoi(data[4]);
                    COEvent * event = new COEvent();
                    event->SetData(_roomId, timeStamp, eventId, sensorId, sensorValue);
                    eventN->pEvent = event;
                    eventList.AddEvent(eventN);
		    break;
		    }
	    case 3:
		    {
		    int sensorValue = -1;
                    IntruderEvent * event = new IntruderEvent();
                    event->SetData(_roomId, timeStamp, eventId, sensorId, sensorValue);
                    eventN->pEvent = event;
                    eventList.AddEvent(eventN);
		    break;
		    }
	    case 8:
		    {
		    int sensorValue = stoi(data[4]);    
		    TrimEvents(sensorValue, timeStamp);
		    delete eventN;
		    break;
		    }
	    case 9:
		    {
		    PrintEvents(timeStamp, sensorId, eventId);
		    delete eventN;
                    break;
                    }
	    default:
		    {
		    cout << "Invalid eventId input." << endl;
		    break;
		    }
    }
}

//Print the events for this room
void Room::PrintEvents(string time, int sensor, int eventType)
{
    //Stage 1
    cout << "*****" << endl;
    cout << "Home Security System: Room " << roomId << " at " << time << endl;
    cout << "Triggered by sensor " << sensor << endl;
    cout << eventList.GetEventCount() << " total room events" << endl;
    eventList.PrintEvents(roomId);
}

//Trim the event list; keep N, based on the argument 'keep' passed in.
void Room::TrimEvents(int keep, string time)
{
    //Stage 3
    int removed = eventList.TrimList(keep);
    cout << "Trim log @ " << time << ": room " << roomId << " log trimmed to length " << keep << " (" << removed << " entries removed). " << endl;
}

RoomNode::RoomNode()
{
    pNextNode = NULL;
    pRoom = new Room(); 
}

RoomNode::~RoomNode()
{
    //Stage 1
    delete pRoom;
}

RoomList::RoomList()
{
    //Stage 1?
    pRoomHead = NULL;
}

RoomList::~RoomList()
{
    //Clean up the list
    //Stage 1 Should probably do in stage 1 but don't understand destructor
    RoomNode * hold;
    while(pRoomHead != NULL){
	    hold = pRoomHead->pNextNode;
	    delete pRoomHead;
	    pRoomHead = hold;
    }

}

//Add a room to the list of rooms and return the pointer to the created object
RoomNode* RoomList::AddRoom(int roomId){
	RoomNode * roomN = new RoomNode();
	roomN->pRoom->SetRoomId(roomId); 
	if(pRoomHead == NULL){
		pRoomHead = roomN;
		return pRoomHead;
	}
	else {
		RoomNode * hold = pRoomHead; 
		while(hold->pNextNode != NULL){
			hold = hold->pNextNode;
		}
		hold->pNextNode = roomN;
		return hold->pNextNode;
	}
}

//Given a roomId, find a room and return the pointer to the object
RoomNode* RoomList::FindRoom(int roomId)
{
	if(pRoomHead == NULL){
		return NULL;
	}
    RoomNode * hold = pRoomHead;
    while(hold != NULL){
	    if(hold->pRoom->GetRoomId() == roomId){
		    return hold;
	    }
	    hold = hold->pNextNode;
    }
    return NULL;


}
