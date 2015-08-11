/*
 * File:   main.cpp
 * Author: luizfelipe
 *
 * Created on October 28, 2010, 10:56 PM
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
#include <string>
#include <stdio.h>
#include <string.h>

#include "cCoord.h"
#include "cBoard.h"
#include "cGame.h"
#include "cPeca.h"

#define TOL_ZERO  0.0e-5

using namespace std;
using std::string;
using std::vector;

// Variáveis
string erro("");

cCoord<float> cor_fundo(1.0f, 1.0f, 1.0f);

cCoord<float> pos_camera_jogador1(85.0f, 0.0f, 80.0f);
cCoord<float> pos_camera_jogador2(-85.0f, 0.0f, 80.0f);

//cCoord<float> pos_camera0(40.0f, 85.0f, 80.0f);
//cCoord<float> pos_camera1(0.0f, 100.0f, 80.0f);
//cCoord<float> pos_camera2(-40.0f, 85.0f, 80.0f);

cCoord<float> pos_camera0(0.0f, 85.0f, 80.0f);
cCoord<float> pos_camera1(0.0f, 85.0f, 80.0f);
cCoord<float> pos_camera2(0.0f, 85.0f, 80.0f);

cCoord<float> pos_center(0.0f, 0.0f, -10.0f);

cCoord<float> pos_camera_corrente;

int w_b, h_b;
float fAspect;

cBoard *board;
cGame *game;

bool vez_jogador1 = true;
bool espera = false;
bool estah_animando = false;
int de_linha = -1, de_coluna = -1, para_linha = -1, para_coluna = -1;

// animacao
const float step_peca = 0.05f;
const float step_camera = 0.8f;
const unsigned int tempo_troca = 10;

int de_linha_ani = -1, de_coluna_ani = -1, para_linha_ani = -1, para_coluna_ani = -1;

void desenha_texto(char *t, float x, float y, float z) {
  glDisable(GL_LIGHTING);
  glColor4f(1 - cor_fundo.x, 1 - cor_fundo.y, 1 - cor_fundo.z, 1.0f);
  glPushMatrix();
  glRasterPos3f(x, y, z);
  while(*t) glutBitmapCharacter(GLUT_BITMAP_TIMES_ROMAN_24, *t++);
  glPopMatrix();
  glEnable(GL_LIGHTING);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void desenha_menu(void)
{
  char att[521];
  if(vez_jogador1 && !erro.empty())
  {
    strcpy(att, erro.c_str());
    desenha_texto(att, -70, -40, 0);
  }
  else if(!vez_jogador1 && !erro.empty())
  {
    strcpy(att, erro.c_str());
    desenha_texto(att, 70, 40, 0);
  }
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void set_focus()
{
  game->set_focus(de_linha, de_coluna);
  board->set_focus(para_linha, para_coluna);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void init(void) {
  // Define a cor de fundo da janela de visualização como preta
  glClearColor(cor_fundo.x, cor_fundo.y, cor_fundo.z, 1.0f);

  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  glEnable(GL_DEPTH_TEST);
  glEnable(GL_NORMALIZE);

  glLightModeli(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);
  glLightModeli(GL_LIGHT_MODEL_LOCAL_VIEWER, GL_TRUE);

  glShadeModel(GL_SMOOTH);

  board = new cBoard();

  game = new cGame();

  pos_camera_corrente = pos_camera_jogador1;
}

// ------------------------------------------------------------------------
// ------------------------------------------------------------------------
void init_light(void)
{
  // definicoes da luz
  GLfloat ambient_light[] = {0.4f, 0.4f, 0.4f, 1.0f};
  GLfloat diffuse_light[] = {0.6f, 0.6f, 0.6f, 1.0f};
  GLfloat specular_light[] = {0.2f, 0.2f, 0.2f, 1.0f};

  GLfloat pos[] = {0.0f, 0.0f, 1.0f, 0.0f};

  glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_light);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_light);
  glLightfv(GL_LIGHT0, GL_SPECULAR, specular_light);
  glLightfv(GL_LIGHT0, GL_POSITION, pos);

  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0); // Enable only the headlight
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void render(void) {

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glClear(GL_COLOR_BUFFER_BIT);

  glEnable(GL_DEPTH_TEST);

  init_light();

  board->draw();

  game->draw_pecas();

  desenha_menu();

  glutSwapBuffers();
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cb_altera_tamanho_janela(GLsizei w, GLsizei h) {

  // Para previnir uma divisão por zero
  if(h == 0) h = 1;

  // backup
  w_b = w;
  h_b = h;

  // Especifica o tamanho da viewport
  glViewport(0, 0, w, h);

  // Calcula a correção de aspecto
  fAspect = (GLfloat)w / (GLfloat)h;

  // Especifica sistema de coordenadas de projeção
  glMatrixMode(GL_PROJECTION);
  // Inicializa sistema de coordenadas de projeção
  glLoadIdentity();

  // Especifica a projeção perspectiva
  gluPerspective(50, fAspect, 1, 500);

  // Especifica sistema de coordenadas do modelo
  glMatrixMode(GL_MODELVIEW);
  // Inicializa sistema de coordenadas do modelo
  glLoadIdentity();

  // Especifica posição do observador e do alvo
  gluLookAt(pos_camera_corrente.x, pos_camera_corrente.y, pos_camera_corrente.z,
            pos_center.x, pos_center.y, pos_center.z,
            0, 0, 1);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cb_mouse_precionado(int, int s, int x, int y) {

  if(s == 0 || estah_animando)
    return; // botão pressionado, não faz nada
  
  // realiza o pick
  
  int x_selected = x;
  int y_selected = h_b - y;

  GLuint buff[64] = {0};
  GLint hits, view[4];

  // buffer onde vai receber os valores de selecao
  glSelectBuffer(64, buff);

  // quarda a view
  glGetIntegerv(GL_VIEWPORT, view);

  // ativa o modo de selecao
  glRenderMode(GL_SELECT);

  // limpa os nomes anteriormente armazenados
  glInitNames();

  // coloca um elemento na pilha de nomes
  glPushName(0);

  // moficica a visualizacao de acordo com o cursor
  glMatrixMode(GL_PROJECTION);
  glPushMatrix();
  glLoadIdentity();

  // restringe o desenho para um area em volta do cursor
  gluPickMatrix(x_selected, y_selected, 1.0, 1.0, view);
  gluPerspective(50, (float)view[2] / (float)view[3], 0.0001, 500.0);

  // desenha na tela
  glMatrixMode(GL_MODELVIEW);

  // desenha novamente e preeche o array de nomes
  render();

  glMatrixMode(GL_PROJECTION);
  glPopMatrix();

  // retorna a quantidade de objetos selecionados
  hits = glRenderMode(GL_RENDER);

  int l, c;

  // busca linha e coluna selecionado
  l = (int)buff[5];
  c = (int)buff[6];

  // verifica se eh valida a linha e a coluna slecionada
  if(l > 0 && c > 0 && l <= 8 && c <= 8)
  {
    if((int)buff[11] == 10)
    {
      // foi selecioada uma peca
      de_linha = l;
      de_coluna = c;
    }
    else if((int)buff[4] == 20)
    {
      // foi selecionado um quadrado (espaco) do tabuleiro
      para_linha = l;
      para_coluna = c;
    }

    // atualiza foco
    set_focus();
    glutPostRedisplay();
  }


  glMatrixMode(GL_MODELVIEW);
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cb_animacao(int i)
{
  if(i == 0)
  {
    // animacao da peca andando 1 casa
    
    float tx, ty, tz;
    // busca a peca que ja se movimentou
    cPeca *p = game->get_peca(para_linha, para_coluna);
    p->get_t(tx, ty, tz);


    if(fabs(((float)tx - para_linha)) < step_peca &&
       fabs(((float)ty - para_coluna)) < step_peca)
    //if(tx == para_linha && ty == para_coluna)
    {
      // chegou no destino
      // para de animar
      estah_animando = false;
      p->set_t(para_linha, para_coluna, 1.0f);
      de_linha = de_coluna = para_linha = para_coluna = -1;
      set_focus();
      espera = true;
    }
    else
    {
      // ainda nao chegou no destino

      // verifica se soma ou subtrai
      int a = 1;
      if(para_linha - de_linha < 0)
        a = -1;
      tx = tx + (a * step_peca);

      a = 1;
      if(para_coluna - de_coluna < 0)
        a = -1;
      ty = ty + (a * step_peca);

      p->set_t(tx, ty, 1.01f);
      
      glutTimerFunc(tempo_troca, cb_animacao, 0);
    }

  }
  else if(i == 1)
  {
    // animacao da peca andando mais de uma casa e comendo uma do oponente

    float tx, ty, tz;
    // busca a peca que ja se movimentou
    cPeca *p = game->get_peca(para_linha, para_coluna);
    p->get_t(tx, ty, tz);

   if(fabs((float)tx - para_linha) < step_peca && fabs((float)ty - para_coluna) < step_peca)
    {
      // chegou no destino
      // para de animar
      estah_animando = false;
      p->set_t(para_linha, para_coluna, 1.0f);
      de_linha = de_coluna = para_linha = para_coluna = -1;
      set_focus();
      espera = true;
    }
    else
    {
      // verifica se esta passando por cima da peca que vai ser comida
      int come_linha = (de_linha + para_linha) / 2;
      int come_coluna = (de_coluna + para_coluna) / 2;
      float come_tx, come_ty, come_tz;
      cPeca *come_p = game->get_peca(come_linha, come_coluna);
      if(come_p)
      {
        come_p->get_t(come_tx, come_ty, come_tz);
        if(fabs((float)tx - come_tx) < step_peca && fabs((float)ty - come_ty) < step_peca)
        {
          // estah em cima da peca que vai ser comida
          // remove a peca
          delete come_p;
          game->set_peca(NULL, come_linha, come_coluna);
        }
      }

      // ainda nao chegou no destino

      // verifica se soma ou subtrai
      int a = 1;
      if(para_linha - de_linha < 0)
        a = -1;
      tx = tx + (a * step_peca);

      a = 1;
      if(para_coluna - de_coluna < 0)
        a = -1;
      ty = ty + (a * step_peca);

      p->set_t(tx, ty, 1.01f);

      glutTimerFunc(tempo_troca, cb_animacao, 1);
    }
  }

  else
  {
    cCoord<float> *c = NULL;
    if(i == 2 && vez_jogador1)
      c = &pos_camera0;
    else if(i == 2 && !vez_jogador1)
      c = &pos_camera2;
    else if(i == 3)
      c = &pos_camera1;
    else if(i == 4 && vez_jogador1)
      c = &pos_camera2;
    else if(i == 4 && !vez_jogador1)
      c = &pos_camera0;
    else if(i == 5 && vez_jogador1)
      c = &pos_camera_jogador2;
    else if(i == 5 && !vez_jogador1)
      c = &pos_camera_jogador1;

    if(fabs((float) pos_camera_corrente.x- c->x) < step_camera &&
       fabs((float) pos_camera_corrente.y- c->y) < step_camera)
    {
      if(i < 5)
        glutTimerFunc(tempo_troca, cb_animacao, i + 1);
      else
        vez_jogador1 = !vez_jogador1;
    }
    else
    {
      int a = 1;
      if(c->x - pos_camera_corrente.x < 0) a = -1;
      if(fabs((float) pos_camera_corrente.x- c->x) >= step_camera)
        pos_camera_corrente.x = pos_camera_corrente.x + (a * step_camera);

      a = 1;
      if(c->y - pos_camera_corrente.y < 0) a = -1;
      if(fabs((float) pos_camera_corrente.y- c->y) >= step_camera)
        pos_camera_corrente.y = pos_camera_corrente.y + (a * step_camera);

      cb_altera_tamanho_janela(w_b, h_b);

      glutTimerFunc(tempo_troca, cb_animacao, i);
    }
  }

//  if(i == 2)
//  {
//    if(fabs((float) pos_camera_corrente.x- 0.0f) < step_camera &&
//       fabs((float) pos_camera_corrente.y- 85.0f) < step_camera)
//    {
//      // chegou no meio
//      glutTimerFunc(tempo_troca, cb_animacao, 3);
//    }
//    else
//    {
//      int a = 1;
//      if(0.0f - pos_camera_corrente.x < 0)
//        a = -1;
//      pos_camera_corrente.x = pos_camera_corrente.x + (a * step_camera);
//
//      a = 1;
//      if(85.0f - pos_camera_corrente.y < 0)
//        a = -1;
//      pos_camera_corrente.y = pos_camera_corrente.y + (a * step_camera);
//
//      //pos_camera_corrente.x++;
//      //pos_camera_corrente.y++;
//
//      cb_altera_tamanho_janela(w_b, h_b);
//
//      glutTimerFunc(tempo_troca, cb_animacao, 2);
//    }
//  }
//
//  if(i == 3)
//  {
//    cCoord<float> *c;
//    if(vez_jogador1)
//      c = &pos_camera_jogador2;
//    else
//      c = &pos_camera_jogador1;
//
//    if(fabs((float) pos_camera_corrente.x- c->x) < step_camera &&
//       fabs((float) pos_camera_corrente.y- c->y) < step_camera)
//    {
//      // chegou no outro jogador
//      vez_jogador1 = !vez_jogador1;
//    }
//    else
//    {
//      int a = 1;
//      if(c->x - pos_camera_corrente.x < 0)
//        a = -1;
//      pos_camera_corrente.x = pos_camera_corrente.x + (a * step_camera);
//
//      a = 1;
//      if(c->y - pos_camera_corrente.y < 0)
//        a = -1;
//      pos_camera_corrente.y = pos_camera_corrente.y + (a * step_camera);
//
//
//      cb_altera_tamanho_janela(w_b, h_b);
//
//      glutTimerFunc(tempo_troca, cb_animacao, 3);
//    }
//  }

  //printf("animando!");
  glutPostRedisplay();
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cb_teclas_especiais(int, int, int) {
  //glutPostRedisplay();
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
void cb_teclas_normais(unsigned char key, int, int) {

  if(estah_animando)
    return;
  
  // precionada a tecla L
  if((key == 'l' || key == 'L') && !estah_animando && !espera)
  {
    // os focos de linha e coluna serao apagados
    de_linha = de_coluna = para_linha = para_coluna = -1;
    set_focus();
    erro.clear();
    glutPostRedisplay();
  }

  // precionada a tecla ENTER
  else if(key == 13 && de_linha > 0 && de_linha <= 9 && de_coluna > 0 && de_coluna <= 9 &&
    para_linha > 0 && para_linha <= 9 && para_coluna > 0 && para_coluna <= 9)
  {
    // realiza a jogada
    erro = "";
    int ani;
    if(vez_jogador1)
      erro = game->play("Jogador 1", de_linha, de_coluna, para_linha, para_coluna, ani);
    else
      erro = game->play("Jogador 2", de_linha, de_coluna, para_linha, para_coluna, ani);

    if(erro.empty())
    {
      // jogada realizada com sucesso
      espera = true;
      
      // animacao
      estah_animando = true;
   
      glutTimerFunc(tempo_troca, cb_animacao, ani);
    }
    else
    {
      // jogada possui erro.

      // TODO mostrar uma string na tela com o erro
    }

    glutPostRedisplay();
  }

  // depois de jogar, espera mais um ENTER para trocar para o proximo jogador
  else if(key == 13 && espera && !estah_animando)
  {
    // TODO animaćão de troca de usuario
    
    espera = false;

    glutTimerFunc(tempo_troca, cb_animacao, 2);
    //vez_jogador1 = !vez_jogador1;
    //cb_altera_tamanho_janela(w_b, h_b);
    //glutPostRedisplay();
  }
  
}

// -------------------------------------------------------------------------------------------------
// -------------------------------------------------------------------------------------------------
int main(int argc, char *argv[]) {
  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);

  glutInitWindowSize(800, 600);
  
  glutCreateWindow("Computacao Grafica - Trabalho 3");

  glutDisplayFunc(render);
  
  glutReshapeFunc(cb_altera_tamanho_janela);
  
  glutMouseFunc(cb_mouse_precionado);
 
  glutSpecialFunc(cb_teclas_especiais);

  glutKeyboardFunc(cb_teclas_normais);

  init();

  glutMainLoop();
}
