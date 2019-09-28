#include "visualizer.hpp"

Visualizer::Visualizer()
{
    // vtkSmartPointer<vtkImageData> grid = vtkSmartPointer<vtkImageData>::New();

    // // Create a mapper and actor.
    // mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    // actor = vtkSmartPointer<vtkImageActor>::New();
    
    // // Create a renderer, render window, and interactor
    // renderer = vtkSmartPointer<vtkRenderer>::New();
    // renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    // renderWindow->AddRenderer(renderer);
    renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
}

Visualizer::~Visualizer()
{
    
}


int Visualizer::start_rendering(bool mesh)
{

    vtkSmartPointer<vtkImageData> imageData = 
    vtkSmartPointer<vtkImageData>::New();

    // Specify the size of the image data
    imageData->SetDimensions(500,500,500);
    imageData->SetSpacing(1.0, 1.0, 1.0);
    imageData->SetOrigin(0.0, 0.0, 0.0);

    vtkSmartPointer<vtkDataSetMapper> mapper = 
    vtkSmartPointer<vtkDataSetMapper>::New();
    mapper->SetInputData(imageData);
    vtkSmartPointer<vtkActor> actor = 
    vtkSmartPointer<vtkActor>::New();
    actor->SetMapper(mapper);

    vtkSmartPointer<vtkRenderWindow> renderWindow = 
    vtkSmartPointer<vtkRenderWindow>::New();

    vtkSmartPointer<vtkRenderer> renderer = 
    vtkSmartPointer<vtkRenderer>::New();

    // Add both renderers to the window
    renderWindow->AddRenderer(renderer);
      
    // Add a sphere to the left and a cube to the right
    renderer->AddActor(actor);

    renderer->ResetCamera();

    vtkSmartPointer<vtkRenderWindowInteractor> renderWindowInteractor = 
    vtkSmartPointer<vtkRenderWindowInteractor>::New();
    renderWindowInteractor->SetRenderWindow(renderWindow);
    renderWindow->Render();
    renderWindowInteractor->Start();
  
}