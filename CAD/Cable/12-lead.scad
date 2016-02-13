outerHeight = 8;
outerWidth = 25;
outerLength = 15;
wall = 1.5;
hdmiWidth = 12;
hdmiHeight = 5;

innerHeight = outerHeight - wall*2;
innerWidth = outerWidth - wall*2;
innerLength = outerLength - wall;

module mainShape(w, h, l) {
    translate([-w/2+h/2, 0, 0])
        cylinder(h=l, r=h/2);
    translate([w/2-h/2, 0, 0])
        cylinder(h=l, r=h/2);
    linear_extrude(l)
        square([w-h, h], true);
}

difference() {
    mainShape(outerWidth, outerHeight, outerLength);
    mainShape(innerWidth, innerHeight, innerLength);
    linear_extrude(50)
        square([hdmiWidth, hdmiHeight], true);
}