wt = 1.5;
clear = 0.5;
tg = 25.4/8;
hb= 29;
bclear = 4.7;
bhd = 2.75;
tapdia = 1.5;
nutdia = 4*2/sqrt(3)+0*clear;
zlip = hb/2-tg-bclear/2;
ri = 2+clear;
ro = ri+wt;
blip = 7;
zbacklip = -hb/2+tg+blip/2;
lipw = 10;
ep = 0.01;
rboard = 69;
hbl = 2;
wbl = 3;
tt=1;
ta = 1.414;
piThick=5;
sinkThick=1.5;
boardThick=25.4/16;
hboard = hb/2-tg-boardThick/2-bclear;
standoff=3.7;
$fs = 0.25 ;
$fa = 1;
nf = 8;
bs=3;
//$fn = 10;
include <tile.scad>
include <decoration2.scad>

module rpi() {
    translate([0,0,standoff/2]){ 
        translate([-11.5,0,standoff/2+piThick/2]) cube([30,65,piThick],center=true);
        translate([0,0,0]) cube([.2*25.4,2*25.4,standoff],center=true);
    }
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
        //translate([0,0,25.4/32]) topCopper();
      translate([0,0,-25.4/32])bottomMask();
        //translate([0,0,25.4*(1/32+.01)]) topSilk();
        for (x= [12.2:6.5:115]){
            for(y=[19:5.5:46.5]){
                translate([x,y,2.2]) led();
            }
        }
    }
    /*difference(){
        cube([121.5,68,25.4/16],center=true);
        translate([56.75,29,0]) cylinder(r=1.25,h=100,center=true);
        translate([56.75,-29,0]) cylinder(r=1.25,h=100,center=true);
        translate([33.75,-29,0]) cylinder(r=1.25,h=100,center=true);
        translate([-57.25,29,0]) cylinder(r=1.25,h=100,center=true);
        translate([-57.25,-29,0]) cylinder(r=1.25,h=100,center=true);}*/

    
     translate([-60.75,-34,0]) {
         translate([6.05,11.75,-25.4/32]) usbub();
         translate([80.93,12.21,-25.4/32]) usba();
     }
 //    translate([0,0,-1.6]) rotate([0,0,0]) auxBoard();
     //translate([42.5,0,-5]) rotate([180,0,90]) omega();
     translate([-60.75+4.626*25.4,0,-25.4/32]) rotate([180,0,0])rpi();
     
     //rotate([0,0,180]) translate([-2,0,-13.4]) batteryPack();
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
module bottomMask() {
    scale(25.4)
    linear_extrude(height=0.01,center=true,convexity=10)
        import(file="MASK2.DXF");
}

module cornerBlock(t) {
            translate([-4-clear-wt+ep,-5-clear-wt+ep,-t/2]) {
                cube([4+bhd/2+2*wt+clear,5+clear+wt,t]);
                cube([4+clear+wt,5+bhd/2+2*wt+clear,t]);
            }
            cylinder(r=bhd/2+wt,h=t,center=true);

}
module cornerBlockShort(t) {
            translate([-4-clear-wt+ep,-5-clear-wt+ep,-t/2]) {
                cube([5.5+bhd/2+2*wt+clear,3.75+clear+wt,t]);
                cube([5.5+clear+wt,3.75+bhd/2+2*wt+clear,t]);
            }
            translate([1.5,-1.25,0])cylinder(r=bhd/2+wt,h=t,center=true);

}
module fifthBlock(t) {
            translate([-bhd/2-wt,-5-clear-wt,-t/2]) {
                cube([bhd+2*wt,5+clear+wt,t]);

            }
            cylinder(r=bhd/2+wt,h=t,center=true);

}
module backCornerBlock(t,w) {
        difference() { 
            union() {
                translate([-4-clear-wt+ep,-4-clear-wt+ep,-t/2]) {
                    cube([w+clear+wt,4+clear+wt,t]);
                    cube([w+clear-(wt+bhd/2)+wt,4+bhd/2+wt+clear+wt,t]);
                }
                translate([w-4-bhd/2-wt,0,0])cylinder(r=bhd/2+wt,h=t,center=true);
            }
            cylinder(r=tapdia/2,h=100,center=true);
        }
}

module taperCut() {
        rotate_extrude(convexity=4) {
            difference(){
                translate([0,-1]) square([clear+(tt+wt)/ta,tt+wt+1]);
                translate([clear+(tt+wt)/ta,0]) scale([1/ta,1]) circle(r=tt+wt,center=true);
                translate([clear,-1]) square([clear+(tt+wt)/ta+ep,1]);
            }
        }
}

module sink() {
    radi=2;
    topClear = 19;
    sideClear = 7;
   
        linear_extrude(height=sinkThick,center=true) {
             difference() {
        square([121.5+2*clear+2*wt-ep,68+2*clear+2*wt-ep],center=true);
        //LED drivers cutout
            translate([.75,34+clear-(topClear+clear)/2]) {
                square([121.5-2*sideClear-2*radi+3,topClear+clear+ep],center=true);
                square([121.5-2*sideClear+3,topClear+clear-2*radi+ep],center=true);
            }
//            translate([60.75-sideClear-radi,34-topClear+radi])
//                square(2*radi,center=true);
            translate([60.75-sideClear-1+.1,34-topClear-1])
                difference() {
                    square(1);
                    circle(r=1,center=true);
                }
            translate([(60.75-sideClear-radi)-0.75,34-topClear+radi]) 
                circle(r=radi,center=true);
            translate([-(60.75-sideClear-radi)-0.75,34-topClear+radi]) 
                circle(r=radi,center=true);
            translate([60.75-sideClear-radi-0.75,34+clear-radi]) 
                circle(r=radi,center=true);
            translate([-(60.75-sideClear-radi)-.75,34+clear-radi]) 
                circle(r=radi,center=true);
        // Header cutout
            translate([-60.75+4.626*25.4,2]) minkowski(){
                square([2*(3-clear),2*25.4+4],center=true);
                circle(r=clear,center=true);
            }
        // USB A cutout
                minkowski(){
                    translate([80.93-60.75,-34+8-clear-ep])
                        square([16,14.1],center=true);
                    circle(r=1,center=true);
                }
        // 4622 cutout
                minkowski(){
                    translate([0.5,-34+7-clear-ep])
                        square([4,6],center=true);
                    circle(r=1,center=true);
                }
        // Power in cutout
                minkowski(){
                    translate([20-60.75-clear-ep,-34+8.75-clear-ep])
                        square([38.2,15.6],center=true);
                    circle(r=1,center=true);
                }


        }
        //translate([114.5-60.75,34-topClear/2]) square([1.5,topClear+2*clear+ep],center=true);
        //translate([114.5-60.75,34-topClear-clear]) circle(r=0.75,center=true);
    }
    translate([114.5-60.75,34-topClear/2,-1]) rotate([90,0,0]) {
        cylinder(r=1,h=topClear+2*clear+2*wt-ep,center=true);
        translate([0,0,(topClear+2*clear+2*wt-ep)/2]) sphere(r=1,center=true);
    }
}

module batteryShelf() {
    translate([-17,0,-3]){
        translate([0,0,0.4]) tiling(2,54+2*clear,68+2*clear+2*wt-ep,0.95,nf);
        translate([0,0,-0.4+ep])
            rotate([180,0,0]) tiling(2,54+2*clear+ep,68+2*clear+2*wt-ep,0.95,nf);
        s = 54/(4+sqrt(3));
        for (angle=[0:60:359]) {
            rotate([0,0,angle]) {
                translate([s,0,0]) 
                    cylinder(r=0.8,h=hboard+3-boardThick/2-sinkThick/2);
            }
            for (angle = [0:180:359]) rotate([0,0,angle]){
                translate([s*(1+sqrt(3)/2),s/2,0])
                    cylinder(r=0.8,h=hboard+3-boardThick/2-sinkThick/2);
                rotate([0,0,-60]) translate([s*(1+sqrt(3)/2),s/2,0])
                    cylinder(r=0.8,h=hboard+3-boardThick/2-sinkThick/2);
                translate([s*(1+sqrt(3)/2),-s/2,0])
                    cylinder(r=0.8,h=hboard+3-boardThick/2-sinkThick/2);
                rotate([0,0,60]) translate([s*(1+sqrt(3)/2),-s/2,0])
                    cylinder(r=0.8,h=hboard+3-boardThick/2-sinkThick/2);
                translate([s*(2+sqrt(3)/2)-.4,s/2,0])
                    cylinder(r=0.8,h=hboard+3-boardThick/2-sinkThick/2);
                translate([s*(2+sqrt(3)/2)-.4,-s/2,0])
                    cylinder(r=0.8,h=hboard+3-boardThick/2-sinkThick/2);
                translate([s*(2+sqrt(3)/2)-.4,s*(1/2+sqrt(3)/2),0])
                    cylinder(r=0.8,h=hboard+3-boardThick/2-sinkThick/2);
                translate([s*(2+sqrt(3)/2)-.4,-s*(1/2+sqrt(3)/2),0])
                    cylinder(r=0.8,h=hboard+3-boardThick/2-sinkThick/2);
            }
        }
    }
}
module case() {
    difference() {
        union() {
            for (rangle = [0:180:359]) rotate([0,0,rangle]) {     
                difference(){
                    translate([60.75+clear-ri/2+ep,34+clear-ri/2+ep,0])
                        cube([ri+2*wt,ri+2*wt,hb],center=true);
                    translate([60.75+clear-ri,34+clear-ri,0]) cylinder(r=ri,h=100,center=true);
                                translate([60.75+clear-ri-wt/2,34+clear-ri,0]) cube([wt,2*ri,100],center=true);
                translate([60.75+clear-ri,34+clear-ri-wt/2,0]) cube([2*ri,wt,100],center=true);
                }
                mirror([0,1,0])
                difference(){
                    translate([60.75+clear-ri/2+ep,34+clear-ri/2+ep,0])
                        cube([ri+2*wt,ri+2*wt,hb],center=true);
                    translate([60.75+clear-ri,34+clear-ri,0]) cylinder(r=ri,h=100,center=true);
                    translate([60.75+clear-ri-wt/2,34+clear-ri,0]) cube([wt,2*ri,100],center=true);
                translate([60.75+clear-ri,34+clear-ri-wt/2,0]) cube([2*ri,wt,100],center=true);

                }
            }
            decoration();
            for (zoff = [-hb/2+1,hb/2-1]){
                    for(xoff=[-60.75-clear-bs/2,60.75+clear+bs/2]) {
                        translate([xoff,0,zoff]) scale([bs/2,1,1])
                            rotate([90,0,0]) cylinder(r=1,h=68+bs+2*clear,center=true);
                        for(yoff=[-34-clear-bs/2,34+clear+bs/2])
                            translate([xoff,yoff,zoff]) 
                                 scale([bs/2,bs/2,1]) sphere(r=1,center=true);
                    }
                    for(yoff=[-34-clear-bs/2,34+clear+bs/2])
                        translate([0,yoff,zoff]) scale([1,bs/2,1])rotate([0,90,0]) cylinder(r=1,h=121.5+bs+2*clear,center=true);
            }
          
                
                translate([0,0,hboard-boardThick/2-sinkThick/2]) sink();    
                union() {
                    translate([-60.75,-34,0]) {
                        translate([0,0,hboard-boardThick/2-standoff/2]) {
                            translate([3.5,5,standoff/2-wt/2]) cornerBlockShort(wt);
                            translate([117.5,5,0]) mirror([1,0,0]) cornerBlock(standoff);
                            translate([117.5,63,0]) rotate([0,0,180]) cornerBlock(standoff);
                            translate([94.5,5,0]) mirror([1,0,0]) fifthBlock(standoff);
                        }
                        translate([0,0,zbacklip]){
                            translate([3.5,64,0]) mirror([0,1,0]) backCornerBlock(blip,12);
                            translate([117.5,64,0]) rotate([0,0,180]) backCornerBlock(blip,7.5);
                            translate([3.5,4,0]) backCornerBlock(blip,12);
                            translate([117.5,4,0]) mirror([1,0,0]) backCornerBlock(blip,7.5);
                        }   
                    }
                    batteryShelf();   
                }
                translate([-60.75,-34,0]) {
                    translate([80.93,-clear-wt/2+.1,hb/2-tg-0.8-bclear-25.4/32-6.9/2])
                        cube([14.5+2*clear+2*wt,wt,7.12+2*clear+2*wt],center=true);
                    translate([-clear-wt/2,11.75,hb/2-tg-0.8-bclear-25.4/32-2.66/2]) 
                        cube([wt,8+2*clear+2*wt,2.66+2*clear+2*wt],center=true);
                }
        }
        translate([-60.75,-34,0]) {
            translate([80.93,-clear,hb/2-tg-0.8-bclear-25.4/32-6.9/2]) 
                minkowski() {
                    cube([14.5,ep,7.12],center=true);
                    rotate([90,0,0]) taperCut();
             }
            translate([-clear,11.75,hb/2-tg-0.8-bclear-25.4/32-2.66/2]) 
                minkowski() {
                    cube([ep,8,2.66],center=true);
                    rotate([0,-90,0]) taperCut();   
            }
            translate([3.5,63,50]) cylinder(r=bhd/2,h=100,center=true);
            translate([3.5,5,50]) cylinder(r=bhd/2,h=100,center=true);
            translate([3.5,5+bhd/2,50]) cube([bhd,bhd,100],center=true);
            translate([117.5,5,50]) cylinder(r=bhd/2,h=100,center=true);
            translate([117.5,63,50]) cylinder(r=bhd/2,h=100,center=true);
            translate([94.5,5,50]) cylinder(r=bhd/2,h=100,center=true);
        }
    }
}

//difference(){
//   union(){
case();
//taperCut();
//translate([0,0,hb/2-tg/2]) cube([121.5+2*clear,68+2*clear,tg-.001],center=true);

//translate([0,0,hboard]) { board();}
//}
        
//       translate([0,34,hboard+25.4/32]) rotate([0,0,0]) translate([0,-34,-25.4/32]) board();
//}

//translate([0,0,-hb/2+tg/2]) cube([121.5+2*clear,68+2*clear,tg-.001],center=true);
//}
// translate([0,-70,-3.7]) cube(100);
//}
