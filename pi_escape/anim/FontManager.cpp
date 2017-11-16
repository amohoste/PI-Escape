#include "FontManager.h"

using namespace std;

/* 
* GlyphDrawCommand code 
*/
GlyphDrawCommand GlyphDrawCommand::changeColor(float r, float g, float b) const {
    t_vec4 col;
	glmc_vec4_set(col, r, g, b, color[3]);

    return GlyphDrawCommand(pos_ltop_x, pos_ltop_y, glyph_x, glyph_y, glyph_w, glyph_h, col);
}

GlyphDrawCommand GlyphDrawCommand::changeAlpha(float a) const {
	t_vec4 col;
	glmc_vec4_set(col, color[0], color[1], color[2], a);

	return GlyphDrawCommand(pos_ltop_x, pos_ltop_y, glyph_x, glyph_y, glyph_w, glyph_h, col);
}

GlyphDrawCommand GlyphDrawCommand::move(int x_offset, int y_offset) const {
	return GlyphDrawCommand(pos_ltop_x + x_offset, pos_ltop_y + y_offset, glyph_x, glyph_y, glyph_w, glyph_h, color);
}

GlyphDrawCommand  GlyphDrawCommand::changeColor(const t_vec4& newColor) const {
	return GlyphDrawCommand(pos_ltop_x, pos_ltop_y, glyph_x, glyph_y, glyph_w, glyph_h, newColor);
}

GlyphDrawCommand  GlyphDrawCommand::changeColor(float r, float g, float b, float a) const {
	t_vec4 col;
	glmc_vec4_set(col, r, g, b,a);

	return GlyphDrawCommand(pos_ltop_x, pos_ltop_y, glyph_x, glyph_y, glyph_w, glyph_h, col);
}

GlyphDrawCommand::GlyphDrawCommand(const int pos_ltop_x, const int pos_ltop_y, const int glyph_x, const int glyph_y,
                                   const int glyph_w, const int glyph_h, const t_vec4 &color) : pos_ltop_x(pos_ltop_x), pos_ltop_y(pos_ltop_y), glyph_x(glyph_x), glyph_y(glyph_y), glyph_w(glyph_w), glyph_h(glyph_h), color(color) {
}

GlyphDrawCommand::GlyphDrawCommand(const GlyphDrawCommand &orig) : pos_ltop_x(orig.pos_ltop_x), pos_ltop_y(orig.pos_ltop_y), glyph_x(orig.glyph_x), glyph_y(orig.glyph_y), glyph_w(orig.glyph_w), glyph_h(orig.glyph_h), color(orig.color) {
}

const t_vec4 &GlyphDrawCommand::getColor() const {
    return color;
}

const int GlyphDrawCommand::getPos_ltop_x() const {
	return pos_ltop_x;
}

const int GlyphDrawCommand::getPos_ltop_y() const {
	return pos_ltop_y;
}

const int GlyphDrawCommand::getGlyph_x() const {
	return glyph_x;
}

const int GlyphDrawCommand::getGlyph_y() const {
	return glyph_y;
}

const int GlyphDrawCommand::getGlyph_w() const {
	return glyph_w;
}

const int GlyphDrawCommand::getGlyph_h() const {
	return glyph_h;
}

/*
* FontManager code
*/
void FontManager::loadFont(const std::string& fontName, const std::string& fontImageFilename, const std::string& fontMetaFilename) {
	
	map<char, GlyphDrawCommand> charInfo;

	string l;

	ifstream in("pi_escape/graphics/" + fontMetaFilename);
	while (!in.eof()) {
		string s;
		if (getline(in, s, ' ')) {

			if (s == "char") {

			}

		}
	}
	in.close();
}