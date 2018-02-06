module rect(w,l,x,y,z,wt) {
    translate([x,y,z]) cube([w,l,wt],center=true);
}
module longSide(wt,h,o) {
    t = wt+2*h;
    translate([0,0,t/2]) {
        rect(121.5+2*(0.5)+2*wt,29,0,0,-h,wt);
        difference() {
            union() {
                rect(16+o,10+o,5,3,h,wt);
                rect(8+o,23+o,15,-1,0,wt);
                rect(17+o,17+o,-15,-2,h,wt);
                rect(10+o,13+o,-5,6.5,0,wt);
                rect(7+o,7+o,3,-3,0,wt);
                rect(10+o,7+o,18,-10,h,wt);
                rect(6+o,6+o,-5,-9,0,wt);
                rect(4+o,4+o,4,-10,h,wt);
                rect(20+o,11+o,32,-2,0,wt);
                rect(4+o,5+o,25,0,h,wt);
                rect(7+o,21+o,35,1.5,h,wt);
                rect(5+o,4+o,16,11.5,h,wt);
                rect(8+o,8+o,50,-5,0,wt);
                rect(9+o,12+o,45,8,h,wt);
                rect(7.5+o,10+o,48,5.5,0,wt);
                rect(4+o,8+o,27,10,h,wt);
                rect(5+o,7+o,44,-10,h,wt);
                rect(12+o,3+o,31,-12,0,wt);
                rect(6+o,10+o,60,2.5,0,wt);
                rect(1.5+o,18+o,61,-3,h,wt);
                rect(7+o,7+o,56,9,h,wt);
                rect(3+o,3+o,60,12,0,wt);
                rect(3+o,4+o,-27,-2,h,wt);
                rect(4+o,17+o,-32,0,h,wt);
                rect(11+o,10+o,-38,-6,0,wt);
                rect(10+o,4+o,-41,-1,h,wt);
                rect(4+o,7+o,-40,7,h,wt);
                rect(2+o,6+o,-30,10,0,wt);      
                rect(5+o,13+o,-18,7,0,wt);
                rect(4+o,4+o,22,6.5,0,wt);
                rect(10+o,10+o,-50,-7.5,0,wt);
                rect(2+o,2+o,-53,-11,h,wt);
                rect(13+o,1.5+o,-49,3,0,wt);
                rect(7+o,1.5+o,-57.5,-5,h,wt);
                rect(4+o,10+o,-60,-3,0,wt);
                rect(9+o,9+o,-59,5,h,wt);
                rect(18+o,1.5+o,-52,12.5,h,wt);
                rect(2+o,9.5+o,-49,9.25,0,wt);
                rect(3+o,6+o,-20,-11,0,wt);
                rect(12+o,1.5+o,-22,-12.5,h,wt);
                rect(2+o,2+o,-61,-12,h,wt);
            }
            rect(44-o,1.5-o,1,-4,h+.1,wt);
            rect(1.5-o,40-o,16,0,h+.1,wt);
            rect(2-o,2-o,-17,4,h+.1,wt);
            rect(5-o,5-o,37,-2,h+.1,wt);
            rect(4-o,9-o,46,-1,h+.1,wt);
            rect(4-o,2-o,24,6.5,h+.1,wt);
            rect(2-o,3-o,44,-10.5,h+.1,wt);
            rect(10-o,1.5-o,57,-6.5,h+.1,wt);
            rect(5-o,2-o,51,8.5,h+.1,wt);
            rect(10-o,4-o,-32,-4,h+.1,wt);
            rect(1.5-o,40-o,-40,0,h+.1,wt);
            rect(1.5-o,6-o,-18.5,11,h+.1,wt);
            rect(4-o,4-o,-49,-6,h+.1,wt);
            rect(2-o,5-o,-58,5,h+.1,wt);
            rect(4.5-o,1.5-o,4,2,h+.1,wt);
        }
        rect(35+o,1.5+o,25,12,0,wt);
        rect(19+o,1.5+o,48,-2.5,h,wt);
        rect(12+o,12+o,-25,-1,0,wt);
        rect(22+o,2+o,50,-11.5,0,wt);
        rect(5+o,4+o,60,-6.5,0,wt);
        rect(12+o,3+o,-39,8,0,wt);
        rect(32+o,2+o,-14,11,h,wt);
        rect(4+o,10+o,-11,-4,0,wt);
        rect(9+o,3+o,-43,-8,h,wt);
        rect(3+o,10+o,-51,0,h,wt);
        rect(5+o,5+o,-55.5,8.5,0,wt);
    }
}
module shortSide(wt,h,o) {
    t = wt+2*h;
    translate([0,0,t/2]) {
        rect(68+2*(0.5)+2*wt,29,0,0,-h,wt);
        difference() {
            union() {
                rect(9+o,9+o,3,-3,h,wt);
                rect(12+o,8+o,0,0,0,wt);
                rect(1.5+o,6+o,4,6,h,wt);
                rect(12+o,5+o,-10,4,h,wt);
                rect(12+o,4+o,-7,11,h,wt);
                rect(6+o,6+o,-17,8,0,wt);
                rect(10+o,4+o,6,10,0,wt);
                rect(12+o,12+o,15,5,h,wt);
                rect(4+o,8+o,6,-8,0,wt);
                rect(15+o,2+o,10,-12,h,wt);
                rect(6+o,4+o,-4,-8,0,wt);
                rect(8+o,5+o,-9,-10,h,wt);
                rect(5+o,12+o,14,-7,0,wt);
                rect(7+o,7+o,-15,-5,0,wt);
                rect(8+o,8+o,-22,0,h,wt);
                rect(5+o,12+o,-25,1,0,wt);
                rect(10+o,6+o,-24,9,h,wt);
                rect(9+o,5+o,-24,-10,h,wt);
                rect(7+o,7+o,-29,-10,0,wt);
                rect(2+o,2+o,-31,-12,h,wt);
                rect(3+o,21+o,25,1,h,wt);
                rect(15+o,2+o,25,3,0,wt);
                rect(6+o,6+o,32,0,h,wt);
                rect(9+o,6+o,30,-4,0,wt);
                rect(2+o,7+o,33,-9,h,wt);
                rect(17+o,1.5+o,25,-12,0,wt);
                rect(1.5+o,13+o,34,7,0,wt);
                rect(3+o,3+o,30,8,h,wt);
                rect(1.5+o,19+o,-31,0,h,wt);
                rect(1.5+o,19+o,-35,2,h,wt);
                rect(2+o,4+o,-35,-8,0,wt);
                rect(6+o,4+o,-32,9,0,wt);
                rect(1.5+o,1.5+o,20,-7,0,wt);
            }
            rect(4-o,4-o,-1,0.5,h+.1,wt);
            rect(1.5-o,40-o,-10,0,h+.1,wt);
            rect(5-o,3-o,16,8,h+.1,wt);
            rect(3-o,3-o,16,-1,h+.1,wt);
            rect(5-o,2-o,-19,-6,h+.1,wt);
            rect(2-o,2-o,-26,9,h+.1,wt);
            rect(2-o,2-o,29,-3,h+.1,wt);
            rect(3-o,1.5-o,34,11,h+.1,wt);
        }
        rect(16+o,1.5+o,-13,3,0,wt);
        rect(5+o,5+o,-9,8,0,wt);
        rect(13+o,2+o,-14,-12.5,0,wt);
        rect(8+o,5+o,21,11,0,wt);
    }
}
module sss() {
    difference() {
        shortSide(1.5,0.5,0);
        translate([0,0,-1.51]) shortSide(1.5,0.5,-3.01);
    }
}

module lss() {
    difference() {
        longSide(1.5,0.5,0);
        translate([0,0,-1.51]) longSide(1.5,0.5,-3.01);
    }
}



module decoration() {
    translate([0,-34-0.5,0]) rotate([90,0,0]) lss();
    translate([0,34+0.5,0]) rotate([90,0,180]) lss();
    translate([60.75+0.5,0,0]) rotate([90,0,90]) sss();
    translate([-60.75-0.5,0,0]) rotate([90,0,-90]) sss();
}

    




