#include "exercises.h"

#define INF 1e10

bool changeMakingUnlimitedDP(unsigned int C[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    std::fill_n(usedCoins, n, 0);

    unsigned int v[n + 1];
    v[0] = 0;
    for (int i = 1; i <= n; i++) { v[i] = C[i - 1]; }

    unsigned int nC[n + 1][T + 1];
    nC[0][0] = 0;
    for (int i = 0; i <= n; i++) { nC[i][0] = 0; }
    for (int k = 1; k <= T; k++) { nC[0][k] = T + 1; }

    unsigned int P[n + 1][T + 1];
    for (int i = 0; i <= n; i++) { nC[i][0] = 0; }
    for (int k = 1; k <= T; k++) { nC[0][k] = 0; }

    for (int i = 1; i <= n; i++) {
        for (int k = 1; k <= v[i] - 1; k++) {
            nC[i][k] = nC[i - 1][k];
            P[i][k] = P[i - 1][k];
        }
    }

    for (int i = 1; i <= n; i++) {
        for (int k = v[i]; k <= T; k++) {
            if (nC[i - 1][k] < 1 + nC[i][k - v[i]]) {
                P[i][k] = P[i - 1][k];
            } else {
                P[i][k] = i;
            }
            //nC[i][k] = std::min(nC[i - 1][k], 1 + nC[i][k - v[i]]);
        }
    }

    /*
    for (int i = 1; i <= n; i++) {
        for (int k = v[i] - 1; k <= T; k++) {
            if (1 + nC[k - v[i - 1]] < nC[k]) {
                nC[k] = 1 + nC[k - v[i - 1]];
                P[k] = i;
            }
        }
    }

      if (nC[T] == T + 1) return false;
      else {
        for (int k = T; k > 0; k -= v[P[k] - 1]) {
            std::cout << "used: " << v[P[k] - 1] << "\t";
        } std::cout << "\n";

        for (int k = T; k > 0; k = k - v[P[k] - 1]) {
            for (int c = 0; c < n; c++) {
                if (C[c] == v[P[k] - 1]) {
                    usedCoins[c]++;
                }
            }
        }

      }*/
    return true;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP4_Ex2, hasChangeCanonical) {
    unsigned int C[] = {1,2,5,10};
    unsigned int n = 4;
    unsigned int usedCoins[4];

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,13,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,38,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 1);
    EXPECT_EQ(usedCoins[2], 1);
    EXPECT_EQ(usedCoins[3], 3);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,10,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 0);
    EXPECT_EQ(usedCoins[3], 1);
}

TEST(TP4_Ex2, hasChangeNonCanonical) {
    unsigned int C[] = {1,4,5};
    unsigned int n = 3;
    unsigned int usedCoins[3];

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,6,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 1);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);
/*
    EXPECT_EQ(changeMakingUnlimitedDP(C,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,7,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);*/
}

TEST(TP4_Ex2, hasNoChange) {
    unsigned int C[] = {5,10};
    unsigned int n = 2;
    unsigned int usedCoins[2];

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,1,usedCoins), false);
}