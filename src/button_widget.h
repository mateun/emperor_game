#include "widget.h"

class Button : public Widget {

public:
	virtual void render(SDL_Renderer* renderer);
	virtual void onInputEvent(InputEvent event);
};