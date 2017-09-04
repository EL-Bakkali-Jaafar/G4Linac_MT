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
auto str = std::to_string(G4Threading::G4GetThreadId())+"_"; 
G4RunManager* runManager = G4RunManager::GetRunManager();
DetectorConstruction * pDetectorConstruction = (DetectorConstruction*)(runManager->GetUserDetectorConstruction()); 
this->Total_Events_To_Be_Processed= runManager->GetNumberOfEventsToBeProcessed();

this-> NumberOfThreads=pDetectorConstruction-> NUMBER_OF_THREADS;
this->DOSIMETRIC_DATA_FileName=str+"Dose3dMap.txt";
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
this-> CentreVoxelID_x=pDetectorConstruction->GetCenterVoxel_X_ID();
this-> CentreVoxelID_y=pDetectorConstruction->GetCenterVoxel_Y_ID();
this-> Voxel_NORMALIZED_ZID=pDetectorConstruction->NomalizedPDDVoxel_Z_ID;
this-> Voxel_NORMALIZED_XID=pDetectorConstruction->NomalizedPROFILEVoxel_X_ID;
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
delete this->Voxels;
delete[] myDosimetricData;
delete[] myPhantomData;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
G4bool PhantomSD::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{
auto str = std::to_string(G4Threading::G4GetThreadId()); 
if (aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName() != "RODetectorZDivisionPhys") return false;
G4String particleName = aStep -> GetTrack() -> GetDynamicParticle() -> GetDefinition() -> GetParticleName();
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
G4double events = this->Voxels[i][j][k].nEvents;
this->NumberTotalEvents++;
}
return true;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void PhantomSD::EndOfEvent(G4HCofThisEvent*)
{
G4RunManager* runManager         = G4RunManager::GetRunManager();
const G4Event * event            =   runManager->GetCurrentEvent();
int Total_Events_To_Be_Processed = runManager->GetNumberOfEventsToBeProcessed();
G4int event_id                   =   event->GetEventID();
if(event_id==0){
//Master Voxels
Master_Voxels=new Svoxel**[this->NumberOfVoxelsAlongX];
for (int ix=0; ix< this->NumberOfVoxelsAlongX; ix++)
{
Master_Voxels[ix]=new Svoxel*[this->NumberOfVoxelsAlongY];
for (int iy=0; iy< this->NumberOfVoxelsAlongY; iy++)
{
 Master_Voxels[ix][iy]=new Svoxel[this->NumberOfVoxelsAlongZ];
for (int iz=0; iz< this->NumberOfVoxelsAlongZ; iz++)
{
Master_Voxels[ix][iy][iz].volumeName="noData";
Master_Voxels[ix][iy][iz].absorbed_dose=0.;
Master_Voxels[ix][iy][iz].absorbed_dose2=0.;
Master_Voxels[ix][iy][iz].HalfSize.set(this->HalfVoxelDimensionAlongX, this->HalfVoxelDimensionAlongY, this->HalfVoxelDimensionAlongZ);
Master_Voxels[ix][iy][iz].pos.set(2.*(ix)*this->HalfVoxelDimensionAlongX  -this->HalfSize.getX()+this->HalfVoxelDimensionAlongX, 
2.*(iy)*this->HalfVoxelDimensionAlongY  -this->HalfSize.getY()+this->HalfVoxelDimensionAlongY, 
2.*(iz)*this->HalfVoxelDimensionAlongZ  -this->HalfSize.getZ()+this->HalfVoxelDimensionAlongZ);
Master_Voxels[ix][iy][iz].nEvents=0;
Master_Voxels[ix][iy][iz].rsd=0.;
}}}};
for (int i=this-> NumberOfThreads; i>= 1; i--){
if( event_id== (i*( Total_Events_To_Be_Processed/this-> NumberOfThreads)-1) ) {
//-------------------------LOCK --------------------
 G4AutoLock merge(&mergeMutex);
last_active_thread++;
MergeDosimetricData();
if(last_active_thread==this->NumberOfThreads){
SaveDataInTextFile();
SaveDataInBinaryFile();
}
merge.unlock();
//-------------------------UNLOCK --------------------
}}}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void PhantomSD::clear(){} 
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void PhantomSD::DrawAll(){}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void PhantomSD::PrintAll(){}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void PhantomSD::saveDataInVoxels()
{
this->saveHeaderDataInVoxels();
dosimetricFile.open(this->DOSIMETRIC_DATA_FileName, std::ios::app);
int iz,iy,ix;
for(ix=0; ix<NumberOfVoxelsAlongX; ix++){
for(iy=0; iy<NumberOfVoxelsAlongY; iy++){
for(iz=0; iz<NumberOfVoxelsAlongZ; iz++){
dosimetricFile<<setw(5)<<ix<<setw(15)<< iy<< setw(20) << iz<<setw(20)<< this->Voxels[ix][iy][iz].absorbed_dose/(MeV/g) << setw(20)<< this->Voxels[ix][iy][iz].rsd<< setw(20)<<this->Voxels[ix][iy][iz].nEvents <<'\n';
}}};
dosimetricFile.close();
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void PhantomSD::saveHeaderDataInVoxels()
{
dosimetricFile.open(this->DOSIMETRIC_DATA_FileName, std::ios::out);
dosimetricFile << "#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#"<< G4endl;
dosimetricFile <<"H5PhaseSpace v2.O: A GEANT4 PHASE-SPACE I/O ROUTINES  BASED ON HDF5 FORMAT "<< G4endl;
dosimetricFile << "DEVELOPED BY DR. JAAFAR EL BAKKALI, BAHMEDJ@GMAIL.COM, TETOUAN-MOROCCO,  JULY 2017 "<< G4endl;
dosimetricFile << "SIMULATION INFOS : CALCULATE DOSIMETRIC DATA" << G4endl;
dosimetricFile<< "TOTAL NUMBERS OF EVENTS IN VOXELISED VOLUME : "<<this->NumberTotalEvents<<G4endl;
dosimetricFile << "VOXELISED PHANTOM SIZE (X,Y,Z) [cm] :" <<pDetectorConstruction-> GetVoxalizedPhantomSizeX()/cm<<"," <<pDetectorConstruction-> GetVoxalizedPhantomSizeY()/cm<<"," <<pDetectorConstruction-> GetVoxalizedPhantomSizeZ()/cm<< G4endl;
dosimetricFile << "NUMBER OF VOXELS (X,Y,Z) : " <<NumberOfVoxelsAlongX<< "," << NumberOfVoxelsAlongY<<","<< NumberOfVoxelsAlongZ<<G4endl;
dosimetricFile << "VOXEL VOLUME : " << this->VoxelVolume/(cm*cm*cm)<< " CM_3 " << G4endl;
dosimetricFile << "VOXEL MASSE : " << this->VoxelMass/(g)<< " GRAMME " << G4endl;
dosimetricFile << "#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#"<< G4endl;
dosimetricFile<< std::setw(5)<<"VOXEL_XID"<<std::setw(15)<<"VOXEL_YID"<<std::setw(20)<<"VOXEL_ZID"<<std::setw(15)<<"DOSE(MeV)"<<std::setw(20)<<"RSD%" << setw(20) <<"NEvents"<<G4endl;
dosimetricFile.close();
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void PhantomSD::MergeDosimetricData(){
// collecting data in each voxel from different threads
int ix,iy,iz;
for(ix=0; ix<NumberOfVoxelsAlongX; ix++){
for(iy=0; iy<NumberOfVoxelsAlongY; iy++){
for(iz=0; iz<NumberOfVoxelsAlongZ; iz++){
Master_Voxels[ix][iy][iz].absorbed_dose+=this->Voxels[ix][iy][iz].absorbed_dose;
Master_Voxels[ix][iy][iz].absorbed_dose2+=this->Voxels[ix][iy][iz].absorbed_dose2;
Master_Voxels[ix][iy][iz].nEvents+=this->Voxels[ix][iy][iz].nEvents;
}}};
// calculating the relative standard deviation for each voxel
int i,j,k;
for(i=0; i<NumberOfVoxelsAlongX; i++){
for(j=0; j<NumberOfVoxelsAlongY; j++){
for(k=0; k<NumberOfVoxelsAlongZ; k++){
G4double events=Master_Voxels[i][j][k].nEvents;
if(events>1){
G4float absorbed_dose =Master_Voxels[i][j][k].absorbed_dose;
G4float absorbed_dose2=Master_Voxels[i][j][k].absorbed_dose2;
G4float absorbed_dose_mean=absorbed_dose/events;
G4float absorbed_dose2_mean=absorbed_dose2/events;
G4float sigma=sqrt((absorbed_dose2_mean-absorbed_dose_mean*absorbed_dose_mean)/(events-1));
Master_Voxels[i][j][k].rsd= 100*sigma/absorbed_dose_mean;
}}}};
auto str_thread = std::to_string(G4Threading::G4GetThreadId());
G4cout<<"\033[33m"<<"G4Linac_Dosecal: getting dosimetric data from thread "<< str_thread<<"\033[0m"<<G4endl;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void PhantomSD::SaveDataInTextFile(){


G4RunManager* runManager = G4RunManager::GetRunManager();

DetectorConstruction * pDetectorConstruction = (DetectorConstruction*)(runManager->GetUserDetectorConstruction()); 
this->Total_Events_To_Be_Processed= runManager->GetNumberOfEventsToBeProcessed();
G4cout<<"this->Total_Events_To_Be_Processed " <<this->Total_Events_To_Be_Processed<<G4endl; 

if (pDetectorConstruction->GeneratorFlag==2){

 this->Total_Events=this->Total_Events_To_Be_Processed*pDetectorConstruction->Nsplit;
G4cout<<"\033[36m"<<"G4Linac_Dosecal: Each particle has been recycled: "<<pDetectorConstruction->Nsplit-1<<" times !"<<G4endl;

}else {

 this->Total_Events=this->Total_Events_To_Be_Processed;

}
TextFile.open("DoseMap.txt", std::ios::out);
int iz,iy,ix;
for(ix=0; ix<NumberOfVoxelsAlongX; ix++){
for(iy=0; iy<NumberOfVoxelsAlongY; iy++){
for(iz=0; iz<NumberOfVoxelsAlongZ; iz++){

TextFile<<setw(5)<<ix<<setw(15)<< iy<< setw(20) << iz<<setw(20)<<Master_Voxels[ix][iy][iz].absorbed_dose/(double)  this->Total_Events<< setw(20)<< Master_Voxels[ix][iy][iz].rsd<< setw(20)<<Master_Voxels[ix][iy][iz].nEvents <<'\n';
}}};
TextFile.close();
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void PhantomSD::SaveDataInBinaryFile(){


G4RunManager* runManager = G4RunManager::GetRunManager();

DetectorConstruction * pDetectorConstruction = (DetectorConstruction*)(runManager->GetUserDetectorConstruction()); 
this->Total_Events_To_Be_Processed= runManager->GetNumberOfEventsToBeProcessed();
G4cout<<"this->Total_Events_To_Be_Processed " <<this->Total_Events_To_Be_Processed<<G4endl; 

if (pDetectorConstruction->GeneratorFlag==2){

 this->Total_Events=this->Total_Events_To_Be_Processed*pDetectorConstruction->Nsplit;


}else {

 this->Total_Events=this->Total_Events_To_Be_Processed;

}
int ix,iy,iz;

G4ThreadLocal fstream fs;
fs.open("dose.dat", ios::out | ios::binary );

G4ThreadLocal DosCalData _DosCalData ;
G4cout<<"this->Total_Events" <<this->Total_Events<<G4endl;

G4cout<<"\033[36m"<<"G4Linac_Dosecal: Total Events Processed: "<<this->Total_Events<<G4endl;
for(ix=0; ix<NumberOfVoxelsAlongX; ix++){
for(iy=0; iy<NumberOfVoxelsAlongY; iy++){
for(iz=0; iz<NumberOfVoxelsAlongZ; iz++){
_DosCalData.PHANTOM_SIZE_X=this->VoxalizedPhantomSizeX/cm;
_DosCalData.PHANTOM_SIZE_Y=this->VoxalizedPhantomSizeY/cm;
_DosCalData.PHANTOM_SIZE_Z=this->VoxalizedPhantomSizeZ/cm;
_DosCalData.VOXEL_XID=ix;
_DosCalData.VOXEL_YID=iy;
_DosCalData.VOXEL_ZID=iz;
_DosCalData.DOSE=Master_Voxels[ix][iy][iz].absorbed_dose/(double)this->Total_Events;// MeV/g/Nevents
_DosCalData.RSD=Master_Voxels[ix][iy][iz].rsd;// relative standard deviation (%)
_DosCalData.NUMBER_VOXELS_ALONG_X= this-> NumberOfVoxelsAlongX;
_DosCalData.NUMBER_VOXELS_ALONG_Y= this-> NumberOfVoxelsAlongY;
_DosCalData.NUMBER_VOXELS_ALONG_Z= this-> NumberOfVoxelsAlongZ;

fs.write(reinterpret_cast<char *>(&_DosCalData),sizeof(DosCalData));
}}}
fs.close();
G4cout<<"\033[36m"<<"G4Linac_Dosecal: All dosimetric data have been successfuly saved to dose.dat"<<"\033[0m"<<G4endl;

}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
