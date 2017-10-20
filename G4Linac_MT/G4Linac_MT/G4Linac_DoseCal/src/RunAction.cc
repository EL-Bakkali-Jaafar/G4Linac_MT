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
#include <ctime>
#include "G4Threading.hh"
#include <fstream>
#include <iostream>
#include "G4ios.hh"
#include <stdio.h>
#include <math.h>
#include "G4RunManager.hh"
#include <ctime>
#include  "DetectorConstruction.hh"
using namespace std;
int last_idem=0;
int data_size=0;
int n=0;
std::string vrt=" none";
double ACTIVE_EVENTS_TO_TOTAL_HISTORIES_RATIO;
std::string  TERMINAL_HEADER =

"#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#\nG4LINAC_MT version 1.O: a Geant4-based application for Medical Linear Accelerator\nDeveloped by Dr.Jaafar EL Bakkali, Assistant Prof. of Nuclear Physics,\nRabat, Morocco,  10/09/ 2017\nWebpage :https://github.com/EL-Bakkali-Jaafar/G4Linac_MT\n#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#\n";

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
 double  RunAction::diffclock(clock_t clock1,clock_t clock2)
{
	double diffticks=clock1-clock2;
	double diffms=(diffticks*1000)/CLOCKS_PER_SEC;
	return diffms;
}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
RunAction::RunAction()
{
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void RunAction::SETUP_DOSIMETRIC_DATA_FROM_BINARY_FILE(std::string _DosimetricDataFileName){


std::fstream binary_file(_DosimetricDataFileName,std::ios::binary|std::ios::in| std::ios::ate );
int size = binary_file.tellg();
 data_size= size/sizeof(DosCalData);
this->RAM_DosimetricData = new DosCalData[data_size];
for(int i = 0; i<data_size; i++)
{ 


this->RAM_DosimetricData[i].VOXEL_ZID              = 0.0;
this->RAM_DosimetricData[i].VOXEL_YID              = 0.0;
this->RAM_DosimetricData[i].VOXEL_XID              = 0.0;
this->RAM_DosimetricData[i].RSD                    = 0.0;
this->RAM_DosimetricData[i].DOSE2                  = 0.0;
this->RAM_DosimetricData[i].DOSE                   = 0.0;
this->RAM_DosimetricData[i].NEVENTS                = 0.0;
this->RAM_DosimetricData[i].NUMBER_VOXELS_ALONG_X  = 0.0;
this->RAM_DosimetricData[i].NUMBER_VOXELS_ALONG_Y  = 0.0;
this->RAM_DosimetricData[i].NUMBER_VOXELS_ALONG_Z  = 0.0;
this->RAM_DosimetricData[i].PHANTOM_SIZE_X         = 0.0;
this->RAM_DosimetricData[i].PHANTOM_SIZE_Y         = 0.0;
this->RAM_DosimetricData[i].PHANTOM_SIZE_Z         = 0.0;
}
}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void RunAction::WRITE_MERGED_DOSIMETRIC_TXT(){
time_t theTime= time(NULL);
struct std::tm* aTime = localtime(&theTime);
int _NumberOfRunningWorkerThreads=G4Threading::GetNumberOfRunningWorkerThreads();
G4RunManager* runManager                    =   G4RunManager::GetRunManager();
int Total_Events_To_Be_Processed            = runManager->GetNumberOfEventsToBeProcessed();
DetectorConstruction *pDetectorConstruction = (DetectorConstruction*)(runManager->GetUserDetectorConstruction()); 
TextFile.open("dose.txt", std::ios::out);
TextFile<< TERMINAL_HEADER <<G4endl;
TextFile<<"@DATE OF FILE CREATION: "<<asctime(aTime)<<"@TOTAL NUMBER OF SIMULATED EVENTS: "<<Total_Events_To_Be_Processed<<"\n";
TextFile<<"@THREAD NUMBERS: "<<_NumberOfRunningWorkerThreads<<"\n";
TextFile<<"@REDUCTION VARIANCE TECHNIQUE:"<< vrt<<"\n"; 
if (vrt!="none"){
TextFile<<"@SPLITTING/RECYCLING FACTOR:"<< pDetectorConstruction->Nsplit<<"\n"; 
}
TextFile<<"@NUMBER_VOXELS_ALONG_X: "<<this->RAM_DosimetricData[0].NUMBER_VOXELS_ALONG_X<<"\n";
TextFile<<"@NUMBER_VOXELS_ALONG_Y: "<<this->RAM_DosimetricData[0].NUMBER_VOXELS_ALONG_Y<<"\n";
TextFile<<"@NUMBER_VOXELS_ALONG_Z: "<<this->RAM_DosimetricData[0].NUMBER_VOXELS_ALONG_Z<<"\n";
TextFile<<"@PHANTOM_SIZE_X: "<< this->RAM_DosimetricData[0].PHANTOM_SIZE_X<<" cm\n";
TextFile<<"@PHANTOM_SIZE_Y: "<< this->RAM_DosimetricData[0].PHANTOM_SIZE_Y<<" cm\n";
TextFile<<"@PHANTOM_SIZE_Z: "<<this->RAM_DosimetricData[0].PHANTOM_SIZE_Z<<" cm\n";
TextFile<<"@VOXEL_SIZE_X: "<<this->RAM_DosimetricData[0].PHANTOM_SIZE_X/(double)this->RAM_DosimetricData[0].NUMBER_VOXELS_ALONG_X<<" cm\n";
TextFile<<"@VOXEL_SIZE_Y: "<<this->RAM_DosimetricData[0].PHANTOM_SIZE_Y/(double)this->RAM_DosimetricData[0].NUMBER_VOXELS_ALONG_Y<<" cm\n";
TextFile<<"@VOXEL_SIZE_Z: "<<this->RAM_DosimetricData[0].PHANTOM_SIZE_Z/(double)this->RAM_DosimetricData[0].NUMBER_VOXELS_ALONG_Z<<" cm\n";
TextFile<<"@VOXEL_VOLUME: "<<(this->RAM_DosimetricData[0].PHANTOM_SIZE_Z/(double)this->RAM_DosimetricData[0].NUMBER_VOXELS_ALONG_Z) * (this->RAM_DosimetricData[0].PHANTOM_SIZE_Y/(double)this->RAM_DosimetricData[0].NUMBER_VOXELS_ALONG_Y)*
(this->RAM_DosimetricData[0].PHANTOM_SIZE_Z/(double)this->RAM_DosimetricData[0].NUMBER_VOXELS_ALONG_Z)<<" cm_3\n";

double cpu_time = (double(diffclock(end,begin)/1000)/(double) _NumberOfRunningWorkerThreads);
G4cout<<"G4LINAC_DOSECAL-> ELAPSED TIME IN SECONDS IS "<<(double(diffclock(end,begin)/1000)/(double) _NumberOfRunningWorkerThreads)<<G4endl;
double rsd_mean=0.0;
double rsd_max=0.0;
double alpha=0;
double beta=0;
double lambda=0;
for(int i = 0; i<data_size; i++)
{ 
if (this->RAM_DosimetricData[i].RSD>0)
{
if ( this->RAM_DosimetricData[i].RSD > rsd_max){
rsd_max=this->RAM_DosimetricData[i].RSD;
}
rsd_mean += this->RAM_DosimetricData[i].RSD;
n++;
}

};
rsd_mean/=(n);

TextFile<<"@GLOBAL_RSD (%): "<<rsd_mean<<"\n";
TextFile<<"@DOSE UNIT IS: (MEV/GRAMME/NUMBER_OF_SIMULATED_EVENTS)\n";
TextFile <<"@ACTIVE EVENTS TO TOTAL HISTORIES IN H5_PHASE_SPACE RATIO: "<<ACTIVE_EVENTS_TO_TOTAL_HISTORIES_RATIO<<G4endl; 
TextFile<<"@ELAPSED TIME IN SECONDS: "<< cpu_time<<G4endl;
alpha=sqrt(cpu_time)*rsd_mean;
beta=sqrt(cpu_time)*rsd_max;
lambda= sqrt(Total_Events_To_Be_Processed)*rsd_mean;
TextFile<<"@ESTIMATED CPU TIME FOR ACHIEVING GLOBAL_RSD ~1%: [ "<<  alpha*alpha<< " SECONDS <=> " << alpha*alpha/3600 << " HOURS ]."<<G4endl;
TextFile<<"@ESTIMATED NUMBER OF REQUIRED EVENTS FOR ACHIEVING GLOBAL_RSD ~1%:  "<< int( lambda*lambda)<< " PARTICLES."<<G4endl;
TextFile<<"@ESTIMATED CPU TIME FOR ACHIEVING MAX_RSD ~1%: [ "<<  beta*beta<< " SECONDS <=> " << beta*beta/3600 << " HOURS ]."<<G4endl;
TextFile <<"---------------------------------------------------------------------------------------- "<<G4endl; 
TextFile<<setw(0)<<"Voxel_X_ID"<<setw(15)<< "Voxel_Y_ID"<< setw(15) << "Voxel_Z_ID"<<setw(15)<<"DOSE" << setw(17)<<"RSD(%)" <<setw(20)<< "NEVENTS_IN_VOXEL"<<"\n";

for(int i = 0; i<data_size; i++)
{ 
TextFile<<setw(5)<<this->RAM_DosimetricData[i].VOXEL_XID<<setw(15)<< this->RAM_DosimetricData[i].VOXEL_YID<< setw(15) <<this->RAM_DosimetricData[i].VOXEL_ZID<<setw(23) <<this->RAM_DosimetricData[i].DOSE<<setw(13) <<this->RAM_DosimetricData[i].RSD<<setw(14) <<this->RAM_DosimetricData[i].NEVENTS<<"\n";
}
TextFile.close();
}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
 void RunAction::READ_DOSIMETRIC_DATA_FROM_BINARY_FILE(std::string _DosimetricDataFileName, int order){
// Read data
std::fstream binary_file(_DosimetricDataFileName,std::ios::binary|std::ios::in| std::ios::ate );
int size = binary_file.tellg();
DosCalData _DosCalData;
for(int i = 0; i<size/sizeof(DosCalData); i++)
{ 
binary_file.seekg(i*sizeof(DosCalData));
binary_file.read(reinterpret_cast<char *>(&_DosCalData),sizeof(DosCalData));
this->RAM_DosimetricData[i].VOXEL_ZID              = _DosCalData.VOXEL_ZID;
this->RAM_DosimetricData[i].VOXEL_YID              = _DosCalData.VOXEL_YID;
this->RAM_DosimetricData[i].VOXEL_XID              = _DosCalData.VOXEL_XID;
this->RAM_DosimetricData[i].RSD                   += _DosCalData.RSD;
this->RAM_DosimetricData[i].DOSE2                 += _DosCalData.DOSE2;
this->RAM_DosimetricData[i].DOSE                  += _DosCalData.DOSE;
this->RAM_DosimetricData[i].NEVENTS               += _DosCalData.NEVENTS;
this->RAM_DosimetricData[i].NUMBER_VOXELS_ALONG_X  = _DosCalData.NUMBER_VOXELS_ALONG_X;
this->RAM_DosimetricData[i].NUMBER_VOXELS_ALONG_Y  = _DosCalData.NUMBER_VOXELS_ALONG_Y;
this->RAM_DosimetricData[i].NUMBER_VOXELS_ALONG_Z  = _DosCalData.NUMBER_VOXELS_ALONG_Z;
this->RAM_DosimetricData[i].PHANTOM_SIZE_X         = _DosCalData.PHANTOM_SIZE_X;
this->RAM_DosimetricData[i].PHANTOM_SIZE_Y         = _DosCalData.PHANTOM_SIZE_Y;
this->RAM_DosimetricData[i].PHANTOM_SIZE_Z         = _DosCalData.PHANTOM_SIZE_Z;
//

}
binary_file.close();
std::remove(_DosimetricDataFileName.c_str());
if (order==last_idem) {
int total_item                              =   size/sizeof(DosCalData);
G4RunManager* runManager                    =   G4RunManager::GetRunManager();
DetectorConstruction *pDetectorConstruction = (DetectorConstruction*)(runManager->GetUserDetectorConstruction()); 
int Total_Events_To_Be_Processed            = runManager->GetNumberOfEventsToBeProcessed();
ACTIVE_EVENTS_TO_TOTAL_HISTORIES_RATIO=
 pDetectorConstruction->NUMBER_OF_ACTIVE_EVENTS/(double)pDetectorConstruction->myBeamData[0].NUMBER_OF_HISORIES;
if (pDetectorConstruction->GeneratorFlag==2) { vrt=" PARTICLE ROTATIONAL SPLITTING ";}
if (pDetectorConstruction->GeneratorFlag==2){
vrt=" PARTICLE RECYCLING ";
Total_Events_To_Be_Processed                = Total_Events_To_Be_Processed*pDetectorConstruction->Nsplit;
}
for(int i = 0; i<data_size; i++)
    { 

this->RAM_DosimetricData[i].DOSE2             = (double)  this->RAM_DosimetricData[i].DOSE2;

if (this->RAM_DosimetricData[i].NEVENTS > 1){
G4double absorbed_dose_mean                   = this->RAM_DosimetricData[i].DOSE/this->RAM_DosimetricData[i].NEVENTS;
G4double absorbed_dose2_mean                  = this->RAM_DosimetricData[i].DOSE2/this->RAM_DosimetricData[i].NEVENTS;
G4double sigma                                = sqrt((absorbed_dose2_mean-absorbed_dose_mean*absorbed_dose_mean)/(this->RAM_DosimetricData[i].NEVENTS-1));
this->RAM_DosimetricData[i].RSD              = 100*sigma/absorbed_dose_mean;
}
this->RAM_DosimetricData[i].DOSE             = ACTIVE_EVENTS_TO_TOTAL_HISTORIES_RATIO* this->RAM_DosimetricData[i].DOSE/(double) Total_Events_To_Be_Processed;
}
fstream fs;
fs.open("dose.dat", ios::out | ios::binary );
 
 for(int i = 0; i<total_item; i++)
{
fs.write(reinterpret_cast<char *>(&this->RAM_DosimetricData[i]),sizeof(DosCalData));
}
fs.close();

}

}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
RunAction::~RunAction()
{
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void RunAction::BeginOfRunAction(const G4Run* )
{
G4cout<< TERMINAL_HEADER <<G4endl;

 begin=clock();
}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void RunAction::EndOfRunAction(const G4Run*)
{
end=clock();
int _NumberOfRunningWorkerThreads=G4Threading::GetNumberOfRunningWorkerThreads();
SETUP_DOSIMETRIC_DATA_FROM_BINARY_FILE(std::to_string(0)+"dose.dat");
last_idem=_NumberOfRunningWorkerThreads-1;
for (int i=0;i<_NumberOfRunningWorkerThreads;i++) {
READ_DOSIMETRIC_DATA_FROM_BINARY_FILE(std::to_string(i)+"dose.dat",i);
}
WRITE_MERGED_DOSIMETRIC_TXT();

}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
