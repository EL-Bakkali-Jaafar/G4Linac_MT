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
 * see http://H5PhaseSpace.GitHub.com
 *
 * - 23/07/2017: public version 2.0
 *
--------------------------------------------------------------------------------------------
*/
#ifndef PhantomSD_h
#define PhantomSD_h 1
#include "G4ThreeVector.hh"
#include "G4VSensitiveDetector.hh"
#include "G4VTouchable.hh"
#include "VoxelStructure.hh"
#include <vector>
#include "G4ios.hh"
#include <stdio.h>
class G4Step;
class G4HCofThisEvent;
class G4TouchableHistory;
class HistoManager;
class DetectorConstruction;
 class  PhantomSD : public G4VSensitiveDetector
{
public:
  PhantomSD(
G4String name);
  ~PhantomSD();
  Svoxel ***Voxels;
  G4bool ProcessHits(G4Step*aStep,G4TouchableHistory*);
  void EndOfEvent(G4HCofThisEvent*HCE);
  void clear();
  void DrawAll();
  void PrintAll();
  void saveDataInVoxels();
  void saveHeaderDataInVoxels();
  void SaveDataInH5File(); 
  void MergeDosimetricData();
typedef struct
{
    G4int    VOXEL_XID,VOXEL_YID,VOXEL_ZID;
    G4float  EDEP,STD_DEV;


}DosimetricData;

typedef struct
{
    G4int   NUMBER_VOXELS_ALONG_X,NUMBER_VOXELS_ALONG_Y,NUMBER_VOXELS_ALONG_Z;
    G4float  PHANTOM_SIZE_X,PHANTOM_SIZE_Y,PHANTOM_SIZE_Z;



}PhantomData;
private:
G4double x;
G4double y;
G4double z;
G4int Voxel_NORMALIZED_ZID,CentreVoxelID_y,CentreVoxelID_x,Voxel_NORMALIZED_XID;
std::vector<G4int> ZposCenter,XprofileCenter;
G4String NameOfPhantomPhysicalVolume;
G4String DOSIMETRIC_DATA_FileName;
std::ofstream  dosimetricFile;
 G4ThreeVector HalfSize;
HistoManager *fHistoManager;
 G4ThreeVector pos;
 G4double HalfVoxelDimensionAlongX, HalfVoxelDimensionAlongY, HalfVoxelDimensionAlongZ;
 G4int NumberTotalEvents, NumberOfVoxelsAlongX, NumberOfVoxelsAlongY, NumberOfVoxelsAlongZ;
 G4double VoxelMass, density, VoxelVolume;
DetectorConstruction* pDetectorConstruction;
int  NumberOfThreads;
G4ThreadLocal  static int INCREMENTOR;
};
#endif


