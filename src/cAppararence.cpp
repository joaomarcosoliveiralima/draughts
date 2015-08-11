/* 
 * File:   cAppearance.cpp
 * Author: luizfelipe
 * 
 * Created on October 29, 2010, 2:28 AM
 */

#include "cApparance.h"

static void generate_select_color(float &r, float &g, float &b);
static void rgb_to_hls(float r, float g, float b, float &h, float &l, float &s);
static void hls_to_rgb(float h, float l, float s, float &r, float &g, float &b);
static float hue_to_rgb(float n1, float n2, float hue);

#ifndef max
#define max(a,b)            (((a) > (b)) ? (a) : (b))
#endif

#ifndef min
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#endif

#define HLSMAX 240.0f
#define RGBMAX 255.0f

#define   MTOL  1.0e-10

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

cAppearance::cAppearance() {
  m_face = GL_FRONT_AND_BACK;

  int i;
  for(i = 0; i < 3; ++i)
  {
    m_color[i] = 0.0f;
    m_ambient[i] = 0.0f;
    m_pick_ambient[i] = 1.0f;

    m_diffuse[i] = 0.0f;
    m_pick_diffuse[i] = 1.0f;

    m_specular[i] = 0.0f;
    m_pick_specular[i] = 1.0f;
  }

  m_color[3] = 1.0f;
  m_ambient[3] = 1.0f;
  m_diffuse[3] = 1.0f;
  m_specular[3] = 1.0f;

  m_pick_ambient[3] = 1.0f;
  m_pick_diffuse[3] = 1.0f;
  m_pick_specular[3] = 1.0f;

  m_shininess = 50.0f;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

cAppearance::cAppearance(GLenum face, GLfloat *color) {
  m_face = face;

  int i;
  for(i = 0; i < 3; ++i)
  {
    m_color[i] = color[i];
    m_ambient[i] = 0.3f * color[i];
    m_pick_ambient[i] = 0.7f * color[i];

    m_diffuse[i] = 0.8f * color[i];
    m_pick_diffuse[i] = 0.9f * color[i];

    m_specular[i] = 0.6f * color[i];
    m_pick_specular[i] = 0.8f * color[i];
  }

  m_color[3] = color[3];
  m_ambient[3] = color[3];
  m_diffuse[3] = color[3];
  m_specular[3] = color[3];

  m_pick_ambient[3] = color[3];
  m_pick_diffuse[3] = color[3];
  m_pick_specular[3] = color[3];

  m_shininess = 50.0f;

  generate_select_color(m_pick_ambient[0], m_pick_ambient[1], m_pick_ambient[2]);
  generate_select_color(m_pick_diffuse[0], m_pick_diffuse[1], m_pick_diffuse[2]);
  generate_select_color(m_pick_specular[0], m_pick_specular[1], m_pick_specular[2]);
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

void cAppearance::set_color(GLfloat *color) {
  int i;
  for(i = 0; i < 3; ++i)
  {
    m_color[i] = color[i];
    m_ambient[i] = 0.3f * color[i];
    m_pick_ambient[i] = 0.7f * color[i];

    m_diffuse[i] = 0.9f * color[i];
    m_pick_diffuse[i] = 0.9f * color[i];

    m_specular[i] = 0.6f * color[i];
    m_pick_specular[i] = 0.8f * color[i];
  }

  generate_select_color(m_pick_ambient[0], m_pick_ambient[1], m_pick_ambient[2]);
  generate_select_color(m_pick_diffuse[0], m_pick_diffuse[1], m_pick_diffuse[2]);
  generate_select_color(m_pick_specular[0], m_pick_specular[1], m_pick_specular[2]);
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

void cAppearance::set_alpha(GLfloat alpha) {
  m_color[3] = alpha;
  m_ambient[3] = alpha;
  m_diffuse[3] = alpha;
  m_specular[3] = alpha;

  m_pick_ambient[3] = alpha;
  m_pick_diffuse[3] = alpha;
  m_pick_specular[3] = alpha;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

void cAppearance::load(eAppearanceColorType type, float alpha) const {
  if(type == COLOR)
  {
    GLfloat ambient_mat[] = {m_ambient[0], m_ambient[1], m_ambient[2], alpha};
    glMaterialfv(m_face, GL_AMBIENT, ambient_mat);

    GLfloat diffuse_mat[] = {m_diffuse[0], m_diffuse[1], m_diffuse[2], alpha};
    glMaterialfv(m_face, GL_DIFFUSE, diffuse_mat);

    GLfloat specular_mat[] = {m_specular[0], m_specular[1], m_specular[2], alpha};
    glMaterialfv(m_face, GL_SPECULAR, specular_mat);
  }
  else if(type == PICK)
  {
    GLfloat ambient_pick_mat[] = {m_pick_ambient[0],
      m_pick_ambient[1],
      m_pick_ambient[2],
      alpha};
    glMaterialfv(m_face, GL_AMBIENT, ambient_pick_mat);

    GLfloat diffuse_pick_mat[] = {m_pick_diffuse[0],
      m_pick_diffuse[1],
      m_pick_diffuse[2],
      alpha};
    glMaterialfv(m_face, GL_DIFFUSE, diffuse_pick_mat);

    GLfloat specular_pick_mat[] = {m_pick_specular[0],
      m_pick_specular[1],
      m_pick_specular[2],
      alpha};
    glMaterialfv(m_face, GL_SPECULAR, specular_pick_mat);
  }
  else if(type == TEXTURE)
  {
    GLfloat ambient_mat[] = {0.25f, 0.25f, 0.25f, alpha};
    glMaterialfv(m_face, GL_AMBIENT, ambient_mat);

    GLfloat diffuse_mat[] = {0.8f, 0.8f, 0.8f, alpha};
    glMaterialfv(m_face, GL_DIFFUSE, diffuse_mat);

    GLfloat specular_mat[] = {0.7f, 0.7f, 0.7f, alpha};
    glMaterialfv(m_face, GL_SPECULAR, specular_mat);
  }

  glMaterialf(m_face, GL_SHININESS, m_shininess);
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

void rgb_to_hls(float r, float g, float b, float &h, float &l, float &s) {
  float cMax = max(r, max(g, b));
  float cMin = min(r, min(g, b));
  float Rdelta, Gdelta, Bdelta;

  l = ((cMax + cMin) * HLSMAX + RGBMAX) / (RGBMAX * 2.0f);

  if(cMax == cMin)
  {
    s = 0.0;
    h = HLSMAX * 2 / 3;
  }
  else
  {
    /* saturation */
    if(l <= 0.5 * HLSMAX)
      s = (((cMax - cMin) * HLSMAX) + ((cMax + cMin) / 2.0f)) / (cMax + cMin);
    else
      s = (((cMax - cMin) * HLSMAX) +
        ((2.0f * RGBMAX - cMax - cMin) / 2.0f)) / (2.0f * RGBMAX - cMax - cMin);

    /* hue */
    Rdelta = (((cMax - r)*(HLSMAX / 6.0f)) + ((cMax - cMin) / 2.0f)) / (cMax - cMin);
    Gdelta = (((cMax - g)*(HLSMAX / 6.0f)) + ((cMax - cMin) / 2.0f)) / (cMax - cMin);
    Bdelta = (((cMax - b)*(HLSMAX / 6.0f)) + ((cMax - cMin) / 2.0f)) / (cMax - cMin);

    if(r == cMax)
      h = Bdelta - Gdelta;
    else if(g == cMax)
      h = (HLSMAX / 3) + Rdelta - Bdelta;
    else /* B == cMax */
      h = ((2 * HLSMAX) / 3) + Gdelta - Rdelta;

    if(h < 0)
      h += HLSMAX;
    if(h > HLSMAX)
      h -= HLSMAX;
  }
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

void hls_to_rgb(float h, float l, float s, float &r, float &g, float &b) {
  float Magic1, Magic2;

  if(s == 0) /* achromatic case */
  {
    r = g = b = (l * RGBMAX) / HLSMAX;
  }
  else /* chromatic case */
  {
    /* set up magic numbers */
    if(l <= (HLSMAX * 0.5))
      Magic2 = (l * (HLSMAX + s) + (HLSMAX * 0.5f)) / HLSMAX;
    else
      Magic2 = l + s - ((l * s) + (HLSMAX * 0.5f)) / HLSMAX;

    Magic1 = 2 * l - Magic2;

    /* get RGB, change units from HLSMAX to RGBMAX */
    r = (hue_to_rgb(Magic1, Magic2, h + (HLSMAX / 3)) * RGBMAX + (HLSMAX / 2)) / HLSMAX;
    g = (hue_to_rgb(Magic1, Magic2, h) * RGBMAX + (HLSMAX / 2)) / HLSMAX;
    b = (hue_to_rgb(Magic1, Magic2, h - (HLSMAX / 3)) * RGBMAX + (HLSMAX / 2)) / HLSMAX;
  }
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

float hue_to_rgb(float n1, float n2, float hue) {
  /* range check: note values passed add/subtract thirds of range */
  if(hue < 0)
    hue += HLSMAX;

  if(hue > HLSMAX)
    hue -= HLSMAX;

  /* return r,g, or b value from this tridrant */
  if(hue < (HLSMAX / 6))
    return( n1 + (((n2 - n1) * hue + (HLSMAX / 12)) / (HLSMAX / 6)));
  if(hue < (HLSMAX / 2))
    return( n2);
  if(hue < ((HLSMAX * 2) / 3))
    return( n1 + (((n2 - n1)*(((HLSMAX * 2) / 3) - hue)+(HLSMAX / 12)) / (HLSMAX / 6)));
  else
    return( n1);
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

void generate_select_color(float &r, float &g, float &b) {
  float h, l, s;
  r *= 255.0f;
  g *= 255.0f;
  b *= 255.0f;

  rgb_to_hls(r, g, b, h, l, s);
  l *= 1.8f;
  if(l > 240.0)
    l = 240.0f;
  hls_to_rgb(h, l, s, r, g, b);

  r /= 255.0f;
  g /= 255.0f;
  b /= 255.0f;
}

