#pragma once

#include <GLFW/glfw3.h>

	static const char* get_key_name(int key)
	{
		switch (key)
		{
			// Printable keys
			case GLFW_KEY_A:            return "a";
			case GLFW_KEY_B:            return "b";
			case GLFW_KEY_C:            return "c";
			case GLFW_KEY_D:            return "d";
			case GLFW_KEY_E:            return "e";
			case GLFW_KEY_F:            return "f";
			case GLFW_KEY_G:            return "g";
			case GLFW_KEY_H:            return "h";
			case GLFW_KEY_I:            return "i";
			case GLFW_KEY_J:            return "j";
			case GLFW_KEY_K:            return "k";
			case GLFW_KEY_L:            return "l";
			case GLFW_KEY_M:            return "m";
			case GLFW_KEY_N:            return "n";
			case GLFW_KEY_O:            return "o";
			case GLFW_KEY_P:            return "p";
			case GLFW_KEY_Q:            return "q";
			case GLFW_KEY_R:            return "r";
			case GLFW_KEY_S:            return "s";
			case GLFW_KEY_T:            return "t";
			case GLFW_KEY_U:            return "u";
			case GLFW_KEY_V:            return "v";
			case GLFW_KEY_W:            return "w";
			case GLFW_KEY_X:            return "x";
			case GLFW_KEY_Y:            return "y";
			case GLFW_KEY_Z:            return "z";
			case GLFW_KEY_1:            return "1";
			case GLFW_KEY_2:            return "2";
			case GLFW_KEY_3:            return "3";
			case GLFW_KEY_4:            return "4";
			case GLFW_KEY_5:            return "5";
			case GLFW_KEY_6:            return "6";
			case GLFW_KEY_7:            return "7";
			case GLFW_KEY_8:            return "8";
			case GLFW_KEY_9:            return "9";
			case GLFW_KEY_0:            return "0";
			case GLFW_KEY_SPACE:        return "space";
			case GLFW_KEY_MINUS:        return "minus";
			case GLFW_KEY_EQUAL:        return "equal";
			case GLFW_KEY_LEFT_BRACKET: return "left bracket";
			case GLFW_KEY_RIGHT_BRACKET: return "right bracket";
			case GLFW_KEY_BACKSLASH:    return "backslash";
			case GLFW_KEY_SEMICOLON:    return "semicolon";
			case GLFW_KEY_APOSTROPHE:   return "apostrophe";
			case GLFW_KEY_GRAVE_ACCENT: return "grave accent";
			case GLFW_KEY_COMMA:        return "comma";
			case GLFW_KEY_PERIOD:       return "period";
			case GLFW_KEY_SLASH:        return "slash";
			case GLFW_KEY_WORLD_1:      return "world 1";
			case GLFW_KEY_WORLD_2:      return "world 2";

			// Function keys
			case GLFW_KEY_ESCAPE:       return "escape";
			case GLFW_KEY_F1:           return "f1";
			case GLFW_KEY_F2:           return "f2";
			case GLFW_KEY_F3:           return "f3";
			case GLFW_KEY_F4:           return "f4";
			case GLFW_KEY_F5:           return "f5";
			case GLFW_KEY_F6:           return "f6";
			case GLFW_KEY_F7:           return "f7";
			case GLFW_KEY_F8:           return "f8";
			case GLFW_KEY_F9:           return "f9";
			case GLFW_KEY_F10:          return "f10";
			case GLFW_KEY_F11:          return "f11";
			case GLFW_KEY_F12:          return "f12";
			case GLFW_KEY_F13:          return "13";
			case GLFW_KEY_F14:          return "f14";
			case GLFW_KEY_F15:          return "f15";
			case GLFW_KEY_F16:          return "f16";
			case GLFW_KEY_F17:          return "f17";
			case GLFW_KEY_F18:          return "f18";
			case GLFW_KEY_F19:          return "f19";
			case GLFW_KEY_F20:          return "f20";
			case GLFW_KEY_F21:          return "f21";
			case GLFW_KEY_F22:          return "f22";
			case GLFW_KEY_F23:          return "f23";
			case GLFW_KEY_F24:          return "f24";
			case GLFW_KEY_F25:          return "f25";
			case GLFW_KEY_UP:           return "up";
			case GLFW_KEY_DOWN:         return "down";
			case GLFW_KEY_LEFT:         return "left";
			case GLFW_KEY_RIGHT:        return "right";
			case GLFW_KEY_LEFT_SHIFT:   return "left shift";
			case GLFW_KEY_RIGHT_SHIFT:  return "right shift";
			case GLFW_KEY_LEFT_CONTROL: return "left control";
			case GLFW_KEY_RIGHT_CONTROL: return "right control";
			case GLFW_KEY_LEFT_ALT:     return "left alt";
			case GLFW_KEY_RIGHT_ALT:    return "right alt";
			case GLFW_KEY_TAB:          return "tab";
			case GLFW_KEY_ENTER:        return "enter";
			case GLFW_KEY_BACKSPACE:    return "backspace";
			case GLFW_KEY_INSERT:       return "insert";
			case GLFW_KEY_DELETE:       return "delete";
			case GLFW_KEY_PAGE_UP:      return "page_up";
			case GLFW_KEY_PAGE_DOWN:    return "page_down";
			case GLFW_KEY_HOME:         return "home";
			case GLFW_KEY_END:          return "end";
			case GLFW_KEY_KP_0:         return "[0]";
			case GLFW_KEY_KP_1:         return "[1]";
			case GLFW_KEY_KP_2:         return "[2]";
			case GLFW_KEY_KP_3:         return "[3]";
			case GLFW_KEY_KP_4:         return "[4]";
			case GLFW_KEY_KP_5:         return "[5]";
			case GLFW_KEY_KP_6:         return "[6]";
			case GLFW_KEY_KP_7:         return "[7]";
			case GLFW_KEY_KP_8:         return "[8]";
			case GLFW_KEY_KP_9:         return "[9]";
			case GLFW_KEY_KP_DIVIDE:    return "keypad divide";
			case GLFW_KEY_KP_MULTIPLY:  return "keypad multiply";
			case GLFW_KEY_KP_SUBTRACT:  return "keypad subtract";
			case GLFW_KEY_KP_ADD:       return "keypad add";
			case GLFW_KEY_KP_DECIMAL:   return "keypad decimal";
			case GLFW_KEY_KP_EQUAL:     return "keypad equal";
			case GLFW_KEY_KP_ENTER:     return "keypad enter";
			case GLFW_KEY_PRINT_SCREEN: return "print screen";
			case GLFW_KEY_NUM_LOCK:     return "num lock";
			case GLFW_KEY_CAPS_LOCK:    return "caps lock";
			case GLFW_KEY_SCROLL_LOCK:  return "scroll lock";
			case GLFW_KEY_PAUSE:        return "pause";
			case GLFW_KEY_LEFT_SUPER:   return "left super";
			case GLFW_KEY_RIGHT_SUPER:  return "right super";
			case GLFW_KEY_MENU:         return "menu";

			default:                    return "unknown";
		}
	} 
