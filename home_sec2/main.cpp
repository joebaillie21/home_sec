#include "HomeSecurity.h"
#include "Room.h"
#include "Parser.h"


int main(int argc, char** argv)
{
    RoomList rooms;

    if (argc < 2)
    {
        cout << "Please provide filename"<<endl;
        return -1;
    }
    string file = argv[1];
    CSVParser p(file);
    //ROOM,SID,HH:MM:SS,TYPE[,VALUE]
    vector<string> lines = p.ReadLines();
    for (string s : lines)
    {
        if (s.length() == 0)
            continue;
        vector<string> data = p.ParseString(s);
        int roomId = stoi(data[0]);
        RoomNode* pRoomNode = rooms.FindRoom(roomId);
        if (!pRoomNode)
            pRoomNode = rooms.AddRoom(roomId);
        pRoomNode->pRoom->LoadData(data);
    }
    //cout<<"\nDone reading file\n";
    return 0;
}


