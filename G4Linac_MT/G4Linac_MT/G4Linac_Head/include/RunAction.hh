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
#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=# */
#ifndef RunAction_h
#define RunAction_h 1
#include <ctime>
#include "G4UserRunAction.hh"
#include "globals.hh"

class G4Run;


class RunAction : public G4UserRunAction
{
  public:
RunAction();
~RunAction();
void BeginOfRunAction(const G4Run*);
void EndOfRunAction(const G4Run*);
double diffclock(clock_t ,clock_t );
void READ_BEAM_DATA(std::string );
void READ_EVENT_DATA(std::string );
void READ_PHSP_DATA(std::string );
void WRITE_PHASE_SPACE_FILE(std::string);
void GetStatistics();
void SUMMARY();
void PHOTONS_ENERGY(G4double);
void ELECTRONS_ENERGY(G4double);
void POSITRONS_ENERGY(G4double);
void PROTONS_ENERGY(G4double);
void NEUTRONS_ENERGY(G4double);
void PHOTON_WEIGHT(G4double);
void ELECTRONS_WEIGHT(G4double);
void POSITRONS_WEIGHT(G4double);
void PROTONS_WEIGHT(G4double);
void NEUTRONS_WEIGHT(G4double);
unsigned short int                 NumberOfFiles;
unsigned int                       TOTAL_NUMBER_OF_HISTORIES,
                                   ITERATOR,
                                   ITERATOR_1,
                                   incr_PhspData,
                                   incr_EventData,
                                   NUMBER_OF_PHOTONS             ,
                                   NUMBER_OF_ELECTRONS           , 
                                   NUMBER_OF_POSITRONS           ,
                                   NUMBER_OF_PROTONS             ,
                                   NUMBER_OF_NEUTRONS            ,
                                   NUMBER_OF_PARTICLES           ,
                                   NUMBER_OF_ENTRIES             ,
                                   NUMBER_OF_ACTIVE_EVENTS       ,
                                   EVENT_ID                      ,                   
                                   TRACK_ID                      ;
G4float                            Z_STOP;
std::string                        H5PHASE_SPACE_NAME_WITHOUT_EXTENSION,
                                   H5PHASE_SPACE_FILE_EXTENSION,
                                   H5PHASE_SPACE_SUMMARY_EXTENSION;

G4double                           ELECTRON_ENERGY_MAX           ,
                                   ELECTRON_ENERGY_MIN           ,
                                   ELECTRON_ENERGY_MEAN          ,
                                   ELECTRONS_WEIGHT_MAX          ,
                                   ELECTRONS_WEIGHT_MIN          ,
                                   ELECTRONS_WEIGHT_MEAN         ,
                                   PHOTON_ENERGY_MAX             ,
                                   PHOTON_ENERGY_MIN             ,
                                   PHOTON_ENERGY_MEAN            ,
                                   POSITRON_ENERGY_MAX           ,
                                   POSITRON_ENERGY_MIN           ,
                                   POSITRON_ENERGY_MEAN          ,
                                   POSITRONS_WEIGHT_MAX          ,
                                   POSITRONS_WEIGHT_MIN          ,
                                   POSITRONS_WEIGHT_MEAN         ,
                                   PROTON_ENERGY_MAX             ,
                                   PROTON_ENERGY_MIN             ,
                                   PROTON_ENERGY_MEAN            ,
                                   PROTON_WEIGHT_MAX             ,
                                   PROTON_WEIGHT_MIN             ,
                                   PROTON_WEIGHT_MEAN            ,
                                   NEUTRON_ENERGY_MAX            ,
                                   NEUTRON_ENERGY_MIN            ,
                                   NEUTRON_ENERGY_MEAN           ,  
                                   NEUTRON_WEIGHT_MAX            ,
                                   NEUTRON_WEIGHT_MIN            ,
                                   NEUTRON_WEIGHT_MEAN           ,  
                                   PHOTON_WEIGHT_MAX             ,
                                   PHOTON_WEIGHT_MIN             , 
                                   PHOTON_WEIGHT_MEAN            ;
typedef struct
{
int    PART_PDGE;
double  PART_WEIGHT
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
unsigned int
       EVENT_ID,
       NUMBER_OF_ENTRIES;

}EventData;

typedef struct
{
unsigned int    
        NUMBER_OF_HISTORIES;
     unsigned int    NUMBER_OF_ACTIVE_EVENTS;
double     
        Z_STOP;

}BeamData;
//structure variables
PhspData * RAM_PhspData;
EventData * RAM_EventData;
BeamData myTotalBeamData[1],myBeamData[1];
std::vector<PhspData>   myPhspData_Vector;
std::vector<EventData>   myEventData_Vector;
PhspData tmp;
//string variables
std::string H5PhaseSpaceFileName;
//clock variables
clock_t begin;
clock_t end;
//double variables
double elapsed_time;
};

#endif
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
