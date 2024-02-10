// Include Libraries
import oscP5.*;
import netP5.*;

// Variables
OscP5 oscP5;
float x = 0;
float y = 0;
float touchx = 0;
float touchy = 0;

int drawx, drawy, touch;

// Setup function
void setup() {
  // Screen size
  size(600, 400);

  // Random starting location
  x = random(drawx, 600);
  y = random(drawy, 400);

  // Screen background color
  background(41, 41, 46);
  frameRate(10);

  // OSC server port
  oscP5 = new OscP5(this, 7777);
}

// Receiving OSC messages
void oscEvent(OscMessage theOscMessage) {
  // X-axis message
  if (theOscMessage.addrPattern().equals("/gyx")) {
    drawx = theOscMessage.get(0).intValue();
  }

  // Y-axis message
  if (theOscMessage.addrPattern().equals("/gyy")) {
    drawy = theOscMessage.get(0).intValue();
  }

  // Touch sensor messages
  if (theOscMessage.addrPattern().equals("/value")) {
    touch = theOscMessage.get(0).intValue();
  }
}

// Draw function
void draw() {
  // random movement effect
  x = random(drawx - 360, drawy + 360);
  y = random(drawx - 360, drawy + 360);

  // Draw fill
  fill(49, 36, 102, 10);

  // Stroke color
  stroke(0, 206, 209, 60);

  // Stroke Weight
  strokeWeight(1);

  // Ellipse position
  ellipse(x, y, 100, 100);
}

// Touch sensor pressed
void keyPressed() {
  // Random movement effect
  touchx = random(width);
  touchy = random(height);

  stroke(204, 102, 0, 30);
  strokeWeight(2);
  rect(x, y, 100, 50);

  stroke(255, 255, 255, 80);
  rect(x + 10, y + 20, 100, 100);

  stroke(0, 0, 0, 80);
  rect(x + 25, y + 25, 40, 40);
}
