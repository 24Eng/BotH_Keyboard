// The keycap stem is from rsheldii from their amazing
// keycap model.
// https://www.thingiverse.com/thing:468651


printSelector = 3;
shaftThickness = 7;
shaftHeight = 10;
boltDiameter = 2;
fingerPadDiameter = 15;
fingerPadThickness = 2;
nutMajorDiameter = 4.4;
nutThickness = 1.5;
washerThickness = 0.75;
keycapHeight = 14;
keycapAngle = 30;

nutMajorRadius = nutMajorDiameter/2;
fingerPadRadius = fingerPadDiameter/2;
boltRadius = boltDiameter/2;
shaftFillet = 1;
roundedShaftSide = shaftThickness - shaftFillet;
roundedShaftHeight = shaftHeight+1.001 - shaftFillet;
existingKeyshaftHeight = 3.99;

$fn = 36;
//$vpr = [70,0,25+$t*360];
$vpd = 100;
$vpt = [0,0,6];

if(printSelector == 0){
    color("red")KeyShaft();
    color("blue"){
        translate([0,0,existingKeyshaftHeight+shaftHeight+boltRadius+fingerPadThickness/2+fingerPadRadius/2]){
            rotate([180,0,0]){
                FingerPad();
            }
        }
    }
}

if(printSelector == 1){
    KeyShaft();
}

if(printSelector == 2){
    FingerPad();
}

if(printSelector == 3){
    RoundedKeycap(keycapHeight, keycapAngle);
}


// 24Eng // B.o.t.H. // Back of the Hand // Modules // 24Eng //
// 24Eng // B.o.t.H. // Back of the Hand // Modules // 24Eng //

module FingerPad(){
    cylinder(fingerPadThickness, fingerPadRadius, fingerPadRadius, center=true);
    rotate([0,0,0]){
        translate([shaftThickness/2+washerThickness,-fingerPadRadius/2,0]){
            difference(){
                translate([0,0,0]){
                    cube([fingerPadThickness, fingerPadRadius, fingerPadThickness/2+fingerPadRadius/2]);
                    translate([fingerPadThickness/2,fingerPadRadius/2,fingerPadRadius/2+fingerPadThickness/2]){
                        rotate([0,90,0]){
                            cylinder(fingerPadThickness, fingerPadRadius/2, fingerPadRadius/2, center=true);
                        }
                    }
                }
                translate([fingerPadThickness/2,fingerPadRadius/2,fingerPadRadius/2+fingerPadThickness/2]){
                    rotate([0,90,0]){
                        cylinder(fingerPadThickness*2, boltRadius, boltRadius, center=true);
                        translate([0,0,0])cylinder(nutThickness, nutMajorRadius, nutMajorRadius, $fn=6);
                    }
                }
            }
        }
    }
    rotate([0,0,180]){
        translate([shaftThickness/2+washerThickness,-fingerPadRadius/2,0]){
            difference(){
                translate([0,0,0]){
                    cube([fingerPadThickness, fingerPadRadius, fingerPadThickness/2+fingerPadRadius/2]);
                    translate([fingerPadThickness/2,fingerPadRadius/2,fingerPadRadius/2+fingerPadThickness/2]){
                        rotate([0,90,0]){
                            cylinder(fingerPadThickness, fingerPadRadius/2, fingerPadRadius/2, center=true);
                        }
                    }
                }
                translate([fingerPadThickness/2,fingerPadRadius/2,fingerPadRadius/2+fingerPadThickness/2]){
                    rotate([0,90,0]){
                        cylinder(fingerPadThickness*2, boltRadius, boltRadius, center=true);
                    }
                }
            }
        }
    }
}

module KeyShaft(){
    import("rsheldiii_keycap_stem.stl", convexity=10);
    difference(){
        translate([0,0,existingKeyshaftHeight + shaftHeight/2+boltDiameter*0.75]){
            minkowski(){
                cube([roundedShaftSide, roundedShaftSide, roundedShaftHeight+boltDiameter*1.5], center=true);
                cylinder(0.01, shaftFillet/2, shaftFillet/2, center=true);
            }
        }


        translate([0,0,existingKeyshaftHeight+shaftHeight+boltRadius]){
            rotate([0,90,0]){
                cylinder(shaftThickness*2, boltRadius, boltRadius, center=true);
            }
        }
    }
}

module RoundedKeycap(RKHeight, RKAngle){
    keyswitchSideLength = 15.6;
    keycapSideLength = keyswitchSideLength + 2*2;
    RKCavityDepth = 6.6 + 3.6 - 3.99;
    RKThickness = 2;
    RKRounding = 2;
    RKCylinderRadius = keyswitchSideLength/2;
    import("rsheldiii_keycap_stem.stl", convexity=10);
    difference(){
        translate([0,0,-RKCavityDepth/2+existingKeyshaftHeight+RKThickness]){
            minkowski(){
                cube([keycapSideLength, keycapSideLength, RKCavityDepth], center=true);
                sphere(RKRounding);
            }
        }
        translate([0,0,-RKCavityDepth/2+existingKeyshaftHeight-RKRounding/2]){
            minkowski(){
                cube([keycapSideLength-RKThickness, keycapSideLength-RKThickness, RKCavityDepth], center=true);
                sphere(RKRounding/2);
            }
        }
    }
    minkowski(){
        difference(){
            translate([0,0,existingKeyshaftHeight+RKRounding]){
                cylinder(RKHeight+RKCylinderRadius, RKCylinderRadius, RKCylinderRadius, center=false);
            }
            translate([0,0,existingKeyshaftHeight + RKHeight + RKCylinderRadius]){
                rotate([RKAngle,0,0]){
                    cube([RKCylinderRadius*6, RKCylinderRadius*6, RKCylinderRadius*2], center=true);
                }
            }
        }
        sphere(RKRounding);
    }
}





        translate([0,0,0]){
            
        }