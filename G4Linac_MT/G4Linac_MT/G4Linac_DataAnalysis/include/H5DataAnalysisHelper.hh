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
#ifndef H5DataAnalysisHelper_h
#define H5DataAnalysisHelper_h 1

#include "H5DataAnalysisHelper.hh"
#include "globals.hh"
class H5DataAnalysisHelper 
{
public:
H5DataAnalysisHelper();    
virtual ~H5DataAnalysisHelper();
void     SET_DOSIMETRIC_FILE_NAME( std::string );
void     SET_PHASE_SPACE_FILE_NAME( std::string );
void     READ_EVENT_DATA();
void     READ_BEAM_DATA();
void     READ_PHASE_SPACE_DATA();
void     READ_DOSIMETRIC_DATA_FROM_BINARY_FILE();
int      GetNumberOfParticle();
int      GetNumberOfVoxelsAlongX();
int      GetNumberOfVoxelsAlongY();
int      GetNumberOfVoxelsAlongZ();
unsigned int      data_size_PhspData;
unsigned int      data_size;
double   GetPhantomsizeX();
double   GetPhantomsizeY();
double   GetPhantomsizeZ();
G4double GetRSD_DOSE(int xid,int yid, int zid);
G4double Get_DOSE(int xid,int yid, int zid);
G4double GetMaxDosePdd(int ix, int iy);
G4double GetMinDosePdd( int ix, int iy);
G4double GetMaxDoseHeatMap(int iz,std::string );
G4double GetMinDoseHeatMap(int iz,std::string);
G4double GetMinDoseXProfile(int ycid, int zcid);
G4double GetMaxDoseXProfile(int ycid, int zcid);
G4double GetMinDoseYProfile(int xcid, int zcid);
G4double GetMaxDoseYProfile(int xcid, int zcid);
G4double GetPosX(int ,int);
G4double GetPosY(int,int );
G4double GetTheta(int , int);
G4double GetMinTheta(int);
G4double GetMaxTheta(int);
G4double GetMinPosX(int);
G4double GetMaxPosX(int);
G4double GetMinPosY(int);
G4double GetMaxPosY(int);
G4double GetMinKineticEnergy(int);
G4double GetMaxKineticEnergy(int);
G4double GetKineticEnergy(int ,int);
G4double GetMaxRSDPdd(int xid, int yid);
G4double GetMinRSDPdd(int xid, int yid);
G4double GetMaxRSDXProfile(int ycid, int zcid);
G4double GetMinRSDXProfile(int ycid, int zcid);
G4double GetMaxRSDYProfile(int xcid, int zcid);
G4double GetMinRSDYProfile(int xcid, int zcid);
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


typedef struct
{
int    PART_PDGE;
double  PART_WEIGHT
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
int     EVENT_ID,
          NUMBER_OF_ENTRIES;
}EventData;

typedef struct
{
int     NUMBER_OF_HISORIES;
double   Z_STOP;

}BeamData;

typedef struct
{
int    VOXEL_XID,
         VOXEL_YID,
         VOXEL_ZID;
double  DOSE,
         RSD;

}DosimetricData;

typedef struct
{
int   NUMBER_VOXELS_ALONG_X,
        NUMBER_VOXELS_ALONG_Y,
        NUMBER_VOXELS_ALONG_Z;
double PHANTOM_SIZE_X,
        PHANTOM_SIZE_Y,
        PHANTOM_SIZE_Z;
}PhantomData;
PhspData*RAM_PhspData;
EventData *RAM_EventData;
DosimetricData *RAM_DosimetricData;
BeamData RAM_BeamData[1];
PhantomData *RAM_PhantomData;
G4double PHANTOM_SIZE_X,PHANTOM_SIZE_Y,PHANTOM_SIZE_Z;
private:
std::string DosimetricDataFileName, 
            PhaseSpaceFileName;
unsigned int data_size_DosimetricData;

};
#endif

/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
