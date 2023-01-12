#ifndef H_MapV2
#define H_MapV2

#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <iostream>
using namespace std;

#include "Map.h"
#include "Item.h"
#include "ull.h"
#include "BasicPlayer.h"
#include "HPSPPlayer.h"
#include "BaseCharacter.h"

class MapV2 : public Map{
public:
    vector<Item*> itemVec;
    Player* pType;

    MapV2(){
        bool ifderr;
			ifderr = false;
			parser.tokenIt();
			nextToken = parser.getNext();

			if(nextToken == "<game>"){
				parser.eatToken();
				nextToken = parser.getNext();
				while(nextToken != "</game>"){  //consider what happens when run out of tokens && not error state
					if(nextToken == "<ptype>"){
                        parser.eatToken();
                        nextToken = parser.getNext();
                        makePtype();
                    }
                    if(nextToken == "<area>"){
						parser.eatToken();
						nextToken = parser.getNext();
						makeArea();
					}
					else if(nextToken == "<links>"){
						parser.eatToken();
						nextToken = parser.getNext();
						makeLinks();
					}
					else if(nextToken == "<item>"){
                        parser.eatToken();
                        nextToken = parser.getNext();
                        makeItem();
					}
					else{
						cout<<"Parse Error Location 1"<<endl;
						ifderr = true;
						break;
					}
					parser.eatToken();
					nextToken = parser.getNext();
				}// while !</game>

				if(ifderr){
					cout<<" :: ERROR :: IF Document Formatting Error"<<endl;
					cout<<"Game Loading Failed"<<endl;
					cout<<"General Area of Parsing Failure:"<<endl;
					cout<<"-------------------------------------"<<endl;
					cout<<nextToken<<endl;
					parser.eatToken();
					nextToken = parser.getNext();
					cout<<nextToken<<endl;
					parser.eatToken();
					nextToken = parser.getNext();
					cout<<nextToken<<endl;
					parser.eatToken();
					nextToken = parser.getNext();
					cout<<nextToken<<endl;
					cout<<"-------------------------------------"<<endl;
					return;
				}
			}
			else{
				cout<<" :: ERROR :: No \"<game>\" tag found."<<endl;
				cout<<"Game Loading Failed"<<endl;
			}
        //link up areas
        linkLinks();
        insertItems();
    }//constructor

    void makeItem(){
        string xstr;
        while(nextToken != "</item>"){
            if(nextToken == "<use>"){
                parser.eatToken();
                nextToken = parser.getNext();
                newUse();
            }
            else if(nextToken == "<consume>"){
                parser.eatToken();
                nextToken = parser.getNext();
                newConsume();
            }
            else if(nextToken == "<basic>"){
                parser.eatToken();
                nextToken = parser.getNext();
                newBasic();
            }
            else if(nextToken == "<omen>"){
                parser.eatToken();
                nextToken = parser.getNext();
                newOmen();
            }
            else if(nextToken == "<interact>"){
                parser.eatToken();
                nextToken = parser.getNext();
                newInteract();
            }
            else if(nextToken == "</use>" || nextToken == "</consume>" || nextToken == "</basic>" ||
                    nextToken == "</omen>" || nextToken == "</interact>"){
                // do nothing
            }
            else{
                cout<<"Parse Error Location 2"<<endl;
                ifderr = true;
                break;
            }
            parser.eatToken();
            nextToken = parser.getNext();
        } // end !</item>
        //itemVec.push_back(tempPTR);
    }//end makeItem()

    void newUse(){
        int beginning, destination;
        char direction;
        string xstr;
        UseItem* tempPTR = new UseItem;
        while(nextToken != "</use>"){
            if(nextToken == "<name>"){
                parser.eatToken();
                nextToken = parser.getNext();
                tempPTR->setName(nextToken);
            }
            else if(nextToken == "<desc>"){
                parser.eatToken();
                nextToken = parser.getNext();
                tempPTR->setDesc(nextToken);
            }
            else if(nextToken == "<star>"){
                parser.eatToken();
                nextToken = parser.getNext();
                istringstream ss(nextToken);
                getline(ss,xstr);
                tempPTR->setSR(atoi(xstr.c_str()));
            }
            else if(nextToken == "<actar>"){
                parser.eatToken();
                nextToken = parser.getNext();
                istringstream ss(nextToken);
                getline(ss,xstr);
                tempPTR->setActiveArea(atoi(xstr.c_str()));
            }
            else if(nextToken == "<actmess>"){
                parser.eatToken();
                nextToken = parser.getNext();
                tempPTR->setActiveMessage(nextToken);
            }
            else if(nextToken == "<rule>"){
                parser.eatToken();
                nextToken = parser.getNext();
                istringstream ss(nextToken);
                getline(ss, xstr, ',');
                beginning = atoi(xstr.c_str());
                getline(ss, xstr, ',');
                direction = *xstr.c_str();
                getline(ss, xstr, ',');
                destination = atoi(xstr.c_str());
                tempPTR->addRule(beginning,direction,destination);
            }
            else if(nextToken == "</name>" || nextToken == "</desc>" || nextToken == "</star>" || nextToken == "</actar>"
                                           || nextToken == "</actmess>" || nextToken == "</rule>"){
                // do nothing
            }
        parser.eatToken();
        nextToken=parser.getNext();
        }
        itemVec.push_back(tempPTR);
    }

    void newConsume(){
        int eID, eAmt;
        string att;
        string xstr;
        ConsumeItem* tempPTR = new ConsumeItem;
        while(nextToken != "</consume>"){
            if(nextToken == "<name>"){
                parser.eatToken();
                nextToken = parser.getNext();
                tempPTR->setName(nextToken);
            }
            else if(nextToken == "<desc>"){
                parser.eatToken();
                nextToken = parser.getNext();
                tempPTR->setDesc(nextToken);
            }
            else if(nextToken == "<star>"){
                parser.eatToken();
                nextToken = parser.getNext();
                istringstream ss(nextToken);
                getline(ss,xstr);
                tempPTR->setSR(atoi(xstr.c_str()));
            }
            else if(nextToken == "<actar>"){
                parser.eatToken();
                nextToken = parser.getNext();
                istringstream ss(nextToken);
                getline(ss,xstr);
                tempPTR->setActiveArea(atoi(xstr.c_str()));
            }
            else if(nextToken == "<actmess>"){
                parser.eatToken();
                nextToken = parser.getNext();
                tempPTR->setActiveMessage(nextToken);
            }//*******************************************************
            else if(nextToken == "<useCnt>"){
                parser.eatToken();
                nextToken = parser.getNext();
                istringstream ss(nextToken);
                getline(ss,xstr);
                tempPTR->setUseCnt(atoi(xstr.c_str()));
            }//*******************************************************
            else if(nextToken == "<effect>"){
                parser.eatToken();
                nextToken = parser.getNext();
                istringstream ss(nextToken);
                getline(ss, xstr, ',');
                att = xstr;
                getline(ss, xstr, ',');
                eID = atoi(xstr.c_str());
                getline(ss, xstr, ',');
                eAmt = atoi(xstr.c_str());
                tempPTR->addEffect(att, eID, eAmt);
            }
            else if(nextToken == "</name>" || nextToken == "</desc>" || nextToken == "</star>" || nextToken == "</actar>"
                                           || nextToken == "</actmess>" || nextToken == "</effect>"|| nextToken == "</useCnt>"){
            }
        parser.eatToken();
        nextToken = parser.getNext();
        }
        itemVec.push_back(tempPTR);
    }

    void newBasic(){
        string xstr;
        Item* tempPTR = new Item;
        while(nextToken != "</basic>"){
            if(nextToken == "<name>"){
                parser.eatToken();
                nextToken = parser.getNext();
                tempPTR->setName(nextToken);
            }
            else if(nextToken == "<desc>"){
                parser.eatToken();
                nextToken = parser.getNext();
                tempPTR->setDesc(nextToken);
            }
            else if(nextToken == "<star>"){
                parser.eatToken();
                nextToken = parser.getNext();
                istringstream ss(nextToken);
                getline(ss,xstr);
                tempPTR->setSR(atoi(xstr.c_str()));
            }
            else if(nextToken == "</name>" || nextToken == "</desc>" || nextToken == "</star>"){
                // do nothing
            }
        parser.eatToken();
        nextToken = parser.getNext();
        }
        itemVec.push_back(tempPTR);
    }

    void newOmen(){
        string xstr;
        omenItem* tempPTR = new omenItem;
        while(nextToken != "</omen>"){
            if(nextToken == "<name>"){
                parser.eatToken();
                nextToken = parser.getNext();
                tempPTR->setName(nextToken);
            }
            else if(nextToken == "<desc>"){
                parser.eatToken();
                nextToken = parser.getNext();
                tempPTR->setDesc(nextToken);
            }
            else if(nextToken == "<star>"){
                parser.eatToken();
                nextToken = parser.getNext();
                istringstream ss(nextToken);
                getline(ss,xstr);
                tempPTR->setSR(atoi(xstr.c_str()));
            }
            else if(nextToken == "</name>" || nextToken == "</desc>" || nextToken == "</star>"){
                // do nothing
            }
        parser.eatToken();
        nextToken = parser.getNext();
        }
        itemVec.push_back(tempPTR);
    }

    void newInteract(){
        int eID, eAmt;
        string att;
        string xstr;
        interactItem* tempPTR = new interactItem;
        while(nextToken != "</interact>"){
            if(nextToken == "<name>"){
                parser.eatToken();
                nextToken = parser.getNext();
                tempPTR->setName(nextToken);
            }
            else if(nextToken == "<desc>"){
                parser.eatToken();
                nextToken = parser.getNext();
                tempPTR->setDesc(nextToken);
            }
            else if(nextToken == "<star>"){
                parser.eatToken();
                nextToken = parser.getNext();
                istringstream ss(nextToken);
                getline(ss,xstr);
                tempPTR->setSR(atoi(xstr.c_str()));
            }
            else if(nextToken == "<actar>"){
                parser.eatToken();
                nextToken = parser.getNext();
                istringstream ss(nextToken);
                getline(ss,xstr);
                tempPTR->setActiveArea(atoi(xstr.c_str()));
            }
            else if(nextToken == "<actmess>"){
                parser.eatToken();
                nextToken = parser.getNext();
                tempPTR->setActiveMessage(nextToken);
            }//*******************************************************
            else if(nextToken == "<useCnt>"){
                parser.eatToken();
                nextToken = parser.getNext();
                istringstream ss(nextToken);
                getline(ss,xstr);
                tempPTR->setUseCnt(atoi(xstr.c_str()));
            }//*******************************************************
            else if(nextToken == "<effect>"){
                parser.eatToken();
                nextToken = parser.getNext();
                istringstream ss(nextToken);
                getline(ss, xstr, ',');
                att = xstr;
                getline(ss, xstr, ',');
                eID = atoi(xstr.c_str());
                getline(ss, xstr, ',');
                eAmt = atoi(xstr.c_str());
                tempPTR->addEffect(att, eID, eAmt);
            }
            else if(nextToken == "</name>" || nextToken == "</desc>" || nextToken == "</star>" || nextToken == "</actar>"
                                           || nextToken == "</actmess>" || nextToken == "</effect>"|| nextToken == "</useCnt>"){
            }
        parser.eatToken();
        nextToken = parser.getNext();
        }
        itemVec.push_back(tempPTR);
    }

    void makePtype(){ // Make a new player based on the type specified by .ifd file
        while(nextToken != "</ptype>"){
            if(nextToken == "basic"){
                pType = new BasicPlayer;
            }
            else if(nextToken == "hpsp"){
                pType = new HPSPPlayer;
            }
            else if(nextToken == "BasicB"){
                pType = new BaseCharacter;
            }
            else if(nextToken == "</ptype>"){
                // do nothing
            }
            parser.eatToken();
            nextToken = parser.getNext();
        }
        parser.eatToken();
        nextToken = parser.getNext();
    }

    Player* getPtype(){
        return pType;
    }

    void insertItems(){
        for(int i=0; i<itemVec.size(); i++){
            areasVec[itemVec[i]->getSR()-1]->info.items.insertFirst(itemVec[i]);
        }
    }

    void resetItems(){
        for(int i=0; i<itemVec.size(); i++){
            areasVec[itemVec[i]->getSR()-1]->info.items.destroyList();
        }
        for(int i=0; i<itemVec.size(); i++){
            itemVec[i]->resetUseCnt();
            areasVec[itemVec[i]->getSR()-1]->info.items.insertFirst(itemVec[i]);
        }
    }

    friend ostream& operator<<(ostream& os, MapV2& map){
        os<<"******************************************************************"<<endl;
        os<<"CHEATING!!!! Printing the set of areas and connections on the map."<<endl;
        os<<"******************************************************************"<<endl;
        for(int i=0; i<map.areasVec.size(); i++){
            os<<"This is area: "<<i+1<<endl;
            os<<map.areasVec[i]->info.getDescription()<<endl;

            if(map.areasVec[i]->info.getID() == 1){
                os<<"Area is INSTADEATH."<<endl;
            }
            if(map.areasVec[i]->info.getGoal() == 1){
                os<<"Area is GOAL."<<endl;
            }
            os<<"Connections:"<<endl;
            os<<"\t u: Area #"<<map.reverseLookUp(map.areasVec[i]->u)<<endl;
            os<<"\t d: Area #"<<map.reverseLookUp(map.areasVec[i]->d)<<endl;
            os<<"\t l: Area #"<<map.reverseLookUp(map.areasVec[i]->l)<<endl;
            os<<"\t r: Area #"<<map.reverseLookUp(map.areasVec[i]->r)<<endl;
        }
        os<<"******************************************************************"<<endl;
        os<<"CHEATING!!!! Printing the set of areas and connections on the map."<<endl;
        os<<"******************************************************************"<<endl;
        for(int i=0; i<map.areasVec.size(); i++){
            os<<"Items for area"<<i+1<<": "<<map.areasVec[i]->info.getDescription()<<endl;
                    map.areasVec[i]->info.items.printNames();
        }
        return os;
    }
};
#endif // H_MapV2
