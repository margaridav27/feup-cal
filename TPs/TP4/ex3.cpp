#include "exercises.h"
#include <unordered_map>

bool changeMakingDP(unsigned int C[], unsigned int Stock[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    std::vector<int> minCoins(T + 1, T + 1);
    minCoins[0] = 0;

    std::vector<std::vector<int>> coinsUsed(T+1, std::vector<int>(n, 0));

    std::fill_n(usedCoins, n, 0);

    for(unsigned j = 1; j <= T; j++){
        for(unsigned i = 0; i < n; i++) {
            if(C[i] > j) continue;
            if (minCoins[j - C[i]] + 1 < minCoins[j] && !(coinsUsed[j - C[i]][i] + 1 > Stock[i])) {
                minCoins[j] = minCoins[j - C[i]] + 1;
                coinsUsed[j] = coinsUsed[j - C[i]]; //this assignment is allowed only if using vectors
                coinsUsed[j][i]++;
            }
        }
    }

    unsigned sum = 0;
    for(int i = 0; i < n; i++){
        usedCoins[i] = coinsUsed[T][i];
        sum += C[i]*usedCoins[i];
    }

    return sum == T;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex3, hasChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {1,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingDP(C,Stock,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    unsigned int Stock2[] = {1,2,4,2};
    EXPECT_EQ(changeMakingDP(C,Stock2,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 3);
    EXPECT_EQ(usedCoins[3], 2);

    unsigned int Stock3[] = {10,2,4,2};
    EXPECT_EQ(changeMakingDP(C,Stock3,n,10,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
}

TEST(TP4_Ex3, hasChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int Stock[] = {2,2,1};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingDP(C,Stock,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingDP(C,Stock,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    unsigned int Stock2[] = {8,2,1};
    EXPECT_EQ(changeMakingDP(C,Stock2,n,7,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);

    EXPECT_EQ(changeMakingDP(C,Stock2,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);
}

TEST(TP4_Ex3, hasNoChange) {
    unsigned int C[] = {1,2,5,10};
    unsigned int Stock[] = {0,1,1,1};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingDP(C,Stock,n,18,usedCoins), false);
    EXPECT_EQ(changeMakingDP(C,Stock,n,1,usedCoins), false);
}