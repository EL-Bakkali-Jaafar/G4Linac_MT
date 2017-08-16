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
//#include "HistoManager.hh"
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

G4ThreadLocal     PhantomSD::DosimetricData *myDosimetricData;

G4ThreadLocal     PhantomSD::PhantomData  myPhantomData[1];

Svoxel ***Master_Voxels;
G4ThreadLocal   int PhantomSD::INCREMENTOR;

int Total_Events_To_Be_Processed;


/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
PhantomSD::PhantomSD(G4String name )
: G4VSensitiveDetector(name),Voxels(0)
{ 

G4cout<<" initializing class PhantomSD" <<G4endl;

//

//



//INITIALIZING INCREMENTOR 
INCREMENTOR=0;
 auto str = std::to_string(G4Threading::G4GetThreadId())+"_"; 

G4RunManager* runManager = G4RunManager::GetRunManager();

pDetectorConstruction = (DetectorConstruction*)(runManager->GetUserDetectorConstruction()); 
this-> NumberOfThreads=pDetectorConstruction-> NUMBER_OF_THREADS;
this->DOSIMETRIC_DATA_FileName=str+"Dose3dMap.txt";
this-> NumberTotalEvents=0;
this-> HalfSize=G4ThreeVector(0.5*pDetectorConstruction-> GetPhantomSizeX(), 0.5*pDetectorConstruction-> GetPhantomSizeY(),0.5*pDetectorConstruction-> GetPhantomSizeZ());
  this-> VoxelVolume=0.;
  this-> VoxelMass=0.*g;
  this-> NumberOfVoxelsAlongX=pDetectorConstruction-> GetNumberOfVoxelsAlongX();
  this-> NumberOfVoxelsAlongY=pDetectorConstruction-> GetNumberOfVoxelsAlongY();
  this-> NumberOfVoxelsAlongZ=pDetectorConstruction->  GetNumberOfVoxelsAlongZ();
  this-> HalfVoxelDimensionAlongX=(0.5*pDetectorConstruction-> GetPhantomSizeX()/this->NumberOfVoxelsAlongX);
  this-> HalfVoxelDimensionAlongY=(0.5*pDetectorConstruction-> GetPhantomSizeY()/this->NumberOfVoxelsAlongY);
  this-> HalfVoxelDimensionAlongZ=(0.5*pDetectorConstruction-> GetPhantomSizeZ()/this->NumberOfVoxelsAlongZ);
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
  this->Voxels[ix][iy][iz].depEnergy=0.;
  this->Voxels[ix][iy][iz].depEnergy2=0.;
  this->Voxels[ix][iy][iz].HalfSize.set(this->HalfVoxelDimensionAlongX, this->HalfVoxelDimensionAlongY, this->HalfVoxelDimensionAlongZ);
  this->Voxels[ix][iy][iz].pos.set(2.*(ix)*this->HalfVoxelDimensionAlongX  -this->HalfSize.getX()+this->HalfVoxelDimensionAlongX, 
  2.*(iy)*this->HalfVoxelDimensionAlongY  -this->HalfSize.getY()+this->HalfVoxelDimensionAlongY, 
  2.*(iz)*this->HalfVoxelDimensionAlongZ  -this->HalfSize.getZ()+this->HalfVoxelDimensionAlongZ);
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


//

}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
G4bool PhantomSD::ProcessHits(G4Step* aStep,G4TouchableHistory*)
{
 auto str = std::to_string(G4Threading::G4GetThreadId()); 
//


   if (aStep -> GetPreStepPoint() -> GetPhysicalVolume() -> GetName() != "RODetectorZDivisionPhys") return false;
  G4String particleName = aStep -> GetTrack() -> GetDynamicParticle() -> GetDefinition() -> GetParticleName();
  G4double edep = aStep -> GetTotalEnergyDeposit();
 //
 edep*=MeV;

  if(edep == 0.) return false;
  if(edep != 0)                       
	    {   

 const G4VTouchable* touchable = aStep->GetPreStepPoint()->GetTouchable();
 G4int k  = touchable->GetReplicaNumber(0);
 G4int i  = touchable->GetReplicaNumber(2);
 G4int j  = touchable->GetReplicaNumber(1);

    
  x = ( - this->NumberOfVoxelsAlongX + 1+ 2*i )*this->HalfVoxelDimensionAlongX;
  y = ( - this->NumberOfVoxelsAlongY+ 1+ 2*j )* this->HalfVoxelDimensionAlongY;
  z = ( - this->NumberOfVoxelsAlongZ+ 1+ 2*k)*this->HalfVoxelDimensionAlongZ;
  this->density=aStep->GetPreStepPoint()->GetPhysicalVolume()->GetLogicalVolume()->GetMaterial()->GetDensity();
  this->VoxelMass=this->VoxelVolume*this->density;
  // Absorbed dose

  //edep/=this->VoxelMass;
  this->Voxels[i][j][k].depEnergy+=edep;
  this->Voxels[i][j][k].depEnergy2+=edep*edep;
  this->Voxels[i][j][k].nEvents++;
  G4double events = this->Voxels[i][j][k].nEvents;

  if(events>1){

  G4double dp =this->Voxels[i][j][k].depEnergy;
  G4double dp2=this->Voxels[i][j][k].depEnergy2;
  G4double dpm=dp/events/MeV;
  G4double dp2m=dp2/events/(MeV*MeV);
 
  G4double sigma=sqrt((dp2m-dpm*dpm)/(events-1));

  //
this->Voxels[i][j][k].rsd=100*sigma/dpm;


  }
  this->NumberTotalEvents++;
  }
  return true;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void PhantomSD::EndOfEvent(G4HCofThisEvent*)
{
//
G4RunManager* runManager = G4RunManager::GetRunManager();

//this->saveDataInVoxels();
//
const G4Event * event    =   runManager->GetCurrentEvent();
int Total_Events_To_Be_Processed= runManager->GetNumberOfEventsToBeProcessed();
G4int event_id           =   event->GetEventID();
for (int i=this-> NumberOfThreads; i>= 1; i--){
if( event_id== (i*( Total_Events_To_Be_Processed/this-> NumberOfThreads)-1) ) {
//
this->saveDataInVoxels();
MergeDosimetricData();
if ( event_id==Total_Events_To_Be_Processed-1){
SaveDataInH5File();}
}
}

}
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

dosimetricFile<<setw(5)<<ix<<setw(15)<< iy<< setw(20) << iz<<setw(20)<< this->Voxels[ix][iy][iz].depEnergy << setw(20)<< this->Voxels[ix][iy][iz].rsd<< setw(20)<<this->Voxels[ix][iy][iz].nEvents <<'\n';
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
dosimetricFile << "VOXELISED PHANTOM SIZE (X,Y,Z) [cm] :" <<pDetectorConstruction-> GetPhantomSizeX()/cm<<"," <<pDetectorConstruction-> GetPhantomSizeY()/cm<<"," <<pDetectorConstruction-> GetPhantomSizeZ()/cm<< G4endl;
dosimetricFile << "NUMBER OF VOXELS (X,Y,Z) : " <<  NumberOfVoxelsAlongX<< "," << NumberOfVoxelsAlongY<<","<< NumberOfVoxelsAlongZ<<G4endl;
dosimetricFile << "VOXEL VOLUME : " << this->VoxelVolume/(cm*cm*cm)  << " CM_3 " << G4endl;
dosimetricFile << "VOXEL MASSE : " << this->VoxelMass/(g)  << " GRAMME " << G4endl;
dosimetricFile << "#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#"<< G4endl;
dosimetricFile<< std::setw(5)<<"VOXEL_XID"<<std::setw(15)<<"VOXEL_YID"<<std::setw(20)<<"VOXEL_ZID"<<std::setw(15)<<"EDEP(MeV)"<<std::setw(20)<<"RSD%" << setw(20) <<"NEvents"<<G4endl;
dosimetricFile.close();
}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/

void PhantomSD::MergeDosimetricData(){
//Initialize Master Voxles data.

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
Master_Voxels[ix][iy][iz].depEnergy=0.;
  Master_Voxels[ix][iy][iz].depEnergy2=0.;
Master_Voxels[ix][iy][iz].HalfSize.set(this->HalfVoxelDimensionAlongX, this->HalfVoxelDimensionAlongY, this->HalfVoxelDimensionAlongZ);
 Master_Voxels[ix][iy][iz].pos.set(2.*(ix)*this->HalfVoxelDimensionAlongX  -this->HalfSize.getX()+this->HalfVoxelDimensionAlongX, 
  2.*(iy)*this->HalfVoxelDimensionAlongY  -this->HalfSize.getY()+this->HalfVoxelDimensionAlongY, 
  2.*(iz)*this->HalfVoxelDimensionAlongZ  -this->HalfSize.getZ()+this->HalfVoxelDimensionAlongZ);
 Master_Voxels[ix][iy][iz].nEvents=0;
 Master_Voxels[ix][iy][iz].rsd=0.;
  }
  }
  }

// collecting data in each voxel from different threads
int ix,iy,iz;
for(ix=0; ix<NumberOfVoxelsAlongX; ix++){
for(iy=0; iy<NumberOfVoxelsAlongY; iy++){
for(iz=0; iz<NumberOfVoxelsAlongZ; iz++){
Master_Voxels[ix][iy][iz].depEnergy+=this->Voxels[ix][iy][iz].depEnergy;
Master_Voxels[ix][iy][iz].depEnergy2+=this->Voxels[ix][iy][iz].depEnergy2;
Master_Voxels[ix][iy][iz].nEvents+=this->Voxels[ix][iy][iz].nEvents;

}}};
// calculating the relative standard deviation for each voxel
int i,j,k;
for(i=0; i<NumberOfVoxelsAlongX; i++){
for(j=0; j<NumberOfVoxelsAlongY; j++){
for(k=0; k<NumberOfVoxelsAlongZ; k++){

G4double events=Master_Voxels[i][j][k].nEvents;
if(events>1){

  G4double dp =Master_Voxels[i][j][k].depEnergy;
  G4double dp2=Master_Voxels[i][j][k].depEnergy2;
  G4double dpm=dp/events/MeV;
  G4double dp2m=dp2/events/(MeV*MeV);
 
  G4double sigma=sqrt((dp2m-dpm*dpm)/(events-1));

  //
Master_Voxels[i][j][k].rsd=100*sigma/dpm;


  }


}}};


}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void PhantomSD::SaveDataInH5File(){

G4RunManager* runManager = G4RunManager::GetRunManager();
 Total_Events_To_Be_Processed= runManager->GetNumberOfEventsToBeProcessed();
const std::string DatasetName("DosimetricData");
const std::string DatasetName_phantom("PhantomData");
const std::string MEMBER_STD_DEV("_STD_DEV");
const std::string MEMBER_EDEP("_EDEP");
const std::string MEMBER_VOXEL_XID("_VOXEL_XID");
const std::string MEMBER_VOXEL_YID("_VOXEL_YID");
const std::string MEMBER_VOXEL_ZID("_VOXEL_ZID");
const std::string MEMBER_NUMBER_VOXELS_ALONG_X("_NUMBER_VOXELS_ALONG_X");
const std::string MEMBER_NUMBER_VOXELS_ALONG_Y("_NUMBER_VOXELS_ALONG_Y");
const std::string MEMBER_NUMBER_VOXELS_ALONG_Z("_NUMBER_VOXELS_ALONG_Z");
const std::string MEMBER_PHANTOM_SIZE_X("_PHANTOM_SIZE_X");
const std::string MEMBER_PHANTOM_SIZE_Y("_PHANTOM_SIZE_Y");
const std::string MEMBER_PHANTOM_SIZE_Z("_PHANTOM_SIZE_Z");
try{
hsize_t dim[1], dim_phantom[1];
dim_phantom[0]= sizeof(myPhantomData) / sizeof(PhantomData);;
dim[0]        =   this-> NumberOfVoxelsAlongX* this-> NumberOfVoxelsAlongY* this-> NumberOfVoxelsAlongZ;

    // the length of dim
int rank                = sizeof(dim) / sizeof(hsize_t);
int rank_phantom = sizeof(dim_phantom) / sizeof(hsize_t);

    // defining the datatype to pass HDF5
G4ThreadLocal H5::CompType mtype_phantom(sizeof(PhantomData));
G4ThreadLocal H5::CompType mtype(sizeof(DosimetricData));


 mtype_phantom.insertMember(MEMBER_NUMBER_VOXELS_ALONG_X,    HOFFSET(PhantomData, NUMBER_VOXELS_ALONG_X),     H5::PredType::NATIVE_INT   );
 mtype_phantom.insertMember(MEMBER_NUMBER_VOXELS_ALONG_Y,  HOFFSET(PhantomData,NUMBER_VOXELS_ALONG_Y),   H5::PredType::NATIVE_INT );
 mtype_phantom.insertMember(MEMBER_NUMBER_VOXELS_ALONG_Z,   HOFFSET(PhantomData,NUMBER_VOXELS_ALONG_Z),    H5::PredType::NATIVE_INT  );
 mtype_phantom.insertMember(MEMBER_PHANTOM_SIZE_X,   HOFFSET(PhantomData, PHANTOM_SIZE_X),    H5::PredType::NATIVE_FLOAT );
 mtype_phantom.insertMember(MEMBER_PHANTOM_SIZE_Y, HOFFSET(PhantomData, PHANTOM_SIZE_Y),H5::PredType::NATIVE_FLOAT );
 mtype_phantom.insertMember(MEMBER_PHANTOM_SIZE_Z,   HOFFSET(PhantomData, PHANTOM_SIZE_Z),    H5::PredType::NATIVE_FLOAT );


mtype.insertMember(MEMBER_VOXEL_XID,    HOFFSET(DosimetricData, VOXEL_XID),     H5::PredType::NATIVE_INT   );
mtype.insertMember(MEMBER_VOXEL_YID,  HOFFSET(DosimetricData,VOXEL_YID),   H5::PredType::NATIVE_INT );
mtype.insertMember(MEMBER_VOXEL_ZID,   HOFFSET(DosimetricData, VOXEL_ZID),    H5::PredType::NATIVE_INT  );
mtype.insertMember(MEMBER_EDEP,   HOFFSET(DosimetricData, EDEP),    H5::PredType::NATIVE_FLOAT );
mtype.insertMember(MEMBER_STD_DEV , HOFFSET(DosimetricData, STD_DEV),H5::PredType::NATIVE_FLOAT );

auto id_thread = std::to_string(G4Threading::G4GetThreadId()); 
string FILE_NAME = "DData.h5";
G4ThreadLocal  H5::DataSpace space(rank, dim);
G4ThreadLocal  H5::DataSpace space_phantom (rank_phantom, dim_phantom);
G4ThreadLocal H5::H5File *file                 = new H5::H5File(FILE_NAME, H5F_ACC_TRUNC	);
G4ThreadLocal  H5::DataSet *dataset_phantom             = new H5::DataSet(file->createDataSet(DatasetName_phantom, mtype_phantom, space_phantom));
G4ThreadLocal  H5::DataSet *dataset             = new H5::DataSet(file->createDataSet(DatasetName, mtype, space));

int ix,iy,iz;
//myPhantomData = new  PhantomData[1];
myPhantomData[0].NUMBER_VOXELS_ALONG_X= this-> NumberOfVoxelsAlongX;

myPhantomData[0].NUMBER_VOXELS_ALONG_Y= this-> NumberOfVoxelsAlongY;
myPhantomData[0].NUMBER_VOXELS_ALONG_Z= this-> NumberOfVoxelsAlongZ;
myPhantomData[0].PHANTOM_SIZE_X=pDetectorConstruction-> GetPhantomSizeX();
myPhantomData[0].PHANTOM_SIZE_Y=pDetectorConstruction-> GetPhantomSizeY();
myPhantomData[0].PHANTOM_SIZE_Z=pDetectorConstruction-> GetPhantomSizeZ();
dataset_phantom ->write(myPhantomData, mtype_phantom);

myDosimetricData = new DosimetricData[this-> NumberOfVoxelsAlongX* this-> NumberOfVoxelsAlongY* this-> NumberOfVoxelsAlongZ];
for(ix=0; ix<NumberOfVoxelsAlongX; ix++){
for(iy=0; iy<NumberOfVoxelsAlongY; iy++){
for(iz=0; iz<NumberOfVoxelsAlongZ; iz++){
myDosimetricData[INCREMENTOR].VOXEL_XID=ix;
myDosimetricData[INCREMENTOR].VOXEL_YID=iy;
myDosimetricData[INCREMENTOR].VOXEL_ZID=iz;
myDosimetricData[INCREMENTOR].EDEP=Master_Voxels[ix][iy][iz].depEnergy/Total_Events_To_Be_Processed;
myDosimetricData[INCREMENTOR].STD_DEV=Master_Voxels[ix][iy][iz].rsd;
INCREMENTOR++;
}}};


dataset->write(myDosimetricData, mtype);



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
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
