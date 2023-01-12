#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <ctime>
#include <iomanip>

#include "IFDParser.h"
#include "LinkData.h"
#include "Area.h"
#include "Item.h"
using namespace std;

#ifndef H_Map
#define H_Map

struct areaNode
{
	Area info;
	areaNode *u;
	areaNode *d;
	areaNode *l;
	areaNode *r;
};
class Map{
	protected:
        vector<Rule*> reset;
		int areacnt;

		//Here is the instance of IFDParser
	  	IFDParser parser;

		//Some additional class attributes here
        vector<LinkData*> linkVec;
		string nextToken;

		bool ifderr;

	public:
		vector<areaNode*> areasVec;

		vector<vector<int>> bGrid, gGrid, uGrid;
        int bRmCnt=0, gRmCnt=0, uRmCnt=0, Ycords=0, Xcords=0;
        bool mapperDapper=false;

        void setRmGrids(){
            bRmCnt=0; gRmCnt=0; uRmCnt=0; Ycords=0; Xcords=0;
            bGrid.clear(); gGrid.clear(); uGrid.clear();
            for(int i=0;i<areasVec.size();i++){
                if(areasVec[i]->info.getType()=="basementR"||areasVec[i]->info.getType()=="basement"){
                    bRmCnt++;
                }else if(areasVec[i]->info.getType()=="groundR"||areasVec[i]->info.getType()=="ground"){
                    gRmCnt++;
                }else if(areasVec[i]->info.getType()=="upperR"||areasVec[i]->info.getType()=="upper"){
                    uRmCnt++;
                }
            }
            bGrid.resize(bRmCnt*2+1, vector<int>(bRmCnt*2+1, 0));
            gGrid.resize(gRmCnt*2+1, vector<int>(gRmCnt*2+1, 0));
            uGrid.resize(uRmCnt*2+1, vector<int>(uRmCnt*2+1, 0));
        }

        void linkCheck(areaNode* current,int X,int Y){
            string testType=current->info.getType();
            if(testType=="basement"||testType=="basmentR"){
                if(mapperDapper){
                    for(int i = bGrid.size()-2; i >= 1; i--){
                        for (int j = 1; j < bGrid[i].size()-1; j++){
                            if(bGrid[i][j]!=0){
                                cout << setw(4) << bGrid[i][j];
                            }else{
                                cout << setw(4) << " ";
                            }
                        }
                        cout << endl << endl;
                    }
                    cout<<"You are in room number: "<<bGrid[Y][X]<<endl;
                }
                if(bGrid[Y+1][X]!=0&&current->u==nullptr&&areasVec[bGrid[Y+1][X]-1]->d==nullptr){
                    current->u=areasVec[bGrid[Y+1][X]-1]; areasVec[bGrid[Y+1][X]-1]->d=current;
                }
                if(bGrid[Y-1][X]!=0&&current->d==nullptr&&areasVec[bGrid[Y-1][X]-1]->u==nullptr){
                    current->d=areasVec[bGrid[Y-1][X]-1]; areasVec[bGrid[Y-1][X]-1]->u=current;
                }
                if(bGrid[Y][X+1]!=0&&current->r==nullptr&&areasVec[bGrid[Y][X+1]-1]->l==nullptr){
                    current->r=areasVec[bGrid[Y][X+1]-1]; areasVec[bGrid[Y][X+1]-1]->l=current;
                }
                if(bGrid[Y][X-1]!=0&&current->l==nullptr&&areasVec[bGrid[Y][X-1]-1]->r==nullptr){
                    current->l=areasVec[bGrid[Y][X-1]-1]; areasVec[bGrid[Y][X-1]-1]->r=current;
                }
            }else if(testType=="ground"||testType=="groundR"){
                if(mapperDapper){
                    for(int i = gGrid.size()-2; i >= 1; i--){
                        for (int j = 1; j < gGrid[i].size()-1; j++)
                            cout << setw(3) << gGrid[i][j] << " ";
                        cout << endl << endl;
                    }
                    cout<<"You are in room number: "<<gGrid[Y][X]<<endl;
                }
                if(gGrid[Y+1][X]!=0&&current->u==nullptr&&areasVec[gGrid[Y+1][X]-1]->d==nullptr){
                    current->u=areasVec[gGrid[Y+1][X]-1]; areasVec[gGrid[Y+1][X]-1]->d=current;
                }
                if(gGrid[Y-1][X]!=0&&current->d==nullptr&&areasVec[gGrid[Y-1][X]-1]->u==nullptr){
                    current->d=areasVec[gGrid[Y-1][X]-1]; areasVec[gGrid[Y-1][X]-1]->u=current;
                }
                if(gGrid[Y][X+1]!=0&&current->r==nullptr&&areasVec[gGrid[Y][X+1]-1]->l==nullptr){
                    current->r=areasVec[gGrid[Y][X+1]-1]; areasVec[gGrid[Y][X+1]-1]->l=current;
                }
                if(gGrid[Y][X-1]!=0&&current->l==nullptr&&areasVec[gGrid[Y][X-1]-1]->r==nullptr){
                    current->l=areasVec[gGrid[Y][X-1]-1]; areasVec[gGrid[Y][X-1]-1]->r=current;
                }
            }else if(testType=="upper"||testType=="upperR"){
                if(mapperDapper){
                    for(int i = uGrid.size()-2; i >= 1; i--){
                        for (int j = 1; j < uGrid[i].size()-1; j++)
                            cout << setw(3) << uGrid[i][j] << " ";
                        cout << endl << endl;
                    }
                    cout<<"You are in room number: "<<uGrid[Y][X]<<endl;
                }
                if(uGrid[Y+1][X]!=0&&current->u==nullptr&&areasVec[uGrid[Y+1][X]-1]->d==nullptr){
                    current->u=areasVec[uGrid[Y+1][X]-1]; areasVec[uGrid[Y+1][X]-1]->d=current;
                }
                if(uGrid[Y-1][X]!=0&&current->d==nullptr&&areasVec[uGrid[Y-1][X]-1]->u==nullptr){
                    current->d=areasVec[uGrid[Y-1][X]-1]; areasVec[uGrid[Y-1][X]-1]->u=current;
                }
                if(uGrid[Y][X+1]!=0&&current->r==nullptr&&areasVec[uGrid[Y][X+1]-1]->l==nullptr){
                    current->r=areasVec[uGrid[Y][X+1]-1]; areasVec[uGrid[Y][X+1]-1]->l=current;
                }
                if(uGrid[Y][X-1]!=0&&current->l==nullptr&&areasVec[uGrid[Y][X-1]-1]->r==nullptr){
                    current->l=areasVec[uGrid[Y][X-1]-1]; areasVec[uGrid[Y][X-1]-1]->r=current;
                }
            }else{
                //stairs do nothing
            }
        }

        void resetRooms(){
            for(int i=0; i<areasVec.size(); i++){
                areasVec[i]->info.resetUsed();
                if(areasVec[i]->info.getTBR()==1&&areasVec[i]->info.getType()=="ground")
                    areasVec[i]->info.setType("groundR");
                else if(areasVec[i]->info.getTBR()==1&&areasVec[i]->info.getType()=="basement")
                    areasVec[i]->info.setType("basementR");
                else if(areasVec[i]->info.getTBR()==1&&areasVec[i]->info.getType()=="upper")
                    areasVec[i]->info.setType("upperR");
            }
        }

        void randRoom(string udlr,areaNode* current){
            srand(time(0));
            string type=current->info.getType(),typeCheck;
            if(type=="ground")
                typeCheck="groundR";
            else if(type=="basement")
                typeCheck="basementR";
            else if(type=="upper")
                typeCheck="upperR";
            int cnt=0, cntR=0;
            for(int i=0; i<areasVec.size(); i++){
                if(areasVec[i]->info.getType()==typeCheck){
                    cnt++;
                }
            }
            if(cnt>0){
                int randN = (rand()%cnt)+1;
                for(int i=0; i<areasVec.size(); i++){
                    if(areasVec[i]->info.getType()==typeCheck){
                        cntR++;
                        if(cntR==randN){
                            areasVec[i]->info.setType(type);
                            if(udlr=="u"){
                                current->u=areasVec[i];
                                areasVec[i]->d=current;
                            }else if(udlr=="d"){
                                current->d=areasVec[i];
                                areasVec[i]->u=current;
                            }else if(udlr=="l"){
                                current->l=areasVec[i];
                                areasVec[i]->r=current;
                            }else if(udlr=="r"){
                                current->r=areasVec[i];
                                areasVec[i]->l=current;
                            }
                        }
                    }
                }
            }else{
                if(udlr=="u"){
                    current->u=current;
                }else if(udlr=="d"){
                    current->d=current;
                }else if(udlr=="l"){
                    current->l=current;
                }else if(udlr=="r"){
                    current->r=current;
                }
            }
        }

		int vecSize(){ // my function
			return areasVec.size();
		}
        vector<areaNode*> getVec(){
            return areasVec;
        }

		void makeArea(){
			string xstr;

			areaNode* tempNodePtr = new areaNode;
			while(nextToken != "</area>"){
				if(nextToken == "<ground>"){
					parser.eatToken();
					nextToken = parser.getNext();
					makeNewGround(tempNodePtr);
				}
				else if(nextToken == "<upper>"){
					parser.eatToken();
					nextToken = parser.getNext();
					makeNewUpper(tempNodePtr);
				}
				else if(nextToken == "<basement>"){
					parser.eatToken();
					nextToken = parser.getNext();
					makeNewBasement(tempNodePtr);
				}
				else if(nextToken == "<stairs>"){
					parser.eatToken();
					nextToken = parser.getNext();
					makeNewStairs(tempNodePtr);
				}
        //********************************************************************************
				else if(nextToken == "<groundR>"){
					parser.eatToken();
					nextToken = parser.getNext();
					makeNewGroundR(tempNodePtr);
				}
				else if(nextToken == "<upperR>"){
					parser.eatToken();
					nextToken = parser.getNext();
					makeNewUpperR(tempNodePtr);
				}
				else if(nextToken == "<basementR>"){
					parser.eatToken();
					nextToken = parser.getNext();
					makeNewBasementR(tempNodePtr);
				}
        //********************************************************************************
				else if(nextToken == "</desc>" || nextToken == "</feats>" || nextToken == "</basement>"
						|| nextToken == "</upper>" || nextToken == "</ground>"){
				  //do nothing
				}
				else{
					cout<<"Parse Error Location 2"<<endl;
					ifderr = true;
					break;
				}
				parser.eatToken();
				nextToken = parser.getNext();
			}//while !</area>
			//add area to vector
			//areasVec.push_back(tempNodePtr);
		} //end makeArea()

		void makeNewBasement(areaNode* tempNodePtr){
			string xstr;
			tempNodePtr->info.setType("basement");
			tempNodePtr->info.setTBR(0);
			while(nextToken != "</basement>"){
                if(nextToken == "<desc>"){
                    parser.eatToken();
                    nextToken = parser.getNext();
                    tempNodePtr->info.setDescription(nextToken);
                }
                else if(nextToken == "<feats>"){
                    parser.eatToken();
                    nextToken = parser.getNext();
                    istringstream ss(nextToken);
                    getline(ss, xstr, ',');
                    tempNodePtr->info.setID(atoi(xstr.c_str()));
                    getline(ss, xstr, ',');
                    tempNodePtr->info.setGoal(atoi(xstr.c_str()));
                }
                else if(nextToken == "<rmEft>"){
                    parser.eatToken();
                    nextToken = parser.getNext();
                    makeEft(tempNodePtr);
                }
                else if(nextToken == "<rmDmg>"){
                    parser.eatToken();
                    nextToken = parser.getNext();
                    makeDmg(tempNodePtr);
                }
                parser.eatToken();
                nextToken = parser.getNext();
			}
			areasVec.push_back(tempNodePtr);
		}

		void makeNewStairs(areaNode* temp){
			string xstr;
			temp->info.setType("stairs");
			temp->info.setTBR(0);
			while(nextToken != "</stairs>"){
                if(nextToken == "<desc>"){
                    parser.eatToken();
                    nextToken = parser.getNext();
                    temp->info.setDescription(nextToken);
                }
                else if(nextToken == "<feats>"){
                    parser.eatToken();
                    nextToken = parser.getNext();
                    istringstream ss(nextToken);
                    getline(ss, xstr, ',');
                    temp->info.setID(atoi(xstr.c_str()));
                    getline(ss, xstr, ',');
                    temp->info.setGoal(atoi(xstr.c_str()));
                }
                parser.eatToken();
                nextToken = parser.getNext();
			}
            areasVec.push_back(temp);

		}
		void makeNewGround(areaNode* tempNodePtr){
			string xstr;
			tempNodePtr->info.setType("ground");
			tempNodePtr->info.setTBR(0);
			while(nextToken != "</ground>"){
                if(nextToken == "<desc>"){
                    parser.eatToken();
                    nextToken = parser.getNext();
                    tempNodePtr->info.setDescription(nextToken);
                }
                else if(nextToken == "<feats>"){
                    parser.eatToken();
                    nextToken = parser.getNext();
                    istringstream ss(nextToken);
                    getline(ss, xstr, ',');
                    tempNodePtr->info.setID(atoi(xstr.c_str()));
                    getline(ss, xstr, ',');
                    tempNodePtr->info.setGoal(atoi(xstr.c_str()));
                }
                else if(nextToken == "<rmEft>"){
                    parser.eatToken();
                    nextToken = parser.getNext();
                    makeEft(tempNodePtr);
                }
                else if(nextToken == "<rmDmg>"){
                    parser.eatToken();
                    nextToken = parser.getNext();
                    makeDmg(tempNodePtr);
                }
                parser.eatToken();
                nextToken = parser.getNext();
			}
            areasVec.push_back(tempNodePtr);
		}

		void makeNewUpper(areaNode* tempNodePtr){
			string xstr;
			tempNodePtr->info.setType("upper");
			tempNodePtr->info.setTBR(0);
			while(nextToken != "</upper>"){
                if(nextToken == "<desc>"){
                    parser.eatToken();
                    nextToken = parser.getNext();
                    tempNodePtr->info.setDescription(nextToken);
                }
                else if(nextToken == "<feats>"){
                    parser.eatToken();
                    nextToken = parser.getNext();
                    istringstream ss(nextToken);
                    getline(ss, xstr, ',');
                    tempNodePtr->info.setID(atoi(xstr.c_str()));
                    getline(ss, xstr, ',');
                    tempNodePtr->info.setGoal(atoi(xstr.c_str()));
                }
                else if(nextToken == "<rmEft>"){
                    parser.eatToken();
                    nextToken = parser.getNext();
                    makeEft(tempNodePtr);
                }
                else if(nextToken == "<rmDmg>"){
                    parser.eatToken();
                    nextToken = parser.getNext();
                    makeDmg(tempNodePtr);
                }
                parser.eatToken();
                nextToken = parser.getNext();
			}
            areasVec.push_back(tempNodePtr);
		}

		//********************************************************************************
		void makeNewBasementR(areaNode* tempNodePtr){
			string xstr;
			tempNodePtr->info.setType("basementR");
			tempNodePtr->info.setTBR(1);
			while(nextToken != "</basementR>"){
                if(nextToken == "<desc>"){
                    parser.eatToken();
                    nextToken = parser.getNext();
                    tempNodePtr->info.setDescription(nextToken);
                }
                else if(nextToken == "<feats>"){
                    parser.eatToken();
                    nextToken = parser.getNext();
                    istringstream ss(nextToken);
                    getline(ss, xstr, ',');
                    tempNodePtr->info.setID(atoi(xstr.c_str()));
                    getline(ss, xstr, ',');
                    tempNodePtr->info.setGoal(atoi(xstr.c_str()));
                }
                else if(nextToken == "<rmEft>"){
                    parser.eatToken();
                    nextToken = parser.getNext();
                    makeEft(tempNodePtr);
                }
                else if(nextToken == "<rmDmg>"){
                    parser.eatToken();
                    nextToken = parser.getNext();
                    makeDmg(tempNodePtr);
                }
                parser.eatToken();
                nextToken = parser.getNext();
			}
			areasVec.push_back(tempNodePtr);
		}

		void makeNewGroundR(areaNode* tempNodePtr){
			string xstr;
			tempNodePtr->info.setType("groundR");
			tempNodePtr->info.setTBR(1);
			while(nextToken != "</groundR>"){
                if(nextToken == "<desc>"){
                    parser.eatToken();
                    nextToken = parser.getNext();
                    tempNodePtr->info.setDescription(nextToken);
                }
                else if(nextToken == "<feats>"){
                    parser.eatToken();
                    nextToken = parser.getNext();
                    istringstream ss(nextToken);
                    getline(ss, xstr, ',');
                    tempNodePtr->info.setID(atoi(xstr.c_str()));
                    getline(ss, xstr, ',');
                    tempNodePtr->info.setGoal(atoi(xstr.c_str()));
                }
                else if(nextToken == "<rmEft>"){
                    parser.eatToken();
                    nextToken = parser.getNext();
                    makeEft(tempNodePtr);
                }
                else if(nextToken == "<rmDmg>"){
                    parser.eatToken();
                    nextToken = parser.getNext();
                    makeDmg(tempNodePtr);
                }
                parser.eatToken();
                nextToken = parser.getNext();
			}
            areasVec.push_back(tempNodePtr);
		}

		void makeNewUpperR(areaNode* tempNodePtr){
			string xstr;
			tempNodePtr->info.setType("upperR");
			tempNodePtr->info.setTBR(1);
			while(nextToken != "</upperR>"){
                if(nextToken == "<desc>"){
                    parser.eatToken();
                    nextToken = parser.getNext();
                    tempNodePtr->info.setDescription(nextToken);
                }
                else if(nextToken == "<feats>"){
                    parser.eatToken();
                    nextToken = parser.getNext();
                    istringstream ss(nextToken);
                    getline(ss, xstr, ',');
                    tempNodePtr->info.setID(atoi(xstr.c_str()));
                    getline(ss, xstr, ',');
                    tempNodePtr->info.setGoal(atoi(xstr.c_str()));
                }
                else if(nextToken == "<rmEft>"){
                    parser.eatToken();
                    nextToken = parser.getNext();
                    makeEft(tempNodePtr);
                }
                else if(nextToken == "<rmDmg>"){
                    parser.eatToken();
                    nextToken = parser.getNext();
                    makeDmg(tempNodePtr);
                }
                parser.eatToken();
                nextToken = parser.getNext();
			}
            areasVec.push_back(tempNodePtr);
		}
		//********************************************************************************

		void makeEft(areaNode* tempNodePtr){
            RollEffect* Dicey = new RollEffect;
			string xstr;
			while(nextToken != "</rmEft>"){
				if(nextToken == "<rmMess>"){
					parser.eatToken();
					nextToken = parser.getNext();
					tempNodePtr->info.setRollMess(nextToken);
				}
				else if(nextToken == "<act>"){
					parser.eatToken();
					nextToken = parser.getNext();
					istringstream ss(nextToken);
					getline(ss, xstr);
					int entered = atoi(xstr.c_str());
					tempNodePtr->info.setRollUsed(entered);
				}
				else if(nextToken == "<#d>"){
                    parser.eatToken();
					nextToken = parser.getNext();
					Dicey->dice = nextToken;
				}
				else if(nextToken == "<hRoll>"){
					parser.eatToken();
					nextToken = parser.getNext();
					istringstream ss(nextToken);
					getline(ss, xstr, ',');
					Dicey->hRoll = atoi(xstr.c_str());
					getline(ss, xstr, ',');
					Dicey->hEffect = atoi(xstr.c_str());
					getline(ss, xstr, ',');
					Dicey->Hatt = xstr;
					getline(ss, xstr, ',');
					Dicey->hrAmt = atoi(xstr.c_str());
				}
				else if(nextToken == "<hMsg>"){
					parser.eatToken();
					nextToken = parser.getNext();
					Dicey->hMess = nextToken;
				}
				else if(nextToken == "<mRoll>"){
					parser.eatToken();
					nextToken = parser.getNext();
					istringstream ss(nextToken);
					getline(ss, xstr, ',');
					Dicey->mRoll = atoi(xstr.c_str());
					getline(ss, xstr, ',');
					Dicey->mEffect = atoi(xstr.c_str());
					getline(ss, xstr, ',');
					Dicey->Matt = xstr;
					getline(ss, xstr, ',');
					Dicey->mrAmt = atoi(xstr.c_str());
				}
				else if(nextToken == "<mMsg>"){
					parser.eatToken();
					nextToken = parser.getNext();
					Dicey->mMess = nextToken;
				}
				else if(nextToken == "<lRoll>"){
					parser.eatToken();
					nextToken = parser.getNext();
					istringstream ss(nextToken);
					getline(ss, xstr, ',');
					Dicey->lRoll = atoi(xstr.c_str());
					getline(ss, xstr, ',');
					Dicey->lEffect = atoi(xstr.c_str());
					getline(ss, xstr, ',');
					Dicey->Latt = xstr;
					getline(ss, xstr, ',');
					Dicey->lrAmt = atoi(xstr.c_str());
				}
				else if(nextToken == "<lMsg>"){
					parser.eatToken();
					nextToken = parser.getNext();
					Dicey->lMess = nextToken;
				}
				parser.eatToken();
				nextToken = parser.getNext();
			}
            tempNodePtr->info.addrmEft(Dicey);
		}

		void makeDmg(areaNode* tempNodePtr){
		    InstaEffect* LvI = new InstaEffect;
			string xstr;
			while(nextToken != "</rmDmg>"){
				if(nextToken == "<act>"){
					parser.eatToken();
					nextToken = parser.getNext();
					istringstream ss(nextToken);
					getline(ss, xstr);
					int instaUsed = atoi(xstr.c_str());
					tempNodePtr->info.setInstaUsed(instaUsed);
				}
				else if(nextToken == "<Dmg>"){
					parser.eatToken();
					nextToken = parser.getNext();
					istringstream ss(nextToken);
					getline(ss, xstr, ',');
					LvI->dmgTypeRm = atoi(xstr.c_str());
					getline(ss, xstr, ',');
					LvI->dmgAtt = xstr;
					getline(ss, xstr, ',');
					LvI->dmgAmt = atoi(xstr.c_str());
				}
				else if(nextToken == "<rmMess>"){
					parser.eatToken();
					nextToken = parser.getNext();
					tempNodePtr->info.setInstaMess(nextToken);
				}
                parser.eatToken();
                nextToken = parser.getNext();
			}
			tempNodePtr->info.addrmDmg(LvI);
		}

		void makeLinks(){
			string xstr;
			int u, d, l, r;
			while(nextToken != "</links>"){
				if(nextToken == "<linkset>"){
					parser.eatToken();
			  		nextToken = parser.getNext();
					LinkData* tempLDPtr = new LinkData;
					istringstream ss(nextToken);
                    getline(ss, xstr, ',');
                    u = atoi(xstr.c_str());
                    getline(ss, xstr, ',');
                    d = atoi(xstr.c_str());
					getline(ss, xstr, ',');
                    l = atoi(xstr.c_str());
					getline(ss, xstr, ',');
					r = atoi(xstr.c_str());
					tempLDPtr->setDigits(u, d, l, r);
                    linkVec.push_back(tempLDPtr);
				}
				else if(nextToken == "</linkset>"){
					//do nothing
				}
				else{
					cout<<"Parse Error Location 3"<<endl;
					ifderr = true;
					break;
				}
				parser.eatToken();
                nextToken = parser.getNext();
			}//while !</links>
		}//makeLinks()


		void linkLinks(){
			for(int i=0; i<linkVec.size(); i++){
                    areasVec[i]->info.getDescription();
                    if(linkVec[i]->getDigit(0) != -1){
                        areasVec[i]->u = areasVec[(linkVec[i]->getDigit(0))-1];
                    }else{
                        areasVec[i]->u = nullptr;
                    }
                    if(linkVec[i]->getDigit(1) != -1){
                        areasVec[i]->d = areasVec[(linkVec[i]->getDigit(1))-1];
                    }else{
                        areasVec[i]->d = nullptr;
                    }
                    if(linkVec[i]->getDigit(2) != -1){
                        areasVec[i]->l = areasVec[(linkVec[i]->getDigit(2))-1];
                    }else{
                        areasVec[i]->l = nullptr;
                    }
                    if(linkVec[i]->getDigit(3) != -1){
                        areasVec[i]->r = areasVec[(linkVec[i]->getDigit(3))-1];
                    }else{
                        areasVec[i]->r = nullptr;
                    }
			}

		}
        //*****************************************************************
        void newLinks(nodeType<Item*>* hold){
            Rule* tempR;
            int i=0;
            while(hold->info->getT3C(tempR,i)){
                makeNewLinks(tempR->beginRm, tempR->destRm, tempR->direction);
                i++;
            }
        }

        void makeNewLinks(int rm, int des, char x){
            if(des!=-1){
                if(x == 'u'){
                    areasVec[rm-1]->u = areasVec[des-1];
                }
                if(x == 'd'){
                    areasVec[rm-1]->d = areasVec[des-1];
                }
                if(x == 'l'){
                    areasVec[rm-1]->l = areasVec[des-1];
                }
                if(x == 'r'){
                    areasVec[rm-1]->r = areasVec[des-1];
                }
            }else{
                if(x == 'u'){
                    areasVec[rm-1]->u = nullptr;
                }
                if(x == 'd'){
                    areasVec[rm-1]->d = nullptr;
                }
                if(x == 'l'){
                    areasVec[rm-1]->l = nullptr;
                }
                if(x == 'r'){
                    areasVec[rm-1]->r = nullptr;
                }
            }
        }

        void resetLinks(){
                linkLinks();

        }
        //*****************************************************************


		areaNode* getStart(){
			return areasVec[0];  //returns a pointer to the first area listed
		}


		friend ostream& operator<<(ostream& os, Map& map){
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
			return os;
		}

		int reverseLookUp(areaNode* addy){
			for(int i=0; i<areasVec.size(); i++){
				if(areasVec[i] == addy){
					return i+1;
				}
			}
			//this should not happen
			return -1;
		}
};
#endif
