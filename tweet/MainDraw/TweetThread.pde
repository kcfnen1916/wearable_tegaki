void login_twitter(){
  driver.get("https://twitter.com");
  delay(1500); //1秒くらい待機
  driver.findElement(By.linkText("ログイン")).click();
  delay(1000); //1秒くらい待機
  driver.switchTo().activeElement().sendKeys(TwiId); //アクティブな要素に文字列を送る
  delay(1000);
  //print(driver.getCurrentUrl());
  WebElement login = driver.findElement(By.xpath("//*[@id='react-root']/div/div/div[1]/main/div/div/form/div/div[2]/label/div/div[2]/div/input"));
  //delay(1000);
  login.sendKeys(TwiPass);
  //delay(500);
  login.sendKeys(Keys.chord(Keys.ENTER));
}

void start_twitter(){
  if (c == 0){
    login_twitter();
  }
  delay(2000);
  driver.findElement(By.xpath("/html/body/div/div/div/div/header/div/div/div/div/div[3]/a/div")).click(); //ツイートボックス？の表示
}

void write_tweet(String tweet){
  if (tweet.length() <= 4){
    driver.switchTo().activeElement().sendKeys(tweet.substring(0,1));
  }
  else if ((tweet.length() >= 5) && (tweet.length() <= 8)){
    if (tweet.substring(0,5).equals("ENTER")){
       driver.switchTo().activeElement().sendKeys(Keys.ENTER);
    }
    else if (tweet.substring(0,5).equals("SPACE")){
       driver.switchTo().activeElement().sendKeys(" ");
    }
  }
  else if (tweet.length() >= 9){
    if (tweet.substring(0,9).equals("BACKSPACE")){
      driver.switchTo().activeElement().sendKeys(Keys.BACK_SPACE);
    }
  }
}

void send_tweet(){
  driver.switchTo().activeElement().sendKeys(Keys.chord(Keys.COMMAND, Keys.ENTER)); //commandキーを押しながらenterキーを押す指示
}

void dispose(){
  driver.quit();
  println("disposed.");
}
