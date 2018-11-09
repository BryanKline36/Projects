var demoCanvas = document.getElementById("mapCanvas"); 
var gameWindow = demoCanvas.getContext("2d");


function gameStatusInterval()	
{ 
  	setInterval(updateOne, 40); 
}

function updateOne()
{
	gameWindow.fillStyle = "#801000";
	gameWindow.fillRect(0, 0, 1000, 400);
}


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




var i;
var rows = [];
var map = [];

for(i = 0; i < 16; i++)
{
	rows[i] = '.';
}
rows[i] = '\n';

for(i = 0; i < 16; i++)
{
	map[i] = rows;
}

var j;
var stringValue = "";
var tempString;

for(i = 0; i < 16; i++)
{
	tempString = "";
	for(j = 0; j < 17; j++)
	{
		// stringValue += data[i].join('');

		tempString += ("___" + map[i][j]);
	}	
	stringValue += tempString;
}


document.getElementById("textArea1").innerText = stringValue;

gameStatusInterval();
