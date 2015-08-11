/* 
 * File:   cBoard.h
 * Author: luizfelipe
 *
 * Created on October 29, 2010, 2:48 AM
 */

#ifndef TABULEIRO_H
#define	TABULEIRO_H

class cTexture;
class cAppearance;

class cBoard {
public:
  cBoard();
  cBoard(const cBoard& orig);
  virtual ~cBoard();

  void set_focus(int l, int c) { m_focus_linha = l - 1; m_focus_coluna = c - 1; }

  void draw(void);
private:

  int m_focus_linha, m_focus_coluna;
  
  cTexture *tex1, *tex2, *tex3;
  cAppearance *app1, *app2, *app3;

};

#endif	/* TABULEIRO_H */

