#include <key_aware/key_aware.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>
#include <algorithm>

// https://en.wikipedia.org/wiki/Levenshtein_distance
int32_t LevenshteinDistance (const char * s, int32_t len_s, const char * t, int32_t len_t) {
    // create two work vectors of integer distances
    int32_t v0[128];
    int32_t v1[128];

    // initialize v0 (the previous row of distances)
    // this row is A[0][i]: edit distance for an empty s
    // the distance is just the number of characters to delete from t
    for (int32_t i = 0; i <= len_s; ++i)
        v0[i] = i * 2;

    for (int32_t i = 0; i < len_t; ++i) {
        // calculate v1 (current row distances) from the previous row v0

        // first element of v1 is A[i+1][0]
        //   edit distance is delete (i+1) chars from s to match empty t
        v1[0] = i + 2;

        // use formula to fill in the rest of the row
        for (int32_t j = 0; j < len_s; ++j) {
            // calculating costs for A[i+1][j+1]
            int32_t deletionCost     = v0[j + 1] + 2;
            int32_t insertionCost    = v1[j] + 2;
            int32_t substitutionCost = (s[i] == t[j]) ? v0[j] : v0[j] + 2;

            v1[j + 1] = std::min({deletionCost, insertionCost, substitutionCost});
        }

        // copy v1 (current row) to v0 (previous row) for next iteration
        std::swap(v0, v1);
    }

    // after the last swap, the results of v1 are now in v0
    return v0[len_s];
}

int32_t KeyGraphDistance (const char * s, int32_t len_s, const char * t, int32_t len_t) {
    return key_aware::Distance(key_aware::StringView(s, len_s), key_aware::StringView(t, len_t));
}

int main () {
    std::vector<std::string> dictionary;
    {
        std::ifstream ifs;
        ifs.open ("dictionary.txt", std::ifstream::in);
    
        std::string str;
        while (ifs >> str) {
            dictionary.emplace_back(std::move(str));
        }

        ifs.close();
    }


    while (true) {
        std::cout << "Search Word: ";

        std::string str;
        if (!(std::cin >> str))
            break;


        struct Best {
            int32_t dist = INT32_MAX;
            std::vector<std::string> words;
        };
        Best bestLevenshtein;
        Best bestKeyGraph;

        using DistanceFunc = decltype(LevenshteinDistance) *;
        auto runBest = [](DistanceFunc func, const std::string & str, const std::string & word, Best * best) {
            const int32_t dist = func(str.c_str(), (int32_t)str.length(), word.c_str(), (int32_t)word.length());
            if (dist < best->dist) {
                best->words.clear();
                best->dist = dist;
            }

            if (dist <= best->dist) {
                best->words.emplace_back(word);
            }
        };

        for (const auto & word : dictionary) {
            runBest(LevenshteinDistance, str, word, &bestLevenshtein);
            runBest(KeyGraphDistance,    str, word, &bestKeyGraph);
        }

        auto printList = [](const std::vector<std::string> & words) {
            bool tail = false;
            for (const auto & word : words) {
                if (tail)
                    std::cout << ", ";
                std::cout << word; 
                tail = true;
            }
            std::cout << std::endl;
        };

        std::cout << "Levenshtein: ";
        printList(bestLevenshtein.words);

        std::cout << "Key-Aware:   ";
        printList(bestKeyGraph.words);

        std::cout << std::endl << std::endl;
    }
}
