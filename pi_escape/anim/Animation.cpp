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

std::vector<GlyphDrawCommand> RainbowColorAnimation::applyTransform(const std::vector<GlyphDrawCommand>& draws, float position) const
{
	std::vector<GlyphDrawCommand> res;

	for (std::vector<GlyphDrawCommand>::const_iterator it = draws.begin(); it != draws.end(); it++) {
		const GlyphDrawCommand& cur = *it;

		float hue = 360.0f * position;
		vector<float> rgb = hsv_to_rgb(hue);
		//hsv_to_rgb(rgb, hue);


		//res.push_back(replacement);
	}

	return res;
}


std::vector<float> RainbowColorAnimation::hsv_to_rgb(float hue) const {
	std::vector<float> result(3);

	// Voor onze noden moeten we enkel de hue kunnen laten veranderen
	float s = 1.0f;
	float v = 1.0f;
	float fract, p, q, t, h;

	if (hue == 360.0f) {
		h = 0.0f;
	} else {
		h = hue / 60.0f;
	}

	fract = h - floor(h);

	p = v * (1.0f - s);
	q = v * (1.0f - (s * fract));
	t = v * (1.0f - (s * (1.0f - fract)));

	if (0.0f <= h && h < 1.0f) {
		result[0] = v;
		result[1] = t;
		result[2] = p;
	}
	else if (1.0f <= h && h < 2) {
		result[0] = q;
		result[1] = v;
		result[2] = p;
	}
	else if (2.0f <= h && h < 3) {
		result[0] = p;
		result[1] = v;
		result[2] = t;
	}
	else if (3.0f <= h && h < 4) {
		result[0] = p;
		result[1] = q;
		result[2] = v;
	}
	else if (4.0f <= h && h < 5) {
		result[0] = t;
		result[1] = p;
		result[2] = v;
	}
	else if (5.0f <= h && h < 6) {
		result[0] = v;
		result[1] = p;
		result[2] = q;
	}
	else {
		result[0] = 0.0f;
		result[1] = 0.0f;
		result[2] = 0.0f;
	}

	return result;
}

RainbowColorAnimation::RainbowColorAnimation() {

}

RainbowColorAnimation::~RainbowColorAnimation()
{
}

