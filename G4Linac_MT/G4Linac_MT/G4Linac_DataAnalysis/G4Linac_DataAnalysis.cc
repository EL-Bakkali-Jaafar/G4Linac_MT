
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
 
  5/10/2017: public version 1.0
 
#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
#include "H5Cpp.h"
#include "HistoManager.hh"
#include "G4SystemOfUnits.hh"
#include "H5DataAnalysisHelper.hh"
#include <stdio.h>
#include <stdlib.h>

std::string TERMINAL_HEADER =
"#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#\nG4LINAC_MT version 1.O: a Geant4-based application for LINAC\nDeveloped by Dr.Jaafar EL Bakkali, Assistant Prof. of Nuclear Physics,\nERSSSM, Rabat, Morocco,  05/10/ 2017\nWebpage :https://github.com/EL-Bakkali-Jaafar/G4Linac_MT\n#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#\n";

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=##=#=#=#=#=#*/
void PrintMessage(std::string _message){
G4cout<<_message<<G4endl;
}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=##=#=#=#=#=#*/
int main(int argc,char** argv)
{
/*-------------TERMINAL HEADER-------------------*/

PrintMessage(TERMINAL_HEADER);

/*-------------TERMINAL HEADER-------------------*/

PrintMessage("G4LINAC_DATA_ANALYSIS->  A TOOL FOR  DATA ANALYZING AND HISTOGRAMMING." );
G4String
arguments,
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
arguments="";
 int _number_of_voxels_along_y,_number_of_voxels_along_x,_number_of_voxels_along_z;
G4double _Phantom_size_x, _Phantom_size_y, _Phantom_size_z;
double HalfVoxelDimensionAlongX,HalfVoxelDimensionAlongY,HalfVoxelDimensionAlongZ;
G4double max_x,min_x;
G4double max_y,min_y;
G4double max_z,min_z;

PrintMessage("G4LINAC_DATA_ANALYSIS->  READING "+ DataType+" FILE." );
PrintMessage("G4LINAC_DATA_ANALYSIS-> FILE NAME IS: "+ NameOfFile+" ." );

H5DataAnalysisHelper *myH5DataAnalysisHelper = new H5DataAnalysisHelper();



/*--------------------------- DosimetricData----------------------*/

if ( DataType=="DosimetricData")

{//if ( DataType=="DosimeticData")
G4String PhysicalQuantity= param_3;

myH5DataAnalysisHelper->SET_DOSIMETRIC_FILE_NAME(NameOfFile);
myH5DataAnalysisHelper->READ_DOSIMETRIC_DATA_FROM_BINARY_FILE();
_number_of_voxels_along_x = myH5DataAnalysisHelper-> GetNumberOfVoxelsAlongX();
_number_of_voxels_along_y = myH5DataAnalysisHelper-> GetNumberOfVoxelsAlongY();
_number_of_voxels_along_z = myH5DataAnalysisHelper-> GetNumberOfVoxelsAlongZ();

PrintMessage("G4LINAC_DATA_ANALYSIS-> NUMBER OF VOXELS ALONG X AXIS IS: " +std::to_string(_number_of_voxels_along_x)  );
PrintMessage("G4LINAC_DATA_ANALYSIS-> NUMBER OF VOXELS ALONG Y AXIS IS: " +std::to_string(_number_of_voxels_along_y ));
PrintMessage("G4LINAC_DATA_ANALYSIS-> NUMBER OF VOXELS ALONG Z AXIS IS: " +std::to_string(_number_of_voxels_along_z) );



_Phantom_size_x= myH5DataAnalysisHelper->GetPhantomsizeX();
_Phantom_size_y= myH5DataAnalysisHelper->GetPhantomsizeY();
_Phantom_size_z= myH5DataAnalysisHelper->GetPhantomsizeZ();


PrintMessage("G4LINAC_DATA_ANALYSIS-> PHAMTOM SIZE ALONG X AXIS IS: " +std::to_string(_Phantom_size_x  ));
PrintMessage("G4LINAC_DATA_ANALYSIS-> PHAMTOM SIZE ALONG Y AXIS IS: " +std::to_string(myH5DataAnalysisHelper->GetPhantomsizeY()) );
PrintMessage("G4LINAC_DATA_ANALYSIS-> PHAMTOM SIZE ALONG Z AXIS IS: " +std::to_string(_Phantom_size_z  ));

max_z=   _Phantom_size_z*0.5;

PrintMessage("G4LINAC_DATA_ANALYSIS-> MAX Z VALUE: "+std::to_string(max_z)  ); 
 
 HalfVoxelDimensionAlongX=0.5*(_Phantom_size_x  /_number_of_voxels_along_x );
 HalfVoxelDimensionAlongY=0.5*( _Phantom_size_y /_number_of_voxels_along_y);
 HalfVoxelDimensionAlongZ=0.5*( _Phantom_size_z /_number_of_voxels_along_z);
 max_x=   _Phantom_size_x*0.5;
 min_x= - _Phantom_size_x*0.5;
 max_y=   _Phantom_size_y*0.5;
 min_y= - _Phantom_size_y*0.5;
 min_z= - _Phantom_size_z*0.5;

//

/*---------------------------Cross-plane_Dose_Profile_Rsd----------------------*/

if (PhysicalQuantity=="Cross-plane_Dose_Profile_Rsd")
{
macrofile="Cross-plane_Dose_Profile_Rsd.C";
HistoManager *fHistoManager = HistoManager::GetInstance();
 int ycid = atoi(param_4.c_str() );
 int zcid = atoi(param_5.c_str() );
G4double max_rsd= myH5DataAnalysisHelper->GetMaxRSDXProfile(ycid,zcid );
G4double min_rsd= myH5DataAnalysisHelper->GetMinRSDXProfile(ycid,zcid);

if (max_rsd==0)
 {
PrintMessage("G4LINAC_DATA_ANALYSIS-> MAX RSD VALUE MUST BE > 0.0");
return false;
}

fHistoManager->SetParametersForXprofile( _number_of_voxels_along_x,ycid,  max_rsd,  min_rsd,  max_x,  min_x);
for (  int i=0; i< _number_of_voxels_along_x ;i++)
{
G4double x=HalfVoxelDimensionAlongX+  ( - _number_of_voxels_along_x + 1+ 2*i )*HalfVoxelDimensionAlongX;
G4double rsd= myH5DataAnalysisHelper->GetRSD_DOSE(i,ycid, zcid);
fHistoManager->Fill_XPROFILE( x,  rsd);
}
fHistoManager->Save();
}

/*---------------------------Cross-plane_Dose_Profile----------------------*/
if (PhysicalQuantity=="Cross-plane_Dose_Profile")
{
macrofile="Cross-plane_Dose_Profile.C";
HistoManager *fHistoManager = HistoManager::GetInstance();
 int ycid = atoi(param_4.c_str() );
 int zcid = atoi(param_5.c_str() );
G4double max_dose= myH5DataAnalysisHelper->GetMaxDoseXProfile(ycid,zcid );
G4double min_dose= myH5DataAnalysisHelper->GetMinDoseXProfile(ycid,zcid);

if (max_dose==0)
 {
PrintMessage("G4LINAC_DATA_ANALYSIS-> MAX DOSE VALUE MUST BE > 0.0");
return false;
}

fHistoManager->SetParametersForXprofile( _number_of_voxels_along_x,ycid,  max_dose,  min_dose,  max_x,  min_x);
for (  int i=0; i< _number_of_voxels_along_x ;i++)
{
G4double x=HalfVoxelDimensionAlongX+  ( - _number_of_voxels_along_x + 1+ 2*i )*HalfVoxelDimensionAlongX;
G4double dose= myH5DataAnalysisHelper->Get_DOSE(i,ycid, zcid);
fHistoManager->Fill_XPROFILE( x,  dose);
}
fHistoManager->Save();
}
/*---------------------------In-plane_Dose_Profile_Rsd----------------------*/
if (PhysicalQuantity=="In-plane_Dose_Profile_Rsd")
{
macrofile="In-plane_Dose_Profile_Rsd.C";
HistoManager *fHistoManager = HistoManager::GetInstance();
 int xcid = atoi(param_4.c_str() );
 int zcid = atoi(param_5.c_str() );

G4double max_rsd= myH5DataAnalysisHelper->GetMaxRSDYProfile(xcid,zcid );
G4double min_rsd= myH5DataAnalysisHelper->GetMinRSDYProfile(xcid,zcid);
if (max_rsd==0)
 {
PrintMessage("G4LINAC_DATA_ANALYSIS-> MAX RSD VALUE MUST BE > 0.0");
return false;
}
fHistoManager->SetParametersForYprofile( _number_of_voxels_along_y,xcid,  max_rsd,  min_rsd,  max_y,  min_y);
for (  int i=0; i< _number_of_voxels_along_y ;i++)
{
G4double y=HalfVoxelDimensionAlongY+  ( - _number_of_voxels_along_y + 1+ 2*i )*HalfVoxelDimensionAlongY;
G4double rsd= myH5DataAnalysisHelper->GetRSD_DOSE(xcid,i, zcid);

fHistoManager->Fill_XPROFILE( y,  rsd);
}
fHistoManager->Save();
}


/*---------------------------In-plane_Dose_Profile----------------------*/
if (PhysicalQuantity=="In-plane_Dose_Profile")
{
macrofile="In-plane_Dose_Profile.C";
HistoManager *fHistoManager = HistoManager::GetInstance();
 int xcid = atoi(param_4.c_str() );
 int zcid = atoi(param_5.c_str() );
G4double max_dose= myH5DataAnalysisHelper->GetMaxDoseYProfile(xcid,zcid );
G4double min_dose= myH5DataAnalysisHelper->GetMinDoseYProfile(xcid,zcid);
if (max_dose==0)
 {
PrintMessage("G4LINAC_DATA_ANALYSIS-> MAX DOSE VALUE MUST BE > 0.0");
return false;
}
fHistoManager->SetParametersForYprofile( _number_of_voxels_along_y,xcid,  max_dose,  min_dose,  max_y,  min_y);
for (  int i=0; i< _number_of_voxels_along_y ;i++)
{
G4double y=HalfVoxelDimensionAlongY+  ( - _number_of_voxels_along_y + 1+ 2*i )*HalfVoxelDimensionAlongY;
G4double dose= myH5DataAnalysisHelper->Get_DOSE(xcid,i, zcid);

fHistoManager->Fill_XPROFILE( y,  dose);
}
fHistoManager->Save();
}


/*---------------------------dose_heatmap----------------------*/
if (PhysicalQuantity=="2D_Dose_HeatMap")
{//if (PhysicalQuantity=="profile")

 std::string axis_name = param_4.c_str() ;
if (axis_name=="x"){
macrofile="2D_Dose_HeatMap_X.C";

int xid= atoi(param_5.c_str() );
G4double max_dose= myH5DataAnalysisHelper->GetMaxDoseHeatMap(xid, axis_name);
G4double min_dose= myH5DataAnalysisHelper->GetMinDoseHeatMap(xid, axis_name);
//if (max_dose==0)
 //{
//PrintMessage("G4LINAC_DATA_ANALYSIS-> MAX DOSE VALUE MUST BE > 0.0");
//return false;
//}
if (xid > _number_of_voxels_along_x-1) {
PrintMessage("G4LINAC_DATA_ANALYSIS->  ERROR IN XID "+std::to_string(xid) + " > "+std::to_string( _number_of_voxels_along_x-1));
return false;
}
PrintMessage("G4LINAC_DATA_ANALYSIS-> X ID OF CURRENT VOXEL IS: " +std::to_string( xid ));
HistoManager *fHistoManager = HistoManager::GetInstance();
fHistoManager->SetTitle_Edep_2DHeatMap("Dose HeatMap along X axis");
max_z=_Phantom_size_z;
min_z=0;

fHistoManager->SetParametersForDosimetricData2DheatMap(_number_of_voxels_along_y,_number_of_voxels_along_z, max_dose, min_dose, max_y,  min_y, max_z, min_z );
for (  int j=0; j<_number_of_voxels_along_z; j++)
{
for (  int i=0; i< _number_of_voxels_along_y ;i++)
{

float y= HalfVoxelDimensionAlongY+( - _number_of_voxels_along_y + 2*i )*HalfVoxelDimensionAlongY;
float z=0.5*_Phantom_size_z+ ( - _number_of_voxels_along_z+1+ 2*j )*HalfVoxelDimensionAlongZ;
G4cout<<y<<G4endl;
double dose_in= myH5DataAnalysisHelper->Get_DOSE(xid,i, j);
//
//
fHistoManager->Fill_Dose_2DHeatMap( y,  z, dose_in);
}//for j
}//for i
fHistoManager->Save();
}

if (axis_name=="y"){
macrofile="2D_Dose_HeatMap_Y.C";
int yid= atoi(param_5.c_str() );
G4double max_dose= myH5DataAnalysisHelper->GetMaxDoseHeatMap(yid, axis_name);
G4double min_dose= myH5DataAnalysisHelper->GetMinDoseHeatMap(yid, axis_name );
/*
if (max_dose==0)
 {
PrintMessage("G4LINAC_DATA_ANALYSIS-> MAX DOSE MUST BE > 0.0");
return false;
}
*/
if (yid > _number_of_voxels_along_y-1) {
PrintMessage("G4LINAC_DATA_ANALYSIS-> ERROR IN YID "+std::to_string(yid) +" > "+ std::to_string(_number_of_voxels_along_y-1));
return false;
}
PrintMessage("G4LINAC_DATA_ANALYSIS-> YID OF VOXEL : " + std::to_string(yid) );
HistoManager *fHistoManager = HistoManager::GetInstance();
fHistoManager->SetTitle_Edep_2DHeatMap("DoseDHeatMap");
PrintMessage("G4LINAC_DATA_ANALYSIS > MAX X VALUE : " +std::to_string( max_x) );
max_z=_Phantom_size_z;
min_z=0;
fHistoManager->SetParametersForDosimetricData2DheatMap(_number_of_voxels_along_z ,_number_of_voxels_along_x, max_dose, min_dose, max_z,  min_z ,max_x, min_x );

for (  int i=0; i< _number_of_voxels_along_x ;i++)
{
for (  int j=0; j<_number_of_voxels_along_z; j++)
{
float x= HalfVoxelDimensionAlongX+ ( - _number_of_voxels_along_x + 2*i )*HalfVoxelDimensionAlongX;
float z=0.5*_Phantom_size_z+ ( - _number_of_voxels_along_z + 1+ 2*j )*HalfVoxelDimensionAlongZ;
float dose= myH5DataAnalysisHelper->Get_DOSE(i,yid, j);

//

fHistoManager->Fill_Dose_2DHeatMap( z,  x, dose);
}//for j
}//for i
fHistoManager->Save();
}

if (axis_name=="z"){
macrofile="2D_Dose_HeatMap_Z.C";
int zid= atoi(param_5.c_str() );
G4double max_dose=myH5DataAnalysisHelper->GetMaxDoseHeatMap(zid, axis_name);
G4double min_dose= myH5DataAnalysisHelper->GetMinDoseHeatMap(zid, axis_name );

/*
if (max_dose==0)
 {

PrintMessage("G4LINAC_DATA_ANALYSIS-> MAX DOSE MUST BE > 0.0");
return false;
}
*/
if (zid > _number_of_voxels_along_z-1) {
PrintMessage("G4LINAC_DATA_ANALYSIS-> ERROR IN ZID "+std::to_string(zid) + " > "+std::to_string(_number_of_voxels_along_z-1));
return false;
}
PrintMessage("G4LINAC_DATA_ANALYSIS-> Z ID OF VOXEL : " +std::to_string( zid) );
HistoManager *fHistoManager = HistoManager::GetInstance();
fHistoManager->SetTitle_Edep_2DHeatMap("Dose_2DHeatMap");
PrintMessage("G4LINAC_DATA_ANALYSIS-> MAX X VALUE : " + std::to_string(max_x ));
fHistoManager->SetParametersForDosimetricData2DheatMap(_number_of_voxels_along_x ,_number_of_voxels_along_y, max_dose, min_dose,  max_x, min_x,  max_y,  min_y);

for (  int i=0; i< _number_of_voxels_along_x ;i++)
{
for (  int j=0; j<_number_of_voxels_along_y; j++)
{
float x= HalfVoxelDimensionAlongX+ ( - _number_of_voxels_along_x + 2*i )*HalfVoxelDimensionAlongX;
float y=  HalfVoxelDimensionAlongY+ ( - _number_of_voxels_along_y + 2*j )*HalfVoxelDimensionAlongY;
G4cout<<x<<G4endl;
float z=
 myH5DataAnalysisHelper->Get_DOSE(i,j, zid);
//

fHistoManager->Fill_Dose_2DHeatMap( x,  y, z);
}//for j
}//for i
fHistoManager->Save();

}
 
} ////if (PhysicalQuantity=="dose_heatmap")


/*---------------------------Percentage_Depth_Dose_Curve_Rsd----------------------*/
else if (PhysicalQuantity=="Percentage_Depth_Dose_Curve_Rsd") 
{
macrofile="Percentage_Depth_Dose_Curve_Rsd.C";
 int xid = atoi(param_4.c_str() );
 int yid = atoi(param_5.c_str() );
if (xid > _number_of_voxels_along_x-1) {
PrintMessage("G4LINAC_DATA_ANALYSIS-> ERROR IN XID "+std::to_string(xid) + " > "+std::to_string( _number_of_voxels_along_x-1));
return false;
}
if (yid > _number_of_voxels_along_y-1) {
PrintMessage("G4LINAC_DATA_ANALYSIS-> ERROR IN YID "+std::to_string(yid) + " > "+std::to_string( _number_of_voxels_along_y-1));
return false;
}
G4double max_rsd= myH5DataAnalysisHelper->GetMaxRSDPdd(xid,yid );
G4double min_rsd= myH5DataAnalysisHelper->GetMinRSDPdd(xid, yid );

if (max_rsd==0)
{
PrintMessage("G4LINAC_DATA_ANALYSIS-> MAC RSD MUST BE> 0.0");
return false;
}
HistoManager *fHistoManager = HistoManager::GetInstance();
max_z=_Phantom_size_z;
min_z=0;
fHistoManager->SetParametersForDosimetricDataPdd(_number_of_voxels_along_z , max_rsd, min_rsd,max_z,min_z);
for (  int j=0; j<_number_of_voxels_along_z; j++)
{
G4double z=0.5*_Phantom_size_z+ ( - _number_of_voxels_along_z + 1+ 2*j )*HalfVoxelDimensionAlongZ;
G4double rsd= myH5DataAnalysisHelper->GetRSD_DOSE(xid,yid, j);

fHistoManager->Fill_PDD( z, rsd);
}
fHistoManager->Save();
}


/*---------------------------Percentage_Depth_Dose_Curve----------------------*/
else if (PhysicalQuantity=="Percentage_Depth_Dose_Curve") 
{
macrofile="Percentage_Depth_Dose_Curve.C";
 int xid = atoi(param_4.c_str() );
 int yid = atoi(param_5.c_str() );
if (xid > _number_of_voxels_along_x-1) {
PrintMessage("G4LINAC_DATA_ANALYSIS-> ERROR IN XID "+std::to_string(xid)+ " > "+std::to_string( _number_of_voxels_along_x-1));
return false;
}
if (yid > _number_of_voxels_along_y-1) {
PrintMessage("G4LINAC_DATA_ANALYSIS-> ERROR IN YID "+std::to_string(yid) + " > "+std::to_string( _number_of_voxels_along_y-1));
return false;
}
G4double max_dose= myH5DataAnalysisHelper->GetMaxDosePdd(xid,yid );
G4double min_dose= myH5DataAnalysisHelper->GetMinDosePdd(xid, yid );
if (max_dose==0)
{
PrintMessage("G4LINAC_DATA_ANALYSIS-> MAX DOSE MUST BE > 0.0");
return false;
}
HistoManager *fHistoManager = HistoManager::GetInstance();
max_z=_Phantom_size_z;
min_z=0;
fHistoManager->SetParametersForDosimetricDataPdd(_number_of_voxels_along_z , max_dose, min_dose,max_z,min_z);
for (  int j=0; j<_number_of_voxels_along_z; j++)
{
G4double z=0.5*_Phantom_size_z+ ( - _number_of_voxels_along_z + 1+ 2*j )*HalfVoxelDimensionAlongZ;
G4double dose= myH5DataAnalysisHelper->Get_DOSE(xid,yid, j);
//

fHistoManager->Fill_PDD( z, dose);
}
fHistoManager->Save();
}
}////if ( DataType=="DosimeticData")

/*---------------------------End DosimetricData----------------------*/



/*---------------------------Begin PhaseSpaceData----------------------*/
else if ( DataType=="PhaseSpaceData")
{//if ( DataType=="PhaseSpaceData")
NameOfFile=param_2;
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
PrintMessage("G4LINAC_DATA_ANALYSIS-> MIN KINETIC ENERGY: " +std::to_string(  min_energy));
PrintMessage("G4LINAC_DATA_ANALYSIS-> MAX KINETIC ENERGY: "+std::to_string(  max_energy));
if (min_energy == max_energy){
PrintMessage( "G4LINAC_DATA_ANALYSIS-> FATAL ERROR  MIN_ENERGY = MAX_ENERGY  !");
return false;
}
fHistoManager->SetParametersForPhaseSpaceDataPhotonsEnergySpectrum("Photon Kinetic Energy Spectrum", EnergyBins, max_energy, min_energy);
G4double _photon_kinetic_energy= 0.0;
for (  int i=0; i< myH5DataAnalysisHelper->data_size_PhspData; i++)
{
_photon_kinetic_energy= myH5DataAnalysisHelper->GetKineticEnergy(i,pdge_photon);
if ( _photon_kinetic_energy !=0) fHistoManager->FillSpectrum (0,  _photon_kinetic_energy,1);
}
fHistoManager->Save();
}
//------------------------------------------------------------------------
if (PhysicalQuantity=="spatial_distribution_xy") {
int pdge_all_particles= 0;
macrofile="spatial_distribution_xy.C";
myH5DataAnalysisHelper->SET_PHASE_SPACE_FILE_NAME(NameOfFile);
myH5DataAnalysisHelper->READ_BEAM_DATA();
myH5DataAnalysisHelper->READ_EVENT_DATA();
myH5DataAnalysisHelper->READ_PHASE_SPACE_DATA();
HistoManager *fHistoManager = HistoManager::GetInstance();
G4double max_energy=myH5DataAnalysisHelper->GetMaxKineticEnergy(pdge_all_particles);
G4double min_energy=myH5DataAnalysisHelper->GetMinKineticEnergy(pdge_all_particles);
PrintMessage(" Min_Kinetic_Energy: " +std::to_string(  min_energy));
PrintMessage(" Max_Kinetic_Energy: " +std::to_string(  max_energy));

if (min_energy == max_energy){
PrintMessage("fatal error : min_energy = max energy " );
return false;
}
 int xbins=2000;
 int ybins=2000;
 max_x= myH5DataAnalysisHelper->GetMaxPosX(0);
 max_y= myH5DataAnalysisHelper->GetMaxPosY(0);
 min_x= myH5DataAnalysisHelper->GetMinPosX(0);
 min_y= myH5DataAnalysisHelper->GetMinPosY(0);
PrintMessage("G4LINAC_DATA_ANALYSIS-> MIN X: " +std::to_string(  min_x));
PrintMessage("G4LINAC_DATA_ANALYSIS-> MAX X: " +std::to_string(  max_x));
fHistoManager->SetParametersForPhaseSpaceDataSpatialDistXY("Spatial Distribution XY",  xbins, max_x/cm,  min_x/cm, ybins,max_y/cm, min_y/cm);
for (  int i=0; i< myH5DataAnalysisHelper->data_size_PhspData; i++)
{
G4double x_pos = myH5DataAnalysisHelper->GetPosX(i,0);
G4double y_pos = myH5DataAnalysisHelper->GetPosY(i,0);
fHistoManager->Fill_spatialDistxy(  x_pos, y_pos);
}
fHistoManager->Save();
}
//-------------------------------------------------------------------------



if (PhysicalQuantity=="photon_spatial_distribution_xy") {
int pdge_photon=22;
macrofile="photon_spatial_distribution_xy.C";
myH5DataAnalysisHelper->SET_PHASE_SPACE_FILE_NAME(NameOfFile);
myH5DataAnalysisHelper->READ_BEAM_DATA();
myH5DataAnalysisHelper->READ_EVENT_DATA();
myH5DataAnalysisHelper->READ_PHASE_SPACE_DATA();
HistoManager *fHistoManager = HistoManager::GetInstance();
G4double max_energy=myH5DataAnalysisHelper->GetMaxKineticEnergy(pdge_photon);
G4double min_energy=myH5DataAnalysisHelper->GetMinKineticEnergy(pdge_photon);
PrintMessage(" Min_Kinetic_Energy: " +std::to_string(  min_energy));
PrintMessage(" Max_Kinetic_Energy: " +std::to_string(  max_energy));

if (min_energy == max_energy){
PrintMessage("fatal error : min_energy = max energy " );
return false;
}
 int xbins=2000;
 int ybins=2000;
 max_x= myH5DataAnalysisHelper->GetMaxPosX(0);
 max_y= myH5DataAnalysisHelper->GetMaxPosY(0);
 min_x= myH5DataAnalysisHelper->GetMinPosX(0);
 min_y= myH5DataAnalysisHelper->GetMinPosY(0);
PrintMessage("G4LINAC_DATA_ANALYSIS-> MIN X: " +std::to_string(  min_x));
PrintMessage("G4LINAC_DATA_ANALYSIS-> MAX X: " +std::to_string(  max_x));
fHistoManager->SetParametersForPhaseSpaceDataSpatialDistXY("Photon Spatial Distribution XY",  xbins, max_x/cm,  min_x/cm, ybins,max_y/cm, min_y/cm);
for (  int i=0; i< myH5DataAnalysisHelper->data_size_PhspData; i++)
{
G4double x_pos = myH5DataAnalysisHelper->GetPosX(i,pdge_photon);
G4double y_pos = myH5DataAnalysisHelper->GetPosY(i,pdge_photon);
fHistoManager->Fill_spatialDistxy(  x_pos, y_pos);
}
fHistoManager->Save();
}
//------------------------------------------------------------------------

if (PhysicalQuantity=="electron_spatial_distribution_xy") {
int pdge_electron=11;
macrofile="electron_spatial_distribution_xy.C";
myH5DataAnalysisHelper->SET_PHASE_SPACE_FILE_NAME(NameOfFile);
myH5DataAnalysisHelper->READ_BEAM_DATA();
myH5DataAnalysisHelper->READ_EVENT_DATA();
myH5DataAnalysisHelper->READ_PHASE_SPACE_DATA();
HistoManager *fHistoManager = HistoManager::GetInstance();
G4double max_energy=myH5DataAnalysisHelper->GetMaxKineticEnergy(pdge_electron);
G4double min_energy=myH5DataAnalysisHelper->GetMinKineticEnergy(pdge_electron);
PrintMessage(" Min_Kinetic_Energy: " +std::to_string(  min_energy));
PrintMessage(" Max_Kinetic_Energy: " +std::to_string(  max_energy));

if (min_energy == max_energy){
PrintMessage("fatal error : min_energy = max energy " );
return false;
}
 int xbins=2000;
 int ybins=2000;
 max_x= myH5DataAnalysisHelper->GetMaxPosX(0);
 max_y= myH5DataAnalysisHelper->GetMaxPosY(0);
 min_x= myH5DataAnalysisHelper->GetMinPosX(0);
 min_y= myH5DataAnalysisHelper->GetMinPosY(0);
PrintMessage("G4LINAC_DATA_ANALYSIS-> MIN X: " +std::to_string(  min_x));
PrintMessage("G4LINAC_DATA_ANALYSIS-> MAX X: " +std::to_string(  max_x));
fHistoManager->SetParametersForPhaseSpaceDataSpatialDistXY("Electron Spatial Distribution XY",  xbins, max_x/cm,  min_x/cm, ybins,max_y/cm, min_y/cm);
for (  int i=0; i< myH5DataAnalysisHelper->data_size_PhspData; i++)
{
G4double x_pos = myH5DataAnalysisHelper->GetPosX(i,pdge_electron);
G4double y_pos = myH5DataAnalysisHelper->GetPosY(i,pdge_electron);
fHistoManager->Fill_spatialDistxy(  x_pos, y_pos);
}
fHistoManager->Save();
}



//------------------------------------------------------------------------
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
 max_x= myH5DataAnalysisHelper->GetMaxPosX(pdge_photon);
 max_y= myH5DataAnalysisHelper->GetMaxPosY(pdge_photon);
 min_x= myH5DataAnalysisHelper->GetMinPosX(pdge_photon);
 min_y= myH5DataAnalysisHelper->GetMinPosY(pdge_photon);
PrintMessage("G4LINAC_DATA_ANALYSIS-> MIN X: " +std::to_string( min_x));
PrintMessage("G4LINAC_DATA_ANALYSIS-> MAX X: " +std::to_string( max_x));
fHistoManager->SetParametersForPhaseSpaceDataPhotonSpatialDistXY_With_Kinetic("Spatial distribution of photons in function of its kinetic energies",  xbins, max_x,  min_x, ybins,max_y, min_y );
//for ( i=0; i< 10; i++)
//
G4double _energy=0.0;
for (  int i=0; i< myH5DataAnalysisHelper->data_size_PhspData; i++)
{
if (myH5DataAnalysisHelper->RAM_PhspData[i].PART_PDGE==22){
 _energy= myH5DataAnalysisHelper->GetKineticEnergy(i,pdge_photon);

//
//PrintMessage("_energy);
G4double x_pos = myH5DataAnalysisHelper->GetPosX(i,pdge_photon);
G4double y_pos = myH5DataAnalysisHelper->GetPosY(i,pdge_photon);
fHistoManager->Fill_spatialDistxy_with_kinetic( x_pos, y_pos, _energy);
}
}
fHistoManager->Save();
}
//------------------------------------------------------------------------

if (PhysicalQuantity=="spatial_distribution_xy_with_kinetic") {
macrofile="spatial_distribution_xy_with_kinetic.C";
myH5DataAnalysisHelper->SET_PHASE_SPACE_FILE_NAME(NameOfFile);
myH5DataAnalysisHelper->READ_BEAM_DATA();
myH5DataAnalysisHelper->READ_EVENT_DATA();
myH5DataAnalysisHelper->READ_PHASE_SPACE_DATA();
HistoManager *fHistoManager = HistoManager::GetInstance();
 int xbins=1000;
 int ybins=1000;
int pdge_all_particles= 0;
 max_x= myH5DataAnalysisHelper->GetMaxPosX(pdge_all_particles);
 max_y= myH5DataAnalysisHelper->GetMaxPosY(pdge_all_particles);
 min_x= myH5DataAnalysisHelper->GetMinPosX(pdge_all_particles);
 min_y= myH5DataAnalysisHelper->GetMinPosY(pdge_all_particles);
PrintMessage("G4LINAC_DATA_ANALYSIS-> MIN X: " +std::to_string( min_x));
PrintMessage("G4LINAC_DATA_ANALYSIS-> MIN X: " +std::to_string( max_x));
fHistoManager->SetParametersForPhaseSpaceDataSpatialDistXY_With_Kinetic(" 2d Spatial distribution of particle in function of its kinetic energies",  xbins, max_x,  min_x, ybins,max_y, min_y );
//for ( i=0; i< 10; i++)
//
G4double _energy=0.0;
for (  int i=0; i< myH5DataAnalysisHelper->data_size_PhspData; i++)
{

{
 _energy= myH5DataAnalysisHelper->GetKineticEnergy(i,pdge_all_particles);

//PrintMessage(std::to_string(_energy));
G4double x_pos = myH5DataAnalysisHelper->GetPosX(i,pdge_all_particles);
G4double y_pos = myH5DataAnalysisHelper->GetPosY(i,pdge_all_particles);
fHistoManager->Fill_spatialDistxy_with_kinetic( x_pos, y_pos, _energy);
}
}
fHistoManager->Save();
}
//---------------------------------------------------------------------------
if (PhysicalQuantity=="electron_spatial_distribution_xy_with_kinetic") {
PrintMessage("electron_spatial_distribution_xy_with_kinetic.C");
macrofile="electron_spatial_distribution_xy_with_kinetic.C";
myH5DataAnalysisHelper->SET_PHASE_SPACE_FILE_NAME(NameOfFile);
myH5DataAnalysisHelper->READ_BEAM_DATA();
myH5DataAnalysisHelper->READ_EVENT_DATA();
myH5DataAnalysisHelper->READ_PHASE_SPACE_DATA();
HistoManager *fHistoManager = HistoManager::GetInstance();
 int xbins=1000;
 int ybins=1000;
 int pdge_electron= 11;
 max_x= myH5DataAnalysisHelper->GetMaxPosX(pdge_electron);
 max_y= myH5DataAnalysisHelper->GetMaxPosY(pdge_electron);
 min_x= myH5DataAnalysisHelper->GetMinPosX(pdge_electron);
 min_y= myH5DataAnalysisHelper->GetMinPosY(pdge_electron);
fHistoManager->SetParametersForPhaseSpaceDataElectronSpatialDistXY_With_Kinetic("Spatial distribution of electrons in function of its kinetic energies",  xbins, max_x,  min_x, ybins,max_y, min_y );
//for ( i=0; i< 10; i++)
//
G4double _energy=0.0;
for (  int i=0; i< myH5DataAnalysisHelper->data_size_PhspData; i++)
{
if (myH5DataAnalysisHelper->RAM_PhspData[i].PART_PDGE==11){
 _energy= myH5DataAnalysisHelper->GetKineticEnergy(i,pdge_electron);

//
//PrintMessage("_energy);
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
PrintMessage("G4LINAC_DATA_ANALYSIS-> MAX THETA: "+std::to_string(max_theta/deg));
G4double min_theta= myH5DataAnalysisHelper->GetMinTheta(pdge_photon);
PrintMessage("G4LINAC_DATA_ANALYSIS-> MIN THETA: "+std::to_string( min_theta/deg));
int thetaBins=1000;
fHistoManager->SetParametersForPhaseSpaceDataPhotonAngularDistribution(" Photon Angular Distribution", thetaBins, max_theta/deg,  min_theta/deg);
//
for (  int i=0; i< myH5DataAnalysisHelper->data_size_PhspData; i++)
//for ( i=0; i< 10; i++)
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
PrintMessage("G4LINAC_DATA_ANALYSIS-> MAX THETA:  "+std::to_string( max_theta/deg));
G4double min_theta= myH5DataAnalysisHelper->GetMinTheta(pdge_electron);
PrintMessage("G4LINAC_DATA_ANALYSIS-> MIN THETA: "+std::to_string( min_theta/deg));
int thetaBins=1000;
fHistoManager->SetParametersForPhaseSpaceDataElectronAngularDistribution(" Electron Angular Distribution", thetaBins, max_theta/deg,  min_theta/deg);
//
for (  int i=0; i< myH5DataAnalysisHelper->data_size_PhspData; i++)
//for ( i=0; i< 10; i++)
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
PrintMessage( "G4LINAC_DATA_ANALYSIS-> MIN KINETIC ENERGY:  " + std::to_string(min_energy));
PrintMessage( "G4LINAC_DATA_ANALYSIS-> MAX KINETIC ENERGY:  "+std::to_string(max_energy));
if (min_energy == max_energy){
PrintMessage( "G4LINAC_DATA_ANALYSIS-> FATAL ERROR  MIN_ENERGY = MAX_ENERGY  !");
return false;
}
fHistoManager->SetParametersForPhaseSpaceDataElectronEnergySpectrum("Electron Kinetic Energy Spectrum", EnergyBins, max_energy, min_energy);
G4double _electron_kinetic_energy= 0.0;
for (  int i=0; i< myH5DataAnalysisHelper->data_size_PhspData; i++)
{
_electron_kinetic_energy= myH5DataAnalysisHelper->GetKineticEnergy(i,pdge_electron);

if ( _electron_kinetic_energy !=0){ fHistoManager->FillSpectrum (0,  _electron_kinetic_energy,1);}

}
fHistoManager->Save();
}

}

/*---------------------------Begin PhaseSpaceData----------------------*/

/*--------------------------- Begin Histogramming----------------------*/
PrintMessage( "G4LINAC_DATA_ANALYSIS->  NOW, THIS COMMAND WILL BE EXECUTED: root " +macrofile);
std::string command= "root ./scripts/"+macrofile;
PrintMessage("root ./scripts/"+macrofile);
//
system(command.c_str());
/*--------------------------- End Histogramming----------------------*/
return 0;
}
