//wt = 1.5;
//h = 0.5;


//difference() {
//   cube([121.5+2*(0.5+t)+2*wt,28.5+2*wt,t],center=true,wt);
//    cube([121.5+2*(0.5+t),28.5,t+1],center=true,wt);
//}
module rect(w,l,x,y,z,wt) {
    translate([x,y,z]) cube([w,l,wt],center=true);
}
module longSide(wt,h) {
    t = wt+2*h;
    translate([0,0,t/2]) {
        rect(121.5+2*(0.5),28.5,0,0,-h,wt);
        difference() {
            union() {
                rect(16,10,5,3,h,wt);
                rect(8,23,15,-1,0,wt);
                rect(17,17,-15,-2,h,wt);
                rect(10,13,-5,6.5,0,wt);
                rect(7,7,3,-3,0,wt);
                rect(10,7,18,-10,h,wt);
                rect(6,6,-5,-9,0,wt);
                rect(4,4,4,-10,h,wt);
                rect(20,11,32,-2,0,wt);
                rect(4,5,25,0,h,wt);
                rect(7,21,35,1.5,h,wt);
                rect(4,4,15.5,11.5,h,wt);
                rect(8,8,50,-5,0,wt);
                rect(9,12,45,8,h,wt);
                rect(7.5,10,48,5.5,0,wt);
                rect(4,8,27,10,h,wt);
                rect(5,7,44,-10,h,wt);
                rect(12,3,31,-12,0,wt);
                rect(6,10,60,2.5,0,wt);
                rect(1.5,18,61,-3,h,wt);
                rect(7,7,56,9,h,wt);
                rect(3,3,60,12,0,wt);
                rect(3,4,-27,-2,h,wt);
                rect(4,17,-32,0,h,wt);
                rect(11,10,-38,-6,0,wt);
                rect(10,4,-41,-1,h,wt);
                rect(4,7,-40,7,h,wt);
                rect(2,6,-30,10,0,wt);      
                rect(5,13,-18,7,0,wt);
                rect(4,4,22,6.5,0,wt);
                rect(10,10,-50,-7.5,0,wt);
                rect(2,2,-53,-11,h,wt);
                rect(13,1.5,-49,3,0,wt);
                rect(7,1.5,-57.5,-5,h,wt);
                rect(4,10,-60,-3,0,wt);
                rect(9,9,-59,5,h,wt);
                rect(18,1.5,-52,12.5,h,wt);
                rect(2,9.5,-49,9.25,0,wt);
                rect(3,6,-20,-11,0,wt);
                rect(12,1.5,-22,-12.5,h,wt);
                rect(2,2,-61,-12,h,wt);
            }
            rect(44,1.5,1,-4,h+.1,wt);
            rect(1.5,40,16,0,h+.1,wt);
            rect(2,2,-17,4,h+.1,wt);
            rect(5,5,37,-2,h+.1,wt);
            rect(4,9,46,-1,h+.1,wt);
            rect(4,2,24,6.5,h+.1,wt);
            rect(2,3,44,-10.5,h+.1,wt);
            rect(10,1.5,57,-6.5,h+.1,wt);
            rect(5,2,51,8.5,h+.1,wt);
            rect(10,4,-32,-4,h+.1,wt);
            rect(1.5,40,-40,0,h+.1,wt);
            rect(1.5,6,-18.5,11,h+.1,wt);
            rect(4,4,-49,-6,h+.1,wt);
            rect(2,5,-58,5,h+.1,wt);
            rect(4.5,1.5,4,2,h+.1,wt);
        }
        rect(35,1.5,25,12,0,wt);
        rect(19,1.5,48,-2.5,h,wt);
        rect(12,12,-25,-1,0,wt);
        rect(22,2,50,-11.5,0,wt);
        rect(5,4,60,-6.5,0,wt);
        rect(12,3,-39,8,0,wt);
        rect(32,2,-14,11,h,wt);
        rect(4,10,-11,-4,0,wt);
        rect(9,3,-43,-8,h,wt);
        rect(3,10,-51,0,h,wt);
        rect(5,5,-55.5,8.5,0,wt);
    }
}
module shortSide(wt,h) {
    t = wt+2*h;
    translate([0,0,t/2]) {
        //rect(68+2*(0.5),28.5,0,0,-h,wt);
        difference() {
            union() {
                rect(9,9,3,-3,h,wt);
                rect(12,8,0,0,0,wt);
                rect(1.5,6,4,6,h,wt);
                rect(12,5,-10,4,h,wt);
                rect(12,4,-7,11,h,wt);
                rect(6,6,-17,8,0,wt);
                rect(10,4,6,10,0,wt);
                rect(12,12,15,5,h,wt);
                rect(4,8,6,-8,0,wt);
                rect(15,2,10,-12,h,wt);
                rect(6,4,-4,-8,0,wt);
                rect(8,5,-9,-10,h,wt);
                rect(5,12,14,-7,0,wt);
                rect(7,7,-15,-5,0,wt);
                rect(8,8,-22,0,h,wt);
                rect(5,12,-25,1,0,wt);
                rect(10,6,-24,9,h,wt);
                rect(9,5,-24,-10,h,wt);
                rect(7,7,-29,-10,0,wt);
                rect(2,2,-31,-12,h,wt);
                rect(3,21,25,1,h,wt);
                rect(15,2,25,3,0,wt);
                rect(6,6,32,0,h,wt);
                rect(9,6,30,-4,0,wt);
                rect(2,7,33,-9,h,wt);
                rect(17,1.5,25,-12,0,wt);
                rect(1.5,13,34,7,0,wt);
                rect(3,3,30,8,h,wt);
                rect(1.5,19,-31,0,h,wt);
                rect(1.5,19,-35,2,h,wt);
                rect(2,4,-35,-8,0,wt);
                rect(6,4,-32,9,0,wt);
                rect(1.5,1.5,20,-7,0,wt);
            }
            rect(4,4,-1,0.5,h+.1,wt);
            rect(1.5,40,-10,0,h+.1,wt);
            rect(5,3,16,8,h+.1,wt);
            rect(3,3,16,-1,h+.1,wt);
            rect(5,2,-19,-6,h+.1,wt);
            rect(2,2,-26,9,h+.1,wt);
            rect(2,2,29,-3,h+.1,wt);
            rect(3,1.5,34,11,h+.1,wt);
        }
        rect(16,1.5,-13,3,0,wt);
        rect(5,5,-9,8,0,wt);
        rect(13,2,-14,-12.5,0,wt);
        rect(8,5,21,11,0,wt);
    }
}


module decoration() {
    translate([0,-34-0.5,0]) rotate([90,0,0]) longSide(1.5,0.5);
    translate([0,34+0.5,0]) rotate([90,0,180]) longSide(1.5,0.5);
    translate([60.75+0.5,0,0]) rotate([90,0,90]) shortSide(1.5,0.5);
    translate([-60.75-0.5,0,0]) rotate([90,0,-90]) shortSide(1.5,0.5);
}
translate([0,-15,0.8]) cube(1.6,center=true);
translate([0,0,0.1]) shortSide(1.5,0.5);
intersection() {
    minkowski() {
        difference(){
            translate([0,0,2.6])cube([69-.01,28.5-.01,2],center=true);
            translate([0,0,0.1]) shortSide(1.5,0.5);
        }
        sphere(r=1.6,center=true);
    }
    translate([0,0,0.8]) cube([69-0.1,28.5-0.1,1.6],center=true);
}
