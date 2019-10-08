#include <visualizer.hpp>

Visualizer::Visualizer()
{
    /*
     Initialises most of the variables required for the visualisation
     */

    cout << "constructor" << endl; 
    
    lineSource = vtkSmartPointer<vtkLineSource>::New();
    mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    actor = vtkSmartPointer<vtkActor>::New();
    colors = vtkSmartPointer<vtkNamedColors>::New();
    renderer = vtkSmartPointer<vtkRenderer>::New();

    programmableFilter = vtkSmartPointer<vtkProgrammableFilter>::New();
    cubeAxesActor = vtkSmartPointer<vtkCubeAxesActor>::New();

    renderWindow = vtkSmartPointer<vtkRenderWindow>::New();

    timerCallback = vtkSmartPointer<vtkCallbackCommand>::New();
    reader = vtkSmartPointer<vtkSTLReader>::New();

    probeMapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    probeActor = vtkSmartPointer<vtkActor>::New();
    
    cout << "constructor ended" << endl; 

}

Visualizer::~Visualizer(){
    // the deconstructor
}

void Visualizer::renderProbe() {

    string inputFilename ("Submarine.stl"); 

    reader->SetFileName(inputFilename.c_str()); 
    reader->Update(); 

    vtkSmartPointer<vtkTransform> transform = vtkSmartPointer<vtkTransform>::New();

    transform->Scale(0.05, 0.05, 0.05); 
    transform->Translate(135.0, 135.0, 200.0); 
    transform->RotateWXYZ(90, 0, 0, 1);
    transform->RotateWXYZ(270, 0, 1, 0);


    vtkSmartPointer<vtkTransformPolyDataFilter> transformFilter = vtkSmartPointer<vtkTransformPolyDataFilter>::New();
  
    transformFilter->SetInputConnection(reader->GetOutputPort());
    transformFilter->SetTransform(transform);

      //transform->RotateWXYZ(double angle, double x, double y, double z);

    /*

    transform->Scale(0.05, 0.05, 0.05); 
    transform->RotateX(90.0); 
    transform->RotateY(180.0); 
   // transform->RotateZ(-180.0); 
   // transform->Translate(10.0, 10.0, 10.0); // x moves it upwards

*/
    probeMapper->SetInputConnection(transformFilter->GetOutputPort());
    probeActor->SetMapper(probeMapper);

}


int Visualizer::setPoints(){

    double p0[3] = {0.0, 0.0, 0.0};
    double p1[3] = {10.0, 10.0, 0.0};

    lineSource->SetPoint1(p0);
    lineSource->SetPoint2(p1);

    lineSource->Update();

    return 0; 
}

void Visualizer::programmableFilterFunc(){

    programmableFilter->SetInputConnection(lineSource->GetOutputPort()); // the programmagbleFilter gets the points source as their input --> then the execute method is the one outlied.
    
    programmableFilter->SetExecuteMethod(AdjustPoints, programmableFilter); //callback to the points function

}

int Visualizer::setMapper() {

    // this is for the line actor

    mapper->SetInputConnection(programmableFilter->GetOutputPort());

    actor->SetMapper(mapper);
    actor->GetProperty()->SetLineWidth(5);
    actor->GetProperty()->SetColor(255,0,0);

    return 0; 

}

int Visualizer::axes() {


    cubeAxesActor->SetUseTextActor3D(1);
    cubeAxesActor->SetBounds(0, 10, 0, 10, 0, 10);
    cubeAxesActor->SetCamera(renderer->GetActiveCamera());
    cubeAxesActor->GetTitleTextProperty(0)->SetFontSize(48);

    cubeAxesActor->DrawXGridlinesOn();
    cubeAxesActor->DrawYGridlinesOn();
    cubeAxesActor->DrawZGridlinesOn();

    cubeAxesActor->XAxisMinorTickVisibilityOff();
    cubeAxesActor->YAxisMinorTickVisibilityOff();
    cubeAxesActor->ZAxisMinorTickVisibilityOff();
    
    cubeAxesActor->SetFlyModeToOuterEdges();

    return 0; 

}

int Visualizer::render(){


    renderer->AddActor(cubeAxesActor);
    renderer->GetActiveCamera()->Azimuth(30);
    renderer->GetActiveCamera()->Elevation(30);
    
    renderer->ResetCamera();
    vtkColor3d backgroundColor = colors->GetColor3d("Black");
    renderer->SetBackground(backgroundColor.GetData());
    
    vtkSmartPointer<vtkRenderWindow> renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    renderWindow->SetSize(1800, 1680);
    
    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindow->SetWindowName("Grid with Line");

    renderWindowInteractor->Initialize();
    renderWindowInteractor->CreateRepeatingTimer(50);

    timerCallback->SetCallback ( TimerCallbackFunction ); // the function
    timerCallback->SetClientData(programmableFilter); // this is the data that is being modified on the callback
    
    renderWindowInteractor->AddObserver ( vtkCommand::TimerEvent, timerCallback );
    
    // Add the actor to the scene
    renderer->AddActor(actor);
    renderer->AddActor(probeActor); 
    
    renderWindow->Render();
    renderWindowInteractor->Start();
    
    return EXIT_SUCCESS;

}

unsigned int counter1 = 10;
unsigned int counter2 = 0;
bool goingDown = true;

void AdjustPoints(void* arguments){

    /*
        
        The origin of the sphere is

    */ 
    
    vtkProgrammableFilter* programmableFilter =
    static_cast<vtkProgrammableFilter*>(arguments);
    
    vtkPoints* inPts = programmableFilter->GetPolyDataInput()->GetPoints();
    vtkIdType numPts = inPts->GetNumberOfPoints();
    vtkSmartPointer<vtkPoints> newPts = vtkSmartPointer<vtkPoints>::New();
    newPts->SetNumberOfPoints(numPts);
    
    // there is always going to be two points
    
    double p[3] = {5.0, 5.0, 10.0}; // this represents the origin.
    
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


