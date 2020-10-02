
#include <iostream>
#include <ctime>
#include <fstream>
#include <string>

#ifndef base
#define base

using namespace std;
class NPuzzle{
    public:
      void  print(const NPuzzle & game);
      void setsize(NPuzzle &game);
      void Build_Table(NPuzzle &game);
      int compare(NPuzzle &game);
      void move_blank(NPuzzle &game);
      int down_move(NPuzzle &game);   
      int left_move(NPuzzle & game);
      int up_move(NPuzzle & game);
      int right_move(NPuzzle & game);
      void PrintReport(NPuzzle & game);
      static int  getMoves();
      void moveRandom(NPuzzle & game);
      void  writeToFile(NPuzzle &game);
      void readFromFile(NPuzzle & game);
      bool isSolved(NPuzzle & game);
      void moveIntelligent(NPuzzle & game);
      int distance(NPuzzle& game);
      int counterFun(NPuzzle & game,int key);
      
      void another_move(NPuzzle & game);
      
    private:
      int **puzzle;
      int height;
      int lenght;
      static int turn;
      static int move;
      int stage[4];
};





#endif