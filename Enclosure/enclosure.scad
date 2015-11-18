eps = 0.01;

enclosure(
    innerWidth = 44,
    innerHeight = 11,
    innerDepth = 49,
    wallThickness = 1.5,
    separatorWidth = 1,
    separatorDepth = 32,
    pcbWidth = 30.2,
    pcbHeight = 48,
    pcbRail = 1,
    pcbThickness = 1.6,
    pcbFromBottom = 2,
    backRailWidth = 10,
    connectorPosition = 10
);

module pcb (width, height, thickness, extWidth = 4.5, extHeight = 1) {
    translate([0, extHeight, 0])
        linear_extrude(thickness)
            square([width, height-extHeight]);
    linear_extrude(thickness)
            square([extWidth, extHeight]);
}

module mainShape(width, height, depth) {
    radius = height / 2;
    iWidth = width - height;
    linear_extrude(depth)
        square([iWidth, height], true);
    translate([-iWidth/2, 0, 0])
        cylinder(r = radius, h = depth);
    translate([+iWidth/2, 0, 0])
        cylinder(r = radius, h = depth);
}

module outerWall(width, height, depth, wallThickness) {
    w2 = wallThickness * 2;
    difference() {
        mainShape(width, height, depth);
        translate([0, 0, wallThickness])
            mainShape(width-w2, height-w2, depth-w2);
        translate([0,0,-1])
            linear_extrude(wallThickness+1+eps)
                square([width+10, height+10], true);
    }
}

module separator(width, height, depth, pcbThickness, pcbFromBottom, pcbRail) {
    r = height/2;
    w = width+r+pcbRail;
    translate([w/2, 0, 0])
        difference() {
            linear_extrude(depth)
                square([w, height], true);
            translate([-w/2, 0, -eps])
                cylinder(r = r, h = depth+2*eps);
            translate([w/2-pcbRail/2, height/2-pcbThickness/2-pcbFromBottom, -eps])
                linear_extrude(depth+eps*2)
                    square([pcbRail+eps, pcbThickness], true);
        }
}

module pcbHolderRight(width, height, depth) {
    r = height/2.0;
    w = r*2.0-width+1;
    difference() {
        cylinder(r = r, h = depth);
        translate([-w/2.0+r/2.0, 0, -eps])
            linear_extrude(depth+eps*2)
                square([w, height], true);
        translate([0, -(height+2)/2, -eps])
            linear_extrude(depth+eps*2)
                square([height+2, height+2], true);        
    }
}

module pcbHolderBack(width, height, depth) {
    linear_extrude(depth)
        square([width, height], true);
}

module hdmiHole() {
    w = 11.5;
    h = 4;
    translate([0, -h/2, 0])
        linear_extrude(100)
            square([w, h], true);
}

module enclosure (
    innerWidth,
    innerHeight,
    innerDepth,
    wallThickness,
    separatorWidth,
    separatorDepth,
    pcbRail,
    pcbWidth,
    pcbHeight,
    pcbThickness,
    pcbFromBottom,
    backRailWidth,
    connectorPosition
)
{
    outerWidth = innerWidth + wallThickness * 2;
    outerHeight = innerHeight + wallThickness * 2;
    outerDepth = innerDepth + wallThickness * 2;
   
    pcbX = - innerWidth/2 + innerHeight + separatorWidth;
    
    color("lightgrey")
        difference() {
            outerWall(outerWidth, outerHeight, outerDepth, wallThickness);
            translate([pcbX + connectorPosition, pcbFromBottom, 0])
            hdmiHole();
        }
    
    
    difference() {
        union () {
            translate([-innerWidth/2+innerHeight/2, 0, wallThickness*3])
                separator(
                    separatorWidth,
                    innerHeight,
                    separatorDepth,
                    pcbThickness,
                    pcbFromBottom,
                    pcbRail);
            
            translate([+innerWidth/2-innerHeight/2, 0, wallThickness*3])
                pcbHolderRight(
                    innerWidth - innerHeight - separatorWidth - pcbWidth + pcbRail,
                    innerHeight,
                    innerDepth - wallThickness*3
                );
            
            backRailHeight = pcbFromBottom + pcbThickness + wallThickness;
            translate([
                -backRailWidth/2 + innerWidth/2 - innerHeight/2,
                -backRailHeight / 2 + innerHeight/2,
                -pcbRail/2 + innerDepth]
            )
                pcbHolderBack(backRailWidth, backRailHeight, pcbRail);
        }
        translate([
            pcbX + pcbWidth,
            -pcbThickness + innerHeight/2 - pcbFromBottom,
            innerDepth - pcbHeight + wallThickness]
        )
            rotate([90, 0, 180])
                pcb(pcbWidth, pcbHeight, pcbThickness);
    }
}





    