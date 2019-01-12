class buttonBox{
int PosX;
int PosY;
int[] rectColor;
String txt;
int shift;

buttonBox(int tempPosX, int tempPosY, int tempShift){
  rectColor = new int[3];
  PosX = tempPosX;
  PosY = tempPosY;
  shift = tempShift;
}

void display(String tempTXT, int[] tempCol){
  txt = tempTXT;
  
  rectColor = tempCol;
  
  fill(rectColor[0], rectColor[1], rectColor[2]);
  noStroke();
  rect(PosX+shift, PosY, 90,50, 10);
  fill(220);
  textSize(30);
  text(txt, 60+shift,180);
}

}

 //fill(#6A92B2);
  //noStroke();
  //rect(40, 145, 90,50, 10);
  //fill(220);
  //textSize(30);
  //text("ON", 63,180);
 
  
  //fill(#6A92B2);
  //noStroke();
  //rect(40+110, 145, 90,50, 10);
  //fill(220);
  //textSize(30);
  //text("OFF", 63+100,180);