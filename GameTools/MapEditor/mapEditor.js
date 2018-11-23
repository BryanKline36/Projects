var demoCanvas = document.getElementById("mapCanvas"); 
var gameWindow = demoCanvas.getContext("2d");

var i, j;
var rows = [];
var map = [];
var stringValue = "";
var input = document.getElementById("myFile");
var output = document.getElementById("output");
document.getElementById("load").addEventListener("click", drawImage);
input.addEventListener("change", readInput);



var imageList = [];
var labelList = ["w", "g"];
loadImages();

function loadImages()
{
	var labelSize = labelList.length;
	
	imageList = [];
	
	for(i = 0; i < labelSize; i++)
	{
		imageList[i] = new Image();
		imageList[i].src = labelList[i] + ".png";
	}


}


function readInput() 
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
}



function readMap()
{
	var i;
	var tempString = "";

	map = document.getElementById("output").value
	
	for(i = 0; i < 272; i++)
	{
		if(map[i] != '\n')
		{
			tempString += map[i];
		}
	}
	
	map = tempString;
}




function getUniqueTiles()
{
	//var size = labelList.length;

	//console.log(size);

	for(i = 0; i < 256; i++)
	{


		// if(!labelExists(map[i]))
		// {
		// 	labelList.push(map[i]);
		// }
	}

	console.log(labelList)
}

function labelExists(tileChar)
{
	for(i = 0; i < 256; i++)
	{
		if(map[i] == tileChar)
		{
			return true;
		}
	}

	return false;
}

function drawImage()
{
	var i;
	var xPosition = 0, yPosition = 0;
	
	readMap();
	//getUniqueTiles();
	loadImages();
	
	for(i = 0; i < 256; i++)
	{
		if(i != 0 && i % 16 == 0)
		{
			xPosition = 0;
			yPosition += 32;
		}
		
		if(map[i] == labelList[0])
		{
			gameWindow.drawImage(imageList[0], xPosition, yPosition);
		}
		else if(map[i] == labelList[1])
		{
			gameWindow.drawImage(imageList[1], xPosition, yPosition);
		}
		
		xPosition += 32;
	}
}


