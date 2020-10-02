
#include "base.h"


int main(){
    
    NPuzzle game;
    bool flag=0;
   
    game.setsize(game);
    game.Build_Table(game);
    
    cout<<"Solve inteligent algorithm:  v"<<endl;
    cout<<"Prints a report:             t"<<endl;
    cout<<"Saves the current board:     e"<<endl;
    cout<<"Loads the current board:     o"<<endl;
    cout<<"Left move:                   l"<<endl;
    cout<<"Right move:                  r"<<endl;
    cout<<"Up move:                     u"<<endl;
    cout<<"Down move:                   d"<<endl;
    cout<<"Inteligent move:             i"<<endl;
    cout<<"Shuffle:                     s"<<endl;
    while(flag!=1){
        game.print(game);
        game.move_blank(game);
        NPuzzle::getMoves();
        flag=game.isSolved(game);
    }
   
   
    return 0;
}
