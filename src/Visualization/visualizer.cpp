#include "visualizer.hpp"

Visualizer::Visualizer(double x_dim, double y_dim, double z_dim, double resolution)
{
    mDims[0] = floor(x_dim / resolution);
    mDims[1] = floor(y_dim / resolution);
    mDims[2] = floor(z_dim / resolution);

    mPoints = vtkSmartPointer<vtkPoints>::New();
    
    mGrid = vtkSmartPointer<vtkStructuredGrid>::New();
    mGrid->SetDimensions( mDims[0], mDims[1], mDims[2] );

    mActor = vtkSmartPointer<vtkActor>::New();
    mMapper = vtkSmartPointer<vtkDataSetMapper>::New();
    mRenderer = vtkSmartPointer<vtkRenderer>::New();
    mRenderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    mRenderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();
}

Visualizer::~Visualizer()
{
    
}


vtkSmartPointer<vtkRenderer> Visualizer::get_renderer()
{
    return mRenderer;
}

void Visualizer::start_rendering(int width, int height)
{
    mRenderWindow->AddRenderer(mRenderer);
    mRenderWindowInteractor->SetRenderWindow(mRenderWindow);
    mRenderer->AddActor(mActor);
    // mRenderer->SetBackground(.8, .8, .8);
    mRenderer->SetBackground(1, 1, 1);
    mRenderWindow->SetSize(width, height);
    mRenderWindow->Render();
    mRenderWindowInteractor->Start();
}

void Visualizer::clear_points()
{
    mPoints->Reset();
}

void Visualizer::add_points(vector < array < double, 3> > &points)
{
    int i = 0;
    for(auto point : points)
    {
        mPoints->InsertNextPoint(point.data());
    }
}

void Visualizer::render_demo_sphere( double radius)
{
    vector< array < double, 3 > > points;

    for(double i = 0; i < mDims[0]; i += 0.1 )
    {
        for(double j = 0; j < mDims[1]; j += 0.1 )
        {
            for(double k = 0; k < mDims[2]; k += 0.1 )
            {
                if( (pow(i  - 5.0, 2) + pow(j - 5.0, 2) + pow( k - 5.0, 2)) < (radius * radius))
                {
                    points.push_back(array<double, 3> {i+5.0, j+5.0, k + 5.0});
                }
            }
        }
    }

    add_points(points);

    mGrid->SetPoints(mPoints);

    vtkSmartPointer<vtkPointOccupancyFilter> occupancy = vtkSmartPointer<vtkPointOccupancyFilter>::New();
    occupancy->SetInputData(mGrid);
    occupancy->SetSampleDimensions( mDims[0], mDims[1], mDims[2]);
    occupancy->SetOccupiedValue(255);
    occupancy->Update();

    vtkSmartPointer<vtkThreshold> threshold =
    vtkSmartPointer<vtkThreshold>::New();
    threshold->SetInputConnection(occupancy->GetOutputPort());
    threshold->ThresholdByUpper(100);
    threshold->AllScalarsOff();


    mMapper->SetInputConnection(threshold->GetOutputPort());
    mMapper->ScalarVisibilityOff();

    double flesh[3] = {198/255.0, 134/255.0, 66/255.0};
    mActor->GetProperty()->SetColor(flesh);
    mActor->SetMapper(mMapper);
    start_rendering();
    
}

void Visualizer::render_demo_sphere_mesh( double radius)
{
    vector< array < double, 3 > > points;

    for(double i = 0; i < mDims[0]; i += 0.1 )
    {
        for(double j = 0; j < mDims[1]; j += 0.1 )
        {
            for(double k = 0; k < mDims[2]; k += 0.1 )
            {
                if( (pow(i  - 5.0, 2) + pow(j - 5.0, 2) + pow( k - 5.0, 2)) < (radius * radius))
                {
                    points.push_back(array<double, 3> {i+5.0, j+5.0, k + 5.0});
                }
            }
        }
    }

    add_points(points);
    mGrid->SetPoints(mPoints);

    vtkSmartPointer<vtkPointOccupancyFilter> occupancy = vtkSmartPointer<vtkPointOccupancyFilter>::New();
    occupancy->SetInputData(mGrid);
    occupancy->SetSampleDimensions( mDims[0], mDims[1], mDims[2]);
    occupancy->SetOccupiedValue(255);
    occupancy->Update();

    vtkSmartPointer<vtkMarchingCubes> surface =
    vtkSmartPointer<vtkMarchingCubes>::New();
    surface->SetInputConnection(occupancy->GetOutputPort());
    surface->ComputeNormalsOn();
    surface->SetValue(0, 0.5);

    mMapper->SetInputConnection(surface->GetOutputPort());

    double flesh[3] = {198/255.0, 134/255.0, 66/255.0};
    mActor->GetProperty()->SetColor(flesh);
    mActor->SetMapper(mMapper);
    mMapper->ScalarVisibilityOff();

    start_rendering();
    
}

void Visualizer::render_demo_cube( double radius)
{
    vector< array < double, 3 > > points;

    for(double i = 4; i < 6; i += 0.1 )
    {
        for(double j = 4; j < 6; j += 0.1 )
        {
            for(double k = 4; k < 6; k += 0.1 )
            {
                // if( (i > (0.25 * mDims[0]) && i < (0.75 * mDims[0]) )&&
                //     (j > (0.25 * mDims[1]) && j < (0.75 * mDims[1]) )&&
                //     (k > (0.25 * mDims[2]) && k < (0.75 * mDims[2]) ) )
                {
                    points.push_back(array<double, 3> {i, j, k});
                }
            }
        }
    }

    add_points(points);

    mGrid->SetPoints(mPoints);

    vtkSmartPointer<vtkPointOccupancyFilter> occupancy = vtkSmartPointer<vtkPointOccupancyFilter>::New();
    occupancy->SetInputData(mGrid);
    occupancy->SetSampleDimensions( mDims[0], mDims[1], mDims[2]);
    occupancy->SetOccupiedValue(255);
    occupancy->Update();

    vtkSmartPointer<vtkThreshold> threshold =
    vtkSmartPointer<vtkThreshold>::New();
    threshold->SetInputConnection(occupancy->GetOutputPort());
    threshold->ThresholdByUpper(100);
    threshold->AllScalarsOff();


    mMapper->SetInputConnection(threshold->GetOutputPort());
    mMapper->ScalarVisibilityOff();

    double flesh[3] = {198/255.0, 134/255.0, 66/255.0};
    mActor->GetProperty()->SetColor(flesh);
    mActor->SetMapper(mMapper);
    start_rendering();
    
}

void Visualizer::render_demo_cube_mesh( double radius)
{
    vector< array < double, 3 > > points;

    for(double i = 4; i < 6; i += 0.1 )
    {
        for(double j = 4; j < 6; j += 0.1 )
        {
            for(double k = 4; k < 6; k += 0.1 )
            {
                // if( (i > (0.25 * mDims[0]) && i < (0.75 * mDims[0]) )&&
                //     (j > (0.25 * mDims[1]) && j < (0.75 * mDims[1]) )&&
                //     (k > (0.25 * mDims[2]) && k < (0.75 * mDims[2]) ) )
                {
                    points.push_back(array<double, 3> {i, j, k});
                }
            }
        }
    }

    add_points(points);
    mGrid->SetPoints(mPoints);

    vtkSmartPointer<vtkPointOccupancyFilter> occupancy = vtkSmartPointer<vtkPointOccupancyFilter>::New();
    occupancy->SetInputData(mGrid);
    occupancy->SetSampleDimensions( mDims[0], mDims[1], mDims[2]);
    occupancy->SetOccupiedValue(255);
    occupancy->Update();

    vtkSmartPointer<vtkMarchingCubes> surface =
    vtkSmartPointer<vtkMarchingCubes>::New();
    surface->SetInputConnection(occupancy->GetOutputPort());
    surface->ComputeNormalsOn();
    surface->SetValue(0, 0.5);

    mMapper->SetInputConnection(surface->GetOutputPort());

    double flesh[3] = {198/255.0, 134/255.0, 66/255.0};
    mActor->GetProperty()->SetColor(flesh);
    mActor->SetMapper(mMapper);
    mMapper->ScalarVisibilityOff();

    start_rendering();
    
}

void Visualizer::render_occupancy()
{

}

