//
// Created by Timothy Coelho on 7/21/24.
//

#ifndef LIBRARY_OF_ALEXANDRIA_CPP_VIRTUAL_KEYS_H
#define LIBRARY_OF_ALEXANDRIA_CPP_VIRTUAL_KEYS_H

//MacOS Virtual Key Mappings
typedef size_t VirtualKey;

// Number Defines
static constexpr VirtualKey VK_0 = 0x1D;
static constexpr VirtualKey VK_1 = 0x12;
static constexpr VirtualKey VK_2 = 0x13;
static constexpr VirtualKey VK_3 = 0x14;
static constexpr VirtualKey VK_4 = 0x15;
static constexpr VirtualKey VK_5 = 0x17;
static constexpr VirtualKey VK_6 = 0x16;
static constexpr VirtualKey VK_7 = 0x1a;
static constexpr VirtualKey VK_8 = 0x1c;
static constexpr VirtualKey VK_9 = 0x19;

//Letter Defines
static constexpr VirtualKey VK_A = 0x00;
static constexpr VirtualKey VK_B = 0x0B;
static constexpr VirtualKey VK_C = 0x08;
static constexpr VirtualKey VK_D = 0x02;
static constexpr VirtualKey VK_E = 0x0E;
static constexpr VirtualKey VK_F = 0x03;
static constexpr VirtualKey VK_G = 0x05;
static constexpr VirtualKey VK_H = 0x04;
static constexpr VirtualKey VK_I = 0x22;
static constexpr VirtualKey VK_J = 0x26;
static constexpr VirtualKey VK_K = 0x28;
static constexpr VirtualKey VK_L = 0x25;
static constexpr VirtualKey VK_M = 0x2E;
static constexpr VirtualKey VK_N = 0x2D;
static constexpr VirtualKey VK_O = 0x1F;
static constexpr VirtualKey VK_P = 0x23;
static constexpr VirtualKey VK_Q = 0x0C;
static constexpr VirtualKey VK_R = 0x0F;
static constexpr VirtualKey VK_S = 0x01;
static constexpr VirtualKey VK_T = 0x11;
static constexpr VirtualKey VK_U = 0x20;
static constexpr VirtualKey VK_V = 0x09;
static constexpr VirtualKey VK_W = 0x0D;
static constexpr VirtualKey VK_X = 0x07;
static constexpr VirtualKey VK_Y = 0x33;
static constexpr VirtualKey VK_Z = 0x06;

//Utility keys
static constexpr VirtualKey VK_TAB = 0x30;
static constexpr VirtualKey VK_LSHIFT = 0x38;
static constexpr VirtualKey VK_RSHIFT = 0x3C;
static constexpr VirtualKey VK_LCONTROL = 0x3B;
static constexpr VirtualKey VK_RCONTROL = 0x3E;
static constexpr VirtualKey VK_ESCAPE = 0x35;
static constexpr VirtualKey VK_COMMAND_L = 0x37; //MacOS C
static constexpr VirtualKey VK_OPTION_L = 0x3A; //MacOS Option Key
static constexpr VirtualKey VK_COMMAND_R = 0x36;
static constexpr VirtualKey VK_OPTION_R = 0x3D; //MacOS Option Key
static constexpr VirtualKey VK_DELETE = 0x75;
static constexpr VirtualKey VK_PAGE_UP = 0x74;
static constexpr VirtualKey VK_PAGE_DOWN = 0x79;
static constexpr VirtualKey VK_INSERT = 0x72;

//OEM Keys
static constexpr VirtualKey VK_OEM_1 = 0x29; // ;:;
static constexpr VirtualKey VK_OEM_2 = 0x2C; // /?
static constexpr VirtualKey VK_OEM_3 = 0x32; // `~
static constexpr VirtualKey VK_OEM_4 = 0x21; // [{
static constexpr VirtualKey VK_OEM_5 = 0x2A; // |
static constexpr VirtualKey VK_OEM_6 = 0x1E; // ]}
static constexpr VirtualKey VK_OEM_7 = 0x27; // '"

static constexpr VirtualKey VK_OEM_PERIOD = 0x2F;
static constexpr VirtualKey VK_OEM_PLUS = 0x18;
static constexpr VirtualKey VK_OEM_MINUS = 0x1B;
static constexpr VirtualKey VK_OEM_COMMA = 0x2B;

//Arrow Keys
static constexpr VirtualKey VK_UP = 0x7E;
static constexpr VirtualKey VK_DOWN = 0x7D;
static constexpr VirtualKey VK_LEFT = 0x7B;
static constexpr VirtualKey VK_RIGHT = 0x7C;

//F Keys
static constexpr VirtualKey VK_F1  = 0x7A;
static constexpr VirtualKey VK_F2  = 0x78;
static constexpr VirtualKey VK_F3  = 0x63;
static constexpr VirtualKey VK_F4  = 0x76;
static constexpr VirtualKey VK_F5  = 0x60;
static constexpr VirtualKey VK_F6  = 0x61;
static constexpr VirtualKey VK_F7  = 0x62;
static constexpr VirtualKey VK_F8  = 0x64;
static constexpr VirtualKey VK_F9  = 0x65;
static constexpr VirtualKey VK_F10 = 0x6D;
static constexpr VirtualKey VK_F11 = 0x67;
static constexpr VirtualKey VK_F12 = 0x6F;

#endif //LIBRARY_OF_ALEXANDRIA_CPP_VIRTUAL_KEYS_H
