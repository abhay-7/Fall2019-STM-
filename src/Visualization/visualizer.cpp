#include "visualizer.hpp"

Visualizer::Visualizer()
{
    cubeSource = vtkSmartPointer<vtkCubeSource>::New();

    // Create a mapper and actor.
    mapper = vtkSmartPointer<vtkPolyDataMapper>::New();
    actor = vtkSmartPointer<vtkActor>::New();
    
    // Create a renderer, render window, and interactor
    renderer = vtkSmartPointer<vtkRenderer>::New();
    renderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    renderWindow->AddRenderer(renderer);
    renderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
}

Visualizer::~Visualizer()
{
    
}


int Visualizer::start_rendering(bool mesh)
{

    mapper->SetInputConnection(cubeSource->GetOutputPort());
    actor->SetMapper(mapper);
    renderWindow->AddRenderer(renderer);
    renderWindowInteractor->SetRenderWindow(renderWindow);

    // Add the actors to the scene
    renderer->AddActor(actor);
    renderer->SetBackground(.3, .2, .1);

    // Render and interact
    renderWindow->Render();
    renderWindowInteractor->Start();
  
}