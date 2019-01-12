class percentBox {
  int txtCol;
  int txtSize; 
  float txtPosX;
  float txtPosY; 
  
  int rectCol;
  int rectSizeX; 
  int rectSizeY; 
  int rectPosX;
  float rectPosY;
  
  //constructor
  percentBox() { 
    txtCol = 250;
    rectCol = 250; //250
    txtSize = 15; //15
    txtPosX = 15;
    //tPosY = 
    rectSizeX = 60; //60
    rectSizeY = 30; //30
    rectPosX = 0;
    rectPosY = h-tall;
  }

  void display() {
    //fill(rectCol);
    fill(255*(1-percent/100), 255*percent/100, 0);
    rect(rectPosX, rectPosY, rectSizeX, rectSizeY);
    textSize(txtSize);
    fill(txtCol);
    text(str(percent)+" %", txtPosX, txtPosY);
  }
}