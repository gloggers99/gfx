#include "KeyMap.hpp"

namespace GFX {

void KeyMap::callback(GLFWwindow *window, int key, int _scancode, int action, int mods) {
    for (auto &keyPair : this->keys) {
        if (key == keyPair.first.key && action == keyPair.first.action && mods == keyPair.first.mods)
            keyPair.second();
    }
}


KeyMap::KeyMap() : keys{{{0, 0, 0}, [](){}}} {

}

KeyMap::KeyMap(const std::unordered_map<KeyBind, KeyMapFunc, KeyBindHash> &keys) : keys(keys) {}

KeyMap::~KeyMap() = default;

} // namespace GFX
