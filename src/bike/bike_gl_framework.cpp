#include "bike_gl_framework.hpp"
#include "hierarchy_node.hpp"

extern GLfloat c_xrot,c_yrot,c_zrot, x_trans, y_trans, z_trans, scale_factor;
extern bool enable_perspective;
extern const int n;
extern csX75::HNode* root_node,*curr_node,*curr_pair,*engine,*handle,*axisrodf,*axisrodb;
namespace csX75
{
  //! Initialize GL State
  void initGL(void)
  {
    //Set framebuffer clear color
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    //Set depth buffer furthest depth
    glClearDepth(1.0);
    //Set depth test to less-than
    glDepthFunc(GL_LESS);
    //Enable depth testing
    glEnable(GL_DEPTH_TEST);
  }
  
  //!GLFW Error Callback
  void error_callback(int error, const char* description)
  {
    std::cerr<<description<<std::endl;
  }
  
  //!GLFW framebuffer resize callback
  void framebuffer_size_callback(GLFWwindow* window, int width, int height)
  {
    //!Resize the viewport to fit the window size - draw to entire window
    glViewport(0, 0, width, height);
  }
  
  //!GLFW keyboard callback
  void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
  {
    //!Close the window if the ESC key was pressed
    if (key == GLFW_KEY_ESCAPE && (action == GLFW_PRESS||action==GLFW_REPEAT))
      glfwSetWindowShouldClose(window, GL_TRUE);
    else if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS||action==GLFW_REPEAT))
      handle->dec_ry();
    else if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS||action==GLFW_REPEAT))
      handle->inc_ry();
    else if (key == GLFW_KEY_UP && (action == GLFW_PRESS||action==GLFW_REPEAT))
      {axisrodb->inc_rz();
      axisrodf->dec_rz();
      x_trans+=0.06;
      }
    else if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS||action==GLFW_REPEAT))
      {axisrodb->dec_rz();
      axisrodf->inc_rz();
      x_trans-=0.06;
      }
    // else if (key == GLFW_KEY_X && (action == GLFW_PRESS||action==GLFW_REPEAT)){
    //   if(GLFW_MOD_SHIFT == mods){
    //     x_trans+=0.1;
    //   }
    //   if(GLFW_MOD_CONTROL == mods){
    //     x_trans-=0.1;
    //   }
    // }
    // else if (key == GLFW_KEY_Y && (action == GLFW_PRESS||action==GLFW_REPEAT)){
    //   if(GLFW_MOD_SHIFT == mods){
    //     y_trans+=0.1;
    //   }
    //   if(GLFW_MOD_CONTROL == mods){
    //     y_trans-=0.1;
    //   }
    // }
    // else if (key == GLFW_KEY_Z && (action == GLFW_PRESS||action==GLFW_REPEAT)){
      // if(GLFW_MOD_SHIFT == mods){
        // z_trans+=0.1;
      // }
      // if(GLFW_MOD_CONTROL == mods){
        // z_trans-=0.1;
      // }
    // }
    else if (key == GLFW_KEY_EQUAL && (action == GLFW_PRESS||action==GLFW_REPEAT)){
      if(GLFW_MOD_SHIFT == mods){
        scale_factor+=0.01;
      }
      if(GLFW_MOD_CONTROL == mods){
        scale_factor -= 0.01;
      }
    }
    else if (key == GLFW_KEY_P && (action == GLFW_PRESS||action==GLFW_REPEAT))
      enable_perspective = !enable_perspective;   
    else if (key == GLFW_KEY_A  && (action == GLFW_PRESS||action==GLFW_REPEAT))
      c_yrot -= 1.0;
    else if (key == GLFW_KEY_D  && (action == GLFW_PRESS||action==GLFW_REPEAT))
      c_yrot += 1.0;
    else if (key == GLFW_KEY_W  && (action == GLFW_PRESS||action==GLFW_REPEAT))
      c_xrot -= 1.0;
    else if (key == GLFW_KEY_S  && (action == GLFW_PRESS||action==GLFW_REPEAT))
      c_xrot += 1.0;        
    else if (key == GLFW_KEY_Q  && (action == GLFW_PRESS||action==GLFW_REPEAT))
      c_zrot -= 1.0;
    else if (key == GLFW_KEY_E  && (action == GLFW_PRESS||action==GLFW_REPEAT))
      c_zrot += 1.0;   
  }
};  
  


