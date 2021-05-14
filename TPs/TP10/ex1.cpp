#include "exercises.h"

#include <vector>
#include <iostream>
#include <fstream>

std::vector<int> computePrefix(std::string pattern) {
    int m = pattern.length();
    std::vector<int> occurences;
    occurences.push_back(-1);
    int k = -1;

    for (int q = 1; q < m; q++) {
        while (k > -1 && pattern[k + 1] != pattern[q]) k = occurences[k];
        if (pattern[k + 1] == pattern[q]) k++;
        occurences.push_back(k);
    }

    return occurences;
}

int kmpMatcher(std::string text, std::string pattern) {
    int n = text.length();
    int m = pattern.length();
    std::vector<int> occurences = computePrefix(pattern);
    int q = -1;
    int counter = 0;

    for (int i = 0; i < n; i++) {
        while (q > -1 && pattern[q + 1] != text[i]) q = occurences[q];
        if (pattern[q + 1] == text[i]) q++;
        if (q == m - 1) {
            counter++;
            q = occurences[q];
        }
    }

    return counter;
}

int numStringMatching(std::string filename, std::string toSearch) {
    std::ifstream istream(filename);
    if (!istream.is_open()) {
        std::cerr << "Failed to open the file.\n";
        return -1;
    }

    int counter = 0;
    std::string text;
    while (getline(istream, text, '\n')) {
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