#ifndef INPUT_HANLDER_H
#define INPUT_HANDLER_H
#include <glfw3.h>
class InputHandler
{
public:
   static Event * handleKey(int key, int state, int mods);
};

#endif