import drop.*;
import test.*;

PImage uView;
PImage sprite;
SDrop drop;

PrintWriter output;

color darkScreen = color(23, 20, 29);

int offset = 7;

void setup() {
  //size(96,97);
  size(110, 110);
  uView = loadImage("uview_t.png");
  drop = new SDrop(this);
}

//Displays the image
void draw() {
  clear();
  background(100, 100, 120);
  image(uView, 0 + offset, 0 + offset);
  fill(darkScreen);
  noStroke();
  rect(16 + offset, 17 + offset, 64, 48);
  if(sprite != null)
  {
    //center the image
    int xPos = 48 - (sprite.width/2) + offset;
    int yPos = 41 - (sprite.height/2) + offset;
    image(sprite, xPos, yPos);
  }
}

//Occurs when a file is dropped into the window
void dropEvent(DropEvent de)
{
  //Load the sprite
  if(de.isImage()) {
    //Can't use de.loadImage() for this part
    //The drag and drop library has a strange bug where
    //the width and height are always 4
    String filePath = de.filePath();
    sprite = loadImage(filePath);
    
    if(sprite.width > 64 || sprite.height > 48) //The sprite is too big
    {
      println("Sprite will not fit on microview screen! Cannot load sprite.");
      sprite = null;
    }
    else
    {
      //Get the filename
      int index = 0;
      for(int j = 0; j < filePath.length(); j++)
      {
        if(filePath.charAt(j) == '\\') //The backslash character in filepaths
          index = j; //We will find the last backslash
      }
      
      //This should give the filename without the file extension...
      //It might not work with weird file paths that have periods in them
      String fileName = filePath.substring(index+1, filePath.indexOf('.'));
      
      //Now it's time to format the image and make sure it displays properly
      sprite.loadPixels();
      
      //Create an empty image buffer
      int arrayHeight = sprite.height/8;
      if(sprite.height % 8 > 0) //If the height is not evenly divisible by 8, then add 1 more row
        arrayHeight++;
      byte[][] buffer = new byte[sprite.width][arrayHeight];
      
      //println(sprite.width);
      //println(arrayHeight);
      
      //In this loop we format the image to look like a microview sprite
      //We also take care of formatting the hex code for the image
      int dimensions = sprite.width*sprite.height;
      for(int i = 0; i < dimensions; i++)
      {
        if(sprite.pixels[i] == color(0, 0, 0)) //If the pixel is black
        {
          sprite.pixels[i] = color(22,208,255); //Make it monochrome blue
          //And mark it as a 1 in our array
          //See http://microview.io/Font/creating-fonts-for-microview.html
          //This will show you how the microview display buffer is arranged
           int y = i / sprite.width;
           int x = i - (y*sprite.width);
           
           buffer[x][y/8] |= (0x01 << y%8);
        }
        else //if the pixel is not black, make it black
        {
          sprite.pixels[i] = darkScreen;
        }
      }
      
      //Now we finish by writing the hex to a file for use with the microView
      for(int k = 0; k < arrayHeight; k++)
      {
        println("//Row " + k);
        for(int l = 0; l < sprite.width; l++)
        {
          print("0x" + hex(buffer[l][k]) + ",");
        }
        println("");
        println("//----------");
      }
      
      sprite.updatePixels();
    }
  }
}