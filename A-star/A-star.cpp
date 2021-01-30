#include "Lib.h"

using namespace std;

int main()
{
    int obs_size, rows, cols;
    set_size(&rows, &cols);
    vector<pair<int, int>> obstacles = set_obstacles(&obs_size, rows, cols);
    int** matrix = create_matrix(rows, cols, obstacles, obs_size);
    cout << "Your map:" << endl;
    print_matrix(matrix, rows, cols);
    std::pair<int, int> start;
    std::pair<int, int> finish;
    set_s_f(start, finish, rows, cols);
    vector<pair<int, int>> path = create_list(matrix, rows, cols, start, finish);
    if (!path.empty())
        cout << "Your path:" << endl;
    print_matrix(matrix, rows, cols, path);
    delete_matrix(matrix, rows);
    system("pause");
}