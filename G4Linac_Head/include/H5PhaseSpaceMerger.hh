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
#ifndef H5PhaseSpaceMerger_hh
#define H5PhaseSpaceMerger_hh 1

#include "G4ThreeVector.hh"
#include "globals.hh"

#include <set>
#include <vector>
#include <map>
class G4Event;
class G4Step;
class G4LogicalVolume;
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/

class H5PhaseSpaceMerger
{
private:
  static H5PhaseSpaceMerger *theInstance;
  H5PhaseSpaceMerger();

public:
  ~H5PhaseSpaceMerger();

public:
static H5PhaseSpaceMerger * GetInstance();
int  Get_Size_Of_PhspData_Dataset( std::string FileName);
int  Get_Size_Of_EventData_Dataset( std::string FileName);
int  Get_Size_Of_BeamData_Dataset( std::string FileName);
int  Get_Total_Size_Of_BeamData_Dataset();
int  Get_Total_Size_Of_PhspData_Dataset();
int  Get_Total_Size_Of_EventData_Dataset();
void WRITE_PHASE_SPACE_FILE(std::string FILE_NAME);
void READ_PHASE_SPACE_FILE_EventData_DataSet(std::string FILE_NAME);
void READ_PHASE_SPACE_FILE_BeamData_DataSet(std::string FILE_NAME);
void READ_PHASE_SPACE_FILE_PhspData_DataSet(std::string FILE_NAME, int inc );
void MergeH5PhaseSpaceFiles();
void CreateSingleH5PhaseSpaceFile(std::string FILE_NAME );
void GetStatistics();
void SUMMARY();
void PHOTONS_ENERGY(G4double);
void ELECTRONS_ENERGY(G4double);
void POSITRONS_ENERGY(G4double);
void PROTONS_ENERGY(G4double);
void NEUTRONS_ENERGY(G4double);
void PHOTON_WEIGHT(G4double Weight );
void ELECTRONS_WEIGHT(G4double Weight );
void POSITRONS_WEIGHT(G4double Weight );
int  Get_DATA_ID( std::string _filename);
typedef struct
{
int   threadid;
int  dataid;

}datamap;
typedef struct
{
int    PART_PDGE;
float  PART_WEIGHT
      ,PART_POS_X
      ,PART_POS_Y
      ,PART_POS_Z
      ,PART_DIR_X
      ,PART_DIR_Y
      ,PART_DIR_Z
      ,PART_KINETIC;
}PhspData;

typedef struct
{
G4int  EVENT_ID,
       NUMBER_OF_ENTRIES;


}EventData;

 typedef struct
  {
     G4int    NUMBER_OF_HISORIES;
     G4float     Z_STOP;
G4int DATA_ID;

  }BeamData;
 //
  PhspData tmp;
  EventData tmp_event;
  //
  BeamData  myBeamData[1];

PhspData *  myPhspData ;
datamap *mydatamap;

EventData *   myEventData ;
G4String _filename;
private:
std::vector<std::string> ArrayFileName;
std::vector<std::string> ArrayH5PhaseSpaceFilesName;
int NumberOfFiles;
int TOTAL_NUMBER_OF_HISTORIES;
int iterator;
int iterator_1;
int incr_PhspData;
int incr_EventData;
G4float     Z_STOP;
std::string H5PHASE_SPACE_NAME_WITHOUT_EXTENSION;
std::string H5PHASE_SPACE_FILE_EXTENSION;
std::string H5PHASE_SPACE_SUMMARY_EXTENSION;
int 
                        NUMBER_OF_PHOTONS                ,
                   NUMBER_OF_ELECTRONS                ,
                   NUMBER_OF_POSITRONS                ,
                   NUMBER_OF_PROTONS                  ,
                   NUMBER_OF_NEUTRONS                 ,
                   NUMBER_OF_PARTICLES                ,

                   NUMBER_OF_ENTRIES                  ,
                   NUMBER_OF_ACTIVE_EVENT             ,
                                  EVENT_ID                           ,                   
                                  TRACK_ID              ;

G4float                            ELECTRON_ENERGY_MAX  ,
                                   ELECTRON_ENERGY_MIN  ,
                                   ELECTRON_ENERGY_MEAN ,
                                   ELECTRONS_WEIGHT_MAX  ,
                                   ELECTRONS_WEIGHT_MIN  ,
                                   ELECTRONS_WEIGHT_MEAN ,
                                   PHOTON_ENERGY_MAX    ,
                                   PHOTON_ENERGY_MIN    ,
                                   PHOTON_ENERGY_MEAN   ,
                                   POSITRON_ENERGY_MAX  ,
                                   POSITRON_ENERGY_MIN  ,
                                   POSITRON_ENERGY_MEAN ,
                                   POSITRONS_WEIGHT_MAX  ,
                                   POSITRONS_WEIGHT_MIN  ,
                                   POSITRONS_WEIGHT_MEAN ,
                                   PROTON_ENERGY_MAX    ,
                                   PROTON_ENERGY_MIN    ,
                                   PROTON_ENERGY_MEAN   ,
                                   NEUTRON_ENERGY_MAX   ,
                                   NEUTRON_ENERGY_MIN   ,
                                   NEUTRON_ENERGY_MEAN  ,  
                                   PHOTON_WEIGHT_MAX    ,
                                   PHOTON_WEIGHT_MIN    , 
                                   PHOTON_WEIGHT_MEAN   ;
};

#endif
