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
#ifndef DetectorConstruction_h
#define DetectorConstruction_h 1

#include "G4VUserDetectorConstruction.hh"
#include "globals.hh"
#include "G4GenericPolycone.hh"
#include"G4Tubs.hh"
#include"G4Cons.hh"
#include"G4Paraboloid.hh"
#include"G4SubtractionSolid.hh"
class G4VPhysicalVolume;
class G4LogicalVolume;
class H5PhaseSpaceWriter;
class G4Material;
class G4Box;
class DetectorMessenger;
class G4tgrMessenger;
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/

class DetectorConstruction : public G4VUserDetectorConstruction
{
public:
DetectorConstruction(int _numberOfThreads);
~DetectorConstruction();
virtual void ConstructSDandField();
G4VPhysicalVolume* Construct();
void SetVerbose(G4int val);
void Setup_PhaseSpaceDetector();
void SetH5PhaseSpaceZStop(G4double _Zstop);
void SetH5PhaseSpaceName(G4String _PhaseSpaceName);

G4String H5_PHASE_SPACE_NAME_WITHOUT_EXTENSION;
 int NUMBER_OF_THREADS;
  DetectorMessenger * pDetectorMessenger;
G4double zstop;

G4tgrMessenger * messenger; 
G4Material *world_mat;
G4String geom_file_name;
G4Box* solidWorld;
bool use_geom_from_text;
G4double world_sizeXY;
G4double world_sizeZ ;
G4double detector_sizeZ ;
G4LogicalVolume* logicWorld;
G4Box* solidTarget;
G4LogicalVolume* logicdTarget ;
G4LogicalVolume*logicdDetector;
H5PhaseSpaceWriter  *mSD;
G4VPhysicalVolume* physWorld;
G4Material * MaterialName(const G4String materialName);
G4VisAttributes *AttributName(const G4String attributName);
void TargetConstructor();
void PrimaryCollimatorConstructor();
void secondaryCollimatorConstructor();
void FlatteningFilterConstructor();
void MonitorConstructor();
void JawsConstructor();
void KillerPlanConstructor();
void GhostConstructor();
void SetNameOfGeomFromTextFile(G4String _FileName);
void SetGeomFromTextFlag(bool _flag);
G4double origin;
G4Box*SolidVolumeTarget;
G4Tubs*SolidVolumePrimaryCollimatorA;
G4Paraboloid*SolidVolumePrimaryCollimatorB;
G4SubtractionSolid*SolidVolumePrimaryCollimator;
G4GenericPolycone * 	SolidVolumeFlatteningFilter;
G4Tubs*SolidVolumeMonitor;
G4Box*Jaws;
G4Box*SolidVolumeGhost;
G4Box* solidDetector;
// Logical Detectors
G4LogicalVolume*LogicalVolumeTarget;
G4LogicalVolume*LogicalVolumePrimaryCollimator;
G4LogicalVolume*LogicalVolumeFlatteningFilter;
G4LogicalVolume*LogicalVolumeMonitor;
G4LogicalVolume*LogicalVolumeJawsX;
G4LogicalVolume*LogicalVolumeJawsY;
G4LogicalVolume*LogicalVolumeGhost;

// Physical Detectors

G4VPhysicalVolume*PhysicalVolumeTarget;
G4VPhysicalVolume*PhysicalVolumePrimaryCollimator;
G4VPhysicalVolume*PhysicalVolumeFlatteningFilter;
G4VPhysicalVolume* PhysicalVolumeMonitor;
G4VPhysicalVolume*PhysicalVolumeJawsX1;
G4VPhysicalVolume*PhysicalVolumeJawsX2;
G4VPhysicalVolume*PhysicalVolumeJawsY1;
G4VPhysicalVolume*PhysicalVolumeJawsY2;
G4VPhysicalVolume * PhysicalVolumeGhost;
};

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/

#endif

