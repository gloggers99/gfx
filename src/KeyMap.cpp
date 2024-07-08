#include "KeyMap.hpp"

namespace GFX {

void KeyMap::callback(GLFWwindow *window, int key, int _scancode, int action, int mods) {
    for (auto &keyPair : this->keys) {
        if (key == keyPair.first.key && action == keyPair.first.action && mods == keyPair.first.mods)
            keyPair.second();
        // don't return after finding the pair so the user can define multiple functions that apply to one keybind
    }
}

void KeyMap::add(const GFX::KeyBind &keyBind, const GFX::KeyMapFunc &keyMapFunc) {
    this->keys.emplace(keyBind, keyMapFunc);
}

void KeyMap::set(const std::unordered_map<KeyBind, KeyMapFunc, KeyBindHash> &keyMap) {
    this->keys = keyMap;
}

KeyMap::KeyMap() : keys{{{0, 0, 0}, [](){}}} {}

KeyMap::KeyMap(const std::unordered_map<KeyBind, KeyMapFunc, KeyBindHash> &keyMap) : keys(keyMap) {}

KeyMap::~KeyMap() = default;

} // namespace GFX
