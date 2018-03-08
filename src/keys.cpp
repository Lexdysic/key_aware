#include <key_aware/key_aware.h>

#include "keys.h"

#include <unordered_map>

namespace key_aware {

#if _WIN32

#define NOMINMAX
#include <Windows.h>

#define KEY_PAIRS \
		PAIR(Escape, VK_ESCAPE) \
		PAIR(F1, VK_F1) \
		PAIR(F2, VK_F2) \
		PAIR(F3, VK_F3) \
		PAIR(F4, VK_F4) \
		PAIR(F5, VK_F5) \
		PAIR(F6, VK_F6) \
		PAIR(F7, VK_F7) \
		PAIR(F8, VK_F8) \
		PAIR(F9, VK_F9) \
		PAIR(F10, VK_F10) \
		PAIR(F11, VK_F11) \
		PAIR(F12, VK_F12) \
		PAIR(PrintScreen, VK_SNAPSHOT) \
		PAIR(ScrollLock, VK_SCROLL) \
		PAIR(Break, VK_PAUSE) \
		\
		PAIR(Tilde, VK_OEM_3) \
		PAIR(Num1, '1') \
		PAIR(Num2, '2') \
		PAIR(Num3, '3') \
		PAIR(Num4, '4') \
		PAIR(Num5, '5') \
		PAIR(Num6, '6') \
		PAIR(Num7, '7') \
		PAIR(Num8, '8') \
		PAIR(Num9, '9') \
		PAIR(Num0, '0') \
		PAIR(Minus, VK_OEM_MINUS) \
		PAIR(Equal, VK_OEM_PLUS) \
		PAIR(Backspace, VK_BACK) \
		PAIR(Insert, VK_INSERT) \
		PAIR(Home, VK_HOME) \
		PAIR(PageUp, VK_PRIOR) \
		\
		PAIR(Tab, VK_TAB) \
		PAIR(Q, 'Q') \
		PAIR(W, 'W') \
		PAIR(E, 'E') \
		PAIR(R, 'R') \
		PAIR(T, 'T') \
		PAIR(Y, 'Y') \
		PAIR(U, 'U') \
		PAIR(I, 'I') \
		PAIR(O, 'O') \
		PAIR(P, 'P') \
		PAIR(LeftBracket, VK_OEM_4) \
		PAIR(RightBracket, VK_OEM_6) \
		PAIR(BackSlash, VK_OEM_5) \
		PAIR(Delete, VK_DELETE) \
		PAIR(End, VK_END) \
		PAIR(PageDown, VK_NEXT) \
		\
		PAIR(CapsLock, VK_CAPITAL) \
		PAIR(A, 'A') \
		PAIR(S, 'S') \
		PAIR(D, 'D') \
		PAIR(F, 'F') \
		PAIR(G, 'G') \
		PAIR(H, 'H') \
		PAIR(J, 'J') \
		PAIR(K, 'K') \
		PAIR(L, 'L') \
		PAIR(Semicolon, VK_OEM_1) \
		PAIR(Quote, VK_OEM_7) \
		PAIR(Enter, VK_RETURN) \
		\
		PAIR(LeftShift, VK_LSHIFT) \
		PAIR(Z, 'Z') \
		PAIR(X, 'X') \
		PAIR(C, 'C') \
		PAIR(V, 'V') \
		PAIR(B, 'B') \
		PAIR(N, 'N') \
		PAIR(M, 'M') \
		PAIR(Comma, VK_OEM_COMMA) \
		PAIR(Period, VK_OEM_PERIOD) \
		PAIR(ForwardSlash, VK_OEM_2) \
		PAIR(RightShift, VK_RSHIFT) \
		\
		PAIR(LeftControl, VK_LCONTROL) \
		PAIR(LeftWindows, VK_LWIN) \
		PAIR(LeftAlt, VK_LMENU) \
		PAIR(Space, VK_SPACE) \
		PAIR(RightAlt, VK_RMENU) \
		PAIR(RightWindows, VK_RWIN) \
		PAIR(Menu, VK_APPS) \
		PAIR(RightControl, VK_RCONTROL) \

const std::unordered_map<Key, int> s_keyToVk = {
#define PAIR(key, vk) { Key::key, vk },
	KEY_PAIRS
#undef PAIR
};

const std::unordered_map<int, Key> s_vkToKey = {
#define PAIR(key, vk) { vk, Key::key },
	KEY_PAIRS
#undef PAIR
};
#endif // _WIN32

char32_t KeyCodeToChar (KeyCode keyCode) {
	(void)keyCode;
	return 0;
}

KeyCode CharToKeyCode (char32_t ch) {
	(void)ch;
	return KeyCode{};
}

} // namespace key_aware