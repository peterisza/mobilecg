width = 86;
height = 54;
thickness = 1;
electronicsWidth = 37;
electronicsHeight = 24;
electronicsOffset = 2.5;
connectorWidth = 13;
screenWidth = 28;
screenHeight = 20;
screenOffset = 4;
batteryDiameter = 20;
batteryOffsetX = 14.5;
batteryOffsetY = 13;
batteryHolderWidth = 25.5;
batteryHolderHeight = 18;
padWidth = 18;
padHeight = 22;
padOffsetY = 15.5;
padOffsetX = 4;

difference() {
    linear_extrude(thickness)
        square([width, height], true);
    translate([0, height/2-electronicsHeight/2-electronicsOffset])
        linear_extrude(thickness)
            square([electronicsWidth, electronicsHeight], true);   
    linear_extrude(thickness)
        square([connectorWidth, 30], true);      
    translate([0, -height/2+screenHeight/2+screenOffset])
        linear_extrude(thickness)
            square([screenWidth, screenHeight], true); 
    translate([-width/2+batteryOffsetX, -height/2+batteryOffsetY])  
        cylinder(r=batteryDiameter/2, h=thickness);
    translate([-width/2+batteryOffsetX, -height/2+batteryHolderHeight/2])  
        linear_extrude(thickness)
            square([batteryHolderWidth, batteryHolderHeight], true); 
    translate([-width/2+padWidth/2+padOffsetX, height/2-padOffsetY])  
        linear_extrude(thickness)
            square([padWidth, padHeight], true); 
    translate([+width/2-padWidth/2-padOffsetX, height/2-padOffsetY])  
        linear_extrude(thickness)
            square([padWidth, padHeight], true);     
}