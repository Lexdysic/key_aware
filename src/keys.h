
namespace key_aware {

enum class Key {
    None,

    Escape,
    F1,
    F2,
    F3,
    F4,
    F5,
    F6,
    F7,
    F8,
    F9,
    F10,
    F11,
    F12,
    PrintScreen,
    ScrollLock,
    Break,

    Tilde,
    Num1,
    Num2,
    Num3,
    Num4,
    Num5,
    Num6,
    Num7,
    Num8,
    Num9,
    Num0,
    Minus,
    Equal,
    Backspace,
    Insert,
    Home,
    PageUp,

    Tab,
    Q,
    W,
    E,
    R,
    T,
    Y,
    U,
    I,
    O,
    P,
    LeftBracket,
    RightBracket,
    BackSlash,
    Delete,
    End,
    PageDown,

    CapsLock,
    A,
    S,
    D,
    F,
    G,
    H,
    J,
    K,
    L,
    Semicolon,
    Quote,
    Enter,

    LeftShift,
    Z,
    X,
    C,
    V,
    B,
    N,
    M,
    Comma,
    Period,
    ForwardSlash,
    RightShift,

    LeftControl,
    LeftWindows,
    LeftAlt,
    Space,
    RightAlt,
    RightWindows,
    Menu,
    RightControl,
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


char32_t KeyCodeToChar (KeyCode keyCode);
KeyCode CharToKeyCode (char32_t ch);


} // namespace key_aware