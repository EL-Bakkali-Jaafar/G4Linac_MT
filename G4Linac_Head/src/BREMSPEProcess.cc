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
#include "BREMSPEProcess.hh"

#include "G4Track.hh"
#include "G4VParticleChange.hh"
#include <assert.h>
#include <vector>
#include "G4SystemOfUnits.hh"
// 
// BREMSPE is modifed version of Bremsstrahlung spltting technique developed by Tinslay (Jane Tinslay, March 2006), to see original technique visit the followning link:
 // J. Tinslay, T. Koi, Hands-on 5 Alternative Physics Lists, Bremsstrahlung Splitting, SLAC National Accelerator Laboratory, Menlo Park, CA, Stanford University, 2010.




// Initialise static data
G4int BREMSPEProcess::fNSplit = 1;
G4int BREMSPEProcess::fNSecondaries = 0;
G4bool BREMSPEProcess::fActive = false;

BREMSPEProcess::BREMSPEProcess() {}

BREMSPEProcess::~BREMSPEProcess() {}

G4VParticleChange* 
BREMSPEProcess::PostStepDoIt(const G4Track& track, const G4Step& step)
{
static int h=0,f=0;
  // Just do regular processing if brem splitting is not activated
  G4VParticleChange* particleChange(0);

  if (!fActive) {
    particleChange = pRegProcess->PostStepDoIt(track, step);
    assert (0 != particleChange);

    fNSecondaries += particleChange->GetNumberOfSecondaries();

    return particleChange;
  }
G4ThreeVector direction = track.GetMomentumDirection();
G4double theta  = std::acos(std::abs(direction.z()));
  if ((track.GetParentID() == 0 ))
{
  //    Do brem splitting

  assert (fNSplit > 0);

  G4int i(0);
  G4double weight = track.GetWeight()/fNSplit;
  
  // Secondary store
  std::vector<G4Track*> secondaries;
  secondaries.reserve(fNSplit);
    
  // Loop over PostStepDoIt method to generate multiple secondaries.
  for (i=0; i<fNSplit; i++) {    
    particleChange = pRegProcess->PostStepDoIt(track, step);

    assert (0 != particleChange);
    particleChange->SetVerboseLevel(0);

    G4int j(0);

    for (j=0; j<particleChange->GetNumberOfSecondaries(); j++) {
      secondaries.push_back(new G4Track(*(particleChange->GetSecondary(j))));
    }
  }	

  // Configure particleChange to handle multiple secondaries. Other 
  // data is unchanged
  particleChange->SetNumberOfSecondaries(secondaries.size());
  particleChange->SetSecondaryWeightByProcess(true);

  // Add all secondaries 
  std::vector<G4Track*>::iterator iter = secondaries.begin();
	
  while (iter != secondaries.end()) {
    G4Track* myTrack = *iter;
    myTrack->SetWeight(weight);
G4ThreeVector direction = myTrack->GetMomentumDirection();
G4ThreeVector position0=myTrack->GetPosition();
G4double theta  = std::acos(std::abs(direction.z()));
 //G4ThreeVector position1=position0.rotateZ(360*G4UniformRand());
//G4double theta  = std::acos(std::abs(direction.z()));
//  myTrack->SetPosition( position1);
//G4ThreeVector direction1=direction.rotateZ(360*G4UniformRand());
 //myTrack->SetMomentumDirection(direction1);
//myTrack->SetPosition(position1);
    // particleChange takes ownership
 //if ( theta < 3 *degree)
 particleChange->AddSecondary(myTrack);

    
    iter++;
  }

  fNSecondaries += secondaries.size();

  return particleChange;
  }

else {   particleChange = pRegProcess->PostStepDoIt(track, step);
    assert (0 != particleChange);

    fNSecondaries += particleChange->GetNumberOfSecondaries();

    return particleChange;}
}

void BREMSPEProcess::SetNSplit(G4int nSplit) 
{
  fNSplit = nSplit;
}

void BREMSPEProcess::SetIsActive(G4bool active) 
{
  fActive = active;
}

G4bool BREMSPEProcess::GetIsActive() 
{
  return fActive;
}

G4int BREMSPEProcess::GetNSplit() 
{
  return fNSplit;
}

G4int BREMSPEProcess::GetNSecondaries() 
{
  return fNSecondaries;
}
