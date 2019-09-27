#ifndef STM_VIZ 
#define STM_VIZ

#include <vtkSmartPointer.h>
#include <vtkActor.h>
#include <vtkCubeSource.h>
#include <vtkPolyData.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>


class Visualizer
{
	private:

		vtkSmartPointer<vtkPolyDataMapper> mapper;
		vtkSmartPointer<vtkActor> actor;
		vtkSmartPointer<vtkRenderer> renderer;
		vtkSmartPointer<vtkRenderWindow> renderWindow;
		vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor;
		vtkSmartPointer<vtkCubeSource> cubeSource;

	public:
		Visualizer();
		~Visualizer();
		void add_points(vtkPoints points);
		int start_rendering(bool mesh = false);

};

#endif