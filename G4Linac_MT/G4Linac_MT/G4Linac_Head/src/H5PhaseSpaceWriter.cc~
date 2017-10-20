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
#include <sstream>
#include "G4Run.hh"
#include "G4Event.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4VSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#ifdef G4MULTITHREADED
#include "G4MTRunManager.hh"
#else
#include "G4RunManager.hh"
#endif
#include "G4SDManager.hh"
#include "G4ParticleDefinition.hh"
#include "G4VVisManager.hh"
#include "G4Colour.hh"
#include "G4VisAttributes.hh"
#include "G4UnitsTable.hh"
#include "G4Circle.hh"
#include "G4ThreeVector.hh"
#include "G4ios.hh"
#include <stdio.h>
#include "H5PhaseSpaceWriter.hh"
#include "G4RunManager.hh"
#include <vector>
#include "G4SystemOfUnits.hh"
#include "H5Cpp.h"
#include "G4Run.hh"
#include "G4SliceTimer.hh"
#include "G4Threading.hh"
#include <time.h>
#include "DetectorConstruction.hh"
#include "G4AutoLock.hh"
#include "PhysicsList.hh"
#include "RunAction.hh"
 const std::string DatasetName("PhspData"),
 DatasetName_event("EventData");
 const std::string
 DatasetName_histories("BeamData"),
 MEMBER_EVENTID("_EVENTID"),
 MEMBER_ENTERIES("_ENTERIES"),
 MEMBER_PART_PDGE("_PART_PDGE"),
 MEMBER_PART_WEIGHT("_PART_WEIGHT"),
 MEMBER_VOXEL_XID("_VOXEL_XID"),
 MEMBER_VOXEL_YID("_VOXEL_YID"),
 MEMBER_VOXEL_ZID("_VOXEL_ZID"),
 MEMBER_PART_DIR_X("_PART_DIR_X"),
 MEMBER_PART_DIR_Y("_PART_DIR_Y"),
 MEMBER_PART_DIR_Z("_PART_DIR_Z"),
 MEMBER_PART_KINETIC("_PART_KINETIC"),
 MEMBER_NUMBER_OF_ACTIVE_EVENTS("_NUMBER_OF_ACTIVE_EVENTS"),
 MEMBER_HISTORIES("_NUMBER_OF_HISTORIES"),
 MEMBER_PART_POS_X("_PART_POS_X"),
 MEMBER_PART_POS_Y("_PART_POS_Y"),
 MEMBER_PART_POS_Z("_PART_POS_Z"),
 MEMBER_Z_STOP("_Z_STOP"),
 MEMBER_DATA_ID("_DATA_ID");
 G4ThreadLocal bool H5PhaseSpaceWriter::used;

 using    namespace std;

G4ThreadLocal   unsigned int 
NUMBER_OF_PHOTONS                        =  0,
NUMBER_OF_ELECTRON                       =  0,
NUMBER_OF_POSITRON                       =  0,
NUMBER_OF_PROTON                         =  0,
NUMBER_OF_NEUTRON                        =  0,
NUMBER_OF_PARTICLES                      =  0,
NUMBER_OF_ENTRIES                        =  0,
NUMBER_OF_ACTIVE_EVENTS                  =  0,
NUMBER_OF_SIMULATED_HISTORIES            =  0,
EVENT_ID                                 =  0,
local_incremetor                         =  0,
TRACK_ID                                 =  0;
G4ThreadLocal    G4float
ELECTRON_ENERGY_MAX                      =  0,
ELECTRON_ENERGY_MIN                      =  0,
ELECTRON_ENERGY_MEAN                     =  0,
PHOTON_ENERGY_MAX                        =  0,
PHOTON_ENERGY_MIN                        =  0,
PHOTON_ENERGY_MEAN                       =  0,
POSITRON_ENERGY_MAX                      =  0,
POSITRON_ENERGY_MIN                      =  0,
POSITRON_ENERGY_MEAN                     =  0,
PROTON_ENERGY_MAX                        =  0,
PROTON_ENERGY_MIN                        =  0,
PROTON_ENERGY_MEAN                       =  0,
NEUTRON_ENERGY_MAX                       =  0,
NEUTRON_ENERGY_MIN                       =  0,
NEUTRON_ENERGY_MEAN                      =  0,
POST_POSITION_Z                          =  0,
PRE_POSITION_Z                           =  0,
POST_ENERGY                              =  0,
PRE_ENERGY                               =  0;


namespace {
 G4Mutex _Initialize_Mutex = G4MUTEX_INITIALIZER;
          }  
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#= */
H5PhaseSpaceWriter::H5PhaseSpaceWriter(G4String name)
    : G4VSensitiveDetector(name),timer(0)

{    
this->NumberOfThreads                      =  1;
used                                       =  false;
NUMBER_OF_PHOTONS                        =  0;
NUMBER_OF_ELECTRON                       =  0;
NUMBER_OF_POSITRON                       =  0;
NUMBER_OF_PROTON                         =  0;
NUMBER_OF_NEUTRON                        =  0;
NUMBER_OF_PARTICLES                      =  0;
NUMBER_OF_ENTRIES                        =  0;
NUMBER_OF_ACTIVE_EVENTS                  =  0;
NUMBER_OF_SIMULATED_HISTORIES            =  0;
EVENT_ID                                 =  0;
local_incremetor                         =  0;
TRACK_ID                                 =  0;
ELECTRON_ENERGY_MAX                      =  0;
ELECTRON_ENERGY_MIN                      =  0;
ELECTRON_ENERGY_MEAN                     =  0;
PHOTON_ENERGY_MAX                        =  0;
PHOTON_ENERGY_MIN                        =  0;
PHOTON_ENERGY_MEAN                       =  0;
POSITRON_ENERGY_MAX                      =  0;
POSITRON_ENERGY_MIN                      =  0;
POSITRON_ENERGY_MEAN                     =  0;
PROTON_ENERGY_MAX                        =  0;
PROTON_ENERGY_MIN                        =  0;
PROTON_ENERGY_MEAN                       =  0;
NEUTRON_ENERGY_MAX                       =  0;
NEUTRON_ENERGY_MIN                       =  0;
NEUTRON_ENERGY_MEAN                      =  0;
POST_POSITION_Z                          =  0;
PRE_POSITION_Z                           =  0;
POST_ENERGY                              =  0;
PRE_ENERGY                               =  0;
PHOTON_WEIGHT_MAX                        =  0;
PHOTON_WEIGHT_MIN                        =  0;
PHOTON_WEIGHT_MEAN                       =  0;
POSITRON_WEIGHT_MAX                      =  0;
POSITRON_WEIGHT_MIN                      =  0;
POSITRON_WEIGHT_MEAN                     =  0;
ELECTRON_WEIGHT_MAX                      =  0;
ELECTRON_WEIGHT_MIN                      =  0;
ELECTRON_WEIGHT_MEAN                     =  0;
PROTON_WEIGHT_MAX             =  0;
PROTON_WEIGHT_MIN             =  0;
PROTON_WEIGHT_MEAN           =  0;
NEUTRON_ENERGY_MAX            =  0;
NEUTRON_ENERGY_MIN            =  0;
NEUTRON_ENERGY_MEAN           =  0;  
NEUTRON_WEIGHT_MAX            =  0;
NEUTRON_WEIGHT_MIN            =  0;
NEUTRON_WEIGHT_MEAN           =  0; 
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#= */
H5PhaseSpaceWriter::~H5PhaseSpaceWriter(){}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#= */
void H5PhaseSpaceWriter::Initialize(G4HCofThisEvent*)
{
if (used==false)
{
//

auto idthread                               =   std::to_string(G4Threading::G4GetThreadId()); 
G4RunManager* runManager                    =   G4RunManager::GetRunManager();
DetectorConstruction* pDetectorConstruction =   (DetectorConstruction*)(runManager->GetUserDetectorConstruction()); 
this->Z_STOP                                =   pDetectorConstruction-> zstop/mm;
this->NumberOfThreads                       =   pDetectorConstruction->NUMBER_OF_THREADS;
this->FILE_NAME                             =   pDetectorConstruction->H5_PHASE_SPACE_NAME_WITHOUT_EXTENSION;
NUMBER_OF_SIMULATED_HISTORIES               =   runManager->GetCurrentRun()->GetNumberOfEventToBeProcessed();
myBeamData[0].NUMBER_OF_HISTORIES           =   NUMBER_OF_SIMULATED_HISTORIES;
myBeamData[0].Z_STOP                        =   this->Z_STOP;
this-> Total_Events_To_Be_Processed         =   runManager->GetNumberOfEventsToBeProcessed();
this->NumberOfEventsPerThread               =   Total_Events_To_Be_Processed/this-> NumberOfThreads;
used                                        =   true;                          
//

}
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#= */
G4bool H5PhaseSpaceWriter::ProcessHits(G4Step* aStep , G4TouchableHistory*)
{
FILL_DATA (aStep );
NUMBER_OF_ENTRIES++;
aStep ->GetTrack()->SetTrackStatus(fStopAndKill);
return true;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#= */
void H5PhaseSpaceWriter::EndOfEvent(G4HCofThisEvent* )
{

G4RunManager* runManager                       = G4RunManager::GetRunManager();
const G4Event * event                          = runManager->GetCurrentEvent();
EVENT_ID                                       = event->GetEventID();
if (NUMBER_OF_ENTRIES>0){
tmp_event.EVENT_ID                             =  EVENT_ID;
tmp_event.NUMBER_OF_ENTRIES                    =  NUMBER_OF_ENTRIES;
myEventData_vector.push_back(tmp_event);
NUMBER_OF_ACTIVE_EVENTS++;
}
G4AutoLock _m(&_Initialize_Mutex);
GET_DATA_FROM_THREAD();
_m.unlock();
NUMBER_OF_ENTRIES                              = 0;
}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#= */
void H5PhaseSpaceWriter::GET_DATA_FROM_THREAD()
{
G4RunManager* runManager                    = G4RunManager::GetRunManager();
DetectorConstruction* pDetectorConstruction = (DetectorConstruction*)(runManager->GetUserDetectorConstruction()); 
this->FILE_NAME                             = pDetectorConstruction-> H5_PHASE_SPACE_NAME_WITHOUT_EXTENSION;
this-> NumberOfThreads                      = pDetectorConstruction->NUMBER_OF_THREADS;
const G4Event * event                       =  runManager->GetCurrentEvent();
unsigned int event_id                       =  event->GetEventID();
for (unsigned short int i                   =  this-> NumberOfThreads; i>= 1; i--){

if( event_id                                == (i*(this-> Total_Events_To_Be_Processed/this-> NumberOfThreads)-1) ) {
this->NUMBER_OF_HISTORIES                   = myBeamData[0].NUMBER_OF_HISTORIES ;
this->H5PHASE_SPACE_NAME_WITHOUT_EXTENSION  =pDetectorConstruction->H5_PHASE_SPACE_NAME_WITHOUT_EXTENSION;
this->H5PHASE_SPACE_FILE_EXTENSION          =".h5";
auto idthread                               =   std::to_string(G4Threading::G4GetThreadId()); 
WRITE_PHASE_SPACE_FILE(this->H5PHASE_SPACE_NAME_WITHOUT_EXTENSION+"_"+idthread +this->H5PHASE_SPACE_FILE_EXTENSION);
//SUMMARY();
}}}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void H5PhaseSpaceWriter::WRITE_PHASE_SPACE_FILE(std::string H5_PHASE_SPACE_FILE_NAME)
{
hsize_t dim[1], dim_event[1], dim_histories[1];
dim_histories[0] = 1;
dim[0]=myPhspData_vector.size();
NUMBER_OF_PARTICLES=myPhspData_vector.size();
dim_event[0]  =   myEventData_vector.size();
int rank                = sizeof(dim) / sizeof(hsize_t);
int rank_event          = sizeof(dim_event) / sizeof(hsize_t);
int rank_histories      = sizeof(dim_histories) / sizeof(hsize_t);
myBeamData->NUMBER_OF_ACTIVE_EVENTS=NUMBER_OF_ACTIVE_EVENTS ;
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
H5::CompType mtype_histories(sizeof(BeamData));
mtype_histories.insertMember(MEMBER_HISTORIES,  HOFFSET(BeamData, NUMBER_OF_HISTORIES),   H5::PredType::NATIVE_INT);
mtype_histories.insertMember(MEMBER_NUMBER_OF_ACTIVE_EVENTS,  HOFFSET(BeamData, NUMBER_OF_ACTIVE_EVENTS),   H5::PredType::NATIVE_INT);
mtype_histories.insertMember(MEMBER_Z_STOP,     HOFFSET(BeamData, Z_STOP),               H5::PredType::NATIVE_DOUBLE);
H5::DataSpace space(rank, dim);
H5::DataSpace space_event(rank_event, dim_event);
H5::DataSpace space_histories(rank_histories, dim_histories);
H5::H5File *file                 = new H5::H5File(H5_PHASE_SPACE_FILE_NAME, H5F_ACC_TRUNC	);
H5::DataSet *dataset             = new H5::DataSet(file->createDataSet(DatasetName, mtype, space));
H5::DataSet *dataset_event       = new H5::DataSet(file->createDataSet(DatasetName_event, mtype_event, space_event));
H5::DataSet *dataset_histories   = new H5::DataSet(file->createDataSet(DatasetName_histories, mtype_histories, space_histories));

dataset_histories->write(myBeamData, mtype_histories);

dataset_event ->write(myEventData_vector.data(),  mtype_event);
dataset->write(myPhspData_vector.data(), mtype);
delete   dataset_event;
delete   dataset_histories;
delete   dataset;
delete   file;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#= */
void H5PhaseSpaceWriter::FILL_DATA ( G4Step*& aStep)
{
tmp.PART_PDGE              =  aStep->GetTrack()->GetDefinition()->GetPDGEncoding();
tmp.PART_WEIGHT            =  aStep->GetTrack()->GetWeight();
tmp.PART_POS_X             =  aStep->GetPreStepPoint()->GetPosition().x()/mm;
tmp.PART_POS_Y             =  aStep->GetPreStepPoint()->GetPosition().y()/mm;
tmp.PART_POS_Z             =  aStep->GetPreStepPoint()->GetPosition().z()/mm;
tmp.PART_DIR_X             =  aStep->GetPreStepPoint()->GetMomentumDirection().x()/mm;
tmp.PART_DIR_Y             =  aStep->GetPreStepPoint()->GetMomentumDirection().y()/mm;
tmp.PART_DIR_Z             =  aStep->GetPreStepPoint()->GetMomentumDirection().z()/mm;
tmp.PART_KINETIC           =  (aStep->GetTrack()->GetKineticEnergy()/MeV);
switch(tmp.PART_PDGE)
{
case 22:
// GAMMA
NUMBER_OF_PHOTONS++;
PHOTONS_ENERGY(tmp.PART_KINETIC);
PHOTON_WEIGHT(tmp.PART_WEIGHT);
break;
case 11:
// ELECTRON
NUMBER_OF_ELECTRON++;
ELECTRON_ENERGY(tmp.PART_KINETIC);
ELECTRON_WEIGHT(tmp.PART_WEIGHT);
break;
case -11:
// POSITRON
NUMBER_OF_POSITRON++;
POSITRON_ENERGY(tmp.PART_KINETIC);
POSITRON_WEIGHT(tmp.PART_WEIGHT);
break;
case 2212:
//PROTON
NUMBER_OF_PROTON++;
PROTON_ENERGY(tmp.PART_KINETIC);
PROTON_WEIGHT(tmp.PART_WEIGHT);
break;
case 2112:
// NEUTRON
NUMBER_OF_NEUTRON++;
NEUTRON_ENERGY(tmp.PART_KINETIC);
NEUTRON_WEIGHT(tmp.PART_WEIGHT);
break;
default:
G4cout << "ERROR:  PARTICLE CODE NOT SUPPORTED  AT EVENT ID: "<< G4MTRunManager::GetRunManager()->GetCurrentEvent()->GetEventID()<< ". code:" << tmp.PART_PDGE<< G4endl;
}
myPhspData_vector.push_back(tmp);
NUMBER_OF_PARTICLES++; 
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#= */
void H5PhaseSpaceWriter::PHOTONS_ENERGY(G4double Energy )
{
G4double TEMP = Energy;
if (PHOTON_ENERGY_MAX <= TEMP ) PHOTON_ENERGY_MAX  = Energy;
if (PHOTON_ENERGY_MAX > TEMP ) PHOTON_ENERGY_MIN  = Energy;
/*.........................*/  PHOTON_ENERGY_MEAN = PHOTON_ENERGY_MEAN+Energy;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#= */
void H5PhaseSpaceWriter::ELECTRON_ENERGY(G4double Energy )
{
G4double TEMP = Energy;
if (ELECTRON_ENERGY_MAX <= TEMP ) ELECTRON_ENERGY_MAX  = Energy;
if (ELECTRON_ENERGY_MAX > TEMP ) ELECTRON_ENERGY_MIN  = Energy;
/*.........................*/    ELECTRON_ENERGY_MEAN = ELECTRON_ENERGY_MEAN+Energy;

}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#= */
void H5PhaseSpaceWriter::POSITRON_ENERGY(G4double Energy )
{
G4double TEMP = Energy;
if (POSITRON_ENERGY_MAX <= TEMP ) POSITRON_ENERGY_MAX  = Energy;
if (POSITRON_ENERGY_MAX > TEMP ) POSITRON_ENERGY_MIN  = Energy;
/*............................*/ POSITRON_ENERGY_MEAN = POSITRON_ENERGY_MEAN+Energy;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#= */
void H5PhaseSpaceWriter::NEUTRON_ENERGY(G4double Energy )
{
G4double TEMP = Energy;
if (NEUTRON_ENERGY_MAX <= TEMP )  NEUTRON_ENERGY_MAX   = Energy;
if (NEUTRON_ENERGY_MAX > TEMP )  NEUTRON_ENERGY_MIN   = Energy;
/*............................*/ NEUTRON_ENERGY_MEAN  = NEUTRON_ENERGY_MEAN+Energy;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#= */
void H5PhaseSpaceWriter::PROTON_ENERGY(G4double Energy )
{
G4double TEMP = Energy;
if (PROTON_ENERGY_MAX <= TEMP )   PROTON_ENERGY_MAX    = Energy;
if (PROTON_ENERGY_MAX > TEMP )   PROTON_ENERGY_MIN    = Energy;
/*............................*/ PROTON_ENERGY_MEAN   = PROTON_ENERGY_MEAN+Energy;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#= */
void H5PhaseSpaceWriter::SUMMARY()
{
G4RunManager* runManager = G4RunManager::GetRunManager();
DetectorConstruction* pDetectorConstruction = (DetectorConstruction*)(runManager->GetUserDetectorConstruction()); 
auto idthread                               =   std::to_string(G4Threading::G4GetThreadId()); 
this->H5PHASE_SPACE_NAME_WITHOUT_EXTENSION=pDetectorConstruction->H5_PHASE_SPACE_NAME_WITHOUT_EXTENSION;
this->H5PHASE_SPACE_FILE_EXTENSION=".h5";
this->H5PHASE_SPACE_SUMMARY_EXTENSION="_"+idthread+".summary";
time_t theTime= time(NULL);
struct std::tm* aTime = localtime(&theTime);
ofstream Summary_file;
PhysicsList* pPhysicsList= (PhysicsList*)(runManager->GetUserPhysicsList()); 
bool bremspe_flag=pPhysicsList-> fSplittingActive;
G4String fileName=this->H5PHASE_SPACE_NAME_WITHOUT_EXTENSION+this->H5PHASE_SPACE_SUMMARY_EXTENSION;
Summary_file.open(fileName, std::ios::out);
Summary_file<<"#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#"<< G4endl;
Summary_file<<"G4LINAC_MT version 1.O: a Geant4-based application for Medical Linear Accelerator"<< G4endl;
Summary_file<< "Developed by Dr.Jaafar EL Bakkali, Assistant Prof. of Nuclear Physics, Tetouan City,Morocco,  30/08/ 2017 "<< G4endl;
Summary_file<<"WebSite: www.g4linac_mt.github.com "<< G4endl;
Summary_file <<"#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#"<< G4endl;
Summary_file <<"\u21B3"<<"    @DATE_OF_CREATION: "<<asctime(aTime);   
Summary_file <<"\u21B3"<<"    @PHASE_SPACE_NAME: "<<H5PHASE_SPACE_NAME_WITHOUT_EXTENSION+"_"+idthread+H5PHASE_SPACE_FILE_EXTENSION<<G4endl;
Summary_file<<"\u21B3" <<"    @Z_STOP: " <<this->Z_STOP<<" mm." <<G4endl;
if (bremspe_flag==true) {
Summary_file <<"\u21B3"<<"    @REDUCTION VARIANCE TECHNIQUE: BREMSPE"<<G4endl;          
Summary_file <<"\u21B3"<<"    @SPLIT NUMBER: "<< pPhysicsList->fNSplit<< G4endl;          
}
Summary_file <<"\u21B3"<<"    @NUMBER_OF_SIMULATED_HISTORIES: " <<this->NumberOfEventsPerThread <<G4endl;
Summary_file <<"\u21B3"<<"    @NUMBER_OF_ACTIVE_EVENTS: " <<NUMBER_OF_ACTIVE_EVENTS<<G4endl;
Summary_file <<"\u21B3"<<"    @ACTIVE_EVENTS_PERCENT: " <<(NUMBER_OF_ACTIVE_EVENTS/(double)this->NumberOfEventsPerThread )*100 <<" %"<<G4endl;
Summary_file <<"\u21B3"<<"    @NUMBER_OF_PARTICLES : "   << NUMBER_OF_PARTICLES  << G4endl;
Summary_file <<"\u21B3"<<"    @NUMBER_OF_PARTICLES_PER_NUMBER_OF_SIMULATED_HISTORIES : "   << (NUMBER_OF_PARTICLES/(double)this->NumberOfEventsPerThread  ) << G4endl;
if (NUMBER_OF_PHOTONS >   0) Summary_file<<"\u21B3"<<"    @NUMBER_OF_PHOTON: "   << NUMBER_OF_PHOTONS  << G4endl;
if (NUMBER_OF_ELECTRON > 0) Summary_file<<"\u21B3"<<"    @NUMBER_OF_ELECTRON: " << NUMBER_OF_ELECTRON << G4endl;
if (NUMBER_OF_POSITRON > 0) Summary_file<<"\u21B3"<<"    @NUMBER_OF_POSITRON: " << NUMBER_OF_POSITRON << G4endl;
if (NUMBER_OF_NEUTRON >  0) Summary_file<<"\u21B3"<<"    @NUMBER_OF_NEUTRON: "  <<NUMBER_OF_NEUTRON <<G4endl;
if (NUMBER_OF_PROTON >   0) Summary_file<<"\u21B3"<<"    @NUMBER_OF_PROTON: " << NUMBER_OF_PROTON <<G4endl;
if (NUMBER_OF_PHOTONS >   0) Summary_file<<"\u21B3"<<"    @PHOTON_PERCENT: "<<100*(NUMBER_OF_PHOTONS/ (double)NUMBER_OF_PARTICLES)<<" %"<<G4endl;
if (NUMBER_OF_ELECTRON > 0) Summary_file<<"\u21B3"<<"    @ELECTRON_PERCENT: " <<100*(NUMBER_OF_ELECTRON/(double)NUMBER_OF_PARTICLES) <<" %" <<G4endl;
if (NUMBER_OF_POSITRON > 0) Summary_file<<"\u21B3"<<"    @POSITRON_PERCENT: " <<100*(NUMBER_OF_POSITRON/(double)NUMBER_OF_PARTICLES) <<" %" <<G4endl;
if (NUMBER_OF_PROTON >   0) Summary_file<<"\u21B3"<<"    @PROTON_PERCENT: "  << 100*(NUMBER_OF_PROTON/(double)NUMBER_OF_PARTICLES)   <<" %"<<G4endl;
if (NUMBER_OF_NEUTRON >  0) Summary_file<<"\u21B3"<<"    @NEUTRON_PERCENT: " << 100*(NUMBER_OF_NEUTRON/(double)NUMBER_OF_PARTICLES)  <<" %"<<G4endl;
Summary_file<<" ____________________________________________________________________________________________________________" <<G4endl;
if (NUMBER_OF_PHOTONS >   0)
{
Summary_file<<"\u21B3"<<"    @PHOTON_MAX_ENERGY: "  << PHOTON_ENERGY_MAX <<" MeV" <<G4endl;
if (PHOTON_ENERGY_MIN > 0) Summary_file<<"\u21B3"<<"    @PHOTON_MIN_ENERGY: "  << PHOTON_ENERGY_MIN <<" MeV" <<G4endl;
Summary_file<<"\u21B3"<<"    @PHOTON_MEAN_ENERGY: " << PHOTON_ENERGY_MEAN/NUMBER_OF_PHOTONS<<" MeV"<<G4endl;
Summary_file<<" ____________________________________________________________________________________________________________" <<G4endl;
}
if (NUMBER_OF_ELECTRON > 0) 
{
Summary_file<<"\u21B3"<<"    @ELECTRON_MAX_ENERGY: "<< ELECTRON_ENERGY_MAX <<" MeV" <<G4endl;
if (ELECTRON_ENERGY_MIN> 0)  Summary_file<<"\u21B3"<<"    @ELECTRON_MIN_ENERGY: " <<ELECTRON_ENERGY_MIN <<" MeV" <<G4endl;
Summary_file<<"\u21B3"<<"    @ELECTRON_MEAN_ENERGY: " << ELECTRON_ENERGY_MEAN/NUMBER_OF_ELECTRON<<" MeV"<<G4endl;
Summary_file<<" ____________________________________________________________________________________________________________" <<G4endl;
}
if (NUMBER_OF_POSITRON > 0) 
{
Summary_file<<"\u21B3"<<"    @POSITRON_MAX_ENERGY: " << POSITRON_ENERGY_MAX<<" MeV"<<G4endl;
if (POSITRON_ENERGY_MIN> 0) Summary_file<<"\u21B3"<<"    @POSITRON_MIN_ENERGY: " << POSITRON_ENERGY_MIN<<" MeV"<<G4endl;
Summary_file<<"\u21B3"<<"    @POSITRON_MEAN_ENERGY: " << POSITRON_ENERGY_MEAN /NUMBER_OF_POSITRON <<" MeV"   <<G4endl;
Summary_file<<" ____________________________________________________________________________________________________________" <<G4endl;
}
if (NUMBER_OF_PROTON >   0)    
{      
Summary_file<<"\u21B3"<<"    @PROTON_MAX_ENERGY: "<< PROTON_ENERGY_MAX<<" MeV"  <<G4endl;
Summary_file<<"\u21B3"<<"    @PROTON_MIN_ENERGY: "<< PROTON_ENERGY_MIN<<" MeV"  <<G4endl;
Summary_file<<"\u21B3"<<"    @PROTON_MEAN_ENERGY: "<< PROTON_ENERGY_MEAN/NUMBER_OF_PROTON <<" MeV"<<G4endl;
Summary_file<<" ____________________________________________________________________________________________________________" <<G4endl;
}
if (NUMBER_OF_NEUTRON > 0) 
{
Summary_file<<"\u21B3"<<"   @NEUTRON_MAX_ENERGY: " << NEUTRON_ENERGY_MAX <<" MeV"<<G4endl;
Summary_file<<"\u21B3"<<"   @NEUTRON_MIN_ENERGY: " << NEUTRON_ENERGY_MIN<<" MeV" <<G4endl;
Summary_file<<"\u21B3"<<"   @NEUTRON_MEAN_ENERGY: "  << NEUTRON_ENERGY_MEAN/NUMBER_OF_NEUTRON<<" MeV" <<G4endl;
Summary_file<<"\u21B3"<<" ____________________________________________________________________________________________________________" <<G4endl;
}
if (NUMBER_OF_PHOTONS >   0)
{
Summary_file<<"\u21B3"<<"    @PHOTONS_MAX_WEIGHT: "  <<PHOTON_WEIGHT_MAX <<" " <<G4endl;
 if (PHOTON_WEIGHT_MIN>0) Summary_file<<"\u21B3"<<"    @PHOTONS_MIN_WEIGHT: "  << PHOTON_WEIGHT_MIN <<"" <<G4endl;
Summary_file<<"\u21B3"<<"    @PHOTONS_MEAN_WEIGHT: " << PHOTON_WEIGHT_MEAN/NUMBER_OF_PHOTONS<<""<<G4endl;
Summary_file<<" ____________________________________________________________________________________________________________" <<G4endl;
}
if (NUMBER_OF_ELECTRON >   0)
{
Summary_file<<"\u21B3"<<"    @ELECTRON_MAX_WEIGHT: "  << ELECTRON_WEIGHT_MAX <<" " <<G4endl;
if (ELECTRON_WEIGHT_MIN>0) Summary_file<<"\u21B3"<<"    @ELECTRON_MIN_WEIGHT: "  << ELECTRON_WEIGHT_MIN <<"" <<G4endl;
Summary_file<<"\u21B3"<<"    @ELECTRON_MEAN_WEIGHT: " << ELECTRON_WEIGHT_MEAN/NUMBER_OF_ELECTRON<<""<<G4endl;
Summary_file<<" ____________________________________________________________________________________________________________" <<G4endl;
}
if (NUMBER_OF_POSITRON >   0)
{
Summary_file<<"\u21B3"<<"    @POSITRON_MAX_WEIGHT: "  << POSITRON_WEIGHT_MAX <<" " <<G4endl;
if (POSITRON_WEIGHT_MIN>0) Summary_file<<"\u21B3"<<"    @POSITRON_MIN_WEIGHT: "  << POSITRON_WEIGHT_MIN <<"" <<G4endl;
Summary_file<<"\u21B3"<<"    @POSITRON_MEAN_WEIGHT: " << POSITRON_WEIGHT_MEAN/NUMBER_OF_POSITRON<<""<<G4endl;
Summary_file<<" ____________________________________________________________________________________________________________" <<G4endl;
}

if (NUMBER_OF_PROTON  >   0)
{
Summary_file<<"\u21B3"<<"    @PROTON_MAX_WEIGHT: "  << PROTON_WEIGHT_MAX <<" " <<G4endl;
Summary_file<<"\u21B3"<<"    @PROTON_MIN_WEIGHT: "  << PROTON_WEIGHT_MIN <<"" <<G4endl;
Summary_file<<"\u21B3"<<"    @PROTON_MEAN_WEIGHT: " << PROTON_WEIGHT_MEAN/NUMBER_OF_PROTON<<""<<G4endl;
Summary_file<<" ____________________________________________________________________________________________________________" <<G4endl;
}
if (NUMBER_OF_NEUTRON >   0)
{
Summary_file<<"\u21B3"<<"    @NEUTRON_MAX_WEIGHT: "  << NEUTRON_WEIGHT_MAX <<" " <<G4endl;
Summary_file<<"\u21B3"<<"    @NEUTRON_MIN_WEIGHT: "  << NEUTRON_WEIGHT_MIN <<"" <<G4endl;
Summary_file<<"\u21B3"<<"    @NEUTRON_MEAN_WEIGHT: " << NEUTRON_WEIGHT_MEAN/NUMBER_OF_NEUTRON<<""<<G4endl;
Summary_file<<" ____________________________________________________________________________________________________________" <<G4endl;
}

Summary_file.close();
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void H5PhaseSpaceWriter::PHOTON_WEIGHT(G4double Weight )
{
G4double TEMP = Weight;

{
if (PHOTON_WEIGHT_MAX <= TEMP ) PHOTON_WEIGHT_MAX  = Weight;
if (PHOTON_WEIGHT_MAX > TEMP )PHOTON_WEIGHT_MIN  = Weight;
/*............................*/ PHOTON_WEIGHT_MEAN = PHOTON_WEIGHT_MEAN+Weight;
}

}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void H5PhaseSpaceWriter::ELECTRON_WEIGHT(G4double Weight )
{
G4double TEMP = Weight;

if (ELECTRON_WEIGHT_MAX <= TEMP ) ELECTRON_WEIGHT_MAX  = Weight;
if (ELECTRON_WEIGHT_MAX > TEMP ) ELECTRON_WEIGHT_MIN  = Weight;
/*............................*/ ELECTRON_WEIGHT_MEAN = ELECTRON_WEIGHT_MEAN+Weight;

}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void H5PhaseSpaceWriter::POSITRON_WEIGHT(G4double Weight )
{
G4double TEMP = Weight;

if (POSITRON_WEIGHT_MAX <= TEMP ) POSITRON_WEIGHT_MAX  = Weight;
if (POSITRON_WEIGHT_MAX > TEMP ) POSITRON_WEIGHT_MIN  = Weight;
/*............................*/ POSITRON_WEIGHT_MEAN = POSITRON_WEIGHT_MEAN+Weight;

}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void H5PhaseSpaceWriter::PROTON_WEIGHT(G4double Weight )
{
G4double TEMP = Weight;

if (PROTON_WEIGHT_MAX <= TEMP ) PROTON_WEIGHT_MAX  = Weight;
if (PROTON_WEIGHT_MAX > TEMP ) PROTON_WEIGHT_MIN  = Weight;
/*............................*/ PROTON_WEIGHT_MEAN = PROTON_WEIGHT_MEAN+Weight;

}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void H5PhaseSpaceWriter::NEUTRON_WEIGHT(G4double Weight )
{
G4double TEMP = Weight;
if (NEUTRON_WEIGHT_MAX <= TEMP ) NEUTRON_WEIGHT_MAX  = Weight;
if (NEUTRON_WEIGHT_MAX > TEMP ) NEUTRON_WEIGHT_MIN  = Weight;
/*............................*/ NEUTRON_WEIGHT_MEAN = NEUTRON_WEIGHT_MEAN+Weight;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/

