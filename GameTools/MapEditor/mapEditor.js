var demoCanvas = document.getElementById("mapCanvas"); 
var gameWindow = demoCanvas.getContext("2d");
var grassImage = new Image();
grassImage.src = "g.png";
var waterImage = new Image();
waterImage.src = "w.png";
document.getElementById("load").addEventListener("click", drawImage);
var i, j;
var rows = [];
var map = [];
var stringValue = "";
var input = document.getElementById("myFile");
var output = document.getElementById("output");

input.addEventListener("change", 
	function() 
	{
  		if (this.files && this.files[0]) 
  		{
    		var myFile = this.files[0];
    		var reader = new FileReader();
    
    		reader.addEventListener('load', 
    			function(e) 
    			{
      				output.textContent = e.target.result;
    			});
    
    		reader.readAsBinaryString(myFile);
  		}   
	});


	
function readMap()
{
	var mapText = document.getElementById("output").value
	
	map = mapText;
	formatMapString();
}

function formatMapString()
{
	var i , j;
	var tempString = "";
	
	console.log(map);

	for(i = 0; i < 272; i++)
	{
		if(map[i] != '\n')
		{
			tempString += map[i];
		}
	}

	map = tempString;

	console.log(map);

}

function writeMapToScreen(map)
{
	document.getElementById("textArea1").innerText = map;
}

function drawImage()
{
	var i;

	readMap()

	for(i = 0; i < 256; i++)
	{
		if(map[i] == 'g')
		{
			gameWindow.drawImage(grassImage, xPosition, yPosition);
		}
		else if(map[i] == 'w')
		{
			gameWindow.drawImage(waterImage, xPosition, yPosition);
		}
	}
}


















// writeMapToScreen(map.join(""));



// gameWindow.fillStyle = "#801000";
// gameWindow.fillRect(0, 0, 1000, 400);

// gameWindow.fillStyle = "#000000";
// gameWindow.fillRect(0, 0, 40, 40);

// var things = new Image(100, 100);
// things.src = "images/w.png";
// gameWindow.drawImage(things, 0, 0);


// var imageObject = new Image();
// imageObject.src = "images/w.png";
// gameWindow.drawImage(imageObject, 0, 0);




// function gameStatusInterval()	
// { 
//   	setInterval(update, 40); 
// }

// function update()
// {
// 	gameWindow.fillStyle = "#801000";
// 	gameWindow.fillRect(0, 0, 1000, 400);
// }

// gameStatusInterval();

// $(document).keyup(function(key) 
// {
// 	if(key.keyCode == 37)
// 	{
// 		settings.canvasOne.x_speed = 2;
// 		LEFT = false;
// 	}
// 	else if(key.keyCode == 39)	
// 	{	
// 		settings.canvasOne.x_speed = 2;
// 		RIGHT = false;
// 	}
// 	else if(key.keyCode == 38)
// 	{
// 		settings.canvasOne.y_speed = 2;
// 		UP = false;
// 	}
// 	else if(key.keyCode == 40)
// 	{
// 		settings.canvasOne.y_speed = 2;
// 		DOWN = false;
// 	}
// });

// function changeSettings(input)
// {
// 	var xmlhttp = new XMLHttpRequest();

// 	xmlhttp.onreadystatechange = function() 
// 	{
// 		if(this.readyState == 4 && this.status == 200) 
// 		{
// 			settings = JSON.parse(this.responseText);
// 		}
// 	};

// 	if(input == 0)
// 	{	
// 		var file = "defaultSettings.JSON";
// 	}
// 	else if(input == 1)
// 	{
// 		var file = "altSettings.JSON";
// 	}

// 	xmlhttp.open("GET", file, true);
// 	xmlhttp.send();
// }
// function openfileDialog() {
//     $("#fileLoader").click();
// }


// var map = document.getElementById("mapCanvas");
// var ctx = map.getContext("2d");


// var baseImage = new Image();
// baseImage.src = "g.png";
// baseImage.addEventListener("load", drawImage);


