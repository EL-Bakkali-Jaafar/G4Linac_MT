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
 * see http://G4PhspH5.GitHub.com
 *
 * - 23/07/2017: public version 2.0
 *
--------------------------------------------------------------------------------------------
*/

#include "H5Cpp.h"

#include "HistoManager.hh"
#include "G4SystemOfUnits.hh"
#include "H5DataAnalysisHelper.hh"
std::string ANSI_RESET_COLOR = "\033[0m";
std::string ANSI_GREEN = "\033[32m";
int main(int argc,char** argv)
{

G4cout<< argc<<G4endl;
G4String
 param_1 ,
 param_2 ,
 param_3 ,
 param_4 ,
 param_5,
 macrofile
 ;


if (argc== 2){

 param_1 = argv[1];

}
if (argc== 3){

 param_1 = argv[1];
 param_2 = argv[2];
}
if (argc== 4){

 param_1 = argv[1];
 param_2 = argv[2];
 param_3 = argv[3];

}
if (argc== 5){

 param_1 = argv[1];
 param_2 = argv[2];
 param_3 = argv[3];
 param_4 = argv[4];

}
if (argc== 6){

 param_1 = argv[1];
 param_2 = argv[2];
 param_3 = argv[3];
 param_4 = argv[4];
 param_5 = argv[5];
}

G4String DataType = param_1 ;

G4String NameOfFile=param_2;
G4cout<<ANSI_GREEN<<"G4LinacDataAnalysis: Reading "<< DataType<<" file." << ANSI_RESET_COLOR<<G4endl;
G4cout<<ANSI_GREEN<<"G4LinacDataAnalysis: File name "<< NameOfFile<<" ." <<ANSI_RESET_COLOR <<G4endl;
H5DataAnalysisHelper *myH5DataAnalysisHelper = new H5DataAnalysisHelper();


if ( DataType=="DosimeticData")
{//if ( DataType=="DosimeticData")

G4String PhysicalQuantity= param_3;
myH5DataAnalysisHelper->SET_DOSIMETRIC_FILE_NAME(NameOfFile);
myH5DataAnalysisHelper->READ_PHANTOM_DATA();
myH5DataAnalysisHelper->READ_DOSIMETRIC_DATA();

int _number_of_voxels_along_x = myH5DataAnalysisHelper-> GetNumberOfVoxelsAlongX();
int _number_of_voxels_along_y = myH5DataAnalysisHelper-> GetNumberOfVoxelsAlongY();
int _number_of_voxels_along_z = myH5DataAnalysisHelper-> GetNumberOfVoxelsAlongZ();
G4double _Phantom_size_x= myH5DataAnalysisHelper->GetPhantomsizeX();
G4double _Phantom_size_y= myH5DataAnalysisHelper->GetPhantomsizeY();
G4double _Phantom_size_z= myH5DataAnalysisHelper->GetPhantomsizeZ();


double HalfVoxelDimensionAlongX=0.5*(_Phantom_size_x  /_number_of_voxels_along_x );
double HalfVoxelDimensionAlongY=0.5*( _Phantom_size_y /_number_of_voxels_along_y);
double HalfVoxelDimensionAlongZ=0.5*( _Phantom_size_z /_number_of_voxels_along_z);
G4double max_x=   _Phantom_size_x*0.5;
G4double min_x= - _Phantom_size_x*0.5;
G4double max_y=   _Phantom_size_y*0.5;
G4double min_y= - _Phantom_size_y*0.5;
G4double min_z= - _Phantom_size_z*0.5;
G4double max_z=   _Phantom_size_z*0.5;
//G4cout <<max_x<<G4endl;
//G4cout <<min_x<<G4endl;


if (PhysicalQuantity=="xprofile")
{
macrofile="xprofile.C";
HistoManager *fHistoManager = HistoManager::GetInstance();
int ycid = atoi(param_4.c_str() );
int zcid = atoi(param_5.c_str() );
G4double max_edep= myH5DataAnalysisHelper->GetMaxEnergyDepositXProfile(ycid,zcid );
G4double min_edep= myH5DataAnalysisHelper->GetMinEnergyDepositXProfile(ycid,zcid);

if (max_edep==0)
 {

G4cout<<ANSI_GREEN<<"G4LinacDataAnalysis:max_edep must be > 0.0"<<ANSI_RESET_COLOR <<G4endl;
return false;
}

fHistoManager->SetParametersForXprofile( _number_of_voxels_along_x,ycid,  max_edep,  min_edep,  max_x,  min_x);
fHistoManager->Book(); 

for (int i=0; i< _number_of_voxels_along_x ;i++)
{


G4double x=  ( - _number_of_voxels_along_x + 1+ 2*i )*HalfVoxelDimensionAlongX;


G4double edep= myH5DataAnalysisHelper->GetEnergyDeposit(i,ycid, zcid);

fHistoManager->Fill_XPROFILE( x,  edep);


}
fHistoManager->Save();


}

if (PhysicalQuantity=="yprofile")
{
macrofile="yprofile.C";
HistoManager *fHistoManager = HistoManager::GetInstance();
int xcid = atoi(param_4.c_str() );
int zcid = atoi(param_5.c_str() );
G4double max_edep= myH5DataAnalysisHelper->GetMaxEnergyDepositXProfile(xcid,zcid );
G4double min_edep= myH5DataAnalysisHelper->GetMinEnergyDepositXProfile(xcid,zcid);
if (max_edep==0)
 {

G4cout<<ANSI_GREEN<<"G4LinacDataAnalysis:max_edep must be > 0.0"<<ANSI_RESET_COLOR <<G4endl;
return false;
}

//G4cout<<";" << _number_of_voxels_along_y <<";"<<xcid<<";"<< min_y<<";"<< max_y<<G4endl;
fHistoManager->SetParametersForYprofile( _number_of_voxels_along_y,xcid,  max_edep,  min_edep,  max_y,  min_y);
fHistoManager->Book(); 

for (int i=0; i< _number_of_voxels_along_y ;i++)
{


G4double y=  ( - _number_of_voxels_along_y + 1+ 2*i )*HalfVoxelDimensionAlongY;


G4double edep= myH5DataAnalysisHelper->GetEnergyDeposit(xcid,i, zcid);

fHistoManager->Fill_XPROFILE( y,  edep);


}
fHistoManager->Save();


}


if (PhysicalQuantity=="edep_heatmap")

{//if (PhysicalQuantity=="profile")
macrofile="edep_heatmap.C";
int zid = atoi(param_4.c_str() );
G4double max_edep= myH5DataAnalysisHelper->GetMaxEnergyDepositHeatMap(zid );
G4double min_edep= myH5DataAnalysisHelper->GetMinEnergyDepositHeatMap(zid );
if (max_edep==0)
 {

G4cout<<ANSI_GREEN<<"G4LinacDataAnalysis:max_edep must be > 0.0"<<ANSI_RESET_COLOR <<G4endl;
return false;
}

if (zid > _number_of_voxels_along_z-1) {
G4cout<<" ERROR IN ZID "<<zid << " > "<< _number_of_voxels_along_z-1<<G4endl;
return false;
}
G4cout<< ANSI_GREEN<<"G4LinacDataAnalysis:id of voxels along z : " << zid << ANSI_RESET_COLOR<<G4endl;
HistoManager *fHistoManager = HistoManager::GetInstance();
fHistoManager->SetTitle_Edep_2DHeatMap("Edep_2DHeatMap");
fHistoManager->SetParametersForDosimetricData2DheatMap(_number_of_voxels_along_x ,_number_of_voxels_along_y, max_edep, min_edep,  max_x, min_x,  max_y,  min_y);

//G4cout<<" max edep " << max_edep/MeV <<G4endl;
//G4cout<<" min edep " << min_edep/MeV <<G4endl;
fHistoManager->Book(); 
for (int i=0; i< _number_of_voxels_along_x ;i++)
{
for (int j=0; j<_number_of_voxels_along_y; j++)
{
G4double x=  ( - _number_of_voxels_along_x + 1+ 2*i )*HalfVoxelDimensionAlongX;
G4double y=  ( - _number_of_voxels_along_y + 1+ 2*j )*HalfVoxelDimensionAlongY;
G4double zpos=  ( - _number_of_voxels_along_z + 1+ 2*zid )*HalfVoxelDimensionAlongZ;
G4double z= myH5DataAnalysisHelper->GetEnergyDeposit(i,j, zid);

//G4cout<<"  pos z cm : "<< zpos/cm<<G4endl;
fHistoManager->Fill_Edep_2DHeatMap( x,  y, z);

}//for j
}//for i
fHistoManager->Save();
} ////if (PhysicalQuantity=="profile")
else if (PhysicalQuantity=="pdd") 
{
macrofile="pdd.C";
int xid = atoi(param_4.c_str() );
int yid = atoi(param_5.c_str() );
if (xid > _number_of_voxels_along_z-1) {
G4cout<< ANSI_GREEN<<" ERROR IN XID "<<xid << " > "<< _number_of_voxels_along_x-1<<ANSI_RESET_COLOR  <<G4endl;
return false;
}
if (yid > _number_of_voxels_along_y-1) {
G4cout<<ANSI_GREEN<<" ERROR IN YID "<<yid << " > "<< _number_of_voxels_along_y-1<<ANSI_RESET_COLOR  <<G4endl;
return false;
}

G4double max_edep= myH5DataAnalysisHelper->GetMaxEnergyDepositPdd(xid,yid );
G4double min_edep= myH5DataAnalysisHelper->GetMinEnergyDepositPdd(xid, yid );
//G4cout << max_edep<< G4endl;
//G4cout<<min_edep<<G4endl;
if (max_edep==0)
 {

G4cout<<ANSI_GREEN<<"G4LinacDataAnalysis:max_edep must be > 0.0"<<ANSI_RESET_COLOR <<G4endl;
return false;
}



HistoManager *fHistoManager = HistoManager::GetInstance();
fHistoManager->SetTitleEdepDistributionZ("PDD");
//
//G4cout<<_number_of_voxels_along_z <<":::"<< max_edep<<" ::::" << min_edep << ":::"  <<max_z <<":::" <<min_z<<G4endl;
fHistoManager->SetParametersForDosimetricDataPdd(_number_of_voxels_along_z , max_edep, min_edep,max_z,min_z);

fHistoManager->Book();
for (int j=0; j<_number_of_voxels_along_z; j++)

{
G4double z=  ( - _number_of_voxels_along_z + 1+ 2*j )*HalfVoxelDimensionAlongZ;
G4double edep= myH5DataAnalysisHelper->GetEnergyDeposit(xid,yid, j);

//
//G4cout<<"  pos z cm : "<< z/cm<<G4endl;
//G4cout<<" edep : "<< edep/MeV<<G4endl;
fHistoManager->Fill_PDD( z, edep);

}
fHistoManager->Save();

//G4cout<<"Percentage depth dose"<<G4endl;
}



}////if ( DataType=="DosimeticData")

else if ( DataType=="PhaseSpaceData")
{//if ( DataType=="PhaseSpaceData")
//
G4String NameOfFile=param_2;
G4String PhysicalQuantity=param_3;

if (PhysicalQuantity=="gamma_energy_spectrum") {
macrofile="gamma_energy_spectrum.C";
myH5DataAnalysisHelper->SET_PHASE_SPACE_FILE_NAME(NameOfFile);
//
myH5DataAnalysisHelper->READ_BEAM_DATA();
//
myH5DataAnalysisHelper->READ_EVENT_DATA();
//
myH5DataAnalysisHelper->READ_PHASE_SPACE_DATA();

HistoManager *fHistoManager = HistoManager::GetInstance();
int EnergyBins=500;
G4double max_energy=myH5DataAnalysisHelper->GetMaxKineticEnergy();
G4double min_energy=myH5DataAnalysisHelper->GetMinKineticEnergy();

G4cout<<" min_energy " << min_energy<<G4endl;
G4cout<<" max_energy " << max_energy<<G4endl;
if (min_energy == max_energy){
G4cout<<" fatal error : min_energy = max energy " <<G4endl;
return false;
}

fHistoManager->SetParametersForPhaseSpaceDataPhotonsEnergySpectrum("Gamma Energy Spectrum", EnergyBins, max_energy, min_energy);
G4double _energy= 0.0;

for (unsigned i=0; i< myH5DataAnalysisHelper->data_size_PhspData; i++)
{
_energy= myH5DataAnalysisHelper->GetKineticEnergy(i);
//G4cout <<" Kenitic E: " <<_energy<<G4endl;
fHistoManager->FillSpectrum (0, _energy,1);


}

fHistoManager->Save();
}

if (PhysicalQuantity=="spatial_distribution_xy") {


macrofile="spatial_distribution_xy.C";
myH5DataAnalysisHelper->SET_PHASE_SPACE_FILE_NAME(NameOfFile);
//
myH5DataAnalysisHelper->READ_BEAM_DATA();
//
myH5DataAnalysisHelper->READ_EVENT_DATA();
//
myH5DataAnalysisHelper->READ_PHASE_SPACE_DATA();

HistoManager *fHistoManager = HistoManager::GetInstance();
int EnergyBins=500;
G4double max_energy=myH5DataAnalysisHelper->GetMaxKineticEnergy();
G4double min_energy=myH5DataAnalysisHelper->GetMinKineticEnergy();

G4cout<<" min_energy " << min_energy<<G4endl;
G4cout<<" max_energy " << max_energy<<G4endl;
if (min_energy == max_energy){
G4cout<<" fatal error : min_energy = max energy " <<G4endl;
return false;
}

int xbins=100;
int ybins=100;
G4double max_x= myH5DataAnalysisHelper->GetMaxPosX();
G4double max_y= myH5DataAnalysisHelper->GetMaxPosY();
G4double min_x= myH5DataAnalysisHelper->GetMinPosX();
G4double min_y= myH5DataAnalysisHelper->GetMinPosY();
fHistoManager->SetParametersForPhaseSpaceDataSpatialDistXY("Spatial Distribution XY",  xbins, max_x/cm,  min_x/cm, ybins,max_y/cm, min_y/cm );
G4double _energy= 0.0;

for (unsigned i=0; i< myH5DataAnalysisHelper->data_size_PhspData; i++)
{
G4double x_pos = myH5DataAnalysisHelper->GetPosX(i);
G4double y_pos = myH5DataAnalysisHelper->GetPosY(i);
//G4cout <<" Kenitic E: " <<_energy<<G4endl;
fHistoManager->Fill_spatialDistxy(  x_pos, y_pos);


}

fHistoManager->Save();


}
}

G4cout<< "\033[32m"<<"G4LinacDataAnalysis: Now you must run this command : " << "\033[33m"<<"root " <<macrofile<<ANSI_RESET_COLOR <<G4endl;
return 0;

}
