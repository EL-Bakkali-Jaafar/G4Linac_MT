
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
DetectorConstruction();
~DetectorConstruction();
G4VPhysicalVolume* Construct();
virtual void ConstructSDandField();
void SetVerbose(G4int val);
void Setup_PhaseSpaceDetector();
void SetH5PhaseSpaceZStop(G4double _Zstop);
void SetH5PhaseSpaceName(G4String _PhaseSpaceName);
void TargetConstructor();
void PrimaryCollimatorConstructor();
void secondaryCollimatorConstructor();
void FlatteningFilterConstructor();
void MonitorConstructor();
void JawsConstructor();
void KillerPlanConstructor();
void GhostConstructor();
void SetNameOfGeomFromTextFile(G4String );
void SetGeomFromTextFlag(bool );
void SetNumberOfEventsPerThread(int);
//Materials & Attribues
G4Material        * world_mat;
G4Material        * Pb;
G4Material        * Tungsten;
G4Material        * FFMAT;
G4Material        * air;
G4Material        * MaterialName(const G4String );
G4VisAttributes   * AttributName(const G4String );
//Messengers
G4tgrMessenger    * messenger; 
DetectorMessenger * pDetectorMessenger;
//Strings
G4String H5_PHASE_SPACE_NAME_WITHOUT_EXTENSION;
G4String geom_file_name;
//Integers
int NUMBER_OF_THREADS;
int NumberOfEventsPerThread; 
//Doubles
G4double zstop;
G4double world_sizeXY;
G4double world_sizeZ ;
G4double detector_sizeZ ;
G4double origin;
//bools
bool use_geom_from_text;
//classes
H5PhaseSpaceWriter  *mSD;
// Solid Volumes
G4Box             * solidTarget;
G4Box             * SolidVolumeTarget;
G4Cons            * SolidVolumePrimaryCollimator;
G4GenericPolycone * SolidVolumeFlatteningFilter;
G4Tubs            * SolidVolumeMonitor;
G4Box             * Jaws;
G4Box             * solidDetector;
G4Box             * solidWorld;
// Logical Volumes
G4LogicalVolume   * LogicalVolumeTarget;
G4LogicalVolume   * LogicalVolumePrimaryCollimator;
G4LogicalVolume   * LogicalVolumeFlatteningFilter;
G4LogicalVolume   * LogicalVolumeMonitor;
G4LogicalVolume   * LogicalVolumeJawsX;
G4LogicalVolume   * LogicalVolumeJawsY;
G4LogicalVolume   * LogicalVolumeGhost;
G4LogicalVolume   * logicWorld;
G4LogicalVolume   * logicdTarget ;
G4LogicalVolume   * logicdDetector;
// Physical Detectors
G4VPhysicalVolume * physWorld;
G4VPhysicalVolume * PhysicalVolumeTarget;
G4VPhysicalVolume * PhysicalVolumePrimaryCollimator;
G4VPhysicalVolume * PhysicalVolumeFlatteningFilter;
G4VPhysicalVolume * PhysicalVolumeMonitor;
G4VPhysicalVolume * PhysicalVolumeJawsX1;
G4VPhysicalVolume * PhysicalVolumeJawsX2;
G4VPhysicalVolume * PhysicalVolumeJawsY1;
G4VPhysicalVolume * PhysicalVolumeJawsY2;
};
#endif
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
