// By: Gonçalo Leão

#include "exercises.h"

int maxSubsequence(int A[], unsigned int n, unsigned int &i, unsigned int &j) {
    int currSum = 0, maxSum = 0;

    for (int size = n - 1; size > 0; size--) {
        for (int a = 0; a + size < n ; a++) {
            for (int b = a; b <= a + size; b++) {
                currSum += A[b];
            }
            if (currSum > maxSum) {
                i = a;
                j = a + size;
                maxSum = currSum;
            }
            currSum = 0;
        }
    }
    return maxSum;
}


/// TESTS ///
/*
#include <gtest/gtest.h>

TEST(TP1_Ex2, maxSubsequence) {
    int A[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n = 9;
    unsigned int i, j;
    EXPECT_EQ(maxSubsequence(A,n,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}
*/