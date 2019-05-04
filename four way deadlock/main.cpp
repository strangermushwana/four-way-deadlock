#include <SFML/Graphics.hpp>
#include <iostream>
#include <map>
#include <algorithm>
#include <iomanip>
#include <time.h>
#include <cmath>

using namespace sf;

//!
//! termcolor
//! ~~~~~~~~~
//!
//! termcolor is a header-only c++ library for printing colored messages
//! to the terminal. Written just for fun with a help of the Force.
//!
//! :copyright: (c) 2013 by Ihor Kalnytskyi
//! :license: BSD, see LICENSE for details
//!

#ifndef TERMCOLOR_HPP_
#define TERMCOLOR_HPP_

// the following snippet of code detects the current OS and
// defines the appropriate macro that is used to wrap some
// platform specific things
#if defined(_WIN32) || defined(_WIN64)
#   define TERMCOLOR_OS_WINDOWS
#elif defined(__APPLE__)
#   define TERMCOLOR_OS_MACOS
#elif defined(__unix__) || defined(__unix)
#   define TERMCOLOR_OS_LINUX
#else
#   error unsupported platform
#endif


// This headers provides the `isatty()`/`fileno()` functions,
// which are used for testing whether a standart stream refers
// to the terminal. As for Windows, we also need WinApi funcs
// for changing colors attributes of the terminal.
#if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
#   include <unistd.h>
#elif defined(TERMCOLOR_OS_WINDOWS)
#   include <io.h>
#   include <windows.h>
#endif


#include <iostream>
#include <cstdio>



namespace termcolor
{
    // Forward declaration of the `_internal` namespace.
    // All comments are below.
    namespace _internal
    {
        // An index to be used to access a private storage of I/O streams. See
        // colorize / nocolorize I/O manipulators for details.
        static int colorize_index = std::ios_base::xalloc();

        inline FILE* get_standard_stream(const std::ostream& stream);
        inline bool is_colorized(std::ostream& stream);
        inline bool is_atty(const std::ostream& stream);

    #if defined(TERMCOLOR_OS_WINDOWS)
        inline void win_change_attributes(std::ostream& stream, int foreground, int background=-1);
    #endif
    }

    inline
    std::ostream& colorize(std::ostream& stream)
    {
        stream.iword(_internal::colorize_index) = 1L;
        return stream;
    }

    inline
    std::ostream& nocolorize(std::ostream& stream)
    {
        stream.iword(_internal::colorize_index) = 0L;
        return stream;
    }

    inline
    std::ostream& reset(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[00m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream, -1, -1);
        #endif
        }
        return stream;
    }


    inline
    std::ostream& bold(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[1m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
        #endif
        }
        return stream;
    }


    inline
    std::ostream& dark(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[2m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
        #endif
        }
        return stream;
    }


    inline
    std::ostream& underline(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[4m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
        #endif
        }
        return stream;
    }


    inline
    std::ostream& blink(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[5m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
        #endif
        }
        return stream;
    }


    inline
    std::ostream& reverse(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[7m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
        #endif
        }
        return stream;
    }


    inline
    std::ostream& concealed(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[8m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
        #endif
        }
        return stream;
    }


    inline
    std::ostream& grey(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[30m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream,
                0   // grey (black)
            );
        #endif
        }
        return stream;
    }

    inline
    std::ostream& red(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[31m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream,
                FOREGROUND_RED
            );
        #endif
        }
        return stream;
    }

    inline
    std::ostream& green(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[32m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream,
                FOREGROUND_GREEN
            );
        #endif
        }
        return stream;
    }

    inline
    std::ostream& yellow(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[33m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream,
                FOREGROUND_GREEN | FOREGROUND_RED
            );
        #endif
        }
        return stream;
    }

    inline
    std::ostream& blue(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[34m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream,
                FOREGROUND_BLUE
            );
        #endif
        }
        return stream;
    }

    inline
    std::ostream& magenta(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[35m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream,
                FOREGROUND_BLUE | FOREGROUND_RED
            );
        #endif
        }
        return stream;
    }

    inline
    std::ostream& cyan(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[36m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream,
                FOREGROUND_BLUE | FOREGROUND_GREEN
            );
        #endif
        }
        return stream;
    }

    inline
    std::ostream& white(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[37m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream,
                FOREGROUND_BLUE | FOREGROUND_GREEN | FOREGROUND_RED
            );
        #endif
        }
        return stream;
    }



    inline
    std::ostream& on_grey(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[40m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream, -1,
                0   // grey (black)
            );
        #endif
        }
        return stream;
    }

    inline
    std::ostream& on_red(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[41m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_RED
            );
        #endif
        }
        return stream;
    }

    inline
    std::ostream& on_green(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[42m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_GREEN
            );
        #endif
        }
        return stream;
    }

    inline
    std::ostream& on_yellow(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[43m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_GREEN | BACKGROUND_RED
            );
        #endif
        }
        return stream;
    }

    inline
    std::ostream& on_blue(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[44m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_BLUE
            );
        #endif
        }
        return stream;
    }

    inline
    std::ostream& on_magenta(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[45m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_BLUE | BACKGROUND_RED
            );
        #endif
        }
        return stream;
    }

    inline
    std::ostream& on_cyan(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[46m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_GREEN | BACKGROUND_BLUE
            );
        #endif
        }
        return stream;
    }

    inline
    std::ostream& on_white(std::ostream& stream)
    {
        if (_internal::is_colorized(stream))
        {
        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            stream << "\033[47m";
        #elif defined(TERMCOLOR_OS_WINDOWS)
            _internal::win_change_attributes(stream, -1,
                BACKGROUND_GREEN | BACKGROUND_BLUE | BACKGROUND_RED
            );
        #endif
        }

        return stream;
    }



    //! Since C++ hasn't a way to hide something in the header from
    //! the outer access, I have to introduce this namespace which
    //! is used for internal purpose and should't be access from
    //! the user code.
    namespace _internal
    {
        //! Since C++ hasn't a true way to extract stream handler
        //! from the a given `std::ostream` object, I have to write
        //! this kind of hack.
        inline
        FILE* get_standard_stream(const std::ostream& stream)
        {
            if (&stream == &std::cout)
                return stdout;
            else if ((&stream == &std::cerr) || (&stream == &std::clog))
                return stderr;

            return 0;
        }

        // Say whether a given stream should be colorized or not. It's always
        // true for ATTY streams and may be true for streams marked with
        // colorize flag.
        inline
        bool is_colorized(std::ostream& stream)
        {
            return is_atty(stream) || static_cast<bool>(stream.iword(colorize_index));
        }

        //! Test whether a given `std::ostream` object refers to
        //! a terminal.
        inline
        bool is_atty(const std::ostream& stream)
        {
            FILE* std_stream = get_standard_stream(stream);

            // Unfortunately, fileno() ends with segmentation fault
            // if invalid file descriptor is passed. So we need to
            // handle this case gracefully and assume it's not a tty
            // if standard stream is not detected, and 0 is returned.
            if (!std_stream)
                return false;

        #if defined(TERMCOLOR_OS_MACOS) || defined(TERMCOLOR_OS_LINUX)
            return ::isatty(fileno(std_stream));
        #elif defined(TERMCOLOR_OS_WINDOWS)
            return ::_isatty(_fileno(std_stream));
        #endif
        }

    #if defined(TERMCOLOR_OS_WINDOWS)
        //! Change Windows Terminal colors attribute. If some
        //! parameter is `-1` then attribute won't changed.
        inline void win_change_attributes(std::ostream& stream, int foreground, int background)
        {
            // yeah, i know.. it's ugly, it's windows.
            static WORD defaultAttributes = 0;

            // Windows doesn't have ANSI escape sequences and so we use special
            // API to change Terminal output color. That means we can't
            // manipulate colors by means of "std::stringstream" and hence
            // should do nothing in this case.
            if (!_internal::is_atty(stream))
                return;

            // get terminal handle
            HANDLE hTerminal = INVALID_HANDLE_VALUE;
            if (&stream == &std::cout)
                hTerminal = GetStdHandle(STD_OUTPUT_HANDLE);
            else if (&stream == &std::cerr)
                hTerminal = GetStdHandle(STD_ERROR_HANDLE);

            // save default terminal attributes if it unsaved
            if (!defaultAttributes)
            {
                CONSOLE_SCREEN_BUFFER_INFO info;
                if (!GetConsoleScreenBufferInfo(hTerminal, &info))
                    return;
                defaultAttributes = info.wAttributes;
            }

            // restore all default settings
            if (foreground == -1 && background == -1)
            {
                SetConsoleTextAttribute(hTerminal, defaultAttributes);
                return;
            }

            // get current settings
            CONSOLE_SCREEN_BUFFER_INFO info;
            if (!GetConsoleScreenBufferInfo(hTerminal, &info))
                return;

            if (foreground != -1)
            {
                info.wAttributes &= ~(info.wAttributes & 0x0F);
                info.wAttributes |= static_cast<WORD>(foreground);
            }

            if (background != -1)
            {
                info.wAttributes &= ~(info.wAttributes & 0xF0);
                info.wAttributes |= static_cast<WORD>(background);
            }

            SetConsoleTextAttribute(hTerminal, info.wAttributes);
        }
    #endif // TERMCOLOR_OS_WINDOWS

    } // namespace _internal

} // namespace termcolor


#undef TERMCOLOR_OS_WINDOWS
#undef TERMCOLOR_OS_MACOS
#undef TERMCOLOR_OS_LINUX

#endif // TERMCOLOR_HPP_

#ifndef COLLISION_H
#define COLLISION_H

namespace Collision {

    bool PixelPerfectTest(const sf::Sprite& Object1 ,const sf::Sprite& Object2, sf::Uint8 AlphaLimit = 0);

    bool CreateTextureAndBitmask(sf::Texture &LoadInto, const std::string& Filename);

    bool CircleTest(const sf::Sprite& Object1, const sf::Sprite& Object2);

    bool BoundingBoxTest(const sf::Sprite& Object1, const sf::Sprite& Object2);
}

#endif	/* COLLISION_H */

namespace Collision
{
    class BitmaskManager
    {
    public:
        ~BitmaskManager() {
            std::map<const sf::Texture*, sf::Uint8*>::const_iterator end = Bitmasks.end();
            for (std::map<const sf::Texture*, sf::Uint8*>::const_iterator iter = Bitmasks.begin(); iter!=end; iter++)
                delete [] iter->second;
        }

        sf::Uint8 GetPixel (const sf::Uint8* mask, const sf::Texture* tex, unsigned int x, unsigned int y) {
            if (x>tex->getSize().x||y>tex->getSize().y)
                return 0;

            return mask[x+y*tex->getSize().x];
        }

        sf::Uint8* GetMask (const sf::Texture* tex) {
            sf::Uint8* mask;
            std::map<const sf::Texture*, sf::Uint8*>::iterator pair = Bitmasks.find(tex);
            if (pair==Bitmasks.end())
            {
                sf::Image img = tex->copyToImage();
                mask = CreateMask (tex, img);
            }
            else
                mask = pair->second;

            return mask;
        }

        sf::Uint8* CreateMask (const sf::Texture* tex, const sf::Image& img) {
            sf::Uint8* mask = new sf::Uint8[tex->getSize().y*tex->getSize().x];

            for (unsigned int y = 0; y<tex->getSize().y; y++)
            {
                for (unsigned int x = 0; x<tex->getSize().x; x++)
                    mask[x+y*tex->getSize().x] = img.getPixel(x,y).a;
            }

            Bitmasks.insert(std::pair<const sf::Texture*, sf::Uint8*>(tex,mask));

            return mask;
        }
    private:
        std::map<const sf::Texture*, sf::Uint8*> Bitmasks;
    };

    BitmaskManager Bitmasks;

    bool PixelPerfectTest(const sf::Sprite& Object1, const sf::Sprite& Object2, sf::Uint8 AlphaLimit) {
        sf::FloatRect Intersection;
        if (Object1.getGlobalBounds().intersects(Object2.getGlobalBounds(), Intersection)) {
            sf::IntRect O1SubRect = Object1.getTextureRect();
            sf::IntRect O2SubRect = Object2.getTextureRect();

            sf::Uint8* mask1 = Bitmasks.GetMask(Object1.getTexture());
            sf::Uint8* mask2 = Bitmasks.GetMask(Object2.getTexture());

            // Loop through our pixels
            for (int i = Intersection.left; i < Intersection.left+Intersection.width; i++) {
                for (int j = Intersection.top; j < Intersection.top+Intersection.height; j++) {

                    sf::Vector2f o1v = Object1.getInverseTransform().transformPoint(i, j);
                    sf::Vector2f o2v = Object2.getInverseTransform().transformPoint(i, j);

                    // Make sure pixels fall within the sprite's subrect
                    if (o1v.x > 0 && o1v.y > 0 && o2v.x > 0 && o2v.y > 0 &&
                        o1v.x < O1SubRect.width && o1v.y < O1SubRect.height &&
                        o2v.x < O2SubRect.width && o2v.y < O2SubRect.height) {

                        if (Bitmasks.GetPixel(mask1, Object1.getTexture(), (int)(o1v.x)+O1SubRect.left, (int)(o1v.y)+O1SubRect.top) > AlphaLimit &&
                            Bitmasks.GetPixel(mask2, Object2.getTexture(), (int)(o2v.x)+O2SubRect.left, (int)(o2v.y)+O2SubRect.top) > AlphaLimit)
                            return true;

                    }
                }
            }
        }
        return false;
    }

    bool CreateTextureAndBitmask(sf::Texture &LoadInto, const std::string& Filename)
    {
        sf::Image img;
        if (!img.loadFromFile(Filename))
            return false;
        if (!LoadInto.loadFromImage(img))
            return false;

        Bitmasks.CreateMask(&LoadInto, img);
        return true;
    }

    sf::Vector2f GetSpriteCenter (const sf::Sprite& Object)
    {
        sf::FloatRect AABB = Object.getGlobalBounds();
        return sf::Vector2f (AABB.left+AABB.width/2.f, AABB.top+AABB.height/2.f);
    }

    sf::Vector2f GetSpriteSize (const sf::Sprite& Object)
    {
        sf::IntRect OriginalSize = Object.getTextureRect();
        sf::Vector2f Scale = Object.getScale();
        return sf::Vector2f (OriginalSize.width*Scale.x, OriginalSize.height*Scale.y);
    }

    bool CircleTest(const sf::Sprite& Object1, const sf::Sprite& Object2) {
        sf::Vector2f Obj1Size = GetSpriteSize(Object1);
        sf::Vector2f Obj2Size = GetSpriteSize(Object2);
        float Radius1 = (Obj1Size.x + Obj1Size.y) / 4;
        float Radius2 = (Obj2Size.x + Obj2Size.y) / 4;

        sf::Vector2f Distance = GetSpriteCenter(Object1)-GetSpriteCenter(Object2);

        return (Distance.x * Distance.x + Distance.y * Distance.y <= (Radius1 + Radius2) * (Radius1 + Radius2));
    }

    class OrientedBoundingBox // Used in the BoundingBoxTest
    {
    public:
        OrientedBoundingBox (const sf::Sprite& Object) // Calculate the four points of the OBB from a transformed (scaled, rotated...) sprite
        {
            sf::Transform trans = Object.getTransform();
            sf::IntRect local = Object.getTextureRect();
            Points[0] = trans.transformPoint(0.f, 0.f);
            Points[1] = trans.transformPoint(local.width, 0.f);
            Points[2] = trans.transformPoint(local.width, local.height);
            Points[3] = trans.transformPoint(0.f, local.height);
        }

        sf::Vector2f Points[4];

        void ProjectOntoAxis (const sf::Vector2f& Axis, float& Min, float& Max) // Project all four points of the OBB onto the given axis and return the dotproducts of the two outermost points
        {
            Min = (Points[0].x*Axis.x+Points[0].y*Axis.y);
            Max = Min;
            for (int j = 1; j<4; j++)
            {
                float Projection = (Points[j].x*Axis.x+Points[j].y*Axis.y);

                if (Projection<Min)
                    Min=Projection;
                if (Projection>Max)
                    Max=Projection;
            }
        }
    };

    bool BoundingBoxTest(const sf::Sprite& Object1, const sf::Sprite& Object2) {
        OrientedBoundingBox OBB1 (Object1);
        OrientedBoundingBox OBB2 (Object2);

        // Create the four distinct axes that are perpendicular to the edges of the two rectangles
        sf::Vector2f Axes[4] = {
            sf::Vector2f (OBB1.Points[1].x-OBB1.Points[0].x,
                          OBB1.Points[1].y-OBB1.Points[0].y),
            sf::Vector2f (OBB1.Points[1].x-OBB1.Points[2].x,
                          OBB1.Points[1].y-OBB1.Points[2].y),
            sf::Vector2f (OBB2.Points[0].x-OBB2.Points[3].x,
                          OBB2.Points[0].y-OBB2.Points[3].y),
            sf::Vector2f (OBB2.Points[0].x-OBB2.Points[1].x,
                          OBB2.Points[0].y-OBB2.Points[1].y)
        };

        for (int i = 0; i<4; i++) // For each axis...
        {
            float MinOBB1, MaxOBB1, MinOBB2, MaxOBB2;

            // ... project the points of both OBBs onto the axis ...
            OBB1.ProjectOntoAxis(Axes[i], MinOBB1, MaxOBB1);
            OBB2.ProjectOntoAxis(Axes[i], MinOBB2, MaxOBB2);

            // ... and check whether the outermost projected points of both OBBs overlap.
            // If this is not the case, the Separating Axis Theorem states that there can be no collision between the rectangles
            if (!((MinOBB2<=MaxOBB1)&&(MaxOBB2>=MinOBB1)))
                return false;
        }
        return true;
    }
}



class GameObject
{
    public:
        void loadTexture(std::string textureName, float vecX, float vecY)
        {
            if (!texture.loadFromFile(textureName))
            {
                std::cout<<"Error occoured!, failed to load "<<textureName<<std::endl;
            }
            sprite.setTexture(texture);
            sprite.setPosition(Vector2f(vecX,vecY));
        }

        void moveSprite(float X, float Y)
        {
            sprite.move(X,Y);
        }

        Sprite getSprite()
        {
            return sprite;
        }

    private:
        Texture texture;
        float directionX;
        float directionY;
        Sprite sprite;
};

bool collision(Sprite object1, Sprite object2)
{
    if(Collision::PixelPerfectTest(object1,object2))
        return true;
    return false;
}

void reset(GameObject object[10])
{
    object[0].loadTexture("images/left/left_yellow.png",0,310);
    object[1].loadTexture("images/left/left_blue.png",60,310);
    object[2].loadTexture("images/left/left_black.png",130,310);

    object[3].loadTexture("images/right/right_blue.png",700,265);
    object[4].loadTexture("images/right/right_yellow.png",630,265);
    object[5].loadTexture("images/right/right_red.png",550,265);

    object[6].loadTexture("images/north/north_red.png",340,0);
    object[7].loadTexture("images/north/north_blue.png",340,60);

    object[8].loadTexture("images/south/south_black.png",385,550);
    object[9].loadTexture("images/south/south_blue.png",385,480);
}

void sleepcp(int milliseconds) // Cross-platform sleep function
{
    clock_t time_end;
    time_end = clock() + milliseconds * CLOCKS_PER_SEC/1000;
    while (clock() < time_end)
    {
    }
}

int main()
{
    RenderWindow window(VideoMode(700, 600), "Deadlock");
    std::string data;
    window.setFramerateLimit(60);
    GameObject object[10];
    GameObject object2[4];

    Clock clock;
    Time time;

    int counterCheck = 1;

    /// Crossroad texture
    Texture texture;
    Sprite crossroad;
    std::string textureName = "images/crossroad.gif";

    if (!texture.loadFromFile(textureName))
    {
        std::cout<<"Error occoured!, failed to load "<<textureName<<std::endl;
    }
    crossroad.setTexture(texture);
    crossroad.setScale(sf::Vector2f(0.6,0.4));

    reset(object);

    while (window.isOpen())
    {
        Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
        }

        /// update
        if(data == "resolve")
        {
            counterCheck++;
            if(counterCheck >= 67)
            {
                object[0].moveSprite(1.9,0);
                object[1].moveSprite(1.9,0);
                object[2].moveSprite(1.9,0);
                object[3].moveSprite(-1.5,0);
                object[4].moveSprite(-1.5,0);
                object[5].moveSprite(-1.5,0);
                object[6].getSprite().setPosition(385,438);

                if(clock.getElapsedTime().asSeconds() >= 6)
                {
                    object2[0].loadTexture("images/traficlights/red.png",485,225);
                    object2[1].loadTexture("images/traficlights/green.png",485,380);//485,380
                    object2[2].loadTexture("images/traficlights/green.png",265,225);//265,255
                    object2[3].loadTexture("images/traficlights/red.png",265,380);

                    object[6].moveSprite(0,1.8);
                    object[7].moveSprite(0,1.8);
                    object[8].moveSprite(0,-1.5);
                    object[9].moveSprite(0,-1.5);
                }
            }
            else
            {
                object[0].moveSprite(1.9,0);
                object[1].moveSprite(1.9,0);
                object[2].moveSprite(1.9,0);
                object[3].moveSprite(-1.5,0);
                object[4].moveSprite(-1.5,0);
                object[5].moveSprite(-1.5,0);
                object[6].moveSprite(0,1.8);
                object[7].moveSprite(0,1.8);
                object[8].moveSprite(0,-1.5);
                object[9].moveSprite(0,-1.5);
            }

        }
        else
        {
            object[0].moveSprite(1.9,0);
            object[1].moveSprite(1.9,0);
            object[2].moveSprite(1.9,0);
            object[3].moveSprite(-1.5,0);
            object[4].moveSprite(-1.5,0);
            object[5].moveSprite(-1.5,0);
            object[6].moveSprite(0,1.8);
            object[7].moveSprite(0,1.8);
            object[8].moveSprite(0,-1.5);
            object[9].moveSprite(0,-1.5);
        }

        if(collision(object[2].getSprite(),object[9].getSprite()) || collision(object[5].getSprite(),object[7].getSprite()))
        {
            std::cout<<"There was a collison, Road Blocked!"<<std::endl;
            std::cout<<"Enter the command \'Resolve\' to resolve the deadlock: ";
            std::cin>>data;
            std::transform(data.begin(), data.end(), data.begin(), ::tolower);
            if(data == "resolve")
            {
                /// Resolve
                reset(object);
                object2[0].loadTexture("images/traficlights/red.png",485,380);
                object2[1].loadTexture("images/traficlights/green.png",485,225);
                object2[2].loadTexture("images/traficlights/green.png",265,380);
                object2[3].loadTexture("images/traficlights/red.png",265,225);
                clock.restart();

            }
            else
            {
                std::cout<<"Wrong command\nExecuting again with Deadlock"<<std::endl;
                reset(object);
            }
        }

        window.clear();

        /// Draw
        window.draw(crossroad);
        if(data == "resolve")
        {
            for(int index = 0; index< 4; index++)
            {
                window.draw(object2[index].getSprite());
            }


            for(int index = 0; index < 10; index++)
            {
                window.draw(object[index].getSprite());
            }
        }
        else
        {
            for(int index = 0; index < 10; index++)
            {
                window.draw(object[index].getSprite());
            }
        }
        /// Display
        window.display();
    }

    return 0;
}

class ResolveDeadlock
{};




















