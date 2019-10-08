#ifndef STM_VIZ
#define STM_VIZ

#include <vtkSmartPointer.h>
#include <vtkCubeAxesActor.h>
#include <vtkPoints.h>
#include <vtkLine.h>
#include <vtkCellArray.h>
#include <vtkCellData.h>
#include <vtkDoubleArray.h>

#include <vtkPolyDataMapper.h>
#include <vtkTextProperty.h>
#include <vtkActorCollection.h>
#include <vtkCamera.h>
#include <vtkRenderWindow.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyLine.h>
#include <vtkActor.h>

#include <vtkProgrammableFilter.h>
#include <vtkCallbackCommand.h>
#include <vtkLineSource.h>
#include <vtkProperty.h>

#include <vtkNamedColors.h>
#include <vtkColor.h>

#include <vtkSTLReader.h>
#include <string>
#include <vtkTransform.h>
#include <vtkTransformPolyDataFilter.h>


using namespace std; 


class Visualizer
{
    
    
    private:
        
        vtkSmartPointer<vtkLineSource> lineSource;
        
    public:

        vtkSmartPointer<vtkProgrammableFilter> programmableFilter;
        vtkSmartPointer<vtkCallbackCommand> timerCallback;
        vtkSmartPointer<vtkPolyDataMapper> mapper; 
        vtkSmartPointer<vtkActor> actor; 
        vtkSmartPointer<vtkNamedColors> colors;
        vtkSmartPointer<vtkRenderer> renderer; 
        vtkSmartPointer<vtkCubeAxesActor> cubeAxesActor; 
        vtkSmartPointer<vtkRenderWindow> renderWindow; 
        vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor; 
        vtkSmartPointer<vtkSTLReader> reader; 
        vtkSmartPointer<vtkPolyDataMapper> probeMapper; 
        vtkSmartPointer<vtkActor> probeActor; 

        Visualizer();
        ~Visualizer();

        void programmableFilterFunc(); 
        int setPoints();         
        int setMapper(); 
        int axes(); 
        int render(); 
        void renderProbe(); 
        
}; 

void TimerCallbackFunction ( vtkObject* caller, long unsigned int eventId, void* clientData, void* callData ); 
void AdjustPoints(void *arguments); 
    
#endif
