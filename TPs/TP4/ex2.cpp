#include "exercises.h"
#include <unordered_map>

bool changeMakingUnlimitedDP(unsigned int C[], unsigned int n, unsigned int T, unsigned int usedCoins[]) {
    std::vector<int> minCoins(T + 1, T + 1);
    minCoins[0] = 0;

    std::vector<std::vector<int>> coinsUsed(T+1, std::vector<int>(n, 0));

    std::fill_n(usedCoins, n, 0);

    for(unsigned j = 1; j <= T; j++){
        for(unsigned i = 0; i < n; i++) {
            if(C[i] > j) continue;
            if (minCoins[j - C[i]] + 1 < minCoins[j]) {
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

    /* the comment below concerns this resolution
    std::fill_n(usedCoins, n, 0);

    //represents the possibilities by using the set of coins correspondent to the iteration
    int minCoinsNeeded[T + 1];
    std::fill_n(minCoinsNeeded, T + 1, T + 1);
    minCoinsNeeded[0] = 0;

    //saves the last coin used to make the k amount
    int coinsUsedLast[T+1];
    std::fill_n(coinsUsedLast, T + 1, 0);

    for (int i = 1; i <= n; i++) {
        for (int k = C[i - 1]; k <= T; k++) {
            if (minCoinsNeeded[k - C[i - 1]] + 1 < minCoinsNeeded[k]) { //in this step we decide whether to use the coin or not
                minCoinsNeeded[k] = 1 + minCoinsNeeded[k - C[i - 1]];
                coinsUsedLast[k] = C[i - 1];
            }
        }
    }

    if(minCoinsNeeded[T] > T) return false;

    std::unordered_map<int, int> mp;
    for (int i = 0; i < n; ++i) {
        mp.insert(std::make_pair(C[i], i));
    }
    for (int i = T; i > 0; i -= coinsUsedLast[i]) {
        usedCoins[mp.at(coinsUsedLast[i])]++;
    }

    return true;
    */
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

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,8,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 0);
    EXPECT_EQ(usedCoins[1], 2);
    EXPECT_EQ(usedCoins[2], 0);

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,7,usedCoins), true);
    EXPECT_EQ(usedCoins[0], 2);
    EXPECT_EQ(usedCoins[1], 0);
    EXPECT_EQ(usedCoins[2], 1);
}

TEST(TP4_Ex2, hasNoChange) {
    unsigned int C[] = {5,10};
    unsigned int n = 2;
    unsigned int usedCoins[2];

    EXPECT_EQ(changeMakingUnlimitedDP(C,n,1,usedCoins), false);
}

/* so, we start by considering not using any of the coins at all
* following that strategy, every index of c would be an infinite number, since to make any amount with no coins, at the limit, we would need an infinite amount of coins
* at the same time, every index of p would be zero since we can consider to be using a special coin of value '0'
*
* so at each iteration, we introduce a new coin to the set of coins we were previously considering
* and we ask ourselves if by using that coin we are decreasing the amount of coins we need, relatively to the amount we would need by not using it
*
* and so, at the very 1st iteration, we are now considering the set of coins to be {1}
* we can immediately realise that, if we decide to use the '1' coin, we now have 1 possibility to make change for every k in [0, T]
* which, guess what, is just by using k '1' coins, for each k
*
* k =  0   1   2   3   4   5   6   -> amount we are considering
* c    0   1   2   3   4   5   6   -> how many coins we need to make change we have if we use the coin we just added to our set
* p    0   1   1   1   1   1   1   -> the coin we used last
*
* at the 2nd iteration, we are now considering the set of coins to be {1, 4}
* if we decide to use the '4' coin, are we able to make change using less coins?
* notice that we just need to start at the k value correspondent to the one of the coin, since we wouldn't ever be able to make a change equal to 2 using a '4' coin
* for example, notice that, when trying to make a change equal to 4, if we decide to use the '4' coin, we now just need 1 coin,
* which is less 3 coins when comparing to how many we would need if we would just use '1' coins, as we were previously doing
*
* k =  0   1   2   3   4   5   6   -> amount we are considering
* c    0   1   2   3   1   2   3   -> how many coins we need to make change we have if we use the coin we just added to our set
* p    0   1   1   1   4   4   4   -> the coin we used last
*
* and so and so on...
* the idea is that if, for each k in [0, T], we guarantee an optimal solution which mean using the fewest coins possible
* when we arrive at T, in the last iteration, we know for sure that we have a globally optimal solution for that amount
* and then, to know the coins we used, we just need to sort of backtrack
*
* what i mean by that is, for example, to make a change of 6, we will end with a '5' coin at index T of p, which means we used the coin, so let's... use it!
* we now have to make a change of 1, and if we look at index 1 of p, we know that the optimal solution to make change for that amount is by using a '1' coin
* and if we use it, we now have to make a change of 0 and, in this case, we are done!
* but you got the point...
*/