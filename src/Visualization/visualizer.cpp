#include "visualizer.hpp"

Visualizer::Visualizer(double x_dim, double y_dim, double z_dim, double resolution)
{
    mResolution = resolution;

    mDims[0] = x_dim;
    mDims[1] = y_dim;
    mDims[2] = z_dim;

    mGridDims[0] = floor(x_dim / resolution);
    mGridDims[1] = floor(y_dim / resolution);
    mGridDims[2] = floor(z_dim / resolution);

    mPoints = vtkSmartPointer<vtkPoints>::New();
    
    mGrid = vtkSmartPointer<vtkStructuredGrid>::New();
    mGrid->SetDimensions( mGridDims[0], mGridDims[1], mGridDims[2] );

    mActor = vtkSmartPointer<vtkActor>::New();
    mGridActor = vtkSmartPointer<vtkActor>::New();
    mMapper = vtkSmartPointer<vtkDataSetMapper>::New();
    mRenderer = vtkSmartPointer<vtkRenderer>::New();
    mRenderWindow = vtkSmartPointer<vtkRenderWindow>::New();
    mRenderWindowInteractor = vtkSmartPointer<vtkRenderWindowInteractor>::New();

    generate_grid(2);
}

Visualizer::~Visualizer()
{
    
}


vtkSmartPointer<vtkRenderer> Visualizer::get_renderer()
{
    return mRenderer;
}

void Visualizer::start_rendering(int width, int height, bool grid)
{
    if(grid)
        mRenderer->AddActor(mGridActor);

    mRenderWindow->AddRenderer(mRenderer);
    mRenderWindowInteractor->SetRenderWindow(mRenderWindow);
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

void Visualizer::generate_grid(double resolution)
{
    long num_points = 0;
    vtkSmartPointer<vtkPoints> grid_points = vtkSmartPointer<vtkPoints>::New();
    vtkSmartPointer<vtkCellArray> grid_lines = vtkSmartPointer<vtkCellArray>::New();
    vtkSmartPointer<vtkPolyData> grid_polydata = vtkSmartPointer<vtkPolyData>::New();

    for(double j = 0; j <= mDims[1]; j += resolution )
    {
        for(double k = 0; k <= mDims[2]; k += resolution )
        {
            grid_points->InsertNextPoint(0, j, k);
            grid_points->InsertNextPoint(mDims[0], j, k);
            vtkSmartPointer<vtkLine> line = vtkSmartPointer<vtkLine>::New();
            line->GetPointIds()->SetId(0,num_points++);
            line->GetPointIds()->SetId(1,num_points++);
            grid_lines->InsertNextCell(line);
        }
    }

    for(double i = 0; i <= mDims[0]; i += resolution )
    {
        for(double k = 0; k <= mDims[2]; k += resolution )
        {
            grid_points->InsertNextPoint(i, 0, k);
            grid_points->InsertNextPoint(i, mDims[1], k);
            vtkSmartPointer<vtkLine> line = vtkSmartPointer<vtkLine>::New();
            line->GetPointIds()->SetId(0,num_points++);
            line->GetPointIds()->SetId(1,num_points++);
            grid_lines->InsertNextCell(line);
        }
    }

    for(double i = 0; i <= mDims[0]; i += resolution )
    {
        for(double j = 0; j <= mDims[1]; j += resolution )
        {
            grid_points->InsertNextPoint(i, j, 0);
            grid_points->InsertNextPoint(i, j, mDims[2]);
            vtkSmartPointer<vtkLine> line = vtkSmartPointer<vtkLine>::New();
            line->GetPointIds()->SetId(0,num_points++);
            line->GetPointIds()->SetId(1,num_points++);
            grid_lines->InsertNextCell(line);
        }
    }

    grid_polydata->SetPoints(grid_points);
    grid_polydata->SetLines(grid_lines);
    vtkSmartPointer<vtkDataSetMapper> grid_mapper = vtkSmartPointer<vtkDataSetMapper>::New();

    grid_mapper->SetInputData(grid_polydata);
    grid_mapper->ScalarVisibilityOff();

    double color [3] = {0, 0, 0};
    mGridActor->GetProperty()->SetColor(color);
    mGridActor->SetMapper(grid_mapper);

}

void Visualizer::render_demo_sphere( double radius)
{
    vector< array < double, 3 > > points;

    for(double i = 0; i < mGridDims[0]; i += mResolution )
    {
        for(double j = 0; j < mGridDims[1]; j += mResolution )
        {
            for(double k = 0; k < mGridDims[2]; k += mResolution )
            {
                if( (pow(i  - 5.0, 2) + pow(j - 5.0, 2) + pow( k - 5.0, 2)) < (radius * radius))
                {
                    points.push_back(array<double, 3> {i, j, k });
                }
            }
        }
    }

    add_points(points);

    mGrid->SetPoints(mPoints);

    vtkSmartPointer<vtkPointOccupancyFilter> occupancy = vtkSmartPointer<vtkPointOccupancyFilter>::New();
    occupancy->SetInputData(mGrid);
    occupancy->SetSampleDimensions( mGridDims[0], mGridDims[1], mGridDims[2]);
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
    mRenderer->AddActor(mActor);
    start_rendering();
    
}

void Visualizer::render_demo_sphere_mesh( double radius)
{
    vector< array < double, 3 > > points;

    for(double i = 0; i < mGridDims[0]; i += mResolution )
    {
        for(double j = 0; j < mGridDims[1]; j += mResolution )
        {
            for(double k = 0; k < mGridDims[2]; k += mResolution )
            {
                if( (pow(i  - 5.0, 2) + pow(j - 5.0, 2) + pow( k - 5.0, 2)) < (radius * radius))
                {
                    points.push_back(array<double, 3> {i, j, k });
                }
            }
        }
    }

    add_points(points);

    vtkSmartPointer<vtkPolyData> pd = vtkSmartPointer<vtkPolyData>::New();
    pd->SetPoints(mPoints);

    vtkSmartPointer<vtkPointOccupancyFilter> occupancy = vtkSmartPointer<vtkPointOccupancyFilter>::New();
    occupancy->SetInputData(pd);
    occupancy->SetSampleDimensions( mGridDims[0], mGridDims[1], mGridDims[2]);
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
    mRenderer->AddActor(mActor);

    start_rendering();
    
}

void Visualizer::render_demo_cube( double length)
{
    vector< array < double, 3 > > points;

    for(double i = mDims[0]/2 - length/2; i < mDims[0]/2 + length/2; i += mResolution )
    {
        for(double j = mDims[1]/2 - length/2; j < mDims[1]/2 + length/2; j += mResolution )
        {
            for(double k = mDims[2]/2 - length/2; k < mDims[2]/2 + length/2; k += mResolution )
            {
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
    occupancy->SetSampleDimensions( mGridDims[0], mGridDims[1], mGridDims[2]);
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
    mRenderer->AddActor(mActor);

    start_rendering();
    
}

void Visualizer::render_demo_cube_mesh( double length)
{
    vector< array < double, 3 > > points;

    for(double i = mDims[0]/2 - length/2; i < mDims[0]/2 + length/2; i += mResolution )
    {
        for(double j = mDims[1]/2 - length/2; j < mDims[1]/2 + length/2; j += mResolution )
        {
            for(double k = mDims[2]/2 - length/2; k < mDims[2]/2 + length/2; k += mResolution )
            {
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
    occupancy->SetSampleDimensions( mGridDims[0], mGridDims[1], mGridDims[2]);
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
    mRenderer->AddActor(mActor);

    start_rendering();
    
}

void Visualizer::render_occupancy()
{

}

