var demoCanvas = document.getElementById("mapCanvas"); 
var gameWindow = demoCanvas.getContext("2d");

var COLUMN_SIZE = 16;
var STEP_SIZE = 32;

var map = [];
var imageList = [];
var labelList = [];
var input = document.getElementById("myFile");
var output = document.getElementById("output");

document.getElementById("savebtn").addEventListener("click", saveTheFile);
document.getElementById("load").addEventListener("click", drawImage);
input.addEventListener("change", readInput);

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
	if(this.files && this.files[0]) 
	{
		var myFile = this.files[0];
		var reader = new FileReader();
		
		reader.addEventListener('load', 
			function(parameter) 
			{
				output.textContent = parameter.target.result;
			});
		
		reader.readAsBinaryString(myFile);
	}   
}

function readMap()
{
	var i, size;
	var tempString = "";

	map = document.getElementById("output").value
	size = map.length;
	
	for(i = 0; i < size; i++)
	{
		if(map[i] != '\n')
		{
			tempString += map[i];
		}
	}
	
	map = tempString;
}

function drawImage()
{
	var i, size;
	var xPosition = 0, yPosition = 0;
	var tempImage = new Image();
	
	readMap();

	labelList = Array.from(new Set(map.split('')));
	size = map.length;

	loadImages();
	
	for(i = 0; i < size; i++)
	{
		if(i != 0 && i % COLUMN_SIZE == 0)
		{
			xPosition = 0;
			yPosition += STEP_SIZE;
		}
		
		tempImage = getImage(i);
		

		gameWindow.drawImage(tempImage, xPosition, yPosition);

		xPosition += STEP_SIZE;
	}
}

function getImage(index)
{
	var charTile = map[index];
	
	index = labelList.indexOf(charTile);

	return imageList[index];
}


var textFile = null,
makeTextFile = function (text) 
	{
		var data = new Blob([text], {type: 'text/plain'});

		// If we are replacing a previously generated file we need to
		// manually revoke the object URL to avoid memory leaks.
		if (textFile !== null) 
		{
			window.URL.revokeObjectURL(textFile);
		}

		textFile = window.URL.createObjectURL(data);

		return textFile;
	};


var create = document.getElementById('create'),
textbox = document.getElementById('textbox');

create.addEventListener('click', function () {
var link = document.createElement('a');
link.setAttribute('download', 'info.txt');
link.href = makeTextFile(textbox.value);
document.body.appendChild(link);

// wait for the link to be added to the document
window.requestAnimationFrame(function () {
	var event = new MouseEvent('click');
	link.dispatchEvent(event);
	document.body.removeChild(link);
	});

}, false);
