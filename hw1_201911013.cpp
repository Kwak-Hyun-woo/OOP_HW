/////////////////////////////////////////////////////////
// SE271 - Assignment 1: Source file
// 0. Rename this file with your ID: "hw1_YOURSTUDENTID.cpp"
// 1. Implement each function 
/////////////////////////////////////////////////////////

#include "hw1.h"
#include <iostream>

int count_odd(const unsigned int* array, int size) {
    int i, num_odd = 0;
    for (i = 0; i < size; i++) {
        if (array[i] % 2 == 1) {
            num_odd += 1;
        }
    }
    return num_odd;
}

int normalize(double* array, int size) {
    double min, max;
    int i = 0, j = 0;

    min = array[0];
    max = array[size - 1];

    for (i = 0; i < size; i++) {
        if (max < array[i]) {
            max = array[i];
        };
        if (min > array[i]) {
            min = array[i];
        };
    }
    

    if (max == min) {
        return 0;

        } else {
        for (j = 0; j < size; j++) {
            array[j] = (array[j] - min) / (max - min);
        }
        return 1;
        }
}

void swap(int* num1, int* num2) {
    int temp{ *num1 };
    *num1 = *num2;
    *num2 = temp;
}

int find_nth(const int* array, int size, int n) {
    if (n > size || n <= 0) {
        return 0;
    }
    int i=0, j;

    int max = array[0];
    int *sorted_arr = new int[size];

    while (i < size) {
        sorted_arr[i] = array[i];
        i += 1;
    }
    

    for (i = 0; i < size - 1; i++) { 
        for (j = i + 1; j < size; j++) {
            if (sorted_arr[i] < sorted_arr[j]) { 
                swap(&sorted_arr[i], &sorted_arr[j]); 
            } 
        } 
    }

    return sorted_arr[n-1];
}

int count_pattern(const char *str, const char * pattern) {
    int i, j = 0,check = 0, cnt_num = 0, N = strlen(str), M = strlen(pattern);

    for (i = 0; i < N; i++) {
        check = 0;

        for (j = 0; j < M; j++) {
            if ((i + j) < N && pattern[j] == str[i+j]) {
                check += 1;
            }
        }

        if (check == M) {
            cnt_num += 1;
        }

    }
    return cnt_num;
}

char* create_shortest_palindrome(const char *src, char* dst) {
    int i,j, N = strlen(src);
    int repeat_num;
    char *inversed_src = new char [N];
    char* src_copied = new char[N];

    for (i = 0; i < N; i++) {
        inversed_src[i] = src[N - 1 - i];
    }
    for (i = 0; i < N; i++) {
        src_copied[i] = src[i];
    }

    for (i = 0; i < N; i++) {
        repeat_num = 0;
        for (j = 0; j < N; j++) {
            if (inversed_src[j] == src[i + j]) {
                repeat_num += 1;
            }
            else {
                break;
            }
        }
        if (repeat_num == N - i) {
            break;
        }
    }


    int M = N - repeat_num;

    
    for (i = 0; i < N; i++) {
        dst[i] = src[i];
    }
    if (N != 0) {
        for (j = 0; j < M; j++) {
            dst[N + j] = inversed_src[repeat_num + j];
        }
    }
    dst[N + M] = 0;
    return dst;
}

#ifdef SE271_HW1
int main() {
    using std::cout;
    using std::endl;

    // Problem 1
    unsigned int a[] = { 0, 1, 2, 3, 5 };
    std::size_t size_a = sizeof(a) / sizeof(int);
    cout << "Problem 1: " << count_odd(a, (int)size_a) << endl;

    // Problem 2
    double b[] = { 1, 2, 2, 3, 2 };
    std::size_t size_b = sizeof(b) / sizeof(double);
    normalize(b, (int)size_b);
    cout << "Problem 2: ";
    for (unsigned int i = 0; i < size_b; ++i) {
        cout << b[i] << " ";
    }
    cout << endl;

    // Problem 3
    int c[] = { 1, 5, 3, 2, 4 };
    cout << "Problem 3: " << find_nth(c, sizeof(c) / sizeof(int), 3) << endl;

    // Problem 4
    cout << "Problem 4: ex1) " << count_pattern("AABBBBAA", "AA") << endl;
    cout << "Problem 4: ex2) " << count_pattern("AABBBBAA", "BB") << endl;


    // Problem 5
    char d[100] = { 0 };
    cout << "Problem 5: ex1) " << create_shortest_palindrome("ABCD", d) << endl;
    cout << "Problem 5: ex2) " << create_shortest_palindrome("AABBCC", d) << endl;

    return 0;

}
#endif
