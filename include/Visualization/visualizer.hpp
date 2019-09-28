#ifndef STM_VIZ 
#define STM_VIZ

#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageActor.h>
#include <vtkPolyData.h>
#include <vtkDataSetMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>


class Visualizer
{
	private:

		vtkSmartPointer<vtkImageMapper3D> mapper;
		vtkSmartPointer<vtkImageActor> actor;
		vtkSmartPointer<vtkRenderer> renderer;
		vtkSmartPointer<vtkRenderWindow> renderWindow;
		vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor;
		vtkSmartPointer<vtkImageData> grid;

	public:
		Visualizer();
		~Visualizer();
		void add_points(vtkPoints points);
		int start_rendering(bool mesh = false);

};

#endif