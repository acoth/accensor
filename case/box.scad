wt = 1.6;
clear = 0.1;
tg = 25.4/8;
hb= 35;
bclear = 4.7;
bhd = 2.75;
zlip = hb/2-tg-bclear/2;

/*difference() {
    cube([111.2,68.2,30],center=true);
    translate([0,0,-15]) cube([108,65,50],center=true);
    translate([0,0,15]) cube([108,65,8],center=true);
}*/

module rpi() {
    cube([30,65,1.6],center=true);
    translate([11.5,0,2.8]) cube([.2*25.4,2*25.4,5],center=true);
}

module battery() {
    cube([72,38,19],center=true);
}

module led() {
    cube([3.5,3.4,2.8],center=true);
}

module usba() {
    cube([13.1,14,7],center=true);
}

module usbub() {
    cube([6.6,8,2.66],center=true);
}
module board() {
    difference(){
        cube([115,65,25.4/16],center=true);
        translate([54,29,0]) cylinder(r=1.25,h=10,center=true,$fn=30);
        translate([54,-29,0]) cylinder(r=1.25,h=10,center=true,$fn=30);
        translate([31,29,0]) cylinder(r=1.25,h=10,center=true,$fn=30);
        translate([31,-29,0]) cylinder(r=1.25,h=10,center=true,$fn=30);
        translate([-54.5,29.5,0]) cylinder(r=1.25,h=10,center=true,$fn=30);}

    for (x= [-53:6.5:45]){
        for(y=[-19.5:5.5:8]){
            translate([x,y,2.2]) led();
         }
     }
     translate([-57.5,-32.5,0]) {
         translate([3.3,4.64,-2.13]) usbub();
         translate([75.43,6.92,-4.3]) usba();
     }
     translate([42.5,0,-5]) rpi();
     translate([-15,1,-10.6]) battery();
}   

module case() {
    union() {
        difference(){
            cube([115+2*(wt+clear),65+2*(wt+clear),hb],center=true);
            cube([115+2*clear,65+2*clear,hb+10],center=true);
        }
        difference(){
            union() {
                translate([-56.5,30,zlip]) 
                    cube([4,5.5,bclear],center=true);
                translate([-55,31.5,zlip]) 
                    cube([5.5,4,bclear],center=true);
                translate([-54.5,29.5,zlip]) cylinder(r=2.25,h=bclear,$fn=30,center=true);
                translate([56,-29.5,zlip]) 
                    cube([5,6.5,bclear],center=true);
                translate([54.5,-31.0,zlip]) 
                    cube([6.5,5,bclear],center=true);
                translate([54.0,-29.0,zlip]) cylinder(r=2.75,h=bclear,$fn=30,center=true);
                translate([56,29.5,zlip]) 
                    cube([5,6.5,bclear],center=true);
                translate([54.5,31.0,zlip]) 
                    cube([6.5,5,bclear],center=true);
                translate([54.0,29.0,zlip]) cylinder(r=2.75,h=bclear,$fn=30,center=true);
                translate([-57.5,0,zlip]) cube([2-clear,66,bclear],center=true);
                translate([0,-32,zlip]) cube([116,3-clear,bclear],center=true);
                                translate([0,32.5,zlip]) cube([116,3-clear,bclear],center=true);

                
            }
            translate([-10,-10,0]) cube([30,60,100],center=true);
            translate([-10,10,0]) cube([7.5,60,100],center=true);
            translate([54,29,0]) cylinder(r=bhd/2,h=100,center=true,$fn=30);
            translate([54,-29,0]) cylinder(r=bhd/2,h=100,center=true,$fn=30);
            translate([31,29,0]) cylinder(r=bhd/2,h=100,center=true,$fn=30);
            translate([31,-29,0]) cylinder(r=bhd/2,h=100,center=true,$fn=30);
            translate([-54.5,29.5,0]) cylinder(r=bhd/2,h=100,center=true,$fn=30);
        }
    }
}

difference(){
    union(){
case();
translate([0,0,hb/2-tg-0.8-bclear]) board();
//translate([0,0,hb/2-tg/2]) cube([4.625*25.4,2.625*25.4,tg],center=true);

//translate([0,0,-hb/2+tg/2]) cube([4.625*25.4,2.625*25.4,tg],center=true);
}
//translate([0,0,-50]) cube(100);
}
