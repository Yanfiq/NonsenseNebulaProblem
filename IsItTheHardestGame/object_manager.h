#include <unordered_map>
#include <string>
#include "objects.h"

class manageObject {
protected:
	static std::unordered_map <std::string, object*> objects_ptr;
	static std::unordered_map <std::string, object*> bullets_object_ptr;
	static std::unordered_map <std::string, sf::RectangleShape*> sprites_ptr;

public:
	static void createObject(std::string _object_id, float _positionX, float _positionY, float _width, float _height, float _gravity);
	static void delete_object(std::string id);
	static object* get_objectptr(std::string id);
	static std::unordered_map<std::string, sf::RectangleShape*> getSpritesMap();
	static bool isintersect(sf::RectangleShape* shape_1, sf::RectangleShape* shape_2);
	static void show_object(std::string id);
	static void unshow_object(std::string id);
	static sf::RectangleShape* draw_sprite(std::string id);
};