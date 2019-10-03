#include "visualizer.hpp"

int main(int, char*[])
{

#if 0

	Visualizer viz(10, 10, 10, 0.1);
	viz.render_demo_cube(4.0);

#else

	Visualizer viz1(10, 10, 10, 0.1);
	viz1.render_demo_cube_mesh(4.0);

#endif

}

