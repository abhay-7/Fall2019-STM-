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
#include <vtkPolyData.h>
#include <vtkPolyLine.h>
#include <vtkProperty.h>
#include <vtkSuperquadricSource.h>
#include <vtkActor.h>

#include <vtkProgrammableFilter.h>
#include <vtkCallbackCommand.h>
#include <vtkLineSource.h>
#include <vtkPolyData.h>
#include <vtkProperty.h>

#include <vtkNamedColors.h>
#include <vtkColor.h>

void TimerCallbackFunction ( vtkObject* caller, long unsigned int eventId, void* clientData, void* callData );

unsigned int counter1 = 10;
unsigned int counter2 = 0;
bool goingDown = true;

void AdjustPoints2(void* arguments)
{
    vtkProgrammableFilter* programmableFilter =
    static_cast<vtkProgrammableFilter*>(arguments);
    
    vtkPoints* inPts = programmableFilter->GetPolyDataInput()->GetPoints();
    vtkIdType numPts = inPts->GetNumberOfPoints();
    vtkSmartPointer<vtkPoints> newPts = vtkSmartPointer<vtkPoints>::New();
    newPts->SetNumberOfPoints(numPts);
    
    // there is always going to be two points
    
    double p[3] = {0, 0, 0}; // this represents the origin.
    
    newPts->SetPoint(0, p); // sets the origin at point ID 0
    
    // get the point of the old coordinate
    double p1[3];
    inPts->GetPoint(1, p1); // sets it to p1
    
    // manipulate the new point

    if(goingDown == true){
        p1[1] = p1[1] - counter2;
    } else {
        p1[1] = p1[1] - counter1;
    }
    
    newPts->SetPoint(1, p1);
    
    programmableFilter->GetPolyDataOutput()->CopyStructure(programmableFilter->GetPolyDataInput());
    programmableFilter->GetPolyDataOutput()->SetPoints(newPts); // then this sets the new points.
}

int main(int, char *[])
{
    

    // Create two points, P0 and P1
    double p0[3] = {0.0, 0.0, 0.0};
    double p1[3] = {10.0, 10.0, 0.0};
    
    vtkSmartPointer<vtkLineSource> lineSource =
    vtkSmartPointer<vtkLineSource>::New();
    lineSource->SetPoint1(p0);
    lineSource->SetPoint2(p1);
    lineSource->Update();
    
    
    vtkSmartPointer<vtkProgrammableFilter> programmableFilter =
    vtkSmartPointer<vtkProgrammableFilter>::New();
    programmableFilter->SetInputConnection(lineSource->GetOutputPort()); // the programmagbleFilter gets the sphere source as their input --> then the execute method is the one outlied.
    
    programmableFilter->SetExecuteMethod(AdjustPoints2, programmableFilter);
    
    // Create a mapper and actor
    vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
    mapper->SetInputConnection(programmableFilter->GetOutputPort());
    vtkSmartPointer<vtkActor> actor = vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);
    actor->GetProperty()->SetLineWidth(1);
    actor->GetProperty()->SetColor(255,0,0); 

    // Define colors for this example
    vtkSmartPointer<vtkNamedColors> colors =
    vtkSmartPointer<vtkNamedColors>::New();
    
    vtkColor3d backgroundColor = colors->GetColor3d("Black");
    vtkColor3d actorColor = colors->GetColor3d("Black");
    vtkColor3d axis1Color = colors->GetColor3d("Black");
    vtkColor3d axis2Color = colors->GetColor3d("Black");
    vtkColor3d axis3Color = colors->GetColor3d("Black");
    
    vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
    
    vtkSmartPointer<T> cubeAxesActor =
    vtkSmartPointer<vtkCubeAxesActor>::New();
    cubeAxesActor->SetUseTextActor3D(1);
    cubeAxesActor->SetBounds(0, 10, 0, 10, 0, 10);
    cubeAxesActor->SetCamera(renderer->GetActiveCamera());
    cubeAxesActor->GetTitleTextProperty(0)->SetFontSize(48);
    //cubeAxesActor->GetLabelTextProperty(0)->SetColor(1.0, 0.0, 0.0);
    
    // cubeAxesActor->GetLabelTextProperty(1)->SetColor(1.0, 0.0, 0.0);
    
    cubeAxesActor->DrawXGridlinesOn();
    cubeAxesActor->DrawYGridlinesOn();
    cubeAxesActor->DrawZGridlinesOn();
    /*
     #if VTK_MAJOR_VERSION == 6
     cubeAxesActor->SetGridLineLocation(VTK_GRID_LINES_FURTHEST);
     #endif
     #if VTK_MAJOR_VERSION > 6
     cubeAxesActor->SetGridLineLocation(
     cubeAxesActor->VTK_GRID_LINES_FURTHEST);
     #endif
     */
    cubeAxesActor->XAxisMinorTickVisibilityOff();
    cubeAxesActor->YAxisMinorTickVisibilityOff();
    cubeAxesActor->ZAxisMinorTickVisibilityOff();
    
    cubeAxesActor->SetFlyModeToOuterEdges();

    // create a render, render window, and interactor 

    renderer->AddActor(cubeAxesActor);
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);
    
    renderer->ResetCamera();
    renderer->SetBackground(backgroundColor.GetData());
    
    vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(1800, 1680);
    
    
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindow->SetWindowName("Grid with Line");

    renderWindowInteractor->Initialize();
    renderWindowInteractor->CreateRepeatingTimer(50);

    vtkSmartPointer<vtkCallbackCommand> timerCallback =
    vtkSmartPointer<vtkCallbackCommand>::New();
    timerCallback->SetCallback ( TimerCallbackFunction ); // the function
    timerCallback->SetClientData(programmableFilter); // this is the data that is being modified on the callback
    
    renderWindowInteractor->AddObserver ( vtkCommand::TimerEvent, timerCallback );
    
    // Add the actor to the scene
    renderer->AddActor(actor);
  //  renderer->SetBackground(1,1,1); // Background color white
    
    renderWindow->Render();
    renderWindowInteractor->Start();
    
    return EXIT_SUCCESS;
}

void TimerCallbackFunction ( vtkObject* caller, long unsigned int vtkNotUsed(eventId), void* clientData, void* vtkNotUsed(callData) )
{
    
    vtkSmartPointer<vtkProgrammableFilter> programmableFilter =
    static_cast<vtkProgrammableFilter*>(clientData);
    
    vtkRenderWindowInteractor *iren =
    static_cast<vtkRenderWindowInteractor*>(caller);
    
    programmableFilter->Modified();
    
    iren->Render();
    
    // the mechanism for the swinging - based on the assumption that p1[1] will always start at 10 because the value of p1[1] always remains the same at 10.
    
    if(goingDown == true){
        
        if(counter2 != 10){
            counter2++;
        } else {
            goingDown = false;
            counter1--;
            counter2 = 0;
        }
        
    } else if(goingDown == false){
        
        if(counter1 != 0){
            counter1--;
        } else {
            goingDown = true;
            counter2++;
            counter1 = 10;
        }
        
    }
    
}

