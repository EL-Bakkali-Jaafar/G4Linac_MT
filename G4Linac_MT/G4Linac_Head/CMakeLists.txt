cmake_minimum_required(VERSION 2.6 FATAL_ERROR)
project(G4Linac_Head)
option(WITH_GEANT4_UIVIS "Build example with Geant4 UI and Vis drivers" ON)
if(WITH_GEANT4_UIVIS)
  find_package(Geant4 REQUIRED ui_all vis_all)
else()
  find_package(Geant4 REQUIRED)
endif()
include(${Geant4_USE_FILE})
include_directories(${PROJECT_SOURCE_DIR}/include )
add_compile_options( "-g" )

file(GLOB sources ${PROJECT_SOURCE_DIR}/src/*.cc)
file(GLOB headers ${PROJECT_SOURCE_DIR}/include/*.hh)
link_directories( /opt/hdf5/lib )
include_directories( /opt/hdf5/include )
add_executable( G4Linac_Head G4Linac_Head.cc ${sources} ${headers})
target_link_libraries( G4Linac_Head ${Geant4_LIBRARIES} -lhdf5_cpp -lhdf5)
set(SCRIPTS
  run.mac
linac.geom
run_geom.mac
  vis.mac
g4linac_head.sh

  )

foreach(_script ${SCRIPTS})
  configure_file(
    ${PROJECT_SOURCE_DIR}/${_script}
    ${PROJECT_BINARY_DIR}/${_script}
    COPYONLY
    )
endforeach()
