#include <algorithm>
#include "exercises.h"
#include "limits.h"

// https://edutechlearners.com/download/Introduction_to_algorithms-3rd%20Edition.pdf
// see chapter 4 section 4.1 - pages 70-72, thank me later
// also see tuple implementation on exercises.h

int maxSubsequenceDC(int A[], unsigned int n, int &i, int &j) {
    i = 0; j = (int)n-1;

    tuple result = maxSubsequenceRec(A, i, j);

    i = result.left; j = result.right;

	return result.maxSum;
}

tuple maxCrossingSubsequence(int A[], int low, int mid, int high) {
    int sum = 0;
    int maxLeftSum = INT_MIN;
    int maxLeft = mid;
    for (int a = mid; a >= low; --a){
        sum += A[a];
        if (sum > maxLeftSum){
            maxLeftSum = sum;
            maxLeft = a;
        }
    }

    sum = 0;
    int maxRightSum = INT_MIN;
    int maxRight = mid + 1;
    for (int b = mid + 1; b <= high; ++b){
        sum += A[b];
        if (sum > maxRightSum){
            maxRightSum = sum;
            maxRight = b;
        }
    }

    tuple result = { .left = maxLeft, .right = maxRight, .maxSum = maxLeftSum + maxRightSum };
    return result;
}

tuple maxSubsequenceRec(int A[], int low, int high) {
    if (low == high) {
        tuple result = { .left = low, .right = high, .maxSum = A[low] };
        return result;
    } else {
        int mid = (low + high) / 2;
        tuple left = maxSubsequenceRec(A, low, mid);
        tuple right = maxSubsequenceRec(A, mid + 1, high);
        tuple cross = maxCrossingSubsequence(A, low, mid, high);

        if (left.maxSum >= right.maxSum && left.maxSum >= cross.maxSum) {
            return left;
        } else if (right.maxSum >= left.maxSum && right.maxSum >= cross.maxSum) {
            return right;
        } else {
            return cross;
        }
    }
}

/// TESTS ///
/*
#include <gtest/gtest.h>

TEST(TP3_Ex2, testMaxSubsequence) {
    int A1[] = {1, 2, 3, 4};
    unsigned int n1 = 4;
    int i, j;
    EXPECT_EQ(maxSubsequenceDC(A1,n1,i,j), 10);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A2[] = {2, -1, -3, 4};
    unsigned int n2 = 4;
    EXPECT_EQ(maxSubsequenceDC(A2,n2,i,j), 4);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 3);

    int A3[] = {2, -1, 3, 4};
    unsigned int n3 = 4;
    EXPECT_EQ(maxSubsequenceDC(A3,n3,i,j), 8);
    EXPECT_EQ(i, 0);
    EXPECT_EQ(j, 3);

    int A4[] = {-2, 1, -3, 4, -1, 2, 1, -5, 4};
    unsigned int n4 = 9;
    EXPECT_EQ(maxSubsequenceDC(A4,n4,i,j), 6);
    EXPECT_EQ(i, 3);
    EXPECT_EQ(j, 6);
}
*/