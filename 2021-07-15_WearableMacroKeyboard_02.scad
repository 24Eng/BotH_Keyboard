// WearableMacroKeyboard by 24Eng
printSelection = 0;
thickness = 2;
platformThickness = 3;
palmWidth = 80;
fingerDistance = 25;
boltDiameter = 2;
boltHeadDiameter = 4.5;
boltHeadThickness = 1.5;
nutMajorDiameter = 4.4;
printerSlop = 0.1;
keyswitchHoleLength = 0.551 * 25.4;
keyswitchHoleWidth = 0.551 * 25.4;
keyswitchHoleThickness = 0.06 * 25.4;
keyswitchLength = 15.6;
keyswitchWidth = 15.6;
keyswitchThickness = 10;
watchBandLength = 31+thickness;
fingerPadSlope = 30;
keycapForwardDistance = 30;

BHLength = 50;
BHWidth = 25.75;
BHThickness = 2;
BHEdge = 0.8;
BHClearance = 12;
BHBoltDiameter = boltDiameter;
BHNutMajorDiameter = nutMajorDiameter;
BHMountOffset = 8;

boltRadius = boltDiameter/2 + printerSlop;
boltHeadRadius = boltHeadDiameter/2 + printerSlop;
nutMajorRadius = nutMajorDiameter / 2 + printerSlop;
platformWidth = (fingerDistance)*4;
platformLength = watchBandLength;
watchBandThickness = 8;


//$vpr = [70,0,55+360 * $t];
//$vpd = 150;
//$vpr = [55,0,25];
//$vpr = [90,0,0];
//$vpt = [0,0,10];
$fn=36;

if(printSelection == 0){
    color("powderblue"){
        // This platform portion touches the back of the palm (Metacarpals)
        MetacarpalPlatform();
        
        // This portion hovers over the fingers (proximal phalanges)
        ProximalPlatform();
        
//        // A cylinder at the joining area should keep the two platform halves from fracturing
//        translate([-platformWidth/2,platformLength/2,0]){
//            rotate([0,90,0]){
//                #cylinder(platformWidth, thickness/2, thickness/2);
//            }
//        }
        
    }
        // The board holder will support the microcontroller
    translate([-BHMountOffset,0,thickness/2]){
        rotate([0,0,270]){
            difference(){
                BoardHolder();
                translate([0,BHLength/2,BHClearance/2+BHThickness/2]){
                    rotate([90,0,0]){
                        EncoderHole();
                    }
                }
            }
        }
    }
    color("violet"){
        translate([-(BHWidth+BHMountOffset+watchBandThickness),-BHWidth/2-BHThickness,thickness/2]){
            difference(){
                translate([0,0,0]){
                    cube([platformWidth/2-BHWidth-BHMountOffset-watchBandThickness-0.5, BHWidth+BHThickness*2, BHClearance+BHThickness*1]);
                    translate([(platformWidth/-12),platformLength,thickness/2]){
                        rotate([fingerPadSlope,0,0]){
                            translate([0,keycapForwardDistance-12,0]){
                                difference(){
                                    cube([platformWidth, 20, 15]);
                                    translate([thickness,thickness,-0.01]){
                                        cube([platformWidth-thickness*2, 20-thickness*2, 15-thickness*2]);
                                    }
                                    translate([10,-2,0]){
                                        cube([platformWidth/2-BHWidth-BHMountOffset-watchBandThickness-1.5-thickness, thickness*3, BHClearance-thickness]);
                                    }
                                }
                            }
                        }
                    }
                    translate([(platformWidth/-12)+8,platformLength,thickness/2]){
                        rotate([fingerPadSlope,0,0]){
                            translate([0,-3,0]){
                                difference(){
                                    cube([platformWidth/2-BHWidth-BHMountOffset-watchBandThickness-0.5, BHWidth-4, BHClearance+1]);
                                   translate([thickness,0,0]){
                                       cube([platformWidth/2-BHWidth-BHMountOffset-watchBandThickness-1.5-thickness, BHWidth+BHThickness*1, BHClearance]);
                                   }
                                }
                            }
                        }
                    }
                }
                translate([(platformWidth/2-BHWidth-BHMountOffset-watchBandThickness)/2,thickness*1.5,0]){
                    cylinder(BHClearance*3, boltRadius, boltRadius, center=true);
                }
                translate([(platformWidth/2-BHWidth-BHMountOffset-watchBandThickness)/2,BHWidth+BHThickness*0.75,0]){
                    cylinder(BHClearance*3, boltRadius, boltRadius, center=true);
                }
                translate([thickness+0.01,thickness+0.01,0]){
                    cube([platformWidth/2-BHWidth-BHMountOffset-watchBandThickness-thickness, BHWidth*1.1, BHClearance]);
                }
            }
        }
    }
}

if(printSelection == 1){
    MetacarpalPlatform();
    ProximalPlatform();
}

if(printSelection == 2){
    color("violet"){
        translate([-(BHWidth+BHMountOffset+watchBandThickness),-BHWidth/2-BHThickness,thickness/2]){
            difference(){
                translate([0,0,0]){
                    cube([platformWidth/2-BHWidth-BHMountOffset-watchBandThickness-0.5, BHWidth+BHThickness*2, BHClearance+BHThickness*1]);
                    translate([(platformWidth/-12),platformLength,thickness/2]){
                        rotate([fingerPadSlope,0,0]){
                            translate([0,keycapForwardDistance-12,0]){
                                difference(){
                                    cube([platformWidth, 20, 15]);
                                    translate([thickness,thickness,-0.01]){
                                        cube([platformWidth-thickness*2, 20-thickness*2, 15-thickness*2]);
                                    }
                                    translate([10,-2,0]){
                                        cube([platformWidth/2-BHWidth-BHMountOffset-watchBandThickness-1.5-thickness, thickness*3, BHClearance-thickness]);
                                    }
                                }
                            }
                        }
                    }
                    translate([(platformWidth/-12)+8,platformLength,thickness/2]){
                        rotate([fingerPadSlope,0,0]){
                            translate([0,-3,0]){
                                difference(){
                                    cube([platformWidth/2-BHWidth-BHMountOffset-watchBandThickness-0.5, BHWidth-4, BHClearance+1]);
                                   translate([thickness,0,0]){
                                       cube([platformWidth/2-BHWidth-BHMountOffset-watchBandThickness-1.5-thickness, BHWidth+BHThickness*1, BHClearance]);
                                   }
                                }
                            }
                        }
                    }
                }
                translate([(platformWidth/2-BHWidth-BHMountOffset-watchBandThickness)/2,thickness*1.5,0]){
                    cylinder(BHClearance*3, boltRadius, boltRadius, center=true);
                }
                translate([(platformWidth/2-BHWidth-BHMountOffset-watchBandThickness)/2,BHWidth+BHThickness*0.75,0]){
                    cylinder(BHClearance*3, boltRadius, boltRadius, center=true);
                }
                translate([thickness+0.01,thickness+0.01,0]){
                    cube([platformWidth/2-BHWidth-BHMountOffset-watchBandThickness-thickness, BHWidth*1.1, BHClearance]);
                }
            }
        }
    }
}

if(printSelection == 3){
    difference(){
        BoardHolder();
        translate([0,BHLength/2,BHClearance/2+BHThickness/2]){
            rotate([90,0,0]){
                EncoderHole();
            }
        }
    }
}


// 24 Eng // Modules // 24 Eng // Modules // 24 Eng // Modules // 24 Eng // Modules 

module EncoderHole(){
    encoderShaftDiameter = 6.8;
    encoderShaftRadius = encoderShaftDiameter/2;
    encoderKeyWidth = 2.1;
    encoderKeyThickness = 0.8;
    encoderKeyOffset = 12.5/2;
    encoderPunctureDepth = 10;
    cylinder(encoderPunctureDepth, encoderShaftRadius, encoderShaftRadius, center=true);
    translate([0,encoderKeyOffset,0])cube([encoderKeyWidth,encoderKeyThickness,encoderPunctureDepth], center=true);
}

module CountersunkBolt(){
    cylinder(thickness*3, boltRadius, boltRadius, center=true);
    cylinder(thickness+0.001, boltHeadRadius, 0, center=true);
}

// This portion hovers over the fingers (proximal phalanges)
module ProximalPlatform(){
    difference(){
        translate([-platformWidth/2,platformLength/2,-thickness/2]){
            rotate([fingerPadSlope,0,0]){
                cube([platformWidth,keycapForwardDistance+keyswitchLength/2+thickness*2,thickness]);
            }
        }
        translate([-platformWidth/2,platformLength/2,0]){
            rotate([fingerPadSlope,0,0]){
                translate([fingerDistance/2,keycapForwardDistance,0]){
                    KeycapNegative();
                }
                translate([fingerDistance*1.5,keycapForwardDistance,0]){
                    KeycapNegative();
                }
                translate([fingerDistance*2.5,keycapForwardDistance,0]){
                    KeycapNegative();
                }
                translate([fingerDistance*3.5,keycapForwardDistance,0]){
                    KeycapNegative();
                }
            }
        }
    }
}

// This platform portion touches the back of the palm (Metacarpals)
module MetacarpalPlatform(){
    difference(){
        translate([0,0,0]){
            cube([platformWidth, platformLength, thickness], center=true);
            translate([platformWidth/2-watchBandThickness/2,0,watchBandThickness/2]){
                cube([watchBandThickness,platformLength*0.99,watchBandThickness], center=true);
            }
            translate([-platformWidth/2+watchBandThickness/2,0,watchBandThickness/2]){
                cube([watchBandThickness,platformLength*0.99,watchBandThickness], center=true);
            }
        }
        rotate([0,0,180]){
            translate([platformWidth/2-watchBandThickness/2,0,watchBandThickness/2]){
                AppleWatchBandCavity();
            }
        }
        rotate([0,0,0]){
            translate([platformWidth/2-watchBandThickness/2,0,watchBandThickness/2]){
                AppleWatchBandCavity();
            }
        }
        rotate([0,0,180]){
            translate([0, BHWidth/2-BHNutMajorDiameter/2-BHEdge,0]){
                CountersunkBolt();
            }
        }
        rotate([0,0,0]){
            translate([0, BHWidth/2-BHNutMajorDiameter/2-BHEdge,0]){
                CountersunkBolt();
            }
        }
        // Mounting holes for a cover
        translate([(platformWidth/2-boltHeadRadius-watchBandThickness-thickness),(platformLength/2-boltHeadRadius-thickness),0]){
            CountersunkBolt();
        }
        translate([-(platformWidth/2-boltHeadRadius-watchBandThickness-thickness),(platformLength/2-boltHeadRadius-thickness),0]){
            CountersunkBolt();
        }
        translate([(platformWidth/2-boltHeadRadius-watchBandThickness-thickness),-(platformLength/2-boltHeadRadius-thickness),0]){
            CountersunkBolt();
        }
        translate([-(platformWidth/2-boltHeadRadius-watchBandThickness-thickness),-(platformLength/2-boltHeadRadius-thickness),0]){
            CountersunkBolt();
        }
    }
}

module KeycapNegative(){
    cube([keyswitchHoleWidth, keyswitchHoleLength, keyswitchHoleThickness*1.01], center = true);
    translate([0,0,(keyswitchHoleThickness + keyswitchThickness)/2]){
        cube([keyswitchWidth, keyswitchLength, keyswitchThickness], center = true);
    }
    translate([0,0,(keyswitchHoleThickness + keyswitchThickness)/-2]){
        cube([keyswitchWidth, keyswitchLength, keyswitchThickness], center = true);
    }
}

module BoardHolder(){
    /* This function expects a few global parameters
    By placing them in the code, you can change them through
    services like Thingiverse.com
BHLength = ;
BHWidth = ;
BHThickness = ;
BHEdge = ;
BHClearance = ;
BHBoltDiameter = ;
BHNutMajorDiameter = ;
BHMountOffset = ;
    */
    BHNutMajorRadius = BHNutMajorDiameter/2;
    BHBoltRadius = BHBoltDiameter/2;
    BHTotalWidth = BHWidth+BHThickness*2;
    BHTotalLength = BHLength+BHThickness*1;
    BHTotalHeight = BHClearance+BHThickness*4;
    
    translate([0,0,BHTotalHeight/2-0.001]){
        color("orange"){
            difference(){
                translate([0,0,0]){
                    cube([BHTotalWidth, BHTotalLength, BHTotalHeight], center = true);
                }
                translate([0,-BHThickness/2-0.01,0]){
                    cube([BHWidth, BHLength, BHClearance*5], center = true);
                }
            }
            difference(){
                translate([0,0,BHTotalHeight/2-BHThickness/2]){
                    cube([BHTotalWidth, BHTotalLength, BHThickness], center = true);
                }
                translate([0,-BHThickness*2,0]){
                    cube([BHWidth-BHEdge*2, BHLength-BHEdge*2+BHThickness*2, BHClearance*5], center = true);
                }
            }
            difference(){
                translate([0,0,BHTotalHeight/2-BHThickness/2-BHThickness*2]){
                    cube([BHTotalWidth, BHTotalLength, BHThickness], center = true);
                }
                translate([0,-BHThickness*2,0]){
                    cube([BHWidth-BHEdge*2, BHLength-BHEdge*2+BHThickness*2, BHClearance*5], center = true);
                }
            }
            translate([BHWidth/2-BHNutMajorRadius-BHEdge,BHMountOffset,-BHTotalHeight/2]){
                difference(){
                    translate([0,0,0]){
                        #cylinder(BHThickness*2, BHNutMajorRadius+BHThickness, BHNutMajorRadius+BHThickness, $fn=36);
                        translate([0,-BHNutMajorRadius-BHThickness,0]){
                            cube([BHNutMajorRadius+BHThickness, BHNutMajorDiameter+BHThickness*2, BHThickness*2]);
                        }
                    }
                    cylinder(BHThickness*6, BHBoltRadius, BHBoltRadius, center=true);
                    translate([0,0,BHThickness]){
                        rotate([0,0,30]){
                            cylinder(BHThickness*2, BHNutMajorRadius, BHNutMajorRadius, $fn=6);
                        }
                    }
                }
            }
            rotate([0,0,180]){
                translate([BHWidth/2-BHNutMajorRadius-BHEdge,-BHMountOffset,-BHTotalHeight/2]){
                    difference(){
                        translate([0,0,0]){
                            cylinder(BHThickness*2, BHNutMajorRadius+BHThickness, BHNutMajorRadius+BHThickness, $fn=36);
                            translate([0,-BHNutMajorRadius-BHThickness,0]){
                                cube([BHNutMajorRadius+BHThickness, BHNutMajorDiameter+BHThickness*2, BHThickness*2]);
                            }
                        }
                        cylinder(BHThickness*6, BHBoltRadius, BHBoltRadius, center=true);
                        translate([0,0,BHThickness]){
                            rotate([0,0,30]){
                                cylinder(BHThickness*2, BHNutMajorRadius, BHNutMajorRadius, $fn=6);
                            }
                        }
                    }
                }
            }
        }
    }
}

module AppleWatchBandCavity(){
    rotate([90,0,0]){
        linear_extrude(height = watchBandLength, center = true, convexity = 10, slices = 20, scale = 1.0, $fn = 18){
            import("AppleWatchCavity.dxf", convexity=3);
        }
        translate([1,-10,0])cube([2.2,20,5.5], center=true);
    }
}


        translate([0,0,0]){
            rotate([0,0,0]){
                
            }
        }