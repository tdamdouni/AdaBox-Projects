# World's Smallest Pong

_Captured: 2017-09-15 at 10:30 from [www.hackster.io](https://www.hackster.io/mwatson/world-s-smallest-pong-a45ea9)_

![World's Smallest Pong](https://hackster.imgix.net/uploads/attachments/280825/huzzah_pong_7suMPDkLus.jpg?auto=compress%2Cformat&w=900&h=675&fit=min)

I just received my Adafruit Feather HUZZAH and their OLED FeatherWing in the mail, and I put this together to get the hang of things. It is a pretty small--perhaps the smallest--Pong game.

Scoring is simple: hitting the ball with the paddle earns a point, and missing it resets your score. Your high score is kept (until reset).
    
    
    const int buttonA = 0;
    
    
    int score = 0;
    
    
        int r = 2;
        int y = rand() % (31 - 2*r) + r;
        int dx = -2;
    
      int draw() {
        display.fillCircle(x, y, r, WHITE);
    
      int update() {
        if (x >= 109 - r - 1) { dx *= -1; }
        if ((y <= r + 1) or (y >= 31 - r - 1)) { dy *= -1; }
        
        x += dx;
        
    
        int height = 10;
        int width = 2;
        int centerx = width;
        int centery = 16;
      
      int draw() {
        display.fillRect(centerx - width/2, centery - height/2, width, height, WHITE);
      
      int update() {
        if ((buttonAState == LOW) and (centery >= height/2 + 1)) {
        if ((buttonCState == LOW) and (centery <= 31 - height/2 - 1)) {
    
    
    void setup() {
      display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
      display.setTextSize(1);
    
    void loop() {
    
      
      display.setTextSize(1);
      display.setCursor(0,0);
      
      if ((ball.x - ball.r <= paddle.centerx + paddle.width/2 + 1)
      and (ball.y <= paddle.centery + paddle.height/2)
      and (ball.y >= paddle.centery - paddle.height/2)) {
        ball.dx *= -1;
        if (score > max_score) {
    
      if (ball.x <= ball.r) {
        ball.x = 100;
        if (score > max_score) {
    
      ball.update();
      paddle.update();
    
      display.drawLine(0, 0, 109, 0, WHITE);
      display.drawLine(0, 31, 109, 31, WHITE);
      display.drawLine(109, 0, 109, 31, WHITE);
      display.setRotation(1);
      display.setCursor(0,0);
      display.print(score);
      display.setCursor(0,9);
      display.print("HI:");
      display.print(max_score);
      display.setRotation(0);
      ball.draw();
      paddle.draw();
      
      display.display();
    
