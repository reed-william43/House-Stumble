#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <iostream>
using namespace std;

#ifndef H_IFDParser
#define H_IFDParser

class IFDParser{
	public:
	IFDParser(){
		pos = 0;
		gameFile = "";
	}

	void tokenIt(){
		string token="";
		string nextLine;
		char c;

		if(gameFile == ""){
			gameFile = getFile();
		}

	   	ifstream inFile;
	   	inFile.open(gameFile.c_str());

        cin.ignore();
		while(!inFile.eof()){
			getline(inFile, nextLine);
			trim(nextLine);
		        c=nextLine[0];

			//dump any comment or blank line (all comments exist alone on their lines)
			if(c=='%' || nextLine == ""){
				//do nothing
			}
			else{
				//tokenize the entire line
				for(int i=0; i<nextLine.length(); i++){
					if(nextLine[i] == '>'){
						token = token + nextLine[i];
						if(token !="\n" && token !="" && token !=" " && token !="\t"){
							tokenVec.push_back(token);
						}
						token = "";
					}
					else if(nextLine[i]=='<'){
						if(token !="\n" && token !="" && token !=" " && token !="\t"){
							tokenVec.push_back(token);
						}
						token = "";
						token = token + nextLine[i];
					}
					else{
						token = token + nextLine[i];
					}
				}
			}
		}//while !eof
		inFile.close();
		return;
	}// end of tokenIt()

	void eatToken(){
		pos++;
	}

	string getNext(){
		return tokenVec[pos];
	}

	//helper function for trimming a string's white space
	void trim(string& s)
    	{
       	size_t p = s.find_first_not_of(" \t");
       	s.erase(0, p);
    		p = s.find_last_not_of(" \t");
       	if (string::npos != p)
          		s.erase(p+1);
    	}

	void printTokens(){
		cout<<":::Printing the Tokens in Order:::"<<endl;
		for(int i=0; i<tokenVec.size(); i++){
			cout<<i<<": "<<tokenVec[i]<<endl;
		}
	}

	string getFile(){
		cout<<"Enter the file name."<<endl;
		cin>>gameFile;cout<<endl;
		return gameFile;
	}

	private:
		int pos;
		string gameFile;
        vector<string> tokenVec;
};
#endif
