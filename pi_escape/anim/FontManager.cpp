#include "FontManager.h"

using namespace std;

/* 
* GlyphDrawCommand code 
*/
GlyphDrawCommand GlyphDrawCommand::changeColor(float r, float g, float b) const {
    t_vec4 col;
	glmc_vec4_set(col, r, g, b, color[3]);

    return GlyphDrawCommand(pos_ltop_x, pos_ltop_y, glyph_x, glyph_y, glyph_w, glyph_h, col, xoffset, yoffset, xadvance);
}

GlyphDrawCommand GlyphDrawCommand::changeAlpha(float a) const {
	t_vec4 col;
	glmc_vec4_set(col, color[0], color[1], color[2], a);

	return GlyphDrawCommand(pos_ltop_x, pos_ltop_y, glyph_x, glyph_y, glyph_w, glyph_h, col, xoffset, yoffset, xadvance);
}

GlyphDrawCommand GlyphDrawCommand::move(int x_offset, int y_offset) const {
	return GlyphDrawCommand(pos_ltop_x + x_offset, pos_ltop_y + y_offset, glyph_x, glyph_y, glyph_w, glyph_h, color, xoffset, yoffset, xadvance);
}

GlyphDrawCommand  GlyphDrawCommand::changeColor(const t_vec4& newColor) const {
	return GlyphDrawCommand(pos_ltop_x, pos_ltop_y, glyph_x, glyph_y, glyph_w, glyph_h, newColor, xoffset, yoffset, xadvance);
}

GlyphDrawCommand  GlyphDrawCommand::changeColor(float r, float g, float b, float a) const {
	t_vec4 col;
	glmc_vec4_set(col, r, g, b,a);

	return GlyphDrawCommand(pos_ltop_x, pos_ltop_y, glyph_x, glyph_y, glyph_w, glyph_h, col, xoffset, yoffset, xadvance);
}

GlyphDrawCommand::GlyphDrawCommand(const int pos_ltop_x, const int pos_ltop_y, const int glyph_x, const int glyph_y,
                                   const int glyph_w, const int glyph_h, const t_vec4 &color, const int xoffset, const int yoffset, const int xadvance) :pos_ltop_x(pos_ltop_x), 
								   pos_ltop_y(pos_ltop_y), glyph_x(glyph_x), glyph_y(glyph_y), glyph_w(glyph_w), glyph_h(glyph_h), color(color), xoffset(xoffset), yoffset(yoffset), xadvance(xadvance) {
}

GlyphDrawCommand::GlyphDrawCommand(const GlyphDrawCommand &orig) : pos_ltop_x(orig.pos_ltop_x), pos_ltop_y(orig.pos_ltop_y), glyph_x(orig.glyph_x), glyph_y(orig.glyph_y), glyph_w(orig.glyph_w),
																   glyph_h(orig.glyph_h), color(orig.color), xoffset(orig.xoffset), yoffset(orig.yoffset), xadvance(orig.xadvance) {
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

GlyphDrawCommand GlyphDrawCommand::duplicate() const {
	return GlyphDrawCommand(pos_ltop_x, pos_ltop_y, glyph_x, glyph_y, glyph_w, glyph_h, color, xoffset, yoffset, xadvance);
}




/*
* FontManager code
*/
FontManager::FontManager(Graphics * graphics, GLGlyph glGlyph) : graphics(graphics), glGlyph(glGlyph) {
}

void FontManager::loadFont(const std::string& fontName, const std::string& fontImageFilename, const std::string& fontMetaFilename) {
	string path = "pi_escape/graphics/";
	
	// Initializeren glyph
	string imagePath = path + fontImageFilename;

	char * charImagePath = new char[imagePath.length() + 1];
	strcpy(charImagePath, imagePath.c_str());

	GLGlyph glGlyph;
	// gl_glyph_init(&glGlyph, graphics, (char*) "pi_escape/graphics/zorque72.png");
	// TODO free

	map<char, GlyphDrawCommand> charInfo;
	map<char, vector<pair<char, int>>> kernings;

	string l;
	
	ifstream in(path + fontMetaFilename);
	std::string::size_type sz; // alias voor size_t

	while (!in.eof()) {
		string line;
		getline(in, line);

		stringstream data(line);
		string item;

		if (getline(data, item, ' ')) {

			// Kijken of lijn begint met char
			if (item == "char") {

				// Nodige dingen
				char karakter;
				const int pos_ltop_x = 0;
				const int pos_ltop_y = 0;
				int glyph_x;
				int glyph_y;
				int glyph_w;
				int glyph_h;
				int xoffset;
				int yoffset;
				int xadvance;
				t_vec4 col = { 1.0f, 0.0f, 0.0f, 1.0f };

				// Waarden inlezen
				while (getline(data, item, ' ')) {

					size_t pos = item.find("=");

					string var = item.substr(0, pos);
					string value = item.substr(pos + 1);    
					int iValue = std::stoi(value, &sz);

					if (var == "id") {
						karakter = static_cast<char>(iValue);
					}
					else if (var == "x") {
						glyph_x = iValue;
					}
					else if (var == "y") {
						glyph_y = iValue;
					}
					else if (var == "width") {
						glyph_w = iValue;
					}
					else if (var == "height") {
						glyph_h = iValue;
					}
					else if (var == "xoffset") {
						xoffset = iValue;
					}
					else if (var == "yoffset") {
						yoffset = iValue;
					}
					else if (var == "xadvance") {
						xadvance = iValue;
					}
					
				}
				
				// Karakter toevoegen aan map met overeenkomstige glyphdrawcommand
				pair<char, GlyphDrawCommand> tmp(karakter, GlyphDrawCommand(pos_ltop_x, pos_ltop_y, glyph_x, glyph_y, glyph_w, glyph_h, col, xoffset, yoffset, xadvance));
				charInfo.insert(tmp);

			}
			else if (item == "kerning") {
				// Nodige dingen
				char firstChar;
				char secondChar;
				int amount;

				// Waarden inlezen
				while (getline(data, item, ' ')) {

					size_t pos = item.find("=");

					string var = item.substr(0, pos);
					string value = item.substr(pos + 1);
					int iValue = std::stoi(value, &sz);

					if (var == "first") {
						firstChar = static_cast<char>(iValue);
					}
					else if (var == "second") {
						secondChar = static_cast<char>(iValue);
					}
					else if (var == "amount") {
						amount = iValue;
					}

				}

				// Karakter toevoegen aan map met overeenkomstige glyphdrawcommand
				pair<char, int> tmp(secondChar, amount);
				map<char, vector<pair<char, int>>>::iterator it = kernings.find(firstChar);
				if (it != kernings.end())
				{
					// Already vector for the given character
					it->second.push_back(tmp);
				}
				else {
					// Nieuwe vector maken en toevoegen aan map
					vector<pair<char, int>> newVec;
					newVec.push_back(tmp);
					pair<char, vector<pair<char, int>>> toevoegen(firstChar, newVec);
					kernings.insert(toevoegen);
				}

			}

		}
	}
	in.close();
	charMap = charInfo;
}

vector<GlyphDrawCommand> FontManager::makeGlyphDrawCommands(string text, int x, int y) const {
	
	vector<GlyphDrawCommand> result;

	for (int i = 0; i < text.length(); i++) {
		char c = text[i];
		map<char, GlyphDrawCommand>::const_iterator it = charMap.find(c);
		if (it != charMap.end()) {
			result.push_back((it->second).duplicate());
		}
	}
	return result;
}

void FontManager::draw(const GlyphDrawCommand & glyphDraw) {

	// gl_glyph_draw(&glGlyph, glyphDraw.getPos_ltop_x(), glyphDraw.getPos_ltop_y(), glyphDraw.getGlyph_x(), glyphDraw.getGlyph_y(), glyphDraw.getGlyph_w(), glyphDraw.getGlyph_h(), glyphDraw.getColor());
}
