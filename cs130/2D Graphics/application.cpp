//  /~ = &<3
#include "application.h"

#include <iostream>
#include <cassert>

#ifndef __APPLE__
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#else
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#endif

using namespace std;
// set pixel (x,y) in framebuffer to color col, where
// col is a float array of three values between 0 and 1
// which specify the amount of red, green, and blue to mix (e.g.
// RED: (1,0,0) GREEN: (0,1,0) BLUE: (0,0,1)
// YELLOW: (1,1,0) MAGENTA: (1,0,1) CYAN: (0,1,1)
// )
//
void set_pixel(int x, int y, float col[3])
{
    // write a 1x1 block of pixels of color col to framebuffer
    // coordinates (x, y)
    glRasterPos2i(x, y);
    glDrawPixels(1, 1, GL_RGB, GL_FLOAT, col);
}

void set_pixel(int x, int y)
{
    float col[] = { 1.0, 1.0, 1.0 };
    set_pixel(x,y,col);
}


//
// This is where the line drawing algorithm gets called
// Fix it so that there are no gaps and that it works for all cases
// This lab requires you to use dda to render the line:
// http://en.wikipedia.org/wiki/Digital_differential_analyzer_%28graphics_algorithm%29
//
void draw_line(int x0, int y0, int x1, int y1, float col[3])
{
    int ihold;
    float dx = x1 - x0;
    float dy = y1 - y0;
    float m = 0;
    float b = 0;

    if(dx != 0){
        m = dy/dx;
        b = y0 - m*x0;
    }

    // vertical
    if(dx == 0){
        if(y1 < y0){
            ihold = y1;
            y1 = y0; 
            y0 = ihold;
        }
        for(int i = y0; i < y1; i++)
            set_pixel(x0, i);
    }

    // f(x), slope < 1
    else if(m <= 1 && m >= -1){
        if(x1 < x0){
            ihold = x1;
            x1 = x0; 
            x0 = ihold;
            ihold = y1;
            y1 = y0; 
            y0 = ihold;
        }
        for(int x = x0; x < x1; ++x)
              set_pixel(x, m*x + b);
    }

    // f(y), slope > 1
    else{
        if(y1 < y0){
            ihold = x1;
            x1 = x0; 
            x0 = ihold;
            ihold = y1;
            y1 = y0; 
            y0 = ihold;
        }
        for(int y = y0; y < y1; ++y)
              set_pixel((y-b)/m, y);
    }
}

void pong::draw_ball(int xc, int yc){
    int x = 0, y = 4;
    int d = 3 - 2 * 4;
    while (y >= x)
    {
        // for each pixel we will
        // draw all eight pixels
        drawCircle(xc, yc, x, y);
        x++;
 
        // check for decision parameter
        // and correspondingly 
        // update d, x, y
        if (d > 0)
        {
            y--; 
            d = d + 4 * (x - y) + 10;
        }
        else
            d = d + 4 * x + 6;
        drawCircle(xc, yc, x, y);
        delay(50);
    }
}

// triggered each time the application needs to redraw
void application::draw_event()
{
    //
    // This code draws a single red horizontal line across
    // the the middle of the window using the function
    // set_pixel. Replace this code with your DDA
    // implementation that can draw a line of any slope. You
    // should only need to call set_pixel within your
    // routine.
    //
    float white[] = { 1.0, 1.0, 1.0 };

    //
    // This code will draw each of the lines
    //
    for (size_t i = 0; i < lines.size(); ++i)
    {
    draw_line(lines[i].x0, lines[i].y0, lines[i].x1, lines[i].y1, white);
    }
}

// triggered when mouse is clicked
void application::mouse_click_event(int button, int button_state, int x, int y)
{
    // Each time the mouse button is pushed down, add a new
    // line segment to our list.
    if (button == GLUT_LEFT_BUTTON && button_state == GLUT_DOWN) {
        lines.push_back(line_segment(x, y, x, y));
        button_down = true;
    }
    if (button == GLUT_LEFT_BUTTON && button_state == GLUT_UP) {
        button_down = false;
    }
    //cout << "button event: " << button << " " << button_state
    //    << " " << x << " " << y << endl;
}

// triggered when mouse button is held down and the mouse is
// moved
void application::mouse_move_event(int x, int y)
{
    // While the mouse button is down, update the last
    // endpoint in our list to reflect the current location
    // of the mouse.
    lines[lines.size()-1].x1 = x;
    lines[lines.size()-1].y1 = y;

    //cout << "move event: " << x << " " << y << endl;
}

// triggered when a key is pressed on the keyboard
void application::keyboard_event(unsigned char key, int x, int y)
{
    // clear our stored clicks
    if (key == 'c')
        lines.clear();
    if (key == 't'){
        lines.clear();
        lines.push_back(line_segment(this->width * 1/5, this->height * 2/5,this->width * 4/5, this->height * 2/5));
        lines.push_back(line_segment(this->width * 1/5, this->height * 3/5,this->width * 4/5, this->height * 3/5));
        lines.push_back(line_segment(this->width * 2/5, this->height * 1/5,this->width * 2/5, this->height * 4/5));
        lines.push_back(line_segment(this->width * 3/5, this->height * 1/5,this->width * 3/5, this->height * 4/5));
        game = new tictactoe;
        delete game;
        game = NULL;
    }
    if (key == 'p'){
        lines.clear();
        lines.push_back(line_segment((this->width-5) /2, 5, (this->width-5) /2, this->height-5));
        lines.push_back(line_segment(5, 5, 5, this->height-5));
        lines.push_back(line_segment(5, 5, this->width-5, 5));
        lines.push_back(line_segment(this->width-5, this->height-5, 5, this->height-5));
        lines.push_back(line_segment(this->width-5, this->height-5, this->width-5, 5));
        game = new pong;
        delete game;
        game = NULL;
    }
}
