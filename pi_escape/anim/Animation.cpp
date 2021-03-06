#include "Animation.h"

using namespace std;

/***************************************************************
 Animation
****************************************************************/
Animation::~Animation() {

}

/***************************************************************
 FadeInAnimation
****************************************************************/
std::vector<GlyphDrawCommand> FadeInAnimation::applyTransform(const std::vector<GlyphDrawCommand>& draws, float position) const {
	float curAlpha = position;

	std::vector<GlyphDrawCommand> res;

	for (std::vector<GlyphDrawCommand>::const_iterator it = draws.begin(); it != draws.end(); it++) {
		const GlyphDrawCommand& cur = *it;
		GlyphDrawCommand replacement = cur.changeAlpha(cur.getColor()[3] * curAlpha);
		res.push_back(replacement);
	}

	return res;
}

FadeInAnimation::~FadeInAnimation() {

}

/***************************************************************
 ColorAnimation
****************************************************************/
ColorAnimation::ColorAnimation(t_vec4 newColor)
	: newColor{ newColor[0], newColor[1], newColor[2], newColor[3] } {}

ColorAnimation::ColorAnimation(float r, float g, float b, float a)
	: newColor{ r,g,b,a } {}

ColorAnimation::ColorAnimation(float r, float g, float b)
	: newColor{ r,g,b,1.0f } {}

ColorAnimation::~ColorAnimation() {

}

std::vector<GlyphDrawCommand> ColorAnimation::applyTransform(const std::vector<GlyphDrawCommand> &draws, float position) const {
	std::vector<GlyphDrawCommand> res;

	for (std::vector<GlyphDrawCommand>::const_iterator it = draws.begin(); it != draws.end(); it++) {
		const GlyphDrawCommand& cur = *it;

		t_vec4 curColor;
		curColor[0] = (cur.getColor()[0] * (1.0f - position)) + (newColor[0] * position);
		curColor[1] = (cur.getColor()[1] * (1.0f - position)) + (newColor[1] * position);
		curColor[2] = (cur.getColor()[2] * (1.0f - position)) + (newColor[2] * position);
		curColor[3] = (cur.getColor()[3] * (1.0f - position)) + (newColor[3] * position);

		GlyphDrawCommand replacement = cur.changeColor(curColor[0], curColor[1], curColor[2]);
		res.push_back(replacement);
	}

	return res;
}

/***************************************************************
 RainbowColorAnimation
****************************************************************/
RainbowColorAnimation::RainbowColorAnimation() {

}

RainbowColorAnimation::~RainbowColorAnimation() {
}

std::vector<GlyphDrawCommand> RainbowColorAnimation::applyTransform(const std::vector<GlyphDrawCommand>& draws, float position) const
{

	std::vector<GlyphDrawCommand> res;

	for (std::vector<GlyphDrawCommand>::const_iterator it = draws.begin(); it != draws.end(); it++) {
		const GlyphDrawCommand& cur = *it;

		// Hue berekenen en omzetten naar rgb
		float hue = 360.0f * position;
		const t_vec3* rgb = hsv_to_rgb(hue);

		t_vec4 newcolor;
		glmc_vec4_set(newcolor, (*rgb)[0], (*rgb)[1], (*rgb)[2], cur.getColor()[3]);
		
		delete []rgb;

		GlyphDrawCommand replacement = cur.changeColor(newcolor[0], newcolor[1], newcolor[2]);
		res.push_back(replacement);
	}

	return res;
}

const t_vec3* RainbowColorAnimation::hsv_to_rgb(float hue) const {
	t_vec3* result = new t_vec3[3];

	// Voor onze noden moeten we enkel de hue kunnen laten veranderen
	float s = 1.0f;
	float v = 1.0f;
	float fract, p, q, t, h;

	if (hue == 360.0f) {
		h = 0.0f;
	}
	else {
		h = hue / 60.0f;
	}

	fract = h - floor(h);

	p = v * (1.0f - s);
	q = v * (1.0f - (s * fract));
	t = v * (1.0f - (s * (1.0f - fract)));

	if (0.0f <= h && h < 1.0f) {
		(*result)[0] = v;
		(*result)[1] = t;
		(*result)[2] = p;
	}
	else if (1.0f <= h && h < 2) {
		(*result)[0] = q;
		(*result)[1] = v;
		(*result)[2] = p;
	}
	else if (2.0f <= h && h < 3) {
		(*result)[0] = p;
		(*result)[1] = v;
		(*result)[2] = t;
	}
	else if (3.0f <= h && h < 4) {
		(*result)[0] = p;
		(*result)[1] = q;
		(*result)[2] = v;
	}
	else if (4.0f <= h && h < 5) {
		(*result)[0] = t;
		(*result)[1] = p;
		(*result)[2] = v;
	}
	else if (5.0f <= h && h < 6) {
		(*result)[0] = v;
		(*result)[1] = p;
		(*result)[2] = q;
	}
	else {
		(*result)[0] = 0.0f;
		(*result)[1] = 0.0f;
		(*result)[2] = 0.0f;
	}

	return result;
}

/***************************************************************
 MoveAnimation
****************************************************************/
MoveAnimation::MoveAnimation(t_ivec2 relPos) 
	: newPos{ relPos[0], relPos[1] } {}

MoveAnimation::MoveAnimation(int x, int y) 
	: newPos{ x, y } {}

MoveAnimation::~MoveAnimation() {

}

std::vector<GlyphDrawCommand> MoveAnimation::applyTransform(const std::vector<GlyphDrawCommand>& draws, float position) const {
	std::vector<GlyphDrawCommand> res;

	for (std::vector<GlyphDrawCommand>::const_iterator it = draws.begin(); it != draws.end(); it++) {
		const GlyphDrawCommand& cur = *it;
		
		t_ivec2 move;
		move[0] = (int) (newPos[0] * position);
		move[1] = (int) (newPos[1] * position);

		GlyphDrawCommand replacement = cur.move(move[0], move[1]);
		res.push_back(replacement);
	}

	return res;
}

/***************************************************************
 FloatInAnimation
****************************************************************/
FloatInAnimation::FloatInAnimation(t_ivec2 relPos)
	: newPos{ relPos[0], relPos[1] } {}

FloatInAnimation::FloatInAnimation(int x, int y)
	: newPos{ x, y } {}

FloatInAnimation::~FloatInAnimation() {

}

std::vector<GlyphDrawCommand> FloatInAnimation::applyTransform(const std::vector<GlyphDrawCommand>& draws, float position) const {
	std::vector<GlyphDrawCommand> res;

	for (std::vector<GlyphDrawCommand>::const_iterator it = draws.begin(); it != draws.end(); it++) {
		const GlyphDrawCommand& cur = *it;

		t_ivec2 move;
		move[0] = (int) (newPos[0] * (1 - position));
		move[1] = (int) (newPos[1] * (1 - position));

		GlyphDrawCommand replacement = cur.move(move[0], -move[1]);
		res.push_back(replacement);
	}

	return res;
}

/***************************************************************
 GlyphIteratingAnimation
****************************************************************/
GlyphIteratingAnimation::GlyphIteratingAnimation(Animation * animation, float overlap) : animation(animation), overlap(overlap) {
}

GlyphIteratingAnimation::~GlyphIteratingAnimation() {
	delete animation;
}

std::vector<GlyphDrawCommand> GlyphIteratingAnimation::applyTransform(const std::vector<GlyphDrawCommand>& draws, float position) const {
	
	std::vector<GlyphDrawCommand> res;

	int size = draws.size();
	float amount = 1.0f / size;

	int i = 0;
	for (std::vector<GlyphDrawCommand>::const_iterator it = draws.begin(); it != draws.end(); it++) {
		
		const GlyphDrawCommand& cur = *it;

		float begin = fmax(0.0f, (i - overlap) * amount);
		float end = fmin(1.0f, ((i + 1) + overlap) * amount);

		if ( begin <= position && position <= end ) {
			const GlyphDrawCommand& cur = *it;

			std::vector<GlyphDrawCommand> tmp;
			tmp.push_back(cur);

			std::vector<GlyphDrawCommand> newGlyph = animation->applyTransform(tmp, (position - begin) / (end - begin));

			std::vector<GlyphDrawCommand>::const_iterator it1 = newGlyph.begin();
			res.push_back(*it1);
		} else if (position <= begin) {
			const GlyphDrawCommand& cur = *it;

			std::vector<GlyphDrawCommand> tmp;
			tmp.push_back(cur);

			std::vector<GlyphDrawCommand> newGlyph = animation->applyTransform(tmp, 0);

			std::vector<GlyphDrawCommand>::const_iterator it1 = newGlyph.begin();
			res.push_back(*it1);
		}
		else {
			const GlyphDrawCommand& cur = *it;

			std::vector<GlyphDrawCommand> tmp;
			tmp.push_back(cur);

			std::vector<GlyphDrawCommand> newGlyph = animation->applyTransform(tmp, 1);

			std::vector<GlyphDrawCommand>::const_iterator it1 = newGlyph.begin();
			res.push_back(*it1);
		}
		
		i++;
	}

	return res;
	
}

/***************************************************************
 RepeatAnimation
****************************************************************/
RepeatAnimation::RepeatAnimation(Animation * animation, int repeats, bool startIn, bool endIn, bool cycleInOut) : animation(animation), repeats(repeats), startIn(startIn), endIn(endIn), cycleInOut(cycleInOut) {

}

RepeatAnimation::RepeatAnimation(Animation * animation, int repeats) : animation(animation), repeats(repeats), startIn(true), endIn(false), cycleInOut(true) {
	// TODO: juiste standaardwaarden
}

RepeatAnimation::~RepeatAnimation() {
	delete animation;
}

std::vector<GlyphDrawCommand> RepeatAnimation::applyTransform(const std::vector<GlyphDrawCommand>& draws, float position) const {
	
	// Repeatanimations worden niet ondersteund op de pi omdat deze issues geeft met het scherm op hoge resolutie (te snel voor de pi)
	#ifdef RPI
	std::vector<GlyphDrawCommand> res = animation->applyTransform(draws, position);

	return res;
	#endif // RPI
	#ifndef RPI
	std::vector<GlyphDrawCommand> res;

	// Berekenen hoeveel animaties er moeten gebeuren
	int i = 2 * repeats;
	if (cycleInOut && startIn != endIn) {
		i += 1;
	}
	else if (!cycleInOut && startIn == endIn) {
		i += 2;
	}

	// Block (aantal positie) per animatie berekenen
	float block = 1.0 / i;
	int cycle = (int) floor(position / (2 * block));

	Animation* a;
	if (startIn) {
		a = animation;
	}
	else {
		a = new ReverseAnimation(animation);
	}

	if (cycleInOut) {
		if (startIn != endIn && position >= 1 - block) {
			if (endIn) {
				res = animation->applyTransform(draws, (position - (cycle * (2 * block))) / (block));
			}
			else {
				ReverseAnimation anim = ReverseAnimation(animation);
				res = anim.applyTransform(draws, (position - (cycle * (2 * block))) / (block));
			}
		}
		else {
			InOutAnimation anim = InOutAnimation(a);

			res = anim.applyTransform(draws, (position - (cycle * (2 * block))) / (2 * block));
		}
	}
	else {
		if (startIn == endIn && position >= 1 - (2 * block)) {
			if (endIn) {
				res = animation->applyTransform(draws, (position - (cycle * (2 * block))) / (2 * block));
			}
			else {
				ReverseAnimation anim = ReverseAnimation(animation);
				res = anim.applyTransform(draws, (position - (cycle * (2 * block))) / (2 * block));
			}
		}
		else {
			res = a->applyTransform(draws, (position - (cycle * (2 * block))) / (2 * block));
		}

	}

	if (!startIn) {
		delete a;
	}

	return res;
	#endif // !RPI
}

/***************************************************************
 SineAnimation
****************************************************************/
SineAnimation::SineAnimation(Animation * animation) : animation(animation) {

}

SineAnimation::~SineAnimation() {
	delete animation;
}

std::vector<GlyphDrawCommand> SineAnimation::applyTransform(const std::vector<GlyphDrawCommand>& draws, float position) const {
	
	std::vector<GlyphDrawCommand> res = animation->applyTransform(draws, sin(position * (PI/2)));

	return res;
}

/***************************************************************
 ReverseAnimation
****************************************************************/
ReverseAnimation::ReverseAnimation(Animation * animation) : animation(animation) {
}

ReverseAnimation::~ReverseAnimation() {
}

std::vector<GlyphDrawCommand> ReverseAnimation::applyTransform(const std::vector<GlyphDrawCommand>& draws, float position) const {
	
	std::vector<GlyphDrawCommand> res = animation->applyTransform(draws, 1.0 - position);

	return res;

}

/***************************************************************
 InOutAnimation
****************************************************************/
InOutAnimation::InOutAnimation(Animation * animation) : animation(animation) {
}

InOutAnimation::~InOutAnimation() {
}

std::vector<GlyphDrawCommand> InOutAnimation::applyTransform(const std::vector<GlyphDrawCommand>& draws, float position) const {
	
	if (position < 0.5) {
		std::vector<GlyphDrawCommand> res = animation->applyTransform(draws, 2 * position);

		return res;
	}
	else {
		std::vector<GlyphDrawCommand> res = animation->applyTransform(draws, 2 * (1.0 - position));

		return res;
	}

}