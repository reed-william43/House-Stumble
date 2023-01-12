#include "MapV2.h"
#include "Player.h"
#include "Map.h"

#ifndef ullItem
#define ullItem
    #include "ull.h"
    #include "Item.h"
#endif
class Game{
	private:
		Player* player1;
		MapV2 map;
  	public:
  	    void Title(){
            cout << R"(
         ___  ___   ________   ___  ___   ________   _______           ________   _________   ___  ___   _____ ______    ________   ___        _______
        |\  \|\  \ |\   __  \ |\  \|\  \ |\   ____\ |\  ___ \         |\   ____\ |\___   ___\|\  \|\  \ |\   _ \  _   \ |\   __  \ |\  \      |\  ___ \
        \ \  \\\  \\ \  \|\  \\ \  \\\  \\ \  \___|_\ \   __/|        \ \  \___|_\|___ \  \_|\ \  \\\  \\ \  \\\__\ \  \\ \  \|\ /_\ \  \     \ \   __/|
         \ \   __  \\ \  \\\  \\ \  \\\  \\ \_____  \\ \  \_|/__       \ \_____  \    \ \  \  \ \  \\\  \\ \  \\|__| \  \\ \   __  \\ \  \     \ \  \_|/__
          \ \  \ \  \\ \  \\\  \\ \  \\\  \\|____|\  \\ \  \_|\ \       \|____|\  \    \ \  \  \ \  \\\  \\ \  \    \ \  \\ \  \|\  \\ \  \____ \ \  \_|\ \
           \ \__\ \__\\ \_______\\ \_______\ ____\_\  \\ \_______\        ____\_\  \    \ \__\  \ \_______\\ \__\    \ \__\\ \_______\\ \_______\\ \_______\
            \|__|\|__| \|_______| \|_______||\_________\\|_______|       |\_________\    \|__|   \|_______| \|__|     \|__| \|_______| \|_______| \|_______|
                                            \|_________|                 \|_________|
                                         ____ ____ ____ ____ _________ ____ ____ ____ ____ ____ ____
                                        ||G |||A |||M |||E |||       |||E |||N |||G |||I |||N |||E ||
                                        ||__|||__|||__|||__|||_______|||__|||__|||__|||__|||__|||__||
                                        |/__\|/__\|/__\|/__\|/_______\|/__\|/__\|/__\|/__\|/__\|/__\| (version 4.20)
                                            CREATED BY: STEPHEN KILLOUGH & WILLIAM REED
                                       .     .
                                       !!!!!!!
                               .       [[[|]]]    .
                               !!!!!!!!|--_--|!!!!!                              ____                                               ____ ____ ____ ____
                               [[[[[[[[\_(X)_/]]]]]                             ||u ||                                             ||h |||e |||l |||p ||
                       .-.     /-_--__-/_--_-\-_--\             To move enter:  ||__||          If you forget the controls enter:  ||__|||__|||__|||__||
                       |=|    /-_---__/__-__-_\__-_\                            |/__\|                                             |/__\|/__\|/__\|/__\|
                   . . |=| ._/-__-__\===========/-__\_                       ____ ____ ____
                   !!!!!!!!!\========[ /]]|[[\ ]=====/                      ||l |||d |||r ||
                  /-_--_-_-_[[[[[[[[[||==  == ||]]]]]]                      ||__|||__|||__||
                 /-_--_--_--_|=  === ||=/^|^\ ||== =|                       |/__\|/__\|/__\|
                /-_-/^|^\-_--| /^|^\=|| | | | ||^\= |
               /_-_-| | |-_--|=| | | ||=|_|_|=||"|==|
              /-__--|_|_|_-_-| |_|_|=||______=||_| =|                                                                 ____ ____ ____ ____
             /_-__--_-__-___-|_=__=_.`---------'._=_|__                                                              ||s |||n |||a |||g ||
            /-----------------------\===========/-----/                             To get items from a room enter:  ||__|||__|||__|||__||
           ^^^\^^^^^^^^^^^^^^^^^^^^^^[[|]]|[[|]]=====/                                                               |/__\|/__\|/__\|/__\|
               |.' ..==::'"'::==.. '.[ /~~~~~\ ]]]]]]]
               | .'=[[[|]]|[[|]]]=`._||==  =  || =\ ]
               ||== =|/ _____ \|== = ||=/^|^\=||^\ ||
               || == `||-----||' = ==|| | | |=|| |=||
               ||= == ||:^s^:|| = == ||=| | | || |=||
               || = = ||:___:||= == =|| |_|_| ||_|=||                                                         ____ ____ ____ ____ ____ ____ ____ ____
              _||_ = =||o---.|| = ==_||_= == =||==_||_                                                       ||i |||n |||t |||e |||r |||a |||c |||t ||
              \__/= = ||:   :||= == \__/[][][][][]\__/                        To use/consume any item enter: ||__|||__|||__|||__|||__|||__|||__|||__||
              [||]= ==||:___:|| = = [||]\\//\\//\\[||]                                                       |/__\|/__\|/__\|/__\|/__\|/__\|/__\|/__\|
              }  {---'"'-----'"'- --}  {//\\//\\//}  {
            __[==]__________________[==]\\//\\//\\[==]_
           |`|~~~~|================|~~~~|~~~~~~~~|~~~~||                             ____ ____ _________ ____ ____ ____ _________ ____ ____ ____
           |^| ^  |================|^   | ^ ^^ ^ |  ^ ||                            ||D |||O |||       |||N |||O |||T |||       |||D |||I |||E ||
          \|//\\/^|/==============\|/^\\\^/^.\^///\\//|///          THE ONLY RULE:  ||__|||__|||_______|||__|||__|||__|||_______|||__|||__|||__||
         \\///\\\//===============\\//\\///\\\\////\\\/////                         |/__\|/__\|/_______\|/__\|/__\|/__\|/_______\|/__\|/__\|/__\|
         ""'""'""".'..'. ' '. ''..'.""'""'""'""''"''"''""")"<<endl;
        }

		Game(){
		    Title();
		    player1=map.getPtype();
			player1->setCurrent(map.getStart());
            map.setRmGrids();
			Move("start");
		}

  		void play(){
            string userInput;
			//cin.ignore();
            while(true){
				//check game status
				if(player1->isGameOver() != 0){
					player1->getCurrent()->info.displayArea();
					return;
				}
      				//display area data
				if(player1->playerMoved()){
	    				player1->getCurrent()->info.displayArea();
	    				player1->playerCheck();
                        if(player1->isGameOver() != 0){
                            return;
                        }

				}else{
				    if(userInput=="u"||userInput=="d"||userInput=="l"||userInput=="r"){
                        cout<<"There appears to be no way to go that direction."<<endl;
				    }
				}
	  			//get movement selection
	  			cout<<"Which way would you like to go?  Enter u, d, l, or r"<<endl;
				getline(cin, userInput);
	  			//update area
	  			if(userInput == "u"||userInput == "d"||userInput == "l"||userInput == "r"){
                    Move(userInput);
	  				/*if(player1->getCurrent()->r!=nullptr){
                        player1->setCurrent(player1->getCurrent()->r);
                        map.linkCheck(player1->getCurrent(),map.Xcords,map.Ycords);
                    }else{
                        if(map.LinksTest("r",player1->getCurrent())==1){
                            map.randRoom("r",player1->getCurrent());
                            player1->setCurrent(player1->getCurrent()->r);
                        }else if(map.LinksTest("r",player1->getCurrent())==0){
                            player1->setCurrent(player1->getCurrent()->r);
                        }
                    }*/
				}
				else if(userInput == "iseedeadpeople"){
					cout<<map;
				}
				else if(userInput == "reset"){
					resetGame();
				}
				else if(userInput == "exit"){
					cout<<"Good bye!"<<endl;
					return;
				}
				else if(userInput == "search"){
					player1->getCurrent()->info.search();
				}
				else if(userInput == "inventory"){
					player1->inventory();
				}
				else if(userInput == "take"){
					player1->take();
				}
				else if(userInput == "leave"){
					player1->leave();
				}
				else if(userInput == "examine"){
					player1->examine();
				}
				else if(userInput == "use"){
                    player1->use(&map);
				}
				else if(userInput == "consume"){
                    player1->consume(&map);
				}
				else if(userInput == "stats"){
                    player1->reportStats();
				}
				else if(userInput == "snag"){
                    player1->snag(&map);
				}
				else if(userInput == "interact"){
                    player1->interact(&map);
				}else if(userInput == "mapperDapper"){
				    if(map.mapperDapper==false){
                            map.mapperDapper=true;
                    }else{
                        map.mapperDapper=false;
                    }
				}
				else if(userInput == "help"){
					cout<<"You may type: "<<endl;
					cout<<"\t u, d, l, or r: to move up, down, left or right on the map,"<<endl;
					cout<<"\t search: to search for items in current area,"<<endl;
					cout<<"\t snag: to attempt to take an item,"<<endl;
					cout<<"\t leave: to attempt to leave an item,"<<endl;
					cout<<"\t examine: to examine an item in your inventory,"<<endl;
					cout<<"\t interact: to use or consume an item in your inventory,"<<endl;
					cout<<"\t stats: to report the player stats,"<<endl;
					cout<<"\t reset: to reset the game,"<<endl;
					cout<<"\t exit: to exit the game."<<endl;
					cout<<endl;
				}
				else{
					cout<<"I do not understand: "<<userInput<<endl<<endl;
				}
			}//end while
        }//end play()

		void resetGame(){
		    system("cls");
			player1->setCurrent(map.getStart());
			player1->items.destroyList();
			map.resetItems();
			map.resetLinks();
			map.resetRooms();
			player1->resetPlayerStats();
			map.mapperDapper=false;
			cout<<"...Game Reset..."<<endl;
			player1->difficultySelect();
			player1->playerSelect();
			Title();
			map.setRmGrids();
            //
            Move("start");
        }

        void Move(string udlr){
            string testType=player1->getCurrent()->info.getType();
            int currentRmNum=map.reverseLookUp(player1->getCurrent());
            if(udlr=="start"){
                map.Ycords=0; map.Xcords=0;
            }
            if(testType=="basement"||testType=="basmentR"){
                if(map.Ycords==0&&map.Xcords==0){
                    map.Ycords=map.bRmCnt;
                    map.Xcords=map.bRmCnt;
                    map.bGrid[map.Ycords][map.Xcords]=currentRmNum;
                    return;
                }else if(udlr=="u"||udlr=="d"||udlr=="l"||udlr=="r"){
                    if(udlr=="u"){
                        if(player1->getCurrent()->u!=nullptr){
                            if(map.bGrid[map.Ycords+1][map.Xcords]==0){
                                if(map.reverseLookUp(player1->getCurrent())!=map.reverseLookUp(player1->getCurrent()->u)){
                                    player1->setCurrent(player1->getCurrent()->u);
                                    map.Ycords++;
                                }
                            }else if(map.bGrid[map.Ycords+1][map.Xcords]==map.reverseLookUp(player1->getCurrent()->u)){
                                player1->setCurrent(player1->getCurrent()->u);
                                map.Ycords++;
                            }
                        }else{
                            if(map.bGrid[map.Ycords+1][map.Xcords]==0){
                                map.randRoom(udlr,player1->getCurrent());
                                if(map.reverseLookUp(player1->getCurrent())!=map.reverseLookUp(player1->getCurrent()->u)){
                                    player1->setCurrent(player1->getCurrent()->u);
                                    map.Ycords++;
                                }
                            }else{
                                cout<<"You hit a wall."<<endl;
                            }
                        }
                    }else if(udlr=="d"){
                        if(player1->getCurrent()->d!=nullptr){
                            if(map.bGrid[map.Ycords-1][map.Xcords]==0){
                                if(map.reverseLookUp(player1->getCurrent())!=map.reverseLookUp(player1->getCurrent()->d)){
                                    player1->setCurrent(player1->getCurrent()->d);
                                    map.Ycords--;
                                }
                            }else if(map.bGrid[map.Ycords-1][map.Xcords]==map.reverseLookUp(player1->getCurrent()->d)){
                                player1->setCurrent(player1->getCurrent()->d);
                                map.Ycords--;
                            }
                        }else{
                            if(map.bGrid[map.Ycords-1][map.Xcords]==0){
                                map.randRoom(udlr,player1->getCurrent());
                                if(map.reverseLookUp(player1->getCurrent())!=map.reverseLookUp(player1->getCurrent()->d)){
                                    player1->setCurrent(player1->getCurrent()->d);
                                    map.Ycords--;
                                }
                            }else{
                                cout<<"You hit a wall."<<endl;
                            }
                        }
                    }else if(udlr=="l"){
                        if(player1->getCurrent()->l!=nullptr){
                            if(map.bGrid[map.Ycords][map.Xcords-1]==0){
                                if(map.reverseLookUp(player1->getCurrent())!=map.reverseLookUp(player1->getCurrent()->l)){
                                    player1->setCurrent(player1->getCurrent()->l);
                                    map.Xcords--;
                                }
                            }else if(map.bGrid[map.Ycords][map.Xcords-1]==map.reverseLookUp(player1->getCurrent()->l)){
                                player1->setCurrent(player1->getCurrent()->l);
                                map.Xcords--;
                            }
                        }else{
                            if(map.bGrid[map.Ycords][map.Xcords-1]==0){
                                map.randRoom(udlr,player1->getCurrent());
                                if(map.reverseLookUp(player1->getCurrent())!=map.reverseLookUp(player1->getCurrent()->l)){
                                    player1->setCurrent(player1->getCurrent()->l);
                                    map.Xcords--;
                                }
                            }else{
                                cout<<"You hit a wall."<<endl;
                            }
                        }
                    }else if(udlr=="r"){
                        if(player1->getCurrent()->r!=nullptr){
                            if(map.bGrid[map.Ycords][map.Xcords+1]==0){
                                if(map.reverseLookUp(player1->getCurrent())!=map.reverseLookUp(player1->getCurrent()->r)){
                                    player1->setCurrent(player1->getCurrent()->r);
                                    map.Xcords++;
                                }
                            }else if(map.bGrid[map.Ycords][map.Xcords+1]==map.reverseLookUp(player1->getCurrent()->r)){
                                player1->setCurrent(player1->getCurrent()->r);
                                map.Xcords++;
                            }
                        }else{
                            if(map.bGrid[map.Ycords][map.Xcords+1]==0){
                                map.randRoom(udlr,player1->getCurrent());
                                if(map.reverseLookUp(player1->getCurrent())!=map.reverseLookUp(player1->getCurrent()->r)){
                                    player1->setCurrent(player1->getCurrent()->r);
                                    map.Xcords++;
                                }
                            }else{
                                cout<<"You hit a wall."<<endl;
                            }
                        }
                    }else{
                        cout<<"ERROR IN MOVE"<<endl;
                    }
                    currentRmNum=map.reverseLookUp(player1->getCurrent());
                    map.bGrid[map.Ycords][map.Xcords]=currentRmNum;
                }
            }else if(testType=="ground"||testType=="groundR"){
                if(map.Ycords==0&&map.Xcords==0){
                    map.Ycords=map.gRmCnt;
                    map.Xcords=map.gRmCnt;
                    map.gGrid[map.Ycords][map.Xcords]=currentRmNum;
                    return;
                }else if(udlr=="u"||udlr=="d"||udlr=="l"||udlr=="r"){
                    if(udlr=="u"){
                        if(player1->getCurrent()->u!=nullptr){
                            if(map.gGrid[map.Ycords+1][map.Xcords]==0){
                                if(map.reverseLookUp(player1->getCurrent())!=map.reverseLookUp(player1->getCurrent()->u)){
                                    player1->setCurrent(player1->getCurrent()->u);
                                    map.Ycords++;
                                }
                            }else if(map.gGrid[map.Ycords+1][map.Xcords]==map.reverseLookUp(player1->getCurrent()->u)){
                                player1->setCurrent(player1->getCurrent()->u);
                                map.Ycords++;
                            }
                        }else{
                            if(map.gGrid[map.Ycords+1][map.Xcords]==0){
                                map.randRoom(udlr,player1->getCurrent());
                                if(map.reverseLookUp(player1->getCurrent())!=map.reverseLookUp(player1->getCurrent()->u)){
                                    player1->setCurrent(player1->getCurrent()->u);
                                    map.Ycords++;
                                }
                            }else{
                                cout<<"You hit a wall."<<endl;
                            }
                        }
                    }else if(udlr=="d"){
                        if(player1->getCurrent()->d!=nullptr){
                            if(map.gGrid[map.Ycords-1][map.Xcords]==0){
                                if(map.reverseLookUp(player1->getCurrent())!=map.reverseLookUp(player1->getCurrent()->d)){
                                    player1->setCurrent(player1->getCurrent()->d);
                                    map.Ycords--;
                                }
                            }else if(map.gGrid[map.Ycords-1][map.Xcords]==map.reverseLookUp(player1->getCurrent()->d)){
                                player1->setCurrent(player1->getCurrent()->d);
                                map.Ycords--;
                            }
                        }else{
                            if(map.gGrid[map.Ycords-1][map.Xcords]==0){
                                map.randRoom(udlr,player1->getCurrent());
                                if(map.reverseLookUp(player1->getCurrent())!=map.reverseLookUp(player1->getCurrent()->d)){
                                    player1->setCurrent(player1->getCurrent()->d);
                                    map.Ycords--;
                                }
                            }else{
                                cout<<"You hit a wall."<<endl;
                            }
                        }
                    }else if(udlr=="l"){
                        if(player1->getCurrent()->l!=nullptr){
                            if(map.gGrid[map.Ycords][map.Xcords-1]==0){
                                if(map.reverseLookUp(player1->getCurrent())!=map.reverseLookUp(player1->getCurrent()->l)){
                                    player1->setCurrent(player1->getCurrent()->l);
                                    map.Xcords--;
                                }
                            }else if(map.gGrid[map.Ycords][map.Xcords-1]==map.reverseLookUp(player1->getCurrent()->l)){
                                player1->setCurrent(player1->getCurrent()->l);
                                map.Xcords--;
                            }
                        }else{
                            if(map.gGrid[map.Ycords][map.Xcords-1]==0){
                                map.randRoom(udlr,player1->getCurrent());
                                if(map.reverseLookUp(player1->getCurrent())!=map.reverseLookUp(player1->getCurrent()->l)){
                                    player1->setCurrent(player1->getCurrent()->l);
                                    map.Xcords--;
                                }
                            }else{
                                cout<<"You hit a wall."<<endl;
                            }
                        }
                    }else if(udlr=="r"){
                        if(player1->getCurrent()->r!=nullptr){
                            if(map.gGrid[map.Ycords][map.Xcords+1]==0){
                                if(map.reverseLookUp(player1->getCurrent())!=map.reverseLookUp(player1->getCurrent()->r)){
                                    player1->setCurrent(player1->getCurrent()->r);
                                    map.Xcords++;
                                }
                            }else if(map.gGrid[map.Ycords][map.Xcords+1]==map.reverseLookUp(player1->getCurrent()->r)){
                                player1->setCurrent(player1->getCurrent()->r);
                                map.Xcords++;
                            }
                        }else{
                            if(map.gGrid[map.Ycords][map.Xcords+1]==0){
                                map.randRoom(udlr,player1->getCurrent());
                                if(map.reverseLookUp(player1->getCurrent())!=map.reverseLookUp(player1->getCurrent()->r)){
                                    player1->setCurrent(player1->getCurrent()->r);
                                    map.Xcords++;
                                }
                            }else{
                                cout<<"You hit a wall."<<endl;
                            }
                        }
                    }else{
                        cout<<"ERROR IN MOVE"<<endl;
                    }
                    currentRmNum=map.reverseLookUp(player1->getCurrent());
                    map.gGrid[map.Ycords][map.Xcords]=currentRmNum;
                }
            }else if(testType=="upper"||testType=="upperR"){
                if(map.Ycords==0&&map.Xcords==0){
                    map.Ycords=map.uRmCnt;
                    map.Xcords=map.uRmCnt;
                    map.uGrid[map.Ycords][map.Xcords]=currentRmNum;
                    return;
                }else if(udlr=="u"||udlr=="d"||udlr=="l"||udlr=="r"){
                    if(udlr=="u"){
                        if(player1->getCurrent()->u!=nullptr){
                            if(map.uGrid[map.Ycords+1][map.Xcords]==0){
                                if(map.reverseLookUp(player1->getCurrent())!=map.reverseLookUp(player1->getCurrent()->u)){
                                    player1->setCurrent(player1->getCurrent()->u);
                                    map.Ycords++;
                                }
                            }else if(map.uGrid[map.Ycords+1][map.Xcords]==map.reverseLookUp(player1->getCurrent()->u)){
                                player1->setCurrent(player1->getCurrent()->u);
                                map.Ycords++;
                            }
                        }else{
                            if(map.uGrid[map.Ycords+1][map.Xcords]==0){
                                map.randRoom(udlr,player1->getCurrent());
                                if(map.reverseLookUp(player1->getCurrent())!=map.reverseLookUp(player1->getCurrent()->u)){
                                    player1->setCurrent(player1->getCurrent()->u);
                                    map.Ycords++;
                                }
                            }else{
                                cout<<"You hit a wall."<<endl;
                            }
                        }
                    }else if(udlr=="d"){
                        if(player1->getCurrent()->d!=nullptr){
                            if(map.uGrid[map.Ycords-1][map.Xcords]==0){
                                if(map.reverseLookUp(player1->getCurrent())!=map.reverseLookUp(player1->getCurrent()->d)){
                                    player1->setCurrent(player1->getCurrent()->d);
                                    map.Ycords--;
                                }
                            }else if(map.uGrid[map.Ycords-1][map.Xcords]==map.reverseLookUp(player1->getCurrent()->d)){
                                player1->setCurrent(player1->getCurrent()->d);
                                map.Ycords--;
                            }
                        }else{
                            if(map.uGrid[map.Ycords-1][map.Xcords]==0){
                                map.randRoom(udlr,player1->getCurrent());
                                if(map.reverseLookUp(player1->getCurrent())!=map.reverseLookUp(player1->getCurrent()->d)){
                                    player1->setCurrent(player1->getCurrent()->d);
                                    map.Ycords--;
                                }
                            }else{
                                cout<<"You hit a wall."<<endl;
                            }
                        }
                    }else if(udlr=="l"){
                        if(player1->getCurrent()->l!=nullptr){
                            if(map.uGrid[map.Ycords][map.Xcords-1]==0){
                                if(map.reverseLookUp(player1->getCurrent())!=map.reverseLookUp(player1->getCurrent()->l)){
                                    player1->setCurrent(player1->getCurrent()->l);
                                    map.Xcords--;
                                }
                            }else if(map.uGrid[map.Ycords][map.Xcords-1]==map.reverseLookUp(player1->getCurrent()->l)){
                                player1->setCurrent(player1->getCurrent()->l);
                                map.Xcords--;
                            }
                        }else{
                            if(map.uGrid[map.Ycords][map.Xcords-1]==0){
                                map.randRoom(udlr,player1->getCurrent());
                                if(map.reverseLookUp(player1->getCurrent())!=map.reverseLookUp(player1->getCurrent()->l)){
                                    player1->setCurrent(player1->getCurrent()->l);
                                    map.Xcords--;
                                }
                            }else{
                                cout<<"You hit a wall."<<endl;
                            }
                        }
                    }else if(udlr=="r"){
                        if(player1->getCurrent()->r!=nullptr){
                            if(map.uGrid[map.Ycords][map.Xcords+1]==0){
                                if(map.reverseLookUp(player1->getCurrent())!=map.reverseLookUp(player1->getCurrent()->r)){
                                    player1->setCurrent(player1->getCurrent()->r);
                                    map.Xcords++;
                                }
                            }else if(map.uGrid[map.Ycords][map.Xcords+1]==map.reverseLookUp(player1->getCurrent()->r)){
                                player1->setCurrent(player1->getCurrent()->r);
                                map.Xcords++;
                            }
                        }else{
                            if(map.uGrid[map.Ycords][map.Xcords+1]==0){
                                map.randRoom(udlr,player1->getCurrent());
                                if(map.reverseLookUp(player1->getCurrent())!=map.reverseLookUp(player1->getCurrent()->r)){
                                    player1->setCurrent(player1->getCurrent()->r);
                                    map.Xcords++;
                                }
                            }else{
                                cout<<"You hit a wall."<<endl;
                            }
                        }
                    }else{
                        cout<<"ERROR IN MOVE"<<endl;
                    }
                    currentRmNum=map.reverseLookUp(player1->getCurrent());
                    map.uGrid[map.Ycords][map.Xcords]=currentRmNum;
                }
            }else if(testType=="stairs"){//stairs movement
                if(udlr=="u"||udlr=="d"||udlr=="l"||udlr=="r"){
                    if(udlr=="u"){
                        if(player1->getCurrent()->u!=nullptr&&map.reverseLookUp(player1->getCurrent()->u)!=map.reverseLookUp(player1->getCurrent())){
                            player1->setCurrent(player1->getCurrent()->u);
                            Move("start");
                        }
                    }else if(udlr=="d"){
                        if(player1->getCurrent()->d!=nullptr&&map.reverseLookUp(player1->getCurrent()->d)!=map.reverseLookUp(player1->getCurrent())){
                            player1->setCurrent(player1->getCurrent()->d);
                            Move("start");
                        }
                    }else if(udlr=="l"){
                        if(player1->getCurrent()->l!=nullptr&&map.reverseLookUp(player1->getCurrent()->l)!=map.reverseLookUp(player1->getCurrent())){
                            player1->setCurrent(player1->getCurrent()->l);
                            Move("start");
                        }
                    }else if(udlr=="r"){
                        if(player1->getCurrent()->r!=nullptr&&map.reverseLookUp(player1->getCurrent()->r)!=map.reverseLookUp(player1->getCurrent())){
                            player1->setCurrent(player1->getCurrent()->r);
                            Move("start");
                        }
                    }else{
                        cout<<"ERROR IN MOVE"<<endl;
                    }
                }
            }
            map.linkCheck(player1->getCurrent(),map.Xcords,map.Ycords);
        }
};
