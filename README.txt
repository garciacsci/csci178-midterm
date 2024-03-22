Use the given game engine to create the following. Make sure to add appropriate classes
if required. 
  - I made modifications to existing classes; no additional classes were created


Include a text (READMe.txt) file outlining your task and approach.
  - This is the README
  - All throughout the project I tried to make commits when major features were implemented
  - I also did a lot of fine tuning on the timings for certain animations

  - I tackled this iteratively, starting first with getting the parallax to work 
    * I'm quite pleased with my parallax background as it has 5 layers

  - I then moved on to getting the player working properly
    * I implemented the player and got the STAND animation working
    * I then moved on to WALKLEFT and WALKRIGHT
    * After this I spent a long time getting the JUMP animation down since it spans
      multiple rows in the spritesheet I was using
        - One of the first things I had to tackle was preventing the default STAND 
          animation from interrupting the JUMP animation from finishing
            * I did this by adding a condition to the KEYUP case in the keystroke handler
              that checks to make sure the player isn't jumping before switching to the
              default STAND animation
        - I refined my approach by breaking the animation down into JUMP and FALL
          * This made rendering the animation simpler and cleaner since I could now
            also delegate the vertical player translations to each animation
        - One of the last things I did was revisit this to have left and right jump
          and fall animations since being locked in facing right was bothering me
    * I also made it so that the player keeps facing the direction they were last facing
      instead of defaulting to right all the time in the STAND animation
    * The very last thing I did was add a check in GLDrawScene that doesn't let the player's x
      position go outside of the scene's bounds (on my laptop screen)
        - You can disable this by commenting out this block
          ``` 
          if(Player->plPosition.x > 1.3)
            Player->plPosition.x = 1.3;
          if(Player->plPosition.x < -1.3)
            Player->plPosition.x = -1.3;
          ```
          in GLScene.cpp under the //-- Player Drawing --// comment

  - I finally moved onto Enemies (which I'm using as the "random objects" that move towards the player)
    * I first got it so that they were appropriately placed and scaled in the scene
    * Next I got it so that they had different textures (colors)
    * Then I made their color and placement assignment "variable"
      - Technically it's fixed what color they get (1-> green 2-> blue 3->red) but it looks random because
        their horizontal placement is random (so the order of colors is different each run)
    * Next I got it so that they were properly animated
    * Then I got them moving horizontall properly as well
      - I later circled back and it made it so that they correctly circled back and continued to follow 
        the player even if the player jumps over past them
    * After that I modified the collision detection to not register a hit from too far or close
    * Next I set up of the death animation so that it triggered when the player collided with an enemy
    * Then I made it so that when the animation finished the alive bool get updated to false
      - I used this in GLSCene to conditionally render the enemy
      - If an enemy was dead it wouldn't be rendered, but would instead be randomly placed not far off screen
        to the right
    * I didn't like that when the player was running left or right the slime movement was not affected
      - So I added a keyEnemey class to translate the slimes left or right appropriately in sync with 
        the parallax background
      - I added in a check to make it so that they don't get translated if they're in their death animation
    * At this point the slimes would respawn in place if they collided with the player while the player was
      running left or right
      - I fixed this by making the conditional render check if the death animation was taking place instead
        of the alive bool
    * Very last thing I did was add randomized scaling to the slimes and improved hit detection
      since the sizes of the slimes were now variable



        



Submit your complete work as in compressed (zip) file to the link in blackboard. If your
program not running in a remote machine you may not get complete marks. Therefore,
make sure your program runs without errors. 
  - I had to make some modifications to the .cdb since there were absolute paths set for
    some of the dependencies. I verified that everything ran as expected in codeblocks after
    making those fixes though.


Your creativity will be awarded extra 5 points.
  - I hope the extra polish and cohesiveness of my project can net me some points :)


1) Have two animations for a player (run and jump) [x]

2) Move the parallax opposite direction of the player running [x]
  - Enemies also move as expected with the parallax


3) Have random objects move towards the player [x]
  - I used the Enemy class for this and made it so that they move towards the player
    * The randomness is their horizontal spread on spawn, scale, and their color
      - The initial "order" of the enemies colors should therefore differ between runs
    * I also made it so that they "respawn" after dying on collision with the player
    * They all come in from the right of the scene moving left, but will turn around
      and go to the right if the player jumps over them

4) Make player jump over objects with jump animation (up key pressed)
  - Player can jump over enemies (both right and left with appropriate animations)

5) Make objects disappear if player collide; [x]
  - Colliding with the player triggers a death animation after which the enemy is no longer
    rendered
      * Once that happens the non rendered enemy object's location is adjusted similar to the
        initial spawn, except this time it happens off screen further to the right to give the illusion
        of a continous stream of oncoming enemies

