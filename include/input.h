#ifndef INPUT_H
#define INPUT_H

#include <SFML/Graphics.hpp>
#include "../include/enum.h"

class Input
{
    public:
        Input();
        virtual ~Input();
        INPUT processEvent(sf::Event*);
        int processInput(sf::RenderWindow*);
        int getMouseDeltaX();
    protected:
    private:
        int dxMouse;
        int prevMouseX;
};

#endif // INPUT_H
