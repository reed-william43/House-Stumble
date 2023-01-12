#ifndef H_HPSPPlayer
#define H_HPSPPlayer
#include <iostream>
using namespace std;

#include "Player.h"
#include "Map.h"

class HPSPPlayer : public Player{
private:
    int hitPT;
    int sanity;
public:
	HPSPPlayer() : Player(){
		hitPT = 100;
		sanity = 100;
		cout<<"...Creating HP & SP Player Game..."<<endl<<endl;
	}
	virtual int isGameOver(){
		if(currentLocation->info.getGoal() == true){
			return 1;
		}
		if(currentLocation->info.getID()==true){
			return 2;
		}
		if(hitPT<=0 || sanity<=0){
            cout<<"You died of your wounds"<<endl;
            return 3;
		}
		else{
			return 0;
		}
	}
	virtual void resetPlayerStats(){
		hitPT = 100;
		sanity = 100;
	}
	virtual void reportStats(){
		cout<<"Player Hit Points: "<<hitPT<<endl;
		cout<<"Player Sanity Status: "<<sanity<<endl;
	}
	virtual void consume(Map* mapptr){
       cout<<"What would you like to consume?"<<endl;
		string n;
		getline(cin, n);
        nodeType<Item*>* temp = NULL;
        Effect* drugs;
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
                    int i=0;
                    while(temp->info->getConsequences(drugs, i)){
                        switch(drugs->effectID){
                            case 0:
                                hitPT-=drugs->effectAmt;
                                break;
                            case 1:
                                hitPT+=drugs->effectAmt;
                                break;
                            case 2:
                                sanity-=drugs->effectAmt;
                                break;
                            case 3:
                                sanity+=drugs->effectAmt;
                                break;
                            default:
                                cout<<"Default error, effectID not recognized."<<endl;
                                break;
                        }
                        i++;
                    }
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
#endif
