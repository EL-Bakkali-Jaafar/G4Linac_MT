//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#
  AUTHOR: Dr. Jaafar EL Bakkali, Assistant Professor of Nuclear Physics, Rabat, Morocco.
  e-mail: bahmedj@gmail.com

  For documentation
  see http://G4Linac_MT.github.com
 
  10/08/2017: public version 1.0
 
#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
#include "RunAction.hh"
#include <sstream>
#include "PhysicsList.hh"
#include <stdio.h>
#include "G4ios.hh"
#include <ctime>
#include "G4Threading.hh"
#include "G4RunManager.hh"
#include "DetectorConstruction.hh"
#ifndef H5_NO_NAMESPACE
#ifndef H5_NO_STD
using std::cout;
using std::endl;
#endif  // H5_NO_STD
#endif
#include "H5Cpp.h"
#ifndef H5_NO_NAMESPACE
using namespace H5;
#endif
/*  DECLARATION  OF ELEMENTS OF H5_PHASE_SPACE DATA */
const std::string DatasetName_histories("BeamData"),
                  MEMBER_HISTORIES("_NUMBER_OF_HISTORIES"),
                  MEMBER_Z_STOP("_Z_STOP"),
                  MEMBER_NUMBER_OF_ACTIVE_EVENTS("_NUMBER_OF_ACTIVE_EVENTS"),
                  DatasetName_event("EventData"),
                  MEMBER_ENTERIES("_ENTERIES"),
                  MEMBER_EVENTID("_EVENTID"),
                  DatasetName("PhspData"),
                  MEMBER_PART_PDGE("_PART_PDGE"),
                  MEMBER_PART_WEIGHT("_PART_WEIGHT"),
                  MEMBER_PART_POS_X("_PART_POS_X"),
                  MEMBER_PART_POS_Y("_PART_POS_Y"),
                  MEMBER_PART_POS_Z("_PART_POS_Z"),
                  MEMBER_PART_DIR_X("_PART_DIR_X"),
                  MEMBER_PART_DIR_Y("_PART_DIR_Y"),
                  MEMBER_PART_DIR_Z("_PART_DIR_Z"),
                  MEMBER_PART_KINETIC("_PART_KINETIC");
std::string       ANSI_RESET_COLOR = "\033[0m",
                  ANSI_GREEN = "\033[32m",

/*  TERMINAL HEADER */
                  TERMINAL_HEADER =

"#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#\nG4LINAC_MT version 1.O: a Geant4-based application for Medical Linear Accelerator\nDeveloped by Dr.Jaafar EL Bakkali, Assistant Prof. of Nuclear Physics, Rabat, Morocco,  10/09/ 2017\nWebpage :https://github.com/EL-Bakkali-Jaafar/G4Linac_MT\n#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#\n";

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
/*  METHOD USED TO CALCULATE CPU TIME SPEND BY SIMULATION*/
 double  RunAction::diffclock(clock_t clock1,clock_t clock2)
  {
	double diffticks=clock1-clock2;
	double diffms=(diffticks*1000)/CLOCKS_PER_SEC;
	return diffms;
   } 
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
RunAction::RunAction()
{
/*  INITIALIZATION OF VARIABLES*/
NUMBER_OF_PHOTONS                  =  0;
NUMBER_OF_ELECTRONS                =  0;
NUMBER_OF_POSITRONS                =  0;
NUMBER_OF_PROTONS                  =  0;
NUMBER_OF_NEUTRONS                 =  0;
this->NUMBER_OF_PARTICLES          =  0;
NUMBER_OF_ENTRIES                  =  0;
NUMBER_OF_ACTIVE_EVENTS            =  0;
EVENT_ID                           =  0;
ELECTRON_ENERGY_MAX                =  0;
ELECTRON_ENERGY_MIN                =  0;
ELECTRON_ENERGY_MEAN               =  0;
PHOTON_ENERGY_MAX                  =  0;
PHOTON_ENERGY_MIN                  =  0;
PHOTON_ENERGY_MEAN                 =  0;
POSITRON_ENERGY_MAX                =  0;
PHOTON_WEIGHT_MAX                  =  0;
PHOTON_WEIGHT_MIN                  =  0;
PHOTON_WEIGHT_MEAN                 =  0;
ELECTRONS_WEIGHT_MAX               =  0;
ELECTRONS_WEIGHT_MIN               =  0;
ELECTRONS_WEIGHT_MEAN              =  0;
POSITRONS_WEIGHT_MAX               =  0;
POSITRONS_WEIGHT_MIN               =  0;
POSITRONS_WEIGHT_MEAN              =  0;
PROTON_WEIGHT_MAX                  =  0;
PROTON_WEIGHT_MIN                  =  0;
PROTON_WEIGHT_MEAN                 =  0;
NEUTRON_WEIGHT_MAX                 =  0;
NEUTRON_WEIGHT_MIN                 =  0;
NEUTRON_WEIGHT_MEAN                =  0;
POSITRON_ENERGY_MIN                =  0;
POSITRON_ENERGY_MEAN               =  0;
PROTON_ENERGY_MAX                  =  0;
PROTON_ENERGY_MIN                  =  0;
PROTON_ENERGY_MEAN                 =  0;
NEUTRON_ENERGY_MAX                 =  0;
NEUTRON_ENERGY_MIN                 =  0;
NEUTRON_ENERGY_MEAN                =  0;
NUMBER_OF_ACTIVE_EVENTS            =  0;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
RunAction::~RunAction()
{
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
/*  READ H5_PHASE_SPACE DATA*/
void RunAction::READ_PHSP_DATA( std::string _H5PhaseSpaceFileName)
{
try{
H5File file( _H5PhaseSpaceFileName, H5F_ACC_RDONLY );
DataSet dataset = file.openDataSet( DatasetName );
H5::CompType mtype2( sizeof(PhspData) );
G4int data_size  = dataset.getSpace().getSimpleExtentNpoints();
RAM_PhspData    = new PhspData[data_size];
mtype2.insertMember(MEMBER_PART_WEIGHT,  HOFFSET(PhspData, PART_WEIGHT),   H5::PredType::NATIVE_DOUBLE);
mtype2.insertMember(MEMBER_PART_POS_X,   HOFFSET(PhspData, PART_POS_X),    H5::PredType::NATIVE_DOUBLE);
mtype2.insertMember(MEMBER_PART_PDGE,    HOFFSET(PhspData, PART_PDGE),     H5::PredType::NATIVE_INT);
mtype2.insertMember(MEMBER_PART_POS_Y,   HOFFSET(PhspData, PART_POS_Y),    H5::PredType::NATIVE_DOUBLE);
mtype2.insertMember(MEMBER_PART_POS_Z,   HOFFSET(PhspData, PART_POS_Z),    H5::PredType::NATIVE_DOUBLE);
mtype2.insertMember(MEMBER_PART_DIR_X,   HOFFSET(PhspData, PART_DIR_X),    H5::PredType::NATIVE_DOUBLE);
mtype2.insertMember(MEMBER_PART_DIR_Y,   HOFFSET(PhspData, PART_DIR_Y),    H5::PredType::NATIVE_DOUBLE);
mtype2.insertMember(MEMBER_PART_DIR_Z,   HOFFSET(PhspData, PART_DIR_Z),    H5::PredType::NATIVE_DOUBLE);
mtype2.insertMember(MEMBER_PART_KINETIC, HOFFSET(PhspData, PART_KINETIC),  H5::PredType::NATIVE_DOUBLE);
dataset.read( RAM_PhspData, mtype2 );
G4cout<< " G4LINAC_HEAD-> NUMBER OF PARTICLES IN  " <<_H5PhaseSpaceFileName<< " IS  " << data_size<<G4endl;
for (int i=0; i< data_size; i++) myPhspData_Vector.push_back(RAM_PhspData[i]);
}
catch( FileIException error )
{
error.printError();
}
catch( DataSetIException error ){
error.printError();
}
catch( DataSpaceIException error )
{
error.printError();
}
catch( DataTypeIException error )
{
 error.printError();
}
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
/*  READ BEAM DATA*/
void RunAction::READ_BEAM_DATA( std::string _H5PhaseSpaceFileName)
 {
try{
const std::string FileName(_H5PhaseSpaceFileName);
H5File file( FileName, H5F_ACC_RDONLY );
DataSet dataset_histories = file.openDataSet( DatasetName_histories );
H5::CompType mtype_beam_data( sizeof(BeamData) );
mtype_beam_data.insertMember(MEMBER_HISTORIES,     HOFFSET(BeamData, NUMBER_OF_HISTORIES),      H5::PredType::NATIVE_INT)   ;
mtype_beam_data.insertMember(MEMBER_Z_STOP   ,     HOFFSET(BeamData, Z_STOP)            ,      H5::PredType::NATIVE_DOUBLE) ;
dataset_histories.read( myBeamData, mtype_beam_data );
myTotalBeamData->NUMBER_OF_HISTORIES= myBeamData->NUMBER_OF_HISTORIES;
myTotalBeamData->Z_STOP = myBeamData->Z_STOP;
this->Z_STOP=myBeamData->Z_STOP;
}
catch( FileIException error )
{
error.printError();
}
catch( DataSetIException error ){
error.printError();
}
catch( DataSpaceIException error )
{
error.printError();
}
catch( DataTypeIException error )
{
 error.printError();
}}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
/*  READ EVENT DATA*/
void RunAction::READ_EVENT_DATA( std::string _H5PhaseSpaceFileName)
{
try{
const std::string FileName(_H5PhaseSpaceFileName);
H5File file( FileName, H5F_ACC_RDONLY );
DataSet dataset_event = file.openDataSet( DatasetName_event );
H5::CompType mtype_event( sizeof(EventData) );
int data_event_size=dataset_event.getSpace().getSimpleExtentNpoints();
RAM_EventData = new EventData[data_event_size];
mtype_event.insertMember(MEMBER_EVENTID,  HOFFSET(EventData, EVENT_ID),                  H5::PredType::NATIVE_INT);
mtype_event.insertMember(MEMBER_ENTERIES, HOFFSET(EventData, NUMBER_OF_ENTRIES),         H5::PredType::NATIVE_INT);
dataset_event.read( RAM_EventData, mtype_event );
for (int i=0; i< data_event_size; i++) myEventData_Vector.push_back(RAM_EventData[i]);
delete [] RAM_EventData;
}
catch( FileIException error )
{
error.printError();
}
catch( DataSetIException error ){
error.printError();
}
catch( DataSpaceIException error )
{
error.printError();
}
catch( DataTypeIException error )
{
 error.printError();
}
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void RunAction::BeginOfRunAction(const G4Run* )
{
 begin=clock();
/*-------------TERMINAL HEADER-------------------*/
G4cout<<TERMINAL_HEADER<<G4endl;
/*-------------TERMINAL HEADER-------------------*/
G4RunManager* runManager = G4RunManager::GetRunManager();
DetectorConstruction* pDetectorConstruction = (DetectorConstruction*)(runManager->GetUserDetectorConstruction());
G4cout<< " G4LINAC_HEAD-> STARTING SIMULATION ! "<<G4endl;
G4cout<< " G4LINAC_HEAD-> NUMBER OF THREADS IS " <<pDetectorConstruction->NUMBER_OF_THREADS <<G4endl;
G4cout<< " G4LINAC_HEAD-> Please Wait, Monte Carlo Simulation  can take several hours! "<<G4endl;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void RunAction::EndOfRunAction(const G4Run*)
{
end=clock();
G4RunManager* runManager = G4RunManager::GetRunManager();
DetectorConstruction* pDetectorConstruction = (DetectorConstruction*)(runManager->GetUserDetectorConstruction()); 
for (int i=0; i< pDetectorConstruction->NUMBER_OF_THREADS; i++)
{
std::string h5PhaseSpaceNameThread= pDetectorConstruction->H5_PHASE_SPACE_NAME_WITHOUT_EXTENSION+"_"+ std::to_string(i) +".h5";
READ_BEAM_DATA(h5PhaseSpaceNameThread);
READ_PHSP_DATA(h5PhaseSpaceNameThread);
READ_EVENT_DATA(h5PhaseSpaceNameThread);
std::remove(h5PhaseSpaceNameThread.c_str());
this->H5PhaseSpaceFileName= pDetectorConstruction->H5_PHASE_SPACE_NAME_WITHOUT_EXTENSION +".h5";
G4cout<< " G4LINAC_HEAD-> ROMOVING H5PHASE_SPACE NAMED  " << h5PhaseSpaceNameThread<<G4endl; 
}
WRITE_PHASE_SPACE_FILE(this->H5PhaseSpaceFileName);
SUMMARY();
G4cout<< " G4LINAC_HEAD-> PHASE SPACE FILE NAMED  " << this->H5PhaseSpaceFileName.c_str()<<" HAS BEEN SUCCESSFULLY CREATED !"<<G4endl; 
G4cout<< " G4LINAC_HEAD-> END OF SIMULATION ! "<<G4endl;
G4cout<<"#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#"<< G4endl;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void RunAction::WRITE_PHASE_SPACE_FILE(std::string FILE_NAME)
{
try{



const std::string FileName(FILE_NAME);
hsize_t dim[1], dim_event[1], dim_histories[1];
dim_histories[0] = 1;
dim[0]=myPhspData_Vector.size();
dim_event[0]  =   myEventData_Vector.size();
myBeamData->NUMBER_OF_ACTIVE_EVENTS=dim_event[0] ;
int rank                = sizeof(dim) / sizeof(hsize_t);
int rank_event          = sizeof(dim_event) / sizeof(hsize_t);
int rank_histories      = sizeof(dim_histories) / sizeof(hsize_t);
H5::CompType mtype(sizeof(PhspData));
mtype.insertMember(MEMBER_PART_PDGE,    HOFFSET(PhspData, PART_PDGE),     H5::PredType::NATIVE_INT   );
mtype.insertMember(MEMBER_PART_WEIGHT,  HOFFSET(PhspData, PART_WEIGHT),   H5::PredType::NATIVE_DOUBLE);
mtype.insertMember(MEMBER_PART_POS_X,   HOFFSET(PhspData, PART_POS_X),    H5::PredType::NATIVE_DOUBLE );
mtype.insertMember(MEMBER_PART_POS_Y,   HOFFSET(PhspData, PART_POS_Y),    H5::PredType::NATIVE_DOUBLE );
mtype.insertMember(MEMBER_PART_POS_Z,   HOFFSET(PhspData, PART_POS_Z),    H5::PredType::NATIVE_DOUBLE );
mtype.insertMember(MEMBER_PART_DIR_X,   HOFFSET(PhspData, PART_DIR_X),    H5::PredType::NATIVE_DOUBLE );
mtype.insertMember(MEMBER_PART_DIR_Y,   HOFFSET(PhspData, PART_DIR_Y),    H5::PredType::NATIVE_DOUBLE );
mtype.insertMember(MEMBER_PART_DIR_Z,   HOFFSET(PhspData, PART_DIR_Z),    H5::PredType::NATIVE_DOUBLE );
mtype.insertMember(MEMBER_PART_KINETIC, HOFFSET(PhspData, PART_KINETIC),  H5::PredType::NATIVE_DOUBLE );
H5::CompType mtype_event(sizeof(EventData));
mtype_event.insertMember(MEMBER_EVENTID,  HOFFSET(EventData, EVENT_ID),                  H5::PredType::NATIVE_INT);
mtype_event.insertMember(MEMBER_ENTERIES, HOFFSET(EventData, NUMBER_OF_ENTRIES),         H5::PredType::NATIVE_INT);
H5::CompType mtype_beam_data(sizeof(BeamData));
mtype_beam_data.insertMember(MEMBER_HISTORIES,  HOFFSET(BeamData, NUMBER_OF_HISTORIES),   H5::PredType::NATIVE_INT);
mtype_beam_data.insertMember(MEMBER_NUMBER_OF_ACTIVE_EVENTS,  HOFFSET(BeamData, NUMBER_OF_ACTIVE_EVENTS),   H5::PredType::NATIVE_INT);
mtype_beam_data.insertMember(MEMBER_Z_STOP,     HOFFSET(BeamData, Z_STOP),               H5::PredType::NATIVE_DOUBLE);
H5::DataSpace space(rank, dim);
H5::DataSpace space_event(rank_event, dim_event);
H5::DataSpace space_histories(rank_histories, dim_histories);
H5::H5File *file                 = new H5::H5File( FileName, H5F_ACC_TRUNC	);
H5::DataSet *dataset             = new H5::DataSet(file->createDataSet(DatasetName, mtype, space));
H5::DataSet *dataset_event       = new H5::DataSet(file->createDataSet(DatasetName_event, mtype_event, space_event));
H5::DataSet *dataset_histories   = new H5::DataSet(file->createDataSet(DatasetName_histories, mtype_beam_data, space_histories));
this->NUMBER_OF_PARTICLES = myPhspData_Vector.size();
this->NUMBER_OF_ACTIVE_EVENTS=myEventData_Vector.size();
dataset_histories->write(myBeamData, mtype_beam_data);
dataset_event ->write(myEventData_Vector.data(),  mtype_event);
dataset->write(myPhspData_Vector.data(), mtype);

GetStatistics();
delete   dataset_event;
delete   dataset_histories;
delete   dataset;
delete   file;
}
catch( FileIException error )
{
error.printError();
}
catch( DataSetIException error ){
error.printError();
}
catch( DataSpaceIException error )
{
error.printError();
}
catch( DataTypeIException error )
{
 error.printError();
}
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void RunAction::SUMMARY()
{
G4RunManager* runManager = G4RunManager::GetRunManager();
PhysicsList* pPhysicsList= (PhysicsList*)(runManager->GetUserPhysicsList()); 
DetectorConstruction * pDetectorConstruction= (DetectorConstruction*)(runManager->GetUserDetectorConstruction()); 
int nthread=pDetectorConstruction->NUMBER_OF_THREADS;
this->elapsed_time= double(diffclock(end,begin)/1000)/((double) nthread);
G4cout<< " G4LINAC_HEAD-> ELAPSED TIME IS [ " << this->elapsed_time<< " seconds <=> "<< this->elapsed_time/60<< " minutes ]"<<G4endl;     
time_t theTime= time(NULL);
struct std::tm* aTime = localtime(&theTime);
std::ofstream Summary_file;
this->TOTAL_NUMBER_OF_HISTORIES=myTotalBeamData->NUMBER_OF_HISTORIES;

bool bremspe_flag=pPhysicsList-> fSplittingActive;
std::string fileName = pDetectorConstruction->H5_PHASE_SPACE_NAME_WITHOUT_EXTENSION+".summary";

Summary_file.open(fileName, std::ios::out);
/*-------------SUMMARY HEADER-------------------*/
Summary_file<<TERMINAL_HEADER<<G4endl;
/*-------------SUMMARY HEADER-------------------*/
Summary_file <<"    @DATE_OF_FILE_CREATION: "<<asctime(aTime);   
Summary_file <<"    @ELAPSED_TIME: "<<this->elapsed_time<<   " seconds."<<G4endl;   

Summary_file <<"    @PHASE_SPACE_NAME: "<<pDetectorConstruction->H5_PHASE_SPACE_NAME_WITHOUT_EXTENSION+".h5"<<G4endl;
Summary_file <<"    @Z_STOP: " <<this->Z_STOP<<" mm." <<G4endl;
if (bremspe_flag==true) {
Summary_file <<"    @REDUCTION VARIANCE TECHNIQUE: BREMSPE"<<G4endl;          
Summary_file <<"    @SPLIT NUMBER: "<< pPhysicsList->fNSplit<< G4endl;          
}
Summary_file <<"    @TOTAL_NUMBER_OF_SIMULATED_HISTORIES: " <<this->TOTAL_NUMBER_OF_HISTORIES<<G4endl;
Summary_file <<"    @TOTAL_NUMBER_OF_ACTIVE_EVENTS: " <<this->NUMBER_OF_ACTIVE_EVENTS <<G4endl;
Summary_file <<"    @ACTIVE_EVENTS_PERCENT: " <<(this->NUMBER_OF_ACTIVE_EVENTS/(double)this->TOTAL_NUMBER_OF_HISTORIES)*100 <<" %"<<G4endl;
Summary_file <<"    @TOTAL_NUMBER_OF_PARTICLES : "   << this->NUMBER_OF_PARTICLES  << G4endl;
Summary_file <<"    @TOTAL_NUMBER_OF_PARTICLES_PER_SECONDE : "   << int (this->NUMBER_OF_PARTICLES/(double )this->elapsed_time) << G4endl;
if (NUMBER_OF_PHOTONS >   0) Summary_file<<"    @TOTAL_NUMBER_OF_PHOTONS: "   << NUMBER_OF_PHOTONS  << G4endl;
if (NUMBER_OF_ELECTRONS > 0) Summary_file<<"    @TOTAL_NUMBER_OF_ELECTRONS: " << NUMBER_OF_ELECTRONS << G4endl;
if (NUMBER_OF_POSITRONS > 0) Summary_file<<"    @TOTAL_NUMBER_OF_POSITRONS: " << NUMBER_OF_POSITRONS << G4endl;
if (NUMBER_OF_NEUTRONS >  0) Summary_file<<"    @TOTAL_NUMBER_OF_NEUTRONS: "  <<NUMBER_OF_NEUTRONS <<G4endl;
if (NUMBER_OF_PROTONS >   0) Summary_file<<"    @TOTAL_NUMBER_OF_PROTONS: " << NUMBER_OF_PROTONS <<G4endl;
if (NUMBER_OF_PHOTONS >   0) Summary_file<<"    @PHOTONS_PERCENT: "<<100*(NUMBER_OF_PHOTONS/ (double)NUMBER_OF_PARTICLES)<<" %"<<G4endl;
if (NUMBER_OF_ELECTRONS > 0) Summary_file<<"    @ELECTRONS_PERCENT: " <<100*(NUMBER_OF_ELECTRONS/(double)NUMBER_OF_PARTICLES) <<" %" <<G4endl;
if (NUMBER_OF_POSITRONS > 0) Summary_file<<"    @POSITRONS_PERCENT: " <<100*(NUMBER_OF_POSITRONS/(double)NUMBER_OF_PARTICLES) <<" %" <<G4endl;
if (NUMBER_OF_PROTONS >   0) Summary_file<<"    @PROTONS_PERCENT: "  << 100*(NUMBER_OF_PROTONS/(double)NUMBER_OF_PARTICLES)   <<" %"<<G4endl;
if (NUMBER_OF_NEUTRONS >  0) Summary_file<<"    @NEUTRONS_PERCENT: " << 100*(NUMBER_OF_NEUTRONS/(double)NUMBER_OF_PARTICLES)  <<" %"<<G4endl;
Summary_file<<" ______________________________________________________________________________________________________" <<G4endl;
if (NUMBER_OF_PHOTONS >   0)
{
if (NUMBER_OF_PHOTONS >   1) Summary_file<<"    @PHOTONS_MAX_ENERGY: "  << PHOTON_ENERGY_MAX <<" MeV" <<G4endl;
if (NUMBER_OF_PHOTONS >   1) Summary_file<<"    @PHOTONS_MIN_ENERGY: "  << PHOTON_ENERGY_MIN <<" MeV" <<G4endl;
Summary_file<<"    @PHOTONS_MEAN_ENERGY: " << PHOTON_ENERGY_MEAN/NUMBER_OF_PHOTONS<<" MeV"<<G4endl;
Summary_file<<" ______________________________________________________________________________________________________" <<G4endl;
}
if (NUMBER_OF_ELECTRONS > 0) 
{
if (NUMBER_OF_ELECTRONS > 1) Summary_file<<"    @ELECTRONS_MAX_ENERGY: "<< ELECTRON_ENERGY_MAX <<" MeV" <<G4endl;
if (NUMBER_OF_ELECTRONS> 1)  Summary_file<<"    @ELECTRONS_MIN_ENERGY: " << ELECTRON_ENERGY_MIN <<" MeV" <<G4endl;
Summary_file<<"    @ELECTRONS_MEAN_ENERGY: " << ELECTRON_ENERGY_MEAN/NUMBER_OF_ELECTRONS<<" MeV"<<G4endl;
Summary_file<<" ______________________________________________________________________________________________________" <<G4endl;
}
if (NUMBER_OF_POSITRONS > 0) 
{
if (NUMBER_OF_POSITRONS > 1) Summary_file<<"    @POSITRONS_MAX_ENERGY: " << POSITRON_ENERGY_MAX<<" MeV"<<G4endl;
if (NUMBER_OF_POSITRONS > 1)  Summary_file<<"    @POSITRONS_MIN_ENERGY: " << POSITRON_ENERGY_MIN<<" MeV"<<G4endl;
Summary_file<<"    @POSITRONS_MEAN_ENERGY: " << POSITRON_ENERGY_MEAN /NUMBER_OF_POSITRONS <<" MeV"   <<G4endl;
Summary_file<<" ______________________________________________________________________________________________________" <<G4endl;
}
if (NUMBER_OF_PROTONS >   0)    
{      
if (NUMBER_OF_PROTONS >   1)  Summary_file<<"    @PROTONS_MAX_ENERGY: "<< PROTON_ENERGY_MAX<<" MeV"  <<G4endl;
if (NUMBER_OF_PROTONS >   1)  Summary_file<<"    @PROTONS_MIN_ENERGY: "<< PROTON_ENERGY_MIN<<" MeV"  <<G4endl;
Summary_file<<"    @PROTONS_MEAN_ENERGY: "<< PROTON_ENERGY_MEAN/NUMBER_OF_PROTONS <<" MeV"<<G4endl;
Summary_file<<" ______________________________________________________________________________________________________" <<G4endl;
}
if (NUMBER_OF_NEUTRONS > 0) 
{
if (NUMBER_OF_NEUTRONS > 1)  Summary_file<<"   @NEUTRONS_MAX_ENERGY: " << NEUTRON_ENERGY_MAX <<" MeV"<<G4endl;
if (NUMBER_OF_NEUTRONS > 1)  Summary_file<<"   @NEUTRONS_MIN_ENERGY: " << NEUTRON_ENERGY_MIN<<" MeV" <<G4endl;
Summary_file<<"   @NEUTRONS_MEAN_ENERGY: "  << NEUTRON_ENERGY_MEAN/NUMBER_OF_NEUTRONS<<" MeV" <<G4endl;
Summary_file<<" ______________________________________________________________________________________________________" <<G4endl;
}
if (NUMBER_OF_PHOTONS >   0)
{
Summary_file<<"    @PHOTONS_MAX_WEIGHT: "  << PHOTON_WEIGHT_MAX <<" " <<G4endl;
Summary_file<<"    @PHOTONS_MIN_WEIGHT: "  << PHOTON_WEIGHT_MIN <<"" <<G4endl;
Summary_file<<"    @PHOTONS_MEAN_WEIGHT: " << PHOTON_WEIGHT_MEAN/(double)NUMBER_OF_PHOTONS<<""<<G4endl;
Summary_file<<" ______________________________________________________________________________________________________" <<G4endl;
}
if (NUMBER_OF_ELECTRONS >   0)
{
Summary_file<<"    @ELECTRONS_MAX_WEIGHT: "  << ELECTRONS_WEIGHT_MAX <<" " <<G4endl;
Summary_file<<"    @ELECTRONS_MIN_WEIGHT: "  << ELECTRONS_WEIGHT_MIN <<"" <<G4endl;
Summary_file<<"    @ELECTRONS_MEAN_WEIGHT: " << ELECTRONS_WEIGHT_MEAN/(double)NUMBER_OF_ELECTRONS<<""<<G4endl;
Summary_file<<" ______________________________________________________________________________________________________" <<G4endl;
}
if (NUMBER_OF_POSITRONS >   0)
{
Summary_file<<"    @POSITRONS_MAX_WEIGHT: "  << POSITRONS_WEIGHT_MAX <<" " <<G4endl;
Summary_file<<"    @POSITRONS_MIN_WEIGHT: "  << POSITRONS_WEIGHT_MIN <<"" <<G4endl;
Summary_file<<"    @POSITRONS_MEAN_WEIGHT: " << POSITRONS_WEIGHT_MEAN/(double)NUMBER_OF_POSITRONS<<""<<G4endl;
Summary_file<<" ______________________________________________________________________________________________________" <<G4endl;
}
if (NUMBER_OF_PROTONS  >   0)
{
Summary_file<<"    @PROTONS_MAX_WEIGHT: "  << PROTON_WEIGHT_MAX <<" " <<G4endl;
Summary_file<<"    @PROTONS_MIN_WEIGHT: "  << PROTON_WEIGHT_MIN <<"" <<G4endl;
Summary_file<<"    @PROTONS_MEAN_WEIGHT: " << PROTON_WEIGHT_MEAN/(double)NUMBER_OF_PROTONS<<""<<G4endl;
Summary_file<<" ______________________________________________________________________________________________________" <<G4endl;
}
if (NUMBER_OF_NEUTRONS >   0)
{
Summary_file<<"    @NEUTRONS_MAX_WEIGHT: "  << NEUTRON_WEIGHT_MAX <<" " <<G4endl;
Summary_file<<"    @NEUTRONS_MIN_WEIGHT: "  << NEUTRON_WEIGHT_MIN <<"" <<G4endl;
Summary_file<<"    @NEUTRONS_MEAN_WEIGHT: " << NEUTRON_WEIGHT_MEAN/(double)NUMBER_OF_NEUTRONS<<""<<G4endl;
Summary_file<<" ______________________________________________________________________________________________________" <<G4endl;
}
Summary_file.close();
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void RunAction::PHOTONS_ENERGY(G4double Energy )
{
G4double TEMP = Energy;
if (PHOTON_ENERGY_MAX < TEMP ) PHOTON_ENERGY_MAX  = Energy;
if (PHOTON_ENERGY_MIN  > TEMP ) PHOTON_ENERGY_MIN  = Energy;
/*.........................*/  PHOTON_ENERGY_MEAN = PHOTON_ENERGY_MEAN+Energy;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void RunAction::ELECTRONS_ENERGY(G4double Energy )
{
G4double TEMP = Energy;
if (ELECTRON_ENERGY_MAX < TEMP ) ELECTRON_ENERGY_MAX  = Energy;
if (ELECTRON_ENERGY_MIN > TEMP ) ELECTRON_ENERGY_MIN  = Energy;
/*.........................*/    ELECTRON_ENERGY_MEAN = ELECTRON_ENERGY_MEAN+Energy;
auto idthread = std::to_string(G4Threading::G4GetThreadId()); 
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void RunAction::POSITRONS_ENERGY(G4double Energy )
{
G4double TEMP = Energy;
if (POSITRON_ENERGY_MAX < TEMP ) POSITRON_ENERGY_MAX  = Energy;
if (POSITRON_ENERGY_MIN > TEMP ) POSITRON_ENERGY_MIN  = Energy;
/*............................*/ POSITRON_ENERGY_MEAN = POSITRON_ENERGY_MEAN+Energy;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void RunAction::NEUTRONS_ENERGY(G4double Energy )
{
G4double TEMP = Energy;
if (NEUTRON_ENERGY_MAX < TEMP )  NEUTRON_ENERGY_MAX   = Energy;
if (NEUTRON_ENERGY_MIN > TEMP )  NEUTRON_ENERGY_MIN   = Energy;
/*............................*/ NEUTRON_ENERGY_MEAN  = NEUTRON_ENERGY_MEAN+Energy;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void RunAction::PROTONS_ENERGY(G4double Energy )
{
G4double TEMP = Energy;
if (PROTON_ENERGY_MAX < TEMP )   PROTON_ENERGY_MAX    = Energy;
if (PROTON_ENERGY_MIN > TEMP )   PROTON_ENERGY_MIN    = Energy;
/*............................*/ PROTON_ENERGY_MEAN   = PROTON_ENERGY_MEAN+Energy;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void RunAction::PHOTON_WEIGHT(G4double Weight )
{
G4double TEMP = Weight;
{
if (PHOTON_WEIGHT_MAX < TEMP )  PHOTON_WEIGHT_MAX  = Weight;
if (PHOTON_WEIGHT_MIN > TEMP )   PHOTON_WEIGHT_MIN  = Weight;
/*............................*/ PHOTON_WEIGHT_MEAN = PHOTON_WEIGHT_MEAN+Weight;
}
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void RunAction::ELECTRONS_WEIGHT(G4double Weight )
{
G4double TEMP = Weight;
if (ELECTRONS_WEIGHT_MAX < TEMP ) ELECTRONS_WEIGHT_MAX  = Weight;
if (ELECTRONS_WEIGHT_MIN > TEMP )  ELECTRONS_WEIGHT_MIN  = Weight;
/*............................*/   ELECTRONS_WEIGHT_MEAN = ELECTRONS_WEIGHT_MEAN+Weight;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void RunAction::POSITRONS_WEIGHT(G4double Weight )
{
G4double TEMP = Weight;
if (POSITRONS_WEIGHT_MAX < TEMP ) POSITRONS_WEIGHT_MAX  = Weight;
if (POSITRONS_WEIGHT_MIN > TEMP )  POSITRONS_WEIGHT_MIN  = Weight;
/*............................*/   POSITRONS_WEIGHT_MEAN = POSITRONS_WEIGHT_MEAN+Weight;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void RunAction::PROTONS_WEIGHT(G4double Weight )
{
G4double TEMP = Weight;
if (PROTON_WEIGHT_MAX < TEMP )  PROTON_WEIGHT_MAX  = Weight;
if (PROTON_WEIGHT_MIN > TEMP )   PROTON_WEIGHT_MIN  = Weight;
/*............................*/ PROTON_WEIGHT_MEAN = PROTON_WEIGHT_MEAN+Weight;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void RunAction::NEUTRONS_WEIGHT(G4double Weight )
{
G4double TEMP = Weight;
if (NEUTRON_WEIGHT_MAX < TEMP ) NEUTRON_WEIGHT_MAX  = Weight;
if (NEUTRON_WEIGHT_MIN > TEMP )  NEUTRON_WEIGHT_MIN  = Weight;
/*............................*/ NEUTRON_WEIGHT_MEAN = NEUTRON_WEIGHT_MEAN+Weight;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void RunAction::GetStatistics()
{// void
try{ 
for (unsigned int i=0; i<NUMBER_OF_PARTICLES; i++){
tmp.PART_KINETIC  =     myPhspData_Vector[i]. PART_KINETIC;
tmp.PART_PDGE     =     myPhspData_Vector[i]. PART_PDGE;
tmp.PART_WEIGHT   =     myPhspData_Vector[i]. PART_WEIGHT;
switch(tmp.PART_PDGE)
{
case 22:
// GAMMA
NUMBER_OF_PHOTONS++;
PHOTONS_ENERGY(tmp.PART_KINETIC);
PHOTON_WEIGHT(tmp.PART_WEIGHT);
if (NUMBER_OF_PHOTONS==1) 
{PHOTON_WEIGHT_MIN=tmp.PART_WEIGHT;
PHOTON_ENERGY_MIN=tmp.PART_KINETIC;
}
break;
case 11:
// ELECTRON
NUMBER_OF_ELECTRONS++;
ELECTRONS_ENERGY(tmp.PART_KINETIC);
ELECTRONS_WEIGHT(tmp.PART_WEIGHT);
if (NUMBER_OF_ELECTRONS==1){ ELECTRONS_WEIGHT_MIN=tmp.PART_WEIGHT;
ELECTRON_ENERGY_MIN=tmp.PART_KINETIC;
}
break;
case -11:
// POSITRON
NUMBER_OF_POSITRONS++;
POSITRONS_ENERGY(tmp.PART_KINETIC);
POSITRONS_WEIGHT(tmp.PART_WEIGHT);
if (NUMBER_OF_POSITRONS==1) { POSITRONS_WEIGHT_MIN=tmp.PART_WEIGHT;
POSITRON_ENERGY_MIN=tmp.PART_KINETIC;
}
break;
case 2212:
// PROTON
NUMBER_OF_PROTONS++;
PROTONS_ENERGY(tmp.PART_KINETIC);
PROTONS_WEIGHT(tmp.PART_WEIGHT);
if (NUMBER_OF_PROTONS==1) {PROTON_WEIGHT_MIN=tmp.PART_WEIGHT;
PROTON_ENERGY_MIN=tmp.PART_KINETIC;
}
break;
case 2112:
// NEUTRON
NUMBER_OF_NEUTRONS++;
NEUTRONS_ENERGY(tmp.PART_KINETIC);
NEUTRONS_WEIGHT(tmp.PART_WEIGHT);
if (NUMBER_OF_NEUTRONS==1) {NEUTRON_WEIGHT_MIN=tmp.PART_WEIGHT;
NEUTRON_ENERGY_MIN=tmp.PART_KINETIC;}
break;
default:
G4cout <<tmp.PART_PDGE  <<G4endl;
}
}

}
 // catch failure caused by the H5File operations
   catch( FileIException error )
   {
      error.printError();
   }
   // catch failure caused by the DataSet operations
   catch( DataSetIException error )
   {
      error.printError();
   }
   // catch failure caused by the DataSpace operations
   catch( DataSpaceIException error )
   {
      error.printError();
   }
   // catch failure caused by the DataSpace operations
   catch( DataTypeIException error )
   {
      error.printError();
   }
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
