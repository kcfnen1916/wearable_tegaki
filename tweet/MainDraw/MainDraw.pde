/* autoTweet Ver:0.1 */

// PROFILE_PATH, putDriverはPC依存
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
String port_id = "/dev/cu.usbserial-BD561307B6";
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

void setup(){
  size(740,displayHeight);
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
}

void draw(){
  c = 1;
  if(myport.available()>0){
    background(color(230, 230, 230, 255));
    x = myport.readString();
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
    else{
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
    
  //  if(x.length()>=5 && x.substring(0,5).equals("ENTER")){
  //    println("enterin");
  //    enter++;
  //    now_enter++;
  //    for(int i=enter;i>now_enter;i--){
  //      now[i]=now[i-1];
  //    }
  //    println(d);
  //    now[now_enter]=now[now_enter-1].substring(d);
  //    now[now_enter-1]=now[now_enter-1].substring(0,d);
  //    d=0;
  //  }
  //  else if(x.length()>=9 && x.substring(0,9).equals("BACKSPACE")){
  //    println("delete");
  //    if(now[now_enter]=="" && now_enter>0){
  //      println("delete1");
  //      enter--;
  //      now_enter--;
  //      d=now[now_enter].length();
  //      for(int i=enter;i>now_enter;i--){
  //        now[i]=now[i+1];
  //      }
  //      now[enter+1]="";
  //    }
  //    else if(now[now_enter]=="" && now_enter==0){
  //      println("deletein");
  //    }
  //    else{
  //      if(d==0 && now_enter>0){
  //        println("buri");
  //        enter--;
  //        now_enter--;
  //        d=now[now_enter].length();
  //        now[now_enter]+=now[now_enter+1];
  //        for(int i=enter;i>now_enter;i--){
  //          now[i]=now[i+1];
  //        }
  //        now[enter+1]="";
  //      }
  //      else{
  //        if(d!=0){
  //          now[now_enter]=now[now_enter].substring(0,d-1)+now[now_enter].substring(d);
  //          d--;
  //        }
  //      }
  //    }
  //  }
  //  else if(x.length()>4 && x.substring(0,4).equals("LEFT")){
  //    if(d>0) d--;
  //    else if(d==0 && now_enter>0){
  //      now_enter--;
  //      d=now[now_enter].length();
  //    }
  //  }
  //  else if(x.length()>5 && x.substring(0,5).equals("RIGHT")){
  //    if(d<now[now_enter].length()) d++;
  //    else if(d==now[now_enter].length() && now_enter!=enter){
  //      now_enter++;
  //      d=0;
  //    }
  //  }
  //  else if(x.length()==3){
  //    x=x.substring(0,1);
  //    println("hello");
  //    now[now_enter]=insert(now[now_enter],x,d);
  //    //d+=x.length(); 
  //    d++;
  //  }
  //  println("input:"+x);
  //  //background(0);
    
  //  for(int i=0;i<=enter;i++){
  //    if(i==now_enter){
  //       if(d==now[i].length()) text(now[i]+'|',x_space,y_space*(i+1));
  //       else{
  //         //text(now[i].substring(0,d)+'_'+now[i].substring(d),x_space,y_space*(i+1));
  //         text(now[i],x_space,y_space*(i+1));
  //         text('|',textWidth(now[i].substring(0,d)),y_space*(i+1));
  //         println("now:"+now_enter);
  //         println("d:"+d);
  //       }
  //    }
  //    else text(now[i],3,30*(i+1));
  //  }
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
    }
}
