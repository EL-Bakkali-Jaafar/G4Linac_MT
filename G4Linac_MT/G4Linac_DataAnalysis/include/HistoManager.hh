
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

#ifndef HistoManager_h
#define HistoManager_h 1

#include "globals.hh"

#include "g4root.hh"

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/

class HistoManager
{

private:
  static HistoManager *theInstance;
    HistoManager();

  public:

   ~HistoManager();
static HistoManager * GetInstance();
void SetParametersForDosimetricData2DheatMap(int,int,G4double,G4double,G4double,G4double,G4double,G4double);
void SetParametersForXprofile(int,int,G4double,G4double,G4double,G4double);
void SetParametersForYprofile(int,int,G4double,G4double,G4double,G4double);
void SetParametersForDosimetricDataPdd(int,G4double,G4double,G4double,G4double );
void SetParametersForPhaseSpaceDataPhotonsEnergySpectrum(G4String,int,G4double,G4double);
void SetParametersForPhaseSpaceDataElectronEnergySpectrum(G4String,int,G4double,G4double);
void SetParametersForPhaseSpaceDataSpatialDistXY(G4String,int,G4double,G4double,int,G4double,G4double );
void SetParametersForPhaseSpaceDataPhotonSpatialDistXY_With_Kinetic(G4String,int,G4double,G4double,int,G4double,G4double);
void SetParametersForPhaseSpaceDataElectronSpatialDistXY_With_Kinetic(G4String,int,G4double,G4double,int,G4double,G4double);
void SetParametersForPhaseSpaceDataElectronAngularDistribution(G4String,int,G4double,G4double);
void SetParametersForPhaseSpaceDataPhotonAngularDistribution(G4String,int,G4double,G4double);
void SetTitle_Edep_2DHeatMap(G4String);
void SetTitleEdepDistributionZ(G4String);
void Save();
void Fill_Edep_2DHeatMap( G4double , G4double ,G4double );
void Fill_PDD( G4double ,G4double );
void Fill_XPROFILE( G4double ,G4double );
void Fill_YPROFILE( G4double ,G4double );
void FillSpectrum (G4int ih, G4double , G4double );
void FillElectronSpectrum (G4int, G4double, G4double);
void FillPhotonAngularDist( G4int, G4double, G4double );
void FillElectronAngularDist( G4int , G4double , G4double );
void Fill_spatialDistxy( G4double x, G4double y);
void Fill_spatialDistxy_with_kinetic( G4double , G4double ,G4double );
G4double max_edep; 
G4double min_edep; 
G4double max_x; 
G4double min_x;
G4double max_z; 
G4double min_z;
G4double max_y; 
G4double min_y;   
int Nxbin;
int Nybin;
int Nzbin;
int EnergyBins;
int ThetaBins;
double max_theta;
double min_theta;
double max_energy;
double min_energy;
G4String photons_energy_spectrum_title;
int cyid;
int cxid;
G4String Title_Edep_2DHeatMap,TitleEdepDistributionZ,TitleXprofile,TitleYprofile,spatialdistxy_title, photon_angular_distribution_title,electron_angular_distribution_title,electron_energy_spectrum_title;

};



#endif
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
