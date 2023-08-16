#include "rider_gl_framework.hpp"
#include "hierarchy_node.hpp"

extern GLfloat c_xrot,c_yrot,c_zrot, x_trans, y_trans, z_trans, scale_factor;
extern bool enable_perspective;
extern csX75::HNode* root_node, *curr_node, *torsou, *torso,*head, *neck, * lupperarm, *llowerarm, *rupperarm, *rlowerarm, *lthigh, *lleg, *rthigh, *rleg, *curr_pair;
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
    else if (key == GLFW_KEY_B && (action == GLFW_PRESS||action==GLFW_REPEAT))
      {curr_node = torso;  
        curr_pair = NULL;}
    else if (key == GLFW_KEY_M && (action == GLFW_PRESS||action==GLFW_REPEAT))
      {curr_node = torsou;
        curr_pair = NULL;}
    else if (key == GLFW_KEY_H && (action == GLFW_PRESS||action==GLFW_REPEAT))
      {curr_node = head;
        curr_pair = NULL;}
    else if (key == GLFW_KEY_N && (action == GLFW_PRESS||action==GLFW_REPEAT))
      {curr_node = neck;
        curr_pair = NULL;}
    else if (key == GLFW_KEY_1 && (action == GLFW_PRESS||action==GLFW_REPEAT))
      {curr_node = lupperarm; 
        curr_pair = rupperarm;}
    else if (key == GLFW_KEY_2 && (action == GLFW_PRESS||action==GLFW_REPEAT))
      {curr_node = llowerarm;
        curr_pair = rlowerarm;}
    else if (key == GLFW_KEY_3 && (action == GLFW_PRESS||action==GLFW_REPEAT))
      {curr_node = lthigh;
        curr_pair = rthigh;}
    else if (key == GLFW_KEY_4 && (action == GLFW_PRESS||action==GLFW_REPEAT))
      {curr_node = lleg;
        curr_pair = rleg;}
    else if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS||action==GLFW_REPEAT) && ( curr_node == torso || curr_node == head || curr_node == neck || curr_node == llowerarm ||  curr_node == lleg))
      {curr_node->dec_ry();
        if(curr_pair!=NULL)
          curr_pair->inc_ry();}
    else if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS||action==GLFW_REPEAT) && ( curr_node == torso || curr_node == head || curr_node == neck || curr_node == llowerarm || curr_node == lleg))
      {curr_node->inc_ry();
        if(curr_pair!=NULL)
          curr_pair->dec_ry();}
    else if (key == GLFW_KEY_UP && (action == GLFW_PRESS||action==GLFW_REPEAT) && (curr_node == torso || curr_node == torsou  || curr_node == neck || curr_node == llowerarm || curr_node == lthigh ))
      {curr_node->dec_rx();
        if(curr_pair!=NULL)
          curr_pair->dec_rx();
        else if (curr_node == lleg)
          curr_pair->inc_rx();}
    else if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS||action==GLFW_REPEAT) && (curr_node == torso || curr_node == torsou|| curr_node == neck || curr_node == llowerarm || curr_node == lthigh ))
      {curr_node->inc_rx();
        if(curr_pair!=NULL)
          curr_pair->inc_rx();
        else if (curr_node == lleg)
          curr_pair->dec_rx();}
    else if (key == GLFW_KEY_PAGE_UP && (action == GLFW_PRESS||action==GLFW_REPEAT) && (curr_node == torso || curr_node == torsou || curr_node == lupperarm || curr_node == llowerarm|| curr_node == lleg))
      {curr_node->dec_rz();
        if(curr_pair!=NULL)
          curr_pair->dec_rz();}
    else if (key == GLFW_KEY_PAGE_DOWN && (action == GLFW_PRESS||action==GLFW_REPEAT) && (curr_node == torso || curr_node == torsou || curr_node== lupperarm || curr_node == llowerarm || curr_node == lleg))
      {curr_node->inc_rz();
        if(curr_pair!=NULL)
          curr_pair->inc_rz();}
    else if (key == GLFW_KEY_X && (action == GLFW_PRESS||action==GLFW_REPEAT)){
      if(GLFW_MOD_SHIFT == mods){
        x_trans+=0.1;
      }
      if(GLFW_MOD_CONTROL == mods){
        x_trans-=0.1;
      }
    }
    else if (key == GLFW_KEY_Y && (action == GLFW_PRESS||action==GLFW_REPEAT)){
      if(GLFW_MOD_SHIFT == mods){
        y_trans+=0.1;
      }
      if(GLFW_MOD_CONTROL == mods){
        y_trans-=0.1;
      }
    }
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
  


