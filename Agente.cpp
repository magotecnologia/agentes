#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <windows.h>
#include <cmath>
#include <cstdlib>

struct Room
{
    public:
    char name;
    bool isClean;
};

class World{
    std::vector<Room> rooms;
    public:
    World(int size);
    void addRoom(Room *room){
        rooms.push_back(*room);
    }
    void clean(int n){
        rooms.at(n).isClean=true;
    }
    Room sense(int n){
        return rooms.at(n);
    }
    int size(){
        return rooms.size();
        }
    void show(){
        for(int i=0; i<rooms.size();i++){
            printf("| %d |",i);
        }
        printf("\n");
        
        for(int i=0; i<rooms.size();i++){
            char status;
            if(rooms.at(i).isClean){
                status= 'O';
            }
            else{
                status= 'X';
            }
            printf("| %c |",status);
        }
        printf("\n");
    } 
    void remoteRoom(){
        printf("Eliminando el cuarto %d \n",rooms.size());
        rooms.pop_back();
    }
    
    void mutate(){
        bool isGrowing=generateBool();
        if(!isGrowing || growingStreak==10 ){
            remoteRoom();
        }
        else{   
            Room newRoom=Room();
            newRoom.isClean=generateBool();
            printf("Creando un nuevo cuarto \n");
            addRoom(&newRoom);
        }
        show();
    }
    private:
    Room createRandomRoom(){
        Room newRoom=Room();
        newRoom.isClean=generateBool();
        return newRoom;
    }
    bool generateBool(){
        static const int shift = static_cast<int>(std::log2(RAND_MAX));
        bool isOdd=(rand() >> shift) & 1;;
        return (isOdd);
    }
    int growingStreak=0;
    
};

World::World(int size){
    for(int i=0;i<size;i++){
        Room newRoom=createRandomRoom();
        addRoom(&newRoom);
    }
}

class Step
{
    public:
    Room persection;
    bool reaction;    
};

//set fullscreen
void toFullscreen(){
	keybd_event(VK_MENU,
                0x38,
                0,
                0);
    keybd_event(VK_RETURN,
                0x1c,
                0,
                0);
    keybd_event(VK_RETURN,
                0x1c,
                KEYEVENTF_KEYUP,
                0);
    keybd_event(VK_MENU,
                0x38,
                KEYEVENTF_KEYUP,
                0);
    return;
}

class Agent{
    std::list<Step> history;
    int roomNumber;
    World& world;
    bool lastAction;

    public:
    Agent (World& world):world(world){}
	
    void start(){
        roomNumber=0;
        while(roomNumber<world.size()){
            Step step;
            step.persection= sense(roomNumber);
            step.reaction=react(step.persection);
            lastAction=step.reaction;
            history.push_back(step);
            printLastAction();   
            printSteps();
        }
    }


    private:
    Room sense(int roomNumber){
        return world.sense(roomNumber);
    }

    void printSteps(){
        for(Step step: history){
            std::string cleanString;
            if(step.persection.isClean){
                cleanString= "LIMPIO";
            }
            else{
                cleanString="SUCIO";
            }
            printf("[%c %s]",step.persection.name,cleanString.c_str());
        }
        printf("\n");
    }

    void printLastAction(){
        std::string lastActionString;
        if(lastAction){
            lastActionString="DERECHA";
        }
        else{
            lastActionString="ASPIRAR";
        }
        printf(" %s \t",lastActionString.c_str());
    }

    bool react(Room room){
        if(room.isClean){
            mover();
        }
        else{
            clean(roomNumber);
        }
        return room.isClean;
        world.mutate();
    }
    
    void clean(int n){
        world.clean(n);
    }

    void mover(){
        roomNumber++;
    }
};

int main()
{
	toFullscreen();
    World world=World(10);
    Agent agent=Agent(world);
    world.show();
    agent.start();
}
