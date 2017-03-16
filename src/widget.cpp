#include "widget.h"

void Widget::addChildWidget(std::shared_ptr<Widget> w) {
	_childWidgets.push_back(w);
}