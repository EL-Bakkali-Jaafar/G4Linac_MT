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
#include "DetectorConstruction.hh"
#include "G4RunManager.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4Cons.hh"
#include "G4Orb.hh"
#include "G4Sphere.hh"
#include "G4Trd.hh"
#include "G4LogicalVolume.hh"
#include "G4PVPlacement.hh"
#include "G4SystemOfUnits.hh"
#include "DetectorMessenger.hh"
#include "G4Threading.hh"
#include "H5PhaseSpaceWriter.hh"
#include "G4SDManager.hh"
#include "G4AutoDelete.hh"
#include"G4RegionStore.hh"
#include"globals.hh"
#include"G4Material.hh"
#include"G4MaterialTable.hh"
#include"G4Element.hh"
#include"G4ElementTable.hh"
#include"G4Box.hh"
#include"G4Region.hh"
#include"G4ThreeVector.hh"
#include"G4PVPlacement.hh"
#include"G4PVReplica.hh"
#include"G4SDManager.hh"
#include"G4VisAttributes.hh"
#include"G4Colour.hh"
#include"G4Tubs.hh"
#include"G4Cons.hh"
#include"G4Paraboloid.hh"
#include"G4SubtractionSolid.hh"
#include"G4UnionSolid.hh"
#include"G4IntersectionSolid.hh"
#include "G4tgbVolumeMgr.hh"
#include "G4tgrMessenger.hh"
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/

DetectorConstruction::DetectorConstruction()
: G4VUserDetectorConstruction(),mSD(0)
{
 pDetectorMessenger= new DetectorMessenger(this);

}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorConstruction::SetNumberOfEventsPerThread(int _NumberOfEventsPerThread){

this->NumberOfEventsPerThread=_NumberOfEventsPerThread;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorConstruction::SetNameOfGeomFromTextFile(G4String _FileName){
this->geom_file_name=_FileName;

}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/

void DetectorConstruction::SetGeomFromTextFlag(bool _flag){
this->use_geom_from_text=_flag;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
DetectorConstruction::~DetectorConstruction()
{ 

}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
G4VPhysicalVolume* DetectorConstruction::Construct(){
if (this->use_geom_from_text==true){
messenger = new G4tgrMessenger;
G4String filename = this->geom_file_name;
G4tgbVolumeMgr* volmgr = G4tgbVolumeMgr::GetInstance();
volmgr->AddTextFile(filename);
//------------------------------------------------
// Read the text files and construct the GEANT4 geometry
//------------------------------------------------
this->physWorld= volmgr->ReadAndConstructDetector();


return this->physWorld;
} else {
G4NistManager* nist = G4NistManager::Instance();
this->world_sizeXY     =   80*cm;
this-> world_sizeZ  = 120*cm;
this-> detector_sizeZ  = 2*mm;
world_mat = nist->FindOrBuildMaterial("G4_Galactic");
solidWorld =new G4Box("solidWorld",this->world_sizeXY/2.0,this->world_sizeXY/2.0,this-> world_sizeZ/2.0);   
logicWorld = new G4LogicalVolume(solidWorld, world_mat,"logicWorld");   
logicWorld->SetVisAttributes(G4VisAttributes::GetInvisible());        
physWorld = new G4PVPlacement(0,G4ThreeVector(),logicWorld, "World",0, false,0, false);
this->Pb=this->MaterialName("Pb");
this->Tungsten=this->MaterialName("Tungsten");
this->FFMAT=this->MaterialName("FFMAT");
this->air=MaterialName("air");
 origin=-this-> world_sizeZ /2.0;

//
TargetConstructor();
//
PrimaryCollimatorConstructor();
//
FlatteningFilterConstructor();
//
MonitorConstructor();
//
JawsConstructor();
//GhostConstructor();

Setup_PhaseSpaceDetector();
return physWorld;
}}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorConstruction::ConstructSDandField(){
G4SDManager* pSDManager = G4SDManager::GetSDMpointer();
mSD = new H5PhaseSpaceWriter("Phantom");
pSDManager-> AddNewDetector(mSD);
SetSensitiveDetector("PHASE_SPACE",mSD);
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/

void DetectorConstruction::Setup_PhaseSpaceDetector()
{
G4double detector_z_pos=origin+this->zstop+this->detector_sizeZ/2.0;
solidDetector=new G4Box("Detector",this->world_sizeXY/2.0, this->world_sizeXY/2.0, this->detector_sizeZ/2.0);
logicdDetector =new G4LogicalVolume(solidDetector,this->world_mat,"PHASE_SPACE");
new G4PVPlacement(0, G4ThreeVector(0,0,detector_z_pos),logicdDetector,"pDetector",this->logicWorld,false,0,false);
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorConstruction::SetH5PhaseSpaceZStop(G4double _Zstop){
this->zstop=_Zstop;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
void DetectorConstruction::SetH5PhaseSpaceName(G4String _PhaseSpaceName){
this->H5_PHASE_SPACE_NAME_WITHOUT_EXTENSION=_PhaseSpaceName;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#*/
G4VisAttributes*DetectorConstruction::AttributName(const G4String    attributName)
{
G4VisAttributes*attribut=new  G4VisAttributes();
if(attributName=="Target_VisAttribut")
{
G4VisAttributes*Target_VisAttribut=new  G4VisAttributes(G4Colour(0/255.,0/255.,255/255.));
attribut=Target_VisAttribut;
return attribut;
}
if(attributName=="Monitor_VisAttribut")
{
G4VisAttributes*Monitor_VisAttribut=new  G4VisAttributes(G4Colour(0/255.,255/255.,0/255.));
attribut=Monitor_VisAttribut;
return attribut;
}
if(attributName=="PrimaryCollimator_VisAttribut")
{
G4VisAttributes*PrimaryCollimator_VisAttribut=new  G4VisAttributes(G4Colour(255/255.,0/255.,255/255.));
attribut=PrimaryCollimator_VisAttribut;
return attribut;
}
if(attributName=="Jaws_VisAttribut")
{
G4VisAttributes*Jaws_VisAttribut=new  G4VisAttributes(G4Colour(0/255.,255/255.,255/255.));
attribut=Jaws_VisAttribut;
return attribut;
}
if(attributName=="LogicalVolumeFlatteningFilterilter_VisAttribut")
{
G4VisAttributes*LogicalVolumeFlatteningFilterilter_VisAttribut=new  G4VisAttributes(G4Colour(255/255.,255/255.,0/255.));
attribut=LogicalVolumeFlatteningFilterilter_VisAttribut;
return attribut;
}
return attribut;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
G4Material*DetectorConstruction::MaterialName(const G4String    materialName)
{
G4double z,a,density;
G4String   name,symbol;
G4int   ncomponents;
G4Material*material=0;
G4Element*elementC=new G4Element("Carbon","C",6.,12.01*g/mole);
G4Element*elementN=new G4Element("Nitrogen","N",7.,14.00674*g/mole);
G4Element*elementO=new G4Element("Oxygen","O",8.,15.9994*g/mole);
G4Element*elementSi=new G4Element("Silicon","Si",14.,28.0855*g/mole);
G4Element*elementAr=new G4Element("Argon","Ar",18.,39.948*g/mole);
G4Element*elementMn=new G4Element("Maganese","Mn",25.,54.93805*g/mole);
G4Element*elementFe=new G4Element("Fer","Fe",26.,55.85*g/mole);
if(materialName=="air"){
this->air=new G4Material("air",density=0.0012*g/cm3,ncomponents=4);
air->AddElement(elementC,0.0124*perCent);
air->AddElement(elementN,75.527*perCent);
air->AddElement(elementO,23.178*perCent);
air->AddElement(elementAr,1.2827*perCent);
material=this->air;
}
else if(materialName=="Copper")
{
G4Material*Cu=new G4Material("Copper",z=29.,a=63.546*g/mole,density=8.96*g/cm3);
material=Cu;
}
else if(materialName=="Pb")
{
this->Pb=new G4Material("Lead",z=82.,a=207.19*g/mole,density=11.34*g/cm3);
material=this->Pb;
}

else if(materialName=="Tungsten")
{
this->Tungsten=new G4Material("Tungsten",z=74,a=183.85*g/mole,density=19.3*g/cm3);
material=this->Tungsten;
}
else if(materialName=="FFMAT")
{
this->FFMAT=new G4Material(name="FFMAT",density=8*g/cm3,ncomponents=3);
FFMAT->AddElement(elementMn,33.33*perCent);
FFMAT->AddElement(elementFe,33.33*perCent);
FFMAT->AddElement(elementSi,33.34*perCent);

material=this->FFMAT;
}
return material;
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
void DetectorConstruction::TargetConstructor()
{
G4VisAttributes*Target_VisAttribut=this->AttributName("Target_VisAttribut");
G4double Target_Dim_y=4*cm;
G4double Target_Dim_x=4*cm;
G4double Target_Dim_z=0.5*cm;
SolidVolumeTarget=new G4Box("SolidVolumeTarget",Target_Dim_x/2.0,Target_Dim_y/2.0,Target_Dim_z/2.0);
G4RotationMatrix *Target_rotation_z=new G4RotationMatrix ;
Target_rotation_z->rotateZ(0.*rad);
LogicalVolumeTarget=new G4LogicalVolume(SolidVolumeTarget,this->Tungsten,"LogicalVolumeTarget",0,0,0);
LogicalVolumeTarget->SetVisAttributes(Target_VisAttribut);
G4RotationMatrix rotMatrix;
G4double anglePhysicalVolumeTarget=0.0*deg;
rotMatrix.rotateX(anglePhysicalVolumeTarget);
G4double Target_centre_pos_z=Target_Dim_z/2.0;
PhysicalVolumeTarget=new G4PVPlacement(G4Transform3D(rotMatrix,G4ThreeVector  (0*cm,0.0*m,Target_centre_pos_z+origin)),"PhysicalVolumeTarget",LogicalVolumeTarget,this->physWorld,false,0);
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
void DetectorConstruction::PrimaryCollimatorConstructor()
{

G4VisAttributes*PrimaryCollimator_VisAttributt=this->AttributName("PrimaryCollimator_VisAttribut");
G4RotationMatrix RotationMatrix_PrimaryCollimator;
G4double Angle_PrimaryCollimator=180.0*deg;
RotationMatrix_PrimaryCollimator.rotateX(Angle_PrimaryCollimator);
G4double  pRmax1                 = 10*cm,
          pRmin1                 = 0.5*cm,
          pRmax2                 = 10*cm,
          pRmin2                 = 2.5*cm,
          hightOfTheCone         = 6.0*cm,
          startAngleOfTheCone    = 0.*deg,
          spanningAngleOfTheCone = 360.*deg;
SolidVolumePrimaryCollimator     = new G4Cons("SolidVolumePrimaryCollimator",pRmin2,pRmax2,pRmin1,				   pRmax1,hightOfTheCone/2.0,startAngleOfTheCone,spanningAngleOfTheCone);
LogicalVolumePrimaryCollimator=new G4LogicalVolume(SolidVolumePrimaryCollimator,this->Pb,"LogicalVolumePrimaryCollimator",0,0,0);
LogicalVolumePrimaryCollimator->SetVisAttributes(PrimaryCollimator_VisAttributt);
G4double LogicalVolumePrimaryCollimator_Centre_z=1.6*cm+hightOfTheCone/2.0;
PhysicalVolumePrimaryCollimator=new G4PVPlacement(G4Transform3D(RotationMatrix_PrimaryCollimator,G4ThreeVector  (0*cm,0.0*m,LogicalVolumePrimaryCollimator_Centre_z+origin)),"PhysicalVolumePrimaryCollimator",LogicalVolumePrimaryCollimator,this->physWorld,false,0);
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
void DetectorConstruction::FlatteningFilterConstructor()
{
G4VisAttributes*LogicalVolumeFlatteningFilterilter_VisAttribut=this->AttributName("LogicalVolumeFlatteningFilterilter_VisAttribut");
G4double* r = new G4double[5];
G4double* z = new G4double[5];
r[0]= 0*cm;
r[1]= 1.*cm;
r[2]= 1.7*cm;
r[3]= 1.7*cm;
r[4]= 2.*cm;

z[0]= 1.25*mm;
z[1]= 9*mm;
z[2]= 13.8*mm;
z[3]= 27*mm;
z[4]= 27*mm;
SolidVolumeFlatteningFilter= new G4GenericPolycone("SFF",0.0*rad,360.0*rad,4,r, z);
G4RotationMatrix rotMatrixPhysicalVolumeTarget;
G4double anglePhysicalVolumeTarget=180.0*deg;
rotMatrixPhysicalVolumeTarget.rotateX(anglePhysicalVolumeTarget);
LogicalVolumeFlatteningFilter=new G4LogicalVolume(SolidVolumeFlatteningFilter,this->FFMAT,"LogicalVolumeFlatteningFilter",0,0,0);
PhysicalVolumeFlatteningFilter=new G4PVPlacement(G4Transform3D(rotMatrixPhysicalVolumeTarget,G4ThreeVector  (0*cm,0.0*m,8*cm+origin)),"PhysicalVolumeFlatteningFilter",LogicalVolumeFlatteningFilter,this->physWorld,false,0);
LogicalVolumeFlatteningFilter->SetVisAttributes(LogicalVolumeFlatteningFilterilter_VisAttribut);
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
void DetectorConstruction::MonitorConstructor()
{
G4VisAttributes*Monitor_VisAttribut=this->AttributName("Monitor_VisAttribut");
G4RotationMatrix rotMatrixPhysicalVolumeTarget;
G4double anglePhysicalVolumeTarget=180.0*deg;
rotMatrixPhysicalVolumeTarget.rotateX(anglePhysicalVolumeTarget);
G4double Angle_First=0.0*rad;
G4double  Angle_Last=360.0*rad;
G4double MonitorRayon=10*cm;
G4double MonitorDemiZ=1.5*cm;
SolidVolumeMonitor=new G4Tubs("SolidVolumeMonitor",0.0*mm,MonitorRayon,MonitorDemiZ,Angle_First, Angle_Last);
LogicalVolumeMonitor=new G4LogicalVolume(SolidVolumeMonitor,this->air,"LogicalVolumeMonitor",0,0,0);
G4double z_Centre_ChI_PlAl=15*cm;
PhysicalVolumeMonitor=new G4PVPlacement(G4Transform3D(rotMatrixPhysicalVolumeTarget,G4ThreeVector  (0*cm,0.0*m,z_Centre_ChI_PlAl+origin)),"pLogicalVolumeMonitor",LogicalVolumeMonitor,this->physWorld,false,0);
LogicalVolumeMonitor->SetVisAttributes(Monitor_VisAttribut);
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
void DetectorConstruction::JawsConstructor(){
G4double FIELD = 20.0*cm;
G4double  DSP  = 100.*cm;
G4double theta=std::atan((FIELD/DSP)/2.0);
G4VisAttributes*Jaws_VisAttribut=this->AttributName("Jaws_VisAttribut");
G4double JAWS_DIM_X=20*cm;
G4double JAWS_DIM_Y=20*cm;
G4double JAWS_DIM_Z=10*cm;
Jaws=new G4Box("Jaws",JAWS_DIM_Y/2.0,JAWS_DIM_Y/2.0,JAWS_DIM_Z/2.0);
LogicalVolumeJawsX=new G4LogicalVolume(Jaws,this->Pb,"LogicalVolumeJawsX",0,0,0);
LogicalVolumeJawsY=new G4LogicalVolume(Jaws,this->Pb,"LogicalVolumeJawsY",0,0,0);
LogicalVolumeJawsX->SetVisAttributes(Jaws_VisAttribut);
LogicalVolumeJawsY->SetVisAttributes(Jaws_VisAttribut);
G4double JawsX_origin_centre_z=20*cm;
G4double JawsY_origin_centre_z=JawsX_origin_centre_z+JAWS_DIM_Z;
G4double Distance_Source_JawsX=JawsX_origin_centre_z+JAWS_DIM_Z/2.0;
G4double dx=Distance_Source_JawsX*tan(theta);
G4double JawsX_Centre_X=0.5*JAWS_DIM_X+dx;
G4RotationMatrix RMX1,RMX2;
G4double Angle_X=-theta;
RMX1.rotateY(-Angle_X);
RMX2.rotateY(Angle_X);
PhysicalVolumeJawsX1=new G4PVPlacement(G4Transform3D(RMX1,
G4ThreeVector  (JawsX_Centre_X,0, Distance_Source_JawsX+origin)),"PhysicalVolumeJawsX1",LogicalVolumeJawsX,this->physWorld,false,0);
PhysicalVolumeJawsX2=new G4PVPlacement(G4Transform3D(RMX2,G4ThreeVector  (-JawsX_Centre_X,0, Distance_Source_JawsX+origin)),"PhysicalVolumeJawsX2",LogicalVolumeJawsX,this->physWorld,false,0);
G4double Distance_Source_JawsY=JawsY_origin_centre_z+JAWS_DIM_Z/2.0;
G4double dy=Distance_Source_JawsY*tan(theta);
G4RotationMatrix RMY1,RMY2;
G4double Angle_Y=-theta;
RMY1.rotateX(Angle_Y);
RMY2.rotateX(-Angle_Y);
G4double JawsY_Centre_X=0*mm;
G4double JawsY_Centre_Y=0.5*JAWS_DIM_Y+dy;
PhysicalVolumeJawsY1=new G4PVPlacement(G4Transform3D(RMY1,G4ThreeVector  (JawsY_Centre_X,JawsY_Centre_Y,  Distance_Source_JawsY+origin)),
"PhysicalVolumeJawsY1",LogicalVolumeJawsY,this->physWorld,false,0);
PhysicalVolumeJawsY2=new G4PVPlacement(G4Transform3D(RMY2,G4ThreeVector  (JawsY_Centre_X,-JawsY_Centre_Y,  Distance_Source_JawsY+origin)),"PhysicalVolumeJawsY2",LogicalVolumeJawsY,this->physWorld,false,0);
}
/*#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=#=*/
