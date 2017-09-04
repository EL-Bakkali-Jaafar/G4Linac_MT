
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
#include "H5Cpp.h"
#include "HistoManager.hh"
#include "G4SystemOfUnits.hh"
#include "H5DataAnalysisHelper.hh"
std::string ANSI_RESET_COLOR = "\033[0m";
std::string ANSI_GREEN = "\033[32m";
int main(int argc,char** argv)
{
/*-------------TERMINAL HEADER-------------------*/
G4cout<< "\033[31m" <<"#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#"<< G4endl;
G4cout<<"G4LINAC_MT version 1.O: a Geant4-based application for Medical Linear Accelerator"<< G4endl;
G4cout<< "Developed by Dr.Jaafar EL Bakkali, Assistant Prof. of Nuclear Physics, Tetouan City,Morocco,  30/08/ 2017 "<< G4endl;
G4cout<<"WebSite: www.g4linac_mt.github.com "<< G4endl;
G4cout<<"#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#"<<  "\033[0m"<< G4endl;
/*-------------TERMINAL HEADER-------------------*/
G4cout<<ANSI_GREEN<<"G4LinacDataAnalysis: a tool for analyzing and histogramming h5PhaseSpace data and dosimetric data." << ANSI_RESET_COLOR<<G4endl;
G4String
 param_1 ,
 param_2 ,
 param_3 ,
 param_4 ,
 param_5,
 macrofile;
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

int _number_of_voxels_along_y,_number_of_voxels_along_x,_number_of_voxels_along_z;
G4double _Phantom_size_x, _Phantom_size_y, _Phantom_size_z;
double HalfVoxelDimensionAlongX,HalfVoxelDimensionAlongY,HalfVoxelDimensionAlongZ;
G4double max_x,min_x;
G4double max_y,min_y;
G4double max_z,min_z;
G4cout<<ANSI_GREEN<<"G4LinacDataAnalysis: Reading "<< DataType<<" file." << ANSI_RESET_COLOR<<G4endl;
G4cout<<ANSI_GREEN<<"G4LinacDataAnalysis: the name of File is: "<< NameOfFile<<" ." <<ANSI_RESET_COLOR <<G4endl;

H5DataAnalysisHelper *myH5DataAnalysisHelper = new H5DataAnalysisHelper();

if ( DataType=="DosimetricData")

{//if ( DataType=="DosimeticData")
G4String PhysicalQuantity= param_3;

myH5DataAnalysisHelper->SET_DOSIMETRIC_FILE_NAME(NameOfFile);
myH5DataAnalysisHelper->READ_DOSIMETRIC_DATA_FROM_BINARY_FILE();
_number_of_voxels_along_x = myH5DataAnalysisHelper-> GetNumberOfVoxelsAlongX();
_number_of_voxels_along_y = myH5DataAnalysisHelper-> GetNumberOfVoxelsAlongY();
_number_of_voxels_along_z = myH5DataAnalysisHelper-> GetNumberOfVoxelsAlongZ();
G4cout <<ANSI_GREEN<<"G4LinacDataAnalysis: Number of voxels along x is " <<_number_of_voxels_along_x <<G4endl;
G4cout <<ANSI_GREEN<<"G4LinacDataAnalysis: Number of voxels along y is " <<_number_of_voxels_along_y <<G4endl;
G4cout <<ANSI_GREEN<<"G4LinacDataAnalysis: Number of voxels along z is " <<_number_of_voxels_along_z <<G4endl;
 _Phantom_size_x= myH5DataAnalysisHelper->GetPhantomsizeX();

_Phantom_size_y= myH5DataAnalysisHelper->GetPhantomsizeY();
_Phantom_size_z= myH5DataAnalysisHelper->GetPhantomsizeZ();

G4cout <<ANSI_GREEN<<"G4LinacDataAnalysis: Phantom size along x is " <<_Phantom_size_x <<G4endl;
G4cout <<ANSI_GREEN<<"G4LinacDataAnalysis: Phantom size along y is " <<myH5DataAnalysisHelper->GetPhantomsizeY() <<G4endl;
G4cout <<ANSI_GREEN<<"G4LinacDataAnalysis: Phantom size along z is " <<_Phantom_size_z <<G4endl;
 max_z=   _Phantom_size_z*0.5;
G4cout <<"max z "<<max_z<<G4endl;
 HalfVoxelDimensionAlongX=0.5*(_Phantom_size_x  /_number_of_voxels_along_x );

 HalfVoxelDimensionAlongY=0.5*( _Phantom_size_y /_number_of_voxels_along_y);
 HalfVoxelDimensionAlongZ=0.5*( _Phantom_size_z /_number_of_voxels_along_z);
 max_x=   _Phantom_size_x*0.5;
 min_x= - _Phantom_size_x*0.5;
 max_y=   _Phantom_size_y*0.5;
 min_y= - _Phantom_size_y*0.5;
 min_z= - _Phantom_size_z*0.5;

//

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
fHistoManager->SetParametersForYprofile( _number_of_voxels_along_y,xcid,  max_edep,  min_edep,  max_y,  min_y);
for (int i=0; i< _number_of_voxels_along_y ;i++)
{
G4double y=  ( - _number_of_voxels_along_y + 1+ 2*i )*HalfVoxelDimensionAlongY;
G4double edep= myH5DataAnalysisHelper->GetEnergyDeposit(xcid,i, zcid);
fHistoManager->Fill_XPROFILE( y,  edep);
}
fHistoManager->Save();
}
if (PhysicalQuantity=="dose_heatmap")
{//if (PhysicalQuantity=="profile")
macrofile="dose_heatmap.C";
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
fHistoManager->SetTitle_Edep_2DHeatMap("Dose_2DHeatMap");
G4cout<< ANSI_GREEN<<"G4LinacDataAnalysis:Max x : " << max_x << ANSI_RESET_COLOR<<G4endl;
fHistoManager->SetParametersForDosimetricData2DheatMap(_number_of_voxels_along_x ,_number_of_voxels_along_y, max_edep, min_edep,  max_x, min_x,  max_y,  min_y);

for (int i=0; i< _number_of_voxels_along_x ;i++)
{
for (int j=0; j<_number_of_voxels_along_y; j++)
{
G4double x=  ( - _number_of_voxels_along_x + 1+ 2*i )*HalfVoxelDimensionAlongX;
G4double y=  ( - _number_of_voxels_along_y + 1+ 2*j )*HalfVoxelDimensionAlongY;
G4double zpos=  ( - _number_of_voxels_along_z + 1+ 2*zid )*HalfVoxelDimensionAlongZ;
G4double z= myH5DataAnalysisHelper->GetEnergyDeposit(i,j, zid);
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
if (xid > _number_of_voxels_along_x-1) {
G4cout<< ANSI_GREEN<<" ERROR IN XID "<<xid << " > "<< _number_of_voxels_along_x-1<<ANSI_RESET_COLOR  <<G4endl;
return false;
}
if (yid > _number_of_voxels_along_y-1) {
G4cout<<ANSI_GREEN<<" ERROR IN YID "<<yid << " > "<< _number_of_voxels_along_y-1<<ANSI_RESET_COLOR  <<G4endl;
return false;
}
G4double max_edep= myH5DataAnalysisHelper->GetMaxEnergyDepositPdd(xid,yid );
G4double min_edep= myH5DataAnalysisHelper->GetMinEnergyDepositPdd(xid, yid );
if (max_edep==0)
{
G4cout<<ANSI_GREEN<<"G4LinacDataAnalysis:max_edep must be > 0.0"<<ANSI_RESET_COLOR <<G4endl;
return false;
}
HistoManager *fHistoManager = HistoManager::GetInstance();
fHistoManager->SetTitleEdepDistributionZ("PDD");
max_z=_Phantom_size_z;
min_z=0;
fHistoManager->SetParametersForDosimetricDataPdd(_number_of_voxels_along_z , max_edep, min_edep,max_z,min_z);
for (int j=0; j<_number_of_voxels_along_z; j++)
{
G4double z=0.5*_Phantom_size_z+ ( - _number_of_voxels_along_z + 1+ 2*j )*HalfVoxelDimensionAlongZ;
G4double edep= myH5DataAnalysisHelper->GetEnergyDeposit(xid,yid, j);
//
fHistoManager->Fill_PDD( z, edep);
}
fHistoManager->Save();
}
}////if ( DataType=="DosimeticData")
else if ( DataType=="PhaseSpaceData")
{//if ( DataType=="PhaseSpaceData")
G4String NameOfFile=param_2;
G4String PhysicalQuantity=param_3;
if (PhysicalQuantity=="photon_energy_spectrum") {
macrofile="photon_energy_spectrum.C";
myH5DataAnalysisHelper->SET_PHASE_SPACE_FILE_NAME(NameOfFile);
myH5DataAnalysisHelper->READ_BEAM_DATA();
myH5DataAnalysisHelper->READ_EVENT_DATA();
myH5DataAnalysisHelper->READ_PHASE_SPACE_DATA();
HistoManager *fHistoManager = HistoManager::GetInstance();
int EnergyBins=500;
int pdge_photon= 22;
G4double max_energy=myH5DataAnalysisHelper->GetMaxKineticEnergy(pdge_photon);
G4double min_energy=myH5DataAnalysisHelper->GetMinKineticEnergy(pdge_photon);
G4cout<<ANSI_GREEN <<" Min_Kinetic_Energy: " << min_energy<<G4endl;
G4cout<< ANSI_GREEN<<" Max_Kinetic_Energy: " << max_energy<<G4endl;
if (min_energy == max_energy){
G4cout<<" fatal error : min_energy = max energy !" <<G4endl;
return false;
}
fHistoManager->SetParametersForPhaseSpaceDataPhotonsEnergySpectrum("Photon Kinetic Energy Spectrum", EnergyBins, max_energy, min_energy);
G4double _photon_kinetic_energy= 0.0;
for (unsigned i=0; i< myH5DataAnalysisHelper->data_size_PhspData; i++)
{
_photon_kinetic_energy= myH5DataAnalysisHelper->GetKineticEnergy(i,pdge_photon);
if ( _photon_kinetic_energy !=0) fHistoManager->FillSpectrum (0,  _photon_kinetic_energy,1);
}
fHistoManager->Save();
}
if (PhysicalQuantity=="spatial_distribution_xy") {
int pdge_all_particles= 0;
macrofile="spatial_distribution_xy.C";
myH5DataAnalysisHelper->SET_PHASE_SPACE_FILE_NAME(NameOfFile);
myH5DataAnalysisHelper->READ_BEAM_DATA();
myH5DataAnalysisHelper->READ_EVENT_DATA();
myH5DataAnalysisHelper->READ_PHASE_SPACE_DATA();
HistoManager *fHistoManager = HistoManager::GetInstance();
int EnergyBins=1000;
G4double max_energy=myH5DataAnalysisHelper->GetMaxKineticEnergy(pdge_all_particles);
G4double min_energy=myH5DataAnalysisHelper->GetMinKineticEnergy(pdge_all_particles);
G4cout<<" Min_Kinetic_Energy: " << min_energy<<G4endl;
G4cout<<" Max_Kinetic_Energy: " << max_energy<<G4endl;
if (min_energy == max_energy){
G4cout<<" fatal error : min_energy = max energy " <<G4endl;
return false;
}
int xbins=1000;
int ybins=1000;
G4double max_x= myH5DataAnalysisHelper->GetMaxPosX(0);
G4double max_y= myH5DataAnalysisHelper->GetMaxPosY(0);
G4double min_x= myH5DataAnalysisHelper->GetMinPosX(0);
G4double min_y= myH5DataAnalysisHelper->GetMinPosY(0);
fHistoManager->SetParametersForPhaseSpaceDataSpatialDistXY("Spatial Distribution XY",  xbins, max_x/cm,  min_x/cm, ybins,max_y/cm, min_y/cm );
G4double _energy= 0.0;
for (unsigned i=0; i< myH5DataAnalysisHelper->data_size_PhspData; i++)
{
G4double x_pos = myH5DataAnalysisHelper->GetPosX(i,0);
G4double y_pos = myH5DataAnalysisHelper->GetPosY(i,0);
fHistoManager->Fill_spatialDistxy(  x_pos, y_pos);
}
fHistoManager->Save();
}
if (PhysicalQuantity=="photon_spatial_distribution_xy_with_kinetic") {
macrofile="photon_spatial_distribution_xy_with_kinetic.C";
myH5DataAnalysisHelper->SET_PHASE_SPACE_FILE_NAME(NameOfFile);
myH5DataAnalysisHelper->READ_BEAM_DATA();
myH5DataAnalysisHelper->READ_EVENT_DATA();
myH5DataAnalysisHelper->READ_PHASE_SPACE_DATA();
HistoManager *fHistoManager = HistoManager::GetInstance();
int xbins=1000;
int ybins=1000;
int pdge_photon= 22;
G4double max_x= myH5DataAnalysisHelper->GetMaxPosX(pdge_photon);
G4double max_y= myH5DataAnalysisHelper->GetMaxPosY(pdge_photon);
G4double min_x= myH5DataAnalysisHelper->GetMinPosX(pdge_photon);
G4double min_y= myH5DataAnalysisHelper->GetMinPosY(pdge_photon);
fHistoManager->SetParametersForPhaseSpaceDataPhotonSpatialDistXY_With_Kinetic("Spatial distribution of photons in function of its kinetic energies",  xbins, max_x,  min_x, ybins,max_y, min_y );
//for (unsigned i=0; i< 10; i++)
//
G4double _energy=0.0;
for (unsigned i=0; i< myH5DataAnalysisHelper->data_size_PhspData; i++)
{
if (myH5DataAnalysisHelper->RAM_PhspData[i].PART_PDGE==22){
 _energy= myH5DataAnalysisHelper->GetKineticEnergy(i,pdge_photon);

//
//G4cout<<_energy<<G4endl;
G4double x_pos = myH5DataAnalysisHelper->GetPosX(i,pdge_photon);
G4double y_pos = myH5DataAnalysisHelper->GetPosY(i,pdge_photon);
fHistoManager->Fill_spatialDistxy_with_kinetic( x_pos, y_pos, _energy);
}
}
fHistoManager->Save();
}


if (PhysicalQuantity=="electron_spatial_distribution_xy_with_kinetic") {
macrofile="electron_spatial_distribution_xy_with_kinetic.C";
myH5DataAnalysisHelper->SET_PHASE_SPACE_FILE_NAME(NameOfFile);
myH5DataAnalysisHelper->READ_BEAM_DATA();
myH5DataAnalysisHelper->READ_EVENT_DATA();
myH5DataAnalysisHelper->READ_PHASE_SPACE_DATA();
HistoManager *fHistoManager = HistoManager::GetInstance();
int xbins=1000;
int ybins=1000;
int pdge_electron= 11;
G4double max_x= myH5DataAnalysisHelper->GetMaxPosX(pdge_electron);
G4double max_y= myH5DataAnalysisHelper->GetMaxPosY(pdge_electron);
G4double min_x= myH5DataAnalysisHelper->GetMinPosX(pdge_electron);
G4double min_y= myH5DataAnalysisHelper->GetMinPosY(pdge_electron);
fHistoManager->SetParametersForPhaseSpaceDataElectronSpatialDistXY_With_Kinetic("Spatial distribution of electrons in function of its kinetic energies",  xbins, max_x,  min_x, ybins,max_y, min_y );
//for (unsigned i=0; i< 10; i++)
//
G4double _energy=0.0;
for (unsigned i=0; i< myH5DataAnalysisHelper->data_size_PhspData; i++)
{
if (myH5DataAnalysisHelper->RAM_PhspData[i].PART_PDGE==11){
 _energy= myH5DataAnalysisHelper->GetKineticEnergy(i,pdge_electron);

//
//G4cout<<_energy<<G4endl;
G4double x_pos = myH5DataAnalysisHelper->GetPosX(i,pdge_electron);
G4double y_pos = myH5DataAnalysisHelper->GetPosY(i,pdge_electron);
fHistoManager->Fill_spatialDistxy_with_kinetic( x_pos, y_pos, _energy);
}
}
fHistoManager->Save();
}
if (PhysicalQuantity=="photon_angular_distribution") {
int pdge_photon=22;
macrofile="photon_angular_distribution.C";
myH5DataAnalysisHelper->SET_PHASE_SPACE_FILE_NAME(NameOfFile);
myH5DataAnalysisHelper->READ_BEAM_DATA();
myH5DataAnalysisHelper->READ_EVENT_DATA();
myH5DataAnalysisHelper->READ_PHASE_SPACE_DATA();
HistoManager *fHistoManager = HistoManager::GetInstance();
G4double max_theta= myH5DataAnalysisHelper->GetMaxTheta(pdge_photon);
G4cout<< ANSI_GREEN<<" max theta: :"<< max_theta/deg<<G4endl;
G4double min_theta= myH5DataAnalysisHelper->GetMinTheta(pdge_photon);
G4cout<< ANSI_GREEN<<" min theta: :"<< min_theta/deg<<G4endl;
int thetaBins=1000;
fHistoManager->SetParametersForPhaseSpaceDataPhotonAngularDistribution(" Photon Angular Distribution", thetaBins, max_theta/deg,  min_theta/deg);
//
for (unsigned i=0; i< myH5DataAnalysisHelper->data_size_PhspData; i++)
//for (unsigned i=0; i< 10; i++)
{
G4double _theta = myH5DataAnalysisHelper->GetTheta(i,pdge_photon);
fHistoManager->FillPhotonAngularDist( 0,_theta,1);
}
fHistoManager->Save();
}

if (PhysicalQuantity=="electron_angular_distribution") {
int pdge_electron=  11;
macrofile="electron_angular_distribution.C";
myH5DataAnalysisHelper->SET_PHASE_SPACE_FILE_NAME(NameOfFile);
myH5DataAnalysisHelper->READ_BEAM_DATA();
myH5DataAnalysisHelper->READ_EVENT_DATA();
myH5DataAnalysisHelper->READ_PHASE_SPACE_DATA();
HistoManager *fHistoManager = HistoManager::GetInstance();
G4double max_theta= myH5DataAnalysisHelper->GetMaxTheta(pdge_electron);
G4cout<<" max theta: :"<< max_theta/deg<<G4endl;
G4double min_theta= myH5DataAnalysisHelper->GetMinTheta(pdge_electron);
G4cout<<" min theta: :"<< min_theta/deg<<G4endl;
int thetaBins=1000;
fHistoManager->SetParametersForPhaseSpaceDataElectronAngularDistribution(" Electron Angular Distribution", thetaBins, max_theta/deg,  min_theta/deg);
//
for (unsigned i=0; i< myH5DataAnalysisHelper->data_size_PhspData; i++)
//for (unsigned i=0; i< 10; i++)
{
G4double _theta = myH5DataAnalysisHelper->GetTheta(i,pdge_electron);
fHistoManager->FillElectronAngularDist( 0,_theta,1);
}
fHistoManager->Save();
}

if (PhysicalQuantity=="electron_energy_spectrum") {
macrofile="electron_energy_spectrum.C";
myH5DataAnalysisHelper->SET_PHASE_SPACE_FILE_NAME(NameOfFile);
myH5DataAnalysisHelper->READ_BEAM_DATA();
myH5DataAnalysisHelper->READ_EVENT_DATA();
myH5DataAnalysisHelper->READ_PHASE_SPACE_DATA();
HistoManager *fHistoManager = HistoManager::GetInstance();
int EnergyBins=500;
int pdge_electron=  11;
G4double max_energy=myH5DataAnalysisHelper->GetMaxKineticEnergy(pdge_electron);
G4double min_energy=myH5DataAnalysisHelper->GetMinKineticEnergy(pdge_electron);
G4cout<<" Min_Kinetic_Energy: " << min_energy<<G4endl;
G4cout<<" Max_Kinetic_Energy: " << max_energy<<G4endl;
if (min_energy == max_energy){
G4cout<<" fatal error : min_energy = max energy !" <<G4endl;
return false;
}
fHistoManager->SetParametersForPhaseSpaceDataElectronEnergySpectrum("Electron Kinetic Energy Spectrum", EnergyBins, max_energy, min_energy);
G4double _electron_kinetic_energy= 0.0;
for (unsigned i=0; i< myH5DataAnalysisHelper->data_size_PhspData; i++)
{
_electron_kinetic_energy= myH5DataAnalysisHelper->GetKineticEnergy(i,pdge_electron);
//G4cout<<_electron_kinetic_energy<<G4endl;
if ( _electron_kinetic_energy !=0){ fHistoManager->FillSpectrum (0,  _electron_kinetic_energy,1);}

}
fHistoManager->Save();
}



}
G4cout<< "\033[32m"<<"G4LinacDataAnalysis: Now you must run this command : " << "\033[33m"<<"root " <<macrofile<<ANSI_RESET_COLOR <<G4endl;
return 0;
}
