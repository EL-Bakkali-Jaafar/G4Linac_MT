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
#include "G4Run.hh"
#include "G4Event.hh"
#include "G4Track.hh"
#include "G4Step.hh"
#include "G4VSolid.hh"
#include "G4LogicalVolume.hh"
#include "G4VPhysicalVolume.hh"
#include "G4VTouchable.hh"
#include "G4TouchableHistory.hh"
#include "G4RunManager.hh"
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
#include "PhantomSD.hh"
#include "DetectorConstruction.hh"
#include "G4RunManager.hh"
#include <vector>
#include "G4SystemOfUnits.hh"
#include "G4Threading.hh"
#include "G4Threading.hh"
#include "G4EventManager.hh"
#include "G4RunManager.hh"
#include "G4Threading.hh"
#include "G4AutoLock.hh"
#include <iostream>
#include <math.h>
#include <fstream>
using namespace std;
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
using namespace std;
namespace {G4Mutex mergeMutex = G4MUTEX_INITIALIZER;}

G4ThreadLocal     PhantomSD::DosimetricData*  myDosimetricData;
G4ThreadLocal     PhantomSD::PhantomData      myPhantomData[1];
                  Svoxel ***                  Master_Voxels;
G4ThreadLocal     int                         PhantomSD::INCREMENTOR; 
                  static int                  last_active_thread=0;
                  int                         Total_Events_To_Be_Processed;
const std::string DatasetName("DosimetricData");
const std::string DOSIMRTRICDATA_FILE_NAME("DosimetricData.h5");
const std::string MEMBER_RSD("_RSD");//Relative Standard Deviation expressed in %
const std::string MEMBER_DOSE("_DOSE");
const std::string MEMBER_VOXEL_XID("_VOXEL_XID");
const std::string MEMBER_VOXEL_YID("_VOXEL_YID");
const std::string MEMBER_VOXEL_ZID("_VOXEL_ZID");
const std::string DatasetName_phantom("PhantomData");
const std::string MEMBER_NUMBER_VOXELS_ALONG_X("_NUMBER_VOXELS_ALONG_X");
const std::string MEMBER_NUMBER_VOXELS_ALONG_Y("_NUMBER_VOXELS_ALONG_Y");
const std::string MEMBER_NUMBER_VOXELS_ALONG_Z("_NUMBER_VOXELS_ALONG_Z");
const std::string MEMBER_PHANTOM_SIZE_X("_PHANTOM_SIZE_X");
const std::string MEMBER_PHANTOM_SIZE_Y("_PHANTOM_SIZE_Y");
const std::string MEMBER_PHANTOM_SIZE_Z("_PHANTOM_SIZE_Z");

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
PhantomSD::PhantomSD(G4String name )
: G4VSensitiveDetector(name),Voxels(0)
{ 
INCREMENTOR=0;
G4RunManager* runManager = G4RunManager::GetRunManager();
this->pDetectorConstruction = (DetectorConstruction*)(runManager->GetUserDetectorConstruction()); 
this->Total_Events_To_Be_Processed= runManager->GetNumberOfEventsToBeProcessed();
this-> NumberOfThreads=pDetectorConstruction-> NUMBER_OF_THREADS;
this-> NumberTotalEvents=0;
this-> HalfSize=G4ThreeVector(0.5*pDetectorConstruction-> GetVoxalizedPhantomSizeX(), 0.5*pDetectorConstruction-> GetVoxalizedPhantomSizeY(),0.5*pDetectorConstruction-> GetVoxalizedPhantomSizeZ());
this-> VoxelVolume=0.;
this-> VoxelMass=0.*g;
this-> NumberOfVoxelsAlongX=pDetectorConstruction-> GetNumberOfVoxelsAlongX();
this-> NumberOfVoxelsAlongY=pDetectorConstruction-> GetNumberOfVoxelsAlongY();
this-> NumberOfVoxelsAlongZ=pDetectorConstruction-> GetNumberOfVoxelsAlongZ();
this->VoxalizedPhantomSizeX=pDetectorConstruction-> GetVoxalizedPhantomSizeX();
this->VoxalizedPhantomSizeY=pDetectorConstruction-> GetVoxalizedPhantomSizeY();
this->VoxalizedPhantomSizeZ=pDetectorConstruction-> GetVoxalizedPhantomSizeZ();
this-> HalfVoxelDimensionAlongX=(0.5*this->VoxalizedPhantomSizeX/this->NumberOfVoxelsAlongX);
this-> HalfVoxelDimensionAlongY=(0.5*this->VoxalizedPhantomSizeY/this->NumberOfVoxelsAlongY);
this-> HalfVoxelDimensionAlongZ=(0.5*this->VoxalizedPhantomSizeZ/this->NumberOfVoxelsAlongZ);
this->VoxelVolume=(2*this->HalfVoxelDimensionAlongX)*(2*this->HalfVoxelDimensionAlongY)*(2*this->HalfVoxelDimensionAlongZ);
// Thread Voxels
this->Voxels=new Svoxel**[this->NumberOfVoxelsAlongX];
for (int ix=0; ix< this->NumberOfVoxelsAlongX; ix++)
{
this->Voxels[ix]=new Svoxel*[this->NumberOfVoxelsAlongY];
for (int iy=0; iy< this->NumberOfVoxelsAlongY; iy++)
{
this->Voxels[ix][iy]=new Svoxel[this->NumberOfVoxelsAlongZ];
for (int iz=0; iz< this->NumberOfVoxelsAlongZ; iz++)
{
this->Voxels[ix][iy][iz].volumeName="noData";
this->Voxels[ix][iy][iz].absorbed_dose=0.;
this->Voxels[ix][iy][iz].absorbed_dose2=0.;
this->Voxels[ix][iy][iz].HalfSize.set(this->HalfVoxelDimensionAlongX, this->HalfVoxelDimensionAlongY, this->HalfVoxelDimensionAlongZ);
this->Voxels[ix][iy][iz].pos.set(2.*(ix)*this->HalfVoxelDimensionAlongX-this->HalfSize.getX()+this->HalfVoxelDimensionAlongX, 
2.*(iy)*this->HalfVoxelDimensionAlongY-this->HalfSize.getY()+this->HalfVoxelDimensionAlongY, 
2.*(iz)*this->HalfVoxelDimensionAlongZ-this->HalfSize.getZ()+this->HalfVoxelDimensionAlongZ);
this->Voxels[ix][iy][iz].nEvents=0;
this->Voxels[ix][iy][iz].rsd=0.;
}
}
}	
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
PhantomSD::~PhantomSD()
{

}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
G4bool PhantomSD::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{
if (aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName() != "RODetectorZDivisionPhys") return false;
G4double ENERGY_DEPOSIT = aStep -> GetTotalEnergyDeposit();
ENERGY_DEPOSIT *=MeV;
if(ENERGY_DEPOSIT  == 0.) return false;
if(ENERGY_DEPOSIT  != 0) { 
const G4VTouchable* touchable = aStep->GetPreStepPoint()->GetTouchable();
G4int k= touchable->GetReplicaNumber(0);
G4int i= touchable->GetReplicaNumber(2);
G4int j= touchable->GetReplicaNumber(1);
x= ( - this->NumberOfVoxelsAlongX + 1+ 2*i )*this->HalfVoxelDimensionAlongX;
y= ( - this->NumberOfVoxelsAlongY+ 1+ 2*j )* this->HalfVoxelDimensionAlongY;
z = ( - this->NumberOfVoxelsAlongZ+ 1+ 2*k)*this->HalfVoxelDimensionAlongZ;
this->density=aStep->GetPreStepPoint()->GetPhysicalVolume()->GetLogicalVolume()->GetMaterial()->GetDensity();
this->VoxelMass*=g;
this->VoxelMass=this->VoxelVolume*this->density;
G4double DOSE;
DOSE*=MeV/g;
DOSE=ENERGY_DEPOSIT/this->VoxelMass;
this->Voxels[i][j][k].absorbed_dose+=DOSE/(MeV/g);
this->Voxels[i][j][k].absorbed_dose2+=(DOSE/(MeV/g)*DOSE/(MeV/g));
this->Voxels[i][j][k].nEvents++;
this->NumberTotalEvents++;
G4double events = this->Voxels[i][j][k].nEvents;
if(events>1){
G4double absorbed_dose =Voxels[i][j][k].absorbed_dose;
G4double absorbed_dose2=Voxels[i][j][k].absorbed_dose2;
G4double absorbed_dose_mean=absorbed_dose/events;
G4double absorbed_dose2_mean=absorbed_dose2/events;
G4double sigma=sqrt((absorbed_dose2_mean-absorbed_dose_mean*absorbed_dose_mean)/(events-1));
Voxels[i][j][k].rsd= 100*sigma/absorbed_dose_mean;
}
}
return true;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void PhantomSD::EndOfEvent(G4HCofThisEvent*)
{
G4RunManager* runManager           = G4RunManager::GetRunManager();
const G4Event * event              =   runManager->GetCurrentEvent();
this->Total_Events_To_Be_Processed = runManager->GetNumberOfEventsToBeProcessed();
G4int event_id                     =   event->GetEventID();

for (int i=G4Threading::GetNumberOfRunningWorkerThreads(); i>= 1; i--){
if( event_id== (i*( Total_Events_To_Be_Processed/this-> NumberOfThreads)-1) ) {

SaveDataInBinaryFile();

}}}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void PhantomSD::clear(){} 
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void PhantomSD::DrawAll(){}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void PhantomSD::PrintAll(){}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
 void PhantomSD::SaveDataInBinaryFile(){
auto str_thread = std::to_string(G4Threading::G4GetThreadId());
G4cout<<"G4LINAC_DOSECAL-> GETTING DOSIMETRIC DATA FROM THREAD:  "<< str_thread<<G4endl;
G4RunManager* runManager = G4RunManager::GetRunManager();
this->pDetectorConstruction = (DetectorConstruction*)(runManager->GetUserDetectorConstruction()); 
this->Total_Events_To_Be_Processed= runManager->GetNumberOfEventsToBeProcessed();
if (pDetectorConstruction->GeneratorFlag==2){
 this->Total_Events=this->Total_Events_To_Be_Processed*pDetectorConstruction->Nsplit;
}else {
 this->Total_Events=this->Total_Events_To_Be_Processed;
}
int ix,iy,iz;
G4ThreadLocal fstream fs;
fs.open(str_thread+"dose.dat", ios::out | ios::binary );
G4ThreadLocal DosCalData _DosCalData ;
for(ix=0; ix<NumberOfVoxelsAlongX; ix++){
for(iy=0; iy<NumberOfVoxelsAlongY; iy++){
for(iz=0; iz<NumberOfVoxelsAlongZ; iz++){
_DosCalData.PHANTOM_SIZE_X=this->VoxalizedPhantomSizeX/cm;
_DosCalData.PHANTOM_SIZE_Y=this->VoxalizedPhantomSizeY/cm;
_DosCalData.PHANTOM_SIZE_Z=this->VoxalizedPhantomSizeZ/cm;
_DosCalData.VOXEL_XID=ix;
_DosCalData.VOXEL_YID=iy;
_DosCalData.VOXEL_ZID=iz;
_DosCalData.NEVENTS=Voxels[ix][iy][iz].nEvents;// MeV/g/Nevents
_DosCalData.DOSE=Voxels[ix][iy][iz].absorbed_dose;// MeV/g/Nevents
_DosCalData.DOSE2=Voxels[ix][iy][iz].absorbed_dose2;// MeV/g/Nevents
_DosCalData.RSD=Voxels[ix][iy][iz].rsd;// relative standard deviation (%)
_DosCalData.NUMBER_VOXELS_ALONG_X= this-> NumberOfVoxelsAlongX;
_DosCalData.NUMBER_VOXELS_ALONG_Y= this-> NumberOfVoxelsAlongY;
_DosCalData.NUMBER_VOXELS_ALONG_Z= this-> NumberOfVoxelsAlongZ;
fs.write(reinterpret_cast<char *>(&_DosCalData),sizeof(DosCalData));
}}}
fs.close();

}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
