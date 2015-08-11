/* 
 * File:   cTexture.cpp
 * Author: luizfelipe
 * 
 * Created on October 29, 2010, 2:06 AM
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

#include "cTexture.h"
#include "imageloader.h"

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
cTexture::cTexture(const string filename) {
  glEnable(GL_TEXTURE_2D);

  m_filename = filename;

  m_mode = cTexture::TEXTURE_MODULATE;

  glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

  Image* imagem = loadBMP(filename.c_str());

  if(imagem)
  {
    glGenTextures(1, &m_texName);
    glBindTexture(GL_TEXTURE_2D, m_texName);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, 
      imagem->width, imagem->height, 0,
      GL_RGB, GL_UNSIGNED_BYTE, imagem->pixels);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    delete imagem;
  }
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cTexture::load(void) {
  glEnable(GL_TEXTURE_2D);

  if(m_mode == cTexture::TEXTURE_MODULATE)
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
  else
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

  bool istexture = false;
  GLuint* pname = &m_texName;
  glAreTexturesResident(1, pname, (GLboolean*) & istexture);
  glBindTexture(GL_TEXTURE_2D, m_texName);
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------

void cTexture::unload(void) {
  glDisable(GL_TEXTURE_2D);
}
