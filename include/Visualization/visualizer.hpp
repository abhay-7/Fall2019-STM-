#ifndef STM_VIZ 
#define STM_VIZ

#include <vector>
#include <array>
#include <unistd.h>

#include <vtkSmartPointer.h>
#include <vtkDataSetMapper.h>
#include <vtkPoints.h>
#include <vtkLine.h>
#include <vtkCellArray.h>
#include <vtkStructuredGrid.h>
#include <vtkSphereSource.h>
#include <vtkThreshold.h>
#include <vtkProperty.h>

#include <vtkRenderer.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>

#include <vtkMarchingCubes.h>
#include <vtkPointOccupancyFilter.h>

using namespace std;

class Visualizer
{
	private:

		//Members containing grid properties
		double mResolution;
		double mDims[3];
		double mGridDims[3];

		//Data structures storing the pointd or the scan data
		vtkSmartPointer<vtkPoints> mPoints;
		vtkSmartPointer<vtkStructuredGrid> mGrid;

		//Member variables used for rendering and interaction
		vtkSmartPointer<vtkDataSetMapper> mMapper;
		vtkSmartPointer<vtkActor> mActor;
		vtkSmartPointer<vtkActor> mGridActor;
		vtkSmartPointer<vtkRenderer> mRenderer;
		vtkSmartPointer<vtkRenderWindow> mRenderWindow;
		vtkSmartPointer<vtkRenderWindowInteractor> mRenderWindowInteractor;

	public:

		//Constructor which takes the dimensions as inputs
		Visualizer(double x_dim, double y_dim, double z_dim, double resolution);
		Visualizer();
		~Visualizer();

		//Method which should be used to incrementally add points to the existing data
		void add_points(vector < array < double, 3> > &points);
		void clear_points();

		void generate_grid(double interval);


		//Demo functions
		void render_demo_sphere( double radius);
		void render_demo_sphere_mesh( double radius);
		void render_demo_cube( double radius);
		void render_demo_cube_mesh( double radius);

		//Functions to render the data 
		vtkSmartPointer<vtkRenderer> get_renderer();
		void start_rendering(int width = 1920, int height = 1080, bool grid = true);
		void render_occupancy();
		void generate_sphere(vtkSmartPointer<vtkImageData> grid);

};

#endif