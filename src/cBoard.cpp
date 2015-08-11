/* 
 * File:   cBoard.cpp
 * Author: luizfelipe
 * 
 * Created on October 29, 2010, 2:48 AM
 */


#ifdef WIN32
#include <Windows.h>    /* includes only in MSWindows not in UNIX */
#include <gl/gl.h>     /* OpenGL functions*/
#include <gl/glu.h>    /* OpenGL utilitary functions*/
#include <gl/glut.h>    /* OpenGL utilitary functions*/
#else
#include <GL/gl.h>     /* OpenGL functions*/
#include <GL/glu.h>    /* OpenGL utilitary functions*/
#include <GL/glut.h>    /* OpenGL utilitary functions*/
#endif

#include "cBoard.h"
#include "cCube.h"
#include "cTexture.h"
#include "cApparance.h"

cBoard::cBoard(void) {

  // TEXTURA
#ifdef WIN32
  tex3 = new cTexture("../../images/madeira.bmp");
#else
  tex3 = new cTexture("../images/madeira.bmp");
#endif
  tex3->mode(cTexture::TEXTURE_MODULATE);

#ifdef WIN32
  tex1 = new cTexture("../../images/branco_m.bmp");
#else
  tex1 = new cTexture("../images/branco_m.bmp");
#endif
  tex1->mode(cTexture::TEXTURE_MODULATE);
  
#ifdef WIN32
  tex2 = new cTexture("../../images/preto_m.bmp");
#else
  tex2 = new cTexture("../images/preto_m.bmp");
#endif
  tex2->mode(cTexture::TEXTURE_MODULATE);
  // TEXTURA

  GLfloat cor[3];

  // APARARENCIA
  cor[0] = 1.0f; cor[1] = 1.0f; cor[2] = 1.0f;
  app1 = new cAppearance();
  app1->set_color(cor);

  cor[0] = 0.0f; cor[1] = 0.0f; cor[2] = 0.0f;
  app2 = new cAppearance();
  app2->set_color(cor);

  cor[0] = 0.1f; cor[1] = 0.1f; cor[2] = 0.8f;
  app3 = new cAppearance();
  app3->set_color(cor);
  // APARENCIA

  m_focus_coluna = -1;
  m_focus_linha = -1;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
cBoard::~cBoard() {
  delete tex1; delete tex2; delete tex3;
  delete app1; delete app2; delete app3;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cBoard::draw(void)
{
  cubo c;

  glEnable(GL_LIGHTING);

 glPushMatrix();

 glTranslatef(-22.5 * 2.0f, -22.5 * 2.0f, 0.0f);
  
  bool alterna_tex = false;
  for(int i = 0; i < 10; i++)
  {
    for(int j = 0; j < 10; j++)
    {
      app3->load(cAppearance::TEXTURE, 1.0);
      
      if(i == 0 || j == 0 || i == 9 || j == 9)
        tex3->load();
      else
      {
        glPushName(20);
        glPushName(i);
        glPushName(j);

        if(i == m_focus_linha + 1 && j == m_focus_coluna + 1)
        {
          glPushMatrix();
          {
            glDisable(GL_LIGHTING);
            glColor4f(0.0f, 1.0f, 0.0f, 1.0f);
            glScalef(5.0f, 5.0f, 1.0f);
            glTranslatef(i * 2.0f, j * 2.0f, 0.10f);
            c.desenha_linhas_superiores();
            glEnable(GL_LIGHTING);
          }
          glPopMatrix();
        }

        alterna_tex ? tex1->load() : tex2->load();
      }

      glPushMatrix();
      {
        glScalef(5.0f, 5.0f, 1.0f);
        glTranslatef(i * 2.0f, j * 2.0f, 0.0f);
        c.desenha();
      }
      glPopMatrix();

      //alterna_tex ? tex1.load() : tex2.load();
      if(i == 0 || j == 0 || i == 9 || j == 9)
      {
        tex1->unload();
      }
      else
      {
        alterna_tex ? tex1->unload() : tex2->unload();

        glPopName();
        glPopName();
        glPopName();
        
      }

      alterna_tex = !alterna_tex;
    }

    alterna_tex = !alterna_tex;
  }

  glPopMatrix();
}

