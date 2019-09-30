#ifndef STM_VIZ 
#define STM_VIZ

#include <vtkSmartPointer.h>
#include <vtkImageData.h>
#include <vtkImageActor.h>
#include <vtkPolyData.h>
#include <vtkDataSetMapper.h>
#include <vtkPolyDataMapper.h>
#include <vtkRenderWindow.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkRenderer.h>
#include <vtkImageDataGeometryFilter.h>
#include <vtkPointOccupancyFilter.h>
#include <vtkThreshold.h>
#include <vtkCamera.h>
#include <vtkProperty.h>
#include <vtkNamedColors.h>
#include <vtkMarchingCubes.h>
#include <vtkVoxelModeller.h>


class Visualizer
{
	private:
		vtkNew<vtkPoints> points;
		vtkSmartPointer<vtkImageData> imageData;
		vtkSmartPointer<vtkDataSetMapper> mapper;
		vtkSmartPointer<vtkActor> actor;
		vtkSmartPointer<vtkRenderer> renderer;
		vtkSmartPointer<vtkRenderWindow> renderWindow;
		vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor;

	public:
		Visualizer();
		~Visualizer();
		void add_points();
		int start_rendering(bool mesh = false);
		void render_occupancy();

};

#endif