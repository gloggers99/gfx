#pragma once

#include <utility>
#include <functional>
#include <unordered_map>

#include <glad/gl.h>
#include "GLFW/glfw3.h"

namespace GFX {

typedef struct KeyBind {
    int key;
    int action;
    int mods;
    bool operator==(const KeyBind &other) const {
        return key == other.key && action == other.action && mods == other.mods;
    };
} KeyBind;

typedef struct keyBindHash {
    std::size_t operator()(const KeyBind &kb) const {
        std::size_t h1 = std::hash<int>()(kb.key);
        std::size_t h2 = std::hash<int>()(kb.action);
        std::size_t h3 = std::hash<int>()(kb.mods);
        return h1 ^ (h2 << 1) ^ (h3 << 2); // Combine the hashes
    }
} KeyBindHash;

typedef std::function<void()> KeyMapFunc;

class KeyMap {
private:
    std::unordered_map<KeyBind, KeyMapFunc, KeyBindHash> keys;
public:
    void callback(GLFWwindow *window, int key, int _scancode, int action, int mods);

    KeyMap();
    explicit KeyMap(const std::unordered_map<KeyBind, KeyMapFunc, KeyBindHash>&);
    ~KeyMap();
};

} // namespace GFX