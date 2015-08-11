/*
 * File:   cAppearance.h
 * Author: luizfelipe
 *
 * Created on October 29, 2010, 2:48 AM
 */

#ifndef _APPEARANCE_H_
#define _APPEARANCE_H_

#ifdef _WIN32
#include <windows.h>
#endif
#include <GL/gl.h>

class cAppearance
{
private:
  GLenum m_face;

  GLfloat m_color[4];

  GLfloat m_ambient[4];
  GLfloat m_diffuse[4];
  GLfloat m_specular[4];
  GLfloat m_shininess;

  GLfloat m_pick_ambient[4];
  GLfloat m_pick_diffuse[4];
  GLfloat m_pick_specular[4];
  GLfloat m_pick_shininess;

public:
 cAppearance();
 cAppearance(GLenum face, GLfloat *color);
 ~cAppearance() { }

 enum eAppearanceColorType{COLOR=1, PICK, TEXTURE};

 void set_face(GLenum face) { m_face = face; }

 void set_color(GLfloat *color);

 void set_alpha(GLfloat alpha);

 const GLfloat* get_color(void) const { return &m_color[0]; }

 void load(eAppearanceColorType type = COLOR, float alpha = 1.0f) const;
};

#endif
