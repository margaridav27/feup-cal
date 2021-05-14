#include "exercises.h"

#include <vector>
#include <iostream>
#include <fstream>

std::vector<int> computePrefix(std::string pattern) {
    int m = pattern.length();
    std::vector<int> occurences;
    occurences.at(0) = 0;
    int k = -1;

    for (int i = 1; i < m; ++i) {
        while (k > 0 && pattern.at(k + 1) != pattern.at(i)) k = occurences.at(k);
        if (pattern.at(k + 1) == pattern.at(i)) k++;
        occurences.at(i) = k;
    }

    return occurences;
}

int kmpMatcher(std::string text, std::string pattern) {
    int n = text.length();
    int m = pattern.length();
    std::vector<int> occurences = computePrefix(pattern);
    int q = -1;

    for (int i = 0; i < n; ++i) {
        while (q > 0 && pattern.at(q + 1) != text.at(i)) {
            q = occurences.at(q);
            if (pattern.at(q + 1) == text.at(i)) q++;
            if (q == m) q = occurences.at(q);
        }

    }

    return q;
}

int numStringMatching(const std::string &filename, const std::string &toSearch) {
    std::ifstream istream(filename);
    if (!istream.is_open()) {
        std::cerr << "Failed to open the file.\n";
        return -1;
    }

    int counter = 0;
    std::string text;
    while (!istream.eof()) {
        istream >> text;
        counter += kmpMatcher(text, toSearch);
    }

    istream.close();
    return counter;
}

/// TESTS ///
#include <gtest/gtest.h>

TEST(TP10_Ex1, testKmpMatcher) {
    EXPECT_EQ(3, kmpMatcher("aaabaabaacaabaa", "aabaa"));

    EXPECT_EQ(0, kmpMatcher("", "a"));
    EXPECT_EQ(1, kmpMatcher("a", "a"));
}


#define REL_PATH std::string("../TP10/") // relative path to the tests

TEST(TP10_Ex1, testNumStringMatching) {
    int num1 = numStringMatching(REL_PATH + "text1.txt", "estrutura de dados");
    EXPECT_EQ(3, num1);

    int num2 = numStringMatching(REL_PATH + "text2.txt", "estrutura de dados");
    EXPECT_EQ(2, num2);
}
