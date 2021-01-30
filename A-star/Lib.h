#pragma once
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>

class Cell;

std::vector<std::pair<int, int>> set_obstacles(int* size, int rows, int cols);
void set_size(int* rows, int* cols);
bool is_found(std::vector<std::pair<int, int>> pair_array, std::pair<int, int> find);
int** create_matrix(int rows, int cols, std::vector<std::pair<int, int>> obstacles, int obs_size);
void print_array(int* array, int size);
void print_matrix(int** matrix, int rows, int cols);
void print_matrix(int** matrix, int rows, int cols, std::vector<std::pair<int, int>> path);
void delete_matrix(int** matrix, int rows);
void set_s_f(std::pair<int, int> &start, std::pair<int, int> &finish, int rows, int cols);
std::vector<std::pair<int, int>> create_list(int** matrix, int rows, int cols, std::pair<int, int> start, std::pair<int, int> finish);
int find_pos(std::vector<Cell> pair_array, std::pair<int, int> find);
std::vector<std::pair<int, int>> create_path(std::vector<Cell> closed_list);