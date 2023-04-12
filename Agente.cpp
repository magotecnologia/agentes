#include <iostream>
#include <vector>
#include <list>
#include <string>
#include <windows.h>
struct Room
{
    public:
    char name;
    bool isClean;
};

class World{
    std::vector<Room> rooms;
    public:
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
};

struct Step
{
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
    World world=World();
    
    Room first			= Room();
    first.name			= 'A';
    first.isClean		= true;
    
    Room second			= Room();
    second.name			= 'B';
    second.isClean		= false;
    
    Room third			= Room();
    third.name			= 'C';
    third.isClean		= true;
    
    Room four			= Room();
    four.name			= 'D';
    four.isClean		= false;
    
    Room five			= Room();
    five.name			= 'E';
    five.isClean		= false;
    
    Room six			= Room();
    six.name			= 'F';
    six.isClean			= false;
    
    Room seven			= Room();
    seven.name			= 'G';
    seven.isClean		= true;
    
    Room eight			= Room();
    eight.name			= 'H';
    eight.isClean		= true;
    
    Room nine			= Room();
    nine.name			= 'I';
    nine.isClean		= false;
    
    Room ten			= Room();
    ten.isClean			= false;
    ten.name			= 'J';
    
    world.addRoom(&first);
    world.addRoom(&second);
    world.addRoom(&third);
    world.addRoom(&four);
    world.addRoom(&five);
    world.addRoom(&six);
    world.addRoom(&seven);
    world.addRoom(&eight);
    world.addRoom(&nine);
    world.addRoom(&ten);
    Agent agent=Agent(world);
    agent.start();
}
