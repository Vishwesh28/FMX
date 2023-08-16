/*
  A program which opens a window and draws three arms in a hierarchy

  Use the arrow keys and PgUp,PgDn, 
  keys to make the arms move.

  Use the keys 1,2 and 3 to switch between arms.

  Written by - 
               Harshavardhan Kode
*/
#ifndef _MODEL_HPP_
#define _MODEL_HPP_

// Defining the ESCAPE Key Code
#define ESCAPE 27
// Defining the DELETE Key Code
#define DELETE 127

#include <vector>
#include "track_gl_framework.hpp"
#include "shader_util.hpp"
#include "glm/vec3.hpp"
#include "glm/vec4.hpp"
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "hierarchy_node.hpp"

/*// Translation Parameters
GLfloat xpos=0.0,ypos=0.0,zpos=0.0;
// Rotation Parameters
GLfloat xrot=0.0,yrot=0.0,zrot=0.0;*/
// Camera position and rotation Parameters
GLfloat c_xpos = 0.0, c_ypos = 0.0, c_zpos = 2.0;
GLfloat c_up_x = 0.0, c_up_y = 1.0, c_up_z = 0.0;
GLfloat c_xrot=0.0,c_yrot=0.0,c_zrot=0.0;
GLfloat x_trans = 0.0, y_trans = 0.0, z_trans = 0.0;
GLfloat scale_factor = 0.7;

//Running variable to toggle culling on/off
bool enable_culling=true;
//Running variable to toggle wireframe/solid modelling
bool solid=true;
//Enable/Disable perspective view
bool enable_perspective=false;
//Shader program attribs
GLuint vPosition,vColor;

const int n = 100;

//global matrix stack for hierarchical modelling
std::vector<glm::mat4> matrixStack;

csX75::HNode* root_node;
csX75::HNode* curr_node;
csX75::HNode* curr_pair;
csX75::HNode* engine; 
csX75::HNode* body;
csX75::HNode* backrodf;
csX75::HNode* backrodb;
csX75::HNode* frontrodf;
csX75::HNode* frontrodb;
csX75::HNode* handle;
csX75::HNode* wheelf[n];
csX75::HNode* wheelb[n];
csX75::HNode* axisrodf;
csX75::HNode* axisrodb;
csX75::HNode* spokesf[n];
csX75::HNode* spokesb[n];
// csX75::HNode* seat;
csX75::HNode* rod;

csX75::HNode* torso; 
csX75::HNode* torsou;
csX75::HNode* head;
csX75::HNode* hair;
csX75::HNode* lefteye;
csX75::HNode* righteye;
csX75::HNode* neck;
csX75::HNode* lupperarm;
csX75::HNode* llowerarm;
csX75::HNode* rupperarm;
csX75::HNode* rlowerarm;
csX75::HNode* lthigh;
csX75::HNode* lleg;
csX75::HNode* rthigh;
csX75::HNode* rleg;


//-------------------------------------------------------------------------

#endif
