void tweetThread(String tweet){
  
  if (c == 0){
    driver.get("https://twitter.com");
    print("url¥n");
    delay(500); //1秒くらい待機
    driver.findElement(By.linkText("ログイン")).click();
    delay(500); //1秒くらい待機
    driver.switchTo().activeElement().sendKeys(TwiId); //アクティブな要素に文字列を送る
    //delay(1000);
    print(driver.getCurrentUrl());
    WebElement login = driver.findElement(By.xpath("//*[@id='react-root']/div/div/div[1]/main/div/div/form/div/div[2]/label/div[2]/div/input"));
    //delay(1000);
    login.sendKeys(TwiPass);
    //delay(500);
    login.sendKeys(Keys.chord(Keys.ENTER));
  }
  delay(2000);
  driver.findElement(By.className("DraftEditor-root")).click(); //ツイートボックス？の表示
  driver.switchTo().activeElement().sendKeys(tweet);
  //delay(2000);
  //if (tweetボタンが押された){
  driver.switchTo().activeElement().sendKeys(Keys.chord(Keys.COMMAND, Keys.ENTER)); //commandキーを押しながらenterキーを押す指示
  //}
  delay(2000);
  //dispose();
}

void dispose(){
  driver.quit();
  println("disposed.");
}
