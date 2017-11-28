/**
 * minigl.cpp
 * -------------------------------
 * Implement miniGL here.
 *
 * You may include minigl.h and any of the standard C++ libraries.
 * No other includes are permitted.  Other preprocessing directives
 * are also not permitted.  These requirements are strictly
 * enforced.  Be sure to run a test grading to make sure your file
 * passes the sanity tests.
 *
 * The behavior of the routines your are implenting is documented here:
 * https://www.opengl.org/sdk/docs/man2/
 * Note that you will only be implementing a subset of this.  In particular,
 * you only need to implement enough to pass the tests in the suite.
 */

// source: am math major
#include "minigl.h"
#include "vec.h"
#include "mat.h"
#include <algorithm>
#include <cassert>
#include <cmath>
#include <vector>
#include <cstdio>
#include <iostream>
#include <limits>

using namespace std;

/**
 * Useful data types
 */
typedef mat<MGLfloat,4,4> mat4; //data structure storing a 4x4 matrix, see mat.h
typedef mat<MGLfloat,3,3> mat3; //data structure storing a 3x3 matrix, see mat.h
typedef vec<MGLfloat,4> vec4;   //data structure storing a 4 dimensional vector, see vec.h
typedef vec<MGLfloat,3> vec3;   //data structure storing a 3 dimensional vector, see vec.h
typedef vec<MGLfloat,2> vec2;   //data structure storing a 2 dimensional vector, see vec.h

/**
 * Standard macro to report errors
 */
inline void MGL_ERROR(const char* description) {
    printf("%s\n", description);
    exit(1);
}

vec3 current_color = {1,1,1};

struct vertex{
    vec3 color;
    vec4 pos;
    MGLfloat w0;

    vertex(){
        color = current_color;
        pos = vec4(0,0,0,0);
        w0 = 0;
    }

    vertex(mat<MGLfloat,4,1> matrix){
        color = current_color;
        w0 = matrix.values[3];
        pos = vec4(matrix.values[0], matrix.values[1], matrix.values[2], matrix.values[3]);
        pos /= w0;
    }

    vertex(MGLfloat x, MGLfloat y, MGLfloat z, MGLfloat w){
        color = current_color;
        w0 = 1;
        pos = vec4(x,y,z,w);
    }

    // converts verticies to pixels location
    void convert(MGLsize width, MGLsize height){
        pos[0] = width/2 * (1+pos[0]);
        pos[1] = height/2 * (1+pos[1]);
    }
};

MGLfloat area(vertex a, vertex b, vertex c){
    return a.pos[0]*(b.pos[1]-c.pos[1]) + a.pos[1]*(c.pos[0]-b.pos[0]) + (b.pos[0]*c.pos[1]-b.pos[1]*c.pos[0]);
}

struct triangle{
    vertex a, b, c;

    triangle(vertex A, vertex B, vertex C){
        a=A;
        b=B;
        c=C;
    }

    void convert(MGLfloat width, MGLfloat height){
        a.convert(width, height);
        b.convert(width, height);
        c.convert(width, height);
    }

    void rasterize(MGLsize width, MGLsize height, MGLpixel *data, MGLfloat *buffer){
        convert(width, height);
        
        // clipping and other vaiables
        int xmin = max(min(min(a.pos[0], b.pos[0]), c.pos[0]),static_cast<float>(0));
        int xmax = min(max(max(a.pos[0], b.pos[0]), c.pos[0]),static_cast<float>(width));
        int ymin = max(min(min(a.pos[1], b.pos[1]), c.pos[1]),static_cast<float>(0));
        int ymax = min(max(max(a.pos[1], b.pos[1]), c.pos[1]),static_cast<float>(height));
        MGLfloat alpha, beta, gamma;
        vertex p;

        for(int x = xmin; x < xmax; x++){
            for(int y = ymin; y < ymax; y++){
                p.pos = {static_cast<float>(x+.5),static_cast<float>(y+.5),0,1};
                
                // barycentric coodinates
                alpha = (area(p,b,c)/a.w0) / ((area(p,b,c)/a.w0) + (area(a,p,c)/b.w0) + (area(a,b,p)/c.w0));
                beta = (area(a,p,c)/b.w0) / ((area(p,b,c)/a.w0) + (area(a,p,c)/b.w0) + (area(a,b,p)/c.w0));
                gamma = (area(a,b,p)/c.w0) / ((area(p,b,c)/a.w0) + (area(a,p,c)/b.w0) + (area(a,b,p)/c.w0));
                p.color = alpha*a.color + beta*b.color + gamma*c.color;
                
                // pos of z used for z clipping
                p.pos[2] = alpha*a.pos[2] + beta*b.pos[2] + gamma*c.pos[2];

                // clip rasty check
                if((alpha < 0 || beta < 0 || gamma < 0 || alpha+beta > 1 || alpha+gamma > 1 || beta+gamma > 1) || (p.pos[2] < -1 || p.pos[2] >= 1))
                    continue;

                // pos of z used for depth test
                p.pos[2] = alpha*a.pos[2]*a.w0 + beta*b.pos[2]*b.w0 + gamma*c.pos[2]*c.w0;

                // zbuffer
                if(p.pos[2] < buffer[static_cast<int>(y*width+x)]){
                    data[static_cast<int>(y*width+x)] = Make_Pixel(p.color[0]*255,p.color[1]*255,p.color[2]*255);
                    buffer[static_cast<int>(y*width+x)] = p.pos[2];
                }
            }
        }
    }
};

// lists of: vertecies, triangles, projections and modelviews
MGLpoly_mode draw_mode;
vector<vertex> LoV;
vector<triangle> LoT;

MGLmatrix_mode matrix_mode;
mat4 projection = {{1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1}};
mat4 modelview = {{1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1}};

vector<mat4> LoP;
vector<mat4> LoM;

// return current matrix
mat4* get_current(){
    if(matrix_mode == MGL_PROJECTION)
        return &projection;
    else 
        return &modelview;
}

/**
 * Read pixel data starting with the pixel at coordinates
 * (0, 0), up to (width,  height), into the array
 * pointed to by data.  The boundaries are lower-inclusive,
 * that is, a call with width = height = 1 would just read
 * the pixel at (0, 0).
 *
 * Rasterization and z-buffering should be performed when
 * this function is called, so that the data array is filled
 * with the actual pixel values that should be displayed on
 * the two-dimensional screen.
 */
void mglReadPixels(MGLsize width, MGLsize height, MGLpixel *data){
    MGLfloat buffer[width*height];
    for(unsigned int i = 0; i < width*height; i++){
        buffer[i] = numeric_limits<float>::max();
    }
    for(unsigned int i = 0; i < LoT.size(); i++){
        LoT[i].rasterize(width, height, data, buffer);
    }
    while(LoT.size() > 0)
        LoT.pop_back();
    while(LoM.size() > 0)
        LoM.pop_back();
    while(LoP.size() > 0)
        LoP.pop_back();
}

/**
 * Start specifying the vertices for a group of primitives,
 * whose type is specified by the given mode.
 */
void mglBegin(MGLpoly_mode mode){
    draw_mode = mode;
}


/**
 * Stop specifying the vertices for a group of primitives.
 */
void mglEnd(){
    if(draw_mode == MGL_TRIANGLES)
        for(unsigned int i = 0; i < LoV.size()/3; i++)
            LoT.push_back(triangle(LoV[i*3],LoV[i*3+1],LoV[i*3+2]));
    else
        for(unsigned int i = 0; i < LoV.size()/4; i++){
            LoT.push_back(triangle(LoV[i*3],LoV[i*3+1],LoV[i*3+2]));
            LoT.push_back(triangle(LoV[i*3],LoV[i*3+2],LoV[i*3+3]));
        }
    while(LoV.size() > 0)
        LoV.pop_back();
}

/**
 * Specify a two-dimensional vertex; the x- and y-coordinates
 * are explicitly specified, while the z-coordinate is assumed
 * to be zero.  Must appear between calls to mglBegin() and
 * mglEnd().
 */
void mglVertex2(MGLfloat x, MGLfloat y){
    mglVertex3(x, y, 0);
}

/**
 * Specify a three-dimensional vertex.  Must appear between
 * calls to mglBegin() and mglEnd().
 */
void mglVertex3(MGLfloat x, MGLfloat y, MGLfloat z){
    mat<MGLfloat,4,1> matrix = {{x,y,z,1}};
    matrix = modelview * matrix;
    matrix = projection * matrix;
    LoV.push_back(vertex(matrix));
}

/**
 * Set the current matrix mode (modelview or projection).
 */
void mglMatrixMode(MGLmatrix_mode mode){
    matrix_mode = mode;
}

/**
 * Push a copy of the current matrix onto the stack for the
 * current matrix mode.
 */
void mglPushMatrix(){
    if(matrix_mode == MGL_PROJECTION)
        LoP.push_back(projection);
    else
        LoM.push_back(modelview);
}

/**
 * Pop the top matrix from the stack for the current matrix
 * mode.
 */
void mglPopMatrix(){
    if(matrix_mode == MGL_PROJECTION){
        projection = LoP[LoP.size()-1];
        LoP.pop_back();
    }
    else{
        modelview = LoM[LoM.size()-1];
        LoM.pop_back();
    }
}

/**
 * Replace the current matrix with the identity.
 */
void mglLoadIdentity(){
    float matrix[16] = {1,0,0,0,0,1,0,0,0,0,1,0,0,0,0,1};
    mglLoadMatrix(matrix);
}

/**
 * Replace the current matrix with an arbitrary 4x4 matrix,
 * specified in column-major order.  That is, the matrix
 * is stored as:
 *
 *   ( a0  a4  a8  a12 )
 *   ( a1  a5  a9  a13 )
 *   ( a2  a6  a10 a14 )
 *   ( a3  a7  a11 a15 )
 *
 * where ai is the i'th entry of the array.
 */
void mglLoadMatrix(const MGLfloat *matrix){
    mat4* current = get_current();
    for(int i = 0; i < 16; i++)
        current->values[i] = matrix[i];
}

/**
 * Multiply the current matrix by an arbitrary 4x4 matrix,
 * specified in column-major order.  That is, the matrix
 * is stored as:
 *
 *   ( a0  a4  a8  a12 )
 *   ( a1  a5  a9  a13 )
 *   ( a2  a6  a10 a14 )
 *   ( a3  a7  a11 a15 )
 *
 * where ai is the i'th entry of the array.
 */
void mglMultMatrix(const MGLfloat *matrix){
    mat4 mhold;
    for(int i = 0; i < 16; i++)
        mhold.values[i] = matrix[i];
    mat4* current = get_current();

    *current = *current * mhold;
}

/**
 * Multiply the current matrix by the translation matrix
 * for the translation vector given by (x, y, z).
 */
void mglTranslate(MGLfloat x, MGLfloat y, MGLfloat z){
    MGLfloat matrix[16] = {1,0,0,0,0,1,0,0,0,0,1,0,x,y,z,1};
    mglMultMatrix(matrix);
}

/**
 * Multiply the current matrix by the rotation matrix
 * for a rotation of (angle) degrees about the vector
 * from the origin to the point (x, y, z).
 */
void mglRotate(MGLfloat angle, MGLfloat x, MGLfloat y, MGLfloat z){
    double fhold = sqrt((x*x)+(y*y)+(z*z));
    x/=fhold;
    y/=fhold;
    z/=fhold;
    
    angle *= (3.14159265359)/180;
    MGLfloat c = cos(angle);
    MGLfloat s = sin(angle);
    MGLfloat matrix[16] = {(x*x*(1-c))+c, (y*x*(1-c))+(z*s), (x*z*(1-c))-(y*s), 0, (x*y*(1-c))-(z*s), (y*y*(1-c))+c, (y*z*(1-c))+(x*s), 0, (x*z*(1-c))+(y*s), (y*z*(1-c))-(x*s), (z*z*(1-c))+c, 0,0,0,0,1};
    mglMultMatrix(matrix);
}

/**
 * Multiply the current matrix by the scale matrix
 * for the given scale factors.
 */
void mglScale(MGLfloat x, MGLfloat y, MGLfloat z){
    MGLfloat matrix[16] = {x,0,0,0,0,y,0,0,0,0,z,0,0,0,0,1};
    mglMultMatrix(matrix);
}

/**
 * Multiply the current matrix by the perspective matrix
 * with the given clipping plane coordinates.
 */
void mglFrustum(MGLfloat left, MGLfloat right, MGLfloat bottom, 
                MGLfloat top, MGLfloat near, MGLfloat far){
    MGLfloat matrix[16] = {2*near/(right-left), 0,0,0,0, 2*near/(top-bottom), 0,0, (right+left)/(right-left), (top+bottom)/(top-bottom), -(far+near)/(far-near), -1,0,0, -(2*far*near)/(far-near), 0};
    mglMultMatrix(matrix);
    
}

/**
 * Multiply the current matrix by the orthographic matrix
 * with the given clipping plane coordinates.
 */
void mglOrtho(MGLfloat left, MGLfloat right, MGLfloat bottom,
              MGLfloat top, MGLfloat near, MGLfloat far){
    MGLfloat matrix[16] = {2/(right-left),0,0,0,0,2/(top-bottom),0,0,0,0,-2/(far-near),0,-(right+left)/(right-left),-(top+bottom)/(top-bottom),-(far+near)/(far-near),1};
    mglMultMatrix(matrix);
}

/**
 * Set the current color for drawn shapes.
 */
void mglColor(MGLfloat red, MGLfloat green, MGLfloat blue){
    current_color = {red, green, blue};
}
