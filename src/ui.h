#include <sdl2/sdl.h>
#include <vector>

void registerMouseWatchComponent(int x, int y, int w, int h, const char* name);

// Returns a vector of components which had a ui event detected
std::vector<const char*> pollUIEvents();