var demoCanvas = document.getElementById("mapCanvas"); 
var gameWindow = demoCanvas.getContext("2d");
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
	//mapText = mapText.toString()
	console.log(mapText);

	//alert(mapText);
	writeMap(mapText);
   	writeMapToScreen(map);
}

function writeMap(inputText)
{
	// map = inputText;
	var i , j;
	//alert("hello")

	// console.log(inputText.length);
	//console.log(inputText);
	//console.log(map.join(''));

	var file = fopen("output", 3);
	fwrite(file, "hello");
	fclose(file);

	for(i = 0; i < 16; i++)
	{

		for(j = 0; j < 17; j++)
		{

			// alert(inputText[(i * 17) + j]);
			// map[i][j] = inputText[(i * 17) + j];
			// console.log(map[i][j] + " : " + input[(i * 17) + j]); 
		}	
	}
}


function writeMapToScreen()
{

	//alert(map);
	var i , j;
	var stringValue = "";
	var tempString;

	for(i = 0; i < 16; i++)
	{
		tempString = "";
		for(j = 0; j < 17; j++)
		{
			tempString += (map[i][j]);
		}	
		stringValue += tempString;
	}

	document.getElementById("textArea1").innerText = stringValue;
}

for(i = 0; i < 16; i++)
{
	rows[i] = '.';
}
rows[i] = '\n';

for(i = 0; i < 16; i++)
{
	map[i] = rows;
}

writeMapToScreen();



gameWindow.fillStyle = "#801000";
gameWindow.fillRect(0, 0, 1000, 400);






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