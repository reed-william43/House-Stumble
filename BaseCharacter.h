#ifndef H_BasePlayer
#define H_BasePlayer
#include <iostream>
using namespace std;

#include "Player.h"
#include "Map.h"
#include <stdlib.h>
#include <time.h>

class BaseCharacter : public Player{
public:
	BaseCharacter() : Player(){
        difficultySelect();
        playerSelect();
		cout<<"...Yeeting Character Into Game..."<<endl<<endl;
	}

	void difficultySelect(){
        cout<<"\t\t\t\t\t\t Select Game Difficulty"<<endl;
	    cout<<"\t\t\t\t(1)Easy\t\t(2)Medium\t(3)Hard\t\t(4)Extra Hard"<<endl<<endl;
	    bool a=true;
	    while(a){
            cout<<"\t\t\t\t\tEnter Corresponding Difficulty Number: ";
            cin>>omenN;
            cin.ignore();
            if(omenN==1){
                OmensNeeded=3;
                a=false;
            }else if(omenN==2){
                OmensNeeded=4;
                a=false;
            }else if(omenN==3){
                OmensNeeded=5;
                a=false;
            }else if(omenN==4){
                OmensNeeded=6;
                a=false;
            }else{
                cout<<"\t\t\t\t\t\t\t\tINVALID INPUT"<<endl;
            }
	    }
	    system("cls");
	}

	void playerSelect(){
        cout << R"(
      _____ _    _  ____   ____   _____ ______  __     ______  _    _ _____     _____ _    _          _____            _____ _______ ______ _____
     / ____| |  | |/ __ \ / __ \ / ____|  ____| \ \   / / __ \| |  | |  __ \   / ____| |  | |   /\   |  __ \     /\   / ____|__   __|  ____|  __ \
    | |    | |__| | |  | | |  | | (___ | |__     \ \_/ / |  | | |  | | |__) | | |    | |__| |  /  \  | |__) |   /  \ | |       | |  | |__  | |__) |
    | |    |  __  | |  | | |  | |\___ \|  __|     \   /| |  | | |  | |  _  /  | |    |  __  | / /\ \ |  _  /   / /\ \| |       | |  |  __| |  _  /
    | |____| |  | | |__| | |__| |____) | |____     | | | |__| | |__| | | \ \  | |____| |  | |/ ____ \| | \ \  / ____ \ |____   | |  | |____| | \ \
     \_____|_|  |_|\____/ \____/|_____/|______|    |_|  \____/ \____/|_|  \_\  \_____|_|  |_/_/    \_\_|  \_\/_/    \_\_____|  |_|  |______|_|  \_\

)"<<endl;
	    cout<<"\t\t\t\t(1)Trevor Peck\t\t(2)Lomax Freeman\t\t(3)Just Michael\t\t(4)Evan Bowers"<<endl;
	    cout<<"\t\t\t\tmight:     4\t\tmight:     5\t\t\tmight:     4\t\tmight:     6"<<endl;
	    cout<<"\t\t\t\tagility:   6\t\tagility:   4\t\t\tagility:   4\t\tagility:   4"<<endl;
	    cout<<"\t\t\t\tsanity:    3\t\tsanity:    4\t\t\tsanity:    4\t\tsanity:    3"<<endl;
	    cout<<"\t\t\t\tknowledge: 3\t\tknowledge: 4\t\t\tknowledge: 4\t\tknowledge: 4"<<endl<<endl;

        bool b=true;
        while(b){
            cout<<"\t\t\t\t\t\t\t  Enter Corresponding Player Number: ";
            cin>>playerNum;
            cin.ignore();
            if(playerNum==1){
                playerName="TREVOR PECK";
                might=4; mightReset=4;
                agility=6; agilityReset=6;
                sanity=3; sanityReset=3;
                knowledge=3; knowledgeReset=3;
                b=false;
            }else if(playerNum==2){
                playerName="Lomax Freeman";
                might=5; mightReset=5;
                agility=4; agilityReset=4;
                sanity=4; sanityReset=4;
                knowledge=5; knowledgeReset=5;
                b=false;
            }else if(playerNum==3){
                playerName="Just Michael";
                might=4; mightReset=4;
                agility=4; agilityReset=4;
                sanity=4; sanityReset=4;
                knowledge=4; knowledgeReset=4;
                b=false;
            }else if(playerNum==4){
                playerName="Evan Bowers";
                might=6; mightReset=6;
                agility=4; agilityReset=4;
                sanity=3; sanityReset=3;
                knowledge=4; knowledgeReset=4;
                b=false;
            }else if(playerNum==424){
                playerName="MARGARET";
                might=10; mightReset=10;
                agility=10; agilityReset=10;
                sanity=10; sanityReset=10;
                knowledge=10; knowledgeReset=10;
                b=false;
            }else if(playerNum==2002){
                playerName="IMMORTALITY";
                might=100; mightReset=100;
                agility=100; agilityReset=100;
                sanity=100; sanityReset=100;
                knowledge=100; knowledgeReset=100;
                b=false;
            }else{
                cout<<"\t\t\t\t\t\t\t\tINVALID INPUT"<<endl;
            }
        }
        system("cls");
	}

	int isGameOver(){
		if(currentLocation->info.getGoal() == true){
			return 1;
		}
		if(currentLocation->info.getID()==true){
			return 2;
		}
		if(might<=0){
            cout<<"You died of your wounds"<<endl;
            return 3;
		}
		if(sanity<=0){
            cout<<"You died of insanity"<<endl;
            return 3;
		}
		if(agility<=0){
            cout<<"You died of exhaustion"<<endl;
            return 3;
		}
		if(knowledge<=0){
            cout<<"Your brain melts and you are now a vegetable"<<endl;
            return 3;
		}
		else{
			return 0;
		}
	}

	void playerCheck(){
        checkInstaEffect();
        checkRollEffect();
        omenCheck();
    }

	void omenCheck(){
	    nodeType<Item*>* temp = items.getFirst();
	    if(omenC==0){
            int cnt=0;
            if(temp == NULL){
                return;
            }
            else{
                while(temp != NULL){
                    if(temp->info->getType()=="Omen"){
                        cnt++;
                    }
                    temp = temp->link;
                }
                if(cnt>=OmensNeeded){
                    temp = items.getFirst();
                    while(temp != NULL){
                        if(temp->info->getType()=="Omen"){
                            items.deleteNode(temp->info);
                        }
                        temp = temp->link;
                    }
                    omenC=1;
                    cout<<"The omens you are carrying vanish and a magical golden and glowing chainsaw appears in your hands"<<endl;
                    UseItem* tempPTR = new UseItem;
                    tempPTR->setName("Golden Chainsaw");
                    tempPTR->setDesc("A Golden Chainsaw with a message inscribed on the blade saying 'USE ON FRONT DOOR'.");
                    tempPTR->setActiveArea(4);
                    tempPTR->setActiveMessage("Vroom! Vroom! and your way out of this light forsaken place is opened.");
                    tempPTR->addRule(4,'l',7);
                    tempPTR->setSR(7);
                    items.insertLast(tempPTR);
                }
            }
	    }else{
            while(temp != NULL){
                if(temp->info->getType()=="Omen"){
                    cout<<"The omen vanishes as you grab it"<<endl;
                    items.deleteNode(temp->info);
                }
                temp = temp->link;
            }
	    }
	}

	void checkInstaEffect(){
	    int i=0;
	    InstaEffect* LvI;
	    if(currentLocation->info.getInstaUsed()>0){
            currentLocation->info.setInstaUsed(currentLocation->info.getInstaUsed()-1);
            cout<<currentLocation->info.getInstaMess()<<endl;
            while(currentLocation->info.getLUCKvIRONY(LvI,i)){
                if(LvI->dmgAtt=="m"){
                    if(LvI->dmgTypeRm==0){
                        might-=LvI->dmgAmt;
                    }else if(LvI->dmgTypeRm==1){
                        might+=LvI->dmgAmt;
                    }
                }else if(LvI->dmgAtt=="a"){
                    if(LvI->dmgTypeRm==0){
                        agility-=LvI->dmgAmt;
                    }else if(LvI->dmgTypeRm==1){
                        agility+=LvI->dmgAmt;
                    }
                }else if(LvI->dmgAtt=="s"){
                    if(LvI->dmgTypeRm==0){
                        sanity-=LvI->dmgAmt;
                    }else if(LvI->dmgTypeRm==1){
                        sanity+=LvI->dmgAmt;
                    }
                }else if(LvI->dmgAtt=="k"){
                    if(LvI->dmgTypeRm==0){
                        knowledge-=LvI->dmgAmt;
                    }else if(LvI->dmgTypeRm==1){
                        knowledge+=LvI->dmgAmt;
                    }
                }
                i++;
                if(LvI->dmgAmt!=0){
                    reportStats();
                }
            }
	    }
	    return;
	}

	void checkRollEffect(){
        int i=0;
        RollEffect* Dicey;
        srand(time(0));
        if(currentLocation->info.getRollUsed()>0){
            currentLocation->info.setRollUsed(currentLocation->info.getRollUsed()-1);
            cout<<currentLocation->info.getRollMess()<<endl;
            while(currentLocation->info.getDice4Life(Dicey,i)){
                int diceCnt,result=0;
                if(Dicey->dice=="m"){
                    diceCnt=might;
                }else if(Dicey->dice=="a"){
                    diceCnt=agility;
                }else if(Dicey->dice=="s"){
                    diceCnt=sanity;
                }else if(Dicey->dice=="k"){
                    diceCnt=knowledge;
                }
                for(int d=0;d<diceCnt;d++){
                    int roll=rand()%3;
                    result+=roll;
                    //cout<<"dice "<<d+1<<": "<<roll<<endl;
                }
                string traitEffected;
                int HurtvHeal, eAmt;
                if(result>=Dicey->hRoll){
                    cout<<Dicey->hMess<<endl;
                    traitEffected=Dicey->Hatt;
                    HurtvHeal=Dicey->hEffect;
                    eAmt=Dicey->hrAmt;
                }else if(result>=Dicey->mRoll){
                    cout<<Dicey->mMess<<endl;
                    traitEffected=Dicey->Matt;
                    HurtvHeal=Dicey->mEffect;
                    eAmt=Dicey->mrAmt;
                }else{
                    cout<<Dicey->lMess<<endl;
                    traitEffected=Dicey->Latt;
                    HurtvHeal=Dicey->lEffect;
                    eAmt=Dicey->lrAmt;
                }
                if(traitEffected=="m"){
                    if(HurtvHeal==0){
                        might-=eAmt;
                    }else if(HurtvHeal==1){
                        might+=eAmt;
                    }
                }else if(traitEffected=="a"){
                    if(HurtvHeal==0){
                        agility-=eAmt;
                    }else if(HurtvHeal==1){
                        agility+=eAmt;
                    }
                }else if(traitEffected=="s"){
                    if(HurtvHeal==0){
                        sanity-=eAmt;
                    }else if(HurtvHeal==1){
                        sanity+=eAmt;
                    }
                }else if(traitEffected=="k"){
                    if(HurtvHeal==0){
                        knowledge-=eAmt;
                    }else if(HurtvHeal==1){
                        knowledge+=eAmt;
                    }
                }
                i++;
                if(eAmt!=0){
                    reportStats();
                }
            }
        }
	}

	void resetPlayerStats(){
		might = mightReset;
		sanity = sanityReset;
        agility = agilityReset;
        knowledge = knowledgeReset;
	}

	void reportStats(){
	    cout<<"Status of "<<playerName<<endl;
		cout<<"Player Might:     "<<might<<endl;
		cout<<"Player Sanity:    "<<sanity<<endl;
        cout<<"Player Agility:   "<<agility<<endl;
        cout<<"Player Knowledge: "<<knowledge<<endl;
	}

	void interact(Map* mapptr){//searching area not inventory to use
	    inventory();
	    if(items.getFirst()==NULL){
            return;
        }
	    cout<<"Interact with what item? (type none to cancel)"<<endl;
	    string n;
		getline(cin, n);
		if(n=="none"){return;}
		Effect* drugs;
        nodeType<Item*>* temp = items.getFirst();
        bool found = false;
        while(temp != NULL && !found){
            if(n == temp->info->getName()){
                found = true;
            }else{
                temp = temp->link;
            }
        }
        if(found){
            cout<<"You grab: "<<n<<endl;
            cout<<temp->info->getDesc()<<endl;
            if(temp->info->getType()=="Use"){
                    if(mapptr->reverseLookUp(currentLocation) == temp->info->getActiveArea()||temp->info->getActiveArea() == 0){
                        cout<<temp->info->getActiveMessage()<<endl;
                        mapptr->newLinks(temp);
                    }else{
                        cout<<"You cannot use the "<<temp->info->getName()<<" here."<<endl;
                    }
            }else if(temp->info->getType()=="Consume"){
                if(temp->info->getUseCnt()<=0){
                    cout<<"You cannot consume " <<temp->info->getName()<<" anymore."<<endl;
                    return;
                }
                temp->info->setUseCnt(temp->info->getUseCnt()-1);
                if(mapptr->reverseLookUp(currentLocation) == temp->info->getActiveArea()||temp->info->getActiveArea() == 0){
                    cout<<temp->info->getActiveMessage()<<endl;
                    int i=0;
                    while(temp->info->getConsequences(drugs, i)){
                        if(drugs->attribute=="m"){
                            if(drugs->effectID==0){
                                might-=drugs->effectAmt;
                            }else if(drugs->effectID==1){
                                might+=drugs->effectAmt;
                            }
                        }else if(drugs->attribute=="a"){
                            if(drugs->effectID==0){
                                agility-=drugs->effectAmt;
                            }else if(drugs->effectID==1){
                                agility+=drugs->effectAmt;
                            }
                        }else if(drugs->attribute=="s"){
                            if(drugs->effectID==0){
                                sanity-=drugs->effectAmt;
                            }else if(drugs->effectID==1){
                                sanity+=drugs->effectAmt;
                            }
                        }else if(drugs->attribute=="k"){
                            if(drugs->effectID==0){
                                knowledge-=drugs->effectAmt;
                            }else if(drugs->effectID==1){
                                knowledge+=drugs->effectAmt;
                            }
                        }
                        i++;
                    }
                    if(drugs->effectAmt!=0){
                        reportStats();
                    }
                }else{
                    cout<<"You cannot consume the "<<temp->info->getName()<<" here."<<endl;
                }
            }else if(temp->info->getType()=="Interact"){
                if(temp->info->getUseCnt()<=0){
                    cout<<"You cannot interact with " <<temp->info->getName()<<" anymore."<<endl;
                    return;
                }
                temp->info->setUseCnt(temp->info->getUseCnt()-1);
                if(mapptr->reverseLookUp(currentLocation) == temp->info->getActiveArea()||temp->info->getActiveArea() == 0){
                    cout<<temp->info->getActiveMessage()<<endl;
                    int i=0;
                    while(temp->info->getConsequences(drugs, i)){
                        if(drugs->attribute=="m"){
                            if(drugs->effectID==0){
                                might-=drugs->effectAmt;
                            }else if(drugs->effectID==1){
                                might+=drugs->effectAmt;
                            }
                        }else if(drugs->attribute=="a"){
                            if(drugs->effectID==0){
                                agility-=drugs->effectAmt;
                            }else if(drugs->effectID==1){
                                agility+=drugs->effectAmt;
                            }
                        }else if(drugs->attribute=="s"){
                            if(drugs->effectID==0){
                                sanity-=drugs->effectAmt;
                            }else if(drugs->effectID==1){
                                sanity+=drugs->effectAmt;
                            }
                        }else if(drugs->attribute=="k"){
                            if(drugs->effectID==0){
                                knowledge-=drugs->effectAmt;
                            }else if(drugs->effectID==1){
                                knowledge+=drugs->effectAmt;
                            }
                        }
                        i++;
                    }
                    if(drugs->effectAmt!=0){
                        reportStats();
                    }
                }else{
                    cout<<"You cannot use the "<<temp->info->getName()<<" here."<<endl;
                }
            }else if(temp->info->getType()=="Omen"||temp->info->getType()=="basic"){
                            //do nothing
            }
        }else{
            cout<<"No item by that name here."<<endl;
        }
    }

	void consume(Map* mapptr){
	    interact(mapptr);
    }

	void use(Map* mapptr){
	    interact(mapptr);
    }

    void snag(Map* mapptr){
	    currentLocation->info.search();
	    if(currentLocation->info.items.getFirst()==NULL){return;}
	    cout<<"Snag what item? (type none to cancel)"<<endl;
	    string n;
		getline(cin, n);
		if(n=="none"){return;}
		Effect* drugs;
        nodeType<Item*>* temp = NULL;
		temp = currentLocation->info.items.getFirst();
        bool found = false;
        while(temp != NULL && !found){
            if(n == temp->info->getName()){
                found = true;
                items.insertLast(temp->info);
                currentLocation->info.items.deleteNode(temp->info);
            }else{
                temp = temp->link;
            }
        }
        if(found){
            cout<<"You have snagged: "<<n<<endl;
            cout<<temp->info->getDesc()<<endl;
            char ans='S';
            if(temp->info->getType()=="Use"){
                while(ans!='y'&&ans!='n'){
                    cout<<"Would you like to use this item now? (y/n)"<<endl;
                    cin>>ans;
                    cin.ignore();
                    if(ans=='y'){
                        if(mapptr->reverseLookUp(currentLocation) == temp->info->getActiveArea()||temp->info->getActiveArea() == 0){
                            cout<<temp->info->getActiveMessage()<<endl;
                            mapptr->newLinks(temp);
                        }else{
                            cout<<"You cannot use the "<<temp->info->getName()<<" here."<<endl;
                        }
                    }else if(ans=='n'){return;}
                    else{
                        cout<<"Input of '"<<ans<<"' does not compute"<<endl;
                    }
                }
            }else if(temp->info->getType()=="Consume"){
                while(ans!='y'&&ans!='n'){
                    cout<<"Would you like to consume this item now? (y/n)"<<endl;
                    cin>>ans;
                    cin.ignore();
                    if(ans=='y'){
                        if(temp->info->getUseCnt()<=0){
                            cout<<"You cannot consume " <<temp->info->getName()<<" anymore."<<endl;
                            return;
                        }
                        temp->info->setUseCnt(temp->info->getUseCnt()-1);
                        if(mapptr->reverseLookUp(currentLocation) == temp->info->getActiveArea()||temp->info->getActiveArea() == 0){
                            cout<<temp->info->getActiveMessage()<<endl;
                            int i=0;
                            while(temp->info->getConsequences(drugs, i)){
                                if(drugs->attribute=="m"){
                                    if(drugs->effectID==0){
                                        might-=drugs->effectAmt;
                                    }else if(drugs->effectID==1){
                                        might+=drugs->effectAmt;
                                    }
                                }else if(drugs->attribute=="a"){
                                    if(drugs->effectID==0){
                                        agility-=drugs->effectAmt;
                                    }else if(drugs->effectID==1){
                                        agility+=drugs->effectAmt;
                                    }
                                }else if(drugs->attribute=="s"){
                                    if(drugs->effectID==0){
                                        sanity-=drugs->effectAmt;
                                    }else if(drugs->effectID==1){
                                        sanity+=drugs->effectAmt;
                                    }
                                }else if(drugs->attribute=="k"){
                                    if(drugs->effectID==0){
                                        knowledge-=drugs->effectAmt;
                                    }else if(drugs->effectID==1){
                                        knowledge+=drugs->effectAmt;
                                    }
                                }
                                i++;
                            }
                            if(drugs->effectAmt!=0){
                                reportStats();
                            }
                        }else{
                            cout<<"You cannot consume the "<<temp->info->getName()<<" here."<<endl;
                        }
                    }else if(ans=='n'){return;}
                else{
                        cout<<"Input of '"<<ans<<"' does not compute"<<endl;
                    }
                }
            }else if(temp->info->getType()=="Interact"){
                while(ans!='y'&&ans!='n'){
                    cout<<"Would you like to interact with this item now? (y/n)"<<endl;
                    cin>>ans;
                    cin.ignore();
                    if(ans=='y'){
                        if(temp->info->getUseCnt()<=0){
                            cout<<"You cannot interact with " <<temp->info->getName()<<" anymore."<<endl;
                            return;
                        }
                        temp->info->setUseCnt(temp->info->getUseCnt()-1);
                        if(mapptr->reverseLookUp(currentLocation) == temp->info->getActiveArea()||temp->info->getActiveArea() == 0){
                            cout<<temp->info->getActiveMessage()<<endl;
                            int i=0;
                            while(temp->info->getConsequences(drugs, i)){
                                if(drugs->attribute=="m"){
                                    if(drugs->effectID==0){
                                        might-=drugs->effectAmt;
                                    }else if(drugs->effectID==1){
                                        might+=drugs->effectAmt;
                                    }
                                }else if(drugs->attribute=="a"){
                                    if(drugs->effectID==0){
                                        agility-=drugs->effectAmt;
                                    }else if(drugs->effectID==1){
                                        agility+=drugs->effectAmt;
                                    }
                                }else if(drugs->attribute=="s"){
                                    if(drugs->effectID==0){
                                        sanity-=drugs->effectAmt;
                                    }else if(drugs->effectID==1){
                                        sanity+=drugs->effectAmt;
                                    }
                                }else if(drugs->attribute=="k"){
                                    if(drugs->effectID==0){
                                        knowledge-=drugs->effectAmt;
                                    }else if(drugs->effectID==1){
                                        knowledge+=drugs->effectAmt;
                                    }
                                }
                                i++;
                            }
                            if(drugs->effectAmt!=0){
                                reportStats();
                            }
                        }else{
                            cout<<"You cannot use the "<<temp->info->getName()<<" here."<<endl;
                        }
                    }else if(ans=='n'){return;}
                    else{
                        cout<<"Input of '"<<ans<<"' does not compute"<<endl;
                    }
                }
            }else if(temp->info->getType()=="Omen"||temp->info->getType()=="basic"){
                            //do nothing
            }
        }else{
            cout<<"No item by that name here."<<endl;
        }
    }

private:
    int playerNum;
    string playerName;
    int might,mightReset;
    int sanity,sanityReset;
    int agility,agilityReset;
    int knowledge,knowledgeReset;
    int omenC=0, omenN=0, OmensNeeded;
};
#endif
