//consume and use item classes at bottom
#ifndef H_Item
#define H_Item
#ifndef h_structs
#define h_structs
    #include "structs.h"
#endif

#include <string>
#include <iostream>
#include <vector>
using namespace std;

class Item{
 	public:
        Item(){
            activeMessage = "That seems quite impossible.";
            activeArea = -1;
            type = "basic";
        }
        void setName (string n){
            name = n;
        }
		void setDesc(string desc){
			description = desc;
		}
		void setSR(int rm){
			startRoom = rm;
		}
		string getName(){
            return name;
        }
        string getDesc(){
            return description;
        }
        int getSR(){
			return startRoom;
		}
		void displayName(){
			cout<<name<<endl;
		}
		void displayDesc(){
			cout<<description<<endl;
		}
		string getType(){
            return type;
		}

        virtual void setUseCnt(int x){
            cout<<"DEBUG WARNING: Objects of the Item (basic items) class don't have active messages."<<endl;
        }

        virtual int getUseCnt(){
            int uC = 0;
            return uC;
        }

        virtual void setDmgType(int x){
            cout<<"DEBUG WARNING: Objects of the Item (basic items) class don't have active messages."<<endl;
        }

        virtual int getDmgType(){
            int dT = 0;
            return dT;
        }

        virtual void setAmt(int x){
            cout<<"DEBUG WARNING: Objects of the Item (basic items) class don't have active messages."<<endl;
        }

        virtual int getAmt(){
            int gA = 0;
            return gA;
        }

        virtual void setAttribute(string x){
            cout<<"DEBUG WARNING: Objects of the Item (basic items) class don't have active messages."<<endl;
        }

        virtual string getAttribute(){
            string gA = "You see no way to do that";
            return gA;
        }

        virtual void setActiveMessage(string s){
            cout<<"DEBUG WARNING: Objects of the Item (basic items) class don't have active messages."<<endl;
	    }
	    virtual string getActiveMessage(){
           //Objects of the Item (basic items) class don't have active messages.
           string aM = "You see no way to do that.";
           return aM;
	    }
		virtual void setActiveArea(int i){
            cout<<"DEBUG WARNING: Objects of the Item (basic items) class don't have active areas."<<endl;
		}
		virtual int getActiveArea(){
            //as this is a basic item, it doesn't have an active area
            return -1;
		}
		virtual void addRule(Rule* temp){
			cout<<"DEBUG WARNING: Objects of the Item (basic items) class don't have associated rules."<<endl;
		}
        virtual vector<Rule*> getItemUseRules(){
            //shouldn't ever call this method directly
			return T3C;
		}
		virtual void addEffect(Effect* temp){
			cout<<"DEBUG WARNING: Objects of the Item (basic items) class don't have associated effects."<<endl;
		}
        virtual vector<Effect*> getItemConsumeEffects(){
			//shouldn't ever call this method directly
			return consequences;
		}

		bool getConsequences(Effect* &drugs, int i){
		    if(i!=consequences.size()){
                drugs=consequences[i];
                return true;
            }else{
                return false;
            }
        }

        bool getT3C(Rule* &rule, int i){
            if(i!=T3C.size()){
                rule=T3C[i];
                return true;
            }else{
                return false;
            }
        }

        virtual void resetUseCnt(){
            //do nothing
        }

	friend ostream& operator<<(ostream&, Item&);

    protected:
        string name;
    	string description;
        int startRoom;
        string activeMessage;
        int activeArea;
        string type;
        vector<Effect*> consequences;
        vector<Rule*> T3C;//the three commandments
        int useCnt, useCntReset=0;
        int dmgType;
        int amt;
        string attribute;

};

ostream& operator<<(ostream& osObject, Item& item){
	osObject<<"Name: "<<item.getName()<<endl;
	osObject<<"Desc: "<<item.getDesc()<<endl;
	osObject<<"StrtRm: "<<item.getSR()<<endl;
	return osObject;
}


class ConsumeItem : public Item{
public:
    Effect consume;

    ConsumeItem(){
        activeMessage = "That seems quite impossible.";
        activeArea = -1;
        type = "Consume";
    }

    void setActiveMessage(string s){
        activeMessage=s;
    }

    string getActiveMessage(){
        return activeMessage;
    }

    void setActiveArea(int i){
        activeArea=i;
    }

    int getActiveArea(){
        return activeArea;
    }

    void setUseCnt(int x){
        useCnt=x;
        if(useCntReset==0){

            useCntReset=x;
        }
    }

    int getUseCnt(){
        return useCnt;
    }

    void resetUseCnt(){
        setUseCnt(useCntReset);
    }

    void addEffect(string att, int eID, int eAmt){
        Effect* consume1=new Effect;
        consume1->attribute=att;
        consume1->effectAmt=eAmt;
        consume1->effectID=eID;
        consequences.push_back(consume1);
    }
};

class UseItem : public Item{
public:
    Rule use;

    UseItem(){
        activeMessage = "That seems quite impossible.";
        activeArea = -1;
        type = "Use";
    }

    void setActiveMessage(string s){
        activeMessage=s;
    }

    string getActiveMessage(){
        return activeMessage;
    }

    void setActiveArea(int i){
        activeArea=i;
    }

    int getActiveArea(){
        return activeArea;
    }

    void addRule(int b, char dir, int des){
        Rule* use1 = new Rule;
        use1->beginRm=b;
        use1->direction=dir;
        use1->destRm=des;
        T3C.push_back(use1);
    }
};

class omenItem : public Item{
public:
    omenItem(){
        activeMessage = "That seems quite impossible.";
        activeArea = -1;
        type = "Omen";
    }
};

class interactItem : public Item{
public:
    interactItem(){
        activeMessage = "That seems quite impossible.";
        activeArea = -1;
        type = "Interact";
    }

    void setName(string s){
        name=s;
    }

    string getName(){
        return name;
    }

    void setDesc(string s){
        description = s;
    }

    string getDesc(){
        return description;
    }

    void setActiveMessage(string s){
        activeMessage=s;
    }

    string getActiveMessage(){
        return activeMessage;
    }

    void setActiveArea(int i){
        activeArea=i;
    }

    int getActiveArea(){
        return activeArea;
    }

    void setUseCnt(int x){
        useCnt=x;
        if(useCntReset==0){
            useCntReset=x;
        }
    }

    int getUseCnt(){
        return useCnt;
    }

    void resetUseCnt(){
        setUseCnt(useCntReset);
    }

    void addEffect(string att, int eID, int eAmt){
        Effect* consume1=new Effect;
        consume1->attribute=att;
        consume1->effectAmt=eAmt;
        consume1->effectID=eID;
        consequences.push_back(consume1);
    }
};
#endif
