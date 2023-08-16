#include "model_track.hpp"


int SCR_WID = 1920;
int SCR_HEI = 1080;

float r = 1.3;
float R = 2.1;

GLuint shaderProgram;

GLuint  VAO, VBO;

glm::mat4 rotation_matrix;
glm::mat4 projection_matrix;
glm::mat4 c_rotation_matrix;
glm::mat4 lookat_matrix;
glm::mat4 translation_matrix;
glm::mat4 scale_matrix;

glm::mat4 model_matrix;
glm::mat4 view_matrix;

glm::mat4 modelview_matrix;

GLuint uModelViewMatrix;
const int num_vertices = 36;
float s = 1.5;
float s2 = 2*s;

// glm::vec4 vertices[2] = {
    // glm::vec4(2.0, 0.0, 0.0, 1.0),
    // glm::vec4(1.0, 0.0, 0.0, 1.0)
// };
// 

//-----------------------------------------------------------------

//Eight vertices in homogenous coordinates
//elongated cuboid , basic arm in the hierarchy;
glm::vec4 body_p[8] = {
  glm::vec4(-1.0/s, 0.0/s, 0.7/s, 1.0),
  glm::vec4(-3.0/s, 2.6/s, 0.7/s, 1.0),
  glm::vec4(3.0/s, 2.6/s, 0.7/s, 1.0),
  glm::vec4(1.0/s, 0.0/s, 0.7/s, 1.0),
  glm::vec4(-1.0/s, 0.0/s, -0.7/s, 1.0),
  glm::vec4(-3.0/s, 2.6/s, -0.7/s, 1.0),
  glm::vec4(3.0/s, 2.6/s, -0.7/s, 1.0),
  glm::vec4(1.0/s, 0.0/s, -0.7/s, 1.0)
};

glm::vec4 engine_p[8] = {
  glm::vec4(-0.0/s, -1.4/s, 0.5/s, 1.0),
  glm::vec4(-1.0/s, -0.1/s, 0.5/s, 1.0),
  glm::vec4(1.0/s, -0.1/s, 0.5/s, 1.0),
  glm::vec4(0.0/s, -1.4/s, 0.5/s, 1.0),
  glm::vec4(-0.0/s, -1.4/s, -0.5/s, 1.0),
  glm::vec4(-1.0/s, -0.1/s, -0.5/s, 1.0),
  glm::vec4(1.0/s, -0.1/s, -0.5/s, 1.0),
  glm::vec4(0.0/s, -1.4/s, -0.5/s, 1.0)
};

glm::vec4 backrod_f[8] = {
  glm::vec4(0.0/s, -0.25/s, 0.95/s, 1.0),
  glm::vec4(0.0/s, 0.25/s, 0.95/s, 1.0),
  glm::vec4(4.0/s, 0.25/s, 0.95/s, 1.0),
  glm::vec4(4.0/s, -0.25/s, 0.95/s, 1.0),
  glm::vec4(0.0/s, -0.25/s, 0.45/s, 1.0),
  glm::vec4(0.0/s, 0.25/s, 0.45/s, 1.0),
  glm::vec4(4.0/s, 0.25/s, 0.45/s, 1.0),
  glm::vec4(4.0/s, -0.25/s, 0.45/s, 1.0)
};

glm::vec4 backrod_b[8] = {
  glm::vec4(0.0/s, -0.25/s, -0.95/s, 1.0),
  glm::vec4(0.0/s, 0.25/s, -0.95/s, 1.0),
  glm::vec4(4.0/s, 0.25/s, -0.95/s, 1.0),
  glm::vec4(4.0/s, -0.25/s, -0.95/s, 1.0),
  glm::vec4(0.0/s, -0.25/s, -0.45/s, 1.0),
  glm::vec4(0.0/s, 0.25/s, -0.45/s, 1.0),
  glm::vec4(4.0/s, 0.25/s, -0.45/s, 1.0),
  glm::vec4(4.0/s, -0.25/s, -0.45/s, 1.0)
};

glm::vec4 frontrod_f[8] = {
  glm::vec4(0.0/s, -0.25/s, 0.95/s, 1.0),
  glm::vec4(0.0/s, 0.25/s, 0.95/s, 1.0),
  glm::vec4(6.0/s, 0.25/s, 0.95/s, 1.0),
  glm::vec4(6.0/s, -0.25/s, 0.95/s, 1.0),
  glm::vec4(0.0/s, -0.25/s, 0.45/s, 1.0),
  glm::vec4(0.0/s, 0.25/s, 0.45/s, 1.0),
  glm::vec4(6.0/s, 0.25/s, 0.45/s, 1.0),
  glm::vec4(6.0/s, -0.25/s, 0.45/s, 1.0)
};

glm::vec4 frontrod_b[8] = {
  glm::vec4(0.0/s, -0.25/s, -0.95/s, 1.0),
  glm::vec4(0.0/s, 0.25/s, -0.95/s, 1.0),
  glm::vec4(6.0/s, 0.25/s, -0.95/s, 1.0),
  glm::vec4(6.0/s, -0.25/s, -0.95/s, 1.0),
  glm::vec4(0.0/s, -0.25/s, -0.45/s, 1.0),
  glm::vec4(0.0/s, 0.25/s, -0.45/s, 1.0),
  glm::vec4(6.0/s, 0.25/s, -0.45/s, 1.0),
  glm::vec4(6.0/s, -0.25/s, -0.45/s, 1.0)
};

glm::vec4 handle_p[8] = {
  glm::vec4(0.0/s, -0.125/s, 2.0/s, 1.0),
  glm::vec4(0.0/s, 0.125/s, 2.0/s, 1.0),
  glm::vec4(0.25/s, 0.125/s, 2.0/s, 1.0),
  glm::vec4(0.25/s, -0.125/s, 2.0/s, 1.0),
  glm::vec4(0.0/s, -0.125/s, -2.0/s, 1.0),
  glm::vec4(0.0/s, 0.125/s, -2.0/s, 1.0),
  glm::vec4(0.25/s, 0.125/s, -2.0/s, 1.0),
  glm::vec4(0.25/s, -0.125/s, -2.0/s, 1.0)
};

glm::vec4 rod_p[8] = {
  glm::vec4(0.0/s, -0.25/s, 0.95/s, 1.0),
  glm::vec4(0.0/s, 0.25/s, 0.95/s, 1.0),
  glm::vec4(2.25/s, 0.25/s, 0.95/s, 1.0),
  glm::vec4(2.25/s, -0.25/s, 0.95/s, 1.0),
  glm::vec4(0.0/s, -0.25/s, 0.45/s, 1.0),
  glm::vec4(0.0/s, 0.25/s, 0.45/s, 1.0),
  glm::vec4(2.25/s, 0.25/s, 0.45/s, 1.0),
  glm::vec4(2.25/s, -0.25/s, 0.45/s, 1.0)
};

glm::vec4 tyre_p[8] = {
 glm::vec4(r*glm::cos(M_PI/n)/s, -r*glm::sin(M_PI/n)/s, 0.2/s, 1.0),
 glm::vec4(r*glm::cos(M_PI/n)/s, r*glm::sin(M_PI/n)/s, 0.2/s, 1.0),
 glm::vec4(R*glm::cos(M_PI/n)/s, R*glm::sin(M_PI/n)/s, 0.4/s, 1.0),
 glm::vec4(R*glm::cos(M_PI/n)/s, -R*glm::sin(M_PI/n)/s, 0.4/s, 1.0),
 glm::vec4(r*glm::cos(M_PI/n)/s, -r*glm::sin(M_PI/n)/s, -0.2/s, 1.0),
 glm::vec4(r*glm::cos(M_PI/n)/s, r*glm::sin(M_PI/n)/s, -0.2/s, 1.0),
 glm::vec4(R*glm::cos(M_PI/n)/s, R*glm::sin(M_PI/n)/s, -0.4/s, 1.0),
 glm::vec4(R*glm::cos(M_PI/n)/s, -R*glm::sin(M_PI/n)/s, -0.4/s, 1.0)
};

glm::vec4 axis_rod[8] = {
  glm::vec4(0.0/s, -0.125/s, 0.45/s, 1.0),
  glm::vec4(0.0/s, 0.125/s, 0.45/s, 1.0),
  glm::vec4(0.25/s, 0.125/s, 0.45/s, 1.0),
  glm::vec4(0.25/s, -0.125/s, 0.45/s, 1.0),
  glm::vec4(0.0/s, -0.125/s, -0.45/s, 1.0),
  glm::vec4(0.0/s, 0.125/s, -0.45/s, 1.0),
  glm::vec4(0.25/s, 0.125/s, -0.45/s, 1.0),
  glm::vec4(0.25/s, -0.125/s, -0.45/s, 1.0)
};

glm::vec4 spoke[8] = {
  glm::vec4(-0.05/s, -r/s, 0.05/s, 1.0),
  glm::vec4(-0.05/s, r/s, 0.05/s, 1.0),
  glm::vec4(0.05/s, r/s, 0.05/s, 1.0),
  glm::vec4(0.05/s, -r/s, 0.05/s, 1.0),
  glm::vec4(-0.05/s, -r/s, -0.05/s, 1.0),
  glm::vec4(-0.05/s, r/s, -0.05/s, 1.0),
  glm::vec4(0.05/s, r/s, -0.05/s, 1.0),
  glm::vec4(0.05/s, -r/s, -0.05/s, 1.0)
};

//-----------------------------------------------------------------------------//

glm::vec4 torso_p[8] = {
  glm::vec4(-0.7/s, 0.0/s, 0.5/s, 1.0),
  glm::vec4(-1.0/s, 3.0/s, 0.5/s, 1.0),
  glm::vec4(1.0/s, 3.0/s, 0.5/s, 1.0),
  glm::vec4(0.7/s, 0.0/s, 0.5/s, 1.0),
  glm::vec4(-0.7/s, 0.0/s, -0.5/s, 1.0),
  glm::vec4(-1.0/s, 3.0/s, -0.5/s, 1.0),
  glm::vec4(1.0/s, 3.0/s, -0.5/s, 1.0),
  glm::vec4(0.7/s, 0.0/s, -0.5/s, 1.0)
};

glm::vec4 torso_pu[8] = {
  glm::vec4(-0.7/s, -1.0/s, 0.5/s, 1.0),
  glm::vec4(-0.7/s, 0.0/s, 0.5/s, 1.0),
  glm::vec4(0.7/s, 0.0/s, 0.5/s, 1.0),
  glm::vec4(0.7/s, -1.0/s, 0.5/s, 1.0),
  glm::vec4(-0.7/s, -1.0/s, -0.5/s, 1.0),
  glm::vec4(-0.7/s, 0.0/s, -0.5/s, 1.0),
  glm::vec4(0.7/s, 0.0/s, -0.5/s, 1.0),
  glm::vec4(0.7/s, -1.0/s, -0.5/s, 1.0)
};

glm::vec4 hands[8] = {
  glm::vec4(0.0/s, -0.25/s, 0.25/s, 1.0),
  glm::vec4(0.0/s, 0.25/s, 0.25/s, 1.0),
  glm::vec4(2.0/s, 0.25/s, 0.25/s, 1.0),
  glm::vec4(2.0/s, -0.25/s, 0.25/s, 1.0),
  glm::vec4(0.0/s, -0.25/s, -0.25/s, 1.0),
  glm::vec4(0.0/s, 0.25/s, -0.25/s, 1.0),
  glm::vec4(2.0/s, 0.25/s, -0.25/s, 1.0),
  glm::vec4(2.0/s, -0.25/s, -0.25/s, 1.0)
};

glm::vec4 head_p[8] = {
  glm::vec4(-0.6/s2, -0.0/s2, 0.7/s2, 1.0),
  glm::vec4(-1.0/s2, 4.0/s2, 0.7/s2, 1.0),
  glm::vec4(1.0/s2, 4.0/s2, 0.7/s2, 1.0),
  glm::vec4(0.6/s2, -0.0/s2, 0.7/s2, 1.0),
  glm::vec4(-0.6/s2, -0.0/s2, -0.5/s2, 1.0),
  glm::vec4(-1.0/s2, 4.0/s2, -0.5/s2, 1.0),
  glm::vec4(1.0/s2, 4.0/s2, -0.5/s2, 1.0),
  glm::vec4(0.6/s2, -0.0/s2, -0.5/s2, 1.0)
};

glm::vec4 neck_p[8] = {
  glm::vec4(0.0/s2, -0.25/s, 0.25/s, 1.0),
  glm::vec4(0.0/s2, 0.25/s, 0.25/s, 1.0),
  glm::vec4(2.0/s2, 0.25/s, 0.25/s, 1.0),
  glm::vec4(2.0/s2, -0.25/s, 0.25/s, 1.0),
  glm::vec4(0.0/s2, -0.25/s, -0.25/s, 1.0),
  glm::vec4(0.0/s2, 0.25/s, -0.25/s, 1.0),
  glm::vec4(2.0/s2, 0.25/s, -0.25/s, 1.0),
  glm::vec4(2.0/s2, -0.25/s, -0.25/s, 1.0)
};

glm::vec4 hair_p[8] = {
  glm::vec4(-1.1/s2, -0.0/s2, 0.8/s2, 1.0),
  glm::vec4(-1.1/s2, 1.0/s2, 0.8/s2, 1.0),
  glm::vec4(1.1/s2, 1.0/s2, 0.8/s2, 1.0),
  glm::vec4(1.1/s2, -0.0/s2, 0.8/s2, 1.0),
  glm::vec4(-1.1/s2, -0.0/s2, -0.5/s2, 1.0),
  glm::vec4(-1.1/s2, 1.0/s2, -0.5/s2, 1.0),
  glm::vec4(1.1/s2, 1.0/s2, -0.5/s2, 1.0),
  glm::vec4(1.1/s2, -0.0/s2, -0.5/s2, 1.0)
};

glm::vec4 eye_p[8] = {
  glm::vec4(-0.1/s2, -0.0/s2, 0.02/s2, 1.0),
  glm::vec4(-0.1/s2, 0.4/s2, 0.02/s2, 1.0),
  glm::vec4(0.1/s2, 0.4/s2, 0.02/s2, 1.0),
  glm::vec4(0.1/s2, -0.0/s2, 0.02/s2, 1.0),
  glm::vec4(-0.1/s2, -0.0/s2, -0.02/s2, 1.0),
  glm::vec4(-0.1/s2, 0.4/s2, -0.02/s2, 1.0),
  glm::vec4(0.1/s2, 0.4/s2, -0.02/s2, 1.0),
  glm::vec4(0.1/s2, -0.0/s2, -0.02/s2, 1.0)
};

//----------------------------------------------------------------------------//




//RGBA colors
glm::vec4 colorblack[1] = {
  glm::vec4(0.0, 0.0, 0.0, 1.0),
};

glm::vec4 colorred[1] = {
  glm::vec4(1.0, 0.0, 0.0, 1.0),
};

glm::vec4 colorskin[1] = {
  glm::vec4(0.9, 0.745, 0.674, 1.0),
};

glm::vec4 colorblue[1] = {
  glm::vec4(0.0, 0.0, 0.8, 1.0),
};

glm::vec4 colorbrown[1] = {
  glm::vec4(0.545, 0.27, 0.074, 1.0),
};

glm::vec4 coloreyewhite[1] = {
  glm::vec4(0.3, 0.3, 0.3, 1.0),
};

glm::vec4 colorgrey[1] = {
  glm::vec4(0.5, 0.5, 0.5, 1.0),
};

glm::vec4 colorgreen[1] = {
  glm::vec4(0.0, 0.5, 0.0, 1.0),
};

glm::vec4 coloryellow[1] = {
  glm::vec4(0.9, 0.9, 0.0, 1.0),
};


int tri_idx_bike=0;
int tri_idx_human=0;
int tri_idx2=0;
// int tri_idx3=0;
// int tri_idx4=0;
// int tri_idx5=0;
// int ind = 0;

glm::vec4 v_positionshands[num_vertices];
glm::vec4 v_positionstorsop[num_vertices];
glm::vec4 v_positionshead[num_vertices];
glm::vec4 v_positionsneck[num_vertices];
glm::vec4 v_positionstorsopu[num_vertices];
glm::vec4 v_positionshair[num_vertices];
glm::vec4 v_positionseye[num_vertices];

glm::vec4 v_positionsbackrod_f[num_vertices];
glm::vec4 v_positionsbackrod_b[num_vertices];
glm::vec4 v_positionsfrontrod_f[num_vertices];
glm::vec4 v_positionsfrontrod_b[num_vertices];
glm::vec4 v_positionsbody[num_vertices];
glm::vec4 v_positionsengine[num_vertices];
glm::vec4 v_positionshandle[num_vertices];
glm::vec4 v_positionstyre[num_vertices];
glm::vec4 v_positionsaxis_rod[num_vertices];
glm::vec4 v_positionsspoke[num_vertices];
glm::vec4 v_positionsrod[num_vertices]; 




glm::vec4 v_colors_black[num_vertices];
glm::vec4 v_colors_red[num_vertices];
glm::vec4 v_colors_skin[num_vertices];
glm::vec4 v_colors_blue[num_vertices];
glm::vec4 v_colors_brown[num_vertices];
glm::vec4 v_colors_eyewhite[num_vertices];
glm::vec4 v_colors_grey[num_vertices];
glm::vec4 v_colors_green[num_vertices];
glm::vec4 v_colors_yellow[num_vertices];

// quad generates two triangles for each face and assigns colors to the vertices

void fill_color()
{
  for(int i=0; i<num_vertices; i++)
  {
    v_colors_black[i] = colorblack[0];
    v_colors_red[i] = colorred[0];
    v_colors_skin[i] = colorskin[0];
    v_colors_blue[i] = colorblue[0];
    v_colors_brown[i] = colorbrown[0];
    v_colors_eyewhite[i] = coloreyewhite[0];
    v_colors_grey[i] = colorgrey[0];
    v_colors_green[i] = colorgreen[0];
    v_colors_yellow[i] = coloryellow[0];
  }
}

void bike(int a, int b, int c, int d)
{
  v_positionsbackrod_f[tri_idx_bike] = backrod_f[a];
  v_positionsbackrod_b[tri_idx_bike] = backrod_b[a];
  v_positionsfrontrod_f[tri_idx_bike] = frontrod_f[a];
  v_positionsfrontrod_b[tri_idx_bike] = frontrod_b[a];
  v_positionshandle[tri_idx_bike] = handle_p[a];
  v_positionsbody[tri_idx_bike] = body_p[a];
  v_positionsengine[tri_idx_bike] = engine_p[a]; 
  v_positionsaxis_rod[tri_idx_bike] = axis_rod[a];
  v_positionsspoke[tri_idx_bike] = spoke[a];
  v_positionsrod[tri_idx_bike] = rod_p[a];
  tri_idx_bike++;
  v_positionsbackrod_f[tri_idx_bike] = backrod_f[b]; 
  v_positionsbackrod_b[tri_idx_bike] = backrod_b[b];
  v_positionsfrontrod_f[tri_idx_bike] = frontrod_f[b];
  v_positionsfrontrod_b[tri_idx_bike] = frontrod_b[b];
  v_positionshandle[tri_idx_bike] = handle_p[b];
  v_positionsbody[tri_idx_bike] = body_p[b]; 
  v_positionsengine[tri_idx_bike] = engine_p[b]; 
  v_positionsaxis_rod[tri_idx_bike] = axis_rod[b];
  v_positionsspoke[tri_idx_bike] = spoke[b];
  v_positionsrod[tri_idx_bike] = rod_p[b];
  tri_idx_bike++;
  v_positionsbackrod_f[tri_idx_bike] = backrod_f[c];
  v_positionsbackrod_b[tri_idx_bike] = backrod_b[c];
  v_positionsfrontrod_f[tri_idx_bike] = frontrod_f[c];
  v_positionsfrontrod_b[tri_idx_bike] = frontrod_b[c];
  v_positionshandle[tri_idx_bike] = handle_p[c];
  v_positionsbody[tri_idx_bike] = body_p[c]; 
  v_positionsengine[tri_idx_bike] = engine_p[c]; 
  v_positionsaxis_rod[tri_idx_bike] = axis_rod[c];
  v_positionsspoke[tri_idx_bike] = spoke[c];
  v_positionsrod[tri_idx_bike] = rod_p[c];
  tri_idx_bike++;
  v_positionsbackrod_f[tri_idx_bike] = backrod_f[a]; 
  v_positionsbackrod_b[tri_idx_bike] = backrod_b[a];
  v_positionsfrontrod_f[tri_idx_bike] = frontrod_f[a];
  v_positionsfrontrod_b[tri_idx_bike] = frontrod_b[a];
  v_positionshandle[tri_idx_bike] = handle_p[a];
  v_positionsbody[tri_idx_bike] = body_p[a]; 
  v_positionsengine[tri_idx_bike] = engine_p[a]; 
  v_positionsaxis_rod[tri_idx_bike] = axis_rod[a];
  v_positionsspoke[tri_idx_bike] = spoke[a];
  v_positionsrod[tri_idx_bike] = rod_p[a];
  tri_idx_bike++;
  v_positionsbackrod_f[tri_idx_bike] = backrod_f[c]; 
  v_positionsbackrod_b[tri_idx_bike] = backrod_b[c];
  v_positionsfrontrod_f[tri_idx_bike] = frontrod_f[c];
  v_positionsfrontrod_b[tri_idx_bike] = frontrod_b[c];
  v_positionshandle[tri_idx_bike] = handle_p[c];
  v_positionsbody[tri_idx_bike] = body_p[c]; 
  v_positionsengine[tri_idx_bike] = engine_p[c]; 
  v_positionsaxis_rod[tri_idx_bike] = axis_rod[c];
  v_positionsspoke[tri_idx_bike] = spoke[c];
  v_positionsrod[tri_idx_bike] = rod_p[c];
  tri_idx_bike++;
  v_positionsbackrod_f[tri_idx_bike] = backrod_f[d]; 
  v_positionsbackrod_b[tri_idx_bike] = backrod_b[d];
  v_positionsfrontrod_f[tri_idx_bike] = frontrod_f[d];
  v_positionsfrontrod_b[tri_idx_bike] = frontrod_b[d];
  v_positionshandle[tri_idx_bike] = handle_p[d];
  v_positionsbody[tri_idx_bike] = body_p[d]; 
  v_positionsengine[tri_idx_bike] = engine_p[d]; 
  v_positionsaxis_rod[tri_idx_bike] = axis_rod[d];
  v_positionsspoke[tri_idx_bike] = spoke[d];
  v_positionsrod[tri_idx_bike] = rod_p[d];
  tri_idx_bike++;
}

void man(int a, int b, int c, int d)
{
  v_positionshands[tri_idx_human] = hands[a]; 
  v_positionstorsop[tri_idx_human] = torso_p[a]; 
  v_positionshead[tri_idx_human] = head_p[a]; 
  v_positionsneck[tri_idx_human] = neck_p[a]; 
  v_positionstorsopu[tri_idx_human] = torso_pu[a]; 
  v_positionshair[tri_idx_human] = hair_p[a]; 
  v_positionseye[tri_idx_human] = eye_p[a] ;
  tri_idx_human++;

  v_positionshands[tri_idx_human] = hands[b]; 
  v_positionstorsop[tri_idx_human] = torso_p[b]; 
  v_positionshead[tri_idx_human] = head_p[b]; 
  v_positionsneck[tri_idx_human] = neck_p[b]; 
  v_positionstorsopu[tri_idx_human] = torso_pu[b]; 
  v_positionshair[tri_idx_human] = hair_p[b]; 
  v_positionseye[tri_idx_human] = eye_p[b] ;
  tri_idx_human++;

  v_positionshands[tri_idx_human] = hands[c]; 
  v_positionstorsop[tri_idx_human] = torso_p[c];
  v_positionshead[tri_idx_human] = head_p[c];
  v_positionsneck[tri_idx_human] = neck_p[c]; 
  v_positionstorsopu[tri_idx_human] = torso_pu[c]; 
  v_positionshair[tri_idx_human] = hair_p[c]; 
  v_positionseye[tri_idx_human] = eye_p[c] ;
  tri_idx_human++;

  v_positionshands[tri_idx_human] = hands[a]; 
  v_positionstorsop[tri_idx_human] = torso_p[a]; 
  v_positionshead[tri_idx_human] = head_p[a]; 
  v_positionsneck[tri_idx_human] = neck_p[a]; 
  v_positionstorsopu[tri_idx_human] = torso_pu[a]; 
  v_positionshair[tri_idx_human] = hair_p[a]; 
  v_positionseye[tri_idx_human] = eye_p[a] ;
  tri_idx_human++;

  v_positionshands[tri_idx_human] = hands[c]; 
  v_positionstorsop[tri_idx_human] = torso_p[c]; 
  v_positionshead[tri_idx_human] = head_p[c]; 
  v_positionsneck[tri_idx_human] = neck_p[c]; 
  v_positionstorsopu[tri_idx_human] = torso_pu[c]; 
  v_positionshair[tri_idx_human] = hair_p[c]; 
  v_positionseye[tri_idx_human] = eye_p[c] ;
  tri_idx_human++;

  v_positionshands[tri_idx_human] = hands[d]; 
  v_positionstorsop[tri_idx_human] = torso_p[d]; 
  v_positionshead[tri_idx_human] = head_p[d]; 
  v_positionsneck[tri_idx_human] = neck_p[d]; 
  v_positionstorsopu[tri_idx_human] = torso_pu[d]; 
  v_positionshair[tri_idx_human] = hair_p[d]; 
  v_positionseye[tri_idx_human] = eye_p[d] ;
  tri_idx_human++;
}

void tyre(int a, int b, int c, int d)
{
   v_positionstyre[tri_idx2] = tyre_p[a];
   tri_idx2++;

   v_positionstyre[tri_idx2] = tyre_p[b];
   tri_idx2++;

   v_positionstyre[tri_idx2] = tyre_p[c];
   tri_idx2++;

   v_positionstyre[tri_idx2] = tyre_p[a];
   tri_idx2++;

   v_positionstyre[tri_idx2] = tyre_p[c];
   tri_idx2++;

   v_positionstyre[tri_idx2] = tyre_p[d];
   tri_idx2++;

}

// generate 12 triangles: 36 vertices and 36 colors
void initcolors(void){
  fill_color();
}

void draw_bike(void)
{
    bike( 1, 0, 3, 2 );
    bike( 2, 3, 7, 6 );
    bike( 3, 0, 4, 7 );
    bike( 6, 5, 1, 2 );
    bike( 4, 5, 6, 7 );
    bike( 5, 4, 0, 1 );
}

void draw_man(void)
{
    man( 1, 0, 3, 2 );
    man( 2, 3, 7, 6 );
    man( 3, 0, 4, 7 );
    man( 6, 5, 1, 2 );
    man( 4, 5, 6, 7 );
    man( 5, 4, 0, 1 );
}


void draw_tyre(void)
{
    tyre( 1, 0, 3, 2 );
    tyre( 2, 3, 7, 6 );
    // tyre( 3, 0, 4, 7 );
    // tyre( 6, 5, 1, 2 );
    tyre( 4, 5, 6, 7 );
    tyre( 5, 4, 0, 1 );
}

void initBuffersGL(void)
{

  // Load shaders and use the resulting shader program
  std::string vertex_shader_file("./src/rider/vshader.glsl");
  std::string fragment_shader_file("./src/rider/fshader.glsl");

  std::vector<GLuint> shaderList;
  shaderList.push_back(csX75::LoadShaderGL(GL_VERTEX_SHADER, vertex_shader_file));
  shaderList.push_back(csX75::LoadShaderGL(GL_FRAGMENT_SHADER, fragment_shader_file));

  shaderProgram = csX75::CreateProgramGL(shaderList);
  glUseProgram( shaderProgram );

  // getting the attributes from the shader program
  vPosition = glGetAttribLocation( shaderProgram, "vPosition" );
  vColor = glGetAttribLocation( shaderProgram, "vColor" ); 
  uModelViewMatrix = glGetUniformLocation( shaderProgram, "uModelViewMatrix");

  // Creating the hierarchy:
  // We are using the original colorcube function to generate the vertices of the cuboid
  initcolors();
  draw_bike();
  draw_man();
  draw_tyre();

  //note that the buffers are initialized in the respective constructors

  
  engine = new csX75::HNode(NULL,num_vertices,v_positionsengine,v_colors_green,sizeof(v_positionsengine),sizeof(v_colors_green));
  body = new csX75::HNode(engine,num_vertices,v_positionsbody,v_colors_yellow,sizeof(v_positionsbody),sizeof(v_colors_yellow));
  body->change_parameters(0.0/s2,0.0/s,0.0/s,0.0,0.0,0.0);
  handle = new csX75::HNode(body,num_vertices,v_positionshandle,v_colors_brown,sizeof(v_positionshandle),sizeof(v_colors_brown));
  handle->change_parameters(2.7/s,3.5/s,0.0/s,0.0,0.0,0.0);
  backrodf = new csX75::HNode(body,num_vertices,v_positionsbackrod_f,v_colors_black,sizeof(v_positionsbackrod_f),sizeof(v_colors_black));
  backrodf->change_parameters(-1.0/s,1.5/s,0.0/s,0.0,180.0,-70.0);
  backrodb = new csX75::HNode(body,num_vertices,v_positionsbackrod_b,v_colors_black,sizeof(v_positionsbackrod_b),sizeof(v_colors_black));
  backrodb->change_parameters(-1.0/s,1.5/s,0.0/s,0.0,180.0,-70.0);
  frontrodf = new csX75::HNode(handle,num_vertices,v_positionsfrontrod_f,v_colors_black,sizeof(v_positionsfrontrod_f),sizeof(v_colors_black));
  frontrodf->change_parameters(0.0/s,0.0/s,0.0/s,0.0,0.0,-85.0);
  frontrodb = new csX75::HNode(handle,num_vertices,v_positionsfrontrod_b,v_colors_black,sizeof(v_positionsfrontrod_b),sizeof(v_colors_black));
  frontrodb->change_parameters(0.0/s,0.0/s,0.0/s,0.0,0.0,-85.0);
  axisrodf = new csX75::HNode(frontrodf,num_vertices,v_positionsaxis_rod,v_colors_black,sizeof(v_positionsaxis_rod),sizeof(v_colors_black));
  axisrodf->change_parameters(5.7/s,0.0/s,0.0/s,0.0,0.0,0.0);
  axisrodb = new csX75::HNode(backrodf,num_vertices,v_positionsaxis_rod,v_colors_black,sizeof(v_positionsaxis_rod),sizeof(v_colors_black));
  axisrodb->change_parameters(3.7/s,0.0/s,0.0/s,0.0,0.0,0.0);
  rod = new csX75::HNode(backrodb,num_vertices,v_positionsrod,v_colors_black,sizeof(v_positionsrod),sizeof(v_colors_black));
  rod->change_parameters(2/s,0/s,0/s,0,0,110);
  for(int i=0;i<n;i++)
  {
    wheelf[i] = new csX75::HNode(axisrodf,num_vertices,v_positionstyre,v_colors_eyewhite,sizeof(v_positionstyre),sizeof(v_colors_black));
    wheelf[i]->change_parameters(0.0/s,0.0/s,0.0/s,0.0,0.0,360.0*i/n);
  }
  for(int i=0;i<n;i++)
  {
    wheelb[i] = new csX75::HNode(axisrodb,num_vertices,v_positionstyre,v_colors_eyewhite,sizeof(v_positionstyre),sizeof(v_colors_black));
    wheelb[i]->change_parameters(0.0/s,0.0/s,0.0/s,0.0,0.0,360.0*i/n);
  }
  for(int i=0;i<n/10;i++)
  {
    spokesf[i] = new csX75::HNode(axisrodf,num_vertices,v_positionsspoke,v_colors_black,sizeof(v_positionsspoke),sizeof(v_colors_black));
    spokesf[i]->change_parameters(0.0/s,0.0/s,0.0/s,0.0,0.0,10*360.0*i/n);
  }
  for(int i=0;i<n/10;i++)
  {
    spokesb[i] = new csX75::HNode(axisrodb,num_vertices,v_positionsspoke,v_colors_black,sizeof(v_positionsspoke),sizeof(v_colors_black));
    spokesb[i]->change_parameters(0.0/s,0.0/s,0.0/s,0.0,0.0,10*360.0*i/n);
  }
  
torso = new csX75::HNode(engine,num_vertices,v_positionstorsopu,v_colors_blue,sizeof(v_positionstorsopu),sizeof(v_colors_blue));
torso->change_parameters(0.0/s,3.75/s,0/s,0.0,90,0);
torsou = new csX75::HNode(torso,num_vertices,v_positionstorsop,v_colors_red,sizeof(v_positionstorsop),sizeof(v_colors_red));
torsou->change_parameters(0.0/s2,-0/s,0.0/s,25,0,0.0);
neck = new csX75::HNode(torsou,num_vertices,v_positionsneck,v_colors_skin,sizeof(v_positionsneck),sizeof(v_colors_skin));
neck->change_parameters(0.0/s2,3/s,0.0/s,-10,0.0,90);
head = new csX75::HNode(neck,num_vertices,v_positionshead,v_colors_skin,sizeof(v_positionshead),sizeof(v_colors_skin));
head->change_parameters(2/s2,0.0/s2,0.0/s2,0.0,0.0,-90);
lefteye = new csX75::HNode(head,num_vertices,v_positionseye,v_colors_eyewhite,sizeof(v_positionseye),sizeof(v_colors_eyewhite));
lefteye->change_parameters(-0.3/s2,2.5/s2,0.7/s2,0.0,0.0,0);
righteye = new csX75::HNode(head,num_vertices,v_positionseye,v_colors_eyewhite,sizeof(v_positionseye),sizeof(v_colors_eyewhite));
righteye->change_parameters(0.3/s2,2.5/s2,0.7/s2,0.0,0.0,0);
hair = new csX75::HNode(head,num_vertices,v_positionshair,v_colors_brown,sizeof(v_positionshair),sizeof(v_colors_brown));
hair->change_parameters(0/s2,4/s2,0/s2,0.0,0.0,0.0);
lupperarm = new csX75::HNode(torsou,num_vertices,v_positionshands,v_colors_red,sizeof(v_positionshands),sizeof(v_colors_red));
lupperarm->change_parameters(1/s,3/s,0.0/s,-40,0.0,-75);
llowerarm = new csX75::HNode(lupperarm,num_vertices,v_positionshands,v_colors_skin,sizeof(v_positionshands),sizeof(v_colors_skin));
llowerarm->change_parameters(2/s,0.0/s,0.0/s,0,-30,0);
rupperarm = new csX75::HNode(torsou,num_vertices,v_positionshands,v_colors_red,sizeof(v_positionshands),sizeof(v_colors_red));
rupperarm->change_parameters(-1/s,3/s,0.0/s,-40,180,-75);
rlowerarm = new csX75::HNode(rupperarm,num_vertices,v_positionshands,v_colors_skin,sizeof(v_positionshands),sizeof(v_colors_skin));
rlowerarm->change_parameters(2/s,0.0/s,0.0/s,0,30,0);
lthigh = new csX75::HNode(torso,num_vertices,v_positionshands,v_colors_blue,sizeof(v_positionshands),sizeof(v_colors_blue));
lthigh->change_parameters(0.5/s,-1/s,0.0/s,-20,0.0,-80);
lleg = new csX75::HNode(lthigh,num_vertices,v_positionshands,v_colors_skin,sizeof(v_positionshands),sizeof(v_colors_skin));
lleg->change_parameters(2/s,0.0/s,0.0/s,0,50,-10);
rthigh = new csX75::HNode(torso,num_vertices,v_positionshands,v_colors_blue,sizeof(v_positionshands),sizeof(v_colors_blue));
rthigh->change_parameters(-0.5/s,-1/s,0.0/s,-20,0.0,-100);
rleg = new csX75::HNode(rthigh,num_vertices,v_positionshands,v_colors_skin,sizeof(v_positionshands),sizeof(v_colors_skin));
rleg->change_parameters(2/s,0.0/s,0.0/s,0,50,10);

  root_node = engine;
  curr_node = engine;
  curr_pair = NULL;

}

void renderGL(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  matrixStack.clear();

  //Creating the lookat and the up vectors for the camera
  c_rotation_matrix = glm::rotate(glm::mat4(1.0f), glm::radians(c_xrot), glm::vec3(1.0f,0.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_yrot), glm::vec3(0.0f,1.0f,0.0f));
  c_rotation_matrix = glm::rotate(c_rotation_matrix, glm::radians(c_zrot), glm::vec3(0.0f,0.0f,1.0f));

  translation_matrix = glm::translate(glm::mat4(1.0f), glm::vec3(x_trans,y_trans,z_trans));

  glm::vec4 c_pos = glm::vec4(c_xpos,c_ypos,c_zpos, 1.0)*c_rotation_matrix;
  glm::vec4 c_up = glm::vec4(c_up_x,c_up_y,c_up_z, 1.0)*c_rotation_matrix;
  //Creating the lookat matrix
  lookat_matrix = glm::lookAt(glm::vec3(c_pos),glm::vec3(0.0),glm::vec3(c_up));

  //creating the projection matrix
  if(enable_perspective)
    projection_matrix = glm::frustum(-7.0, 7.0, -7.0, 7.0, 1.0, 7.0);
    //projection_matrix = glm::perspective(glm::radians(90.0),1.0,0.1,5.0);
  else
    projection_matrix = glm::ortho(-7.0, 7.0, -7.0, 7.0, -5.0, 5.0);

  scale_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(scale_factor,scale_factor,scale_factor));

  view_matrix = scale_matrix*projection_matrix*lookat_matrix*translation_matrix;

  matrixStack.push_back(view_matrix);

  engine->render_tree();


}

int main(int argc, char** argv)
{
  //! The pointer to the GLFW window
  GLFWwindow* window;

  //! Setting up the GLFW Error callback
  glfwSetErrorCallback(csX75::error_callback);

  //! Initialize GLFW
  if (!glfwInit())
    return -1;

  //We want OpenGL 4.0
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  //This is for MacOSX - can be omitted otherwise
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
  //We don't want the old OpenGL 
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 

  //! Create a windowed mode window and its OpenGL context
  window = glfwCreateWindow(SCR_WID,SCR_HEI,"Track", NULL, NULL);
  if (!window)
    {
      glfwTerminate();
      return -1;
    }
  
  //! Make the window's context current 
  glfwMakeContextCurrent(window);

  //Initialize GLEW
  //Turn this on to get Shader based OpenGL
  glewExperimental = GL_TRUE;
  GLenum err = glewInit();
  if (GLEW_OK != err)
    {
      //Problem: glewInit failed, something is seriously wrong.
      std::cerr<<"GLEW Init Failed : %s"<<std::endl;
    }

  //Print and see what context got enabled
  std::cout<<"Vendor: "<<glGetString (GL_VENDOR)<<std::endl;
  std::cout<<"Renderer: "<<glGetString (GL_RENDERER)<<std::endl;
  std::cout<<"Version: "<<glGetString (GL_VERSION)<<std::endl;
  std::cout<<"GLSL Version: "<<glGetString (GL_SHADING_LANGUAGE_VERSION)<<std::endl;

  //Keyboard Callback
  glfwSetKeyCallback(window, csX75::key_callback);
  //Framebuffer resize callback
  glfwSetFramebufferSizeCallback(window, csX75::framebuffer_size_callback);

  // Ensure we can capture the escape key being pressed below
  glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

  //Initialize GL state
  csX75::initGL();
  initBuffersGL();

  // Loop until the user closes the window
  while (glfwWindowShouldClose(window) == 0)
    {
       
      // Render here
      renderGL();

      // Swap front and back buffers
      glfwSwapBuffers(window);
      
      // Poll for and process events
      glfwPollEvents();
    }
  
  glfwTerminate();
  return 0;
}

//-------------------------------------------------------------------------

