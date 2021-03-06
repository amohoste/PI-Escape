#ifndef LED_VIEW
#define LED_VIEW

#include "UI.h"
#include "Menu.h"

extern "C" {
	#include "../led/led.h"
}

class MenuModel;


class LedView;

class LedView : public Observer, public UIView {
private:
	int length_pattern;
	int frame;
	char** tiny_font;
	int** pattern;
	MenuModel *model;
public:
	LedView();

	~LedView();

	void notified() override;

	virtual void draw() override;

	virtual void invalidated() override;

	void setModel(MenuModel *model);
};

#endif	// LED_VIEW