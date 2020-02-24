/* autoTweet Ver:0.1 */
import org.openqa.selenium.Keys;
import org.openqa.selenium.By;
import org.openqa.selenium.WebDriver;
import org.openqa.selenium.WebElement;
import org.openqa.selenium.chrome.ChromeDriver;
import org.openqa.selenium.chrome.ChromeDriverService;
import org.openqa.selenium.chrome.ChromeOptions;

WebDriver driver;

String TwiId = "@wearbo_sxsw";   //TwitterID
String TwiPass = "wataame1105!";  

String tweet = "test";  
String putDriver = "/Users/sanoyuki/Downloads/chromedriver";
String PROFILE_PATH = "/Users/sanoyuki/Library/Application Support/Google/Chrome";

void setup(){
  size(500,500);
  //driver setup
  System.setProperty("webdriver.chrome.driver", putDriver);
  ChromeOptions options = new ChromeOptions();
  driver = new ChromeDriver();
  options.addArguments("user-data-dir=/Users/sanoyuki/Library/Application Support/Google/Chrome");
}

void draw(){
  background(0);  
  if(frameCount % frameRate == 1){
    thread("tweetThread");
  }
}
