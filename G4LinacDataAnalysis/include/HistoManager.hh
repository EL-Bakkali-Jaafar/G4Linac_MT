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


#ifndef HistoManager_h
#define HistoManager_h 1

#include "globals.hh"

#include "g4root.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

class HistoManager
{

private:
  static HistoManager *theInstance;
    HistoManager();

  public:

   ~HistoManager();
  static HistoManager * GetInstance();
void SetParametersForDosimetricData2DheatMap(int xbin,int ybin, G4double max_edep, G4double min_edep, G4double max_x, G4double min_x, G4double max_y, G4double min_y);
void SetParametersForXprofile( int Nxbin,int cyid, G4double max_edep, G4double min_edep, G4double max_x, G4double min_x);
void SetParametersForYprofile( int Nybin,int cxid, G4double max_edep, G4double min_edep, G4double max_y, G4double min_y);
void SetParametersForDosimetricDataPdd(int zbin, G4double max_edep, G4double min_edep, G4double max_z, G4double min_z);
void SetParametersForPhaseSpaceDataPhotonsEnergySpectrum( G4String _title, int EnergyBins,G4double max_energy, G4double);
void SetParametersForPhaseSpaceDataSpatialDistXY(G4String,  int, G4double,  G4double, int,G4double, G4double );

void SetTitle_Edep_2DHeatMap(G4String _title);
void SetTitleEdepDistributionZ(G4String _title);
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
double max_energy;
double min_energy;
G4String photons_energy_spectrum_title;
int cyid;
int cxid;
void Book();
void Save();
void Fill_Edep_2DHeatMap( G4double x, G4double y,G4double z);
void Fill_PDD( G4double z,G4double edep);
void Fill_XPROFILE( G4double x,G4double edep);
void Fill_YPROFILE( G4double y,G4double edep);
void FillSpectrum (G4int ih, G4double _energy, G4double weight);
void Fill_spatialDistxy( G4double x, G4double y);
G4String Title_Edep_2DHeatMap,TitleEdepDistributionZ,TitleXprofile,TitleYprofile,spatialdistxy_title;

};

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#endif

