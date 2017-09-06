:P phantom_size 20*cm
:P phantom_z_center 20*cm
:ROTM RM0 0 0 0
:VOLU expHall BOX 50*cm 50*cm 150*cm G4_AIR
:VIS expHall OFF

// phantom 
:VOLU phantom BOX $phantom_size  $phantom_size $phantom_size G4_Water
:COLOR phantom  0 0.1 1
:PLACE phantom  1 expHall RM0 0.0 0.0 $phantom_z_center

