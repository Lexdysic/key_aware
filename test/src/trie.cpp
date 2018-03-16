#include <fstream>
#include <string>
#include <catch/catch.hpp>

#include <key_aware/key_aware.h>

TEST_CASE("Small Test", "[trie]") {
    key_aware::Trie trie;

    {
        trie.Add("A");
        trie.Add("to");
        trie.Add("tea");
        trie.Add("ted");
        trie.Add("ten");
        trie.Add("i");
        trie.Add("in");
        trie.Add("inn");
    }

    SECTION("Search for known values") {
        std::set<std::string> set;
        trie.Search("te", &set);

        CHECK(set.size() == 3);
        CHECK(set.find("tea") != set.end());
        CHECK(set.find("ted") != set.end());
        CHECK(set.find("ten") != set.end());
    }

    SECTION("Search for missing values") {
        std::set<std::string> set;
        trie.Search("s", &set);

        CHECK(set.size() == 0);
    }
}

struct BigTestFixture {
    BigTestFixture () {
        std::ifstream ifs;
        ifs.open ("dictionary.txt", std::ifstream::in);

        std::string str;
        while (ifs >> str) {
            trie.Add(key_aware::StringView(str.data(), str.length()));
        }

        ifs.close();
    }

    key_aware::Trie trie;
};

TEST_CASE_METHOD(BigTestFixture, "Big Test", "[trie]") {
    REQUIRE(!trie.IsEmpty());

    SECTION("Search for known values") {
        std::set<std::string> set;
        trie.Search("abstr", &set);

        CHECK(set.size() == 3);
        CHECK(set.find("abstract")    != set.end());
        CHECK(set.find("abstraction") != set.end());
        CHECK(set.find("abstracts")   != set.end());
    }

    SECTION("Search for missing values") {
        std::set<std::string> set;
        trie.Search("zx", &set);

        CHECK(set.size() == 0);
    }
}