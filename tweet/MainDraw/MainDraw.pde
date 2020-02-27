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
String port_id = "/dev/cu.usbserial-6152C00AB6";
int text_size=200;

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
  //driver setup
  System.setProperty("webdriver.chrome.driver", putDriver);
  ChromeOptions options = new ChromeOptions();
  driver = new ChromeDriver();
  options.addArguments("user-data-dir"+PROFILE_PATH);
  c = 0;
  start_twitter();
  
  //fullScreen();
  background(color(230, 230, 230, 255));
  fill(255);
  
  myport = new Serial(this, port_id,115200);
  //for(int i=0;i<30;i++){
  //  now[i]="";
  //}
  fill(color(0, 30, 30));
  textAlign(CENTER,TOP);
  font = createFont("Arial",text_size);
  //フォントを指定
  textFont(font);
  minim = new Minim(this);
  player = minim.loadFile("a.mp3");
  String[] args = {"SecondApplet"};   
  SecondApplet sa = new SecondApplet();
  PApplet.runSketch(args, sa);
}

void draw(){
  c = 1;
  print(x);
  if(myport.available()>0){
    background(color(230, 230, 230, 255));
    x = myport.readString();
    if (x.charAt(1) == "1".charAt(0)){
      //何もしない(もう一個のウィンドウで処理)
    }
    else{
      write_tweet(x);
      if (x.length() >= 8){
        textSize(height*0.20);
        ascent = textAscent();
        descent = textDescent();
        textHeight = ascent + descent; 
        textPosY = int(height-textHeight)/2;
        x = "DELETE";
      }
      else if (x.length() >= 5){
        textSize(height*0.20);
        ascent = textAscent();
        descent = textDescent();
        textHeight = ascent + descent; 
        textPosY = int(height-textHeight)/2;
      }
      else {
        textSize(height*0.5);
        ascent = textAscent();
        descent = textDescent();
        textHeight = ascent + descent; 
        textPosY = int(height-textHeight)/2 - 10;
        //roller = minim.loadSample(x.substring(0,1)+".wav", 2048);
        //roller.trigger();
        player.play();
        minim = new Minim(this);
        player = minim.loadFile("a.mp3");
      }
      text(x, int(width/2), textPosY);
    }
  }
  if (tweetbottun){
    background(color(230, 230, 230, 255));
    textSize(height*0.23);
    ascent = textAscent();
    descent = textDescent();
    textHeight = ascent + descent; 
    textPosY = int(height-textHeight)/2;
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

//ここに2こめのディスプレイの処理をかく
public class SecondApplet extends PApplet {
  void settings() {
    size(740,450);
  }
  void setup(){
    // 文字指定
    textSize(24);
    textAlign(LEFT,TOP);
  }
  float subTextX = 0;
  void draw() {
    // 適当なものを表示してみる
    background(color(230, 230, 230, 255));
    fill(0);
    //rect(60, 80, int(height/6), int(height/6)*5);
    //rect(90, 80, int(height/6), int(height/6));
    //rect(90, 40, int(height/6), int(height/6));
    //rect(90, 120, int(height/6), int(height/6));
    ////rect(60, 80, int(height/6), int(height/6));
    ////rect(60, 80, int(height/6), int(height/6));
    ////rect(60, 80, int(height/6), int(height/6));
    ////rect(60, 80, int(height/6), int(height/6));
    ////rect(60, 80, int(height/6), int(height/6));
    ////rect(60, 80, int(height/6), int(height/6));
    ////rect(60, 80, int(height/6), int(height/6));
    ////rect(60, 80, int(height/6), int(height/6));
  }
}
