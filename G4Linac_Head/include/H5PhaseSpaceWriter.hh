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
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
 class H5PhaseSpaceWriter : public G4VSensitiveDetector
{
public:
  H5PhaseSpaceWriter(G4String name);
  ~H5PhaseSpaceWriter();
typedef struct
{
    G4int    PART_PDGE;
    G4float  PART_WEIGHT
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
      G4int
               EVENT_ID,
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
  //
  std::vector<PhspData>    myPhspData;
  std::vector<EventData>   myEventData;

  void Initialize(G4HCofThisEvent*);
  G4bool ProcessHits(G4Step*aStep, G4TouchableHistory*);
  void EndOfEvent(G4HCofThisEvent*HCE);
  void clear();
  void DrawAll();
  void PrintAll();
  void PHOTONS_ENERGY(G4double);
  void ELECTRONS_ENERGY(G4double);
  void POSITRONS_ENERGY(G4double);
  void PROTONS_ENERGY(G4double);
  void NEUTRONS_ENERGY(G4double);
  void FILL_DATA (G4Step*& aStep );
  void WRITE_PHSP_FILE();
  void SUMMARY();

private:
 int  NumberOfThreads;
 int  NumberOfEventsPerThread;
 int  Total_Events_To_Be_Processed;
 G4String FILE_NAME;
 G4float  Z_STOP;
int DATA_ID;
G4ThreadLocal static bool used;
};
#endif

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
