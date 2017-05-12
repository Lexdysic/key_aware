#include <Windows.h>
#include <map>
#include <vector>
#include <iostream>
#include <set>
#include <cctype>
#include <cstdio>


class Key {
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

    None = 0
};

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

using KeyMapping = std::map<Key, std::vector<Key>>;

static KeyMapping s_keyGraphUs104 = {
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

KeyCode CharToKeyCode (char32_t ch) {
    KeyCode keyCode;

    SHORT vkScan = VkKeyScanW(WCHAR(ch));
    keyCode.key  = Key(LOBYTE(vkScan));
    keyCode.meta = MetaMask(HIBYTE(vkScan));

    return keyCode;
}

char32_t KeyCodeToChar (KeyCode keyCode) {
    BYTE keyState[256] = {};
    keyState[VK_SHIFT] = (keyCode.meta & kMetaShift) ? 0xff : 0;
    keyState[VK_CONTROL] = (keyCode.meta & kMetaCtrl) ? 0xff : 0;
    keyState[VK_MENU] = (keyCode.meta & kMetaAlt) ? 0xff : 0;

    WCHAR buffer[8];
    int rv = ToUnicode(UINT(keyCode.key), 0, keyState, buffer, 8, 0);
    if (rv == 1) {
        return buffer[0];
    }
    else {
        return 0;
    }
}

int main () {
    char ch;

    while (std::cin >> ch) {
        KeyCode inputKeyCode = CharToKeyCode(ch);

        std::set<char32_t> neighbors;

        auto it = s_keyGraphUs104.find(inputKeyCode.key);
        if (it != s_keyGraphUs104.end()) {
            for (uint8_t meta = 0; meta < kMetaTerm; ++meta) {
                for (const auto & key : it->second) {
                    KeyCode outputKeyCode;
                    outputKeyCode.key = key;
                    outputKeyCode.meta = MetaMask(meta);

                    const char32_t ch = KeyCodeToChar(outputKeyCode);

                    if (ch && !std::iscntrl(ch)) {
                        neighbors.insert(ch);
                    }
                }
            }
        }

        if (neighbors.empty()) {
            std::cout << "No mappings";
        }
        else {
            for (char32_t ch : neighbors) {
                std::cout << (char)ch << " ";
            }
        }

        std::cout << std::endl;
    }
}
