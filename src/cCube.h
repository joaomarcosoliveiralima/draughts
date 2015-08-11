/* 
 * File:   cCube.h
 * Author: luizfelipe
 *
 * Created on October 29, 2010, 1:57 AM
 */

#ifndef _CUBO_H_
#define _CUBO_H_


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

class cubo {
private:
 
public:

  cubo(void){}

  void desenha(void) {
    glBegin(GL_QUADS); // Face posterior
    glNormal3f(0.0, 0.0, 1.0); // Normal da face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0, 1.0, 1.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0, -1.0, 1.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0, -1.0, 1.0);
    glEnd();
    glBegin(GL_QUADS); // Face frontal
    glNormal3f(0.0, 0.0, -1.0); // Normal da face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0, 1.0, -1.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0, -1.0, -1.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0, -1.0, -1.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0, 1.0, -1.0);
    glEnd();
    glBegin(GL_QUADS); // Face lateral esquerda
    glNormal3f(-1.0, 0.0, 0.0); // Normal da face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0, 1.0, 1.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0, 1.0, -1.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(-1.0, -1.0, -1.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0, -1.0, 1.0);
    glEnd();
    glBegin(GL_QUADS); // Face lateral direita
    glNormal3f(1.0, 0.0, 0.0); // Normal da face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0, -1.0, 1.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0, -1.0, -1.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0, 1.0, -1.0);
    glEnd();
    glBegin(GL_QUADS); // Face superior
    glNormal3f(0.0, 1.0, 0.0); // Normal da face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0, 1.0, -1.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(-1.0, 1.0, 1.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0, 1.0, 1.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(1.0, 1.0, -1.0);
    glEnd();
    glBegin(GL_QUADS); // Face inferior
    glNormal3f(0.0, -1.0, 0.0); // Normal da face
    glTexCoord2f(0.0f, 0.0f);
    glVertex3f(-1.0, -1.0, -1.0);
    glTexCoord2f(1.0f, 0.0f);
    glVertex3f(1.0, -1.0, -1.0);
    glTexCoord2f(1.0f, 1.0f);
    glVertex3f(1.0, -1.0, 1.0);
    glTexCoord2f(0.0f, 1.0f);
    glVertex3f(-1.0, -1.0, 1.0);
    glEnd();
  }

  void desenha_linhas_superiores(void) {

    glLineWidth(5.0f);
    glBegin(GL_LINES); // Face posterior
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);

     glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);

    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glEnd();
  }
};

#endif

