#pragma once
#include <vector>
#include <memory>


class SDL_Renderer; 
class InputEvent;

class Widget {

public:
	virtual void render(SDL_Renderer* renderer) = 0;
	virtual void onInputEvent(InputEvent event) = 0; 
	virtual void addChildWidget(std::shared_ptr<Widget> w);


protected:
	bool _visible;
	std::vector<std::shared_ptr<Widget>> _childWidgets;
	
};