#ifndef H_BasicPlayer
#define H_BasicPlayer

#include <iostream>
using namespace std;

#include "Player.h"
#include "Map.h"

class BasicPlayer : public Player{
public:
	BasicPlayer() : Player(){
	    cout<<"...Creating Basic Player Game..."<<endl<<endl;
	}
	virtual int isGameOver(){
		if(currentLocation->info.getGoal() == true){
			return 1;
		}
		if(currentLocation->info.getID() == true){
			return 2;
		}
		else{
			return 0;
		}
	}
	virtual void resetPlayerStats(){
		//do nothing for basic player
	}
	virtual void reportStats(){
		cout<<"No player statistics to report."<<endl;
	}
	virtual void consume(Map* mapptr){
        cout<<"What would you like to consume?"<<endl;
		string n;
		getline(cin, n);
        nodeType<Item*>* temp = NULL;
		temp = items.getFirst();
		if(temp == NULL){
			cout<<"You have no items in your inventory."<<endl;
		}
		else{
			bool found = false;
			while(temp != NULL && !found){
				if(n == temp->info->getName()){
					found = true;
					if(temp->info->getType()!="consume"){
                        cout<<"That proves impossible"<<endl;
                        return;
                    }
				}
				else{
					temp = temp->link;
				}
			}
			if(found){
                if(mapptr->reverseLookUp(currentLocation) == temp->info->getActiveArea()||temp->info->getActiveArea() == 0){
                    cout<<temp->info->getActiveMessage()<<endl;
                }else{
                    cout<<"You cannot consume the "<<temp->info->getName()<<" here."<<endl;
                }
			}
			else{
				cout<<"No item by that name in your inventory."<<endl;
			}
		}
    }


	virtual void use(Map* mapptr){
	    cout<<"What would you like to use?"<<endl;
		string n;
		getline(cin, n);
        nodeType<Item*>* temp = NULL;
		temp = items.getFirst();
		if(temp == NULL){
			cout<<"You have no items in your inventory."<<endl;
		}
		else{
			bool found = false;
			while(temp != NULL && !found){
				if(n == temp->info->getName()){
					found = true;
				}
				else{
					temp = temp->link;
				}
			}
			if(found){
                if(temp->info->getType()!="use"){
                        cout<<"There's no way to use this item."<<endl;
                        return;
                    }
                if(mapptr->reverseLookUp(currentLocation) == temp->info->getActiveArea()||temp->info->getActiveArea() == 0){
                    cout<<temp->info->getActiveMessage()<<endl;
                    mapptr->newLinks(temp);
                }else{
                    cout<<"You cannot use the "<<temp->info->getName()<<" here."<<endl;
                }
			}
			else{
				cout<<"No item by that name in your inventory."<<endl;
			}
		}
    }
};
#endif // H_BasicPlayer
