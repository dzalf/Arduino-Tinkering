class conditionsBox {
  int[] txtColor;
  int posTxtX;
  int posTxtY;
  int txtSize;
  //String txtString;

  conditionsBox(int tempTxtSize, int tempX, int tempY, int[] tempCol) {
    
    txtColor = new int[3];
    txtSize = tempTxtSize;
    //txtString = tempTxt;
    posTxtX = tempX;
    posTxtY = tempY;
    txtColor = tempCol;
  }

  void display(String tempTxt) {
    textSize(txtSize);
    fill(txtColor[0],txtColor[1],txtColor[2]);
    text(tempTxt, posTxtX, posTxtY);
  }
}