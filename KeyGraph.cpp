
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <set>
#include <cctype>
#include <cstdio>
#include <locale>
#include <codecvt>
#include <algorithm>


//
// CONSTANTS
//
enum class Key;

#ifdef _WIN32
#define NOMINMAX
#include <Windows.h>
#include <io.h>
#include <fcntl.h>

enum class Key {
    None            = 0,

    Escape          = VK_ESCAPE,
    F1              = VK_F1,
    F2              = VK_F2,
    F3              = VK_F3,
    F4              = VK_F4,
    F5              = VK_F5,
    F6              = VK_F6,
    F7              = VK_F7,
    F8              = VK_F8,
    F9              = VK_F9,
    F10             = VK_F10,
    F11             = VK_F11,
    F12             = VK_F12,
    PrintScreen     = VK_SNAPSHOT,
    ScrollLock      = VK_SCROLL,
    Break           = VK_PAUSE,

    Tilde           = VK_OEM_3,
    Num1            = '1',
    Num2            = '2',
    Num3            = '3',
    Num4            = '4',
    Num5            = '5',
    Num6            = '6',
    Num7            = '7',
    Num8            = '8',
    Num9            = '9',
    Num0            = '0',
    Minus           = VK_OEM_MINUS,
    Equal           = VK_OEM_PLUS,
    Backspace       = VK_BACK,
    Insert          = VK_INSERT,
    Home            = VK_HOME,
    PageUp          = VK_PRIOR,

    Tab             = VK_TAB,
    Q               = 'Q',
    W               = 'W',
    E               = 'E',
    R               = 'R',
    T               = 'T',
    Y               = 'Y',
    U               = 'U',
    I               = 'I',
    O               = 'O',
    P               = 'P',
    LeftBracket     = VK_OEM_4,
    RightBracket    = VK_OEM_6,
    BackSlash       = VK_OEM_5,
    Delete          = VK_DELETE,
    End             = VK_END,
    PageDown        = VK_NEXT,

    CapsLock        = VK_CAPITAL,
    A               = 'A',
    S               = 'S',
    D               = 'D',
    F               = 'F',
    G               = 'G',
    H               = 'H',
    J               = 'J',
    K               = 'K',
    L               = 'L',
    Semicolon       = VK_OEM_1,
    Quote           = VK_OEM_7,
    Enter           = VK_RETURN,

    LeftShift       = VK_LSHIFT,
    Z               = 'Z',
    X               = 'X',
    C               = 'C',
    V               = 'V',
    B               = 'B',
    N               = 'N',
    M               = 'M',
    Comma           = VK_OEM_COMMA,
    Period          = VK_OEM_PERIOD,
    ForwardSlash    = VK_OEM_2,
    RightShift      = VK_RSHIFT,

    LeftControl     = VK_LCONTROL,
    LeftWindows     = VK_LWIN,
    LeftAlt         = VK_LMENU,
    Space           = VK_SPACE,
    RightAlt        = VK_RMENU,
    RightWindows    = VK_RWIN,
    Menu            = VK_APPS,
    RightControl    = VK_RCONTROL,

};
#endif

enum MetaMask {
    kMetaNone    = 0x0,
    kMetaShift   = 0x1,
    kMetaCtrl    = 0x2,
    kMetaAlt     = 0x4,
    kMetaHankaku = 0x8,
    kMetaTerm    = 0x16,
};

struct KeyCode {
    Key        key  = Key::None;
    MetaMask   meta = kMetaNone;
};

//
// HELPERS
//

static HKL s_hCurrentKL = GetKeyboardLayout(0);
static HKL s_hKeyboardLayout = LoadKeyboardLayoutW(L"", 0);
//MAKELCID(LANG_SWEDISH, SUBLANG_SWEDISH);
//LANG_SWEDISH SUBLANG_SWEDISH
KeyCode CharToKeyCode (char32_t ch) {
    KeyCode keyCode;

    SHORT vkScan = VkKeyScanExW(WCHAR(ch), s_hCurrentKL);
    keyCode.key  = Key(LOBYTE(vkScan));
    keyCode.meta = MetaMask(HIBYTE(vkScan));

    return keyCode;
}

char32_t KeyCodeToChar (KeyCode keyCode) {
    BYTE keyState[256] = {};
    keyState[VK_SHIFT]   = (keyCode.meta & kMetaShift) ? 0xff : 0;
    keyState[VK_CONTROL] = (keyCode.meta & kMetaCtrl) ? 0xff : 0;
    keyState[VK_MENU]    = (keyCode.meta & kMetaAlt) ? 0xff : 0;

    WCHAR buffer[8];
    int rv = ToUnicode(UINT(keyCode.key), 0, keyState, buffer, 8, 0);
    if (rv == 1) {
        return buffer[0];
    }
    else {
        return 0;
    }
}


//
// KeyGraph
//

using KeySet      = std::set<Key>;
using CharSet     = std::set<char32_t>;
using KeyMapping  = std::map<Key, KeySet>;
using CharMapping = std::map<char32_t, CharSet>;

class KeyGraph {
public:
    KeyGraph (std::initializer_list<KeyMapping::value_type> && list) :
        m_keyMapping(std::move(list))
    {
        for (const auto & kv : m_keyMapping) {
            for (uint8_t meta = 0; meta < kMetaTerm; ++meta) {
                KeyCode keyCode;
                keyCode.key  = kv.first;
                keyCode.meta = MetaMask(meta);

                char32_t ch = KeyCodeToChar(keyCode);
                m_charMapping[ch] = ComputeNeighbors(ch);
            }
        }
    }

    KeySet Neighbors (Key key) {
        KeySet neighbors;

        auto it = m_keyMapping.find(key);
        if (it != m_keyMapping.end()) {
            neighbors = it->second;
        }

        return neighbors;
    }
    
    CharSet Neighbors (char32_t ch) {
        CharSet neighbors;

        auto it = m_charMapping.find(ch);
        if (it != m_charMapping.end()) {
            neighbors = it->second;
        }

        return neighbors;
    }
    
    CharSet ComputeNeighbors (char32_t ch) {
        CharSet neighbors;

        auto addAllMetaVariations = [&neighbors](Key key) {
            for (uint8_t meta = 0; meta < kMetaTerm; ++meta) {
                KeyCode outputKeyCode;
                outputKeyCode.key  = key;
                outputKeyCode.meta = MetaMask(meta);

                const char32_t ch = KeyCodeToChar(outputKeyCode);

                if (ch && !std::iscntrl(ch)) {
                    neighbors.insert(ch);
                }
            }
        };

        KeyCode keycode = CharToKeyCode(ch);
        addAllMetaVariations(keycode.key);

        auto it = m_keyMapping.find(keycode.key);
        if (it != m_keyMapping.end()) {
            for (const Key key : it->second) {
                addAllMetaVariations(key);
            }
        }

        return neighbors;
    }


    CharSet Convert (Key key) {
        CharSet chars;

        auto it = m_keyMapping.find(key);
        if (it != m_keyMapping.end()) {
            for (uint8_t meta = 0; meta < kMetaTerm; ++meta) {
                for (const auto & key : it->second) {
                    KeyCode outputKeyCode;
                    outputKeyCode.key  = key;
                    outputKeyCode.meta = MetaMask(meta);

                    const char32_t ch = KeyCodeToChar(outputKeyCode);

                    if (ch && !std::iscntrl(ch)) {
                        chars.insert(ch);
                    }
                }
            }
        }

        return chars;
    }

private:
    KeyMapping  m_keyMapping;  // from each key to neighbor key
    CharMapping m_charMapping; // from each char to each neighbor char
};


//
// TEST
//

static KeyGraph s_keyGraphUs104 = {
    { Key::Escape,          {} },
    { Key::F1,              { Key::F2 } },
    { Key::F2,              { Key::F1, Key::F3 } },
    { Key::F3,              { Key::F2, Key::F4 } },
    { Key::F4,              { Key::F3 } },
    { Key::F5,              { Key::F6 } },
    { Key::F6,              { Key::F5, Key::F7 } },
    { Key::F7,              { Key::F6, Key::F8 } },
    { Key::F8,              { Key::F7 } },
    { Key::F9,              { Key::F10 } },
    { Key::F10,             { Key::F9, Key::F11 } },
    { Key::F11,             { Key::F10, Key::F12 } },
    { Key::F12,             { Key::F11 } },
    { Key::PrintScreen,     { Key::ScrollLock } },
    { Key::ScrollLock,      { Key::PrintScreen, Key::Break } },
    { Key::Break,           { Key::ScrollLock } },

    { Key::Tilde,           { Key::Num1, Key::Tab } },
    { Key::Num1,            { Key::Tilde, Key::Num2, Key::Tab, Key::Q } },
    { Key::Num2,            { Key::Num1, Key::Num3, Key::Q, Key::W } },
    { Key::Num3,            { Key::Num2, Key::Num4, Key::W, Key::E } },
    { Key::Num4,            { Key::Num3, Key::Num5, Key::E, Key::R } },
    { Key::Num5,            { Key::Num4, Key::Num6, Key::R, Key::T } },
    { Key::Num6,            { Key::Num5, Key::Num7, Key::T, Key::Y } },
    { Key::Num7,            { Key::Num6, Key::Num8, Key::Y, Key::U } },
    { Key::Num8,            { Key::Num7, Key::Num9, Key::U, Key::I } },
    { Key::Num9,            { Key::Num8, Key::Num0, Key::I, Key::O } },
    { Key::Num0,            { Key::Num9, Key::Minus, Key::O, Key::P } },
    { Key::Minus,           { Key::Num0, Key::Equal, Key::P, Key::LeftBracket } },
    { Key::Equal,           { Key::Minus, Key::Backspace, Key::LeftBracket, Key::RightBracket } },
    { Key::Backspace,       { Key::Equal, Key::RightBracket, Key::BackSlash } },

    { Key::Tab,             { Key::Tilde, Key::Num1, Key::Q, Key::CapsLock } },
    { Key::Q,               { Key::Num1, Key::Num2, Key::Tab, Key::W, Key::CapsLock, Key::A } },
    { Key::W,               { Key::Num2, Key::Num3, Key::Q, Key::E, Key::A, Key::S } },
    { Key::E,               { Key::Num3, Key::Num4, Key::W, Key::R, Key::S, Key::D } },
    { Key::R,               { Key::Num4, Key::Num5, Key::E, Key::T, Key::D, Key::F } },
    { Key::T,               { Key::Num5, Key::Num6, Key::R, Key::Y, Key::F, Key::G } },
    { Key::Y,               { Key::Num6, Key::Num7, Key::T, Key::U, Key::G, Key::H } },
    { Key::U,               { Key::Num7, Key::Num8, Key::Y, Key::I, Key::H, Key::J } },
    { Key::I,               { Key::Num8, Key::Num9, Key::U, Key::O, Key::J, Key::K } },
    { Key::O,               { Key::Num9, Key::Num0, Key::I, Key::P, Key::K, Key::L } },
    { Key::P,               { Key::Num0, Key::Minus, Key::O, Key::LeftBracket, Key::L, Key::Semicolon } },
    { Key::LeftBracket,     { Key::Minus, Key::Equal, Key::P, Key::RightBracket, Key::Semicolon, Key::Quote } },
    { Key::RightBracket,    { Key::Equal, Key::Backspace, Key::LeftBracket, Key::BackSlash, Key::Quote, Key::Enter } },
    { Key::BackSlash,       { Key::Backspace, Key::RightBracket, Key::Enter } },

    { Key::CapsLock,        { Key::Tab, Key::A, Key::LeftShift } },
    { Key::A,               { Key::Q, Key::W, Key::CapsLock, Key::S, Key::LeftShift, Key::Z } },
    { Key::S,               { Key::W, Key::E, Key::A, Key::D, Key::Z, Key::X } },
    { Key::D,               { Key::E, Key::R, Key::S, Key::F, Key::X, Key::C } },
    { Key::F,               { Key::R, Key::T, Key::D, Key::G, Key::C, Key::V } },
    { Key::G,               { Key::T, Key::Y, Key::F, Key::H, Key::V, Key::B } },
    { Key::H,               { Key::Y, Key::U, Key::G, Key::J, Key::B, Key::N } },
    { Key::J,               { Key::U, Key::I, Key::H, Key::K, Key::N, Key::M } },
    { Key::K,               { Key::I, Key::O, Key::J, Key::L, Key::M, Key::Comma } },
    { Key::L,               { Key::O, Key::P, Key::K, Key::Semicolon, Key::Comma, Key::Period } },
    { Key::Semicolon,       { Key::P, Key::LeftBracket, Key::L, Key::Quote, Key::Period, Key::ForwardSlash } },
    { Key::Quote,           { Key::LeftBracket, Key::RightBracket, Key::Semicolon, Key::Enter, Key::ForwardSlash, Key::RightShift } },
    { Key::Enter,           { Key::RightBracket, Key::BackSlash, Key::Quote, Key::RightShift } },

    { Key::LeftShift,       { Key::CapsLock, Key::A, Key::Z, Key::LeftControl, Key::LeftWindows } },
    { Key::Z,               { Key::A, Key::S, Key::LeftShift, Key::X, Key::LeftWindows, Key::LeftAlt } },
    { Key::X,               { Key::S, Key::D, Key::Z, Key::C, Key::LeftAlt, Key::Space } },
    { Key::C,               { Key::D, Key::F, Key::X, Key::V, Key::Space } },
    { Key::V,               { Key::F, Key::G, Key::C, Key::B, Key::Space } },
    { Key::B,               { Key::G, Key::H, Key::V, Key::N, Key::Space } },
    { Key::N,               { Key::H, Key::J, Key::B, Key::M, Key::Space } },
    { Key::M,               { Key::J, Key::K, Key::N, Key::Comma, Key::Space } },
    { Key::Comma,           { Key::K, Key::L, Key::M, Key::Period, Key::Space, Key::RightAlt } },
    { Key::Period,          { Key::L, Key::Semicolon, Key::Comma, Key::ForwardSlash, Key::RightAlt, Key::RightWindows } },
    { Key::ForwardSlash,    { Key::Semicolon, Key::Quote, Key::Period, Key::RightShift, Key::RightAlt, Key::RightWindows } },
    { Key::RightShift,      { Key::Quote, Key::Enter, Key::ForwardSlash, Key::RightWindows, Key::Menu, Key::RightControl } },

    { Key::LeftControl,     { Key::LeftShift, Key::LeftWindows } },
    { Key::LeftWindows,     { Key::LeftShift, Key::Z, Key::LeftControl, Key::LeftAlt } },
    { Key::LeftAlt,         { Key::Z, Key::X, Key::LeftWindows, Key::Space } },
    { Key::Space,           { Key::X, Key::C, Key::V, Key::B, Key::N, Key::M, Key::Comma, Key::LeftAlt, Key::RightAlt } },
    { Key::RightAlt,        { Key::Comma, Key::Period, Key::Space, Key::RightWindows } },
    { Key::RightWindows,    { Key::Period, Key::ForwardSlash, Key::RightShift, Key::RightAlt, Key::Menu } },
    { Key::Menu,            { Key::RightShift, Key::RightWindows, Key::RightControl } },
    { Key::RightControl,    { Key::RightShift, Key::Menu } },
};

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
            int32_t substitutionCost;
            if (s[i] == t[j]) {
                substitutionCost = v0[j];
            }
            else {
                CharSet neighbors = s_keyGraphUs104.Neighbors(char32_t(s[i]));
                const bool isNeighbor = neighbors.find(t[j]) != neighbors.end();
                substitutionCost = v0[j] + (isNeighbor ? 1 : 2);
            }

            v1[j + 1] = std::min({deletionCost, insertionCost, substitutionCost});
        }

        // copy v1 (current row) to v0 (previous row) for next iteration
        std::swap(v0, v1);
    }

    // after the last swap, the results of v1 are now in v0
    return v0[len_s];
}

int main () {
    std::cout << "Loading Dictionary..." << std::endl;
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
    std::cout << "...Done." << std::endl;


    std::string str;
    while (std::cin >> str) {
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

        std::cout << "Levenshtein: ";
        for (const auto & word : bestLevenshtein.words) {
            std::cout << word << ", ";
        }
        std::cout << std::endl;

        std::cout << "KeyGraph:    ";
        for (const auto & word : bestKeyGraph.words) {
            std::cout << word << ", ";
        }
        std::cout << std::endl;
    }
}
