#include "visualizer.hpp"

Visualizer::Visualizer()
{
    cout << "Entering Visualizer()" << endl;
    points->Allocate(100);

    imageData = vtkSmartPointer<vtkImageData>::New();
    imageData->SetDimensions( 10, 10, 10);
    imageData->SetSpacing(0.2, 0.2, 0.2);
    imageData->SetOrigin(0.0, 0.0, 0.0);
    imageData->AllocateScalars(VTK_DOUBLE,1);
    
    actor = vtkSmartPointer<vtkActor>::New();
    mapper = vtkSmartPointer<vtkDataSetMapper>::New();
    renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
    cout << "Exiting Visualizer()" << endl;
}

Visualizer::~Visualizer()
{
    
}


int Visualizer::start_rendering(bool mesh)
{
    // Specify the size of the image data
    
    mapper->SetInputData(imageData);
    actor->SetMapper(mapper);
    
    // Add both renderers to the window
    renderWindow->AddRenderer(renderer);
      
    // Add a sphere to the left and a cube to the right
    renderer->AddActor(actor);
    renderer->ResetCamera();
    
    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindow->Render();
    renderWindowInteractor->Start();

    return 0;
}

void Visualizer::add_points()
{
    cout << "Entering add_points" << endl;
    int* dims = imageData->GetDimensions();
    std::cout << "Dims: " << " x: " << dims[0] << " y: " << dims[1] << " z: " << dims[2] << std::endl;

    std::cout << "Number of points: " << imageData->GetNumberOfPoints() << std::endl;
    std::cout << "Number of cells: " << imageData->GetNumberOfCells() << std::endl;

    for(int x = 0; x < dims[0]; ++x)
    {
        for(int y = 0; y < dims[1]; ++y)
        {
            for(int z = 0; z < dims[2]; ++z)
            {
                double* pixel = static_cast<double*>(imageData->GetScalarPointer(x,y,z));
                if( (z % 5) && (y % 5) && (x % 5) )
                    pixel[0] = 100.0;
                else
                    pixel[0] = 0.0;
            }
        }
    }
}

void Visualizer::render_occupancy()
{

    vtkSmartPointer<vtkImageDataGeometryFilter> imageDataGeometryFilter = 
    vtkSmartPointer<vtkImageDataGeometryFilter>::New();
    imageDataGeometryFilter->SetInputData(imageData);
    imageDataGeometryFilter->Update();
#if 0


    vtkSmartPointer<vtkPointOccupancyFilter> occupancy = 
    vtkSmartPointer<vtkPointOccupancyFilter>::New();
    occupancy->SetInputData(imageDataGeometryFilter->GetOutput());
    occupancy->SetSampleDimensions(10, 10, 10);
    occupancy->SetOccupiedValue(255);
    occupancy->Update();

    double isoValue = 0.5;
    vtkSmartPointer<vtkMarchingCubes> surface =
    vtkSmartPointer<vtkMarchingCubes>::New();
  surface->SetInputData(imageData);
  surface->ComputeNormalsOn();
  surface->SetValue(0, isoValue);

  vtkSmartPointer<vtkRenderer> renderer =
    vtkSmartPointer<vtkRenderer>::New();
  renderer->SetBackground(.1, .2, .3);

  vtkSmartPointer<vtkRenderWindow> renderWindow =
    vtkSmartPointer<vtkRenderWindow>::New();
  renderWindow->AddRenderer(renderer);
  vtkSmartPointer<vtkRenderWindowInteractor> interactor =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  interactor->SetRenderWindow(renderWindow);

  vtkSmartPointer<vtkPolyDataMapper> mapper =
    vtkSmartPointer<vtkPolyDataMapper>::New();
  mapper->SetInputConnection(surface->GetOutputPort());
    // mapper->SetInputData(imageDataGeometryFilter->GetOutput());
  mapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  renderer->AddActor(actor);

  renderWindow->Render();
  interactor->Start();

#else
    vtkSmartPointer<vtkPointOccupancyFilter> occupancy = 
    vtkSmartPointer<vtkPointOccupancyFilter>::New();
    occupancy->SetInputData(imageDataGeometryFilter->GetOutput());
    occupancy->SetSampleDimensions(100, 100, 100);
    occupancy->SetOccupiedValue(255);
    occupancy->Update();

    vtkSmartPointer<vtkThreshold> threshold =
    vtkSmartPointer<vtkThreshold>::New();
  threshold->SetInputConnection(occupancy->GetOutputPort());
  threshold->ThresholdByUpper(255);
  threshold->AllScalarsOff();

  vtkSmartPointer<vtkDataSetMapper> mapper =
    vtkSmartPointer<vtkDataSetMapper>::New();
  mapper->SetInputConnection(threshold->GetOutputPort());
  mapper->ScalarVisibilityOff();

  vtkSmartPointer<vtkActor> actor =
    vtkSmartPointer<vtkActor>::New();
  actor->SetMapper(mapper);

  // Colors
  vtkSmartPointer<vtkNamedColors> nc =
    vtkSmartPointer<vtkNamedColors>::New();
  double flesh[3];
  nc->GetColorRGB("moccasin", flesh);
  actor->GetProperty()->SetColor(flesh);

  // Create graphics stuff
  //
  vtkSmartPointer<vtkRenderer> ren1 =
    vtkSmartPointer<vtkRenderer>::New();
  ren1->SetBackground(.8, .8, 1.0);

  vtkSmartPointer<vtkRenderWindow> renWin =
    vtkSmartPointer<vtkRenderWindow>::New();
  renWin->AddRenderer(ren1);
  renWin->SetSize(512,512);

  vtkSmartPointer<vtkRenderWindowInteractor> iren =
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
  iren->SetRenderWindow(renWin);

  // Add the actors to the renderer, set the background and size
  //
  ren1->AddActor(actor);

  // Generate an interesting view
  //
  ren1->ResetCamera();
  ren1->GetActiveCamera()->Azimuth(120);
  ren1->GetActiveCamera()->Elevation(30);
  ren1->GetActiveCamera()->Dolly(1.25);
  ren1->ResetCameraClippingRange();

  renWin->Render();
  iren->Initialize();
  iren->Start();
#endif

}

