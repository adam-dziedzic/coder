#include <iostream>
#include <algorithm>
#include <iterator>

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

int main() {

    // keep this function call here
    // cout << FirstReverse(gets(stdin));
    // cout << FirstReverse("coderbyte");
    // cout << FirstReverse("adam");
    // cout << KaprekarsConstant(8352);
    // cout << KaprekarsConstant(8730);
    max_square();
    cout << endl;
    cout << CorrectPath("r?d?drdd", 0, 0, 0);
    return 0;

}
