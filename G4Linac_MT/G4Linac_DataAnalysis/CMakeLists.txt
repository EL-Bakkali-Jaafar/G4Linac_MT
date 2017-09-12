cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(G4Linac_DataAnalysis)
add_compile_options( "-g" )
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
find_package(Geant4 REQUIRED ui_all vis_all)
else()
find_package(Geant4 REQUIRED)
endif()
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include )
file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)
link_directories( /opt/hdf5/lib )
include_directories( /opt/hdf5/include )
add_executable(  G4Linac_DataAnalysis G4Linac_DataAnalysis.cc ${sources} ${headers})
target_link_libraries(G4Linac_DataAnalysis ${Geant4_LIBRARIES} -lhdf5_cpp -lhdf5)
set(_SCRIPTS
dose_heatmap.C
electron_angular_distribution.C
electron_energy_spectrum.C
pdd.C
photon_angular_distribution.C
photon_energy_spectrum.C
photon_spatial_distribution_xy_with_kinetic.C
spatial_distribution_xy.C
electron_spatial_distribution_xy_with_kinetic.C
xprofile.C
yprofile.C
)
foreach(_script ${_SCRIPTS})
configure_file(
${PROJECT_SOURCE_DIR}/macros/${_script}
${PROJECT_BINARY_DIR}/macros/${_script}
COPYONLY
)
endforeach()
