#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>

#include "gl_viewer.h"

class line_segment
{
public:
    line_segment(int x0, int y0, int x1, int y1)
        : x0(x0), y0(y0), x1(x1), y1(y1)
    {}

    int x0, y0, x1, y1;
};

class parent{

};

class pong{
    void draw_ball();
};

class tictactoe{

};

class application : public gl_viewer
{
public:
    bool button_down;
    parent* game; 
    application() {
        button_down=false;
        game = NULL;
    }
    virtual ~application() {}

    void draw_event();
    void mouse_click_event(int button, int button_state, int x, int y);
    void mouse_move_event(int x, int y);
    void keyboard_event(unsigned char key, int x, int y);

private:
    // store the line segments
    std::vector<line_segment> lines;
    bool button_down;
};

#endif
