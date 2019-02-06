//~sushil/bin/submitFP to submit


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

var BLACK = "#000000";
var HELVETICA = "40px Helvetica";
var WHITE = "white";
var SCORE_LABEL = "Score: ";
var LIVES_LABEL = "Lives: ";
var MAP = "map";
var TWO_DIMENSION = "2d";

// JQuery key code constants

var LEFT = 37
var RIGHT = 39;
var UP = 38;
var DOWN = 40;
var SPACE = 32
var ESCAPE = 27;
var ENTER = 13;


var map = document.getElementById(MAP); 
var ctx = map.getContext(TWO_DIMENSION);

//Menus
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

//buttons
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

//Sound initialization
var soundSquash = new Audio(SQUASH_SOUND_PATH);
var soundCrash = new Audio(CRASH_SOUND_PATH);
var soundCop = new Audio(POLICE_SOUND_PATH);
var soundTransit = new Audio(LEVEL_TRANSIT_SOUND_PATH);
var musicGameplay = new Audio(GAME_MUSIC_PATH);
var musicMenu = new Audio(MENU_MUSIC_PATH);
var musicWin = new Audio(WIN_MUSIC_PATH);
var musicLose = new Audio(LOSE_MUSIC_PATH);


//The player struct.	
function Player()
{
	this.playerImage = new Image();  
	this.playerImage.src = PLAYER_IMAGE; 
	//this.playerImage.addEventListener("load", drawImage);
	this.y = 410;
	this.x = 320 - (this.playerImage.width/2);
	this.left = this.x;
	this.right = (this.x + this.playerImage.width);
	this.top = this.y;
	this.bottom = (this.y + this.playerImage.height);
	this.lives;
	this.score;	
	this.isCop = false;
}

//The Frogs struct has two images which are cycled through to simulate frog motion and one image
//for a dead frog when it gets it.
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

//The Cars struct has four images for different types cars, these could be put in a function inside the
//struct.
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

//This is a struct that creates the top of the scene.
function TopScene()
{
	this.topImage = new Image();  
	this.topImage.src = TOP_SCENE_IMAGE_ONE; 
	//this.topImage.addEventListener("load", drawImage); 
	this.topImage2 = new Image();  
	this.topImage2.src = TOP_SCENE_IMAGE_TWO; 
	//this.topImage2.addEventListener("load", drawImage);
	this.topImage3 = new Image();  
	this.topImage3.src = TOP_SCENE_IMAGE_THREE; 
	//this.topImage3.addEventListener("load", drawImage);
	this.x = 0;
	this.y = 0;		
}

//This is a struct that creates the median.	
function MedianScene()
{
	this.medianImage = new Image();  
	this.medianImage.src = MEDIAN_SCENE_IMAGE_ONE; 
	//this.medianImage.addEventListener("load", drawImage); 
	this.medianImage2 = new Image();  
	this.medianImage2.src = MEDIAN_SCENE_IMAGE_TWO; 
	//this.medianImage2.addEventListener("load", drawImage); 
	this.medianImage3 = new Image();  
	this.medianImage3.src = MEDIAN_SCENE_IMAGE_THREE; 
	//this.medianImage3.addEventListener("load", drawImage); 
	this.x = 0;
	this.y = 275;
	this.left = this.x;
	this.right = (this.x + this.medianImage.width);
	this.top = this.y;
	this.bottom = (this.y + this.medianImage.height);
	this.isCop = false;
}

//This is a struct that creates the bottom of the scene.
function BottomScene()
{
	this.bottomImage = new Image();  
	this.bottomImage.src = BOTTOM_SCENE_IMAGE_ONE; 
	//this.bottomImage.addEventListener("load", drawImage); 
	this.bottomImage2 = new Image(); 
	this.bottomImage2.src = BOTTOM_SCENE_IMAGE_TWO; 
	//this.bottomImage2.addEventListener("load", drawImage);
	this.bottomImage3 = new Image(); 
	this.bottomImage3.src = BOTTOM_SCENE_IMAGE_THREE; 
	//this.bottomImage3.addEventListener("load", drawImage);
	this.x = 0;
	this.y = 450;		
}

//Objects of the above struct types are created here.
var SceneTop = new TopScene();
var SceneMedian = new MedianScene();
var SceneBottom = new BottomScene();
var frogProbability = 0.75;
var carProbability = 0.5;
var copProbability = 0;
var carSpeed = 7.5;

//in objectArray, 0 = player, 1 = frog, 2 = cars
//These lines initialize the array and its subarrays:
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

//Image initialization
semiLeft = new Image();  
semiLeft.src = "images/leftsemi1.jpg"; 
//semiLeft.addEventListener("load", drawImage);
carLeft = new Image();  
carLeft.src = "images/leftcar1.jpg"; 
//carLeft.addEventListener("load", drawImage);
carRight1 = new Image();  
carRight1.src = "images/rightcar2.jpg"; 
//carRight1.addEventListener("load", drawImage);
carRight0 = new Image();  
carRight0.src = "images/rightcar5.jpg"; 
//carRight0.addEventListener("load", drawImage);
copRight = new Image();
copRight.src = "images/copRight.jpg" ;
//copRight.addEventListener("load", drawImage);
copRightRed = new Image();
copRightRed.src = "images/copRightRed.jpg" ;
//copRightRed.addEventListener("load", drawImage);
copRightBlue = new Image();
copRightBlue.src = "images/copRightBlue.jpg" ;
//copRightBlue.addEventListener("load", drawImage);

gameStatusInterval();

//Variables that are used globally, scrollSpeed changes the speed of the scenery scrolling.	
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



//Variable initializations for initial game conditions.
objectArray[0][0].score = 0;
objectArray[0][0].lives = 3;

for(i = 0; i < frogProbability; i++)
{
	var yNum = Math.random()*430;
	if(yNum < 150)
	{
		yNum += 160; 
	}
	if((yNum > 270)&&(yNum < 350))
	{
		yNum += 80;
	}

	objectArray[1][i].x = (Math.random()* 640) + Math.random()*100;
	objectArray[1][i].y = yNum;
}

//this function moves cars to the top of their row in the array, and randomly creates a car
function carManager() 
{
	var lengthDown = 0;
	//removes cars outside the map from the array, and consolidates cars in their array
	for (var i = 0; i < objectArray[2].length; i++) 
	{
		if (i != objectArray[2].length - 1) 
		{
			if (objectArray[2][i].x < -100 || objectArray[2][i].x > 640) 
			{
				objectArray[2][i] = objectArray[2][i+1];
				objectArray[2][i+1] = 0;
				lengthDown++;		
			}
			else if ((objectArray[2][i] == 0) && i != objectArray[2].length - 1) 
			{
				objectArray[2][i] = objectArray[2][i+1];
				objectArray[2][i+1] = 0;	
			}
		}
		else if (objectArray[2][i].x < -100 || objectArray[2][i].x > 640) 
		{
			lengthDown++;
		}
	}
	objectArray[2].length = objectArray[2].length - lengthDown;
	//randomly creates cars using carCount variable to keep them regularly spaced
	if (carCount > 0) 
	{
		carCount--;
	}
	else if (Math.random() * 100 <= carProbability && carCount == 0) 
	{
		var carType = Math.random() * 100;

		if (carType < 20) 
		{
			var currentCarIndex = objectArray[2].length;
			objectArray[2][currentCarIndex] = new Cars();
			objectArray[2][currentCarIndex].direction = -1;
			objectArray[2][currentCarIndex].speed = carSpeed;
			objectArray[2][currentCarIndex].x = 640;
			objectArray[2][currentCarIndex].y = 160;

			if (Math.random() * 100 < 50) 
			{
				objectArray[2][currentCarIndex].image = carLeft;
			}
			else 
			{
				objectArray[2][currentCarIndex].image = semiLeft;
			}
		}
		else if (carType >= 20 && carType < 40) 
		{
			var currentCarIndex = objectArray[2].length;
			objectArray[2][currentCarIndex] = new Cars();
			objectArray[2][currentCarIndex].direction = -1;
			objectArray[2][currentCarIndex].speed = carSpeed;
			objectArray[2][currentCarIndex].x = 640;
			objectArray[2][currentCarIndex].y = 220;
			if (Math.random() * 100 < 50) 
			{
				objectArray[2][currentCarIndex].image = carLeft;
			}
			else 
			{
				objectArray[2][currentCarIndex].image = semiLeft;
			}
		}
		else if (carType >= 40 && carType < 60) 
		{
			var currentCarIndex = objectArray[2].length;
			objectArray[2][currentCarIndex] = new Cars();
			objectArray[2][currentCarIndex].direction = 1;
			objectArray[2][currentCarIndex].speed = carSpeed;
			objectArray[2][currentCarIndex].x = -100;
			objectArray[2][currentCarIndex].y = 400;
			
			if (Math.random() * 100 < 50) 
			{
				objectArray[2][currentCarIndex].image = carRight0;
			}
			else 
			{
				objectArray[2][currentCarIndex].image = carRight1;
			}
		} 
		else if (carType >= 60 && carType < 80) 
		{
			var currentCarIndex = objectArray[2].length;
			objectArray[2][currentCarIndex] = new Cars();
			objectArray[2][currentCarIndex].direction = 1;
			objectArray[2][currentCarIndex].speed = carSpeed;
			objectArray[2][currentCarIndex].x = -100;
			objectArray[2][currentCarIndex].y = 340;

			if (Math.random() * 100 < 50) 
			{
				objectArray[2][currentCarIndex].image = carRight0;
			}
			else {
				objectArray[2][currentCarIndex].image = carRight1;
			}
		}
		else if (carType >= 80) 
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

function copImageChanger()
{
	setTimeout(copRed, 300);
	setTimeout(wait, 100);
	setTimeout(copBlue, 400);
}

function wait()
{
	//console.log("Waiting");
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
			objectArray[0][0].x = 320 - (objectArray[0][0].playerImage.width/1);
			objectArray[0][0].y = 410;
			SceneTop.x = 0;
			SceneMedian.x = 0;
			SceneBottom.x = 0;

			for(i = 0; i < objectArray[1].length; i++)
			{
				objectArray[1][i].x = (Math.random()*640 + 700);
			}
		}
	}
	if (e.keyCode == ESCAPE && pause) 
	{
		pause = false;
	}
	else if (e.keyCode == ESCAPE && !pause && gameOn) 
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
	if(e.keyCode == LEFT)
	{
		horizontal = 0;
	}
	if(e.keyCode == RIGHT)
	{
		horizontal = 0;
	}
	if(e.keyCode == UP)
	{
		vertical = 0;
	}
	if(e.keyCode == DOWN)
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
	if(objectArray[0][0].y >= 410)
	{
		objectArray[0][0].y = 410;
	}
	if(objectArray[0][0].y <= 150)
	{
		objectArray[0][0].y = 150;
	}
}


//Function that scrolls the top, median and bottom structs that make up the scene.
function scroll()
{
	SceneTop.x -=  scrollSpeed * dt;
	if(SceneTop.x < -(SceneTop.topImage.width - 640))
	{
		SceneTop.x = 0;
	}

	SceneMedian.x -=  scrollSpeed * dt;
	if(SceneMedian.x < -(SceneMedian.medianImage.width + 300))
	{
		SceneMedian.x = 640;
	}

	SceneBottom.x -=  scrollSpeed * dt;
	if(SceneBottom.x < -(SceneBottom.bottomImage.width - 640))
	{
		SceneBottom.x = 0;
	}	
}


//Frog functions:

//Makes frogs
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

	if((num >= 0)&&(num < 50))
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
	frogPosition(Frog);
	var num = (Math.random() * 100);

	if(num > 10 && num < 20 && Frog.alive)
	{	
		Frog.y -= 4;
	}
}

//Checks to see if the Frog struct bool is alive is true, if so the above function drawFrog
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
	yNum = Math.random()*430;

	if(yNum < 150)
	{
		yNum += 160; 
	}
	if((yNum > 270)&&(yNum < 340))
	{
		yNum += 80;
	}		
	if(Frog.x < -100)
	{
		Frog.y = yNum;
		Frog.x = Math.random()*100 + 900;
		Frog.alive = true;
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
	if(!Frog.alive)
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

		ctx.fillStyle = BLACK;
		ctx.fillRect(0, 0, 640, 480);

		if(level == 1)
		{
			// ctx.fillStyle = BLACK;
			// ctx.fillRect(0, 0, 640, 480);
			ctx.drawImage(level1Image, 0, 0);
		}	
		if(level == 2)
		{
			// ctx.fillStyle = BLACK;
			// ctx.fillRect(0, 0, 640, 480);
			ctx.drawImage(level2Image, 0, 0);
		}
		if(level == 3)
		{
			// ctx.fillStyle = BLACK;
			// ctx.fillRect(0, 0, 640, 480);
			ctx.drawImage(level3Image, 0, 0);
		}

		setTimeout(waitMenu, 3000);
}

function pauseMenu()
{
	$(document).keydown(function(e) 
	{
		if(e.keyCode == UP && !keyPressed)
		{
			pauseSelection--;
			keyPressed = true;
		}
		if(e.keyCode == DOWN && !keyPressed)
		{
			pauseSelection++;
			keyPressed = true;
		}
		if(e.keyCode == ENTER && !keyPressed)
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
		if(e.keyCode == addEventListener)
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
	ctx.fillRect(0, 0, 640, 480);
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
	if(pauseSelection == 1)
	{
		if(soundOn)
		{
			if(!soundKey)
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
			if(!soundKey)
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
	if(pauseSelection == 2)
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
		objectArray[0][0].y = 410;
		SceneTop.x = 0;
		SceneMedian.x = 0;
		SceneBottom.x = 0;
		objectArray[2] = [];
		objectArray[1] = [];
		
		for(i = 0; i < objectArray[1].length; i++)
		{
			objectArray[1][i].x = (Math.random()*640 + 700);
		}
	}
	else if((objectArray[0][0].score >= 30) && (level == 2))
	{
		level = 3;
		levelMenu();
		scrollSpeed = 0.7;
		objectArray[0][0].x = 20;
		objectArray[0][0].y = 410;
		SceneTop.x = 0;
		SceneMedian.x = 0;
		SceneBottom.x = 0;
		objectArray[2] = [];
		objectArray[1] = [];
		
		for(i = 0; i < objectArray[1].length; i++)
		{
			objectArray[1][i].x = (Math.random()*640 + 700);
		}
	}
	else if((objectArray[0][0].score >= 100) && (level == 3))
	{
		if(soundOn)
		{
			musicWin.play();
		}

		ctx.fillStyle = BLACK;
		ctx.fillRect(0, 0, 640, 480);
		ctx.drawImage(winImage, 0, 0);
		gameOn = false;
	}
}


//Function that takes in a struct and sets its top, bottom, left and right variables to their
//x and y values to check for collisions.
function positionUpdate(struct, width, height)
{
	struct.left = struct.x;
	struct.right = (struct.x + width);
	struct.top = struct.y;
	struct.bottom = (struct.y + height);
	
	if(struct.isCop)
	{
		struct.top += 30;
		struct.bottom += 30;
		struct.left += 30;
		struct.right += 30;
	}
}

//Function that takes in two structs and checks to see if there is overlap, this function as well as
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
  	setInterval(gameStatus, 100/3.0); 
	
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
	ctx.fillRect(0, 0, 640, 480);
	ctx.drawImage(loseImage,0,0);
	gameOn = false;
}


levelMenu();

//Update function.
function update()
{ 
	if(!pause) 
	{
		ctx.fillStyle = BLACK;
		ctx.fillRect(0, 0, 640, 480);
	   
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

			if(soundOn)
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
		copImageChanger();
	}
	if(pause) 
	{
		pauseMenu();
	}
}
