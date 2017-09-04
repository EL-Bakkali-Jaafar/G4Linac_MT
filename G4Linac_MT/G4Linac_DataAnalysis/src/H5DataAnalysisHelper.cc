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
#include "H5DataAnalysisHelper.hh"
#include "G4RunManager.hh"
#include "G4ParticleTable.hh"
#include "G4ParticleDefinition.hh"
#include "G4SystemOfUnits.hh"
#include "Randomize.hh"
#include "H5Cpp.h"
#ifndef H5_NO_NAMESPACE
#ifndef H5_NO_STD
    using std::cout;
    using std::endl;
#endif  // H5_NO_STD
#endif

#include "H5Cpp.h"
#include <fstream>
#ifndef H5_NO_NAMESPACE
    using namespace H5;
#endif

const std::string DatasetName_histories("BeamData");
const std::string MEMBER_HISTORIES("_NUMBER_OF_HISTORIES");
const std::string MEMBER_Z_STOP("_Z_STOP");
const std::string DatasetName_event("EventData");
const std::string MEMBER_ENTERIES("_ENTERIES");
const std::string MEMBER_EVENTID("_EVENTID");
const std::string DatasetName_Phsp("PhspData");
const std::string MEMBER_PART_PDGE("_PART_PDGE");
const std::string MEMBER_PART_WEIGHT("_PART_WEIGHT");
const std::string MEMBER_PART_POS_X("_PART_POS_X");
const std::string MEMBER_PART_POS_Y("_PART_POS_Y");
const std::string MEMBER_PART_POS_Z("_PART_POS_Z");
const std::string MEMBER_PART_DIR_X("_PART_DIR_X");
const std::string MEMBER_PART_DIR_Y("_PART_DIR_Y");
const std::string MEMBER_PART_DIR_Z("_PART_DIR_Z");
const std::string MEMBER_PART_KINETIC("_PART_KINETIC");
const std::string DatasetName_Dosimetric("DosimetricData");
const std::string DatasetName_phantom("PhantomData");
const std::string MEMBER_RSD("_RSD");
const std::string MEMBER_DOSE("_DOSE");
const std::string MEMBER_VOXEL_XID("_VOXEL_XID");
const std::string MEMBER_VOXEL_YID("_VOXEL_YID");
const std::string MEMBER_VOXEL_ZID("_VOXEL_ZID");
const std::string MEMBER_NUMBER_VOXELS_ALONG_X("_NUMBER_VOXELS_ALONG_X");
const std::string MEMBER_NUMBER_VOXELS_ALONG_Y("_NUMBER_VOXELS_ALONG_Y");
const std::string MEMBER_NUMBER_VOXELS_ALONG_Z("_NUMBER_VOXELS_ALONG_Z");
const std::string MEMBER_PHANTOM_SIZE_X("_PHANTOM_SIZE_X");
const std::string MEMBER_PHANTOM_SIZE_Y("_PHANTOM_SIZE_Y");
const std::string MEMBER_PHANTOM_SIZE_Z("_PHANTOM_SIZE_Z");


/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/

H5DataAnalysisHelper::H5DataAnalysisHelper()


{

}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
G4double H5DataAnalysisHelper::GetTheta(int id,int part_pdge){

G4double _theta;
_theta*=deg;
if (RAM_PhspData[id].PART_PDGE==part_pdge){

_theta=std::acos(std::abs(RAM_PhspData[id].PART_DIR_Z));
 return _theta ;
}

}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
G4double H5DataAnalysisHelper::GetMaxTheta(int part_pdge)
{
	G4double  max_dir_z=0 , dir_z=0;

max_dir_z*=deg;
dir_z*=deg;
 for (unsigned int i=0 ; i< data_size_PhspData ;i++) {

dir_z= GetTheta(i,part_pdge);

if (  max_dir_z <=dir_z) {  max_dir_z =dir_z;}

}
return max_dir_z;


}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
G4double H5DataAnalysisHelper::GetMinTheta(int part_pdge)
{
	G4double  min_dir_z=0 , dir_z=0;
int incr=-1;
min_dir_z*=deg;
dir_z*=deg;
 for (unsigned int i=0 ; i< data_size_PhspData ;i++) {

dir_z= GetTheta(i, part_pdge);

incr++;
if (incr==0){min_dir_z= GetTheta(i, part_pdge);};
dir_z=GetTheta(i,part_pdge);

if ( min_dir_z >=dir_z) {min_dir_z =dir_z;}

}


return min_dir_z;



}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
G4double H5DataAnalysisHelper::GetPosX(int id,int part_pdge){





if  (part_pdge==0) { 

 return RAM_PhspData[id].PART_KINETIC;

} else 
if (part_pdge!=0){

if (RAM_PhspData[id].PART_PDGE==part_pdge)
{
 return RAM_PhspData[id].PART_POS_X;

}
 else { return 0;}

}





}


/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
G4double H5DataAnalysisHelper::GetPosY(int id,int part_pdge){


if  (part_pdge==0) { 

 return RAM_PhspData[id].PART_KINETIC;

} else 
if (part_pdge!=0){

if (RAM_PhspData[id].PART_PDGE==part_pdge)
{
 return RAM_PhspData[id].PART_POS_Y;

}
 else { return 0;}

}




}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
 G4double H5DataAnalysisHelper::GetMaxPosX(int part_pdge)
{
	G4double  max_pos_x=0 , pos_x=0;


 for (unsigned int i=0 ; i< data_size_PhspData ;i++) {
pos_x= GetPosX(i,part_pdge);
if (  max_pos_x <=pos_x) {  max_pos_x=pos_x;}

}

return max_pos_x;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
G4double H5DataAnalysisHelper::GetMaxPosY(int part_pdge)
{
	G4double  max_pos_y=0 , pos_y=0;


 for (unsigned int i=0 ; i< data_size_PhspData ;i++) {
pos_y= GetPosY(i,part_pdge);
if (  max_pos_y <=pos_y) {  max_pos_y=pos_y;}

}

return max_pos_y;
}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
G4double H5DataAnalysisHelper::GetMinPosY(int part_pdge)
{
	G4double  min_pos_y=0 , pos_y=0;
int incr=-1;

 for (unsigned int i=0 ; i< data_size_PhspData ;i++) {
pos_y= GetPosY(i,part_pdge);

incr++;
if (incr==0){min_pos_y= GetPosY(i,part_pdge);};
pos_y=GetPosY(i,part_pdge);

if ( min_pos_y >=pos_y) {min_pos_y=pos_y;}

}

return min_pos_y;
}


/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/

G4double H5DataAnalysisHelper::GetMinPosX(int part_pdge)
{
	G4double  min_pos_x=0 , pos_x=0;
int incr=-1;

 for (unsigned int i=0 ; i< data_size_PhspData ;i++) {
pos_x= GetPosX(i,part_pdge);

incr++;
if (incr==0){min_pos_x= GetPosX(i,part_pdge);};
pos_x=GetPosX(i,part_pdge);

if ( min_pos_x >=pos_x) {min_pos_x=pos_x;}

}

return min_pos_x;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/

G4double H5DataAnalysisHelper::GetKineticEnergy(int id,int part_pdge){

if  (part_pdge==0) { 

 return RAM_PhspData[id].PART_KINETIC;

} else 
if (part_pdge!=0){

if (RAM_PhspData[id].PART_PDGE==part_pdge)
{
 return RAM_PhspData[id].PART_KINETIC;

}
 else { return 0;}

}
}


/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/

G4double H5DataAnalysisHelper::GetMinKineticEnergy(int part_pdge)
{
	G4double  min_KineticEnergy=0 , KineticEnergy=0;
int incr=-1;

 for (unsigned int i=0 ; i< data_size_PhspData ;i++) {
if (GetKineticEnergy(i,part_pdge!=-1)) KineticEnergy= GetKineticEnergy(i,part_pdge);

incr++;
if (incr==0){


if (GetKineticEnergy(i,part_pdge!=-1)) min_KineticEnergy= GetKineticEnergy(i,part_pdge);


};

if (GetKineticEnergy(i,part_pdge!=-1))  KineticEnergy=GetKineticEnergy(i, part_pdge);

if ( min_KineticEnergy >=KineticEnergy) {min_KineticEnergy=KineticEnergy;}

}

return min_KineticEnergy;
}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/

G4double H5DataAnalysisHelper::GetMaxKineticEnergy(int part_pdge)
{
	G4double  max_KineticEnergy=0 , KineticEnergy=0;


 for (unsigned int i=0 ; i< data_size_PhspData ;i++) {
KineticEnergy= GetKineticEnergy(i,part_pdge);
if (  max_KineticEnergy<=KineticEnergy) {  max_KineticEnergy=KineticEnergy;}

}

return max_KineticEnergy;
}


/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
G4double H5DataAnalysisHelper::GetRSD_DOSE(int xid,int yid, int zid){
     double rsd;
 int incr=-1;
    for ( unsigned i =0; i< data_size_DosimetricData; i++){
        incr++;
      if (this->RAM_DosimetricData[incr].VOXEL_XID==xid and this->RAM_DosimetricData[incr].VOXEL_YID==yid and this->RAM_DosimetricData[incr].VOXEL_ZID==zid)
       {

        rsd= this->RAM_DosimetricData[incr].RSD;
      }

    }

    return rsd;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
G4double H5DataAnalysisHelper::GetEnergyDeposit(int xid,int yid, int zid){
 G4double dose;

 int incr=-1;
    for ( unsigned i =0; i< data_size_DosimetricData; i++){
        incr++;
        if (this->RAM_DosimetricData[incr].VOXEL_XID==xid and this->RAM_DosimetricData[incr].VOXEL_YID==yid and this->RAM_DosimetricData[incr].VOXEL_ZID==zid)
       {

        //
            dose=this->RAM_DosimetricData[incr].DOSE;

      }

    }
//G4cout<<" xid  :" << xid <<" yid : "<< yid<< " zid : " << zid<<" dose :" << dose<<G4endl;
    return dose;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
G4double H5DataAnalysisHelper::GetMaxEnergyDepositPdd(int xid, int yid){
 G4double dose;
G4double max_dose=0.0;


    for ( unsigned i =0; i< data_size_DosimetricData; i++)
{
          if ( this->RAM_DosimetricData[i].VOXEL_XID==xid and  this->RAM_DosimetricData[i].VOXEL_YID==yid )  
       {
            dose=this->RAM_DosimetricData[i].DOSE;
                       if (  max_dose <=dose) { max_dose=dose;}


}


      }

   

    return max_dose;
}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
G4double H5DataAnalysisHelper::GetMaxEnergyDepositHeatMap(int zid){
 G4double dose;
G4double max_dose=0.0;


    for ( unsigned i =0; i< data_size_DosimetricData; i++)
{
          if ( this->RAM_DosimetricData[i].VOXEL_ZID==zid )  
{
            dose=this->RAM_DosimetricData[i].DOSE;
if (  max_dose <=dose) { max_dose=dose;}
}
      }

   

    return max_dose;
}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
G4double H5DataAnalysisHelper::GetMinEnergyDepositXProfile(int ycid, int zcid){
 G4double dose;
G4double min_dose=0.0;
 int incr=-1;

    for ( unsigned i =0; i< data_size_DosimetricData; i++)
{
     if ( this->RAM_DosimetricData[i].VOXEL_ZID==zcid and this->RAM_DosimetricData[i].VOXEL_YID==ycid  )
{  
incr++;
if (incr==0){min_dose= this->RAM_DosimetricData[i].DOSE;};
        //
            dose=this->RAM_DosimetricData[i].DOSE;
if (  min_dose >=dose) { min_dose=dose;}


}
      }

   

    return min_dose;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
G4double H5DataAnalysisHelper::GetMaxEnergyDepositXProfile(int ycid, int zcid){
 G4double dose;
G4double max_dose=0.0;


    for ( unsigned i =0; i< data_size_DosimetricData; i++)
{


          if ( this->RAM_DosimetricData[i].VOXEL_YID==ycid and  this->RAM_DosimetricData[i].VOXEL_ZID==zcid )  
{

            dose=this->RAM_DosimetricData[i].DOSE;
if (  max_dose <=dose) { max_dose=dose;}
}
      }

   

    return max_dose;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
G4double H5DataAnalysisHelper::GetMinEnergyDepositPdd(int xid, int yid){
 G4double dose;
G4double min_dose=0.0;
 int incr=-1;

    for ( unsigned i =0; i< data_size_DosimetricData; i++)
{
     if ( this->RAM_DosimetricData[i].VOXEL_XID==xid and  this->RAM_DosimetricData[i].VOXEL_YID==yid )
{  
incr++;
       if (incr==0){min_dose= this->RAM_DosimetricData[i].DOSE;};
            dose=this->RAM_DosimetricData[i].DOSE;
if (  min_dose >=dose) { min_dose=dose;}


}
      }

   

    return min_dose;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
G4double H5DataAnalysisHelper::GetMinEnergyDepositHeatMap(int  zid){
 G4double dose;
G4double min_dose=0.0;
 int incr=-1;

    for ( unsigned i =0; i< data_size_DosimetricData; i++)
{
     if ( this->RAM_DosimetricData[i].VOXEL_ZID==zid )
{  

incr++;
        //
if (incr==0){min_dose= this->RAM_DosimetricData[i].DOSE;};
            dose=this->RAM_DosimetricData[i].DOSE;
if (  min_dose >=dose) { min_dose=dose;}


}
      }

   

    return min_dose;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
int H5DataAnalysisHelper::GetNumberOfVoxelsAlongX(){

   int _NumberOfVoxelsAlongX= RAM_PhantomData[0].NUMBER_VOXELS_ALONG_X;
    return _NumberOfVoxelsAlongX ;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
int H5DataAnalysisHelper::GetNumberOfVoxelsAlongY(){

   int _NumberOfVoxelsAlongY= RAM_PhantomData[0].NUMBER_VOXELS_ALONG_Y;
    return _NumberOfVoxelsAlongY ;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/

int H5DataAnalysisHelper::GetNumberOfVoxelsAlongZ(){

   int _NumberOfVoxelsAlongZ= RAM_PhantomData[0].NUMBER_VOXELS_ALONG_Z;
    return _NumberOfVoxelsAlongZ ;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/

double H5DataAnalysisHelper::GetPhantomsizeX(){

 double _PHANTOM_SIZE_X=RAM_PhantomData[0].PHANTOM_SIZE_X;
    return  _PHANTOM_SIZE_X;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
double H5DataAnalysisHelper::GetPhantomsizeY(){

   double _PHANTOM_SIZE_Y= RAM_PhantomData[0].PHANTOM_SIZE_Y;
    return   _PHANTOM_SIZE_Y;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
double H5DataAnalysisHelper::GetPhantomsizeZ(){


   double _PHANTOM_SIZE_Z=RAM_PhantomData[0].PHANTOM_SIZE_Z;
    return  _PHANTOM_SIZE_Z;
}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/

H5DataAnalysisHelper::~H5DataAnalysisHelper()
{
   // 


}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/

void H5DataAnalysisHelper::READ_EVENT_DATA()
 {


   H5File file( this->PhaseSpaceFileName, H5F_ACC_RDONLY );

    DataSet dataset_event = file.openDataSet( DatasetName_event );
     CompType mtype_event( sizeof(EventData) );
    // GET NUMBER OF DATA IN DATASET NAMED EventData
     G4int data_event_size=dataset_event.getSpace().getSimpleExtentNpoints();
      RAM_EventData = new EventData[data_event_size];
     mtype_event.insertMember(MEMBER_ENTERIES,     HOFFSET(EventData, NUMBER_OF_ENTRIES),     PredType::NATIVE_INT);
     mtype_event.insertMember(MEMBER_EVENTID,      HOFFSET(EventData, EVENT_ID),              PredType::NATIVE_INT);
     dataset_event.read( RAM_EventData, mtype_event );

 }

 /*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
void H5DataAnalysisHelper::SET_DOSIMETRIC_FILE_NAME( std::string _FileName)

 {
 this->DosimetricDataFileName=_FileName;

 }


void H5DataAnalysisHelper::SET_PHASE_SPACE_FILE_NAME( std::string _FileName)

 {
 this->PhaseSpaceFileName=_FileName;

 }

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/

 void H5DataAnalysisHelper::READ_DOSIMETRIC_DATA_FROM_BINARY_FILE(){



// Read data
 std::fstream binary_file(this->DosimetricDataFileName,std::ios::binary|std::ios::in| std::ios::ate );
 int size = binary_file.tellg();
this->RAM_DosimetricData = new DosimetricData[size];
RAM_PhantomData = new PhantomData[1];
data_size_DosimetricData= size/sizeof(DosCalData);
        DosCalData _DosCalData;
    for(int i = 0; i<size/sizeof(DosCalData); i++)
    { 

        binary_file.seekg(i*sizeof(DosCalData));
        binary_file.read(reinterpret_cast<char *>(&_DosCalData),sizeof(DosCalData));

this->RAM_DosimetricData[i].VOXEL_ZID=_DosCalData.VOXEL_ZID;
this->RAM_DosimetricData[i].VOXEL_YID=_DosCalData.VOXEL_YID;
this->RAM_DosimetricData[i].VOXEL_XID=_DosCalData.VOXEL_XID;
this->RAM_DosimetricData[i].RSD=_DosCalData.RSD;
this->RAM_DosimetricData[i].DOSE=_DosCalData.DOSE;

    }



RAM_PhantomData[0].NUMBER_VOXELS_ALONG_X=_DosCalData.NUMBER_VOXELS_ALONG_X;

RAM_PhantomData[0].NUMBER_VOXELS_ALONG_Y=_DosCalData.NUMBER_VOXELS_ALONG_Y;

RAM_PhantomData[0].NUMBER_VOXELS_ALONG_Z=_DosCalData.NUMBER_VOXELS_ALONG_Z;

RAM_PhantomData[0].PHANTOM_SIZE_X=_DosCalData.PHANTOM_SIZE_X;

RAM_PhantomData[0].PHANTOM_SIZE_Y=_DosCalData.PHANTOM_SIZE_Y;

RAM_PhantomData[0].PHANTOM_SIZE_Z=_DosCalData.PHANTOM_SIZE_Z;
//


    binary_file.close();







}

void H5DataAnalysisHelper::READ_BEAM_DATA()
 {
     const std::string FileName( this->PhaseSpaceFileName);
     H5File file( FileName, H5F_ACC_RDONLY );
     DataSet dataset_histories = file.openDataSet( DatasetName_histories );
    CompType mtype_histories( sizeof(BeamData) );
     mtype_histories.insertMember(MEMBER_HISTORIES,     HOFFSET(BeamData, NUMBER_OF_HISORIES),     PredType::NATIVE_INT);
     mtype_histories.insertMember(MEMBER_Z_STOP,        HOFFSET(BeamData, Z_STOP),                 PredType::NATIVE_FLOAT);
     dataset_histories.read( RAM_BeamData, mtype_histories );
 }

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
void H5DataAnalysisHelper::READ_PHASE_SPACE_DATA()
{

  // LOAD PHASE SPACE HDF5-BASED FORMAT FILE
     H5File file(  this->PhaseSpaceFileName, H5F_ACC_RDONLY );
     DataSet dataset = file.openDataSet( DatasetName_Phsp );
    CompType mtype2( sizeof(PhspData) );
    // GET NUMBER OF DATA IN DATASET NAMED PhspData
     data_size_PhspData  = dataset.getSpace().getSimpleExtentNpoints();
    RAM_PhspData = new PhspData[data_size_PhspData];

    mtype2.insertMember(MEMBER_PART_WEIGHT,  HOFFSET(PhspData, PART_WEIGHT),  PredType::NATIVE_FLOAT);
    mtype2.insertMember(MEMBER_PART_POS_X,   HOFFSET(PhspData, PART_POS_X),   PredType::NATIVE_FLOAT);
    mtype2.insertMember(MEMBER_PART_PDGE,    HOFFSET(PhspData, PART_PDGE),    PredType::NATIVE_INT);
    mtype2.insertMember(MEMBER_PART_POS_Y,   HOFFSET(PhspData, PART_POS_Y),   PredType::NATIVE_FLOAT);
    mtype2.insertMember(MEMBER_PART_POS_Z,   HOFFSET(PhspData, PART_POS_Z),   PredType::NATIVE_FLOAT);
    mtype2.insertMember(MEMBER_PART_DIR_X,   HOFFSET(PhspData, PART_DIR_X),   PredType::NATIVE_FLOAT);
    mtype2.insertMember(MEMBER_PART_DIR_Y,   HOFFSET(PhspData, PART_DIR_Y),   PredType::NATIVE_FLOAT);
    mtype2.insertMember(MEMBER_PART_DIR_Z,   HOFFSET(PhspData, PART_DIR_Z),   PredType::NATIVE_FLOAT);
    mtype2.insertMember(MEMBER_PART_KINETIC, HOFFSET(PhspData, PART_KINETIC), PredType::NATIVE_FLOAT);
    dataset.read( RAM_PhspData, mtype2 );

}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/

