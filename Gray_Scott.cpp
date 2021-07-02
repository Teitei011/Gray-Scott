#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <bits/stdc++.h>

namespace chrono = std::chrono;

class Cell {
public:
  double _B;
  double _A;

  Cell(int A, int B) {
    _A = A;
    _B = B;
  }
};


void inicializando_matrix_cell(std::vector<std::vector<Cell>> &matrix, int N) {
  // Inicializando as grids
  for (int i = 0; i < N; ++i) {
    for (int j = 0; j < N; ++j) {
      matrix[i].push_back(Cell(1., 0.));
    }
  }
}

void show_A(std::vector<std::vector<Cell>> matrix) {
  std::cout << "Matriz A: " << '\n';
  for (unsigned int i = 0; i < matrix.size(); ++i) {
    for (unsigned int j = 0; j < matrix[0].size(); ++j) {
      std::cout << matrix[i][j]._A << ' ';
    }
    std::cout << '\n';
  }
}

void show_B(std::vector<std::vector<Cell>> matrix) {
  std::cout << "Matriz B: " << '\n';
  for (unsigned int i = 0; i < matrix.size(); ++i) {
    for (unsigned int j = 0; j < matrix[0].size(); ++j) {
      std::cout << matrix[i][j]._B << ' ';
    }
    std::cout << '\n';
  }
}

void swap(std::vector<std::vector<Cell>> &grid, std::vector<std::vector<Cell>> &next) {
  std::vector<std::vector<Cell>> buffer(grid.size());
  buffer = grid;
  grid = next;
  next = buffer;
}

void criando_a_pertubacao(std::vector<std::vector<Cell>> &matrix, int pequena_area) { // Colocar numa pequena area B = 1
  for (int i = 0; i < int(pequena_area); ++i) {
    for (int j = 0; j < int(pequena_area); ++j) {
      matrix[int(pequena_area) + i][int(pequena_area) + j]._B = 1.;
    }
  }
}

double laplaceA2(std::vector<std::vector<Cell>> &matrix, int x, int y) { // TODO: O problema esta aqui, tem momentos em que ele percorre espaços vazios da memoria
  double sumA{0};

  sumA += matrix[x][y]._A * -1;
  sumA += matrix[x - 1][y]._A * 0.2;
  sumA += matrix[x + 1][y]._A * 0.2;
  sumA += matrix[x][y + 1]._A * 0.2;
  sumA += matrix[x][y - 1]._A * 0.2;
  sumA += matrix[x - 1][y - 1]._A * 0.05;
  sumA += matrix[x + 1][y - 1]._A * 0.05;
  sumA += matrix[x + 1][y + 1]._A * 0.05;
  sumA += matrix[x - 1][y + 1]._A * 0.05;

  return sumA * sumA;
}

double laplaceB2(std::vector<std::vector<Cell>> &matrix, int x, int y) {
  double sumB{0};

  sumB += matrix[x][y]._B * -1;
  sumB += matrix[x - 1][y]._B * 0.2;
  sumB += matrix[x + 1][y]._B * 0.2;
  sumB += matrix[x][y + 1]._B * 0.2;
  sumB += matrix[x][y - 1]._B * 0.2;
  sumB += matrix[x - 1][y - 1]._B * 0.05;
  sumB += matrix[x + 1][y - 1]._B * 0.05;
  sumB += matrix[x + 1][y + 1]._B * 0.05;
  sumB += matrix[x - 1][y + 1]._B * 0.05;

  return sumB * sumB;
}

void matrixA2raw(std::vector<std::vector<Cell>> &matrix, int number) {
  const char *path="Images/ImagesA";
  std::ofstream output(path);
  std::string write_raw;
  write_raw = "A_" +  std::to_string(number) + ".raw";

  output.open(write_raw);
  if (output.good()) {
    for (unsigned int i = 0; i < matrix.size(); i++) {
      for (unsigned int j = 0; j < matrix[0].size(); j++){
        output << std::to_string(int(255. * matrix[i][j]._A)) << " ";
      }
      output << std::endl;
    }
  } else {
  std::cerr << "Error in the: " << write_raw << " iteration" << std::endl;
  }output.close();
}

void matrixB2raw(std::vector<std::vector<Cell>> &matrix, int number) {
  const char *path="Images/ImagesB";
  std::ofstream output(path);
  std::string write_raw;
  write_raw = "B_" +  std::to_string(number) + ".raw";

  output.open(write_raw);
  if (output.good()) {
    for (unsigned int i = 0; i < matrix.size(); i++) {
      for (unsigned int j = 0; j < matrix[0].size(); j++){
        output << std::to_string(int(255. * matrix[i][j]._B)) << " ";
      }
      output << std::endl;
    }
  } else {
  std::cerr << "Error in the: " << write_raw << " iteration" << std::endl;
  }output.close();
}

int main(int argc, char const *argv[]) {
  double elapsed{0};
  chrono::high_resolution_clock::time_point t1, t2;

  double D_a, D_b, Food, Kill;
  double buffer_ab{0};

  int N;
  int iteracoes;

  // Pegando os argumentos dados no inicio da funcao
  if (argc != 7) {
    std::cout << "Usage: " << argv[0] << " <D_a> <D_b> <Food> <Kill> <Resolution> <Iterations> \n";
    exit(1);
  }

// Colocando os argumentos nas respectivas variaveis
  D_a =  std::atof(argv[1]);
  D_b =  std::atof(argv[2]);
  Food =  std::atof(argv[3]);
  Kill =  std::atof(argv[4]);
  N =  std::stoi(argv[5]);
  iteracoes =  std::stoi(argv[6]);

  N +=2; // Evitando assim o problema das laterais

  // int pequena_area = floor(N * (1. / 16.));
  int pequena_area = 3;

  t1 = chrono::high_resolution_clock::now(); // Timing

  // Criando a matrix
  std::vector<std::vector<Cell>> grid(N), next(N);

  inicializando_matrix_cell(grid, N);

  criando_a_pertubacao(grid, pequena_area);
  next = grid;

  for (int i = 0; i < iteracoes; i++) {
    // Percorrendo as matrizes

    for (int j = 1; j < N - 1; j++) {
      for (int k = 1; k < N - 1; k++) {
        buffer_ab = next[j][k]._A * next[j][k]._B * next[j][k]._B;
        if (j == k && k == 2){
          buffer_ab = next[j][k]._A * next[j][k]._B * next[j][k]._B;
          std::cout << i << " " << buffer_ab << '\n';
        }
        grid[j][k]._A = next[j][k]._A + (D_a * laplaceA2(next, j, k) - buffer_ab
        + Food * (1. - next[j][k]._A));

      grid[j][k]._B = next[j][k]._B + (D_b * laplaceB2(next, j, k) + buffer_ab -
      (Kill + Food) * next[j][k]._B);
      }
    }

    swap(grid, next);

    std::cout << "Iteração: " << i << '\n';
    // show_B(grid);

    // Salvando o estado para criar uma imagem depois
    // matrixA2raw(grid, i);
    matrixB2raw(grid, i);

  }
  std::system("mv *.raw \\Images");
  // show_B(grid);

  // matrixA2raw(grid, 1);

  t2 = chrono::high_resolution_clock::now();

  auto dt = chrono::duration_cast<chrono::microseconds>(t2 - t1);
  elapsed += dt.count();

  // Show timing results
  std::cout << "Iterations: " << iteracoes
            << "\nTime Taken: " << elapsed / 1.0 / 1e6 << " seconds" << std::endl;
  return 0;
}
