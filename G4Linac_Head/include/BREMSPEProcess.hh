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
 * see http://G4Linac_MT.GitHub.com
 *
 * - 23/07/2017: public version 2.0
 *
--------------------------------------------------------------------------------------------
*/

#ifndef BREMSPEPROCESS_HH
#define BREMSPEPROCESS_HH 1
#include "G4WrapperProcess.hh"

class BREMSPEProcess : public G4WrapperProcess {
  
  public:
  BREMSPEProcess();	
  virtual ~BREMSPEProcess();	
  G4VParticleChange* PostStepDoIt(const G4Track& track, const G4Step& step);
  static void SetNSplit(G4int);
  static void SetIsActive(G4bool);
  static G4bool GetIsActive();
  static G4int GetNSplit();
  static G4int GetNSecondaries();

  private:
  static G4int fNSplit;
  static G4int fNSecondaries;
  static G4bool fActive;

};

#endif
