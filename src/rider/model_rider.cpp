#include "model_rider.hpp"

GLuint shaderProgram;

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

//-----------------------------------------------------------------

//Eight vertices in homogenous coordinates
//elongated cuboid , basic arm in the hierarchy;
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

int tri_idx=0;
// int tri_idx2=0;
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
glm::vec4 v_colors_black[num_vertices];
glm::vec4 v_colors_red[num_vertices];
glm::vec4 v_colors_skin[num_vertices];
glm::vec4 v_colors_blue[num_vertices];
glm::vec4 v_colors_brown[num_vertices];
glm::vec4 v_colors_eyewhite[num_vertices];

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
  }
}

void man(int a, int b, int c, int d)
{
   v_positionshands[tri_idx] = hands[a]; 
   v_positionstorsop[tri_idx] = torso_p[a]; 
   v_positionshead[tri_idx] = head_p[a]; 
   v_positionsneck[tri_idx] = neck_p[a]; 
   v_positionstorsopu[tri_idx] = torso_pu[a]; 
   v_positionshair[tri_idx] = hair_p[a]; 
   v_positionseye[tri_idx] = eye_p[a] ;
  tri_idx++;

   v_positionshands[tri_idx] = hands[b]; 
   v_positionstorsop[tri_idx] = torso_p[b]; 
   v_positionshead[tri_idx] = head_p[b]; 
   v_positionsneck[tri_idx] = neck_p[b]; 
   v_positionstorsopu[tri_idx] = torso_pu[b]; 
   v_positionshair[tri_idx] = hair_p[b]; 
   v_positionseye[tri_idx] = eye_p[b] ;
   tri_idx++;

   v_positionshands[tri_idx] = hands[c]; 
   v_positionstorsop[tri_idx] = torso_p[c];
   v_positionshead[tri_idx] = head_p[c];
   v_positionsneck[tri_idx] = neck_p[c]; 
   v_positionstorsopu[tri_idx] = torso_pu[c]; 
   v_positionshair[tri_idx] = hair_p[c]; 
   v_positionseye[tri_idx] = eye_p[c] ;
   tri_idx++;

   v_positionshands[tri_idx] = hands[a]; 
   v_positionstorsop[tri_idx] = torso_p[a]; 
   v_positionshead[tri_idx] = head_p[a]; 
   v_positionsneck[tri_idx] = neck_p[a]; 
   v_positionstorsopu[tri_idx] = torso_pu[a]; 
   v_positionshair[tri_idx] = hair_p[a]; 
   v_positionseye[tri_idx] = eye_p[a] ;
   tri_idx++;

   v_positionshands[tri_idx] = hands[c]; 
   v_positionstorsop[tri_idx] = torso_p[c]; 
   v_positionshead[tri_idx] = head_p[c]; 
   v_positionsneck[tri_idx] = neck_p[c]; 
   v_positionstorsopu[tri_idx] = torso_pu[c]; 
   v_positionshair[tri_idx] = hair_p[c]; 
   v_positionseye[tri_idx] = eye_p[c] ;
   tri_idx++;

   v_positionshands[tri_idx] = hands[d]; 
   v_positionstorsop[tri_idx] = torso_p[d]; 
   v_positionshead[tri_idx] = head_p[d]; 
   v_positionsneck[tri_idx] = neck_p[d]; 
   v_positionstorsopu[tri_idx] = torso_pu[d]; 
   v_positionshair[tri_idx] = hair_p[d]; 
   v_positionseye[tri_idx] = eye_p[d] ;
   tri_idx++;
}

// generate 12 triangles: 36 vertices and 36 colors
void initcolors(void){
  fill_color();
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
  draw_man();

  //note that the buffers are initialized in the respective constructors

  
  torso = new csX75::HNode(NULL,num_vertices,v_positionstorsopu,v_colors_blue,sizeof(v_positionstorsopu),sizeof(v_colors_blue));
  torsou = new csX75::HNode(torso,num_vertices,v_positionstorsop,v_colors_red,sizeof(v_positionstorsop),sizeof(v_colors_red));
  torsou->change_parameters(0.0/s2,-0/s,0.0/s,0.0,0.0,0.0);
  neck = new csX75::HNode(torsou,num_vertices,v_positionsneck,v_colors_skin,sizeof(v_positionsneck),sizeof(v_colors_skin));
  neck->change_parameters(0.0/s2,3/s,0.0/s,0.0,0.0,90);
  head = new csX75::HNode(neck,num_vertices,v_positionshead,v_colors_skin,sizeof(v_positionshead),sizeof(v_colors_skin));
  head->change_parameters(2/s2,0.0/s2,0.0/s2,0.0,0.0,-90);
  lefteye = new csX75::HNode(head,num_vertices,v_positionseye,v_colors_eyewhite,sizeof(v_positionseye),sizeof(v_colors_eyewhite));
  lefteye->change_parameters(-0.3/s2,2.5/s2,0.7/s2,0.0,0.0,0);
  righteye = new csX75::HNode(head,num_vertices,v_positionseye,v_colors_eyewhite,sizeof(v_positionseye),sizeof(v_colors_eyewhite));
  righteye->change_parameters(0.3/s2,2.5/s2,0.7/s2,0.0,0.0,0);
  hair = new csX75::HNode(head,num_vertices,v_positionshair,v_colors_brown,sizeof(v_positionshair),sizeof(v_colors_brown));
  hair->change_parameters(0/s2,4/s2,0/s2,0.0,0.0,0.0);
  lupperarm = new csX75::HNode(torsou,num_vertices,v_positionshands,v_colors_red,sizeof(v_positionshands),sizeof(v_colors_red));
  lupperarm->change_parameters(1/s,3/s,0.0/s,0.0,0.0,-70);
  llowerarm = new csX75::HNode(lupperarm,num_vertices,v_positionshands,v_colors_skin,sizeof(v_positionshands),sizeof(v_colors_skin));
  llowerarm->change_parameters(2/s,0.0/s,0.0/s,0.0,0.0,0);
  rupperarm = new csX75::HNode(torsou,num_vertices,v_positionshands,v_colors_red,sizeof(v_positionshands),sizeof(v_colors_red));
  rupperarm->change_parameters(-1/s,3/s,0.0/s,0.0,180.0,-70);
  rlowerarm = new csX75::HNode(rupperarm,num_vertices,v_positionshands,v_colors_skin,sizeof(v_positionshands),sizeof(v_colors_skin));
  rlowerarm->change_parameters(2/s,0.0/s,0.0/s,0.0,0.0,0);
  lthigh = new csX75::HNode(torso,num_vertices,v_positionshands,v_colors_blue,sizeof(v_positionshands),sizeof(v_colors_blue));
  lthigh->change_parameters(0.5/s,-1/s,0.0/s,0.0,0.0,-90);
  lleg = new csX75::HNode(lthigh,num_vertices,v_positionshands,v_colors_skin,sizeof(v_positionshands),sizeof(v_colors_skin));
  lleg->change_parameters(2/s,0.0/s,0.0/s,90,0.0,0);
  rthigh = new csX75::HNode(torso,num_vertices,v_positionshands,v_colors_blue,sizeof(v_positionshands),sizeof(v_colors_blue));
  rthigh->change_parameters(-0.5/s,-1/s,0.0/s,0.0,0.0,-90);
  rleg = new csX75::HNode(rthigh,num_vertices,v_positionshands,v_colors_skin,sizeof(v_positionshands),sizeof(v_colors_skin));
  rleg->change_parameters(2/s,0.0/s,0.0/s,-90,0.0,0);
  root_node = torso;
  curr_node = torso;
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

  torso->render_tree();

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
  window = glfwCreateWindow(512, 512, "Rider", NULL, NULL);
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

