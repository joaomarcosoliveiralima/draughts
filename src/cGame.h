/* 
 * File:   cGame.h
 * Author: luizfelipe
 *
 * Created on October 29, 2010, 11:41 PM
 */

#ifndef CGAME_H
#define	CGAME_H

#include <vector>
#include <string>
using std::vector;
using std::string;

class cPeca;

class cGame {
public:
  cGame();
  cGame(const cGame& orig);
  virtual ~cGame();

  void reset(void);

  void start_new_game(bool b = false);

  void draw_pecas(void);

  string play(string jogador, int de_linha, int de_coluna, int para_linha, int para_coluna, int &ani);

  void set_focus(int l, int c) { m_focus_linha = l - 1; m_focus_coluna = c - 1; }

  cPeca* get_peca(int linha, int coluna) { return m_game[linha - 1][coluna - 1]; }
  void set_peca(cPeca *p, int linha, int coluna) { m_game[linha - 1][coluna - 1] = p; }
  
private:

  vector< vector< cPeca* > > m_game;

  int m_focus_linha, m_focus_coluna;

};

#endif	/* CGAME_H */

