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
#ifndef DetecorMessenger_h
#define DetecorMessenger_h 1

#include "globals.hh"
#include "G4UImessenger.hh"

class DetectorConstruction;
class G4UIdirectory;
class G4UIcmdWithADoubleAndUnit;
class G4UIcmdWithAString;
class G4UIcmdWithAnInteger;
class G4UIcmdWith3VectorAndUnit;
 class  G4UIcmdWithAString;


class DetectorMessenger: public G4UImessenger
{
  public:
  
    DetectorMessenger(DetectorConstruction* );
   ~DetectorMessenger();
    
    void SetNewValue(G4UIcommand*, G4String);
    
  private:
  DetectorConstruction* fDetectorConstruction;
  G4UIcmdWith3VectorAndUnit* ROGcenterPosCmd;
  G4UIcmdWithAnInteger* numberOfVoxelsAlongZCmd;
  G4UIcmdWithAnInteger* numberOfVoxelsAlongYCmd;
  G4UIcmdWithAnInteger* numberOfVoxelsAlongXCmd;
  G4UIcmdWithAnInteger* CenterVoxel_X_IDCmd;
  G4UIcmdWithAnInteger* CenterVoxel_Y_IDCmd;
  G4UIcmdWithAnInteger* NomalizedPDDVoxel_Z_IDCmd;
  G4UIcmdWithAnInteger* NomalizedPROFILEVoxel_X_IDCmd;
  G4UIcmdWithADoubleAndUnit* phantomSizeXCmd;
  G4UIcmdWithADoubleAndUnit* phantomSizeYCmd;
  G4UIcmdWithADoubleAndUnit* phantomSizeZCmd;
G4UIcmdWithAString *UpdateGeometryCmd;
  G4UIdirectory*  DetectorDir;   
  G4UIcmdWithADoubleAndUnit* H5PhaseSpace_ZSTOPCmd;
G4UIcmdWithAString *H5PhaseSpace_NameCmd; 
 
};



#endif

