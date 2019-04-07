#include <iostream>
#include <algorithm>
#include <iterator>
#include <vector>
#include <sstream>
#include <set>
#include <utility>
#include <climits>
#include <algorithm>
#include <cmath>
#include <bits/stdc++.h>
#include <cstdlib>
#include <cstdio>
#include <iomanip>

using namespace std;

int KaprekarsConstant(int num) {
    int result = 0;
    int count = 0;
    if (num < 100) num *= 100;
    else if (num < 1000) num *= 10;

    while (num != 6174) {
        string small = to_string(num);
        sort(small.begin(), small.end());
        string big;
        reverse_copy(small.begin(), small.end(), big.begin());
        // cout << "big: " << big << endl;
        int big_int = stoi(big);
        int small_int = stoi(small);
        num = big_int - small_int;
        cout << "big_int: " << big_int << " small_int: " << small_int
             << " result: " << result << endl;
        ++count;
        // result = 6174;
    }
    // code goes here
    return count;

}


int MaximalSquare(string strArr[], int height, int width) {
    int **counter = new int *[height];
    for (int i = 0; i < height; ++i) {
        counter[i] = new int[width];
    }
    for (int i = 0; i < height; ++i) {
        counter[i][0] = strArr[i][0] - '0';
    }
    for (int j = 0; j < width; ++j) {
        counter[0][j] = strArr[0][j] - '0';
    }
    int max_count = 1;
    for (int i = 1; i < height; ++i) {
        for (int j = 1; j < width; ++j) {
            // cout << strArr[i][j] << endl;
            if (strArr[i][j] == '1') {
                int local_max = min(min(counter[i - 1][j], counter[i][j - 1]),
                                    counter[i - 1][j - 1]);
                counter[i][j] = local_max + 1;
                if (counter[i][j] > max_count) {
                    max_count = counter[i][j];
                }
            } else {
                counter[i][j] = 0;
            }
        }
    }
    for (int i = 0; i < height; ++i) {
        delete[] counter[i];
    }
    delete[] counter;
    return max_count;
}

int max_square() {
    // string A[] = {"0111", "1111", "1111", "1111"};
    string A[] = {"0111", "1101", "0111"};
    // cout << A[0][1] << endl;
    int width = A[0].size();
    int height = sizeof(A) / sizeof(A[0]);
    cout << MaximalSquare(A, height, width);
    return 0;
}

string CorrectPath(string str, int i, int h, int w) {
    // cout << str << " " << i << " " << h << " " << w << endl;
    string result;
    if (i >= str.size()) {
        if (h == 4 && w == 4) {
            str.push_back('s');
        } else {
            str.push_back('f');
        }
        return str;
    }
    if (str[i] == 'u') {
        result = CorrectPath(str, i + 1, h - 1, w);
    } else if (str[i] == 'd') {
        result = CorrectPath(str, i + 1, h + 1, w);
    } else if (str[i] == 'r') {
        result = CorrectPath(str, i + 1, h, w + 1);
    } else if (str[i] == 'l') {
        result = CorrectPath(str, i + 1, h, w - 1);
    } else {
        result = CorrectPath(str, i + 1, h - 1, w);
        if (result[result.size() - 1] == 'f') {
            result = CorrectPath(str, i + 1, h, w - 1);
            if (result[result.size() - 1] == 'f') {
                result = CorrectPath(str, i + 1, h, w + 1);
                if (result[result.size() - 1] == 'f') {
                    result = CorrectPath(str, i + 1, h + 1, w);
                    result[i] = 'd';
                } else {
                    result[i] = 'r';
                }
            } else {
                result[i] = 'l';
            }
        } else {
            result[i] = 'u';
        }
    }
    if (i == 0) result.pop_back();
    return result;
}

vector<int> from_string_to_vector(string input) {
    vector<int> array;
    input.pop_back(); // pop [
    input = input.substr(1, input.size()); // pop [
    int pos = input.find(",");
    while (pos != string::npos) {
        // cout << "input: " << input.substr(0, pos) << endl;
        int number = stoi(input.substr(0, pos));
        // cout << number << endl;
        array.push_back(number);
        input = input.substr(pos + 1, input.size() - pos - 1);
        // cout << input << endl;
        pos = input.find(",");
    }
    int number = stoi(input.substr(0, pos));
    array.push_back(number);
    return array;
}

string ScaleBalancing(string strArr[]) {
    int pos = strArr[0].find(",");
    // cout << "pos: " << pos << " " << strArr[0].substr(1, pos-1) << endl;
    int l = stoi(strArr[0].substr(1, pos - 1));
    int r = stoi(strArr[0].substr(pos + 1, strArr[0].size() - 1));
    // cout << "l: " <<  l << " r:" << r << endl;

    vector<int> array = from_string_to_vector(strArr[1]);
//  for (int i : array) {
//      cout << i << endl;
//  }

    for (int a : array) {
        if (l + a == r || l == r + a)
            return to_string(a);
    }

    int a, b;
    for (int i = 0; i < array.size(); ++i) {
        for (int j = i + 1; j < array.size(); ++j) {
            if (array[i] < array[j]) {
                a = array[i];
                b = array[j];
            } else {
                a = array[j];
                b = array[i];
            }
            if (l + a + b == r || l + a == r + b || l + b == r + a ||
                l == r + a + b) {
                return to_string(a) + "," + to_string(b);
            }
        }
    }

    // code goes here
    return "not possible";

}

string VowelSquare(string strArr[], int size) {
    char myvowels[] = {'a', 'e', 'i', 'o', 'u'};
    set<char> vowels(myvowels, myvowels + 5);
    for (int i = 0; i < size - 1; ++i) {
        for (int j = 0; j < strArr[i].size() - 1; ++j) {
            if (vowels.find(strArr[i][j]) != vowels.end() &&
                vowels.find(strArr[i][j + 1]) != vowels.end() &&
                vowels.find(strArr[i + 1][j]) != vowels.end() &&
                vowels.find(strArr[i + 1][j + 1]) != vowels.end()) {
                return to_string(i) + "-" + to_string(j);
            }
        }
    }
    return "not found";
}

int vowels() {
    // string A[] = gets(stdin);
    string A[] = {"aqrst",
                  "ukaei",
                  "ffooo"};
    int size = sizeof(A) / sizeof(A[0]);
    cout << VowelSquare(A, size);
    return 0;
}

string EightQueens(string strArr[], int size) {
    for (int i = 0; i < size - 1; ++i) {
        int x1 = strArr[i][1] - '0';
        int y1 = strArr[i][3] - '0';
        for (int j = i + 1; j < size; ++j) {
            int x2 = strArr[j][1] - '0';
            int y2 = strArr[j][3] - '0';
            if ((x2 - x1 == y2 - y1) || (x1 == x2) || (y1 == y2)) {
                return "(" + to_string(x1) + "," + to_string(y1) + ")";
            }
        }
    }
    return "true";
}

void mainEightQueens() {

    // keep this function call here
    /* Note: In C++ you first have to initialize an array and set
       it equal to the stdin to test your code with arrays. */

    string A[] = {"(2,1)", "(4,3)", "(6,3)", "(8,4)", "(3,4)", "(1,6)", "(7,7)",
                  "(5,8)"};
    int size = sizeof(A) / sizeof(A[0]);
    cout << EightQueens(A, size);
}

string ClosestEnemyII(string strArr[], int size) {
    int row_size = strArr[0].size();
    int a[size][row_size];
    int x1, y1;
    vector<pair<int, int> > twos;
    for (int i = 0; i < size; ++i) {
        for (int j = 0; j < row_size; ++j) {
            a[i][j] = strArr[i][j] - '0';
            if (a[i][j] == 1) {
                x1 = i;
                y1 = j;
            } else if (a[i][j] == 2) {
                twos.push_back(make_pair(i, j));
            }
        }
    }
    int distance = INT_MAX;
    if (twos.size() == 0) return "0";
    for (pair<int, int> p : twos) {
        int x2 = p.first;
        int y2 = p.second;

        int dx_left;
        int dx_right;
        if (x1 < x2) {
            dx_left = x1;
            dx_right = row_size - x2;
        } else {
            dx_left = x2;
            dx_right = row_size - 1;
        }
        int dx_side = dx_left + dx_right;
        int dx = min(abs(x2 - x1), dx_side);

        int dy_down;
        int dy_up;
        if (y1 < y2) {
            dy_down = y1;
            dy_up = size - y2;
        } else {
            dy_down = y2;
            dy_up = size - y1;
        }
        int dy_side = dy_up + dy_down;
        int dy = min(abs(y2 - y1), dy_side);

        int delta = dx + dy;

        if (delta < distance) {
            distance = delta;
        }

    }
    return to_string(distance);

}

int mainClosestEnemyII() {
    string A[] = {"000", "100", "200"};
    int size = sizeof(A) / sizeof(A[0]);
    cout << ClosestEnemyII(A, size);
    return 0;
}

string QuestionsMarks(string str) {
    string result = "false";
    for (int i = 0; i < str.size();) {
        while ((str[i] < '0' || str[i] > '9') && i < str.size()) {
            ++i;
        }
        if (i == str.size()) return result;
        int first = str[i] - '0';
        // cout << "first: " << first << endl;
        ++i;
        int q_count = 0;
        while ((str[i] < '0' || str[i] > '9') && i < str.size()) {
            if (str[i] == '?') {
                ++q_count;
            }
            ++i;
        }
        if (i == str.size()) return result;
        int second = str[i] - '0';
        ++i;
        // cout << "second: " << second << endl;
        // cout << "q_count: " << q_count << endl;
        if ((second + first) == 10) {
            // cout << "q_count 2: " << q_count << endl;
            if (q_count >= 3) {
                result = "true";
            } else {
                result = "false";
            }
        }
    }
    return result;

}

int mainQuestionMarks() {
    // keep this function call here
    cout << QuestionsMarks("3???7??????5???5");
    return 0;
}

string ltrim(const string &);

string rtrim(const string &);

vector<string> split(const string &);

// Complete the matrixRotation function below.

/*
You are given a 2D matrix of dimension and a positive integer . You have to
rotate the matrix r times and print the resultant matrix.

Rotation should be in anti-clockwise direction.

Rotation of a matrix is represented by the following figure. Note that in one
 rotation, you have to shift elements by one step only.
 */
void matrixRotation(vector<vector<int>> &matrix, int r, int x, int y,
                    int m, int n) {
    int elem_count = 2 * m + 2 * n - 4;
    if (elem_count <= 1 || m <= 0 || n <= 0) return;
    // gather elements in the one round of the matrix
    vector<int> snake;

    // go to right
    int row = y;
    for (int col = x; col < x + n; ++col) {
        snake.push_back(matrix[row][col]);
    }
    // go down
    if (m > 1) {
        int col = x + n - 1;
        // skip top right corner
        for (int row = y + 1; row < y + m; ++row) {
            snake.push_back(matrix[row][col]);
        }
    }
    // go to left
    if (m > 1) {
        int row = y + m - 1;
        for (int col = x + n - 2; col >= x; --col) {
            snake.push_back(matrix[row][col]);
        }
    }
    // go up
    if (n > 1 && m > 1) {
        int col = x;
        for (int row = y + m - 2; row > y; --row) {
            snake.push_back(matrix[row][col]);
        }
    }

    // write elements out of the snake: snake index
    int s = r % elem_count;

    // go to right
    row = y;
    for (int col = x; col < x + n; ++col) {
        matrix[row][col] = snake[s];
        s = (s + 1) % elem_count;
    }
    // go down
    if (m > 1) {
        int col = x + n - 1;
        // skip top right corner
        for (int row = y + 1; row < y + m; ++row) {
            matrix[row][col] = snake[s];
            s = (s + 1) % elem_count;
        }
    }
    // go to left
    if (m > 1) {
        int row = y + m - 1;
        for (int col = x + n - 2; col >= x; --col) {
            matrix[row][col] = snake[s];
            s = (s + 1) % elem_count;
        }
    }
    // go up
    if (n > 1 && m > 1) {
        int col = x;
        for (int row = y + m - 2; row > y; --row) {
            matrix[row][col] = snake[s];
            s = (s + 1) % elem_count;
        }
    }

    return matrixRotation(matrix, r, x + 1, y + 1, m - 2, n - 2);

}

int mainMatrixRotation() {
    string mnr_temp;
    getline(cin, mnr_temp);

    vector<string> mnr = split(rtrim(mnr_temp));

    int m = stoi(mnr[0]);

    int n = stoi(mnr[1]);

    int r = stoi(mnr[2]);

    vector<vector<int>> matrix(m);

    for (int i = 0; i < m; i++) {
        matrix[i].resize(n);

        string matrix_row_temp_temp;
        getline(cin, matrix_row_temp_temp);

        vector<string> matrix_row_temp = split(rtrim(matrix_row_temp_temp));

        for (int j = 0; j < n; j++) {
            int matrix_row_item = stoi(matrix_row_temp[j]);

            matrix[i][j] = matrix_row_item;
        }
    }

    matrixRotation(matrix, r, 0, 0, m, n);

    return 0;
}

int mainMatrixRotationInput() {
    // Test case 1:
    //    int m = 4;
    //    int n = 4;
    //    int r = 2;
    //
    //    vector<vector<int>> matrix = {{1,  2,  3,  4},
    //                                  {5,  6,  7,  8},
    //                                  {9,  10, 11, 12},
    //                                  {13, 14, 15, 16}};
    //
    // Test case 2:
    //    int m = 5;
    //    int n = 4;
    //    int r = 7;
    //
    //    vector<vector<int>> matrix = {{1,  2,  3,  4},
    //                                  {7,  8,  9,  10},
    //                                  {13, 14, 15, 16},
    //                                  {19, 20, 21, 22},
    //                                  {25, 26, 27, 28}};
    //
    // Test case 3:
    //    int m = 2;
    //    int n = 2;
    //    int r = 3;
    //
    //    vector<vector<int>> matrix = {{1,1},{1,1}};
    // Test case 4:
    int m = 10;
    int n = 8;
    int r = 40;

    vector<vector<int>> matrix(m);
    int i = 0;
    for (int row = 0; row < m; ++row) {
        matrix[row].resize(n);
        for (int col = 0; col < n; ++col) {
            matrix[row][col] = i++;
        }
    }

    // print matrix
    for (int row = 0; row < m; ++row) {
        for (int col = 0; col < n; ++col) {
            cout << matrix[row][col] << " ";
        }
        cout << std::endl;
    }
    cout << std::endl;

    matrixRotation(matrix, r, 0, 0, m, n);


    // print matrix
    for (int row = 0; row < m; ++row) {
        for (int col = 0; col < n; ++col) {
            cout << matrix[row][col] << " ";
        }
        cout << std::endl;
    }

    return 0;
}

string ltrim(const string &str) {
    string s(str);

    s.erase(s.begin(),
            find_if(s.begin(), s.end(), not1(ptr_fun<int, int>(isspace))));

    return s;
}

string rtrim(const string &str) {
    string s(str);

    s.erase(
            find_if(s.rbegin(), s.rend(),
                    not1(ptr_fun<int, int>(isspace))).base(),
            s.end());

    return s;
}

vector<string> split(const string &str) {
    vector<string> tokens;

    string::size_type start = 0;
    string::size_type end = 0;

    while ((end = str.find(" ", start)) != string::npos) {
        tokens.push_back(str.substr(start, end - start));

        start = end + 1;
    }

    tokens.push_back(str.substr(start));

    return tokens;
}

// Complete the formingMagicSquare function below.
int formingMagicSquare(vector<vector<int>> s) {
    int min_cost = INT_MAX;
    vector<vector<vector<int>>> templates = {
            {
                    {8, 3, 4},
                    {1, 5, 9},
                    {6, 7, 2}
            },
            {
                    {6, 7, 2},
                    {1, 5, 9},
                    {8, 3, 4}
            },
            {
                    {4, 9, 2},
                    {3, 5, 7},
                    {8, 1, 6}
            },
            {
                    {2, 9, 4},
                    {7, 5, 3},
                    {6, 1, 8}
            },
            {
                    {2, 7, 6},
                    {9, 5, 1},
                    {4, 3, 8}
            },
            {
                    {4, 3, 8},
                    {9, 5, 1},
                    {2, 7, 6}
            },
            {
                    {6, 1, 8},
                    {7, 5, 3},
                    {2, 9, 4}
            },
            {
                    {8, 1, 6},
                    {3, 5, 7},
                    {4, 9, 2}
            }
    };
    for (vector<vector<int>> temp : templates) {
        int cost = 0;
        for (int i = 0; i < 3; ++i) {
            for (int j = 0; j < 3; ++j) {
                cost += abs(temp[i][j] - s[i][j]);
            }
        }
        if (cost < min_cost) min_cost = cost;
    }
    return min_cost;
}

int mainFormingMagicSquares() {

//    vector<vector<int>> s(3);
//    for (int i = 0; i < 3; i++) {
//        s[i].resize(3);
//
//        for (int j = 0; j < 3; j++) {
//            cin >> s[i][j];
//        }
//
//        cin.ignore(numeric_limits<streamsize>::max(), '\n');
//    }

    vector<vector<int>> s = {{5, 3, 4},
                             {1, 5, 8},
                             {6, 4, 2}};

    int result = formingMagicSquare(s);

    // expected 7
    cout << result << "\n";

    return 0;
}

vector<string> split_string(string);

// Complete the climbingLeaderboard function below.
vector<int> climbingLeaderboard(vector<int> scores, vector<int> alice) {
    vector<int> ranks;
    if (scores.empty()) {
        for (int i = 0; i < alice.size(); ++i) {
            ranks.push_back(1);
        }
        return ranks;
    }
    vector<int> unique_scores;
    int last_score = INT_MAX;
    for (int score : scores) {
        if (score < last_score) {
            unique_scores.push_back(score);
            last_score = score;
        }
    }
    int s = unique_scores.size() - 1;
    for (int i = 0; i < alice.size();) {
        if (s < 0 || alice[i] < unique_scores[s]) {
            ranks.push_back(s + 2);
            ++i;
        } else {
            --s;
        }
    }
    return ranks;
}

// Complete the climbingLeaderboard function below.
vector<int> climbingLeaderboard2(vector<int> scores, vector<int> alice) {
    vector<int> ranks;
    if (scores.empty()) {
        for (int i = 0; i < alice.size(); ++i) {
            ranks.push_back(1);
        }
        return ranks;
    }
    vector<int> unique_scores;
    int last_score = INT_MAX;
    for (int score : scores) {
        if (score < last_score) {
            unique_scores.push_back(score);
            last_score = score;
        }
    }
    for (int score : alice) {
        int left = 0;
        int right = unique_scores.size() - 1;
        while (left < right) {
            int half = int((left + right) / 2);
            if (unique_scores[half] > score) {
                left = half + 1;
            } else if (unique_scores[half] < score) {
                right = half - 1;
            } else {
                break;
            }
        }
        if (unique_scores[left] <= score) {
            ranks.push_back(left + 1);
        } else {
            ranks.push_back(left + 2);
        }
    }
    return ranks;
}

int mainAlice() {
//    ofstream fout(getenv("OUTPUT_PATH"));
//
//    int scores_count;
//    cin >> scores_count;
//    cin.ignore(numeric_limits<streamsize>::max(), '\n');
//
//    string scores_temp_temp;
//    getline(cin, scores_temp_temp);
//
//    vector<string> scores_temp = split_string(scores_temp_temp);
//
//    vector<int> scores(scores_count);
//
//    for (int i = 0; i < scores_count; i++) {
//        int scores_item = stoi(scores_temp[i]);
//
//        scores[i] = scores_item;
//    }
//
//    int alice_count;
//    cin >> alice_count;
//    cin.ignore(numeric_limits<streamsize>::max(), '\n');
//
//    string alice_temp_temp;
//    getline(cin, alice_temp_temp);
//
//    vector<string> alice_temp = split_string(alice_temp_temp);
//
//    vector<int> alice(alice_count);
//
//    for (int i = 0; i < alice_count; i++) {
//        int alice_item = stoi(alice_temp[i]);
//
//        alice[i] = alice_item;
//    }

    // vector<int> scores = {295,294,291,287,287,285,285,284,283,279,277,274,274,271,270,268,268,268,264,260,259,258,257,255,252,250,244,241,240,237,236,236,231,227,227,227,226,225,224,223,216,212,200,197,196,194,193,189,188,187,183,182,178,177,173,171,169,165,143,140,137,135,133,130,130,130,128,127,122,120,116,114,113,109,106,103,99,92,85,81,69,68,63,63,63,61,57,51,47,46,38,30,28,25,22,15,14,12,6,4};
    // vector<int> alice = {5,5,6,14,19,20,23,25,29,29,30,30,32,37,38,38,38,41,41,44,45,45,47,59,59,62,63,65,67,69,70,72,72,76,79,82,83,90,91,92,93,98,98,100,100,102,103,105,106,107,109,112,115,118,118,121,122,122,123,125,125,125,127,128,131,131,133,134,139,140,141,143,144,144,144,144,147,150,152,155,156,160,164,164,165,165,166,168,169,170,171,172,173,174,174,180,184,187,187,188,194,197,197,197,198,201,202,202,207,208,211,212,212,214,217,219,219,220,220,223,225,227,228,229,229,233,235,235,236,242,242,245,246,252,253,253,257,257,260,261,266,266,268,269,271,271,275,276,281,282,283,284,285,287,289,289,295,296,298,300,300,301,304,306,308,309,310,316,318,318,324,326,329,329,329,330,330,332,337,337,341,341,349,351,351,354,356,357,366,369,377,379,380,382,391,391,394,396,396,400};

    vector<int> scores = {100, 100, 50, 40, 40, 20, 10};
    vector<int> alice = {5, 25, 50, 120};

    vector<int> result = climbingLeaderboard(scores, alice);

    for (int i = 0; i < result.size(); i++) {
        std::cout << result[i];

        if (i != result.size() - 1) {
            cout << "\n";
        }
    }

    cout << "\n";

    return 0;
}

vector<string> split_string(string input_string) {
    string::iterator new_end = unique(input_string.begin(), input_string.end(),
                                      [](const char &x, const char &y) {
                                          return x == y and x == ' ';
                                      });

    input_string.erase(new_end, input_string.end());

    while (input_string[input_string.length() - 1] == ' ') {
        input_string.pop_back();
    }

    vector<string> splits;
    char delimiter = ' ';

    size_t i = 0;
    size_t pos = input_string.find(delimiter);

    while (pos != string::npos) {
        splits.push_back(input_string.substr(i, pos - i));

        i = pos + 1;
        pos = input_string.find(delimiter, i);
    }

    splits.push_back(
            input_string.substr(i, min(pos, input_string.length()) - i + 1));

    return splits;
}


int mainMean() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int counter = 10;
    // cin >> counter;
    // cout << "counter: " << counter << endl;
    if (counter == 0) {
        cout << 0 << endl << 0 << endl << 0 << endl;
    }
    vector<int> list = {64630, 11735, 14216, 99233, 14470, 4978, 73429, 38120,
                        51135, 67060};
    int sum = 0;
    for (int i = 0; i < counter; ++i) {
        // int c;
        // cin >> c;
        // list.push_back(c);
        // cout << i << " " << list[i] << endl;
        sum += list[i];
    }
    cout << (1.0 * sum) / counter << endl;
    sort(list.begin(), list.end());
    int half = int(counter / 2);
    if (counter % 2 == 1) {
        cout << list[half] << endl;
    } else {
        cout << (list[half - 1] + list[half]) / 2.0 << endl;
    }
    int mode = list[0];
    int mode_count = 1;
    int current = list[0];
    int current_count = 1;
    for (int i = 1; i < list.size(); ++i) {
        if (list[i] == current) {
            ++current_count;
        } else {
            if (current_count > mode_count) {
                mode_count = current_count;
                mode = current;
            }
            current_count = 1;
            current = list[i];
        }
    }
    cout << mode << endl;
    return 0;
}

int mainWeightedAverage() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int count;
    cin >> count;
    vector<int> nums;
    vector<int> mass;
    for (int i = 0; i < count; ++i) {
        int c;
        cin >> c;
        nums.push_back(c);
    }
    for (int i = 0; i < count; ++i) {
        int c;
        cin >> c;
        mass.push_back(c);
    }
    int num = 0;
    int den = 0;
    for (int i = 0; i < count; ++i) {
        num += nums[i] * mass[i];
        den += mass[i];
    }
    cout << std::setprecision(1) << fixed << 1.0 * num / den << endl;
    return 0;
}

int maximumToys(vector<int> prices, int k) {
    sort(prices.begin(), prices.end());
    int p = 0;
    int i = 0;
    while (i < prices.size()) {
        if ((prices[i] + p) > k) {
            break;
        }
        p += prices[i];
        ++i;
    }
    return i;
}

int mainStandardDeviation() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int N;
    cin >> N;
    vector<int> X;
    int sum = 0;
    for (int i = 0; i < N; ++i) {
        int x;
        cin >> x;
        X.push_back(x);
        sum += x;
    }
    double mean = 1.0 * sum / N;
    double squared_sum = 0.0;
    for (int i = 0; i < N; ++i) {
        squared_sum += pow((X[i] - mean), 2.0);
    }
    cout << std::fixed << std::setprecision(1) << sqrt(squared_sum / N);
    return 0;
}

int median(vector<int> X) {
    int size = X.size();
    if (size % 2 == 0) {
        int upper = size / 2;
        int lower = upper - 1;
        return (X[lower] + X[upper]) / 2;
    } else {
        return X[size / 2];
    }
}


int mainQuartiles() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int N;
    cin >> N;
    vector<int> X;
    for (int i = 0; i < N; ++i) {
        int x;
        cin >> x;
        X.push_back(x);
    }
    sort(X.begin(), X.end());
    int size = X.size();
    int half = size / 2;
    vector<int> lower_half(X.begin(), X.begin() + half);
    cout << median(lower_half) << endl;
    cout << median(X) << endl;
    if (size % 2 == 0) {
        vector<int> upper_half(X.begin() + half, X.end());
        cout << median(upper_half) << endl;
    } else {
        vector<int> upper_half(X.begin() + half + 1, X.end());
        cout << median(upper_half) << endl;
    }
    return 0;
}

pair<double, double> Quartiles(vector<int> X) {
    sort(X.begin(), X.end());
    int size = X.size();
    int half = size / 2;
    vector<int> lower_half(X.begin(), X.begin() + half);
    double q1 = median(lower_half);
    double q2;
    if (size % 2 == 0) {
        vector<int> upper_half(X.begin() + half, X.end());
        q2 = median(upper_half);
    } else {
        vector<int> upper_half(X.begin() + half + 1, X.end());
        q2 = median(upper_half);
    }
    return make_pair(q1, q2);
}

int mainInterQuartileRange() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    int N;
    cin >> N;
    vector<int> I;
    for (int i = 0; i < N; ++i) {
        int x;
        cin >> x;
        I.push_back(x);
    }
    vector<int> F;
    for (int i = 0; i < N; ++i) {
        int f;
        cin >> f;
        F.push_back(f);
    }
    vector<int> X;
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < F[i]; ++j) {
            X.push_back(I[i]);
        }
    }
    pair<double, double> quartiles = Quartiles(X);
    cout << quartiles.second - quartiles.first;
    return 0;
}


int factorial(int n) {
    return (n == 0) || (n == 1) ? 1 : factorial(n - 1) * n;
}

double poisson(double avg, int k) {
    return pow(avg, k) * exp(-avg) / factorial(k);
}

int nk(int n, int k) {
    return factorial(n) / (factorial(k) * factorial(n - k));
}

double binomial(int x, int n, double p) {
    return nk(n, x) * pow(p, x) * pow((1 - p), n - x);
}

// geometric distribution
double gem_dis(int n, double p) {
    return pow((1 - p), n - 1) * p;
}

int mainBinomial() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
//    double ratio;
//    cin >> ratio;
//    int child_per_birth;
//    cin >> child_per_birth;
    double p = 1.09 / 2.09;
    // double p = 0.5;
    double result = 0.0;
    int min = 3;
    int max = 6;
    int n = 6;  // number of trials
    for (int i = min; i <= max; ++i) {
        result += binomial(i, n, p);
    }
    std::cout << std::fixed << std::setprecision(3) << result;
    return 0;
}

int mainPoisson() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */
    std::cout << std::fixed << std::setprecision(3)
              << 160.0 + 40.0 * pow(0.88, 2) << std::endl;
    std::cout << std::fixed << std::setprecision(3)
              << 128.0 + 40.0 * pow(1.55, 2) << std::endl;
    return 0;
}


void removeZeros(string &A) {
    int from = 0;
    for (int i = 0; i < A.length(); ++i) {
        if (A.substr(i, 1) == "0") {
            ++from;
        } else {
            break;
        }
    }
    if (from == A.length()) {
        A = "0";
    } else {
        A = A.substr(from);
    }
}


bool getAB(const string &N, string &A, string &B, int pos, bool is_overflow) {
    if (pos < 0) {
        return true;
    }
    int c = N[pos] - 48; // current digit
    if (is_overflow) c -= 1;
    for (int a = 0; a <= 9; ++a) {  // a digit
        if (a == 4) continue;
        int b = c - a;
        if (b == 4) continue;
        string newA = to_string(a) + A;
        string newB = to_string(b) + B;
        bool is_correct = getAB(N, newA, newB, pos - 1, false);
        if (is_correct) {
            A = newA;
            B = newB;
            return true;
        }
    }
    for (int a = 0; a <= 9; ++a) {  // a digit
        if (a == 4) continue;
        int b = 10 + c - a;
        if (b == 4 || b > 9) continue;
        string newA = to_string(a) + A;
        string newB = to_string(b) + B;
        bool is_correct = getAB(N, newA, newB, pos - 1, true);
        if (is_correct) {
            A = newA;
            B = newB;
            return true;
        }
    }
}


int mainP1() {
    int n = 1;
    // cin >> n;
    for (int i = 1; i <= n; ++i) {
        int N = 434;
        // cin >> N;
        string A = "";
        string B = "";
        string Ns = to_string(N);
        getAB(Ns, A, B, Ns.length() - 1, false);
        removeZeros(A);
        removeZeros(B);
        cout << "Case #" << i << ": " << A << " " << B << endl;
    }
}

bool getPath(int N, bool **ary, string &S, int h, int w) {
    bool result;
    string newS;
    if (h == N - 1 && w == N - 1) {
        return true;
    }
    if (h < N - 1) {
        if (ary[h][w] == false || ary[h + 1][w] == false) {
            newS = S + "S";
            result = getPath(N, ary, newS, h + 1, w);
            if (result == true) {
                S = newS;
                return true;
            }
        }
    }
    if (w < N - 1) {
        if (ary[h][w] == false || ary[h][w + 1] == false) {
            newS = S + "E";
            result = getPath(N, ary, newS, h, w + 1);
            if (result == true) {
                S = newS;
                return true;
            }
        }
    }
    return false;
}


bool getPath2(int N, bool **ary, string &S, int h, int w) {
    bool result;
    string newS;

    if (w == N - 1 && h + 1 == N - 1) {
        S += "S";
        return true;
    }
    if (h == N - 1 && w + 1 == N - 1) {
        S += "E";
        return true;
    }
    if (h + 1 < N && ary[h + 1][w] == true) {
        if (w + 1 < N && ary[h+1][w+1] == true) {
            newS = S + "E";
            result = getPath2(N, ary, newS, h, w+1);
            if (result == true) {
                S = newS;
                return true;
            }
            if (h + 2 < N && ary[h + 2][w] == false) {  // cross south
                newS = S + "SS";
                result = getPath2(N, ary, newS, h+2, w);
                if (result == true) {
                    S = newS;
                    return true;
                }
            }
        }
        if (w + 1 < N) {
            newS = S + "SE";
            result = getPath2(N, ary, newS, h + 1, w + 1);
            if (result == true) {
                S = newS;
                return true;
            }
        }
    }
    if (w + 1 < N && ary[h][w+1] == true) {
        if (h + 1 < N && ary[h+1][w+1] == true) {
            newS = S + "S";
            result = getPath2(N, ary, newS, h + 1, w);
            if (result == true) {
                S = newS;
                return true;
            }
            if (w + 2 < N && ary[h][w+2] == false) {  // cross east
                newS = S + "EE";
                result = getPath2(N, ary, newS, h, w+2);
                if (result == true) {
                    S = newS;
                    return true;
                }
            }
        }

        if (h + 1 < N) {
            newS = S + "ES";
            result = getPath2(N, ary, newS, h + 1, w + 1);
            if (result == true) {
                S = newS;
                return true;
            }
        }
    }

    return false;
}


string getPathSolution(int N, string P) {
    string S = "";  // solution
    bool **ary = new bool *[N];
    for (int i = 0; i < N; ++i) {
        ary[i] = new bool[N];
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            ary[i][j] = false;
        }
    }
    ary[0][0] = true;
    int h = 0;
    int w = 0;
    for (int i = 0; i < P.length(); ++i) {
        char d = P[i];
        if (d == 'S') {
            ++h;
        } else {
            ++w;
        }
        ary[h][w] = true;
    }
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) {
            cout << ary[i][j] << " ";
        }
        cout << endl;
    }

    if (P[0] == 'E' && P[1] == 'E') {
        S = "SE";
        getPath2(N, ary, S, 1, 1);
    } else if (P[0] == 'E' && P[1] == 'S') {
        S = "S";
        getPath2(N, ary, S, 1, 0);
    } else if (P[0] == 'S' && P[1] == 'S') {
        S = "ES";
        getPath2(N, ary, S, 1, 1);
    } else if (P[0] == 'S' && P[1] == 'S') {
        S = "E";
        getPath2(N, ary, S, 0, 1);
    }

    for (int i = 0; i < N; ++i) {
        delete[] ary[i];
    }
    delete[] ary;

    return S;
}

int mainP2() {
    int T = 1;
    // cin >> T;
    for (int i = 1; i <= T; ++i) {
        int N = 5;
        // int N = 2;
        // cin >> N;
        string P = "EESSSESE";
        // string P = "SEEESSES";
        // string P = "ES";
        // std::getline(std::cin, P);
        string S = getPathSolution(N, P);
        cout << "Case #" << i << ": " << S << endl;
    }
}


int main() {
    // cout << "algorithms" << std::endl;
    // keep this function call here
    // cout << FirstReverse(gets(stdin));
    // cout << FirstReverse("coderbyte");
    // cout << FirstReverse("adam");
    // cout << KaprekarsConstant(8352);
    // cout << KaprekarsConstant(8730);
    // max_square();
    // cout << endl;
    // cout << CorrectPath("r?d?drdd", 0, 0, 0);

    // string A[] = {"[3, 4]", "[1, 2, 7, 7]"};
    // string A[] = {"[13, 4]", "[1, 2, 3, 6, 14]"};
    // string A[] = {"[50, 9]", "[1, 2, 6, 7]"};
    // string A[] = {"[6, 1]", "[1, 10, 6, 5]"};
    // cout << ScaleBalancing(A);
    // vowels();
    // mainEightQueens();
    // mainClosestEnemyII();
    // mainQuestionMarks();
    // mainMatrixRotation();
    // mainMatrixRotationInput();
    // mainFormingMagicSquares();
    // mainAlice();
    // mainMean();
    // mainInterQuartileRange();
    // std::cout << "e: " << exp(1) << std::endl;
    // mainBinomial();
    // std::cout << poisson(0.88, 0.88) << std::endl;
    // std::cout << poisson(1.55, 1.55) << std::endl;
    // mainPoisson();
    // mainP1();
    mainP2();
    return 0;
}
