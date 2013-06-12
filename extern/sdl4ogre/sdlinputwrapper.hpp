#ifndef _SDL4OGRE_SDLINPUTWRAPPER_H
#define _SDL4OGRE_SDLINPUTWRAPPER_H

#include <SDL_events.h>

#include <OgreRenderWindow.h>
#include <boost/unordered_map.hpp>

#include "OISCompat.h"
#include "events.h"



namespace SFO
{
    class InputWrapper
    {
    public:
        InputWrapper(SDL_Window *window=NULL);
        ~InputWrapper();

        //void initFromRenderWindow(Ogre::RenderWindow* win);

        void setMouseEventCallback(MouseListener* listen) { mMouseListener = listen; }
        void setKeyboardEventCallback(KeyListener* listen) { mKeyboardListener = listen; }
        void setWindowEventCallback(WindowListener* listen) { mWindowListener = listen; }

        void capture();
        bool isModifierHeld(int mod);

        void setMouseRelative(bool relative);
        bool getMouseRelative() { return mMouseRelative; }
        void setGrabPointer(bool grab);

        OIS::KeyCode sdl2OISKeyCode(SDL_Keycode code);

        void warpMouse(int x, int y);

    private:

        bool _handleWarpMotion(const SDL_MouseMotionEvent& evt);
        void _wrapMousePointer(const SDL_MouseMotionEvent &evt);
        MouseMotionEvent _packageMouseMotion(const SDL_Event& evt);

        void _handleKeyPress(SDL_KeyboardEvent& evt);
        Uint32 _UTF8ToUTF32(const unsigned char *buf);
        void _setupOISKeys();

        SFO::MouseListener* mMouseListener;
        SFO::KeyListener* mKeyboardListener;
        SFO::WindowListener* mWindowListener;

        typedef boost::unordered_map<SDL_Keycode, OIS::KeyCode> KeyMap;
        KeyMap mKeyMap;

        Uint16 mWarpX;
        Uint16 mWarpY;
        bool mWarpCompensate;
        bool mMouseRelative;
        bool mWrapPointer;
        bool mGrabPointer;

        Sint32 mMouseZ;
        Sint32 mMouseX;
        Sint32 mMouseY;

        SDL_Window* mSDLWindow;
        bool mOwnWindow;
    };

}

#endif