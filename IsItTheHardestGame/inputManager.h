#include <SFML/Window.hpp>
#include <unordered_map>

class InputManager {
public:
    InputManager();

    void Update();

    bool IsKeyPressed(sf::Keyboard::Key key);
    bool IsKeyReleased(sf::Keyboard::Key key);
    bool IsKeyDown(sf::Keyboard::Key key);

private:
    std::unordered_map<sf::Keyboard::Key, bool> keyStates;
};