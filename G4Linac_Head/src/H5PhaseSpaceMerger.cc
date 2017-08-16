
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
#include "H5PhaseSpaceMerger.hh"
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
#include <sys/types.h>
#include <ctime>
#include <dirent.h>
#include <errno.h>
#include <vector>
#include <string>
#include <iostream>
#include <cstdio>
#include <stdio.h>
#include <math.h>
#include "DetectorConstruction.hh"
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
#include "H5PhaseSpaceWriter.hh"
#include "G4RunManager.hh"
#include <vector>
#include "G4SystemOfUnits.hh"
#include "H5Cpp.h"
#include "G4Run.hh"
#include "G4SliceTimer.hh"
#include "G4Threading.hh"
using    namespace std;

H5PhaseSpaceMerger * H5PhaseSpaceMerger::theInstance = 0;
H5PhaseSpaceMerger ::PhspData *myTotalPhspData;
H5PhaseSpaceMerger ::EventData *myTotalEventData;
H5PhaseSpaceMerger ::BeamData myTotalBeamData[1];
int dim_total_phsp;
int dim_total_event;
const std::string DatasetName("PhspData");
const std::string DatasetName_event("EventData");
const std::string DatasetName_histories("BeamData");
const std::string MEMBER_HISTORIES("_NUMBER_OF_HISTORIES");
const std::string MEMBER_ENTERIES("_ENTERIES");
const std::string MEMBER_PART_PDGE("_PART_PDGE");
const std::string MEMBER_PART_WEIGHT("_PART_WEIGHT");
const std::string MEMBER_PART_POS_X("_PART_POS_X");
const std::string MEMBER_PART_POS_Y("_PART_POS_Y");
const std::string MEMBER_PART_POS_Z("_PART_POS_Z");
const std::string MEMBER_PART_DIR_X("_PART_DIR_X");
const std::string MEMBER_PART_DIR_Y("_PART_DIR_Y");
const std::string MEMBER_PART_DIR_Z("_PART_DIR_Z");
const std::string MEMBER_PART_KINETIC("_PART_KINETIC");
const std::string MEMBER_Z_STOP("_Z_STOP");
const std::string MEMBER_EVENTID("_EVENTID");
const std::string MEMBER_DATA_ID("_DATA_ID");
std::string ANSI_RESET_COLOR = "\033[0m";
std::string ANSI_GREEN = "\033[33m";
int static ll=0;
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
H5PhaseSpaceMerger * H5PhaseSpaceMerger::GetInstance()
{
  if (!theInstance) theInstance = new H5PhaseSpaceMerger();
  return theInstance;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/

H5PhaseSpaceMerger::H5PhaseSpaceMerger()
{
NUMBER_OF_PHOTONS                  =  0;
NUMBER_OF_ELECTRONS                =  0;
NUMBER_OF_POSITRONS                =  0;
NUMBER_OF_PROTONS                  =  0;
NUMBER_OF_NEUTRONS                 =  0;
NUMBER_OF_PARTICLES                =  0;
NUMBER_OF_ENTRIES                  =  0;
NUMBER_OF_ACTIVE_EVENT             =  0;
EVENT_ID        =  0;
ELECTRON_ENERGY_MAX  =  0;
ELECTRON_ENERGY_MIN  =  0;
ELECTRON_ENERGY_MEAN =  0;
PHOTON_ENERGY_MAX    =  0;
PHOTON_ENERGY_MIN    =  0;
PHOTON_ENERGY_MEAN   =  0;
POSITRON_ENERGY_MAX  =  0;
PHOTON_WEIGHT_MAX    =  0;
PHOTON_WEIGHT_MIN    =  0;
PHOTON_WEIGHT_MEAN   =  0;
ELECTRONS_WEIGHT_MAX    =  0;
ELECTRONS_WEIGHT_MIN    =  0;
ELECTRONS_WEIGHT_MEAN   =  0;

POSITRONS_WEIGHT_MAX    =  0;
POSITRONS_WEIGHT_MIN    =  0;
POSITRONS_WEIGHT_MEAN   =  0;


POSITRON_ENERGY_MIN  =  0;
POSITRON_ENERGY_MEAN =  0;
PROTON_ENERGY_MAX    =  0;
PROTON_ENERGY_MIN    =  0;
PROTON_ENERGY_MEAN   =  0;
NEUTRON_ENERGY_MAX   =  0;
NEUTRON_ENERGY_MIN   =  0;
NEUTRON_ENERGY_MEAN  =  0;
std::string dir = std::string(".");
iterator=0;
iterator_1=-1;
G4cout<< ANSI_GREEN<<"#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#"<< G4endl;
G4cout <<"G4LINAC VERSION 1.O: A GEANT4 BASED APPLICATION FOR MEDICAL LINEAR ACCELERATOR "<< G4endl;
G4cout<< "DEVELOPED BY DR. JAAFAR EL BAKKALI, BAHMEDJ@GMAIL.COM, TETOUAN-MOROCCO,  JULY 2017 "<< G4endl;
G4cout<<"MULTI_THREADING SUPPORT: YES "<< G4endl;
G4cout<<"#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#"<< G4endl;


}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
H5PhaseSpaceMerger::~H5PhaseSpaceMerger()
{

}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
int H5PhaseSpaceMerger::Get_Size_Of_PhspData_Dataset( std::string FileName)
{
int data_size=0;
try{

// LOAD PHASE SPACE HDF5-BASED FORMAT FILE
H5File file( FileName, H5F_ACC_RDONLY );
DataSet dataset = file.openDataSet( DatasetName );
// GET NUMBER OF DATA IN DATASET NAMED PhspData
data_size  = dataset.getSpace().getSimpleExtentNpoints();
}
// catch failure caused by the H5File operations
catch( FileIException error )
{
error.printError();
}
// catch failure caused by the DataSet operations
catch( DataSetIException error ){
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
return data_size;
}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/

int H5PhaseSpaceMerger::Get_Size_Of_EventData_Dataset( std::string FileName)
{
int data_size=0;
try{

// LOAD PHASE SPACE HDF5-BASED FORMAT FILE
H5File file( FileName, H5F_ACC_RDONLY );
DataSet dataset = file.openDataSet( DatasetName_event );
// GET NUMBER OF DATA IN DATASET NAMED PhspData
data_size  = dataset.getSpace().getSimpleExtentNpoints();
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
return data_size;

}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/

int H5PhaseSpaceMerger::Get_Size_Of_BeamData_Dataset( std::string FileName)
{

int data_size=0;
try{

     // LOAD PHASE SPACE HDF5-BASED FORMAT FILE
H5File file( FileName, H5F_ACC_RDONLY );
DataSet dataset = file.openDataSet( DatasetName );
    // GET NUMBER OF DATA IN DATASET NAMED PhspData
 data_size  = dataset.getSpace().getSimpleExtentNpoints();
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
return data_size;


}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/

int H5PhaseSpaceMerger::Get_Total_Size_Of_BeamData_Dataset()
{
int total=0;
for ( int i=0; i < this->NumberOfFiles;i++){

total=Get_Size_Of_BeamData_Dataset(std::to_string(i)+this->_filename);

}
return total;  

}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/

int H5PhaseSpaceMerger::Get_Total_Size_Of_PhspData_Dataset()
{
int total=0;

for ( int i=0; i< this->NumberOfFiles; i++){
  G4cout<<ANSI_GREEN << "\u21B3" <<" NUMBER OF PARTICLES STORED IN "<< std::to_string(i)+this->_filename <<"  IS  " <<Get_Size_Of_PhspData_Dataset(std::to_string(i)+this->_filename) <<  " ." << ANSI_RESET_COLOR<<G4endl; 

total+=Get_Size_Of_PhspData_Dataset(std::to_string(i)+this->_filename);

}
   G4cout<<ANSI_GREEN << "\u21B3"<<" TOTAL NUMBER OF PARTICLES IS :  " <<total<< " ." << ANSI_RESET_COLOR<<G4endl; 
NUMBER_OF_PARTICLES=total;
return total; 

 

}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/

int H5PhaseSpaceMerger::Get_Total_Size_Of_EventData_Dataset()
{
int total=0;

for ( int i=0; i< this->NumberOfFiles; i++){

total+=Get_Size_Of_EventData_Dataset(std::to_string(i)+this->_filename);
}
return total; 

}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/

void H5PhaseSpaceMerger::WRITE_PHASE_SPACE_FILE(std::string FILE_NAME)
 {
// the array of each length of multidimentional data.
hsize_t dim[1], dim_event[1], dim_histories[1];
dim_histories[0] = 1;
dim[0]=dim_total_phsp;
dim_event[0]  =   dim_total_event;
// the length of dim
int rank                = sizeof(dim) / sizeof(hsize_t);
int rank_event          = sizeof(dim_event) / sizeof(hsize_t);
int rank_histories      = sizeof(dim_histories) / sizeof(hsize_t);

// defining the datatype to pass HDF5
H5::CompType mtype(sizeof(PhspData));
mtype.insertMember(MEMBER_PART_PDGE,    HOFFSET(PhspData, PART_PDGE),     H5::PredType::NATIVE_INT   );
mtype.insertMember(MEMBER_PART_WEIGHT,  HOFFSET(PhspData, PART_WEIGHT),   H5::PredType::NATIVE_FLOAT);
mtype.insertMember(MEMBER_PART_POS_X,   HOFFSET(PhspData, PART_POS_X),    H5::PredType::NATIVE_FLOAT );
mtype.insertMember(MEMBER_PART_POS_Y,   HOFFSET(PhspData, PART_POS_Y),    H5::PredType::NATIVE_FLOAT );
mtype.insertMember(MEMBER_PART_POS_Z,   HOFFSET(PhspData, PART_POS_Z),    H5::PredType::NATIVE_FLOAT );
mtype.insertMember(MEMBER_PART_DIR_X,   HOFFSET(PhspData, PART_DIR_X),    H5::PredType::NATIVE_FLOAT );
mtype.insertMember(MEMBER_PART_DIR_Y,   HOFFSET(PhspData, PART_DIR_Y),    H5::PredType::NATIVE_FLOAT );
mtype.insertMember(MEMBER_PART_DIR_Z,   HOFFSET(PhspData, PART_DIR_Z),    H5::PredType::NATIVE_FLOAT );
mtype.insertMember(MEMBER_PART_KINETIC, HOFFSET(PhspData, PART_KINETIC),  H5::PredType::NATIVE_FLOAT );
H5::CompType mtype_event(sizeof(EventData));
mtype_event.insertMember(MEMBER_EVENTID,  HOFFSET(EventData, EVENT_ID),                  H5::PredType::NATIVE_INT);
mtype_event.insertMember(MEMBER_ENTERIES, HOFFSET(EventData, NUMBER_OF_ENTRIES),         H5::PredType::NATIVE_INT);
H5::CompType mtype_histories(sizeof(BeamData));
mtype_histories.insertMember(MEMBER_HISTORIES,  HOFFSET(BeamData, NUMBER_OF_HISORIES),   H5::PredType::NATIVE_INT);
mtype_histories.insertMember(MEMBER_Z_STOP,     HOFFSET(BeamData, Z_STOP),               H5::PredType::NATIVE_FLOAT);
mtype_histories.insertMember(MEMBER_DATA_ID,     HOFFSET(BeamData, DATA_ID),               H5::PredType::NATIVE_INT);
    // preparation of a dataset and a file.
H5::DataSpace space(rank, dim);
H5::DataSpace space_event(rank_event, dim_event);
H5::DataSpace space_histories(rank_histories, dim_histories);
H5::H5File *file                 = new H5::H5File(FILE_NAME, H5F_ACC_TRUNC	);
H5::DataSet *dataset             = new H5::DataSet(file->createDataSet(DatasetName, mtype, space));
H5::DataSet *dataset_event       = new H5::DataSet(file->createDataSet(DatasetName_event, mtype_event, space_event));
H5::DataSet *dataset_histories   = new H5::DataSet(file->createDataSet(DatasetName_histories, mtype_histories, space_histories));
dataset_histories->write(myTotalBeamData, mtype_histories);
dataset_event ->write(myTotalEventData,  mtype_event);
dataset->write(myTotalPhspData, mtype);
    delete[] myTotalEventData;
    delete   dataset_event;
    delete   dataset_histories;
    delete   dataset;
    delete   file;
 }
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/

void H5PhaseSpaceMerger::READ_PHASE_SPACE_FILE_EventData_DataSet(std::string FILE_NAME)
 {
try{
   // DECLARATION OF STRINGS OF MEMBERS OF DATASET NAMED "EventData"
      H5File file(  FILE_NAME, H5F_ACC_RDONLY );
      DataSet dataset_event = file.openDataSet( DatasetName_event );
      H5::CompType mtype_event( sizeof(EventData) );
      // GET NUMBER OF DATA IN DATASET NAMED EventData
      G4int data_event_size=dataset_event.getSpace().getSimpleExtentNpoints();
      mtype_event.insertMember(MEMBER_ENTERIES,     HOFFSET(EventData, NUMBER_OF_ENTRIES),      H5::PredType::NATIVE_INT);
      mtype_event.insertMember(MEMBER_EVENTID,      HOFFSET(EventData, EVENT_ID),               H5::PredType::NATIVE_INT);
      dataset_event.read( myEventData, mtype_event );
     for (int i=0; i<data_event_size; i++){

     myTotalEventData[iterator].EVENT_ID           = myEventData[i].EVENT_ID  ;
     myTotalEventData[iterator].NUMBER_OF_ENTRIES  =  myEventData[i].NUMBER_OF_ENTRIES;

iterator++;
} 

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
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/

void H5PhaseSpaceMerger::READ_PHASE_SPACE_FILE_BeamData_DataSet(std::string FILE_NAME)
 {
try{
     H5File file( FILE_NAME, H5F_ACC_RDONLY );
     DataSet dataset_histories = file.openDataSet( DatasetName_histories );
     H5::CompType mtype_histories( sizeof(BeamData) );
     mtype_histories.insertMember(MEMBER_HISTORIES,     HOFFSET(BeamData, NUMBER_OF_HISORIES),      H5::PredType::NATIVE_INT);
     mtype_histories.insertMember(MEMBER_Z_STOP,        HOFFSET(BeamData, Z_STOP),                  H5::PredType::NATIVE_FLOAT);
     dataset_histories.read( myBeamData, mtype_histories );
     myTotalBeamData[0].NUMBER_OF_HISORIES          +=   myBeamData[0].NUMBER_OF_HISORIES;
     myTotalBeamData[0].Z_STOP   =   myBeamData[0].Z_STOP;
    this->Z_STOP=myTotalBeamData[0].Z_STOP/mm;

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
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/

void H5PhaseSpaceMerger::READ_PHASE_SPACE_FILE_PhspData_DataSet(std::string FILE_NAME,  int inc)
{
   
try{ 
     // LOAD PHASE SPACE HDF5-BASED FORMAT FILE
     H5File file(FILE_NAME, H5F_ACC_RDONLY );
     DataSet dataset = file.openDataSet( DatasetName );
     H5::CompType mtype2( sizeof(PhspData) );
    // GET NUMBER OF DATA IN DATASET NAMED PhspData
    G4int data_size  = dataset.getSpace().getSimpleExtentNpoints();
    mtype2.insertMember(MEMBER_PART_WEIGHT,  HOFFSET(PhspData, PART_WEIGHT),   H5::PredType::NATIVE_FLOAT);
    mtype2.insertMember(MEMBER_PART_POS_X,   HOFFSET(PhspData, PART_POS_X),    H5::PredType::NATIVE_FLOAT);
    mtype2.insertMember(MEMBER_PART_PDGE,    HOFFSET(PhspData, PART_PDGE),     H5::PredType::NATIVE_INT);
    mtype2.insertMember(MEMBER_PART_POS_Y,   HOFFSET(PhspData, PART_POS_Y),    H5::PredType::NATIVE_FLOAT);
    mtype2.insertMember(MEMBER_PART_POS_Z,   HOFFSET(PhspData, PART_POS_Z),    H5::PredType::NATIVE_FLOAT);
    mtype2.insertMember(MEMBER_PART_DIR_X,   HOFFSET(PhspData, PART_DIR_X),    H5::PredType::NATIVE_FLOAT);
    mtype2.insertMember(MEMBER_PART_DIR_Y,   HOFFSET(PhspData, PART_DIR_Y),    H5::PredType::NATIVE_FLOAT);
    mtype2.insertMember(MEMBER_PART_DIR_Z,   HOFFSET(PhspData, PART_DIR_Z),    H5::PredType::NATIVE_FLOAT);
    mtype2.insertMember(MEMBER_PART_KINETIC, HOFFSET(PhspData, PART_KINETIC),  H5::PredType::NATIVE_FLOAT);
    dataset.read( myPhspData, mtype2 );
for (int i=0; i<data_size; i++){
iterator_1++;
        myTotalPhspData[iterator_1]. PART_PDGE   = myPhspData[ i]. PART_PDGE;
         myTotalPhspData[iterator_1]. PART_WEIGHT= myPhspData[ i]. PART_WEIGHT;
        myTotalPhspData[iterator_1]. PART_KINETIC= myPhspData[ i]. PART_KINETIC;
        myTotalPhspData[iterator_1]. PART_POS_X = myPhspData[ i]. PART_POS_X;
        myTotalPhspData[iterator_1]. PART_POS_Y= myPhspData[ i]. PART_POS_Y;
        myTotalPhspData[iterator_1]. PART_POS_Z= myPhspData[ i]. PART_POS_Z;
        myTotalPhspData[iterator_1]. PART_DIR_X = myPhspData[ i]. PART_DIR_X;
      myTotalPhspData[iterator_1]. PART_DIR_Y = myPhspData[ i]. PART_DIR_Y;
     myTotalPhspData[iterator_1]. PART_DIR_Z =  myPhspData[ i]. PART_DIR_Z;
}

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
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
int  H5PhaseSpaceMerger::Get_DATA_ID( std::string _filename){

H5File file( _filename, H5F_ACC_RDONLY );
     DataSet dataset_histories = file.openDataSet( DatasetName_histories );
     H5::CompType mtype_histories( sizeof(BeamData) );
     mtype_histories.insertMember(MEMBER_HISTORIES,     HOFFSET(BeamData, NUMBER_OF_HISORIES),      H5::PredType::NATIVE_INT);
     mtype_histories.insertMember(MEMBER_Z_STOP,        HOFFSET(BeamData, Z_STOP),                  H5::PredType::NATIVE_FLOAT);
 mtype_histories.insertMember(MEMBER_DATA_ID,        HOFFSET(BeamData, DATA_ID),                  H5::PredType::NATIVE_INT);
     dataset_histories.read( myBeamData, mtype_histories );
return myBeamData[0].DATA_ID;
}
void H5PhaseSpaceMerger::MergeH5PhaseSpaceFiles(){
G4RunManager* runManager = G4RunManager::GetRunManager();
DetectorConstruction* pDetectorConstruction = (DetectorConstruction*)(runManager->GetUserDetectorConstruction()); 
this-> _filename= pDetectorConstruction-> H5_PHASE_SPACE_NAME_WITHOUT_EXTENSION+".h5";
this->H5PHASE_SPACE_NAME_WITHOUT_EXTENSION=pDetectorConstruction->H5_PHASE_SPACE_NAME_WITHOUT_EXTENSION;
this->H5PHASE_SPACE_FILE_EXTENSION=".h5";
this->H5PHASE_SPACE_SUMMARY_EXTENSION=".summary";
this->NumberOfFiles= pDetectorConstruction->NUMBER_OF_THREADS;
dim_total_phsp=Get_Total_Size_Of_PhspData_Dataset();
dim_total_event= Get_Total_Size_Of_EventData_Dataset();
myTotalPhspData = new PhspData[dim_total_phsp];
myTotalEventData = new EventData[dim_total_event];








for (int kk=0; kk<this->NumberOfFiles; kk++){


for (int i=0; i<this->NumberOfFiles; i++)
{
int  data_id= Get_DATA_ID(std::to_string(i)+_filename);


if (data_id==ll) {
ll++;
//G4cout<<" File :" << std::to_string(i)+_filename<< " data id "<< data_id<<"  ll : " << ll <<G4endl;
int size_PhspData=Get_Size_Of_PhspData_Dataset(std::to_string(i)+_filename);
int size_EventData=Get_Size_Of_EventData_Dataset(std::to_string(i)+_filename);
//

myEventData = new EventData[size_EventData];
//
myPhspData = new PhspData[size_PhspData];
 
if (size_PhspData > 0){
READ_PHASE_SPACE_FILE_BeamData_DataSet(std::to_string(i)+_filename);

READ_PHASE_SPACE_FILE_PhspData_DataSet(std::to_string(i)+_filename,incr_PhspData);
//
READ_PHASE_SPACE_FILE_EventData_DataSet(std::to_string(i)+_filename);
}
}


}

}


//
   


TOTAL_NUMBER_OF_HISTORIES=myTotalBeamData[0].NUMBER_OF_HISORIES ;
   
// SHOW NUMBER OF TOTAL HISTORIES STORED IN A MASTER H5_PHASE_SPACE FILE
G4cout<<ANSI_GREEN << "\u21B3"<<" TOTAL NUMBER OF HISTORIES IS :  " <<TOTAL_NUMBER_OF_HISTORIES<< " ." << ANSI_RESET_COLOR<<G4endl; 

// WRITTING A MASTER  H5_PHASE_SPACE FILE
WRITE_PHASE_SPACE_FILE(H5PHASE_SPACE_NAME_WITHOUT_EXTENSION+H5PHASE_SPACE_FILE_EXTENSION);


//
 G4cout<< ANSI_GREEN << "\u21B3"<< " ALL H5_PHASE_SPACE FILES HAVE BEEN SUCCESSFULY MERGED INTO A SINGLE ONE CALLED " <<this->H5PHASE_SPACE_NAME_WITHOUT_EXTENSION+this->H5PHASE_SPACE_FILE_EXTENSION<< " ." << ANSI_RESET_COLOR<<G4endl; 

for (int i=0; i<this->NumberOfFiles; i++)
{
std::string file = std::to_string(i)+_filename;
G4cout<< ANSI_GREEN << "\u21B3"<< " ROMOVING H5PHASE_SPACE : " << file.c_str()<< " ." << ANSI_RESET_COLOR<<G4endl; 
 std::remove(file.c_str());

}
 
GetStatistics();
//

//PRINT SUMMARY OF SIMULATION IN A FILE.
SUMMARY();
G4cout<< ANSI_GREEN << "\u21B3"<< " MERGING TASK HAS BEEN FINISHED SUCCESSFULY ." << ANSI_RESET_COLOR<<G4endl; 
G4cout<<ANSI_GREEN <<"#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#"<< ANSI_RESET_COLOR<< G4endl;
}


/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void H5PhaseSpaceMerger::SUMMARY()
{

time_t theTime= time(NULL);
struct std::tm* aTime = localtime(&theTime);


ofstream Summary_file;
//G4String fileName="PHASE_SPACE.summary";
//
G4String fileName=this->H5PHASE_SPACE_NAME_WITHOUT_EXTENSION+this->H5PHASE_SPACE_SUMMARY_EXTENSION;
Summary_file.open(fileName, std::ios::out);
Summary_file<<"#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#"<< G4endl;
Summary_file <<"G4LINAC VERSION 1.O: A GEANT4 BASED APPLICATION FOR MEDICAL LINEAR ACCELERATOR "<< G4endl;
Summary_file << "DEVELOPED BY DR. JAAFAR EL BAKKALI, BAHMEDJ@GMAIL.COM, TETOUAN-MOROCCO,  JULY 2017 "<< G4endl;
Summary_file <<"#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#"<< G4endl;
Summary_file <<"\u21B3"<<"    @DATE_OF_CREATION: "<<asctime(aTime);          
Summary_file <<"\u21B3"<<"    @PHASE_SPACE_NAME: "<<H5PHASE_SPACE_NAME_WITHOUT_EXTENSION+H5PHASE_SPACE_FILE_EXTENSION<<G4endl;
Summary_file<<"\u21B3" <<"    @Z_STOP: " <<this->Z_STOP<<" mm." <<G4endl;
Summary_file <<"\u21B3"<<"    @TOTAL_NUMBER_OF_SIMULATED_HISTORIES: " <<TOTAL_NUMBER_OF_HISTORIES <<G4endl;
Summary_file <<"\u21B3"<<"    @TOTAL_NUMBER_OF_PARTICLES	: "   << NUMBER_OF_PARTICLES  << G4endl;
if (NUMBER_OF_PHOTONS >   0) Summary_file<<"\u21B3"<<"    @TOTAL_NUMBER_OF_PHOTONS: "   << NUMBER_OF_PHOTONS  << G4endl;
if (NUMBER_OF_ELECTRONS > 0) Summary_file<<"\u21B3"<<"    @TOTAL_NUMBER_OF_ELECTRONS: " << NUMBER_OF_ELECTRONS << G4endl;
if (NUMBER_OF_POSITRONS > 0) Summary_file<<"\u21B3"<<"    @TOTAL_NUMBER_OF_POSITRONS: " << NUMBER_OF_POSITRONS << G4endl;
if (NUMBER_OF_NEUTRONS >  0) Summary_file<<"\u21B3"<<"    @TOTAL_NUMBER_OF_NEUTRONS: "  <<NUMBER_OF_NEUTRONS <<G4endl;
if (NUMBER_OF_PROTONS >   0) Summary_file<<"\u21B3"<<"    @TOTAL_NUMBER_OF_PROTONS: " << NUMBER_OF_PROTONS <<G4endl;
if (NUMBER_OF_PHOTONS >   0) Summary_file<<"\u21B3"<<"    @PHOTONS_PERCENT: "<<100*(NUMBER_OF_PHOTONS/ (double)NUMBER_OF_PARTICLES)<<" %"<<G4endl;
if (NUMBER_OF_ELECTRONS > 0) Summary_file<<"\u21B3"<<"    @ELECTRONS_PERCENT: " <<100*(NUMBER_OF_ELECTRONS/(double)NUMBER_OF_PARTICLES) <<" %" <<G4endl;
if (NUMBER_OF_POSITRONS > 0) Summary_file<<"\u21B3"<<"    @POSITRONS_PERCENT: " <<100*(NUMBER_OF_POSITRONS/(double)NUMBER_OF_PARTICLES) <<" %" <<G4endl;
if (NUMBER_OF_PROTONS >   0) Summary_file<<"\u21B3"<<"    @PROTONS_PERCENT: "  << 100*(NUMBER_OF_PROTONS/(double)NUMBER_OF_PARTICLES)   <<" %"<<G4endl;
if (NUMBER_OF_NEUTRONS >  0) Summary_file<<"\u21B3"<<"    @NEUTRONS_PERCENT: " << 100*(NUMBER_OF_NEUTRONS/(double)NUMBER_OF_PARTICLES)  <<" %"<<G4endl;
Summary_file<<" ____________________________________________________________________________________________________________" <<G4endl;
if (NUMBER_OF_PHOTONS >   0)
{
Summary_file<<"\u21B3"<<"    @PHOTONS_MAX_ENERGY: "  << PHOTON_ENERGY_MAX <<" MeV" <<G4endl;
Summary_file<<"\u21B3"<<"    @PHOTONS_MIN_ENERGY: "  << PHOTON_ENERGY_MIN <<" MeV" <<G4endl;
Summary_file<<"\u21B3"<<"    @PHOTONS_MEAN_ENERGY: " << PHOTON_ENERGY_MEAN/NUMBER_OF_PHOTONS<<" MeV"<<G4endl;
Summary_file<<" ____________________________________________________________________________________________________________" <<G4endl;
}
if (NUMBER_OF_ELECTRONS > 0) 
{
Summary_file<<"\u21B3"<<"    @ELECTRONS_MAX_ENERGY: "<< ELECTRON_ENERGY_MAX <<" MeV" <<G4endl;
Summary_file<<"\u21B3"<<"    @ELECTRONS_MIN_ENERGY: " << ELECTRON_ENERGY_MIN <<" MeV" <<G4endl;
Summary_file<<"\u21B3"<<"    @ELECTRONS_MEAN_ENERGY: " << ELECTRON_ENERGY_MEAN/NUMBER_OF_ELECTRONS<<" MeV"<<G4endl;
Summary_file<<" ____________________________________________________________________________________________________________" <<G4endl;
}
if (NUMBER_OF_POSITRONS > 0) 
{
Summary_file<<"\u21B3"<<"    @POSITRONS_MAX_ENERGY: " << POSITRON_ENERGY_MAX<<" MeV"<<G4endl;
Summary_file<<"\u21B3"<<"    @POSITRONS_MIN_ENERGY: " << POSITRON_ENERGY_MIN<<" MeV"<<G4endl;
Summary_file<<"\u21B3"<<"    @POSITRONS_MEAN_ENERGY: " << POSITRON_ENERGY_MEAN /NUMBER_OF_POSITRONS <<" MeV"   <<G4endl;
Summary_file<<" ____________________________________________________________________________________________________________" <<G4endl;
}
if (NUMBER_OF_PROTONS >   0)    
{      
Summary_file<<"\u21B3"<<"    @PROTONS_MAX_ENERGY: "<< PROTON_ENERGY_MAX<<" MeV"  <<G4endl;
Summary_file<<"\u21B3"<<"    @PROTONS_MIN_ENERGY: "<< PROTON_ENERGY_MIN<<" MeV"  <<G4endl;
Summary_file<<"\u21B3"<<"    @PROTONS_MEAN_ENERGY: "<< PROTON_ENERGY_MEAN/NUMBER_OF_PROTONS <<" MeV"<<G4endl;
Summary_file<<" ____________________________________________________________________________________________________________" <<G4endl;
}
if (NUMBER_OF_NEUTRONS > 0) 
{
Summary_file<<"\u21B3"<<"   @NEUTRONS_MAX_ENERGY: " << NEUTRON_ENERGY_MAX <<" MeV"<<G4endl;
Summary_file<<"\u21B3"<<"   @NEUTRONS_MIN_ENERGY: " << NEUTRON_ENERGY_MIN<<" MeV" <<G4endl;
Summary_file<<"\u21B3"<<"   @NEUTRONS_MEAN_ENERGY: "  << NEUTRON_ENERGY_MEAN/NUMBER_OF_NEUTRONS<<" MeV" <<G4endl;
Summary_file<<"\u21B3"<<" ____________________________________________________________________________________________________________" <<G4endl;
}
if (NUMBER_OF_PHOTONS >   0)
{
Summary_file<<"\u21B3"<<"    @PHOTONS_MAX_WEIGHT: "  << PHOTON_WEIGHT_MAX <<" " <<G4endl;
Summary_file<<"\u21B3"<<"    @PHOTONS_MIN_WEIGHT: "  << PHOTON_WEIGHT_MIN <<"" <<G4endl;
Summary_file<<"\u21B3"<<"    @PHOTONS_MEAN_WEIGHT: " << PHOTON_WEIGHT_MEAN/NUMBER_OF_PHOTONS<<""<<G4endl;
Summary_file<<" ____________________________________________________________________________________________________________" <<G4endl;
}

if (NUMBER_OF_ELECTRONS >   0)
{
Summary_file<<"\u21B3"<<"    @ELECTRONS_MAX_WEIGHT: "  << ELECTRONS_WEIGHT_MAX <<" " <<G4endl;
Summary_file<<"\u21B3"<<"    @ELECTRONS_MIN_WEIGHT: "  << ELECTRONS_WEIGHT_MIN <<"" <<G4endl;
Summary_file<<"\u21B3"<<"    @ELECTRONS_MEAN_WEIGHT: " << ELECTRONS_WEIGHT_MEAN/NUMBER_OF_ELECTRONS<<""<<G4endl;
Summary_file<<" ____________________________________________________________________________________________________________" <<G4endl;
}


if (NUMBER_OF_POSITRONS >   0)
{
Summary_file<<"\u21B3"<<"    @POSITRONS_MAX_WEIGHT: "  << POSITRONS_WEIGHT_MAX <<" " <<G4endl;
Summary_file<<"\u21B3"<<"    @POSITRONS_MIN_WEIGHT: "  << POSITRONS_WEIGHT_MIN <<"" <<G4endl;
Summary_file<<"\u21B3"<<"    @POSITRONS_MEAN_WEIGHT: " << POSITRONS_WEIGHT_MEAN/NUMBER_OF_POSITRONS<<""<<G4endl;
Summary_file<<" ____________________________________________________________________________________________________________" <<G4endl;
}
Summary_file.close();
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void H5PhaseSpaceMerger::PHOTONS_ENERGY(G4double Energy )
{
G4double TEMP = Energy;
if (PHOTON_ENERGY_MAX < TEMP ) PHOTON_ENERGY_MAX  = Energy;
if (PHOTON_ENERGY_MAX > TEMP ) PHOTON_ENERGY_MIN  = Energy;
/*.........................*/  PHOTON_ENERGY_MEAN = PHOTON_ENERGY_MEAN+Energy;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void H5PhaseSpaceMerger::ELECTRONS_ENERGY(G4double Energy )
{
G4double TEMP = Energy;
if (ELECTRON_ENERGY_MAX < TEMP ) ELECTRON_ENERGY_MAX  = Energy;
if (ELECTRON_ENERGY_MAX > TEMP ) ELECTRON_ENERGY_MIN  = Energy;
/*.........................*/    ELECTRON_ENERGY_MEAN = ELECTRON_ENERGY_MEAN+Energy;
auto idthread = std::to_string(G4Threading::G4GetThreadId()); 
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void H5PhaseSpaceMerger::POSITRONS_ENERGY(G4double Energy )
{
G4double TEMP = Energy;
if (POSITRON_ENERGY_MAX < TEMP ) POSITRON_ENERGY_MAX  = Energy;
if (POSITRON_ENERGY_MAX > TEMP ) POSITRON_ENERGY_MIN  = Energy;
/*............................*/ POSITRON_ENERGY_MEAN = POSITRON_ENERGY_MEAN+Energy;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void H5PhaseSpaceMerger::NEUTRONS_ENERGY(G4double Energy )
{
G4double TEMP = Energy;
if (NEUTRON_ENERGY_MAX < TEMP )  NEUTRON_ENERGY_MAX   = Energy;
if (NEUTRON_ENERGY_MAX > TEMP )  NEUTRON_ENERGY_MIN   = Energy;
/*............................*/ NEUTRON_ENERGY_MEAN  = NEUTRON_ENERGY_MEAN+Energy;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void H5PhaseSpaceMerger::PROTONS_ENERGY(G4double Energy )
{
G4double TEMP = Energy;
if (PROTON_ENERGY_MAX < TEMP )   PROTON_ENERGY_MAX    = Energy;
if (PROTON_ENERGY_MAX > TEMP )   PROTON_ENERGY_MIN    = Energy;
/*............................*/ PROTON_ENERGY_MEAN   = PROTON_ENERGY_MEAN+Energy;
}



/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void H5PhaseSpaceMerger::PHOTON_WEIGHT(G4double Weight )
{
G4double TEMP = Weight;
if (PHOTON_WEIGHT_MAX < TEMP ) PHOTON_WEIGHT_MAX  = Weight;
if (PHOTON_WEIGHT_MAX > TEMP ) PHOTON_WEIGHT_MIN  = Weight;
/*............................*/ PHOTON_WEIGHT_MEAN = PHOTON_WEIGHT_MEAN+Weight;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/


void H5PhaseSpaceMerger::ELECTRONS_WEIGHT(G4double Weight )
{
G4double TEMP = Weight;
if (ELECTRONS_WEIGHT_MAX < TEMP ) ELECTRONS_WEIGHT_MAX  = Weight;
if (ELECTRONS_WEIGHT_MAX > TEMP ) ELECTRONS_WEIGHT_MIN  = Weight;
/*............................*/ ELECTRONS_WEIGHT_MEAN = ELECTRONS_WEIGHT_MEAN+Weight;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/



void H5PhaseSpaceMerger::POSITRONS_WEIGHT(G4double Weight )
{
G4double TEMP = Weight;
if (POSITRONS_WEIGHT_MAX < TEMP ) POSITRONS_WEIGHT_MAX  = Weight;
if (POSITRONS_WEIGHT_MAX > TEMP ) POSITRONS_WEIGHT_MIN  = Weight;
/*............................*/ POSITRONS_WEIGHT_MEAN = POSITRONS_WEIGHT_MEAN+Weight;
}

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void H5PhaseSpaceMerger::GetStatistics()
{// void

try{ 

for (int i=0; i<NUMBER_OF_PARTICLES; i++){

tmp.PART_KINETIC =  myTotalPhspData[i]. PART_KINETIC;
tmp.PART_PDGE =  myTotalPhspData[i]. PART_PDGE;
tmp.PART_WEIGHT =  myTotalPhspData[i]. PART_WEIGHT;
switch(tmp.PART_PDGE)
{
case 22:
// GAMMA

NUMBER_OF_PHOTONS++;
PHOTONS_ENERGY(tmp.PART_KINETIC);
PHOTON_WEIGHT(tmp.PART_WEIGHT);
break;
case 11:
// ELECTRON
NUMBER_OF_ELECTRONS++;
ELECTRONS_ENERGY(tmp.PART_KINETIC);
ELECTRONS_WEIGHT(tmp.PART_WEIGHT);
break;
case -11:
// POSITRON
NUMBER_OF_POSITRONS++;
POSITRONS_ENERGY(tmp.PART_KINETIC);
POSITRONS_WEIGHT(tmp.PART_WEIGHT);
break;
case 2112:
// NEUTRON
NUMBER_OF_PROTONS++;
PROTONS_ENERGY(tmp.PART_KINETIC);
break;
case 2122:
// PROTON
NUMBER_OF_NEUTRONS++;
NEUTRONS_ENERGY(tmp.PART_KINETIC);
break;
default:

G4cout << "ERROR:  PARTICLE CODE NOT SUPPORTED  . "<< G4endl;

  }
       
}
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
delete [] myTotalPhspData;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
