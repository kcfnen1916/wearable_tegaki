/* autoTweet Ver:0.1 */

// PROFILE_PATH, putDriverはPC依存, size()の中身はディスプレイ依存, port_idはマイコン依存
import org.openqa.selenium.Keys;
import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.chrome.ChromeDriver;
import org.openqa.selenium.chrome.ChromeDriverService;
import org.openqa.selenium.chrome.ChromeOptions;
import processing.serial.*;
import ddf.minim.*;

PImage img;
PImage img2;

Minim minim;
AudioSample roller;
AudioSample foot;
AudioPlayer player; 

WebDriver driver;
Serial myport;
//int x;
int enter=0; //enterの回数（行数）
String [] now = new String[30];
int d=0; //現在のカーソルのx位置
int now_enter=0; //現在の行
int x_space=3;
int y_space=30;
String port_id = "/dev/cu.usbserial-3D524F0BA5";
int text_size=int(height/2.5);

String TwiId = "@wearbo_sxsw";   //TwitterID
String TwiPass = "wataame1105!";  
String x;
String putDriver = "/Users/sanoyuki/Downloads/chromedriver";
String PROFILE_PATH = "/Users/sanoyuki/Library/Application Support/Google/Chrome";
int c;
PFont font;
float ascent;
float descent;
float textHeight;
int textPosY;
boolean tweetbottun = false;

void settings(){
  size(740,900); // これはディスプレイによって数字を変えたほうがいい
}

void setup(){
  print(displayHeight);
  print(displayWidth);
  img = loadImage("gradation_.png");
  img2 = loadImage("gradation_up.png");
  image(img, 0, 0, width, height);
  //driver setup
  System.setProperty("webdriver.chrome.driver", putDriver);
  ChromeOptions options = new ChromeOptions();
  driver = new ChromeDriver();
  options.addArguments("user-data-dir"+PROFILE_PATH);
  c = 0;
  start_twitter();
  //background(color(230, 230, 230, 255));
  fill(255);
  
  myport = new Serial(this, port_id,115200);
  fill(color(255,255,255));
  textAlign(CENTER,TOP);
  font = createFont("Rockwell",text_size);
  //フォントを指定
  textFont(font);
  minim = new Minim(this);
  player = minim.loadFile("a.mp3");
}

void draw(){
  c = 1;
  int haji = 50;
  int uehaji = int(height/2+50);
  int rectsize = int(height/12);
  int kankaku = rectsize/2;
  int diff = rectsize + kankaku;
  int marumi = 25;
  fill(51,204,204);
  strokeJoin(BEVEL);
  noStroke();
  rect(haji+int(rectsize/2), uehaji, rectsize, rectsize*3+kankaku*2, marumi);
  rect(kankaku+haji+diff, uehaji, rectsize, rectsize, marumi);
  
  rect(kankaku+haji+2*diff, uehaji, rectsize, rectsize, marumi);
  rect(kankaku+haji+3*diff, uehaji, rectsize, rectsize, marumi);
  rect(kankaku+haji+4*diff, uehaji , rectsize, rectsize, marumi);
  
  rect(kankaku+haji+diff, uehaji+diff, rectsize, rectsize, marumi);
  rect(kankaku+haji+2*diff, uehaji+diff, rectsize, rectsize, marumi);
  rect(kankaku+haji+3*diff, uehaji+diff, rectsize, rectsize, marumi);
  rect(kankaku+haji+4*diff, uehaji+diff, rectsize, rectsize*2+kankaku, marumi);
  
  rect(kankaku+haji+diff, uehaji+2*diff, rectsize, rectsize, marumi);
  rect(kankaku+haji+2*diff, uehaji+2*diff, rectsize, rectsize, marumi);
  rect(kankaku+haji+3*diff, uehaji+2*diff, rectsize, rectsize, marumi);
  if(myport.available()>0){
    //background(color(230, 230, 230, 255));
    fill(color(230, 230, 230, 255));
    //image(img, 0, 0, width, int(height/2));
    x = myport.readString();  
    fill(173,216,230);
    if (x.length() >= 2 && x.charAt(1) == "1".charAt(0)){
      if (x.charAt(0) == "c".charAt(0)){
          rect(haji+int(rectsize/2), uehaji, rectsize, rectsize*3+kankaku*2, marumi);
      } 
      else if (x.charAt(0) == "t".charAt(0)){
          rect(kankaku+haji+diff, uehaji, rectsize, rectsize, marumi);
      } 
      else if (x.charAt(0) == "y".charAt(0)){
          rect(kankaku+haji+2*diff, uehaji, rectsize, rectsize, marumi);
      } 
      else if (x.charAt(0) == "u".charAt(0)){
          rect(kankaku+haji+3*diff, uehaji, rectsize, rectsize, marumi);
      } 
      else if (x.charAt(0) == "g".charAt(0)){
          rect(kankaku+haji+diff, uehaji+diff, rectsize, rectsize, marumi);
      } 
      else if (x.charAt(0) == "h".charAt(0)){
          rect(kankaku+haji+2*diff, uehaji+diff, rectsize, rectsize, marumi);
      } 
      else if (x.charAt(0) == "j".charAt(0)){
          rect(kankaku+haji+3*diff, uehaji+diff, rectsize, rectsize, marumi);
      } 
      else if (x.charAt(0) == "b".charAt(0)){
          rect(kankaku+haji+diff, uehaji+2*diff, rectsize, rectsize, marumi);
      } 
      else if (x.charAt(0) == "n".charAt(0)){
          rect(kankaku+haji+2*diff, uehaji+2*diff, rectsize, rectsize, marumi);
      } 
      else if (x.charAt(0) == "m".charAt(0)){
          rect(kankaku+haji+3*diff, uehaji+2*diff, rectsize, rectsize, marumi);
      } 
      else if (x.charAt(0) == "d".charAt(0)){
          rect(kankaku+haji+4*diff, uehaji , rectsize, rectsize, marumi);
      } 
      else{
          rect(kankaku+haji+4*diff, uehaji+diff, rectsize, rectsize*2+kankaku, marumi);
      } 
    } else {
      fill(color(0, 30, 30));
      write_tweet(x);
      if (x.length() >= 8){
        textSize(height*0.20);
        ascent = textAscent();
        descent = textDescent();
        textHeight = ascent + descent; 
        textPosY = int(height-textHeight)/2 - int(height/5);
        x = "DELETE";
      }
      else if (x.length() >= 5){
        textSize(height*0.20);
        ascent = textAscent();
        descent = textDescent();
        textHeight = ascent + descent; 
        textPosY = int(height-textHeight)/2 - int(height/5);
      }
      else {
        textSize(height*0.4);
        ascent = textAscent();
        descent = textDescent();
        textHeight = ascent + descent; 
        textPosY = int(height-textHeight)/2 - 10 - int(height/5);
        //roller = minim.loadSample(x.substring(0,1)+".wav", 2048);
        //roller.trigger();
        player.play();
        minim = new Minim(this);
        player = minim.loadFile("a.mp3");
      }
      image(img2, 0, 0, width, int(height/2));
      text(x, int(width/2), textPosY);
    }
  }
  
  if (tweetbottun){
    fill(color(255,255,255));
    image(img, 0, 0, width, height);
    textSize(height*0.19);
    ascent = textAscent();
    descent = textDescent();
    textHeight = ascent + descent; 
    textPosY = int(height-textHeight)/2 - int(height/5);
    text("Tweet!!!", int(width/2), textPosY);
    tweetbottun = false;
  }
}

void keyPressed() {
  if (key == ENTER) {
      tweetbottun = true;
      send_tweet();
      start_twitter();
    }
}
