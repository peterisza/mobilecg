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
pcbThickness = 1.82;
pcbFromBottom = 2;
backRailWidth = 10;
connectorPosition = 10;
logoHeight = 0.5;
hookThickness = 1.5;
lidHoleWidth = 8;
lidHolePosition = 8;
thinRailWidth = 1;
thinRailDepth = 0.5;


cylinderResolution = 200;



pcbX = -innerWidth/2 + innerHeight + separatorWidth;
pcbTop = wallThickness + pcbFromBottom + pcbThickness;
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
        cylinder(r = radius, h = depth, $fn = cylinderResolution);
    translate([+iWidth/2, 0, 0])
        cylinder(r = radius, h = depth, $fn = cylinderResolution);
}

module outerWall() {
    w2 = wallThickness * 2;
    difference() {
        mainShape(outerWidth, outerHeight, outerDepth);
        translate([0, 0, -eps])
            mainShape(outerWidth-w2, outerHeight-w2, outerDepth-wallThickness);
        /*translate([0,0,-1])
            linear_extrude(wallThickness+1+eps)
                square([outerWidth+10, outerHeight+10], true);*/
        translate([0,-50,-eps])
            linear_extrude(wallThickness+hookThickness*2+eps)
                square([100,100], true);
    }
}

module separator(width, height, depth, skip) {
    r = height/2;
    w = width+r+pcbRail;
    translate([w/2, 0, 0])
        difference() {
            linear_extrude(depth)
                square([w, height], true);
            translate([-w/2, 0, -eps])
                cylinder(r = r, h = depth+2*eps, $fn = cylinderResolution);
            translate([w/2-pcbRail/2, height/2-pcbThickness/2-pcbFromBottom, -eps])
                linear_extrude(depth+eps*2)
                    square([pcbRail+eps, pcbThickness], true);
            translate([-w+r, -r, -eps])
                linear_extrude(skip)
                    square([r, r], true);             
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
        cylinder(r = r, h = hookThickness+eps, $fn = cylinderResolution);
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

module pcbHolderRight(width, height, depth) {
    r = height/2.0;
    w = r*2.0-width+1;
    difference() {
        cylinder(r = r, h = depth, $fn = cylinderResolution);
        translate([-w/2.0+r/2.0, 0, -eps])
            linear_extrude(depth+eps*2)
                square([w, height], true);
        translate([0, -(height+2)/2, -eps])
            linear_extrude(depth+eps*2)
                square([height+2, height+2], true);        
    }
}

module pcbHolders() {
    translate([-innerWidth/2+innerHeight/2, 0, wallThickness])
        separator(
            separatorWidth,
            innerHeight,
            separatorDepth,
            wallThickness+hookThickness
        );
    
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
            innerDepth - wallThickness*2
        );        
  
   translate([
        -backRailWidth/2 + innerWidth/2 - innerHeight/2,
        -backRailHeight / 2 + innerHeight/2,
        innerDepth + wallThickness - pcbRail]
    )
        linear_extrude(pcbRail)
            square([backRailWidth, backRailHeight], true);
  
}

module logo() {
    translate([0,+outerHeight/2+0.01, 31])
        rotate([90,0,0]) scale([1.6, 1.6, 1])
            scale([1, -1, 1]) translate([-17.6/2, -15.06/2, 0])
                linear_extrude(logoHeight+0.02)
                    import (file = "logo2.dxf");
}

module prototype() {
    translate([10,-outerHeight/2+logoHeight,48])
        scale([0.5,1,0.5])
            rotate([90, -55+180, 0])
                linear_extrude(10)
                    text("PROTOTYPE", font="Liberation Sans:style=Bold");

    translate([-14.6,+outerHeight/2,48.5])
        scale([-0.35,1,0.35])
            rotate([90, 180, 0])
                linear_extrude(logoHeight)
                    text("PROTOTYPE", font="Liberation Sans:style=Bold");    
}

module lidBase() {
    difference() {
        mainShape(outerWidth, outerHeight, wallThickness + hookThickness*2);
        translate([0, 0, wallThickness])
            mainShape(innerWidth, innerHeight, wallThickness + hookThickness*2);  
    }

    translate([-lidHoleWidth/2 + innerWidth/2 - lidHolePosition, -hookThickness/2 + innerHeight/2, wallThickness])
        linear_extrude(hookThickness)
            square([lidHoleWidth + hookThickness * 4, hookThickness], true);  

    w = hookThickness * 2;
    translate([pcbX + pcbRail + w/2, leftHookHeight/2 - innerHeight/2, wallThickness])
        linear_extrude(hookThickness*2)
            square([w, leftHookHeight], true); 

    intersection() {
        translate([innerWidth/2 - w/2, 0, wallThickness])
            linear_extrude(hookThickness)
                square([w, innerHeight], true);
        translate([0, 0, wallThickness])
            mainShape(innerWidth, innerHeight, wallThickness + hookThickness*2); 
    }
    
    /*x = pcbX + separatorWidth + hookThickness;
    w = innerWidth/2-innerHeight/2 - x;

    translate([+w/2+x, 0, wallThickness])
        linear_extrude(hookThickness)
            square([w, innerHeight], true);*/
}

module lid() {
    difference() {
        lidBase();
        enclosure();
    }
}

module enclosure ()
{
    color("lightgrey")
        difference() {
            outerWall();
            hdmiHole();   
            logo();
            prototype();
            lidHole();
        }
   
    
    color("lightgrey")
    difference() {
        union () {
            pcbHolders();
            hooks();
        }
        pcb();
    }

    //color("green")
     //   pcb();
}


/*color("red")
    translate([0, outerHeight/2, -10])
    rotate([90, 0, 0])
        lid();*/


scale([1.015,1.015,-1.015]) {
    difference() {
        enclosure();
        /*translate([0,-25,0])
            linear_extrude(60)
                square([60, 60], true);*/
    }    
    /*rotate([180,0,0])
        translate([0, -6, 0])
            lid();*/
}








    