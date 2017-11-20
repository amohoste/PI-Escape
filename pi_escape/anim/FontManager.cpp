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

const int GlyphDrawCommand::getXoffset() const {
	return xoffset;;
}
const int GlyphDrawCommand::getYoffset() const {
	return yoffset;
}
const int GlyphDrawCommand::getXadvance() const {
	return xadvance;
}

GlyphDrawCommand GlyphDrawCommand::duplicate() const {
	return GlyphDrawCommand(pos_ltop_x, pos_ltop_y, glyph_x, glyph_y, glyph_w, glyph_h, color, xoffset, yoffset, xadvance);
}

/*
* FontManager code
*/
FontManager::FontManager(Graphics * graphics) : graphics(graphics) {

}

void FontManager::loadFont(const std::string& fontName, const std::string& fontImageFilename, const std::string& fontMetaFilename) {
	
	string path = "pi_escape/graphics/";

	map<string, pair<map<char, GlyphDrawCommand>, map<char, map<char, int>>>>::const_iterator fontIt = fonts.find(fontName);
	// Als font nog niet is ingeladen inladen in fonts
	if (fontIt == fonts.end()) {

		map<char, GlyphDrawCommand> charInfo;
		map<char, map<char, int>> kernings;

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
					GlyphDrawCommand c = GlyphDrawCommand(pos_ltop_x, pos_ltop_y, glyph_x, glyph_y, glyph_w, glyph_h, col, xoffset, yoffset, xadvance);
					c.changeColor(col[0], col[1], col[2], col[3]);

					pair<char, GlyphDrawCommand> tmp(karakter, c);
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
					map<char, map<char, int>>::iterator it = kernings.find(firstChar);
					if (it != kernings.end())
					{
						// Already map for the given character
						it->second.insert(tmp);
					}
					else {
						// Nieuwe map maken en toevoegen aan map
						map<char, int> newMap;
						newMap.insert(tmp);
						pair<char, map<char, int>> toevoegen(firstChar, newMap);
						kernings.insert(toevoegen);
					}

				}

			}
		}
		in.close();

		pair<map<char, GlyphDrawCommand>, map<char, map<char, int>>> fontPair(charInfo, kernings);

		pair<string, pair<map<char, GlyphDrawCommand>, map<char, map<char, int>>>> toevoegen(fontName, fontPair);
		fonts.insert(toevoegen);
	}

	// Initializeren glyph
	string imagePath = path + fontImageFilename;

	char * charImagePath = new char[imagePath.length() + 1];
	strcpy(charImagePath, imagePath.c_str());

	gl_glyph_init(&glGlyph, graphics, charImagePath);
	// TODO free

	// Charmap en kernings aanpassen naar huidig font
	pair<map<char, GlyphDrawCommand>, map<char, map<char, int>>> fontInfo = (fonts.find(fontName)->second);
	charMap = fontInfo.first;
	charKernings = fontInfo.second;

}

vector<GlyphDrawCommand> FontManager::makeGlyphDrawCommands(string text, int x, int y) const {
	
	vector<GlyphDrawCommand> result;
	char prevChar;
	int x1 = x;

	for (int i = 0; i < text.length(); i++) {
		char c = text[i];
		map<char, GlyphDrawCommand>::const_iterator it = charMap.find(c);
		if (it != charMap.end()) {
			GlyphDrawCommand found = (it->second);
			// Als i groter dan 0 is eerst kerning tov vorige character berekenen
			if (i > 0) {
				// Als kernings vorige karakter bevat
				map<char, map<char, int>>::const_iterator kerIt1 = charKernings.find(prevChar);
				if (kerIt1 != charKernings.end()) {
					map<char, int>::const_iterator kerIt2 = (kerIt1->second).find(c);
					if (kerIt2 != (kerIt1->second).end()) {
						x1 += kerIt2->second;
					}
				}
			}
			result.push_back(found.move(x1 + found.getXoffset(), y - found.getYoffset()));
			prevChar = c;
			x1 += found.getXadvance();
		} 
	}
	return result;
}

void FontManager::draw(const GlyphDrawCommand & glyphDraw) {
	t_vec4 col = { 1.0f, 0.0f, 0.0f, 1.0f };
	gl_glyph_draw(&glGlyph, glyphDraw.getPos_ltop_x(), glyphDraw.getPos_ltop_y(), glyphDraw.getGlyph_x(), glyphDraw.getGlyph_y(), glyphDraw.getGlyph_w(), glyphDraw.getGlyph_h(), col);
}

void FontManager::setFont(const string & fontName) {
	// Initializeren glyph
	string path = "pi_escape/graphics/";
	// TODO beter
	string imagePath = path + fontName + "72.png";

	char * charImagePath = new char[imagePath.length() + 1];
	strcpy(charImagePath, imagePath.c_str());

	gl_glyph_init(&glGlyph, graphics, charImagePath);
	// TODO free
	// TODO checken of bestaat
	GLGlyph *gl = new GLGlyph;

	// Charmap en kernings aanpassen naar huidig font
	pair<map<char, GlyphDrawCommand>, map<char, map<char, int>>> fontInfo = (fonts.find(fontName)->second);
	charMap = fontInfo.first;
	charKernings = fontInfo.second;
}
