
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
void SetH5PhaseSpaceZStop(G4double _Zstop);
void SetH5PhaseSpaceName(G4String _PhaseSpaceName);
void SetNameOfGeomFromTextFile(G4String );
void SetNumberOfEventsPerThread(int);

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

// Physical Detectors
G4VPhysicalVolume * physWorld;

};
#endif
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
