#ifndef PIESCAPE2_FONTMANAGER_H
#define PIESCAPE2_FONTMANAGER_H

#include "../graphics/opengl_game_renderer.h"

#include <vector>
#include <map>
#include <string>
#include <cstdlib>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iterator>

using namespace std;

//for format of .fnt file, see http://www.angelcode.com/products/bmfont/doc/file_format.html

class GlyphDrawCommand {
private:
	const int pos_ltop_x;
	const int pos_ltop_y;
	const int glyph_x;
	const int glyph_y;
	const int glyph_w;
	const int glyph_h;
	const int xoffset;
	const int yoffset;
	const int xadvance;
    const t_vec4& color;
public:
    /**
     * Create a draw command
     * @param pos_ltop_x The X coordinate of the position on the screen of the left top of the glyph
     * @param pos_ltop_y The Y coordinate of the position on the screen of the left top of the glyph
     * @param glyph_x The X coordinate of the glyph in the font image
     * @param glyph_y The Y coordinate of the glyph in the font image
     * @param glyph_w The width of the glyph (both on screen and in the font image)
     * @param glyph_h The height of the glyph (both on screen and in the font image)
     * @param color The color the glyph should have. Note that this includes the alpha (1.0f = opaque, 0.0f = transparent)
     */
    GlyphDrawCommand(const int pos_ltop_x, const int pos_ltop_y,
					 const int glyph_x, const int glyph_y,
                     const int glyph_w, const int glyph_h,
                     const t_vec4& color, const int xoffset, 
					 const int yoffset, const int xadvance);
    GlyphDrawCommand(const GlyphDrawCommand& orig);

    //these method create a NEW GlyphDrawCommand based on a transformation of this one
    GlyphDrawCommand move(int x_offset, int y_offset) const;
    GlyphDrawCommand changeColor(const t_vec4& newColor) const;
    GlyphDrawCommand changeColor(float r, float g, float b, float a) const;
    GlyphDrawCommand changeColor(float r, float g, float b) const;
    GlyphDrawCommand changeAlpha(float a) const;
	GlyphDrawCommand duplicate() const;

    const t_vec4& getColor() const;
	const int getPos_ltop_x() const;
	const int getPos_ltop_y() const;
	const int getGlyph_x() const;
	const int getGlyph_y() const;
	const int getGlyph_w() const;
	const int getGlyph_h() const;
    //TODO extend this class where needed
};

enum TextJustification { TEXT_LEFT, TEXT_CENTER, TEXT_RIGHT };
enum TextVerticalPosition { TEXT_TOP, TEXT_MIDDLE, TEXT_BOTTOM };

class FontManager {
private:
    //TODO extend this class where needed
	map<char, GlyphDrawCommand> charMap;
public:
    FontManager(Graphics* graphics);
    // virtual ~FontManager();
    
    void loadFont(const string& fontName,
                  const string& fontImageFilename,
                  const string& fontMetaFilename);

    //these method set attibutes for the next  makeGlyphDrawCommands call
    void setHpos(TextJustification hpos);
    void setVpos(TextVerticalPosition vpos);
    void setColor(const t_vec4& color);
    void setScale(const t_vec2& scale);
    void setColor(float colorR, float colorG, float colorB, float colorA);
    void setScale(float xScale, float yScale);
    void setFont(const string& fontName);

    vector<GlyphDrawCommand> makeGlyphDrawCommands(string text, int x, int y) const;
    
    void draw(const GlyphDrawCommand& glyphDraw) const;
};

#endif //PIESCAPE2_FONTMANAGER_H
