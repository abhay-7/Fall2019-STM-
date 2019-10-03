#include "visualizer.hpp"

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		cout << "Incorrect Usage" << endl;
		cout << " Usage : ./test_visualizer <0 or 1 or 2 or 3>" << endl;
		return 0;
	}

	Visualizer viz(10, 10, 10, 0.1);

	switch(atoi(argv[1]))
	{
		case 0:
			viz.render_demo_sphere(4.0);
			break;

		case 1:
			viz.render_demo_sphere_mesh(4.0);
			break;

		case 2:
			viz.render_demo_cube(6.0);
			break;

		case 3:
			viz.render_demo_cube_mesh(6.0);
			break;

		default:
			cout << "Wrong argument value" << endl;
			break;
	}

}

