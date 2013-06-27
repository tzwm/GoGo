#ifndef __CONTROLLER_GTP_H__
#define __CONTROLLER_GTP_H__

#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string>
#include <iostream>

using namespace std;

class Controller_GTP
{
public:
    enum color{BLACK, WHITE};
    static color b, w;
    Controller_GTP();
    ~Controller_GTP();
    bool launchEngine();
    string genmove(color _color);
    bool play(color _color, string move);
    bool undo();
    bool quitEngine();
   
private:
    bool waitForActivity();
    bool sendCommand(string command);
    string getResponse(string command);

    int input_handle;
    int output_handle;
    
    int buf_size;
};

#endif

