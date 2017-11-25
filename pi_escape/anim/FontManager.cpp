#include "FontManager.h"

using namespace std;

/***************************************************************
 GlyphDrawCommand code
****************************************************************/

GlyphDrawCommand GlyphDrawCommand::changeColor(float r, float g, float b) const {
	t_vec4& col = *new t_vec4[4];
	glmc_vec4_set(col, r, g, b, color[3]);

    return GlyphDrawCommand(pos_ltop_x, pos_ltop_y, glyph_x, glyph_y, glyph_w, glyph_h, col, xoffset, yoffset, xadvance, font);
}

GlyphDrawCommand GlyphDrawCommand::changeAlpha(float a) const {
	t_vec4& col = *new t_vec4[4];
	glmc_vec4_set(col, color[0], color[1], color[2], a);

	return GlyphDrawCommand(pos_ltop_x, pos_ltop_y, glyph_x, glyph_y, glyph_w, glyph_h, col, xoffset, yoffset, xadvance, font);
}

GlyphDrawCommand GlyphDrawCommand::move(int x_offset, int y_offset) const {
	return GlyphDrawCommand(pos_ltop_x + x_offset, pos_ltop_y + y_offset, glyph_x, glyph_y, glyph_w, glyph_h, color, xoffset, yoffset, xadvance, font);
}

GlyphDrawCommand  GlyphDrawCommand::changeColor(const t_vec4& newColor) const {
	return GlyphDrawCommand(pos_ltop_x, pos_ltop_y, glyph_x, glyph_y, glyph_w, glyph_h, newColor, xoffset, yoffset, xadvance, font);
}

GlyphDrawCommand  GlyphDrawCommand::changeColor(float r, float g, float b, float a) const {
	t_vec4& col = *new t_vec4[4];
	glmc_vec4_set(col, r, g, b,a);

	return GlyphDrawCommand(pos_ltop_x, pos_ltop_y, glyph_x, glyph_y, glyph_w, glyph_h, col, xoffset, yoffset, xadvance, font);
}

GlyphDrawCommand::GlyphDrawCommand(const int pos_ltop_x, const int pos_ltop_y, const int glyph_x, const int glyph_y,
                                   const int glyph_w, const int glyph_h, const t_vec4 &color, const int xoffset, const int yoffset, const int xadvance,string font) :pos_ltop_x(pos_ltop_x),
								   pos_ltop_y(pos_ltop_y), glyph_x(glyph_x), glyph_y(glyph_y), glyph_w(glyph_w), glyph_h(glyph_h), color(color), xoffset(xoffset), yoffset(yoffset), xadvance(xadvance), font(font) { }



GlyphDrawCommand::GlyphDrawCommand(const GlyphDrawCommand &orig) : pos_ltop_x(orig.pos_ltop_x), pos_ltop_y(orig.pos_ltop_y), glyph_x(orig.glyph_x), glyph_y(orig.glyph_y), glyph_w(orig.glyph_w),
																   glyph_h(orig.glyph_h), color(orig.color), xoffset(orig.xoffset), yoffset(orig.yoffset), xadvance(orig.xadvance), font(orig.font) { }



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

const string GlyphDrawCommand::getfont() const {
	return font;
}


/***************************************************************
 FontManager code
****************************************************************/
FontManager::FontManager(Graphics * gr) {
	graphics = new Graphics;
	*graphics = *gr;
}

FontManager::~FontManager()
{
	

	delete graphics;
}

void FontManager::free() {
	// Alle glglyphs in map freen
	map<std::string, GLGlyph*>::iterator it = glyphMap.begin();

	// Iterate over the map using Iterator till end.
	while (it != glyphMap.end())
	{
		gl_glyph_free(it->second);
		delete(it->second);
		it++;
	}
}

void FontManager::loadFont(const std::string& fontName, const std::string& fontImageFilename, const std::string& fontMetaFilename) {
	
	string path = "pi_escape/graphics/";

	map<string, Font>::const_iterator fontIt = fonts.find(fontName);
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
					t_vec4& col = *new t_vec4[4];
					glmc_vec4_set(col, 1.0f, 0.0f, 0.0f, 1.0f);

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
					GlyphDrawCommand c = GlyphDrawCommand(pos_ltop_x, pos_ltop_y, glyph_x, glyph_y, glyph_w, glyph_h, col, xoffset, yoffset, xadvance, fontName);

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
		Font f = Font(charInfo, kernings);

		pair<string, Font> toevoegen(fontName, f);
		fonts.insert(toevoegen);
		
		// Glyph toevoegen aan map
		GLGlyph* glGlyph = new GLGlyph;
		string path = "pi_escape/graphics/";

		// Initializeren glyph
		string imagePath = path + fontImageFilename;

		char * charImagePath = new char[imagePath.length() + 1];
		strcpy(charImagePath, imagePath.c_str());

		gl_glyph_init(glGlyph, graphics, charImagePath);
		delete charImagePath;

		pair<string, GLGlyph*> glyphPair(fontName, glGlyph);
		glyphMap.insert(glyphPair);
	}

	
	// Charmap en kernings aanpassen naar huidig font
	Font font = (fonts.find(fontName)->second);
	curFont = font;
}

vector<GlyphDrawCommand> FontManager::makeGlyphDrawCommands(string text, int x, int y) const {
	
	vector<GlyphDrawCommand> result;
	char prevChar;
	int x1 = x;

	for (int i = 0; i < text.length(); i++) {
		char c = text[i];
		map<char, GlyphDrawCommand>::const_iterator it = curFont.charMap.find(c);
		if (it != curFont.charMap.end()) {
			GlyphDrawCommand found = (it->second);
			// Als i groter dan 0 is eerst kerning tov vorige character berekenen
			if (i > 0) {
				// Als kernings vorige karakter bevat
				map<char, map<char, int>>::const_iterator kerIt1 = curFont.charKernings.find(prevChar);
				if (kerIt1 != curFont.charKernings.end()) {
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
	string fontName = glyphDraw.getfont();
	GLGlyph* glglyph = glyphMap.find(fontName)->second;

	gl_glyph_draw(glglyph, glyphDraw.getPos_ltop_x(), glyphDraw.getPos_ltop_y(), glyphDraw.getGlyph_x(), glyphDraw.getGlyph_y(), glyphDraw.getGlyph_w(), glyphDraw.getGlyph_h(), glyphDraw.getColor());
}

void FontManager::setFont(const string & fontName) {

	// TODO checken of bestaat

	// Charmap en kernings aanpassen naar huidig font
	Font font = (fonts.find(fontName)->second);
	curFont = font;
}

/***************************************************************
 Font code
****************************************************************/

Font::Font(map<char, GlyphDrawCommand> charMap, map<char, map<char, int>> charKernings) 
													: charMap(charMap), charKernings(charKernings) { }

Font::Font(const Font & orig): charMap(orig.charMap), charKernings(orig.charKernings) { }

Font::Font() { }


Font& Font::operator= (const Font & other) {
	if (this != &other) // protect against invalid self-assignment
	{
		charMap = other.charMap;
		charKernings = other.charKernings;
	}
	// by convention, always return *this
	return *this;
}

