#include "exercises.h"
#include <sstream>

int sumArray(int sequence[], int i, int m) {
    int sum = 0;
    for (int k = i; k < i + m; k++) {
        sum += sequence[k];
    }
    return sum;
}

std::string calcSum(int sequence[], unsigned long n) {
    std::string res;
    std::stringstream sstr(res);

    for (int m = 1; m <= n; m++) {

        std::cout << "subarray of size " << m << "\n\n";
        int minSum = INT_MAX;
        int minSumIndex = 0;

        for (int i = 0; i < n; i++) {
            if (i + m > n) break;

            int sum = sumArray(sequence, i, m);
            if (sum < minSum) {
                minSum = sum;
                minSumIndex = i;
            }
        }
        sstr << minSum << "," << minSumIndex << ";";
    }
    return sstr.str();
}

void testPerformanceCalcSum() {
    //TODO
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex4, CalcSumArrayTest) {
    int sequence[5] = {4,7,2,8,1};
    int sequence2[9] = {6,1,10,3,2,6,7,2,4};

    EXPECT_EQ("1,4;9,1;11,2;18,1;22,0;",calcSum(sequence, 5));
    EXPECT_EQ("1,1;5,3;11,3;16,1;20,3;24,3;31,1;35,1;41,0;",calcSum(sequence2, 9));
	
	testPerformanceCalcSum();
}