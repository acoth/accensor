wt = 3;
clear = 0.5;
tg = 25.4/8;
hb= 28.5;
bclear = 4.7;
bhd = 2.75;
tapdia = 1.5;
nutdia = 4*2/sqrt(3)+0*clear;
zlip = hb/2-tg-bclear/2;
ri = 2+clear;
ro = 2+clear+wt/2;
blip = 7;
zbacklip = -hb/2+tg+blip/2;
lipw = 10;
ep = 0.01;
rboard = 69;
hboard = hb/2-tg-25.4/32-bclear;
hbl = 2;
wbl = 3;

include <tile.scad>
/*difference() {
    cube([111.2,68.2,30],center=true);
    translate([0,0,-15]) cube([108,65,50],center=true);
    translate([0,0,15]) cube([108,65,8],center=true);
}*/

module rpi() {
    translate([0,0,-2.5]){translate([-11.5,0,-2.8]) cube([30,65,1.6],center=true);
    cube([.2*25.4,2*25.4,5],center=true);}
}

module omega(){
    cube([42.9,26.4,3.9],center=true);
    translate([0,12.2,-2.95]) cube([32,2,2],center=true);
    translate([0,-12.2,-2.95]) cube([32,2,2],center=true);
}
module auxBoard(){
    cube([121.5,40,25.4/16],center=true);
    translate([32.5,0,-4.25]) rotate([180,0,180]) omega();
}

module battery() {
    cube([101.5,67.5,3.7],center=true);
    translate([55.75,12.25,0]) cube([10,5,0.1],center=true);
    translate([55.75,-12.25,0]) cube([10,5,0.1],center=true);
}

module batteryPack() {
    translate([0,0,1.9]) battery();
    translate([0,0,-1.9]) battery();
    translate([55.75,0,0]) cube([8,40,1.6],center=true);
}

module led() {
    cube([3.5,3.4,2.8],center=true);
}

module usba() {
    translate([0,7-12.99,-6.9/2])cube([13.1,14,6.90],center=true);
}

module usbub() {
    translate([3.3-6.15,0,-2.66/2]) cube([6.6,8,2.66],center=true);
}
module board() {
    translate([-60.75,-34,0]) {
        translate([0,0,25.4/32]) topCopper();
      //translate([0,0,-25.4/32])bottomCopper();
        //translate([0,0,25.4*(1/32+.01)]) topSilk();
        for (x= [12.2:6.5:115]){
            for(y=[19:5.5:46.5]){
                translate([x,y,2.2]) led();
            }
        }
    }
    /*difference(){
        cube([121.5,68,25.4/16],center=true);
        translate([56.75,29,0]) cylinder(r=1.25,h=100,center=true,$fn=100);
        translate([56.75,-29,0]) cylinder(r=1.25,h=100,center=true,$fn=100);
        translate([33.75,-29,0]) cylinder(r=1.25,h=100,center=true,$fn=100);
        translate([-57.25,29,0]) cylinder(r=1.25,h=100,center=true,$fn=100);
        translate([-57.25,-29,0]) cylinder(r=1.25,h=100,center=true,$fn=100);}*/

    
     translate([-60.75,-34,0]) {
         translate([6.05,11.75,-25.4/32]) usbub();
         translate([80.93,12.21,-25.4/32]) usba();
     }
 //    translate([0,0,-1.6]) rotate([0,0,0]) auxBoard();
     //translate([42.5,0,-5]) rotate([180,0,90]) omega();
     //translate([-60.75+4.626*25.4,0,-25.4/32]) rpi();
     
     //rotate([0,0,180]) translate([-2,0,-11.8]) batteryPack();
}   

module topCopper() {
    scale(25.4)
    linear_extrude(height=.01,center=true,convexity=10)
        import(file="LAYER1.DXF");
}
module topSilk() {
    scale(25.4)
    linear_extrude(height=.01,center=true,convexity=10)
        import(file="SILK1.DXF");
}

module bottomCopper() {
    scale(25.4)
    linear_extrude(height=.01,center=true,convexity=10)
        import(file="LAYER4.DXF");
}

module cornerBlock(t) {
            translate([-4-clear,-5-clear,-t/2]) {
                cube([4+nutdia/2+wt/2+clear,5+clear,t]);
                cube([4+clear,5+nutdia/2+wt/2+clear,t]);
            }
            cylinder(r=nutdia/2+wt/2,h=t,$fn=100,center=true);

}
module fifthBlock() {
            translate([-27-clear,-5-clear,-bclear/2]) {
                cube([27+bhd/2+wt+clear,5+clear,bclear]);
                cube([27+clear,5+bhd/2,bclear]);
            }
            cylinder(r=bhd/2+wt,h=bclear,$fn=100,center=true);

}
module backCornerBlock(t,w) {
        difference() { 
            union() {
                translate([-4-clear,-4-clear,-t/2]) {
                    cube([w,4+clear,t]);
                    cube([w-(wt+clear+bhd/2),4+bhd/2+wt+clear,t]);
                }
                translate([w-4-(wt+clear+bhd/2),0,0])cylinder(r=bhd/2+wt,h=t,$fn=100,              center=true);
            }
            cylinder(r=tapdia/2,h=100,$fn=100,center=true);
        }
}

module case() {
    difference(){
    union() {
        difference(){
             minkowski() {
                union() {
                    translate([0,-34-clear-0.75*wt+ep,0]) rotate([0,90,90]) 
                        tiling(1,hb,121.5+2*clear-1*ro,wt/2);
                    translate([0,34+clear+0.75*wt-ep,0]) rotate([0,90,90]) 
                        tiling(1,hb,121.5+2*clear-1*ro,wt/2);
                    translate([60.75+clear+0.75*wt-ep,0,0]) rotate([90,90,90])
                        tiling(1,hb,68+2*clear-1*ro,wt/2);
                    translate([-(60.75+clear+0.75*wt-ep),0,0]) rotate([90,90,90])
                        tiling(1,hb,68+2*clear-1*ro,wt/2);
                    cube([121.5+2*clear+wt,68+2*clear+wt-2*ro,hb],center=true);
                    cube([121.5+2*clear+wt-2*ro,68+2*clear+wt,hb],center=true);
                    //translate([60.75+wt/2+clear-ro,34+wt/2+clear-ro,0]) cylinder(r=ro+wt/2,h=hb,$fn=100,center=true);
                    //translate([-(60.75+wt/2+clear-ro),34+wt/2+clear-ro,0]) cylinder(r=ro+wt/2,h=hb,$fn=100,center=true);
                    //translate([60.75+wt/2+clear-ro,-(34+wt/2+clear-ro),0]) cylinder(r=ro+wt/2,h=hb,$fn=100,center=true);
                    //translate([-(60.75+wt/2+clear-ro),-(34+wt/2+clear-ro),0]) cylinder(r=ro+wt/2,h=hb,$fn=100,center=true);
                }
//                sphere(r=wt/2,center=true,$fn=9);
            }
            cube([121.5+2*clear-2*ri,68+2*clear,hb+10],center=true);
            cube([121.5+2*clear,68+2*clear-2*ri,hb+10],center=true);
            translate([60.75+clear-ri,34+clear-ri,0]) cylinder(r=ri,h=100,$fn=100,center=true);
                translate([-(60.75+clear-ri),34+clear-ri,0]) cylinder(r=ri,h=100,$fn=100,center=true);
                translate([60.75+clear-ri,-(34+clear-ri),0]) cylinder(r=ri,h=100,$fn=100,center=true);
                translate([-(60.75+clear-ri),-(34+clear-ri),0]) cylinder(r=ri,h=100,$fn=100,center=true);
        }
        
            union() {
                translate([-60.75,-34,0]) {
                    translate([0,0,zlip]) {
                        translate([3.5,5,0]) cornerBlock(bclear);
                        translate([3.5,63,0]) mirror([0,1,0]) cornerBlock(bclear);
                        translate([117.5,5,0]) mirror([1,0,0]) cornerBlock(bclear);
                        translate([117.5,63,0]) rotate([0,0,180]) cornerBlock(bclear);
                        translate([94.5,5,0]) mirror([1,0,0]) fifthBlock(bclear);
                    }
                    translate([0,0,zbacklip]){
                        translate([3.5,64,0]) mirror([0,1,0]) backCornerBlock(blip,12);
                        translate([117.5,64,0]) rotate([0,0,180]) backCornerBlock(blip,7.5);
                        //translate([9-clear,66.5,0]) cube([6,5.5,blip],center=true);
                    }
                    
                }
                translate([-20,34+clear+ep-wbl/2,hb/2-tg-0.8-bclear-25.4/32-6.9+hbl/2]) cube([81.5+2*clear,wbl,hbl],center=true);
                difference() {
                    translate([-60.75-clear-ep/2,-34-clear-ep,-hb/2+tg]) cube([121.5+2*clear+ep,10,hboard+hb/2-tg]);
                    translate([0,34+clear,hboard]) rotate([0,90,0])                
                        rotate_extrude(convexity=4,$fn=1000) 
                            intersection() {
                                minkowski(){
                                    union() {
                                        square([67*2,117.5],center=true);
                                        translate([67,20.18]) square([2,13],center=true);
                                    }
                                    circle(2+clear+ep);
                                }
                                translate([500,0]) square([1000,1000],center=true);
                            }
                    
                    //translate([0,34+clear,hboard]) rotate([0,90,0]) cylinder(r=rboard+clear,h=117.5+2*clear,$fn=1000,center=true);
                    }
                
            }
        }
            translate([-60.75,-34,0]) {
                
                translate([80.93,12.21,hb/2-tg-0.8-bclear-25.4/32-6.9/2]) 
                    minkowski() {
                        cube([14.5,50,7.12],center=true);
                        sphere(r=clear,center=true,$fn=100);
                    }
                translate([6.05,11.75,hb/2-tg-0.8-bclear-25.4/32-2.66/2]) 
                    minkowski() {
                        cube([30,8,2.66],center=true);
                        sphere(r=clear,center=true,$fn=100);
                    }
                translate([3.5,63,50]) cylinder(r=nutdia/2,h=100,center=true,$fn=100);
                translate([3.5,5,50]) cylinder(r=nutdia/2,h=100,center=true,$fn=100);
                translate([117.5,5,50]) cylinder(r=nutdia/2,h=100,center=true,$fn=100);
                translate([117.5,63,50]) cylinder(r=nutdia/2,h=100,center=true,$fn=100);
                translate([94.5,5,50]) cylinder(r=nutdia/2,h=100,center=true,$fn=100);
            }
        
    }
}

//difference(){
//   union(){
case();
//translate([0,0,hb/2-tg/2]) cube([121.5+2*clear,68+2*clear,tg-.001],center=true);

//translate([0,0,hboard]) {
        
//       translate([0,34,hboard+25.4/32]) rotate([0,0,0]) translate([0,-34,-25.4/32]) board();
//}

//translate([0,0,-hb/2+tg/2]) cube([121.5+2*clear,68+2*clear,tg-.001],center=true);
//}
 //translate([0,-70,-2.7]) cube(100);
//}
