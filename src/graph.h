#include <map>
#include <set>

#include "keys.h"

namespace key_aware {

using KeySet  = std::set<Key>;
using CharSet = std::set<char32_t>;

using KeyMapping  = std::map<Key, KeySet>;
using CharMapping = std::map<char32_t, CharSet>;

class KeyGraph {
public:
    KeyGraph(std::initializer_list<KeyMapping::value_type> && list);

    KeySet  Neighbors (Key key);
    CharSet Neighbors (char32_t ch);

private:
    CharSet ComputeNeighbors(char32_t ch);
    CharSet Convert(Key key);

    KeyMapping  m_keyMapping;  // from each key to neighbor key
    CharMapping m_charMapping; // from each char to each neighbor char
};

} // namespace key_aware