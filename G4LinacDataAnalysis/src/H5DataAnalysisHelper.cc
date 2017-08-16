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


/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/

H5DataAnalysisHelper::H5DataAnalysisHelper()


{

}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
G4double H5DataAnalysisHelper::GetPosX(int id){



 return RAM_PhspData[id].PART_POS_X;


}


/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
G4double H5DataAnalysisHelper::GetPosY(int id){



 return RAM_PhspData[id].PART_POS_Y;


}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
 G4double H5DataAnalysisHelper::GetMaxPosX()
{
	G4double  max_pos_x=0 , pos_x=0;


 for (unsigned int i=0 ; i< data_size_PhspData ;i++) {
pos_x= GetPosX(i);
if (  max_pos_x <=pos_x) {  max_pos_x=pos_x;}

}

return max_pos_x;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
G4double H5DataAnalysisHelper::GetMaxPosY()
{
	G4double  max_pos_y=0 , pos_y=0;


 for (unsigned int i=0 ; i< data_size_PhspData ;i++) {
pos_y= GetPosY(i);
if (  max_pos_y <=pos_y) {  max_pos_y=pos_y;}

}

return max_pos_y;
}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
G4double H5DataAnalysisHelper::GetMinPosY()
{
	G4double  min_pos_y=0 , pos_y=0;
int incr=-1;

 for (unsigned int i=0 ; i< data_size_PhspData ;i++) {
pos_y= GetPosY(i);

incr++;
if (incr==0){min_pos_y= GetPosY(i);};
pos_y=GetPosY(i);

if ( min_pos_y >=pos_y) {min_pos_y=pos_y;}

}

return min_pos_y;
}


/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/

G4double H5DataAnalysisHelper::GetMinPosX()
{
	G4double  min_pos_x=0 , pos_x=0;
int incr=-1;

 for (unsigned int i=0 ; i< data_size_PhspData ;i++) {
pos_x= GetPosX(i);

incr++;
if (incr==0){min_pos_x= GetPosX(i);};
pos_x=GetPosX(i);

if ( min_pos_x >=pos_x) {min_pos_x=pos_x;}

}

return min_pos_x;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/

G4double H5DataAnalysisHelper::GetKineticEnergy(int id){



 return RAM_PhspData[id].PART_KINETIC;


}


/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/

G4double H5DataAnalysisHelper::GetMinKineticEnergy()
{
	G4double  min_KineticEnergy=0 , KineticEnergy=0;
int incr=-1;

 for (unsigned int i=0 ; i< data_size_PhspData ;i++) {
KineticEnergy= GetKineticEnergy(i);

incr++;
if (incr==0){min_KineticEnergy= GetKineticEnergy(i);};
KineticEnergy=GetKineticEnergy(i);

if ( min_KineticEnergy >=KineticEnergy) {min_KineticEnergy=KineticEnergy;}

}

return min_KineticEnergy;
}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/

G4double H5DataAnalysisHelper::GetMaxKineticEnergy()
{
	G4double  max_KineticEnergy=0 , KineticEnergy=0;


 for (unsigned int i=0 ; i< data_size_PhspData ;i++) {
KineticEnergy= GetKineticEnergy(i);
if (  max_KineticEnergy<=KineticEnergy) {  max_KineticEnergy=KineticEnergy;}

}

return max_KineticEnergy;
}


/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
G4double H5DataAnalysisHelper::GetRSD_EDEP(int xid,int yid, int zid){
     double rsd;
 int incr=-1;
    for ( unsigned i =0; i< data_size_DosimetricData; i++){
        incr++;
      if (RAM_DosimetricData[incr].VOXEL_XID==xid and RAM_DosimetricData[incr].VOXEL_YID==yid and RAM_DosimetricData[incr].VOXEL_ZID==zid)
       {

        rsd= RAM_DosimetricData[incr].STD_DEV;
      }

    }

    return rsd;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
G4double H5DataAnalysisHelper::GetEnergyDeposit(int xid,int yid, int zid){
 G4double edep;

 int incr=-1;
    for ( unsigned i =0; i< data_size_DosimetricData; i++){
        incr++;
        if (RAM_DosimetricData[incr].VOXEL_XID==xid and RAM_DosimetricData[incr].VOXEL_YID==yid and RAM_DosimetricData[incr].VOXEL_ZID==zid)
       {

        //
            edep=RAM_DosimetricData[incr].EDEP;

      }

    }
//G4cout<<" xid  :" << xid <<" yid : "<< yid<< " zid : " << zid<<" edep :" << edep<<G4endl;
    return edep;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
G4double H5DataAnalysisHelper::GetMaxEnergyDepositPdd(int xid, int yid){
 G4double edep;
G4double max_edep=0.0;


    for ( unsigned i =0; i< data_size_DosimetricData; i++)
{
          if ( RAM_DosimetricData[i].VOXEL_XID==xid and  RAM_DosimetricData[i].VOXEL_YID==yid )  
       {
            edep=RAM_DosimetricData[i].EDEP;
                       if (  max_edep <=edep) { max_edep=edep;}


}


      }

   

    return max_edep;
}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
G4double H5DataAnalysisHelper::GetMaxEnergyDepositHeatMap(int zid){
 G4double edep;
G4double max_edep=0.0;


    for ( unsigned i =0; i< data_size_DosimetricData; i++)
{
          if ( RAM_DosimetricData[i].VOXEL_ZID==zid )  
{
            edep=RAM_DosimetricData[i].EDEP;
if (  max_edep <=edep) { max_edep=edep;}
}
      }

   

    return max_edep;
}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
G4double H5DataAnalysisHelper::GetMinEnergyDepositXProfile(int ycid, int zcid){
 G4double edep;
G4double min_edep=0.0;
 int incr=-1;

    for ( unsigned i =0; i< data_size_DosimetricData; i++)
{
     if ( RAM_DosimetricData[i].VOXEL_ZID==zcid and RAM_DosimetricData[i].VOXEL_YID==ycid  )
{  
incr++;
if (incr==0){min_edep= RAM_DosimetricData[i].EDEP;};
        //
            edep=RAM_DosimetricData[i].EDEP;
if (  min_edep >=edep) { min_edep=edep;}


}
      }

   

    return min_edep;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
G4double H5DataAnalysisHelper::GetMaxEnergyDepositXProfile(int ycid, int zcid){
 G4double edep;
G4double max_edep=0.0;


    for ( unsigned i =0; i< data_size_DosimetricData; i++)
{
          if ( RAM_DosimetricData[i].VOXEL_YID==ycid and  RAM_DosimetricData[i].VOXEL_ZID==zcid )  
{

            edep=RAM_DosimetricData[i].EDEP;
if (  max_edep <=edep) { max_edep=edep;}
}
      }

   

    return max_edep;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
G4double H5DataAnalysisHelper::GetMinEnergyDepositPdd(int xid, int yid){
 G4double edep;
G4double min_edep=0.0;
 int incr=-1;

    for ( unsigned i =0; i< data_size_DosimetricData; i++)
{
     if ( RAM_DosimetricData[i].VOXEL_XID==xid and  RAM_DosimetricData[i].VOXEL_YID==yid )
{  
incr++;
       if (incr==0){min_edep= RAM_DosimetricData[i].EDEP;};
            edep=RAM_DosimetricData[i].EDEP;
if (  min_edep >=edep) { min_edep=edep;}


}
      }

   

    return min_edep;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
G4double H5DataAnalysisHelper::GetMinEnergyDepositHeatMap(int  zid){
 G4double edep;
G4double min_edep=0.0;
 int incr=-1;

    for ( unsigned i =0; i< data_size_DosimetricData; i++)
{
     if ( RAM_DosimetricData[i].VOXEL_ZID==zid )
{  

incr++;
        //
if (incr==0){min_edep= RAM_DosimetricData[i].EDEP;};
            edep=RAM_DosimetricData[i].EDEP;
if (  min_edep >=edep) { min_edep=edep;}


}
      }

   

    return min_edep;
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

G4double H5DataAnalysisHelper::GetPhantomsizeX(){

   G4double _PHANTOM_SIZE_X =RAM_PhantomData[0].PHANTOM_SIZE_X;
    return _PHANTOM_SIZE_X;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
G4double H5DataAnalysisHelper::GetPhantomsizeY(){

   G4double _PHANTOM_SIZE_Y= RAM_PhantomData[0].PHANTOM_SIZE_Y;
    return _PHANTOM_SIZE_Y;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
G4double H5DataAnalysisHelper::GetPhantomsizeZ(){

   G4double _PHANTOM_SIZE_Z =RAM_PhantomData[0].PHANTOM_SIZE_Z;
    return _PHANTOM_SIZE_Z;
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

 void H5DataAnalysisHelper::READ_DOSIMETRIC_DATA(){
     try{
             // DECLARATION OF STRINGS OF MEMBERS OF DATASET NAMED "DosimetricData"
     H5File file(  this->DosimetricDataFileName, H5F_ACC_RDONLY );
//G4cout<<" File Name" << this->DosimetricDataFileName<<G4endl;
     DataSet dataset = file.openDataSet( DatasetName_Dosimetric);
     //H5:: DataSet dataset_phantom = file.openDataSet( DatasetName_phantom);

     CompType mtype( sizeof(DosimetricData) );


     data_size_DosimetricData=dataset.getSpace().getSimpleExtentNpoints();
//G4cout<<" data_size_DosimetricData " << data_size_DosimetricData<<G4endl;
RAM_DosimetricData    = new DosimetricData[data_size_DosimetricData];


               //
     mtype.insertMember(MEMBER_VOXEL_XID,                        HOFFSET(DosimetricData, VOXEL_XID),     PredType::NATIVE_INT);
     mtype.insertMember(MEMBER_VOXEL_YID,                        HOFFSET(DosimetricData, VOXEL_YID),     PredType::NATIVE_INT);
     mtype.insertMember(MEMBER_VOXEL_ZID,                        HOFFSET(DosimetricData, VOXEL_ZID),     PredType::NATIVE_INT);
     mtype.insertMember(MEMBER_STD_DEV,                          HOFFSET(DosimetricData, STD_DEV),       PredType::NATIVE_FLOAT);
     mtype.insertMember(MEMBER_EDEP,                             HOFFSET(DosimetricData,EDEP),           PredType::NATIVE_FLOAT);
     dataset.read(RAM_DosimetricData, mtype );


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
 /*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/

void H5DataAnalysisHelper::READ_PHANTOM_DATA(){
    try{
//G4cout<<" File Name" << this->DosimetricDataFileName<<G4endl;
   H5File file(  this->DosimetricDataFileName, H5F_ACC_RDONLY );
   //
   DataSet dataset_phantom = file.openDataSet( DatasetName_phantom);

   CompType mtype_phantom( sizeof(PhantomData) );


   //

   int data_size_phantom=dataset_phantom.getSpace().getSimpleExtentNpoints();
//G4cout<<" data_size_phantom " <<data_size_phantom<<G4endl;

RAM_PhantomData    = new PhantomData[data_size_phantom];
   mtype_phantom.insertMember(MEMBER_NUMBER_VOXELS_ALONG_X,     HOFFSET(PhantomData, NUMBER_VOXELS_ALONG_X),     PredType::NATIVE_INT);
   mtype_phantom.insertMember(MEMBER_NUMBER_VOXELS_ALONG_Y,     HOFFSET(PhantomData, NUMBER_VOXELS_ALONG_Y),     PredType::NATIVE_INT);
   mtype_phantom.insertMember(MEMBER_NUMBER_VOXELS_ALONG_Z,     HOFFSET(PhantomData, NUMBER_VOXELS_ALONG_Z),     PredType::NATIVE_INT);
   mtype_phantom.insertMember(MEMBER_PHANTOM_SIZE_X,            HOFFSET(PhantomData,PHANTOM_SIZE_X),     PredType::NATIVE_FLOAT);
   mtype_phantom.insertMember(MEMBER_PHANTOM_SIZE_Y,            HOFFSET(PhantomData,PHANTOM_SIZE_Y),     PredType::NATIVE_FLOAT);
   mtype_phantom.insertMember(MEMBER_PHANTOM_SIZE_Z,            HOFFSET(PhantomData,PHANTOM_SIZE_Z),     PredType::NATIVE_FLOAT);
   dataset_phantom.read(RAM_PhantomData, mtype_phantom );
//G4cout<<" Read Ok" <<G4endl;

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

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/

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

