#include "controllerGTP.h"

Controller_GTP::color Controller_GTP::b = BLACK;
Controller_GTP::color Controller_GTP::w = WHITE;

Controller_GTP::Controller_GTP()
{
    buf_size = 128;
    launchEngine();
}

Controller_GTP::~Controller_GTP()
{
    quitEngine();
}

bool Controller_GTP::launchEngine()
{
    int r_pipes[2];
    int w_pipes[2];
    int err;
    pid_t pid;

    err = pipe(r_pipes);
    if(err != 0)
        return false;

    err = pipe(w_pipes);
    if(err != 0)
        return false;

    pid = fork();

    if (pid == 0) 
    {
        close(STDIN_FILENO);
        close(STDOUT_FILENO);
        close(STDERR_FILENO);
        dup2(w_pipes[0], STDIN_FILENO);
        dup2(r_pipes[1], STDOUT_FILENO);
        dup2(r_pipes[1], STDERR_FILENO);
        close(w_pipes[1]);
        close(w_pipes[0]);
        close(r_pipes[1]);
        close(r_pipes[0]);

        int err = execl("/usr/local/bin/gnugo", "gnugo", "--mode=gtp", "--level=1", NULL);
        if(err == -1)
            return false;
        exit(1);
    }
    close(w_pipes[0]);
    close(r_pipes[1]);

    input_handle = w_pipes[1];
    output_handle = r_pipes[0];

    return true;
}

string Controller_GTP::genmove(color _color)
{
    string command;

    switch(_color)
    {
        case BLACK:
            command = "genmove black";
            break;
        case WHITE:
            command = "genmove WHITE";
            break;
        default:
            return "";
    }

    return getResponse(command);
}

bool Controller_GTP::play(color _color, string move)
{
    string command;

    switch(_color)
    {
        case BLACK:
            command = "play black ";
            break;
        case WHITE:
            command = "play white ";
            break;
        default:
            return false;
    }
    command = command + move;

    string res = getResponse(command);
    if(res == "")
        return false;

    return true;
}

bool Controller_GTP::undo()
{
    string res = getResponse("undo");
    if(res == "")
        return false;

    return true;
}

bool Controller_GTP::quitEngine()
{
    bool ret = sendCommand("quit");
    close(input_handle);
    close(output_handle);
    
    return ret;
}

bool Controller_GTP::waitForActivity()
{
    sleep(1);

    fd_set read_fds;

    FD_ZERO(&read_fds);
    FD_SET(output_handle, &read_fds);

    int err = select(output_handle +1, &read_fds, NULL, NULL, NULL);
    if(err<0)
        exit(1);
    
    return true;
}   

bool Controller_GTP::sendCommand(string command)
{
    ssize_t wc;
    
    string cmd = command;
    cmd += "\n\0";

    wc = write(input_handle, cmd.c_str(), cmd.size());
    if(wc < 0)
        return false;

    return true;
}

string Controller_GTP::getResponse(string command)
{
    ssize_t rc;
    bool ret;

    ret = sendCommand(command);
    if(!ret)
        return "";

    ret = waitForActivity();
    if(!ret)
        return "";

    char res[buf_size];
    rc = read(output_handle, &res, buf_size);
    if(rc < 0)
        return "";

    string response = string(res);
    response = response.erase(0, 2);

    return response;
}


