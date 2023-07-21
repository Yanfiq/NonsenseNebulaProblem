#include "SFML/Graphics.hpp"
#include "SFML/Window.hpp"
#include "SFML/Rect.hpp"
#include <string>
#include <unordered_map>

class object{
private:
	float positionX = 0.f, positionY = 0.f;
	float velocityX = 0.f, velocityY = 0.f;
	float width = 0, height = 0;
	float gravity = 0.0002f;
	float maxY = 0.5f;
	float minY = -0.5f;
	float HP = 100;
	std::string object_id;
	sf::RectangleShape object_sprite;

public:
	object(std::string _object_id, float _positionX, float _positionY, float _width, float _height, float _gravity);
	sf::RectangleShape getSprite();
	sf::RectangleShape shoot(float velocity_x, object shooter);
	void reduceHP(float damage);
	float getPositionX();
	float getPositionY();
	float getVelocityX();
	void thrust();
	float getVelocityY();
	void setVelocity(float vx, float vy);
	void update(float time);
	std::string getId();
};

class manageObject {
private:
	static std::unordered_map <std::string, object*> objects_ptr;
	static std::unordered_map <std::string, object*> bullets_object_ptr;
	static std::unordered_map <std::string, sf::RectangleShape*> sprites_ptr;

public:
	static void assign_objectptr(std::string id, object* Object);
	static void assign_bulletptr(std::string id, object* Object);
	static void delete_object(std::string id);
	static object* get_objectptr(std::string id);
	static std::unordered_map<std::string, sf::RectangleShape*> getSpritesMap();
	static std::unordered_map<std::string, object*> getBulletsMap();
	static void deassign_bulletptr(std::string id, object* Object);
	static bool isintersect(std::string id_1, std::string id_2);
	static void show_object(std::string id);
	static void unshow_object(std::string id);
	static sf::RectangleShape* draw_sprite(std::string id);
};