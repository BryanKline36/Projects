
// Asset path constants
var SQUASH_SOUND_PATH = "audio/squash.wav";
var CRASH_SOUND_PATH = "audio/crash.wav";
var POLICE_SOUND_PATH = "audio/police.wav";
var LEVEL_TRANSIT_SOUND_PATH = "audio/levelTransit.wav"; 
var GAME_MUSIC_PATH = "audio/musicGame.wav";
var MENU_MUSIC_PATH = "audio/start.wav";
var WIN_MUSIC_PATH = "audio/musicWin.wav";
var LOSE_MUSIC_PATH = "audio/lose.wav";
var PLAYER_IMAGE = "images/player1.png";
var FROG_IMAGE_ONE = "images/upfrog1.png";
var FROG_IMAGE_TWO = "images/upfrog2.png";
var DEAD_FROG_IMAGE = "images/blood.png";
var TOP_SCENE_IMAGE_ONE = "images/TopScene.jpg";
var MEDIAN_SCENE_IMAGE_ONE = "images/MedianScene.jpg"; 
var BOTTOM_SCENE_IMAGE_ONE = "images/BottomScene.jpg";
var TOP_SCENE_IMAGE_TWO = "images/TopScene2.jpg";
var MEDIAN_SCENE_IMAGE_TWO = "images/MedianScene2.jpg"; 
var BOTTOM_SCENE_IMAGE_TWO = "images/BottomScene2.jpg";
var TOP_SCENE_IMAGE_THREE = "images/TopScene3.png";
var MEDIAN_SCENE_IMAGE_THREE = "images/MedianScene3.png"; 
var BOTTOM_SCENE_IMAGE_THREE = "images/BottomScene3.png";
var LEFT_SEMI_IMAGE_ONE = "images/leftsemi1.jpg"; 
var LEFT_CAR_IMAGE_ONE = "images/leftcar1.jpg"; 
var RIGHT_CAR_IMAGE_TWO = "images/rightcar2.jpg"; 
var RIGHT_CAR_IMAGE_FIVE = "images/rightcar5.jpg"; 
var COP_CAR_IMAGE = "images/copRight.jpg";
var COP_CAR_RED = "images/copRightRed.jpg";
var COP_CAR_BLUE = "images/copRightBlue.jpg";
var PAUSE_IMAGE = "images/pauseBack.png";
var WIN_IMAGE = "images/winMenu.png";
var LOSE_IMAGE = "images/loseMenu.png";
var LEVEL_IMAGE_ONE = "images/level1Menu.png";
var LEVEL_IMAGE_TWO = "images/level2Menu.png";
var LEVEL_IMAGE_THREE = "images/level3Menu.png";
var QUIT_SELECT_BUTTON = "images/buttons/QuitSel.png";
var QUIT_UNSELECT_BUTTON = "images/buttons/QuitUn.png";
var SOUND_OFF_SELECT_BUTTON = "images/buttons/SoundOffSel.png";
var SOUND_OFF_UNSELECT_BUTTON = "images/buttons/SoundOffUn.png";
var SOUND_ON_SELECT_BUTTON = "images/buttons/SoundOnSel.png";
var SOUND_ON_UNSELECT_BUTTON = "images/buttons/SoundOnUn.png";
var RESUME_SELECT_BUTTON = "images/buttons/ResumeSel.png";
var RESUME_UNSELECT_BUTTON = "images/buttons/ResumeUn.png";

// JQuery key code constants
var LEFT = 37
var RIGHT = 39;
var UP = 38;
var DOWN = 40;
var SPACE = 32
var ESCAPE = 27;
var ENTER = 13;

// Game value constants
var BLACK = "#000000";
var HELVETICA = "40px Helvetica";
var WHITE = "white";
var SCORE_LABEL = "Score: ";
var LIVES_LABEL = "Lives: ";

// Game value variables
var pauseSelection = 0;
var soundOn = true;
var pause = false;
var dt = 1000/30.0;
var scrollSpeed = 0.4;
var horizontal = 0;
var vertical = 0;
var level = 1;
var e;
var gameOn = true;
var carCountDifficulty = 150;
var carCount = 150;
var frogCount = 150;
var frogCountDifficulty = 150;
var musicFlag = 0;
var startFlag = false;
var keyPressed = false;
var soundKey = false;
var resumeKey = false;
var quitKey = false;
var frogProbability = 0.75;
var carProbability = 0.5;
var copProbability = 0;
var carSpeed = 7.5;
var SCREEN_WIDTH = SCREEN_WIDTH;
var SCREEN_HEIGHT = SCREEN_HEIGHT;
var START_X_POSITION = START_X_POSITION;
var START_Y_POSITION = START_Y_POSITION;

//Menus images
var pauseImage = new Image();
pauseImage.src = PAUSE_IMAGE;
var winImage = new Image();
winImage.src = WIN_IMAGE;
var loseImage = new Image();
loseImage.src = LOSE_IMAGE;
var level1Image = new Image();
level1Image.src = LEVEL_IMAGE_ONE;
var level2Image = new Image();
level2Image.src = LEVEL_IMAGE_TWO;
var level3Image = new Image();
level3Image.src = LEVEL_IMAGE_THREE;

//Button images
var quitSel = new Image();
quitSel.src = QUIT_SELECT_BUTTON;
var quitUn = new Image();
quitUn.src = QUIT_UNSELECT_BUTTON;
var soundOffSel = new Image();
soundOffSel.src = SOUND_OFF_SELECT_BUTTON;
var soundOffUn = new Image();
soundOffUn.src = SOUND_OFF_UNSELECT_BUTTON;
var soundOnSel = new Image();
soundOnSel.src = SOUND_ON_SELECT_BUTTON;
var soundOnUn = new Image();
soundOnUn.src = SOUND_ON_UNSELECT_BUTTON;
var resumeSel = new Image();
resumeSel.src = RESUME_SELECT_BUTTON;
var resumeUn = new Image();
resumeUn.src = RESUME_UNSELECT_BUTTON;

//Game sounds
var soundSquash = new Audio(SQUASH_SOUND_PATH);
var soundCrash = new Audio(CRASH_SOUND_PATH);
var soundCop = new Audio(POLICE_SOUND_PATH);
var soundTransit = new Audio(LEVEL_TRANSIT_SOUND_PATH);
var musicGameplay = new Audio(GAME_MUSIC_PATH);
var musicMenu = new Audio(MENU_MUSIC_PATH);
var musicWin = new Audio(WIN_MUSIC_PATH);
var musicLose = new Audio(LOSE_MUSIC_PATH);

//Car images
semiLeft = new Image();  
semiLeft.src = LEFT_SEMI_IMAGE_ONE; 
carLeft = new Image();  
carLeft.src = LEFT_CAR_IMAGE_ONE; 
carRight1 = new Image();  
carRight1.src = RIGHT_CAR_IMAGE_TWO; 
carRight0 = new Image();  
carRight0.src = RIGHT_CAR_IMAGE_FIVE; 
copRight = new Image();
copRight.src = COP_CAR_IMAGE;
copRightRed = new Image();
copRightRed.src = COP_CAR_RED;
copRightBlue = new Image();
copRightBlue.src = COP_CAR_BLUE;

//Canvas creation
var map = document.getElementById("map"); 
var ctx = map.getContext("2d");


//Game objects


//The player object	
function Player()
{
	this.playerImage = new Image();  
	this.playerImage.src = PLAYER_IMAGE; 
	this.y = START_Y_POSITION;
	this.x = START_X_POSITION - (this.playerImage.width/2);
	this.left = this.x;
	this.right = (this.x + this.playerImage.width);
	this.top = this.y;
	this.bottom = (this.y + this.playerImage.height);
	this.lives;
	this.score;	
	this.isCop = false;
}

//The frog object
function Frogs()
{
	this.frogImage1 = new Image();
	this.frogImage2 = new Image();
	this.frogImageDead = new Image();  
	this.frogImage1.src = FROG_IMAGE_ONE;
	this.frogImage2.src = FROG_IMAGE_TWO; 
	this.frogImageDead.src = DEAD_FROG_IMAGE; 
	this.y;
	this.x;
	this.left = (this.x) + 40;
	this.right = this.x + this.frogImage1.width;
	this.top = this.y;
	this.bottom = this.y + this.frogImage1.height;
	this.alive = true;
	this.isCop = false;
}

//The car object
function Cars()
{
	this.image = new Image();
	this.y;
	this.x;
	this.left = this.x;
	this.right;
	this.top = this.y;
	this.bottom;
	this.direction;
	this.speed;
	this.isCop = false;
}

//Top game scene object
function TopScene()
{
	this.topImage = new Image();  
	this.topImage.src = TOP_SCENE_IMAGE_ONE;
	this.topImage2 = new Image();  
	this.topImage2.src = TOP_SCENE_IMAGE_TWO; 
	this.topImage3 = new Image();  
	this.topImage3.src = TOP_SCENE_IMAGE_THREE;
	this.x = 0;
	this.y = 0;		
}

//Median game scene object
function MedianScene()
{
	this.medianImage = new Image();  
	this.medianImage.src = MEDIAN_SCENE_IMAGE_ONE;
	this.medianImage2 = new Image();  
	this.medianImage2.src = MEDIAN_SCENE_IMAGE_TWO;
	this.medianImage3 = new Image();  
	this.medianImage3.src = MEDIAN_SCENE_IMAGE_THREE;
	this.x = 0;
	this.y = 275;
	this.left = this.x;
	this.right = (this.x + this.medianImage.width);
	this.top = this.y;
	this.bottom = (this.y + this.medianImage.height);
	this.isCop = false;
}

//Bottom game scene object
function BottomScene()
{
	this.bottomImage = new Image();  
	this.bottomImage.src = BOTTOM_SCENE_IMAGE_ONE;
	this.bottomImage2 = new Image(); 
	this.bottomImage2.src = BOTTOM_SCENE_IMAGE_TWO;
	this.bottomImage3 = new Image(); 
	this.bottomImage3.src = BOTTOM_SCENE_IMAGE_THREE;
	this.x = 0;
	this.y = 450;		
}

//Game scene instance creation 
var SceneTop = new TopScene();
var SceneMedian = new MedianScene();
var SceneBottom = new BottomScene();

//Initializationof the main object array and its subarrays where row 0 is the player, 
//row 1 is an array of frogs, and row 2 is an array of cars cars
var objectArray = [];
for (var i = 0; i < 3; i++) 
{
	objectArray[i] = [];
}
objectArray[0][0] = new Player();
for (var i = 0; i < frogProbability; i++) 
{
	objectArray[1][i] = new Frogs();
}





//Sets player values to initial values
objectArray[0][0].score = 0;
objectArray[0][0].lives = 3;

//Initially positions frogs in game scene
for(i = 0; i < frogProbability; i++)
{
	var yNum = Math.random() * 430;
	
	if(yNum < 150)
	{
		yNum += 160; 
	}
	if((yNum > 270) && (yNum < 350))
	{
		yNum += 80;
	}
	
	objectArray[1][i].x = (Math.random()* SCREEN_WIDTH) + Math.random() * 100;
	objectArray[1][i].y = yNum;
}

//Function which moves cars to the top of their row in the array, and randomly creates a car
function carManager() 
{
	var lengthDown = 0;
	//removes cars outside the map from the array, and consolidates cars in their array
	for(var i = 0; i < objectArray[2].length; i++) 
	{
		if(i != objectArray[2].length - 1) 
		{
			if(objectArray[2][i].x < -100 || objectArray[2][i].x > SCREEN_WIDTH) 
			{
				objectArray[2][i] = objectArray[2][i + 1];
				objectArray[2][i + 1] = 0;
				lengthDown++;		
			}
			else if((objectArray[2][i] == 0) && i != objectArray[2].length - 1) 
			{
				objectArray[2][i] = objectArray[2][i + 1];
				objectArray[2][i + 1] = 0;	
			}
		}
		else if(objectArray[2][i].x < -100 || objectArray[2][i].x > SCREEN_WIDTH) 
		{
			lengthDown++;
		}
	}
	
	objectArray[2].length = objectArray[2].length - lengthDown;
	
	//randomly creates cars using carCount variable to keep them regularly spaced
	if(carCount > 0) 
	{
		carCount--;
	}
	else if(Math.random() * 100 <= carProbability && carCount == 0) 
	{
		var carType = Math.random() * 100;
		
		if(carType < 20) 
		{
			var currentCarIndex = objectArray[2].length;
			objectArray[2][currentCarIndex] = new Cars();
			objectArray[2][currentCarIndex].direction = -1;
			objectArray[2][currentCarIndex].speed = carSpeed;
			objectArray[2][currentCarIndex].x = SCREEN_WIDTH;
			objectArray[2][currentCarIndex].y = 160;
			
			if(Math.random() * 100 < 50) 
			{
				objectArray[2][currentCarIndex].image = carLeft;
			}
			else 
			{
				objectArray[2][currentCarIndex].image = semiLeft;
			}
		}
		else if(carType >= 20 && carType < 40) 
		{
			var currentCarIndex = objectArray[2].length;
			objectArray[2][currentCarIndex] = new Cars();
			objectArray[2][currentCarIndex].direction = -1;
			objectArray[2][currentCarIndex].speed = carSpeed;
			objectArray[2][currentCarIndex].x = SCREEN_WIDTH;
			objectArray[2][currentCarIndex].y = 220;
			
			if(Math.random() * 100 < 50) 
			{
				objectArray[2][currentCarIndex].image = carLeft;
			}
			else 
			{
				objectArray[2][currentCarIndex].image = semiLeft;
			}
		}
		else if(carType >= 40 && carType < 60) 
		{
			var currentCarIndex = objectArray[2].length;
			objectArray[2][currentCarIndex] = new Cars();
			objectArray[2][currentCarIndex].direction = 1;
			objectArray[2][currentCarIndex].speed = carSpeed;
			objectArray[2][currentCarIndex].x = -100;
			objectArray[2][currentCarIndex].y = 400;
			
			if(Math.random() * 100 < 50) 
			{
				objectArray[2][currentCarIndex].image = carRight0;
			}
			else 
			{
				objectArray[2][currentCarIndex].image = carRight1;
			}
		} 
		else if(carType >= 60 && carType < 80) 
		{
			var currentCarIndex = objectArray[2].length;
			objectArray[2][currentCarIndex] = new Cars();
			objectArray[2][currentCarIndex].direction = 1;
			objectArray[2][currentCarIndex].speed = carSpeed;
			objectArray[2][currentCarIndex].x = -100;
			objectArray[2][currentCarIndex].y = 340;
			if(Math.random() * 100 < 50) 
			{
				objectArray[2][currentCarIndex].image = carRight0;
			}
			else 
			{
				objectArray[2][currentCarIndex].image = carRight1;
			}
		}
		else if(carType >= 80) 
		{
			var currentCarIndex = objectArray[2].length;
			objectArray[2][currentCarIndex] = new Cars();
			objectArray[2][currentCarIndex].direction = 1;
			objectArray[2][currentCarIndex].speed = carSpeed;
			objectArray[2][currentCarIndex].x = -100;
			objectArray[2][currentCarIndex].y = 340;
			objectArray[2][currentCarIndex].isCop = true;
			objectArray[2][currentCarIndex].image = copRight;	
		}
		
		carCount = carCountDifficulty;
	}
}

//Functions to create the cop car animation
function copAnimation()
{
	setTimeout(copRed, 300);
	setTimeout(wait, 100);
	setTimeout(copBlue, 400);
}

function copRed()
{
	copImage = copRightRed;
}

function copBlue()
{
	copImage = copRightBlue;
}


//Functions:
























//JQuery function that senses keystrokes.  
$(document).keydown(function(e) 
{
	if(e.keyCode == LEFT)
	{
		horizontal = -1;
	}
	else if(e.keyCode == RIGHT)	
	{	
		horizontal = 1;
	}
	else if(e.keyCode == UP)
	{
		vertical = -1;
	}
	else if(e.keyCode == DOWN)
	{		
		vertical = 1;
	}
	else if(e.keyCode == SPACE)
	{
		if(!gameOn)
		{				
			gameOn = true;
			objectArray[0][0].x = START_X_POSITION - (objectArray[0][0].playerImage.width);
			objectArray[0][0].y = START_Y_POSITION;
			SceneTop.x = 0;
			SceneMedian.x = 0;
			SceneBottom.x = 0;
			
			for(i = 0; i < objectArray[1].length; i++)
			{
				objectArray[1][i].x = (Math.random() * SCREEN_WIDTH + 700);
			}
		}
	}
	if (e.keyCode == SPACE && pause) 
	{
		pause = false;
	}
	else if (e.keyCode == SPACE && !pause && gameOn) 
	{
		pauseSelection = 0;
		pause = true;
		soundKey = false;
		resumeKey = false;
		quitKey = false;
	}
});

$(document).keyup(function(e) 
{
	if(e.keyCode == LEFT || e.keyCode == RIGHT)
	{
		horizontal = 0;
	}
	if(e.keyCode == UP || e.keyCode == DOWN)
	{
		vertical = 0;
	}
});































//Function that changes game state depending on keystrokes sensed.
function controls()
{
	if(horizontal == -1)
	{
		objectArray[0][0].x = (objectArray[0][0].x - 10);
	}
	if(horizontal == 1)
	{
		objectArray[0][0].x = (objectArray[0][0].x + 7.5);
	}
	if(vertical == -1)
	{
		objectArray[0][0].y = (objectArray[0][0].y - 9);
	}
	if(vertical == 1)
	{
		objectArray[0][0].y = (objectArray[0][0].y + 9);
	}	
	if(objectArray[0][0].x <= 0)
	{
		objectArray[0][0].x = 0;
	}
	if(objectArray[0][0].x >= 570)
	{
		objectArray[0][0].x = 570;
	}
	if(objectArray[0][0].y >= START_Y_POSITION)
	{
		objectArray[0][0].y = START_Y_POSITION;
	}
	if(objectArray[0][0].y <= 150)
	{
		objectArray[0][0].y = 150;
	}
}


//Function that scrolls the top, median and bottom objects that make up the scene.
function scroll()
{
	SceneTop.x -=  scrollSpeed * dt;
	
	if(SceneTop.x < -(SceneTop.topImage.width - SCREEN_WIDTH))
	{
		SceneTop.x = 0;
	}
	
	SceneMedian.x -=  scrollSpeed * dt;
	
	if(SceneMedian.x < -(SceneMedian.medianImage.width + 300))
	{
		SceneMedian.x = SCREEN_WIDTH;
	}
	
	SceneBottom.x -=  scrollSpeed * dt;
	
	if(SceneBottom.x < -(SceneBottom.bottomImage.width - SCREEN_WIDTH))
	{
		SceneBottom.x = 0;
	}	
}


//Frog functions:

//Function that makes frogs
function frogMaker()
{
	if (frogCount == 0)
	{
		if (Math.random() <= frogProbability)
		{
			var newFrog = objectArray[1].length
			objectArray[1][newFrog] = new Frogs();
			objectArray[1][newFrog].alive = true;
			objectArray[1][newFrog].x = 900;
			objectArray[1][newFrog].y = 200 + (Math.random() * 240);
		}
		
		frogCount = frogCountDifficulty;
	}
	else
	{
		frogCount--;
	}
}

//Function that scrolls the x position of the frogs with the scenery
function frogScroll(Frog)
{
	Frog.x -= scrollSpeed * dt;
}

//Randomly cycles through the two live frog images, giving the appearance of hopping or motion.
function drawFrog(Frog)
{
	var num = (Math.random() * 100);
	
	if((num >= 0) && (num < 50))
	{	
		ctx.drawImage(Frog.frogImage1, Frog.x, Frog.y);
	}
	if((num >= 50)&&(num < 100))
	{	
		ctx.drawImage(Frog.frogImage2, Frog.x, Frog.y);
	}	
}

//Changes the frog y position randomly so that the fogs don't simply fly up the
//page, but randomly kind of wait for a second or so before moving up again.
function frogHop(Frog)
{
	var num = (Math.random() * 100);
	
	frogPosition(Frog);
	
	if(((num > 10) && (num < 20)) && Frog.alive)
	{	
		Frog.y -= 4;
	}
}

//Checks to see if the Frog object bool is alive is true, if so the above function drawFrog
//is called to make a hopping frog, if not it will remain dead.
function isFrogAlive(Frog)
{
	if(Frog.alive)
	{
		drawFrog(Frog);
	}	
}

//Once frogs have scrolled off the screen this function respawns the frog random positions and it
//calls the positionUpdate function to get the coordinates of their sides for collision purposes.
function frogPosition(Frog)
{
	var yNum;
	
	positionUpdate(Frog, Frog.frogImage1.width, Frog.frogImage1.height);
	yNum = Math.random() * 430;
	
	if(yNum < 150)
	{
		yNum += 160; 
	}
	if((yNum > 270) && (yNum < 340))
	{
		yNum += 80;
	}		
	if(Frog.x < -100)
	{
		Frog.alive = true;
		Frog.y = yNum;
		Frog.x = Math.random() * 100 + 900;
	}
	if(Frog.y <= 140)
	{
		if(objectArray[0][0].score > 0)
		{
			objectArray[0][0].score -= 10;
		}	
		
		Frog.y = yNum;
		Frog.x = Math.random()*100 + 700;
		Frog.alive = true;
	}
}

//Checks to see if a frog is up against the median, if so the frog just stays put in the road.
function medianAndFrog(Frog)
{
	if(!collision(Frog, SceneMedian))
	{
		frogHop(Frog);
	}
}

//Checks to see if there's been a collision with either a car or the player car, makes the bool
//alive false and increments the player's score, which as of yet is not working properly
//as it will continually increment if there is an intersection even if the frog is dead. 
function frogAndCar()
{
	for (var i = 0; i < objectArray[1].length; i++) 
	{
		if (collision(objectArray[0][0], objectArray[1][i]) && objectArray[1][i].alive)
		{
			objectArray[0][0].score += 10;
			objectArray[1][i].alive = false;
			soundSquash.play();
		}
		for (var j = 0; j < objectArray[2].length; j++) 
		{
			if(collision(objectArray[2][j], objectArray[1][i]))
			{
				objectArray[1][i].alive = false;
				soundSquash.play();
			}
		}
		if (objectArray[1][i].x < -100)
		{
			for (var j = i; j < objectArray[1].length; j++) 
			{
				if (j != objectArray[1].length - 1)
				{
					objectArray[1][j] = objectArray[1][j + 1];
				}
			}
			objectArray[1].length--;
		}
	}
}

//If the bool alive is false this draws the frog as a blood stain.
function deadFrog(Frog)
{
	if(Frog.alive == false)
	{
		ctx.drawImage(Frog.frogImageDead, Frog.x, Frog.y);
		frogHop(Frog);
	}
}

//This packages all the above frog functions into one that can be called once in update.
function setFrog(Frog)
{
	frogScroll(Frog);
	isFrogAlive(Frog);
	frogPosition(Frog);
	medianAndFrog(Frog);
	deadFrog(Frog);
}


//Car function:

//Moves the cars in either direction depending upon the way their image is facing, cars going
//the opposite direction from the player car move faster. 
function driveCar(Car)
{
	if(Car.direction == -1)
	{
		Car.x -= Car.speed * 0.2 * dt;
	}
	else if(Car.direction == 1)
	{
		Car.x += Car.speed * 0.03 * dt;
	}
}


//General functions:

function levelMenu()
{
	gameOn = false;
	
	if(level == 1)
	{
		ctx.fillStyle = BLACK;
		ctx.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		ctx.drawImage(level1Image, 0, 0);
	}	
	if(level == 2)
	{
		ctx.fillStyle = BLACK;
		ctx.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		ctx.drawImage(level2Image, 0, 0);
	}
	if(level == 3)
	{
		ctx.fillStyle = BLACK;
		ctx.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		ctx.drawImage(level3Image, 0, 0);
	}
	
	setTimeout(waitMenu, 3000);
}

function pauseMenu()
{
	console.log(pauseSelection);
	
	$(document).keydown(function(e) 
	{
		if((e.keyCode == UP) && !keyPressed)
		{
			pauseSelection--;
			keyPressed = true;
		}
		if((e.keyCode == DOWN) && !keyPressed)
		{
			pauseSelection++;
			keyPressed = true;
		}
		if((e.keyCode == ENTER) && !keyPressed)
		{
			resumeKey = true;
			quitKey = true;
			keyPressed = true;
			
			if(soundOn)
			{
				soundKey = true;
			}
			else
			{
				soundKey = false;
			}
		}
	});
	
	$(document).keyup(function(e) 
	{
		if(e.keyCode == UP)
		{
			keyPressed = false;
		}
		if(e.keyCode == DOWN)
		{
			keyPressed = false;
		}
		if(e.keyCode == ENTER)
		{
			resumeKey = false;
			quitKey = false;
			keyPressed = false;
		}
	});
	
	if (pauseSelection >= 3)
	{
		pauseSelection = 0;
	}
	if (pauseSelection <= -1)
	{
		pauseSelection = 2;
	}
	
	ctx.fillStyle = BLACK;
	ctx.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	ctx.drawImage(pauseImage,0,0);
	
	if (pauseSelection == 0)
	{
		ctx.drawImage(resumeSel, 40, 100);
		if(resumeKey)
		{
			pause = false;
		}
	}
	else
	{
		ctx.drawImage(resumeUn, 40, 100);
	}
	if (pauseSelection == 1)
	{
		if (soundOn)
		{
			if(soundKey)
			{	
				ctx.drawImage(soundOffSel, 40, 200);
			}
			if(soundKey)
			{
				ctx.drawImage(soundOnSel, 40, 200);
				soundOn = false;
			}
		}
		else
		{
			if(soundKey)
			{
				ctx.drawImage(soundOnSel, 40, 200);
				soundOn = true;
			}
			if(soundKey)
			{
				ctx.drawImage(soundOnSel, 40, 200);
			}
		}
	}
	else
	{
		if(soundOn)
		{
			ctx.drawImage(soundOffUn, 40, 200);
		}
		else
		{
			ctx.drawImage(soundOnUn, 40, 200);
		}
	}
	if (pauseSelection == 2)
	{
		ctx.drawImage(quitSel, 40, 300);
		if(quitKey)
		{
			gameEnd();
		}
	}
	else
	{
		ctx.drawImage(quitUn, 40, 300);
	}
}

function waitMenu()
{
	gameOn = true;
}

//Checks score to see if score is in some range, and what the current level is to then resets the score, object positions 
//and the car array and changes carCountDifficulty, makes fewer frogs and increases scrollSpeed and increments level
function levelCheck()
{
	if((objectArray[0][0].score >= 20) && (level == 1))
	{	
		level = 2;
		levelMenu();
		scrollSpeed = 0.50;
		objectArray[0][0].x = 20;
		objectArray[0][0].y = START_Y_POSITION;
		SceneTop.x = 0;
		SceneMedian.x = 0;
		SceneBottom.x = 0;
		objectArray[2] = [];
		objectArray[1] = [];
		//frogProbability = 1;
		//carProbability = 1;
		//carCountDifficulty = 200;
		//frogCountDifficulty = 200;
		for(i = 0; i < objectArray[1].length; i++)
		{
			objectArray[1][i].x = (Math.random()*SCREEN_WIDTH + 700);
		}
	}
	else if((objectArray[0][0].score >= 30) && (level == 2))
	{
		level = 3;
		levelMenu();
		scrollSpeed = 0.7;
		objectArray[0][0].x = 20;
		objectArray[0][0].y = START_Y_POSITION;
		SceneTop.x = 0;
		SceneMedian.x = 0;
		SceneBottom.x = 0;
		objectArray[2] = [];
		objectArray[1] = [];
		//frogProbability = 1;
		//carProbability = 1;
		//carCountDifficulty = 300;
		//frogCountDifficulty = 300;
		
		for(i = 0; i < objectArray[1].length; i++)
		{
			objectArray[1][i].x = (Math.random() * SCREEN_WIDTH + 700);
		}
	}
	else if((objectArray[0][0].score >= 100) && (level == 3))
	{
		if(soundOn == true)
		{
			musicWin.play();
		}	
		ctx.fillStyle = BLACK;
		ctx.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		ctx.drawImage(winImage, 0, 0);
		gameOn = false;
	}
}


//Function that takes in a object and sets its top, bottom, left and right variables to their
//x and y values to check for collisions.
function positionUpdate(object, width, height)
{
	object.left = object.x;
	object.right = (object.x + width);
	object.top = object.y;
	object.bottom = (object.y + height);
	
	if(object.isCop)
	{
		object.top += 30;
		object.bottom += 30;
		object.left += 30;
		object.right += 30;
	}
}

//Function that takes in two objects and checks to see if there is overlap, this function as well as
//the above positionUpdate will probably not be necessary once a 2D array is implemented to 
//keep track of collisions.
function collision(R2, R1)
{
	if((((R2.left > R1.left) && (R2.left < R1.right)) || ((R2.right > R1.left) && (R2.right < R1.right))) &&
	(((R2.top > R1.top) && (R2.top < R1.bottom) || (R2.bottom > R1.top) && (R2.bottom < R1.bottom))))
	{	
		return true;
	}
	else 
	{
		return false;
	}
}

//Function that draws images on an interval, but first goes through the below gameStatus function
//which allows update to be interrupted.
function gameStatusInterval()	
{ 
	setInterval(gameStatus, 100.0/3); 
}


//Updates game unless the global bool gameOn is false in which case the game ends. 
function gameStatus()
{
	if(gameOn)
	{
		update();
	}
}

function gameEnd()
{
	if(soundOn)
	{
		musicLose.play();
	}
	ctx.fillStyle = BLACK;
	ctx.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	ctx.drawImage(loseImage, 0, 0);
	gameOn = false;
}


//Sets the interval for the gameStatus function which is the main loop of the game
gameStatusInterval();

levelMenu();

//Update function.
function update()
{ 
	if(!pause) 
	{
		ctx.fillStyle = BLACK;
		ctx.fillRect(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
		
		ctx.drawImage(objectArray[0][0].playerImage, objectArray[0][0].x, objectArray[0][0].y);
		controls();
		
		frogMaker();
		frogAndCar();

		if(level == 1)
		{
			ctx.drawImage(SceneTop.topImage, SceneTop.x, SceneTop.y);
			ctx.drawImage(SceneMedian.medianImage, SceneMedian.x, SceneMedian.y);
			ctx.drawImage(SceneBottom.bottomImage, SceneBottom.x, SceneBottom.y);
		}
		if(level == 2)
		{
			ctx.drawImage(SceneTop.topImage2, SceneTop.x, SceneTop.y);
			ctx.drawImage(SceneMedian.medianImage2, SceneMedian.x, SceneMedian.y);
			ctx.drawImage(SceneBottom.bottomImage2, SceneBottom.x, SceneBottom.y);
		}
		if(level == 3)
		{
			ctx.drawImage(SceneTop.topImage3, SceneTop.x, SceneTop.y);
			ctx.drawImage(SceneMedian.medianImage3, SceneMedian.x, SceneMedian.y);
			ctx.drawImage(SceneBottom.bottomImage3, SceneBottom.x, SceneBottom.y);
		}
		
		positionUpdate(objectArray[0][0], objectArray[0][0].playerImage.width, objectArray[0][0].playerImage.height);
		positionUpdate(SceneMedian, SceneMedian.medianImage.width, SceneMedian.medianImage.height);

		for (var i = 0; i < objectArray[2].length; i++) 
		{
			if(objectArray[2][i].isCop)
			{
				objectArray[2][i].image = copImage;
			}

			positionUpdate(objectArray[2][i], objectArray[2][i].image.width, objectArray[2][i].image.height);
			ctx.drawImage(objectArray[2][i].image, objectArray[2][i].x, objectArray[2][i].y);
			driveCar(objectArray[2][i]);

			if(collision(objectArray[0][0], objectArray[2][i]))
			{
				if(!objectArray[2][i].isCop && soundOn)
				{
					soundCrash.play();
				}
				else if(objectArray[2][i].isCop && soundOn)
				{
					soundCop.play();
				}

				gameOn = false;
				objectArray[0][0].lives--;
				objectArray[0][0].score = 0;
				objectArray[2] = [];
			}
		}
		
		if(!collision(objectArray[0][0], SceneMedian))			
		{	
			scroll();
		}	

		if(collision(objectArray[0][0], SceneMedian))
		{
			gameOn = false;
			objectArray[0][0].lives--;
			objectArray[0][0].score = 0;
			objectArray[2] = [];
			if(soundOn == true)
			{
				soundCrash.play();
			}
		}

		for (var i = 0; i < objectArray[2].length; i++) 
		{
			if(collision(objectArray[0][0], objectArray[2][i]))
			{
				if(!objectArray[2][i].isCop && soundOn)
				{
					soundCrash.play();
				}
				else(objectArray[2][i].isCop && soundOn)
				{
					soundCop.play();
				}
				gameOn = false;
				objectArray[0][0].lives--;
				objectArray[0][0].score = 0;
				objectArray[2] = [];
			}
		}

		ctx.font = HELVETICA;
		ctx.fillStyle = WHITE;
		ctx.fillText(SCORE_LABEL, 380, 50);
		ctx.fillText(objectArray[0][0].score, 500, 50);
		ctx.fillText(LIVES_LABEL, 380, 100);	
		ctx.fillText(objectArray[0][0].lives, 500, 100);	
		
		for (var i = 0; i < objectArray[1].length; i++) 
		{
			setFrog(objectArray[1][i]);
		}
		
		if(objectArray[0][0].lives < 1)
		{
			gameEnd();
		}
		
		levelCheck();
		carManager();
		copAnimation();
	}

	if (pause) 
	{
		pauseMenu();
	}
}
