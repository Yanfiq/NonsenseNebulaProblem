 //
 // SFML - Simple and Fast Multimedia Library
 // Copyright (C) 2007-2009 Laurent Gomila (laurent.gom@gmail.com)
 //
 // This software is provided 'as-is', without any express or implied warranty.
 // In no event will the authors be held liable for any damages arising from the use of this software.
 //
 // Permission is granted to anyone to use this software for any purpose,
 // including commercial applications, and to alter it and redistribute it freely,
 // subject to the following restrictions:
 //
 // 1. The origin of this software must not be misrepresented;
 //    you must not claim that you wrote the original software.
 //    If you use this software in a product, an acknowledgment
 //    in the product documentation would be appreciated but is not required.
 //
 // 2. Altered source versions must be plainly marked as such,
 //    and must not be misrepresented as being the original software.
 //
 // 3. This notice may not be removed or altered from any source distribution.
 //
 
 #ifndef SFML_RECT_HPP
 #define SFML_RECT_HPP
 
 // Headers
 #include <algorithm>
 
 
 namespace sf
 {
 template <typename T>
 class Rect
 {
 public :
 
     Rect();
 
     Rect(T LeftCoord, T TopCoord, T RightCoord, T BottomCoord);
 
     T GetWidth() const;
 
     T GetHeight() const;
 
     void Offset(T OffsetX, T OffsetY);
 
     bool Contains(T X, T Y) const;
 
     bool Intersects(const Rect<T>& Rectangle, Rect<T>* OverlappingRect = NULL) const;
 
     // Member data
     T Left;   
     T Top;    
     T Right;  
     T Bottom; 
 };
 
 #include <SFML/Graphics/Rect.inl>
 
 // Define the most common types
 typedef Rect<int>   IntRect;
 typedef Rect<float> FloatRect;
 
 } // namespace sf
 
 
 #endif // SFML_RECT_HPP