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

function drawMap(map)
{
	var x = 0;
	var y = 0;

	// for(i = 0; i < 272; i++)
	// {
	// 	map[i] = '.';

	// 	if(i != 0 && i % 16 == 0)
	// 	{
	// 		map[i] = '\n';
	// 	}
	// }

	//gameWindow.drawImage("w.png", x, y);

}
	
function readMap()
{
	var mapText = document.getElementById("output").value
	//mapText = mapText.toString()
	// console.log(mapText);

	//alert(mapText);
	// writeMap(mapText);
	// alert("going");
	map = mapText;

	//writeMapToScreen(map);
	drawMap(map);   
}


function writeMap(inputText)
{
	// map = inputText;
	var i , j;
	//alert("hello")

	console.log(inputText.length);
	console.log(inputText);
	//console.log(map.join(''));


	for(i = 0; i < 16; i++)
	{
		for(j = 0; j < 17; j++)
		{
			//console.log("position (1)" + i + "-" + j + ":  " + map[i][j] + "  end");


			map[i][j] = inputText[(i * 17) + j];
			console.log("position (2)" + i + "-" + j + ":  " + map[i][j] + "  end");
			//console.log("position " + i + "-" + j + ":  " + inputText[(i * 17) + j] + "  end");
			// console.log(map[i][j] + " : " + input[(i * 17) + j]); 
		}	
	}

	for(i = 0; i < 16; i++)
	{
		for(j = 0; j < 17; j++)
		{

			// map[i][j] = inputText[(i * 17) + j];
			console.log("position (new) " + i + "-" + j + ":  " + map[i][j] + "  end");
			//console.log("position " + i + "-" + j + ":  " + inputText[(i * 17) + j] + "  end");
			// console.log(map[i][j] + " : " + input[(i * 17) + j]); 
		}	
	}
}


function writeMapToScreen(map)
{


	var i , j;
	var stringValue = map;
	// var tempString = map;

	// for(i = 0; i < 17; i++)
	// {
	// 	tempString = "";
	// 	for(j = 0; j < 16; j++)
	// 	{
	// 		//console.log("position " + i + "-" + j + ":  " + map[i][j] + "  end");
	// 		tempString += (map[i][j]);
	// 	}	
	// 	stringValue += tempString;
	// }

	document.getElementById("textArea1").innerText = map;
}

// for(i = 0; i < 16; i++)
// {
// 	rows[i] = '.';
// }
// rows[i] = '\n';

for(i = 0; i < 272; i++)
{
	map[i] = '.';

	if(i != 0 && i % 16 == 0)
	{
		map[i] = '\n';
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

function drawImage()
{
    var i;
    var xPosition = 0, yPosition = 0;

    readMap()

    for(i = 0; i < 272; i++)
    {
        if(xPosition == 544)
        {
            xPosition = 0;
            yPosition += 32;
        }

        if(map[i] != '\n')
        {
            console.log("i:map[i]:xPosition:yPosition\t" + i + ":" + map[i] + ":" + xPosition + ":"+ yPosition);
            if(map[i] == 'g')
            {
                // alert("g")
                gameWindow.drawImage(grassImage, xPosition, yPosition);
            }
            else if(map[i] == 'w')
            {
                // alert("w")

                gameWindow.drawImage(waterImage, xPosition, yPosition);
            }

        }
        xPosition += 32;

    }

    // var baseImage = new Image();
    // baseImage.src = "g.png";

}

