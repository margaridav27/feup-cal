// By: Gonçalo Leão

#include "exercises.h"
#include <algorithm>

bool Activity::operator==(const Activity &a2) const {
    return start == a2.start && finish == a2.finish;
}

bool Activity::operator<(const Activity &a2) const {
    return finish < a2.finish;
}

std::vector<Activity> earliestFinishScheduling(std::vector<Activity> A) {
    sort(A.begin(), A.end()); //sorting the vector accordingly to the priority criterion

    std::vector<Activity> res;
    std::vector<Activity> toEliminate;
    std::vector<Activity>::iterator i = A.begin(), j;

    while(!A.empty()) {
        res.push_back(*i);
        toEliminate.push_back(*i);

        j = i; j++;
        if (j == A.end()) break;
        while(j != A.end()) {
            if (j->start < i->finish) toEliminate.push_back(*j);
            j++;
        }

        for (auto inv = toEliminate.begin(); inv != toEliminate.end(); inv++) {
            for (auto act = A.begin(); act != A.end(); act++) {
                if (*act == *inv) {
                    A.erase(act);
                    break;
                }
            }
        }

        toEliminate.empty();
    }

    return res;
}

/// TESTS ///
#include <gtest/gtest.h>
#include <gmock/gmock.h>

TEST(TP1_Ex6, activityScheduling) {
    std::vector<Activity> A = {{10,20}, {30, 35}, {5, 15}, {10, 40}, {40, 50}};
    std::vector<Activity> V = earliestFinishScheduling(A);
    EXPECT_EQ(V.size(), 3 );
    ASSERT_THAT(earliestFinishScheduling(A),  ::testing::ElementsAre(Activity(5, 15), Activity(30, 35), Activity(40, 50)));
}