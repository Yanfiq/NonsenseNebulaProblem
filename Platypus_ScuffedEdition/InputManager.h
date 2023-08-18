#include <stdio.h>
#include <SFML/Graphics.hpp>
#include <unordered_map>

class InputManager
{
private:
	static InputManager *pInstance;
	InputManager();
	struct Key
	{
		// Is the key down or up
		// 0 up
		// 1 down
		int curState;
		int prevState;
		// Holds the key being bound
		sf::Keyboard::Key key;
		Key(sf::Keyboard::Key k)
		{
			this->curState = 0;
			this->prevState = 0;
			this->key = k;
		}
	};
	// This maps a given key to another key as necessary
	std::unordered_map<std::string, Key> KeyboardBinds;
	// Check if a bind exists
	bool IsBound(std::string k);

public:
	static InputManager *Instance();
	// Is key down
	bool KeyDown(std::string code);
	// Is key up
	bool KeyUp(std::string code);
	// On key press
	bool KeyPress(std::string code);
	// On key release
	bool KeyRelease(std::string code);
	// Updates real-time inputs
	void Update();
	// Updates releases
	void KRUpdate(sf::Event e);
	// Rebinds a key
	void KBind(std::string code, sf::Keyboard::Key key);
};

InputManager *InputManager::pInstance = NULL;

InputManager *InputManager::Instance()
{
	if (pInstance == NULL)
		pInstance = new InputManager;

	return pInstance;
}

InputManager::InputManager()
{
	// Initialization
}

// Checks if key is bound
bool InputManager::IsBound(std::string k)
{
	if (InputManager::KeyboardBinds.find(k) != InputManager::KeyboardBinds.end())
		return true;
	return false;
}

// Is key down
bool InputManager::KeyDown(std::string code)
{
	if (!IsBound(code))
		return false;

	if (InputManager::KeyboardBinds.find(code)->second.curState)
		return true;

	return false;
}

// Is key up
bool InputManager::KeyUp(std::string code)
{
	if (!IsBound(code))
		return false;

	if (!InputManager::KeyboardBinds.find(code)->second.curState)
		return true;

	return false;
}
// On key press
bool InputManager::KeyPress(std::string code)
{
	if (!IsBound(code))
		return false;

	if (InputManager::KeyboardBinds.find(code)->second.prevState == 0 && InputManager::KeyboardBinds.find(code)->second.curState == 1)
		return true;

	return false;
}

// On key release
bool InputManager::KeyRelease(std::string code)
{
	if (!IsBound(code))
		return false;

	if (InputManager::KeyboardBinds.find(code)->second.prevState == 1 && InputManager::KeyboardBinds.find(code)->second.curState == 0)
		return true;

	return false;
}

// Binds a reference number to a key
void InputManager::KBind(std::string code, sf::Keyboard::Key key)
{
	if (InputManager::IsBound(code))
		InputManager::KeyboardBinds.find(code)->second.key = key;
	else
		InputManager::KeyboardBinds.insert(std::make_pair(code, key));
}

// Updates releases
// Maybe I'll look into making this a bit nicer in the future
// Also, the only reason we can search by value is because the mapping is bijective so keep that in mind
void InputManager::KRUpdate(sf::Event e)
{
	if (e.type == sf::Event::KeyReleased)
		for(auto k : InputManager::KeyboardBinds) if (k.second.key == e.key.code)
				InputManager::KeyboardBinds.find(k.first)
					->second.curState = 0;
	if (e.type == sf::Event::KeyPressed)
		for (auto k : InputManager::KeyboardBinds) if (k.second.key == e.key.code)
				InputManager::KeyboardBinds.find(k.first)
					->second.curState = 1;
}

// Updates real-time inputs ALWAYS place at end of Update function/end of gameloop such that keys can retake input
void InputManager::Update()
{
	// Updates the previous state with the current state at the end of the current update
	for (auto k : InputManager::KeyboardBinds)
		{
			InputManager::KeyboardBinds.find(k.first)->second.prevState = k.second.curState;
		}
}