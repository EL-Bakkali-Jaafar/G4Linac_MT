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
//
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#
  AUTHOR: Dr. Jaafar EL Bakkali, Assistant Professor of Nuclear Physics, Rabat, Morocco.
  e-mail: bahmedj@gmail.com

  For documentation
  see http://G4Linac_MT.github.com
 
  10/08/2017: public version 1.0
 
#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
#include "DetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "G4SDManager.hh"
#include "PhantomSD.hh"
#include "G4PVReplica.hh"
#include "G4VisAttributes.hh"
#include "DetectorROGeometry.hh"
#include "DetectorMessenger.hh"
#include "G4TransportationManager.hh"
#include "G4tgbVolumeMgr.hh"
#include "G4tgrMessenger.hh"
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
const std::string                                  DatasetName_histories("BeamData")       ,
                                                   MEMBER_HISTORIES("_NUMBER_OF_HISTORIES"),
                                                   MEMBER_Z_STOP("_Z_STOP")                ,
                                                   DatasetName_event("EventData")          ,
                                                   MEMBER_ENTERIES("_ENTERIES")            ,
                                                   MEMBER_EVENTID("_EVENTID")              ,
                                                   DatasetName("PhspData")                 ,
                                                   MEMBER_PART_PDGE("_PART_PDGE")          ,
                                                   MEMBER_PART_WEIGHT("_PART_WEIGHT")      ,
                                                   MEMBER_PART_POS_X("_PART_POS_X")        ,
                                                   MEMBER_PART_POS_Y("_PART_POS_Y")        ,
                                                   MEMBER_PART_POS_Z("_PART_POS_Z")        ,
                                                   MEMBER_PART_DIR_X("_PART_DIR_X")        ,
                                                   MEMBER_PART_DIR_Y("_PART_DIR_Y")        ,
                                                   MEMBER_PART_DIR_Z("_PART_DIR_Z")        ,
                                                   MEMBER_PART_KINETIC("_PART_KINETIC")    ;
DetectorConstruction::PhspData*                    RAM_PhspData                            ;
DetectorConstruction::EventData*                   RAM_EventData                           ;

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
G4ThreadLocal G4bool DetectorConstruction::fConstructedSDandField = false;
DetectorConstruction::DetectorConstruction(int _NUMBER_OF_THREADS)
: G4VUserDetectorConstruction(), mPhantomSD(0), fConstructed(false),VoxalizedPhantomSizeZ(0),VoxalizedPhantomSizeX(0),VoxalizedPhantomSizeY(0),NUMBER_OF_THREADS(_NUMBER_OF_THREADS)
{ 
pDetectorMessenger= new DetectorMessenger(this); 
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
DetectorConstruction::~DetectorConstruction()
{ 
delete RAM_PhspData;
delete RAM_EventData;
delete myBeamData;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorConstruction::SetNumberOfEventsPerThread( int _NumberOfEventsPerThread)
{
this->NumberOfEventsPerThread=_NumberOfEventsPerThread;
}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorConstruction::SetNsplit( int _nsplit)
{ 
this->Nsplit=_nsplit;
}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorConstruction::SetNameOfGeomFromTextFile(G4String _FileName){
this->geom_file_name=_FileName;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorConstruction::SetGeomFromTextFlag(bool _flag){
this->use_geom_from_text=_flag;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorConstruction::SetGeneratorFlag(int _flag)
{ 
this->GeneratorFlag=_flag;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
G4VPhysicalVolume* DetectorConstruction::Construct(){
if (this->use_geom_from_text==true)
{
G4String filename = this->geom_file_name;
messenger = new G4tgrMessenger;
G4tgbVolumeMgr* volmgr = G4tgbVolumeMgr::GetInstance();
volmgr->AddTextFile(filename);
//------------------------------------------------
// Read the text files and construct the GEANT4 geometry
//------------------------------------------------
G4VPhysicalVolume* physiWorld = volmgr->ReadAndConstructDetector();
G4cout<<"  construct Geant4 geometry"<<G4endl;
//volmgr -> DumpSummary();

DetectorROGeometry* RO = (DetectorROGeometry*) GetParallelWorld(0);
RO->Initialize(this->ReadOutGeometryCenterPosition ,
                     GetVoxalizedPhantomSizeX()/2           ,
                     GetVoxalizedPhantomSizeY()/2           ,
                     GetVoxalizedPhantomSizeZ()/2           ,
                     GetNumberOfVoxelsAlongX()     ,
                     GetNumberOfVoxelsAlongY()     ,
                     GetNumberOfVoxelsAlongZ())    ;
    

RO->UpdateROGeometry();  
READ_BEAM_DATA();
READ_EVENT_DATA();
READ_PHSP_DATA();
return physiWorld;



} 
else
{
if(!fConstructed)
{
fConstructed = true;
SetupGeometry();
READ_BEAM_DATA();
READ_EVENT_DATA();
READ_PHSP_DATA();
}
return this->physWorld;
}
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
/*
void DetectorConstruction::ConstructSDandField() 
{
// 
fConstructedSDandField = true;
SetupDetectors(); 
}
*/
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorConstruction::SetupGeometry(){  
// Get nist material manager
G4NistManager* nist = G4NistManager::Instance();
// World and detector dimensions
G4double world_sizeXY           = 2*m;
G4double world_sizeZ            = 2*m;
G4double detector_size          = 20*cm;
phantom_mat         = nist->FindOrBuildMaterial("G4_WATER");// Tungesten
G4Material* world_mat           = nist->FindOrBuildMaterial("G4_Galactic");//Vacum
solidWorld               = new G4Box("World", 0.5*world_sizeXY, 0.5*world_sizeXY, 0.5*world_sizeZ);      
logicWorld     = new G4LogicalVolume(solidWorld, world_mat, "logicWorld");
logicWorld->SetVisAttributes(G4VisAttributes::GetInvisible());
this->physWorld   = new G4PVPlacement(0, G4ThreeVector(),logicWorld,"World",  0, false,0,false);                     
// 
solidDetector            = new G4Box("Detector", 0.5*detector_size , 0.5*detector_size,  0.5*detector_size);      
 //
logicdDetector = new G4LogicalVolume(solidDetector,phantom_mat,  "logicdDetector");
//
pDetector    = new G4PVPlacement(0,  G4ThreeVector(0.0,0.0,20*cm), logicdDetector,  "pDetector", logicWorld,false,  0, false);
DetectorROGeometry* RO = (DetectorROGeometry*) GetParallelWorld(0);
RO->Initialize(this->ReadOutGeometryCenterPosition ,
                     GetVoxalizedPhantomSizeX()/2           ,
                     GetVoxalizedPhantomSizeY()/2           ,
                     GetVoxalizedPhantomSizeZ()/2           ,
                     GetNumberOfVoxelsAlongX()     ,
                     GetNumberOfVoxelsAlongY()     ,
                     GetNumberOfVoxelsAlongZ())    ;
    

RO->UpdateROGeometry();    
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorConstruction::SetupDetectors()
{
 G4SDManager* pSDManager         = G4SDManager::GetSDMpointer();
 PhantomSD *pPhantomSD = new PhantomSD("Phantom");
 pSDManager-> AddNewDetector(mPhantomSD);
 SetSensitiveDetector("logicdDetector",pPhantomSD);
  }
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorConstruction::SetNumberOfVoxelsAlongX(int _numberOfVoxelsAlongX) {
this->numberOfVoxelsAlongX= _numberOfVoxelsAlongX;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
int  DetectorConstruction::GetNumberOfVoxelsAlongX() {
return this->numberOfVoxelsAlongX;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorConstruction::SetNumberOfVoxelsAlongY(int _numberOfVoxelsAlongY) {
this->numberOfVoxelsAlongY= _numberOfVoxelsAlongY;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
int  DetectorConstruction::GetNumberOfVoxelsAlongY() {
return this->numberOfVoxelsAlongY;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorConstruction::SetNumberOfVoxelsAlongZ(int _numberOfVoxelsAlongZ) {
this->numberOfVoxelsAlongZ= _numberOfVoxelsAlongZ;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
int  DetectorConstruction::GetNumberOfVoxelsAlongZ() {
return this->numberOfVoxelsAlongZ;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorConstruction::SetVoxalizedPhantomSizeX(G4double _VoxalizedPhantomSizeX) {
this->VoxalizedPhantomSizeX= _VoxalizedPhantomSizeX;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
int  DetectorConstruction::GetVoxalizedPhantomSizeX() {
return this->VoxalizedPhantomSizeX;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorConstruction::SetVoxalizedPhantomSizeY(G4double _VoxalizedPhantomSizeY) {
this->VoxalizedPhantomSizeY= _VoxalizedPhantomSizeY;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
int  DetectorConstruction::GetVoxalizedPhantomSizeY() {
return this->VoxalizedPhantomSizeY;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorConstruction::SetVoxalizedPhantomSizeZ(G4double _VoxalizedPhantomSizeZ) {
this->VoxalizedPhantomSizeZ= _VoxalizedPhantomSizeZ;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
int  DetectorConstruction::GetVoxalizedPhantomSizeZ() {
return this->VoxalizedPhantomSizeZ;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorConstruction::SetReadOutGeometryCenterPosition(G4ThreeVector  _ReadOutGeometryCenterPosition) {
this->ReadOutGeometryCenterPosition= _ReadOutGeometryCenterPosition;
}
G4ThreeVector  DetectorConstruction::GetReadOutGeometryCenterPosition() {
return this->ReadOutGeometryCenterPosition;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorConstruction::SetCenterVoxel_X_ID(G4int _CenterVoxel_X_ID) {
this->CenterVoxel_X_ID= _CenterVoxel_X_ID;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
int  DetectorConstruction::GetCenterVoxel_X_ID() {
return this->CenterVoxel_X_ID;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorConstruction::SetCenterVoxel_Y_ID(G4int _CenterVoxel_Y_ID) {
this->CenterVoxel_Y_ID= _CenterVoxel_Y_ID;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
int  DetectorConstruction::GetCenterVoxel_Y_ID() {
return this->CenterVoxel_Y_ID;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorConstruction::SetNomalizedPDDVoxel_Z_ID(G4int _NomalizedPDDVoxel_Z_ID) {
this->NomalizedPDDVoxel_Z_ID= _NomalizedPDDVoxel_Z_ID;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
int  DetectorConstruction::GetNomalizedPDDVoxel_Z_ID() {
return this->NomalizedPDDVoxel_Z_ID;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorConstruction::SetNomalizedPROFILEVoxel_X_ID(G4int _NomalizedPROFILEVoxel_X_ID) {
this->NomalizedPROFILEVoxel_X_ID= _NomalizedPROFILEVoxel_X_ID;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
int  DetectorConstruction::GetNomalizedPROFILEVoxel_X_ID() {
return this->NomalizedPROFILEVoxel_X_ID;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorConstruction::SetNewZSTOP(G4double _ZSTOP){
this->NewZSTOP=_ZSTOP;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorConstruction::SetH5PhaseSpaceFileName(G4String _Filename){
this->H5PhaseSpaceFileName=_Filename+".h5";
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorConstruction::READ_PHSP_DATA(){
{
H5File file( this->H5PhaseSpaceFileName, H5F_ACC_RDONLY );
DataSet dataset = file.openDataSet( DatasetName );
H5::CompType mtype2( sizeof(PhspData) );
G4int data_size  = dataset.getSpace().getSimpleExtentNpoints();
    RAM_PhspData    = new PhspData[data_size];
    mtype2.insertMember(MEMBER_PART_WEIGHT,  HOFFSET(PhspData, PART_WEIGHT),   H5::PredType::NATIVE_FLOAT);
    mtype2.insertMember(MEMBER_PART_POS_X,   HOFFSET(PhspData, PART_POS_X),    H5::PredType::NATIVE_FLOAT);
    mtype2.insertMember(MEMBER_PART_PDGE,    HOFFSET(PhspData, PART_PDGE),     H5::PredType::NATIVE_INT);
    mtype2.insertMember(MEMBER_PART_POS_Y,   HOFFSET(PhspData, PART_POS_Y),    H5::PredType::NATIVE_FLOAT);
    mtype2.insertMember(MEMBER_PART_POS_Z,   HOFFSET(PhspData, PART_POS_Z),    H5::PredType::NATIVE_FLOAT);
    mtype2.insertMember(MEMBER_PART_DIR_X,   HOFFSET(PhspData, PART_DIR_X),    H5::PredType::NATIVE_FLOAT);
    mtype2.insertMember(MEMBER_PART_DIR_Y,   HOFFSET(PhspData, PART_DIR_Y),    H5::PredType::NATIVE_FLOAT);
    mtype2.insertMember(MEMBER_PART_DIR_Z,   HOFFSET(PhspData, PART_DIR_Z),    H5::PredType::NATIVE_FLOAT);
    mtype2.insertMember(MEMBER_PART_KINETIC, HOFFSET(PhspData, PART_KINETIC),  H5::PredType::NATIVE_FLOAT);
    dataset.read( RAM_PhspData, mtype2 );

}
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorConstruction::READ_BEAM_DATA()
 {
     const std::string FileName(this->H5PhaseSpaceFileName);
     H5File file( FileName, H5F_ACC_RDONLY );
     DataSet dataset_histories = file.openDataSet( DatasetName_histories );
     H5::CompType mtype_histories( sizeof(BeamData) );
     mtype_histories.insertMember(MEMBER_HISTORIES,     HOFFSET(BeamData, NUMBER_OF_HISORIES),      H5::PredType::NATIVE_INT)   ;
     mtype_histories.insertMember(MEMBER_Z_STOP   ,     HOFFSET(BeamData, Z_STOP)            ,      H5::PredType::NATIVE_FLOAT) ;
     dataset_histories.read( myBeamData, mtype_histories );
 }
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorConstruction::READ_EVENT_DATA()
 {
     G4ThreadLocal  H5File file(  this->H5PhaseSpaceFileName, H5F_ACC_RDONLY );
     G4ThreadLocal DataSet dataset_event = file.openDataSet( DatasetName_event );
     G4ThreadLocal H5::CompType mtype_event( sizeof(EventData) );
     G4int data_event_size=dataset_event.getSpace().getSimpleExtentNpoints();
     RAM_EventData = new EventData[data_event_size];
     mtype_event.insertMember(MEMBER_ENTERIES,     HOFFSET(EventData, NUMBER_OF_ENTRIES),      H5::PredType::NATIVE_INT);
     mtype_event.insertMember(MEMBER_EVENTID,      HOFFSET(EventData, EVENT_ID),               H5::PredType::NATIVE_INT);
     dataset_event.read( RAM_EventData, mtype_event );

 }
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
