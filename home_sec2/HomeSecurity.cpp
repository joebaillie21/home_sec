#include <iostream>
#include <string>
#include "HomeSecurity.h"

using namespace std;

HomeEvent::HomeEvent()
{
    //Your code here
    timeStamp = "";
    eventId = 0;
    sensorId = 0;
    sensorValue = 0;
}

//Set the data for the event - generic.  There is an over-ride for each unique child sensor
//sensorId: The number of the sensor
//eventId: The type of event
void HomeEvent::SetData(int room, string time, int _eventId, int _sensorId, int _sensorValue)
{
    //Stage 1
    timeStamp = time;
    eventId = _eventId;
    sensorId = _sensorId;
    sensorValue = _sensorValue;
}

string HomeEvent::GetTime()
{
    //Stage 1

    return timeStamp;
}

//Return the numeric value of the event type
int HomeEvent::GetEventId()
{
    //Stage 1
    
    return eventId;
}
int HomeEvent::GetSensorId()
{
    //Stage 1

    return sensorId;
}

//Return the value of for the sensor.  If there is no valid value (an event w/o a value), return -1
int HomeEvent::GetSensorValue()
{     
    //Stage 1
    //Intruder Event, Print, and Trim will all have sensorValue -1
    
    return sensorValue;
}

//Print the event info - generic
void HomeEvent::Print(int room)
{
    //Stage 1
    cout << "Generic Sensor alert @ " << timeStamp;
    cout << ": room " << room ;
    cout <<" sensor " << sensorId << endl;
}

//Set the data for the event - specific to a temperature event.  
// Check the values to see if an alert should be printered
void TemperatureEvent::SetData(int room, string time, int _eventId, int _sensorId, int _sensorValue)
{
    //Stage 1
    timeStamp = time;
    eventId = _eventId;
    sensorId = _sensorId;
    sensorValue = _sensorValue;
    if(sensorValue > maxTemp || sensorValue < minTemp){
	    cout << "Temperature alert @ " << timeStamp << ": room " << room << " / sensor " << sensorId << " / " << sensorValue << " degrees. " << endl;
    }
}

//Print the event info - specific to temperature event
void TemperatureEvent::Print(int room)
{
    //Stage 1
    cout << "Sensor " << sensorId << " @ " << timeStamp << " temperature reading " << sensorValue << " degrees" << endl;
}

//Set the data for the event - specific to a CO event
// Check the values to see if an alert should be printered
void COEvent::SetData(int room, string time, int _eventId, int _sensorId, int _sensorValue)
{
    //Stage 1
    timeStamp = time;
    eventId = _eventId;
    sensorId = _sensorId;
    sensorValue = _sensorValue;
    if(sensorValue > maxCO){
            cout << "Carbon monoxide  alert @ " << timeStamp << ": room " << room << " / sensor " << sensorId << " / " << sensorValue << " PPB. " << endl;
    }
}

//Print the event info - specific to a CO event
void COEvent::Print(int room)
{
    //Stage 1
    cout << "Sensor " << sensorId << " @ " << timeStamp << " carbon monoxide reading " << sensorValue << " PPB" << endl;
}

//Set the data for the event - specific to an Intruder event
//Intruder events always generate an alert/ print
void IntruderEvent::SetData(int room, string time, int _eventId, int _sensorId, int _sensorValue)
{
    //Stage 1
    timeStamp = time;
    eventId = _eventId;
    sensorId = _sensorId;
    sensorValue = -1;
    cout << "Intruder alert @ " << timeStamp << ": room " << room << " / sensor " << sensorId <<  endl;
}


//Print the event info - specific to an Intruder event
void IntruderEvent::Print(int room)
{
    //Stage 1
    cout << "Sensor " << sensorId << " @ " << timeStamp << " intruder alert" << endl;
}

EventNode::EventNode()
{
    //Stage 1
    pNextNode = NULL;
    pEvent = NULL;

}

EventNode::~EventNode()
{
    //Stage 1, but not sure how to do, might complete in later stage
    if(pEvent != NULL){
	    delete pEvent;
    }

}

EventList::EventList()
{
    //Stage 1
    pEvents = NULL;
    totalEvents = 0;
}
EventList::~EventList()
{
    //Stage 1, but not sure how to do, might complete in later stage
    EventNode * hold;
    while(pEvents != NULL){
	    hold = pEvents->pNextNode;
	    delete pEvents;
	    pEvents = hold;
    }
}

//Add an event to the list
void EventList::AddEvent(EventNode* pNode)
{
    //Stage 1
    //if derefenced list pointer (should be first element) is null, set list pointer to pNode x 
    //else
    //	make hold pointer to first position x 
    //	loop with list pointer until list pointer -> next is null x 
    //	add new node as list pointer -> next x 
    //	set list pointer back to hold pointer at first position x 
	if(pEvents == NULL){
		pEvents = pNode;
	}
	else{
		EventNode * hold = pEvents;
		pEvents = pNode;
		pNode->pNextNode = hold;
	}
	totalEvents++;
}

//Trim the list; keep = how many to keep
int EventList::TrimList(int keep)
{
    //Stage 3
    int removed = 0;
    EventNode * current = pEvents;
    for(int i = 1; i < keep; ++i){
	    if(current != NULL)
		    current = current->pNextNode;
    }
    if(current == NULL)
	    return 0;
    EventNode * next = current->pNextNode;
    current->pNextNode = NULL;	//end of line
    current = next;
    while(current){
	    next = current->pNextNode;
	    delete current;
	    current = next;
	    removed++;
    }
    if(keep == 0){
	    delete pEvents;
	    pEvents = NULL;
	    removed++;
    }
    return removed;
}
void EventList::PrintList()
{
    cout<<"*********************"<<endl;
    EventNode* pNode = pEvents;//Head of list
    while (pNode)
    {
        cout<<"pNode:"<<pNode<<";pEvent:"<<pNode->pEvent<<";pNext:"<<pNode->pNextNode<<endl;
        pNode = pNode->pNextNode;
    }
    cout<<"*********************"<<endl;
}

//Return the total events that have been added over time
int EventList::GetEventCount()
{
    //Stage 1
    return totalEvents;
}

//Print all the events in the list
void EventList::PrintEvents(int _roomId)
{
    //Stage 1
    //Make a hold pointer to first position
    //Loop until pEvents->pNext is NULL (this will be the last position in the list)
    //Print pEvents->pEvent
    //set pEvents back to hold at first position
    if(pEvents != NULL){
    EventNode * hold = pEvents;
    while(hold != NULL){
	    hold->pEvent->Print(_roomId);
	    hold = hold->pNextNode;
    }
    }
}

