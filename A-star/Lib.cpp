#include "Lib.h"

using namespace std;

class Cell {
private:
	pair<int, int> pos;
	bool status;
	int weight;
	int g;
	pair<int, int> parent_pos;
	int get_heuristic (pair<int, int> finish) {
		return abs(pos.first - finish.first) + abs(pos.second - finish.second);
	}
public:
	Cell() {
		pos = make_pair(-1, -1);
		status = 0;
		g = 0;
		weight = 0;
		parent_pos = make_pair(-1, -1);
	}
	Cell(pair<int, int> pos, bool status) {
		this->pos = pos;
		this->status = status;
		g = 0;
		weight = 0;
		parent_pos = make_pair(-1, -1);
	}
	void set_weight(int energy_to, pair<int, int> finish) {
		g = energy_to;
		weight = energy_to + 10 * get_heuristic(finish);
	}
	void set_parent(pair<int, int> parent_pos) {
		this->parent_pos = parent_pos;
	}
	pair<int, int> get_pos() {
		return pos;
	}
	bool get_status() {
		return status;
	}
	int get_weight() {
		return weight;
	}
	int get_g() {
		return g;
	}
	pair<int, int> get_parent() {
		return parent_pos;
	}
};

vector<pair<int, int>> set_obstacles(int* size, int rows, int cols) {
	cout << "How many obstacles do you want to enter? ";
	cin >> *size;
	while (*size < 0 || cin.fail()) {
		cin.clear();
		cin.ignore(8192, '\n');
		cout << "Reenter quantity: ";
		cin >> *size;
	}
	vector<pair<int, int>> obstacles;
	obstacles.resize(*size);
	int x, y;
	for (int i = 0; i < *size; i++)
	{
		cout << "Enter x" << i+1 << ": ";
		cin >> x;
		while (x < 0 || x >= rows || cin.fail()) {
			cin.clear();
			cin.ignore(8192, '\n');
			cout << "Reenter x: ";
			cin >> x;
		}
		cout << "Enter y" << i + 1 << ": ";
		cin >> y;
		while (y < 0 || y>= cols || cin.fail()) {
			cin.clear();
			cin.ignore(8192, '\n');
			cout << "Reenter y: ";
			cin >> y;
		}
		obstacles[i] = make_pair(x, y);
	}
	return obstacles;
}

void set_size(int* rows, int* cols) {
	cout << "How many rows do you want? ";
	cin >> *rows;
	while (*rows <= 0 || cin.fail()) {
		cin.clear();
		cin.ignore(8192, '\n');
		cout << "Reenter rows: ";
		cin >> *rows;
	}
	cout << "How many cols do you want? ";
	cin >> *cols;
	while (*cols <= 0 || cin.fail()) {
		cin.clear();
		cin.ignore(8192, '\n');
		cout << "Reenter cols: ";
		cin >> *cols;
	}
}

bool is_found(vector<pair<int, int>> pair_array, pair<int, int> find) {
	for (size_t i = 0; i < pair_array.size(); i++)
		if (pair_array[i] == find)
			return true;
	return false;
}

int** create_matrix(int rows, int cols, vector<pair<int, int>> obstacles, int obs_size) {
	int** matrix = new int * [rows];
	for (int i = 0; i < rows; i++)
	{
		matrix[i] = new int[cols];
		for (int j = 0; j < cols; j++)
			matrix[i][j] = is_found(obstacles, make_pair(i, j));
	}
	return matrix;
}

void print_array(int* array, int size) {
	for (int i = 0; i < size; i++)
		cout << setw(3) << array[i];
	cout << endl;
}

void print_matrix(int** matrix, int rows, int cols) {
	for (int i = 0; i < rows; i++)
		print_array(matrix[i], cols);
}

void print_matrix(int** matrix, int rows, int cols, vector<pair<int, int>> path) {
	for (int i = 0; i < rows; i++) {
		for (int j = 0; j < cols; j++)
		{
			if (is_found(path, make_pair(i, j))) {
				if (path[0] == make_pair(i, j))
					cout << setw(3) << 'S';
				else if (path[path.size() - 1] == make_pair(i, j))
					cout << setw(3) << 'F';
				else
					cout << setw(3) << '-';
			}
			else
				cout << setw(3) << matrix[i][j];
		}
		cout << endl;
	}
}

void delete_matrix(int** matrix, int rows) {
	for (int i = 0; i < rows; i++)
		delete[] matrix[i];
	delete[] matrix;
}

void set_s_f(std::pair<int, int>& start, std::pair<int, int>& finish, int rows, int cols) {
	cout << "Enter the start point x: ";
	cin >> start.first;
	while (start.first >= rows || cin.fail()) {
		cin.clear();
		cin.ignore(8192, '\n');
		cout << "Reenter the start point x: ";
		cin >> start.first;
	}
	cout << "Enter the start point y: ";
	cin >> start.second;
	while (start.second >= cols || cin.fail()) {
		cin.clear();
		cin.ignore(8192, '\n');
		cout << "Reenter the start point y: ";
		cin >> start.second;
	}
	cout << "Enter the finish point x: ";
	cin >> finish.first;
	while (finish.first >= rows || cin.fail()) {
		cin.clear();
		cin.ignore(8192, '\n');
		cout << "Reenter the finish point x: ";
		cin >> finish.first;
	}
	cout << "Enter the finish point y: ";
	cin >> finish.second;
	while (finish.second >= cols|| cin.fail()) {
		cin.clear();
		cin.ignore(8192, '\n');
		cout << "Reenter the finish point y: ";
		cin >> finish.second;
	}
}

std::vector<std::pair<int, int>> create_list(int** matrix, int rows, int cols, std::pair<int, int> start, std::pair<int, int> finish) {
	vector<Cell> opened;
	vector<Cell> closed;
	Cell current_cell;
	int found_pos;
	opened.push_back(Cell(start, 0));
	while (find_pos(opened, finish) == -1 && !opened.empty()) {
		int min_weight = opened[0].get_weight();
		for (size_t i = 0; i < opened.size(); i++)
			if (opened[i].get_weight() < min_weight)
				min_weight = opened[i].get_weight();
		for (size_t i = 0; i < opened.size(); i++) {
			if (opened[i].get_weight() == min_weight) {
				current_cell = opened[i];
				swap(opened[opened.size() - 1], opened[i]);
				closed.push_back(current_cell);
				opened.pop_back();
				break;
			}
		}
		for (int i = current_cell.get_pos().first - 1; i <= current_cell.get_pos().first + 1; i++) {
			for (int j = current_cell.get_pos().second - 1; j <= current_cell.get_pos().second + 1; j++) {
				if (i >= 0 && i < rows && j >= 0 && j < cols && !matrix[i][j] && find_pos(closed, make_pair(i, j)) == -1) {
					if (find_pos(opened, make_pair(i, j)) == -1) {
						opened.push_back(Cell(make_pair(i, j), matrix[i][j]));
						opened[opened.size() - 1].set_weight(current_cell.get_g() + ((i == current_cell.get_pos().first || j == current_cell.get_pos().second) ? 10 : 14), finish);
						opened[opened.size() - 1].set_parent(current_cell.get_pos());
					}
					else if ((((i == current_cell.get_pos().first || j == current_cell.get_pos().second) ? 10 : 14) + current_cell.get_g()) < opened[find_pos(opened, make_pair(i, j))].get_g()) {
						found_pos = find_pos(opened, make_pair(i, j));
						opened[found_pos].set_weight(current_cell.get_g() + ((i == current_cell.get_pos().first || j == current_cell.get_pos().second) ? 10 : 14), finish);
						opened[found_pos].set_parent(current_cell.get_pos());
					}
				}
			}
		}
	}
	vector<pair<int, int>> path;
	if (!opened.empty()) {
		closed.push_back(Cell(finish, 0));
		closed[closed.size() - 1].set_weight(current_cell.get_g() + ((finish.first == current_cell.get_pos().first || finish.second == current_cell.get_pos().second) ? 10 : 14), finish);
		closed[closed.size() - 1].set_parent(current_cell.get_pos());
		path = create_path(closed);
	}
	else {
		closed.clear();
		cout << "No path." << endl;
	}
	return path;
}

int find_pos(std::vector<Cell> pair_array, std::pair<int, int> find) {
	for (size_t i = 0; i < pair_array.size(); i++)
		if (pair_array[i].get_pos() == find)
			return i;
	return -1;
}

vector<pair<int, int>> create_path(vector<Cell> closed_list) {
	vector<pair<int, int>> path;
	Cell current_cell = closed_list[closed_list.size() - 1];
	path.push_back(closed_list[closed_list.size() - 1].get_pos());
	for (int i = closed_list.size() - 1; i >= 0; i--)
	{
		if (closed_list[i].get_pos() == current_cell.get_parent()) {
			path.insert(path.begin(), closed_list[i].get_pos());
			current_cell = closed_list[i];
		}
	}
	return path;
}