#include "inputManager.h"

InputManager::InputManager() {
    // Initialize the key states to false
    for (int key = 0; key < sf::Keyboard::KeyCount; ++key) {
        keyStates[static_cast<sf::Keyboard::Key>(key)] = false;
    }
}

void InputManager::Update() {
    // Update the key states based on SFML events
    for (int key = 0; key < sf::Keyboard::KeyCount; ++key) {
        if (sf::Keyboard::isKeyPressed(static_cast<sf::Keyboard::Key>(key))) {
            keyStates[static_cast<sf::Keyboard::Key>(key)] = true;
        }
        else {
            keyStates[static_cast<sf::Keyboard::Key>(key)] = false;
        }
    }
}

bool InputManager::IsKeyPressed(sf::Keyboard::Key key) {
    return keyStates[key];
}

bool InputManager::IsKeyReleased(sf::Keyboard::Key key) {
    return !keyStates[key];
}

bool InputManager::IsKeyDown(sf::Keyboard::Key key) {
    return sf::Keyboard::isKeyPressed(key);
}