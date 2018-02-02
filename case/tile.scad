delta = 0.01;
prenf = 4;

module tileUnit(s,t,w,nf) {
    for (f=[0:1:nf]) {
        translate([0,0,t/2*(f/nf)]){
            cylinder(r1=s-w/2,r2=s-w/2*(nf-f)/nf,h=t*(nf-f)/nf+delta,$fn=6,center=true);
            for (angle=[0:120:359]) rotate([0,0,angle]) translate([0,s*(1+sqrt(3))/2,0]) {
                    rotate([0,0,45]) cylinder(r1=(s/2-w/2)*sqrt(2),r2=(s/2-w/2*(nf-f)/nf)*sqrt(2),h=t*(nf-f)/nf+delta,$fn=4,center=true);
                    translate([s*(1/2+sqrt(3)/6),0,0]) 
                        cylinder(r1=s*sqrt(3)/3-w/2,r2=s*sqrt(3)/3-w/2*(nf-f)/nf,h=t*(nf-f)/nf+delta,$fn=3,center=true);    
            }
        }
    }
}
module tiling(w,width,length,t) {
    nr = ceil(1.5*length/width);
    s = width/(4+sqrt(3));
    difference(){
        cube([width,length,t],center=true);
         intersection() {
             for (y=[-nr:1:nr-1]){
                translate([-s*(3/2+sqrt(3)/2),s*(1+sqrt(3))*(y+1/2),0]) mirror([1,0,0]) tileUnit(s,t,w,prenf);
                translate([0,s*(1+sqrt(3))*y,0]) tileUnit(s,t,w,prenf);
                translate([s*(3/2+sqrt(3)/2),s*(1+sqrt(3))*(y+1/2),0]) mirror([1,0,0]) tileUnit(s,t,w,prenf);
            }
            cube([width-2*w,length+10,t*2],center=true);
        }
    }
}
//tiling(0.8,28,68,0.4);