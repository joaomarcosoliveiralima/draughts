/* 
 * File:   cGame.cpp
 * Author: luizfelipe
 * 
 * Created on October 29, 2010, 11:41 PM
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

#include <stdlib.h>
#include <stdio.h>

#include "cGame.h"
#include "cPeca.h"


//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
cGame::cGame() {

  start_new_game();

  m_focus_coluna = -1;
  m_focus_linha = -1;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
cGame::~cGame() {
  //delete m_peca_branca; delete m_peca_preta;
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cGame::reset() {
  for(int i = 0; i < (int)m_game.size(); i++)
  {
    for(int j = 0; j < (int)m_game[i].size(); j++)
    {
      delete m_game[i][j];
    }
  }
  m_game.clear();
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cGame::start_new_game(bool b)
{
  m_game.clear();
  
  for(int i = 0; i < 8; i++)
  {
    vector<cPeca*> vec;
    for(int j = 0; j < 8; j++)
    {
      if(b)
      {
        if(i < 3)
          vec.push_back(new cPeca("Jogador 2", 0.9f, 0.0f, 0.0f, i+1 , j+1));
        else if (i > 4)
          vec.push_back(new cPeca("Jogador 1", 0.1f, 0.1f, 0.1f, i+1 , j+1));
        else
          vec.push_back(NULL);
      }
      else
        vec.push_back(NULL);

      b = !b;
    }
    m_game.push_back(vec);
    b = !b;
  }
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------
void cGame::draw_pecas(void)
{
  glPushMatrix();
  glTranslatef(-22.5 * 2.0f, -22.5 * 2.0f, 0.0f);
  for(int i = 0; i < (int)m_game.size(); i++)
  {
    for(int j = 0; j < (int)m_game[i].size(); j++)
    {
      cPeca *p = m_game[i][j];
      if(p) 
      {
        if(i == m_focus_linha && j == m_focus_coluna)
          p->draw(true);
        else
          p->draw(false);
      }
    }
  }
  glPopMatrix();
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

string cGame::play(string jogador, int de_linha, int de_coluna, int para_linha, int para_coluna, int &ani) {
 
  --de_linha; --de_coluna; --para_linha; --para_coluna;

  // verifica se está no mesmo lugar
  if(de_linha == para_linha && de_coluna == para_coluna)
    return "DE e PARA nao podem estar no mesmo lugar.";

  // verifica se o de eh do proprio jogador,
  // necessario atacar com um jogador seu
  if(((cPeca*)m_game[de_linha][de_coluna])->get_jogador().compare(jogador) != 0)
    return "DE precisa ser seu.";

  // verifica se o para ja existe alguma peca
  if(((cPeca*)m_game[para_linha][para_coluna]) != NULL)
    return "PARA nao pode ter alguma peca nele.";

  // andou apenas um espaco na diagonal
  if(abs(de_linha - para_linha) == 1 && abs(de_coluna - para_coluna) == 1)
  {
    // movimenta a peca
    cPeca *p = ((cPeca*)m_game[de_linha][de_coluna]);
    //p->set_t(para_linha + 1, para_coluna + 1);
    m_game[para_linha][para_coluna] = p;
    m_game[de_linha][de_coluna] = NULL;
    
    // animacao 0
    ani = 0;
  }

  // andou 2 espacos na diagonal
  else if(abs(de_linha - para_linha) == 2 && abs(de_coluna - para_coluna) == 2)
  {
    // pretende comer alguma peca
    int come_linha = (de_linha + para_linha) / 2;
    int come_coluna = (de_coluna + para_coluna) / 2;

    // verifica se existe peca para ser comida
    if(m_game[come_linha][come_coluna] == NULL)
      return "Para andar dois espacos eh necessario comer alguma peca do adversario.";

    // verifica se esta tentando comer sua propria peca
    if(((cPeca*)m_game[come_linha][come_coluna])->get_jogador().compare(jogador) == 0)
      return "Para comer alguma peca eh necessario que a peca seja do oponente.";

    // movimenta a peca
    cPeca *p = ((cPeca*)m_game[de_linha][de_coluna]);
    //p->set_t(para_linha + 1, para_coluna + 1);
    m_game[para_linha][para_coluna] = p;
    m_game[de_linha][de_coluna] = NULL;
    
    // come a peca
    //delete m_game[come_linha][come_coluna];
    //m_game[come_linha][come_coluna] = NULL;

    ani = 1;
  }

  // andou mais de 2 espacos ou não está na diagonal
  else
  {
    return "Andou mais de dois espacos ou nao andou na diagonal.";
  }

  return "";
}

//--------------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------------

//  // verifica se a origem existe
//  if(m_game[c_de][l_de] == NULL)
//    return "";
//
//  // verifica se o destino existe (nao pode existir)
//  if(m_game[c_para][l_para] != NULL)
//  {
//    ((cPeca*)m_game[c_de][l_de])->set_focus(false);
//    printf("Existe alguma peca no destino: linha %d coluna %d\n", para_linha, para_coluna);
//    return "";
//  }
//
//  // verifica se o jogador está tentando usar uma peca que nao é dele
//  if(jogador != m_game[c_de][l_de]->get_jogador())
//  {
//    ((cPeca*)m_game[c_de][l_de])->set_focus(false);
//    printf("Jogador tentando usar uma peca que nao eh dele: linha %d coluna %d\n", de_linha, de_coluna);
//    return "";
//  }
//
//  // TODO verificar se o jogador está voltando com a peca.
//
//  // verifica se ele está andando apenas 1
//  if(abs(l_de - l_para) == 1 && abs(c_de - c_para) == 1)
//  {
//    // andou apenas 1
//    // TODO anima();
//
//    cPeca *p = m_game[c_de][l_de];
//    p->set_focus(false);
//    p->set_t(c_para + 1, l_para + 1);
//    m_game[c_de][l_de] = NULL;
//    m_game[c_para][l_para] = p;
//
//    printf("Andou com a peca de: linha %d coluna %d, para: linha %d coluna %d\n", de_linha, de_coluna, para_linha, para_coluna);
//
//  }
//  else if(abs(l_de - l_para) == 2 && abs(c_de - c_para) == 2)
//  {
//    // andou 2 (come outra peca)
//    // verifica se a peca que vai comer é vazia ou se do proprio jogador
//    // TODO
//    int come_linha = (de_linha + para_linha) / 2;
//    int come_coluna = (de_coluna + para_coluna) / 2;
//
//    int l_come = come_coluna - 1;
//    int c_come = 9 - come_linha - 1;
//
//    if(m_game[c_come][l_come] != NULL)
//    {
//      return "";
//    }
//
//    cPeca *p = m_game[c_de][l_de];
//    p->set_focus(false);
//    p->set_t(c_para + 1, l_para + 1);
//    m_game[c_de][l_de] = NULL;
//    m_game[c_para][l_para] = p;
//
//    delete m_game[c_come][l_come];
//    m_game[c_come][l_come] = NULL;
//    // anima_come(de_linha, de_coluna, para_linha, para_coluna);
//  }
//  else
//  {
//    ((cPeca*)m_game[c_de][l_de])->set_focus(false);
//    return "";
//  }

