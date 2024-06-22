import("stdfaust.lib");

// Define hsliders to control the drive and offset
drive = hslider("Drive[style:knob]", 0.6, 0, 1, 0.01);
offset = hslider("Offset[style:knob]", 0, -1, 1, 0.01);

// Apply cubicnl function independently to each channel with controlled parameters
process = par(i, 2, ef.cubicnl(drive, offset));
