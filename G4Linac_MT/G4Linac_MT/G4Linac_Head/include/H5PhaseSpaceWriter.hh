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
#ifndef H5PhaseSpaceWriter_h
#define H5PhaseSpaceWriter_h 1
#include "G4ThreeVector.hh"
#include "G4VSensitiveDetector.hh"
#include "G4VTouchable.hh"
#include <vector>
#include "G4Threading.hh"
#include "G4ThreadLocalSingleton.hh"
#include "G4Cache.hh"
class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;
class G4Track;
class G4SliceTimer;
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
 class H5PhaseSpaceWriter : public G4VSensitiveDetector
{
public:
  H5PhaseSpaceWriter(G4String name);
  ~H5PhaseSpaceWriter();
G4SliceTimer *timer;
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
     unsigned int    NUMBER_OF_HISTORIES;
     unsigned int    NUMBER_OF_ACTIVE_EVENTS;
     double     Z_STOP;
}BeamData;
PhspData tmp;
EventData tmp_event;
BeamData  myBeamData[1];
std::vector<PhspData>    myPhspData_vector;
std::vector<EventData>   myEventData_vector;
void Initialize(G4HCofThisEvent*);
G4bool ProcessHits(G4Step*aStep, G4TouchableHistory*);
void EndOfEvent(G4HCofThisEvent*HCE);
void PHOTONS_ENERGY(G4double);
void ELECTRON_ENERGY(G4double);
void POSITRON_ENERGY(G4double);
void PROTON_ENERGY(G4double);
void NEUTRON_ENERGY(G4double);
void FILL_DATA (G4Step*& aStep );
void WRITE_PHSP_FILE();
void SUMMARY();
void PHOTON_WEIGHT(G4double Weight );
void ELECTRON_WEIGHT(G4double Weight );
void POSITRON_WEIGHT(G4double Weight );
void PROTON_WEIGHT(G4double Weight );
void NEUTRON_WEIGHT(G4double Weight );
void GET_DATA_FROM_THREAD();
void WRITE_PHASE_SPACE_FILE(std::string );
std::string                        H5PHASE_SPACE_NAME_WITHOUT_EXTENSION,
                                   H5PHASE_SPACE_FILE_EXTENSION,
                                   H5PHASE_SPACE_SUMMARY_EXTENSION;

G4float                            ELECTRON_ENERGY_MAX           ,
                                   ELECTRON_ENERGY_MIN           ,
                                   ELECTRON_ENERGY_MEAN          ,
                                   ELECTRON_WEIGHT_MAX          ,
                                   ELECTRON_WEIGHT_MIN          ,
                                   ELECTRON_WEIGHT_MEAN         ,
                                   PHOTON_ENERGY_MAX             ,
                                   PHOTON_ENERGY_MIN             ,
                                   PHOTON_ENERGY_MEAN            ,
                                   POSITRON_ENERGY_MAX           ,
                                   POSITRON_ENERGY_MIN           ,
                                   POSITRON_ENERGY_MEAN          ,
                                   POSITRON_WEIGHT_MAX          ,
                                   POSITRON_WEIGHT_MIN          ,
                                   POSITRON_WEIGHT_MEAN         ,
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


unsigned int                      

                                   NUMBER_OF_ACTIVE_EVENTS  ,NUMBER_OF_HISTORIES    ;
double                              elapsed_time;
                                 
private:
unsigned int  NumberOfThreads,
      NumberOfEventsPerThread,
      Total_Events_To_Be_Processed,
      DATA_ID;
G4String FILE_NAME;
G4float  Z_STOP;
G4ThreadLocal static bool used;
};
#endif
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
