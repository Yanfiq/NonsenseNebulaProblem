#include <unordered_map>
#include <string>
#include "SFML/Graphics.hpp"
#include "SFML/Rect.hpp"
#include "objects.h"

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
	static bool isintersect(std::string id_1, std::string id_2);
	static void show_object(std::string id);
	static void unshow_object(std::string id);
	static sf::RectangleShape* draw_sprite(std::string id);
};