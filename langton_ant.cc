////////////////////////////////
//
// Author: Zhiqian Yuan
//
//
////////////////////////////////

#include <iostream>

using namespace std;

#include <stdlib.h>
#include <time.h>

//orientation = 0, 1, 2, 3 to denote up, down, left, right respectively
#define UP    0
#define DOWN  1
#define LEFT  2
#define RIGHT 3

#define TURN_LEFT  0
#define TURN_RIGHT 1

#define R_FULL   0
#define R_CENTER 1

template<int Scale>
class LangtonAnt {
 public:
     LangtonAnt(int ori, int x, int y)
         : _x(x), _y(y), _ori(ori) {
         for (int i = 0; i < Scale; ++i) {
             for (int j = 0; j < Scale; ++j) {
                 _board[i][j] = 0;
             }
         }
     }

     void randomize_board(int type) {
         switch (type) {
             case R_FULL:
                 randomize_full_board();
                 break;
             case R_CENTER:
                 randomize_central_board(5);
                 break;
         };
     }

     void run(int steps) {
         for (int i = 0; i < steps; ++i) {
             _step = i;
             check_and_move();
         }
     }

     // 0 indicates white and 1 indicates black
     void check_and_move() {
         if (_board[_y][_x] == 0) {
             _board[_y][_x] = 1;
             turn_and_move(TURN_RIGHT); 
         } else {
             _board[_y][_x] = 0;
             turn_and_move(TURN_LEFT); 
         } 
     }

     void turn_and_move(int turn) {
         switch (_ori) {
             case UP:
                 _x = turn ? (_x + 1) : (_x - 1);
                 _ori = turn ? RIGHT : LEFT;
                 check_border(_x);
                 break;
             case DOWN:
                 _x = turn ? (_x - 1) : (_x + 1);
                 _ori = turn ? LEFT : RIGHT;
                 check_border(_x);
                 break;
             case LEFT:
                 _y = turn ? (_y + 1) : (_y - 1);
                 _ori = turn ? UP : DOWN;
                 check_border(_y);
                 break;
             case RIGHT:
                 _y = turn ? (_y - 1) : (_y + 1);
                 _ori = turn ? DOWN : UP;
                 check_border(_y);
                 break;
         }
     }

     void print() {
         for (int i = Scale - 1; i >= 0; --i) {
             for (int j = 0; j < Scale; ++j) {
                 if (_x == j && _y == i) {
                     char ch;

                     switch (_ori) {
                         case UP:
                             ch = '#';
                             break;
                         case DOWN:
                             ch = '$';
                             break;
                         case LEFT:
                             ch = '%';
                             break;
                         case RIGHT:
                             ch = '^';
                             break;
                         default:
                             ch = '!';
                     };

                     cout << ch << "";
                 } else {
                     cout << (_board[i][j] ? "_" : "0") << "";
                 }
             }

             cout << endl;
         }

         cout << endl;
     }

     void check_border(int val) {
         if (val < 0 || val >= Scale) {
             cout << "border reached! step: " << _step << endl;
             print();
             exit(1);
         }
     }

 private:
     void randomize_full_board() {
         srand(time(NULL));
         for (int i = 0; i < Scale; ++i) {
             for (int j = 0; j < Scale; ++j) {
                 int color = rand() % 2;
                 _board[i][j] = color;
             }
         }
     }

     void randomize_central_board(int range) {
         srand(time(NULL));
         for (int i = Scale / 2 - range; i < Scale / 2 + range; ++i) {
             for (int j = Scale / 2 - range; j < Scale / 2 + range; ++j) {
                 int color = rand() % 2;
                 _board[i][j] = color;
             }
         }
     }

 private:
     int _board[Scale][Scale];
     int _x;
     int _y;
     int _ori;
     int _step;
};

int main() {
    LangtonAnt<150> ant(UP, 75, 75);
    ant.print();

    ant.randomize_board(R_CENTER);
    ant.run(12000);

    ant.print();

    return 0;
}





