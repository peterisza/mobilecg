eps = 0.01;


innerWidth = 44;
innerHeight = 11;
innerDepth = 49;
wallThickness = 1.5;
separatorWidth = 1;
separatorDepth = 32;
pcbWidth = 30.2;
pcbHeight = 48;
pcbExtWidth = 4.5;
pcbExtHeight = 1;
pcbRail = 1;
pcbThickness = 1.6;
pcbFromBottom = 2;
backRailWidth = 10;
connectorPosition = 10;
logoHeight = 0.4;
hookThickness = 1.5;
lidHoleWidth = 8;
lidHolePosition = 8;
thinRailWidth = 1;
thinRailDepth = 0.5;


enclosure();


pcbX = -innerWidth/2 + innerHeight + separatorWidth;
outerWidth = innerWidth + wallThickness * 2;
outerHeight = innerHeight + wallThickness * 2;
outerDepth = innerDepth + wallThickness * 2;
leftHookHeight = innerHeight - pcbFromBottom - pcbThickness - 1;    
backRailHeight = pcbFromBottom + pcbThickness + wallThickness;
    
module pcb () {
    translate([
        pcbX + pcbWidth,
        -pcbThickness + innerHeight/2 - pcbFromBottom,
        innerDepth - pcbHeight + wallThickness]
    )
        rotate([90, 0, 180])    
        {    
            translate([0, pcbExtHeight, 0])
                linear_extrude(pcbThickness)
                    square([pcbWidth, pcbHeight-pcbExtHeight]);
            linear_extrude(pcbThickness)
                    square([pcbExtWidth, pcbExtHeight]);
        }
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

module outerWall(width, height, depth) {
    w2 = wallThickness * 2;
    difference() {
        mainShape(width, height, depth);
        translate([0, 0, -eps])
            mainShape(width-w2, height-w2, depth-w2);
        /*translate([0,0,-1])
            linear_extrude(wallThickness+1+eps)
                square([width+10, height+10], true);*/
        translate([0,-50,-eps])
            linear_extrude(wallThickness+hookThickness*2+eps)
                square([100,100], true);

    }
}

module separator(width, height, depth) {
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

module hdmiHole() {
    w = 11.5;
    h = 4;
    translate([pcbX + connectorPosition, pcbFromBottom, 0])    
        translate([0, -h/2, 0])
            linear_extrude(95)
                square([w, h], true);
}

module leftHook(height) {
    linear_extrude(hookThickness)
        square([hookThickness, height]);
}

module lidHole() {
    translate([-lidHoleWidth/2 + innerWidth/2 - lidHolePosition, 0, wallThickness])
        linear_extrude(hookThickness)
            square([lidHoleWidth, 20], true);  
}

module sideHook(innerWidth, innerHeight, hookWidth) {
    r = innerHeight/2;
    intersection() {
        cylinder(r = r, h = hookThickness+eps);
        w = hookWidth;
        translate([innerHeight/2 - w/2, innerHeight/2 - hookThickness, 0])
            linear_extrude(hookThickness)
                square([w, innerHeight], true);
    }    
}

module hooks() {
    translate([innerWidth/2 - innerHeight/2, 0, 0])
        sideHook(innerWidth, outerHeight, wallThickness);

    translate([innerWidth/2 - innerHeight/2, 0, wallThickness])
        sideHook(innerWidth, outerHeight, wallThickness + hookThickness);

    scale([-1,1,1]) {
        translate([innerWidth/2 - innerHeight/2, 0, 0])
            sideHook(innerWidth, outerHeight, wallThickness);
        translate([innerWidth/2 - innerHeight/2, 0, wallThickness])
            sideHook(innerWidth, outerHeight, wallThickness);
    }    
}

module pcbHolders() {
    translate([-innerWidth/2+innerHeight/2, 0, wallThickness])
        separator(
            separatorWidth,
            innerHeight,
            separatorDepth,
            pcbThickness,
            pcbFromBottom,
            pcbRail);
    
    translate([
        -innerWidth/2 + innerHeight + separatorWidth + hookThickness/2,
        -innerHeight/2,
        wallThickness
    ])
        leftHook(leftHookHeight);
    
    translate([+innerWidth/2-innerHeight/2, 0, wallThickness*3])
        pcbHolderRight(
            innerWidth - innerHeight - separatorWidth - pcbWidth + pcbRail,
            innerHeight,
            innerDepth - wallThickness*3
        );        
  
   translate([
        -backRailWidth/2 + innerWidth/2 - innerHeight/2,
        -backRailHeight / 2 + innerHeight/2,
        -pcbRail/2 + innerDepth]
    )
        linear_extrude(pcbRail)
            square([backRailWidth, backRailHeight], true);
  
}

module logo() {
    translate([0,-outerHeight/2+logoHeight-0.01, 32])
        rotate([90,0,0]) scale([1.5, 1.5, 1])
            scale([-1, -1, 1]) translate([-17.6/2, -15.06/2, 0])
                linear_extrude(logoHeight+0.02)
                    import (file = "logo2.dxf");    
}

module enclosure (
)
{
    
    color("lightgrey")
        difference() {
            outerWall(outerWidth, outerHeight, outerDepth);
            hdmiHole();   
            logo();
            lidHole();
        }
   
    
    color("lightgrey")
    difference() {
        union () {
            pcbHolders();
            hooks();
        }
        
        translate([
            pcbX + pcbWidth,
            -pcbThickness + innerHeight/2 - pcbFromBottom,
            innerDepth - pcbHeight + wallThickness]
        )
            rotate([90, 0, 180])
                pcb();
    }

    color("green")


            pcb();
}








    