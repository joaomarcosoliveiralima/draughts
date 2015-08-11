/* 
 * File:   cTexture.h
 * Author: luizfelipe
 *
 * Created on October 29, 2010, 2:06 AM
 */


#ifndef _TEXTURA_H_
#define _TEXTURA_H_

#include <string>

using std::string;

class cTexture
{
private:

 string m_filename;
 GLuint m_texName;
 int m_mode;
 bool m_load;

public:
 cTexture(const string filename);
 ~cTexture() {}

 enum { TEXTURE_REPLACE = 1, TEXTURE_MODULATE };

 void mode(int b) { m_mode = b; }
 int  mode(void) { return m_mode; }

 GLuint get_texName(void) { return m_texName; }
 string get_filename(void) { return m_filename; }

 void load(void);
 void unload(void);

};

#endif
