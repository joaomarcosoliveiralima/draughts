/* 
 * File:   cPeca.h
 * Author: luizfelipe
 *
 * Created on October 29, 2010, 12:15 PM
 */

#ifndef PECA_H
#define	PECA_H

#include <string>

using std::string;

class cTexture;
class cAppearance;

#include "cCoord.h"

class cPeca {
public:
  cPeca(string jogador, float r = 0.0f, float g = 0.0f, float b = 0.0f,
        float tx = 0.0f, float ty = 0.0f);
  virtual ~cPeca();

  void set_t(float tx, float ty, float tz = 1.0f) { m_t.x = tx; m_t.y = ty; m_t.z = tz;}
  void get_t(float &tx, float &ty, float &tz) { tx = m_t.x; ty = m_t.y; tz = m_t.z; }

  void draw(bool is_focus);

  string get_jogador(void) { return m_jogador; }

  void set_focus(bool b) { m_is_focus = b; }
  bool is_focus(void) { return m_is_focus; }

private:

  bool m_is_focus;
  string m_jogador;
  cCoord<float> m_t;
  cAppearance *m_app1, *m_app2;
  cTexture *m_tex1, *m_tex2;
};

#endif	/* PECA_H */

