#include <string>
#include <iostream>
#ifndef ullItem
#define ullItem
	#include "ull.h"
	#include "Item.h"
#endif
using namespace std;

#ifndef H_Area
#define H_Area

class Area{
  public:
    void setDescription (string desc){
    	description = desc;
    }
    void setGoal(bool g){
        goal = g;
    }
    void setID(bool id){
        instadeath = id;
    }
    string getDescription(){
    	return description;
    }
    bool getID(){
    	return instadeath;
    }
    bool getGoal(){
        return goal;
    }
    void displayArea(){
        cout<<endl<<R"(-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-=x=-)"<<endl;
        cout<<description<<endl;
    }

    uLList<Item*> items;

    void addrmDmg(InstaEffect* LvI){
        LUCKvIRONY.push_back(LvI);
    }

    void addrmEft(RollEffect* Dicey){
        Dice4Life.push_back(Dicey);
    }

    bool getLUCKvIRONY(InstaEffect* &LvI, int i){
            if(i!=LUCKvIRONY.size()){
                LvI=LUCKvIRONY[i];
                return true;
            }else{
                return false;
            }
        }
    bool getDice4Life(RollEffect* &Roll, int i){
            if(i!=Dice4Life.size()){
                Roll=Dice4Life[i];
                return true;
            }else{
                return false;
            }
    }

    void search(){
         nodeType<Item*> *list;
            list=items.getFirst();
            if(list==nullptr){
                cout<<"No items in this area."<<endl;
            }else{
                cout<<"The following items are in this area: "<<endl;
                while(list!=nullptr){
                    cout<<"\t"<<list->info->getName()<<endl;
                    list=list->link;
                }
            }
    }
    void setType(string t){
        type=t;
    }
    string getType(){
        return type;
    }
    void setInstaUsed(int u){
        instaUsed=u;
        if(instaUsedR==0)
            instaUsedR=u;
    }
    int getInstaUsed(){
        return instaUsed;
    }
    void setInstaMess(string t){
        instaMess=t;
    }
    string getInstaMess(){
        return instaMess;
    }
    void setRollUsed(int u){
        rollUsed=u;
        if(rollUsedR==0)
            rollUsedR=u;
    }
    int getRollUsed(){
        return rollUsed;
    }
     void setRollMess(string t){
        rollMess=t;
    }
    string getRollMess(){
        return rollMess;
    }
    void setTBR(int num){
        TBR=num;
    }
    int getTBR(){
        return TBR;
    }
    void resetUsed(){
        setInstaUsed(instaUsedR);
        setRollUsed(rollUsedR);
    }
  protected:
	vector<RollEffect*> Dice4Life;
	vector<InstaEffect*> LUCKvIRONY;
    string description;
    bool instadeath;
    bool goal;
    string type;
    int instaUsed=0,rollUsed=0,instaUsedR=0,rollUsedR=0;
    string instaMess,rollMess;
    int TBR;//will be 0 on preset rooms and 1 on random rooms
};
#endif
