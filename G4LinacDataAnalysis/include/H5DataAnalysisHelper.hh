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
#ifndef H5DataAnalysisHelper_h
#define H5DataAnalysisHelper_h 1

#include "H5DataAnalysisHelper.hh"
#include "globals.hh"


class H5DataAnalysisHelper 
{
  public:
    H5DataAnalysisHelper();    
    virtual ~H5DataAnalysisHelper();


    void SET_DOSIMETRIC_FILE_NAME( std::string _FileName);
    void SET_PHASE_SPACE_FILE_NAME( std::string _FileName);
    void READ_DOSIMETRIC_DATA();
    void READ_EVENT_DATA();
    void READ_PHANTOM_DATA();
    void READ_BEAM_DATA();
    void READ_PHASE_SPACE_DATA();
    G4double GetRSD_EDEP(int xid,int yid, int zid);
    G4double  GetEnergyDeposit(int xid,int yid, int zid);
G4double GetMaxEnergyDepositPdd(int ix, int iy);
G4double GetMinEnergyDepositPdd( int ix, int iy);
G4double GetMaxEnergyDepositHeatMap(int iz);
G4double GetMinEnergyDepositHeatMap(int iz);
G4double GetMinEnergyDepositXProfile(int ycid, int zcid);
G4double GetMaxEnergyDepositXProfile(int ycid, int zcid);
G4double GetPosX(int id);
G4double GetPosY(int id);
G4double GetMinPosX();
G4double GetMaxPosX();
G4double GetMinPosY();
G4double GetMaxPosY();
G4double GetMinKineticEnergy();
G4double GetMaxKineticEnergy();
G4double GetKineticEnergy(int id);
int GetNumberOfParticle();
int GetNumberOfVoxelsAlongX();
int GetNumberOfVoxelsAlongY();
int GetNumberOfVoxelsAlongZ();
int data_size_PhspData;
int data_size;
double GetPhantomsizeX();
double GetPhantomsizeY();
double GetPhantomsizeZ();

    typedef struct
    {
        G4int    PART_PDGE;
        G4float  PART_WEIGHT
                ,PART_POS_X
                ,PART_POS_Y
                ,PART_POS_Z
                ,PART_DIR_X
                ,PART_DIR_Y
                ,PART_DIR_Z
                ,PART_KINETIC;


    }PhspData;

      typedef struct
      {
          G4int
                   EVENT_ID,
                   NUMBER_OF_ENTRIES;

      }EventData;

      typedef struct
      {
         G4int    NUMBER_OF_HISORIES;
         G4float     Z_STOP;

      }BeamData;

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
     //
       PhspData *RAM_PhspData;
       EventData *RAM_EventData;
       DosimetricData *RAM_DosimetricData;
       BeamData RAM_BeamData[1];
       PhantomData *RAM_PhantomData;
  private:
  std::string DosimetricDataFileName;
  std::string PhaseSpaceFileName;
int data_size_DosimetricData;

};

#endif


