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
#ifndef G4UserH5PhaseSpaceReader_h
#define G4UserH5PhaseSpaceReader_h 1

#include "G4VPrimaryGenerator.hh"
#include "G4ParticleGun.hh"
#include "globals.hh"

class G4Event;
class G4ParticleDefinition;
class DetectorConstruction;
class G4UserH5PhaseSpaceReader : public G4VPrimaryGenerator
{
public:
G4UserH5PhaseSpaceReader();
~G4UserH5PhaseSpaceReader();
public:
void GeneratePrimaryVertex(G4Event* anEvent);   // Mandatory
void SET_First_ID_Of_Event_In_Thread(int );
void SET_EVENT_GENERATION_FLAG(G4int FLAG);
void GENERATE_NEW_PART_ROT_SPLITTING(int incr,G4Event*& anEvent);
void GENERATE_NEW_PART_SPLITTING(int incr,G4Event*& anEvent);
void GENERATE_NEW_PARTICLE(int incr,G4Event*& ev);
void SET_PHASE_SPACE_FILE_NAME( G4String  _FileName);
void SET_Z_PLANE( G4double Z_plane,  bool apply );
void SET_PARAMETERS(G4String, bool, G4float, int, int);
DetectorConstruction *pDetectorConstruction;

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
G4int    EVENT_ID,
NUMBER_OF_ENTRIES;
 }EventData;

typedef struct
{
G4int    NUMBER_OF_HISORIES;
G4float     Z_STOP;
}BeamData;
BeamData  myBeamData[1];
private:
G4int particle_pdge, particle_weight,Number_of_Entries,NUMBER_OF_SIMULATED_HISTORIES;
G4float particle_time,pos_x, pos_y, pos_z, dir_x,dir_y,dir_z, Z_STOP, energy,Z_plane;
G4String FileName;
G4ThreeVector particle_momentum;
bool apply;
G4int EVENT_GENERATION_FLAG, SPLITTING_FACTOR;
G4ParticleDefinition* GET_PARTICLE_DEFINITION(int& PDGE);
G4ThreadLocal static int  First_ID_Of_Event_In_Thread;
G4ThreadLocal static int  Event_ID;
G4ThreadLocal static bool AUTORIZED;
G4ThreadLocal static int  Local_ITERATOR;
G4ThreadLocal static int  ITERATOR;
G4ThreadLocal static int  ID_OF_NEXT_EVENT;
G4ThreadLocal static int  NUMBER_OF_TIME_OF_REUSE_PHASE_SPACE_FILE;
G4ThreadLocal static int  INDEX_OF_CURRENT_DATA;
G4ThreadLocal static int  event_data_length;
};
#endif
