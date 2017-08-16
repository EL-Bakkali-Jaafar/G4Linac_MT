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

 /*
 *   AUTHOR:
 *
 *   Dr. Jaafar EL Bakkali, Assistant Professor of Nuclear Physics, Rabat, Morocco.
 *   e-mail: bahmedj@gmail.com

-------------------------------------------------------------------------------------------
 * For documentation
 * see http://G4Linac_MT.GitHub.com
 *
 * - 23/07/2017: public version 2.0
 *
--------------------------------------------------------------------------------------------
*/
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
#include "H5PhaseSpaceMerger.hh"
#include <time.h>
#include "DetectorConstruction.hh"
const std::string DatasetName("PhspData");
const std::string DatasetName_event("EventData");
const std::string DatasetName_histories("BeamData");
const std::string MEMBER_EVENTID("_EVENTID");
const std::string MEMBER_ENTERIES("_ENTERIES");
const std::string MEMBER_PART_PDGE("_PART_PDGE");
const std::string MEMBER_PART_WEIGHT("_PART_WEIGHT");
const std::string MEMBER_VOXEL_XID("_VOXEL_XID");
const std::string MEMBER_VOXEL_YID("_VOXEL_YID");
const std::string MEMBER_VOXEL_ZID("_VOXEL_ZID");
const std::string MEMBER_PART_DIR_X("_PART_DIR_X");
const std::string MEMBER_PART_DIR_Y("_PART_DIR_Y");
const std::string MEMBER_PART_DIR_Z("_PART_DIR_Z");
const std::string MEMBER_PART_KINETIC("_PART_KINETIC");
const std::string MEMBER_HISTORIES("_NUMBER_OF_HISTORIES");
const std::string MEMBER_PART_POS_X("_PART_POS_X");
const std::string MEMBER_PART_POS_Y("_PART_POS_Y");
const std::string MEMBER_PART_POS_Z("_PART_POS_Z");
const std::string MEMBER_Z_STOP("_Z_STOP");
const std::string MEMBER_DATA_ID("_DATA_ID");
G4ThreadLocal bool H5PhaseSpaceWriter::used;
G4SliceTimer *timer;
using    namespace std;
G4ThreadLocal  int 
NUMBER_OF_PHOTONS                  =  0,
NUMBER_OF_ELECTRONS                =  0,
NUMBER_OF_POSITRONS                =  0,
NUMBER_OF_PROTONS                  =  0,
NUMBER_OF_NEUTRONS                 =  0,
NUMBER_OF_PARTICLES                =  0,
NUMBER_OF_ENTRIES                  =  0,
NUMBER_OF_ACTIVE_EVENT             =  0,
NUMBER_OF_SIMULATED_HISTORIES      =  0,
EVENT_ID                           =  0,
TRACK_ID                           =  0;
G4ThreadLocal     G4float
ELECTRON_ENERGY_MAX  =  0,
ELECTRON_ENERGY_MIN  =  0,
ELECTRON_ENERGY_MEAN =  0,
PHOTON_ENERGY_MAX    =  0,
PHOTON_ENERGY_MIN    =  0,
PHOTON_ENERGY_MEAN   =  0,
POSITRON_ENERGY_MAX  =  0,
POSITRON_ENERGY_MIN  =  0,
POSITRON_ENERGY_MEAN =  0,
PROTON_ENERGY_MAX    =  0,
PROTON_ENERGY_MIN    =  0,
PROTON_ENERGY_MEAN   =  0,
NEUTRON_ENERGY_MAX   =  0,
NEUTRON_ENERGY_MIN   =  0,
NEUTRON_ENERGY_MEAN  =  0,
POST_POSITION_Z      =  0,
PRE_POSITION_Z       =  0,
POST_ENERGY          =  0,
PRE_ENERGY           =  0;
G4ThreadLocal int di=0;
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#= */
H5PhaseSpaceWriter::H5PhaseSpaceWriter(G4String name)
    : G4VSensitiveDetector(name)

{    
timer = new G4SliceTimer();
this->NumberOfThreads=1;
used=false;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#= */
H5PhaseSpaceWriter::~H5PhaseSpaceWriter()
{ 
 delete timer;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#= */
void H5PhaseSpaceWriter::Initialize(G4HCofThisEvent*)
{
if (used==false){
auto idthread = std::to_string(G4Threading::G4GetThreadId()); 
G4RunManager* runManager = G4RunManager::GetRunManager();
DetectorConstruction* pDetectorConstruction = (DetectorConstruction*)(runManager->GetUserDetectorConstruction()); 
this->Z_STOP=pDetectorConstruction-> zstop/mm;
this->NumberOfThreads=pDetectorConstruction->NUMBER_OF_THREADS;
this->FILE_NAME=pDetectorConstruction->H5_PHASE_SPACE_NAME_WITHOUT_EXTENSION;
NUMBER_OF_SIMULATED_HISTORIES             =  runManager->GetCurrentRun()->GetNumberOfEventToBeProcessed()/this->NumberOfThreads ;
myBeamData[0].NUMBER_OF_HISORIES          =  NUMBER_OF_SIMULATED_HISTORIES;
myBeamData[0].Z_STOP                      =   this->Z_STOP;
this-> Total_Events_To_Be_Processed= runManager->GetNumberOfEventsToBeProcessed();
this->NumberOfEventsPerThread=Total_Events_To_Be_Processed/this-> NumberOfThreads;
used=true;
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
G4MTRunManager* runManager_ = G4MTRunManager::GetMasterRunManager();
G4RunManager* runManager = G4RunManager::GetRunManager();
const G4Event * event = runManager->GetCurrentEvent();
di++;

if (di==1){
auto idthread = std::to_string(G4Threading::G4GetThreadId()); 
int first_event_id= event->GetEventID();


int event_modulo = runManager_->GetEventModulo();
this->DATA_ID= first_event_id/ event_modulo;

G4cout<<"Thread ID :" <<idthread << "; First event ID: " << first_event_id<<"; dataId: "<<this->DATA_ID<<G4endl;


myBeamData[0].DATA_ID = this->DATA_ID;
}

EVENT_ID=event->GetEventID();
if (NUMBER_OF_ENTRIES>0){
tmp_event.EVENT_ID                      =  EVENT_ID;
tmp_event.NUMBER_OF_ENTRIES             =  NUMBER_OF_ENTRIES;
myEventData.push_back(tmp_event);
NUMBER_OF_ACTIVE_EVENT++;
}
WRITE_PHSP_FILE ();
NUMBER_OF_ENTRIES=0;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#= */
void H5PhaseSpaceWriter::WRITE_PHSP_FILE ()
{
G4RunManager* runManager = G4RunManager::GetRunManager();
DetectorConstruction* pDetectorConstruction = (DetectorConstruction*)(runManager->GetUserDetectorConstruction()); 
this->FILE_NAME=pDetectorConstruction-> H5_PHASE_SPACE_NAME_WITHOUT_EXTENSION;
this-> NumberOfThreads= pDetectorConstruction->NUMBER_OF_THREADS;
const G4Event * event    =   runManager->GetCurrentEvent();
G4int event_id           =   event->GetEventID();
for (int i=this-> NumberOfThreads; i>= 1; i--){
if( event_id== (i*(this-> Total_Events_To_Be_Processed/this-> NumberOfThreads)-1) ) {
    // the array of each length of multidimentional data.
hsize_t dim[1],  dim_event[1], dim_histories[1];
dim_histories[0] = sizeof(myBeamData) / sizeof(BeamData);
dim[0]        =  myPhspData.size();
dim_event[0]  =  myEventData.size();
    // the length of dim
int rank                = sizeof(dim) / sizeof(hsize_t);
int rank_event          = sizeof(dim_event) / sizeof(hsize_t);
int rank_histories      = sizeof(dim_histories) / sizeof(hsize_t);
    // defining the datatype to pass HDF5
G4ThreadLocal H5::CompType mtype(sizeof(PhspData));
mtype.insertMember(MEMBER_PART_PDGE,    HOFFSET(PhspData, PART_PDGE),     H5::PredType::NATIVE_INT   );
mtype.insertMember(MEMBER_PART_WEIGHT,  HOFFSET(PhspData, PART_WEIGHT),   H5::PredType::NATIVE_FLOAT);
mtype.insertMember(MEMBER_PART_POS_X,   HOFFSET(PhspData, PART_POS_X),    H5::PredType::NATIVE_FLOAT );
mtype.insertMember(MEMBER_PART_POS_Y,   HOFFSET(PhspData, PART_POS_Y),    H5::PredType::NATIVE_FLOAT );
mtype.insertMember(MEMBER_PART_POS_Z,   HOFFSET(PhspData, PART_POS_Z),    H5::PredType::NATIVE_FLOAT );
mtype.insertMember(MEMBER_PART_DIR_X,   HOFFSET(PhspData, PART_DIR_X),    H5::PredType::NATIVE_FLOAT );
mtype.insertMember(MEMBER_PART_DIR_Y,   HOFFSET(PhspData, PART_DIR_Y),    H5::PredType::NATIVE_FLOAT );
mtype.insertMember(MEMBER_PART_DIR_Z,   HOFFSET(PhspData, PART_DIR_Z),    H5::PredType::NATIVE_FLOAT );
mtype.insertMember(MEMBER_PART_KINETIC, HOFFSET(PhspData, PART_KINETIC),  H5::PredType::NATIVE_FLOAT );
G4ThreadLocal  H5::CompType mtype_event(sizeof(EventData));
mtype_event.insertMember(MEMBER_EVENTID,  HOFFSET(EventData, EVENT_ID),                  H5::PredType::NATIVE_INT);
mtype_event.insertMember(MEMBER_ENTERIES, HOFFSET(EventData, NUMBER_OF_ENTRIES),         H5::PredType::NATIVE_INT);
G4ThreadLocal  H5::CompType mtype_histories(sizeof(BeamData));
mtype_histories.insertMember(MEMBER_HISTORIES,  HOFFSET(BeamData, NUMBER_OF_HISORIES),   H5::PredType::NATIVE_INT);
mtype_histories.insertMember(MEMBER_Z_STOP,     HOFFSET(BeamData, Z_STOP),               H5::PredType::NATIVE_FLOAT);
mtype_histories.insertMember(MEMBER_DATA_ID,     HOFFSET(BeamData, DATA_ID),               H5::PredType::NATIVE_INT);
auto id_thread = std::to_string(G4Threading::G4GetThreadId()); 
string _THREAD_FILE_NAME_WITH_EXTENSION = id_thread+this->FILE_NAME+".h5";
G4ThreadLocal  H5::DataSpace space(rank, dim);
G4ThreadLocal  H5::DataSpace space_event(rank_event, dim_event);
G4ThreadLocal  H5::DataSpace space_histories(rank_histories, dim_histories);
G4ThreadLocal H5::H5File *file                 = new H5::H5File(_THREAD_FILE_NAME_WITH_EXTENSION , H5F_ACC_TRUNC	);
G4ThreadLocal  H5::DataSet *dataset             = new H5::DataSet(file->createDataSet(DatasetName, mtype, space));
G4ThreadLocal H5::DataSet *dataset_event       = new H5::DataSet(file->createDataSet(DatasetName_event, mtype_event, space_event));
G4ThreadLocal  H5::DataSet *dataset_histories   = new H5::DataSet(file->createDataSet(DatasetName_histories, mtype_histories, space_histories));
dataset_histories->write(myBeamData, mtype_histories);
EventData *pEventData          =  new EventData[myEventData.size()];
PhspData *pPhspData             =  new PhspData[myPhspData.size()];
for (unsigned int l= 0; l < myPhspData.size(); l++){
pPhspData[l].PART_PDGE           =  myPhspData[l].PART_PDGE;
pPhspData[l].PART_WEIGHT         =  myPhspData[l].PART_WEIGHT;
pPhspData[l].PART_POS_X          =  myPhspData[l].PART_POS_X ;// mm
pPhspData[l].PART_POS_Y          =  myPhspData[l].PART_POS_Y;
pPhspData[l].PART_POS_Z          =  this->Z_STOP;
pPhspData[l].PART_DIR_X          =  myPhspData[l].PART_DIR_X;
pPhspData[l].PART_DIR_Y          =  myPhspData[l].PART_DIR_Y ;
pPhspData[l].PART_DIR_Z          =  myPhspData[l].PART_DIR_Z;
pPhspData[l].PART_KINETIC        =  myPhspData[l].PART_KINETIC ; //MeV
 };
myPhspData.clear();

for (unsigned int n = 0; n< myEventData.size(); n++){
pEventData[n].EVENT_ID           =  myEventData[n].EVENT_ID    ;
pEventData[n].NUMBER_OF_ENTRIES  =  myEventData[n].NUMBER_OF_ENTRIES;
}
myEventData.clear();
dataset_event ->write(pEventData,mtype_event);
//
dataset->write(pPhspData, mtype);
myPhspData.clear();
delete[] pPhspData;
delete[] pEventData;
delete   dataset_event;
delete   dataset_histories;
delete   dataset;
delete   file;
// WRITE SUMMARY OF SIMULATION
//SUMMARY();
}
}
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
auto ithread               = std::to_string(G4Threading::G4GetThreadId()); 
switch(tmp.PART_PDGE)
{
case 22:
// GAMMA
NUMBER_OF_PHOTONS++;
PHOTONS_ENERGY(tmp.PART_KINETIC);
break;
case 11:
// ELECTRON
NUMBER_OF_ELECTRONS++;
ELECTRONS_ENERGY(tmp.PART_KINETIC);
break;
case -11:
// POSITRON
NUMBER_OF_POSITRONS++;
POSITRONS_ENERGY(tmp.PART_KINETIC);
break;
case 2112:
// NEUTRON
NUMBER_OF_PROTONS++;
PROTONS_ENERGY(tmp.PART_KINETIC);
break;
case 2122:
// PROTON
NUMBER_OF_NEUTRONS++;
NEUTRONS_ENERGY(tmp.PART_KINETIC);
break;
default:
G4cout << "ERROR:  PARTICLE CODE NOT SUPPORTED  AT EVENT ID: "<< G4MTRunManager::GetRunManager()->GetCurrentEvent()->GetEventID()<< "." << G4endl;
}
myPhspData.push_back(tmp);
NUMBER_OF_PARTICLES++; 
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#= */
void H5PhaseSpaceWriter::PHOTONS_ENERGY(G4double Energy )
{
G4double TEMP = Energy;
if (PHOTON_ENERGY_MAX < TEMP ) PHOTON_ENERGY_MAX  = Energy;
if (PHOTON_ENERGY_MAX > TEMP ) PHOTON_ENERGY_MIN  = Energy;
/*.........................*/  PHOTON_ENERGY_MEAN = PHOTON_ENERGY_MEAN+Energy;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#= */
void H5PhaseSpaceWriter::ELECTRONS_ENERGY(G4double Energy )
{
G4double TEMP = Energy;
if (ELECTRON_ENERGY_MAX < TEMP ) ELECTRON_ENERGY_MAX  = Energy;
if (ELECTRON_ENERGY_MAX > TEMP ) ELECTRON_ENERGY_MIN  = Energy;
/*.........................*/    ELECTRON_ENERGY_MEAN = ELECTRON_ENERGY_MEAN+Energy;
auto idthread = std::to_string(G4Threading::G4GetThreadId()); 
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#= */
void H5PhaseSpaceWriter::POSITRONS_ENERGY(G4double Energy )
{
G4double TEMP = Energy;
if (POSITRON_ENERGY_MAX < TEMP ) POSITRON_ENERGY_MAX  = Energy;
if (POSITRON_ENERGY_MAX > TEMP ) POSITRON_ENERGY_MIN  = Energy;
/*............................*/ POSITRON_ENERGY_MEAN = POSITRON_ENERGY_MEAN+Energy;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#= */
void H5PhaseSpaceWriter::NEUTRONS_ENERGY(G4double Energy )
{
G4double TEMP = Energy;
if (NEUTRON_ENERGY_MAX < TEMP )  NEUTRON_ENERGY_MAX   = Energy;
if (NEUTRON_ENERGY_MAX > TEMP )  NEUTRON_ENERGY_MIN   = Energy;
/*............................*/ NEUTRON_ENERGY_MEAN  = NEUTRON_ENERGY_MEAN+Energy;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#= */
void H5PhaseSpaceWriter::PROTONS_ENERGY(G4double Energy )
{
G4double TEMP = Energy;
if (PROTON_ENERGY_MAX < TEMP )   PROTON_ENERGY_MAX    = Energy;
if (PROTON_ENERGY_MAX > TEMP )   PROTON_ENERGY_MIN    = Energy;
/*............................*/ PROTON_ENERGY_MEAN   = PROTON_ENERGY_MEAN+Energy;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#= */
void H5PhaseSpaceWriter::clear()
{} 
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#= */
void H5PhaseSpaceWriter::DrawAll()
{}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#= */
void H5PhaseSpaceWriter::PrintAll()
{}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#= */
void H5PhaseSpaceWriter::SUMMARY()
{
timer->Stop();
time_t theTime= time(NULL);
struct std::tm* aTime = localtime(&theTime);
ofstream Summary_file;
auto id_thread1 = std::to_string(G4Threading::G4GetThreadId()); 
G4String fileName=id_thread1+this->FILE_NAME +".summary";
Summary_file.open(fileName, std::ios::out);
Summary_file <<"#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#"<< G4endl;
Summary_file <<"G4LINAC VERSION 1.O: A GEANT4 BASED APPLICATION FOR MEDICAL LINEAR ACCELERATOR "<< G4endl;
Summary_file << "DEVELOPED BY DR. JAAFAR EL BAKKALI, BAHMEDJ@GMAIL.COM, TETOUAN-MOROCCO,  JULY 2017 "<< G4endl;
Summary_file <<"#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#"<< G4endl;
Summary_file <<"    @DATE_OF_CREATION: "<<asctime(aTime);          
Summary_file <<"    @THREAD_ID: "<< id_thread1 <<G4endl;          
Summary_file <<"    @PHASE_SPACE_NAME: "<<id_thread1+this->FILE_NAME <<G4endl;
Summary_file <<"    @Z_STOP: " <<this->Z_STOP<<" mm." <<G4endl;
Summary_file <<"    @ELAPSED_TIME: " << timer->GetUserElapsed() <<" s" <<G4endl;
Summary_file <<"    @NUMBER_OF_SIMULATED_HISTORIES_PER_THREAD: " <<NUMBER_OF_SIMULATED_HISTORIES <<G4endl;
Summary_file <<"    @NUMBER_OF_ACTIVE_EVENT: " << NUMBER_OF_ACTIVE_EVENT<<",("<<100*( NUMBER_OF_ACTIVE_EVENT/(double)NUMBER_OF_SIMULATED_HISTORIES)<<"%)" <<G4endl;
Summary_file <<"    @TOTAL_NUMBER_OF_PARTICLES	: "   << NUMBER_OF_PARTICLES  << G4endl;
if (NUMBER_OF_PHOTONS >   0) Summary_file<<"    @TOTAL_NUMBER_OF_PHOTONS: "   << NUMBER_OF_PHOTONS   << G4endl;
if (NUMBER_OF_ELECTRONS > 0) Summary_file<<"    @TOTAL_NUMBER_OF_ELECTRONS: " << NUMBER_OF_ELECTRONS << G4endl;
if (NUMBER_OF_POSITRONS > 0) Summary_file<<"    @TOTAL_NUMBER_OF_POSITRONS: " << NUMBER_OF_POSITRONS << G4endl;
if (NUMBER_OF_NEUTRONS >  0) Summary_file<<"    @TOTAL_NUMBER_OF_NEUTRONS: "  <<NUMBER_OF_NEUTRONS <<G4endl;
if (NUMBER_OF_PROTONS >   0) Summary_file<<"    @TOTAL_NUMBER_OF_PROTONS: " << NUMBER_OF_PROTONS <<G4endl;
if (NUMBER_OF_PHOTONS >   0) Summary_file<<"    @PHOTONS_PERCENT: "<<100*(NUMBER_OF_PHOTONS/ (double)NUMBER_OF_PARTICLES)<<" %"<<G4endl;
if (NUMBER_OF_ELECTRONS > 0) Summary_file<<"    @ELECTRONS_PERCENT: " <<100*(NUMBER_OF_ELECTRONS/(double)NUMBER_OF_PARTICLES) <<" %" <<G4endl;
if (NUMBER_OF_POSITRONS > 0) Summary_file<<"    @POSITRONS_PERCENT: " <<100*(NUMBER_OF_POSITRONS/(double)NUMBER_OF_PARTICLES) <<" %" <<G4endl;
if (NUMBER_OF_PROTONS >   0) Summary_file<<"    @PROTONS_PERCENT: "  << 100*(NUMBER_OF_PROTONS/(double)NUMBER_OF_PARTICLES)   <<" %"<<G4endl;
if (NUMBER_OF_NEUTRONS >  0) Summary_file<<"    @NEUTRONS_PERCENT: " << 100*(NUMBER_OF_NEUTRONS/(double)NUMBER_OF_PARTICLES)  <<" %"<<G4endl;
Summary_file<<" ____________________________________________________________________________________________________________" <<G4endl;
if (NUMBER_OF_PHOTONS >   0)
{
Summary_file<<"    @PHOTONS_MAX_ENERGY: "  << PHOTON_ENERGY_MAX <<" MeV" <<G4endl;
Summary_file<<"    @PHOTONS_MIN_ENERGY: "  << PHOTON_ENERGY_MIN <<" MeV" <<G4endl;
Summary_file<<"    @PHOTONS_MEAN_ENERGY: " << PHOTON_ENERGY_MEAN/NUMBER_OF_PHOTONS<<" MeV"<<G4endl;
Summary_file<<" ____________________________________________________________________________________________________________" <<G4endl;
}
if (NUMBER_OF_ELECTRONS > 0) 
{
Summary_file<<"    @ELECTRONS_MAX_ENERGY: "<< ELECTRON_ENERGY_MAX <<" MeV" <<G4endl;
Summary_file<<"    @ELECTRONS_MIN_ENERGY: " << ELECTRON_ENERGY_MIN <<" MeV" <<G4endl;
Summary_file<<"    @ELECTRONS_MEAN_ENERGY: " << ELECTRON_ENERGY_MEAN/NUMBER_OF_ELECTRONS<<" MeV"<<G4endl;
Summary_file<<" ____________________________________________________________________________________________________________" <<G4endl;
}
if (NUMBER_OF_POSITRONS > 0) 
{
Summary_file<<"    @POSITRONS_MAX_ENERGY: " << POSITRON_ENERGY_MAX<<" MeV"<<G4endl;
Summary_file<<"    @POSITRONS_MIN_ENERGY: " << POSITRON_ENERGY_MIN<<" MeV"<<G4endl;
Summary_file<<"    @POSITRONS_MEAN_ENERGY: " << POSITRON_ENERGY_MEAN /NUMBER_OF_POSITRONS <<" MeV"   <<G4endl;
Summary_file<<" ____________________________________________________________________________________________________________" <<G4endl;
}
if (NUMBER_OF_PROTONS >   0)    
{      
Summary_file<<"    @PROTONS_MAX_ENERGY: "<< PROTON_ENERGY_MAX<<" MeV"  <<G4endl;
Summary_file<<"    @PROTONS_MIN_ENERGY: "<< PROTON_ENERGY_MIN<<" MeV"  <<G4endl;
Summary_file<<"    @PROTONS_MEAN_ENERGY: "<< PROTON_ENERGY_MEAN/NUMBER_OF_PROTONS <<" MeV"<<G4endl;
Summary_file<<" ____________________________________________________________________________________________________________" <<G4endl;
}
if (NUMBER_OF_NEUTRONS > 0) 
{
Summary_file<<"   @NEUTRONS_MAX_ENERGY: " << NEUTRON_ENERGY_MAX <<" MeV"<<G4endl;
Summary_file<<"   @NEUTRONS_MIN_ENERGY: " << NEUTRON_ENERGY_MIN<<" MeV" <<G4endl;
Summary_file<<"   @NEUTRONS_MEAN_ENERGY: "  << NEUTRON_ENERGY_MEAN/NUMBER_OF_NEUTRONS<<" MeV" <<G4endl;
Summary_file<<" ____________________________________________________________________________________________________________" <<G4endl;
}
Summary_file.close();
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#= */
