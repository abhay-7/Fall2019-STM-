# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.15.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.15.3/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/Users/roxy/Desktop/Ultrasound Code/Fall2019-STM-/test"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/Users/roxy/Desktop/Ultrasound Code/Fall2019-STM-/test/build"

# Include any dependencies generated for this target.
include CMakeFiles/test_visualizer.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/test_visualizer.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_visualizer.dir/flags.make

CMakeFiles/test_visualizer.dir/test_visualizer.cpp.o: CMakeFiles/test_visualizer.dir/flags.make
CMakeFiles/test_visualizer.dir/test_visualizer.cpp.o: ../test_visualizer.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/Users/roxy/Desktop/Ultrasound Code/Fall2019-STM-/test/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_visualizer.dir/test_visualizer.cpp.o"
	/Library/Developer/CommandLineTools/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/test_visualizer.dir/test_visualizer.cpp.o -c "/Users/roxy/Desktop/Ultrasound Code/Fall2019-STM-/test/test_visualizer.cpp"

CMakeFiles/test_visualizer.dir/test_visualizer.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_visualizer.dir/test_visualizer.cpp.i"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/Users/roxy/Desktop/Ultrasound Code/Fall2019-STM-/test/test_visualizer.cpp" > CMakeFiles/test_visualizer.dir/test_visualizer.cpp.i

CMakeFiles/test_visualizer.dir/test_visualizer.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_visualizer.dir/test_visualizer.cpp.s"
	/Library/Developer/CommandLineTools/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/Users/roxy/Desktop/Ultrasound Code/Fall2019-STM-/test/test_visualizer.cpp" -o CMakeFiles/test_visualizer.dir/test_visualizer.cpp.s

# Object files for target test_visualizer
test_visualizer_OBJECTS = \
"CMakeFiles/test_visualizer.dir/test_visualizer.cpp.o"

# External object files for target test_visualizer
test_visualizer_EXTERNAL_OBJECTS =

test_visualizer: CMakeFiles/test_visualizer.dir/test_visualizer.cpp.o
test_visualizer: CMakeFiles/test_visualizer.dir/build.make
test_visualizer: src/Visualization/libvisualization.a
test_visualizer: /usr/local/lib/libvtkDomainsChemistryOpenGL2-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkFiltersFlowPaths-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkFiltersGeneric-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkFiltersHyperTree-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkFiltersParallelImaging-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkFiltersPoints-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkFiltersProgrammable-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkFiltersSMP-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkFiltersSelection-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkFiltersTexture-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkFiltersTopology-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkFiltersVerdict-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkGeovisCore-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkIOAMR-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkIOAsynchronous-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkIOCityGML-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkIOEnSight-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkIOExodus-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkIOExportOpenGL2-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkIOExportPDF-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkIOImport-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkIOInfovis-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkIOLSDyna-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkIOMINC-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkIOMovie-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkIOPLY-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkIOParallel-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkIOParallelXML-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkIOSQL-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkIOSegY-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkIOTecplotTable-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkIOVeraOut-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkIOVideo-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkImagingMorphological-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkImagingStatistics-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkImagingStencil-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkInteractionImage-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkRenderingContextOpenGL2-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkRenderingImage-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkRenderingLOD-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkRenderingVolumeOpenGL2-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkViewsContext2D-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkViewsInfovis-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkDomainsChemistry-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkverdict-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkproj-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkFiltersAMR-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkpugixml-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkIOExport-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkRenderingGL2PSOpenGL2-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkgl2ps-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtklibharu-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtklibxml2-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtktheora-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkogg-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkFiltersParallel-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkexodusII-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkIOGeometry-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkIONetCDF-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkNetCDF-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkjsoncpp-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkParallelCore-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkIOLegacy-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtksqlite-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkhdf5-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkhdf5_hl-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkRenderingOpenGL2-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkglew-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkImagingMath-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkChartsCore-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkRenderingContext2D-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkFiltersImaging-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkInfovisLayout-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkInfovisCore-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkViewsCore-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkInteractionWidgets-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkFiltersHybrid-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkImagingGeneral-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkImagingSources-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkFiltersModeling-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkImagingHybrid-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkIOImage-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkDICOMParser-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkmetaio-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkjpeg-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkpng-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtktiff-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkInteractionStyle-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkFiltersExtraction-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkFiltersStatistics-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkImagingFourier-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkRenderingAnnotation-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkImagingColor-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkRenderingVolume-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkImagingCore-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkIOXML-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkIOXMLParser-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkIOCore-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkdoubleconversion-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtklz4-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtklzma-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkexpat-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkRenderingLabel-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkRenderingFreeType-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkRenderingCore-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkCommonColor-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkFiltersGeometry-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkFiltersSources-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkFiltersGeneral-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkCommonComputationalGeometry-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkFiltersCore-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkCommonExecutionModel-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkCommonDataModel-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkCommonMisc-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkCommonSystem-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtksys-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkCommonTransforms-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkCommonMath-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkCommonCore-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkfreetype-8.2.1.dylib
test_visualizer: /usr/local/lib/libvtkzlib-8.2.1.dylib
test_visualizer: CMakeFiles/test_visualizer.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/Users/roxy/Desktop/Ultrasound Code/Fall2019-STM-/test/build/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable test_visualizer"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_visualizer.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_visualizer.dir/build: test_visualizer

.PHONY : CMakeFiles/test_visualizer.dir/build

CMakeFiles/test_visualizer.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_visualizer.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_visualizer.dir/clean

CMakeFiles/test_visualizer.dir/depend:
	cd "/Users/roxy/Desktop/Ultrasound Code/Fall2019-STM-/test/build" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/Users/roxy/Desktop/Ultrasound Code/Fall2019-STM-/test" "/Users/roxy/Desktop/Ultrasound Code/Fall2019-STM-/test" "/Users/roxy/Desktop/Ultrasound Code/Fall2019-STM-/test/build" "/Users/roxy/Desktop/Ultrasound Code/Fall2019-STM-/test/build" "/Users/roxy/Desktop/Ultrasound Code/Fall2019-STM-/test/build/CMakeFiles/test_visualizer.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/test_visualizer.dir/depend

