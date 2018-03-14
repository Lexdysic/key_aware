#include <key_aware/key_aware.h>
#include <cassert>

int main () {
    key_aware::Trie trie;

    trie.Add("A");
    trie.Add("to");
    trie.Add("tea");
    trie.Add("ted");
    trie.Add("ten");
    trie.Add("i");
    trie.Add("in");
    trie.Add("inn");

    std::set<std::string> set;
    trie.Search("te", &set);
    assert(set.size() == 3);
    assert(set.find("tea") != set.end());
    assert(set.find("ted") != set.end());
    assert(set.find("ten") != set.end());

    return 0;
}