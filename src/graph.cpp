#include "graph.h"
#include <key_aware/key_aware.h>

namespace key_aware {

KeyGraph::KeyGraph (std::initializer_list<KeyMapping::value_type> && list) :
    m_keyMapping(std::move(list))
{
    for (const auto & kv : m_keyMapping) {
        for (uint8_t meta = 0; meta < kMetaTerm; ++meta) {
            KeyCode keyCode;
            keyCode.key = kv.first;
            keyCode.meta = MetaMask(meta);

            char32_t ch = KeyCodeToChar(keyCode);
            m_charMapping[ch] = ComputeNeighbors(ch);
        }
    }
}

KeySet KeyGraph::Neighbors (Key key) {
    KeySet neighbors;

    auto it = m_keyMapping.find(key);
    if (it != m_keyMapping.end()) {
        neighbors = it->second;
    }

    return neighbors;
}

CharSet KeyGraph::Neighbors (char32_t ch) {
    CharSet neighbors;

    auto it = m_charMapping.find(ch);
    if (it != m_charMapping.end()) {
        neighbors = it->second;
    }

    return neighbors;
}

CharSet KeyGraph::ComputeNeighbors (char32_t ch) {
    CharSet neighbors;

    auto addAllMetaVariations = [&neighbors](Key key) {
        for (uint8_t meta = 0; meta < kMetaTerm; ++meta) {
            KeyCode outputKeyCode;
            outputKeyCode.key = key;
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

CharSet KeyGraph::Convert (Key key) {
    CharSet chars;

    auto it = m_keyMapping.find(key);
    if (it != m_keyMapping.end()) {
        for (uint8_t meta = 0; meta < kMetaTerm; ++meta) {
            for (const auto & key : it->second) {
                KeyCode outputKeyCode;
                outputKeyCode.key = key;
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

int32_t Distance (const StringView & from, const StringView & to) {
    const size_t maxLen = std::max(from.Length(), to.Length());
    const bool isSmall = maxLen < 128;

    int32_t v0Small[128];
    int32_t v1Small[128];

    int32_t * v0;
    int32_t * v1;
    if (isSmall) {
        v0 = v0Small;
        v1 = v1Small;
    }
    else {
        v0 = new int32_t[maxLen];
        v1 = new int32_t[maxLen];
    }

    // initialize v0 (the previous row of distances)
    // this row is A[0][i]: edit distance for an empty s
    // the distance is just the number of characters to delete from t
    for (int32_t i = 0; i <= from.Length(); ++i) {
        v0[i] = i * 2;
    }

    for (int32_t i = 0; i < to.Length(); ++i) {
        // calculate v1 (current row distances) from the previous row v0

        // first element of v1 is A[i+1][0]
        //   edit distance is delete (i+1) chars from s to match empty t
        v1[0] = i + 2;

        // use formula to fill in the rest of the row
        for (int32_t j = 0; j < from.Length(); ++j) {
            // calculating costs for A[i+1][j+1]
            int32_t deletionCost     = v0[j + 1] + 2;
            int32_t insertionCost    = v1[j] + 2;
            int32_t substitutionCost;
            if (from[i] == to[j]) {
                substitutionCost = v0[j];
            }
            else {
                CharSet neighbors = s_keyGraphUs104.Neighbors(char32_t(from[i]));
                const bool isNeighbor = neighbors.find(to[j]) != neighbors.end();
                substitutionCost = v0[j] + (isNeighbor ? 1 : 2);
            }

            v1[j + 1] = std::min({deletionCost, insertionCost, substitutionCost});
        }

        // copy v1 (current row) to v0 (previous row) for next iteration
        std::swap(v0, v1);
    }

    // after the last swap, the results of v1 are now in v0

    const int32_t distance = v0[from.Length()];

    if (!isSmall) {
        delete[] v0;
        delete[] v1;
    }

    return distance;
}

} // namespace key_aware