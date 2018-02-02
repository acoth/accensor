include <tile.scad>

minkowski() {
    tiling(0.1,28,68,0.8);
    sphere(r=0.8,$fn=9);
}