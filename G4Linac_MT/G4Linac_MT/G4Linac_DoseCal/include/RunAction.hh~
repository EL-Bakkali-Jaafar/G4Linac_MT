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

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#
  AUTHOR: Dr. Jaafar EL Bakkali, Assistant Professor of Nuclear Physics, Rabat, Morocco.
  e-mail: bahmedj@gmail.com

  For documentation
  see http://G4Linac_MT.github.com
 
  10/08/2017: public version 1.0
#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=# */
#ifndef RunAction_h
#define RunAction_h 1
#include <ctime>
#include "G4UserRunAction.hh"
#include "globals.hh"
#include <vector>
#include <fstream>
#include <iostream>
#include "G4ios.hh"
#include <stdio.h>
#include <math.h>
class G4Run;


class RunAction : public G4UserRunAction
{
  public:
    RunAction();
   ~RunAction();
    void READ_DOSIMETRIC_DATA_FROM_BINARY_FILE(std::string, int);
    void SETUP_DOSIMETRIC_DATA_FROM_BINARY_FILE(std::string );
    void WRITE_MERGED_DOSIMETRIC_TXT();
    void BeginOfRunAction(const G4Run*);
    void EndOfRunAction(const G4Run*);
    double diffclock(clock_t ,clock_t );

 clock_t begin;

 clock_t end;
std::ofstream  TextFile;
typedef struct
{
int   NUMBER_VOXELS_ALONG_X,NUMBER_VOXELS_ALONG_Y,NUMBER_VOXELS_ALONG_Z;
double  PHANTOM_SIZE_X,PHANTOM_SIZE_Y,PHANTOM_SIZE_Z;
int  
NEVENTS,
VOXEL_XID,
VOXEL_YID,
VOXEL_ZID;
double  
DOSE,
DOSE2,
RSD;
}DosCalData;

DosCalData*  RAM_DosimetricData;
};

#endif

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
