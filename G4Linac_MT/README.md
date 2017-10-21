# G4Linac_MT
 a Geant4-based application for modeling medical linear accelerators used in radiotherapy ( Multithreaded version)
 
<b>Quick Introduction to G4Linac_MT</b>

The word G4Linac_MT is an acronym of “Geant4 Application For Modelling Linac with support of Multi Threading mode ”, as its name indicates, this code is dedicated to accurately modeling medical linear accelerator used in radiotherapy to treat cancer diseases by employing ionizing radiations. This code has been developed by Dr. Jaafar EL Bakkali, which is actually working as Assistant Professor of Nuclear Physics in Morocco. G4Linac_MT has been written in C++ language from scratch to perform all mandatory tasks required for validating the Monte Carlo Geant4 code for such Linac operating at photon or electron mode. The code supports the following features:
The code was built on the top of the last known stable version of Geant4 (namely Geant4 .10.3).
 It uses multi-threading option allowing it to start multiple Monte Carlo simulations at the same time and finally it merges output data delivered by different threads at the end of a run.
The code can accurately modeling the physics of all components of treatment head of  a given Linac.
The code can accurately modeling the dose distribution either in homogeneous or either in heterogeneous water phantoms.
The code uses script language as the material and geometry specification are read from .geom file (GEANT4 GEOMETRY FROM TEXT FILE version 1.0).
It uses a new format of PhaseSpace file based on HDF5 file format by the mean of the HDF5 C++ library that I was developped in earlier years. For more information please consult this paper “ Investigation of the HDF5 C++ Library in Development of
 New Phase-Space I/O for Radiotherapy Simulation Using Monte Carlo Geant4 Code”.
In order to avoiding unnecessary time spent by writing data to the physical disk, those data are stored in RAM memory and finally are dumped to the physical disk at the end of a Run.
 It also stores the dosimetric data on a file with binary format, this for each thread. At the end of a run all dosimetric files are merged together in order to produce a single one.
The code contains a tool that can be serve at extracting and visualizing data, two kind of files are supported namely: h5PhaseSpace and DosimetricData.

<b>Modules of G4Linac_MT</b>

G4Linac_MT code consists of following three modules:

<b>G4Linac_Head</b>

This module lets user construct  a Geant4 model of a typical Linac treatment head geometry that includes:
Invariant elements: primary collimator, output window, monitors chamber, mirror and mesh.
Elements which strongly depend on the selected irradiation energy, namely X-ray target and flattening filter.
Others that depend on the shape of the beam, namely removable jaws and multi-leaf system.

The construct of a model geometry is simply taken place by reading Geant4 Geometry From Text code. G4Linac_Head module allows one to start its Monte Carlo simulation in multi-threading mode. Indeed, in each thread it will create an h5PhaseSpace file at the end of a thread-run, after that all H5PhaseSpace files will be finally merged in a single one, thus without user intervention and is done at the end of a given Run. It should be noted here, that this code is the only one which uses a new phase-space file format based on HDF5 file format and so called h5PhaseSpace file. Regarding variance reduction technique, the module uses the technique called BREMSPE for photons bremsstrahlung splitting.

<b>G4Linac_DoseCal</b>

This module lets user perform Monte Carlo simulation of doses deposition in either homogeneous or heterogeneous water phantoms. The user can run multiple simulation at the same time, since this code supports multi-threading features. In aim to reduce RAM memory usage, all thread share some copy of h5PhaseSpace file which is used as an input to the Monte Carlo dose calculations. At the end of execution of each run, this module merges DosimetricData whi are produced produced by each thread in a binary file which can be furherly analyzed by G4Linac_DataAnalysis module.


<b>G4Linac_DataAnalysis</b>

This module can be used for data analysis and histogramming tasks. The data can be either h5PhaseSpace data or either DosimetricData. For h5PhaseSpace data, this tool can be used for histogramming ten physics quantities
can be used for histogramming ten physics quantities:
  photon energy spectrum
  electron energy spectrum
  photon angular distribution
  electron angular distribution
  photon spatial distribution in plane XY
  electron spatial distribution in plane XY
  particle spatial distribution in plane XY
  photon spatial distribution in plane XY in function of its kinetic energies
  electron spatial distribution in plane XY in function of its kinetic energies
   particle spatial distribution in plane XY in function of its kinetic energies


For DosimetricData, this tool can be used for performing histogramming tasks of six physics quantities:

   percentage depth dose curve
   Cross-plane  Dose Profile
   In-plane Dose Profile
   Dose Heat Map in plane YZ
   Dose Heat Map in plane XZ
   Dose Heat Map in plane XY
  
This tool also allows one to draw Relative Standard Deviation curves for three dosimetric quantities:
  rsd curve associated to percentage depth dose
  rsd curve associated to Cross-plane Dose Profile
  rsd curve associated to In-plane Dose Profile


<b>H5Phase-Space data format</b>

h5PhaseSpace is a new PhaseSpace file format that stores all particle data at a given plane. I have developed this PhaseSpace file format since 2015 where its first version can be worked only in a sequential mode. Todays, a new version has been developed that exploits the multi-threading capabilities of Geant4 Monte Carlo code. The h5PhaseSpace data consists of two distinct file formats:
h5PhaseSpace_name.h5: an hdf5 file which keeps all information about recorded particles that include: the number of simulated histories, particle kinetic energy, particle statistical weight, particle PDGE code, particle position, and particle momentum direction. It stores also  Monte Carlo simulation information include number of active events, event unique ID of a number of particles created at the same Geant4 event  unit, number of these particles, number of original histories and the z-coordinate of h5PhaseSpace plane.
h5PhaseSpace_name.summary: an ASCII text file generated at the end of a Geant4 Run unit which has an extension of “.summary”. It stores meaningful statistical data about a given Monte Carlo simulation shuch as number of simulated histories, percent of active events, max-mean-min energy and weight of all recorded particles, percent of each of them, CPU time spent by a Monte Carlo simulation and date of creation of an  h5PhaseSpace file. It should be noted here, that all of these data are self-explanatory.


 <b>DosimericData data format</b>
 
DosimericData is a binary file that keeps all information about dosimetric and phantom data, such as number of voxels along x axis, number of voxels along y axis, number of voxels along z axis, voxalized phantom dimensions along x, y and z axis, number of events recorded in each voxel, absorbed dose and associated relative standard deviation in a given voxel. At the end of a given Geant4 Run unit, these useful information are dumped to an ASCII text file which can be furthmore readable by users. This data will be used as input parameters for G4Linac_DataAnalysis module in order to perform histogramming tasks of dosimeric functions such as 2d dose heat map along a given axis which is a common visualizing method for plotting data in a graphical manner.

