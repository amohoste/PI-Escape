#ifndef LED_VIEW
#define LED_VIEW

#include "UI.h"
#include "Menu.h"

class LedView : public Observer {
private:
	MenuModel *model;
public:
	LedView();

	~LedView();

	void notified() override;

	void setModel(MenuModel *model);
};

#endif	// LED_VIEW