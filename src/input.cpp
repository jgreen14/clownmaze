#include "../include/input.h"

Input::Input()
{
    //ctor
    prevMouseX = 0;
    dxMouse = 0;
}

Input::~Input()
{
    //dtor
}

INPUT Input::processEvent(sf::Event* event)
{
    // CLOSEWINDOW
    if (event->type == sf::Event::Closed)
        return CLOSEWINDOW;

    if (event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::X)
        return QUIT;

    if (event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::N)
        return NEXTMAP;

    if (event->type == sf::Event::KeyPressed && event->key.code == sf::Keyboard::P)
        return PREVMAP;

    if (event->type == sf::Event::MouseButtonPressed)
        return MOUSEBUTTONLEFT;

    return NOINPUT;
}//processEvent

int Input::processInput(sf::RenderWindow* window)
{
    int newInput = NOINPUT;

    if (window->hasFocus())
    {
        dxMouse = sf::Mouse::getPosition(*window).x - prevMouseX;

        if (dxMouse != 0)
        {
            newInput = newInput | MOUSETURN;
            //Keep the mouse cursor inside the window (DOESN"T WORK IF THE MOUSE IS MOVED QUICKLY)

            sf::Mouse::setPosition(sf::Vector2i(window->getSize().x/2, window->getSize().y/2), *window);
            prevMouseX = sf::Mouse::getPosition(*window).x;
        }//if
    }//if
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
        newInput = newInput | LEFT;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        newInput = newInput | RIGHT;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        newInput = newInput | FORWARD;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        newInput = newInput | STRAFELEFT;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        newInput = newInput | BACKWARD;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        newInput = newInput | STRAFERIGHT;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
        newInput = newInput | UP;
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::F))
        newInput = newInput | DOWN;

    return newInput;
}//processInput*/

int Input::getMouseDeltaX()
{
    return dxMouse;
}//getMouseDeltaX
