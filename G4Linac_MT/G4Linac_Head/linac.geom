:P field 10*cm
:P ssd 100*cm
:p JAWS_DIM_X 10*cm
:P theta atan($field/$ssd)/deg
:p JAWS_DIM_Z 50.
:p JAWS_DIM_Y 10*cm
:P JawsX_origin_centre_z 300.
:P Distance_Source_JawsX ($JawsX_origin_centre_z+$JAWS_DIM_X/2.0)
:P dx $Distance_Source_JawsX*tan($theta*deg/2.0)
:P JawsX_Centre_X $JAWS_DIM_X+$dx
:p JawsY_origin_centre_z 420.
:P Distance_Source_JawsY ($JawsY_origin_centre_z+$JAWS_DIM_Y/2.0)
:P dy $Distance_Source_JawsY*tan($theta*deg/2.0)
:P JawsY_Centre_Y ($JAWS_DIM_Y+$dy)
:ROTM RM0 0 0 0
:ROTM RM1 0 $theta*deg 0
:ROTM RM2  $theta*deg 0 0
:ROTM RM3 0 -$theta*deg 0
:ROTM RM4  -$theta*deg 0 0
:MATE CU521ICRU 29 63.54 8.9333
:MATE W521ICRU 74 183.85 19.3

:VOLU expHall BOX 50*cm 50*cm 150*cm G4_AIR

:VIS expHall OFF

:P TARGET_THICK 2.5

// Target 
:VOLU target BOX 2*cm 2*cm $TARGET_THICK G4_Cu
:COLOR target  1 0 0
:PLACE target  1 expHall RM0 0.0 0.0 $TARGET_THICK

// Primary collimator
:P RMAX 10*cm
:P PC_ZMIN 1.6*cm
:P PC_ZMAX 7.6*cm

:VOLU "primary collimator_0" TUBE 0 $RMAX ($PC_ZMAX-$PC_ZMIN)/2. G4_W
:COLOR "primary collimator_0"  0 1 0
:VOLU "primary collimator_1" CONE 0 4 0 20 ($PC_ZMAX-$PC_ZMIN)/2. G4_AIR
:COLOR "primary collimator_1"  0.5 0.5 0.5
:PLACE "primary collimator_0"  1 expHall RM0  0. 0. ($PC_ZMIN+$PC_ZMAX)/2.
:PLACE "primary collimator_1"  1 "primary collimator_0"  RM0  0. 0. 0. 

// Flattening filter
:MIXT SiFeMn 8. 3 
       G4_Si 1./3.
       G4_Fe 1./3.
       G4_Mn 1./3.

:VOLU "flattening filter" POLYCONE 0. 360.*deg 5
 0. 0. 1.25
 10. 0. 9.
 17. 0. 13.8
 17. 0. 27.8
 18. 0. 27.8
SiFeMn
:PLACE "flattening filter" 0 expHall RM0 0. 0. 8.*cm

// Monitor
:VOLU monitor TUBE 0. 100. 15. G4_AIR
:PLACE monitor 1 expHall RM0 0. 0. 150. 


// Detector
:VOLU Detector BOX 200 200. 5. G4_AIR
:PLACE Detector 1 expHall RM0 0. 0. 1005

// Jaws

:VOLU jaws_X1 BOX 10*cm 10*cm 5*cm G4_W 
:COLOR jaws_X1  1 0 1
:PLACE jaws_X1 1 expHall RM1 -$JawsX_Centre_X 0. 300.


:VOLU jaws_X2 BOX 10*cm 10*cm 5*cm G4_W 
:COLOR jaws_X2  1 0 1
:PLACE jaws_X2 1 expHall RM3 $JawsX_Centre_X 0. 300.



:VOLU jaws_Y1 BOX 10*cm 10*cm 5*cm G4_W 
:COLOR jaws_Y1  1 0 1
:PLACE jaws_Y1 1 expHall RM2 0. $JawsY_Centre_Y  420.

:VOLU jaws_Y2 BOX 10*cm 10*cm 5*cm G4_W 
:COLOR jaws_Y2  1 0 1
:PLACE jaws_Y2 1 expHall RM4 0. -$JawsY_Centre_Y  420.


