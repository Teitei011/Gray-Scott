#include <cstdlib>
#include <iostream>
#include <iomanip>
#include <string>
#include <tuple>
#include <vector>
#include <cmath>

class Cell{
public:
  float _A{1.};
  float _B{0.};
};


auto swap(Cell grid, Cell next, int N){
    // Criando matriz swap
    Cell **swap = new Cell *[N];
    Cell *SC = new Cell [N*N];

    // linking pointers
    for (int i = 0; i < N; i++) {
      swap[i] = &SC[i*N];
    }

//    swap = grid;
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        swap[i][j]._A = grid[i][j]._A;
        swap[i][j]._B= grid[i][j]._B;
      }
    }

  //  grid = next;
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      grid[i][j]._A = next[i][j]._A;
      grid[i][j]._B = next[i][j]._B;
    }
  }

    // next = swap;
    for (int i = 0; i < N; ++i) {
      for (int j = 0; j < N; ++j) {
        next[i][j]._A = swap[i][j]._A;
        next[i][j]._B = swap[i][j]._B;
      }
    }

    return {next, swap};
}

int main(int argc, char const *argv[]){
  int N = 15 + 2;
  int pequena_area = 3;
  pequena_area = floor(N / pequena_area);


    // Criando matrix
    Cell **grid = new Cell *[N];
    Cell *SA = new Cell [N*N];

    Cell **next = new Cell *[N];
    Cell *SB = new Cell [N*N];

    // linking pointers
    for (int i = 0; i < N; i++) {
      grid[i] = &SA[i*N];
      next[i] = &SB[i*N];
    }


  // Inicializando a matriz com as celulas
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      grid[i][j] = Cell();
      next[i][j] = Cell();
    }
  }


  // Colocar numa pequena area B = 1
  for (int i = 0; i < pequena_area; ++i) {
    for (int j = 0; j < pequena_area; ++j) {
      grid[pequena_area + i][pequena_area + j]._B = 1.;
      next[pequena_area + i][pequena_area + j]._B = 1.;
    }
  }


  swap(grid, next, N);
  return 0;
}
