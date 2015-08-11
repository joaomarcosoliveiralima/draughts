/* 
 * File:   cPeca.cpp
 * Author: luizfelipe
 * 
 * Created on October 29, 2010, 12:15 PM
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

#include "cPeca.h"
#include "cApparance.h"

static GLUquadric* quadric = NULL;

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
cPeca::cPeca(string jogador, float r, float g, float b, float tx, float ty) {

  m_jogador = jogador;
  
  float cor[3];
  cor[0] = r; cor[1] = g; cor[2] = b;
  m_app1 = new cAppearance();
  m_app1->set_color(cor);

  m_t.x = tx;
  m_t.y = ty;
  m_t.z = 1.0f;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
cPeca::~cPeca() {
  delete m_app1;
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cPeca::draw(bool is_focus)
{
  if(!quadric)
    quadric = gluNewQuadric();

  if(is_focus)
    m_app1->load(cAppearance::PICK, 1.0);
  else
    m_app1->load(cAppearance::COLOR, 1.0);

  glPushName((int)10);
  glPushName((int)m_t.x); // push line
  glPushName((int)m_t.y); // push coluna

  glPushMatrix();
  {
    glTranslatef(m_t.x * 10.0f, m_t.y * 10.0f, m_t.z);
    glScalef(2.3, 2.3, 1);
    gluCylinder(quadric, 1.0f, 1.0f, 1.0f, 32, 32);
    gluDisk(quadric, 0.0f, 1.0f, 32, 32);
    glTranslatef(0.0f, 0.0f, 1.0f);
    gluDisk(quadric, 0.0f, 1.0f, 32, 32);
  }

  glPopName();
  glPopName();
  glPopName();

  glPopMatrix();
}

