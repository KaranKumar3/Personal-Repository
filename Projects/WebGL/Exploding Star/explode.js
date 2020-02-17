//
//CSE 470 HW 1 Explode!  
//
/*
Written by: Karan Kumar
Date: Feb 2019

Description: 
This program creates an exploding object that fades to the background color as it reaches the boundary of the window
*/

var canvas;
var gl;

//store the vertices
//Each triplet represents one triangle
var vertices = [];

//store a color for each vertex
var colors = [];

//HW470: control the explosion
//(Your variables here)
//var theta = 0.0;
//var thetaLoc;
var expo = 0.0;
var expoLoc;
var colorChange = 0.0;
var colorChangeLoc;

var KFTinit = 0.0;
var KFT = 0.0;
var KFTmax = 0.9;

//HW470: control the redraw rate
var delay = 10;

// =============== function init ======================
 
// When the page is loaded into the browser, start webgl stuff
window.onload = function init()
{
	// notice that gl-canvas is specified in the html code
    canvas = document.getElementById( "gl-canvas" );
    
	// gl is a canvas object
    gl = WebGLUtils.setupWebGL( canvas );
    if ( !gl ) { alert( "WebGL isn't available" ); }

	// Track progress of the program with print statement
    console.log("Opened canvas");
        
    //HW470:
    // Define  data for object 
	// See HW specs for number of vertices and parts required
	// Recommendation: each set of three points corresponds to a triangle.
	// DCH: I have used sval for scaling the object size if I am not
	// happy with my initial design. (Just an idea for you; no need to use.)
	//(During the explosion all geometry must remain in the window.)
    //
	var sval = 0.09;
    vertices = [
        // core
        vec2( -sval, 0.0 ),                 //0
        vec2( sval, 0.0 ),                  //1
        vec2( -sval, (2 * -sval)),          //2
        vec2( sval, (2 * -sval)),           //3
        // star point north
        vec2( -sval, 0.0 ),                 //4
        vec2( 0.0, (4 *sval) ),             //5
        vec2( sval, 0.0 ),                  //6
        // star point east
        vec2( sval, 0.0 ),                  //7
        vec2( sval, (2 * -sval)),           //8
        vec2( (5 * sval), -sval ),          //9
        // star point west
        vec2( -sval, 0.0 ),                 //10
        vec2( -sval, (2 * -sval)),          //11
        vec2( (5 * -sval), -sval ),         //12
        // star point south
        vec2( sval, (2 * -sval)),           //13
        vec2( 0.0, (6 * -sval) ),           //14
        vec2( -sval, (2 * -sval)),          //15
        // star edge point north west
        vec2( -sval, 0.0 ),                  //16
        vec2( (2 * -sval), (1.5 *sval) ),   //17
        vec2( -sval, (2 * -sval)),          //18
        // star edge point south west
        vec2( -sval, 0.0 ),                 //19
        vec2( (2 * -sval), (3 *-sval) ),    //20
        vec2( -sval, (2 * -sval)),          //21
        // star cross point north east bot
        vec2( sval, 0.0 ),                  //22
        vec2( (2 * sval), (1.5 * sval) ),   //23
        vec2( sval, (2 * -sval)),           //24
        // star edge point south east
        vec2( sval, 0.0 ),                  //25
        vec2( (2 * sval), (3 * -sval) ),    //26
        vec2( sval, (2 * -sval)),           //27
        // star cross point north east top
        vec2( sval, 0.0 ),                  //28
        vec2( (2.5 * sval), (1 * sval) ),   //29
        vec2( -sval, 0.0),                   //30
        // star cross point south west bot
        vec2( -sval, (2 * -sval)),          //31
        vec2( (2.5 * -sval), (2.7 * -sval) ),   //32
        vec2( sval, (2 * -sval))            //33
    ];
	 
	
	//HW470: Create colors for the core and outer parts
	// See HW specs for the number of colors needed
	for(var i=0; i < 4; i++) {
        colors.push(vec3(0.0, 1.0, 1.0)); //neon blue
	};
    for(var i=4; i < 7; i++) {
        colors.push(vec3(0.537, 0.812, 0.941)); //baby blue
    };
    for(var i=7; i < 10; i++) {
        colors.push(vec3(1.0, 0.0, 1.0)); //hot pink
    };
    for(var i=10; i < 13; i++) {
        colors.push(vec3(0.3, 0.5, 1.0)); //royal blue
    };
    for(var i=13; i < vertices.length; i++) {
        colors.push(vec3(0.7, 0.0, 0.7)); //purple
    };
    
	
	// HW470: Print the input vertices and colors to the console
	console.log("Input vertices and colors:");
	 
	 

    //  Configure WebGL
    gl.viewport( 0, 0, canvas.width, canvas.height );
	// Background color to white
    gl.clearColor( 1.0, 1.0, 1.0, 1.0 );

    //  Define shaders to use  
    var program = initShaders( gl, "vertex-shader", "fragment-shader" );
    gl.useProgram( program );

    // Load the data into the GPU
	//
	// color buffer: create, bind, and load
    var cBuffer = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, cBuffer );
    gl.bufferData( gl.ARRAY_BUFFER, flatten(colors), gl.STATIC_DRAW );
	
	// Associate shader variable for  r,g,b color
	var vColor = gl.getAttribLocation( program, "vColor" );
    gl.vertexAttribPointer( vColor, 3, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( vColor );
    
    // vertex buffer: create, bind, load
    var vbuffer = gl.createBuffer();
    gl.bindBuffer( gl.ARRAY_BUFFER, vbuffer );
    gl.bufferData( gl.ARRAY_BUFFER, flatten(vertices), gl.STATIC_DRAW );

    // Associate shader variables for x,y vertices	
    var vPosition = gl.getAttribLocation( program, "vPosition" );
    gl.vertexAttribPointer( vPosition, 2, gl.FLOAT, false, 0, 0 );
    gl.enableVertexAttribArray( vPosition );
	
	//HW470: associate shader explode variable ("Loc" variables defined here) 
    expoLoc = gl.getUniformLocation( program, "expo" );
    colorChangeLoc = gl.getUniformLocation( program, "colorChange" );

    console.log("Data loaded to GPU -- Now call render");

    render();
};
// =============== KFT Function ======================
function KFTcalc() {
    
    if (KFT > KFTmax){
        KFT = KFTinit;
    }
    else{
        KFT += 0.01;
    }
    
}

// =============== function render ======================

function render()
{
    // clear the screen 
    gl.clear( gl.COLOR_BUFFER_BIT );
	
	//HW470: send uniform(s) to vertex shader
    //some function that modifies the explosion
    KFTcalc();
    expo = KFT;
    colorChange = KFTmax;
    gl.uniform1f(colorChangeLoc, colorChange);
	//HW470: draw the object
	//You will need to change this to create the exploding outer parts effect
    //Core
    gl.uniform1f(expoLoc, 0.0);
    gl.drawArrays( gl.TRIANGLES, 0, 3 );
    gl.drawArrays( gl.TRIANGLES, 1, 3 );
        
	//Exploding Points
    gl.uniform1f(expoLoc, expo); //Start exploding here
              
    gl.drawArrays( gl.TRIANGLES, 4, 3 );
	gl.drawArrays( gl.TRIANGLES, 7, 3 );
	gl.drawArrays( gl.TRIANGLES, 10, 3 );
	gl.drawArrays( gl.TRIANGLES, 13, 3 );
    //gl.uniform1f(expoLoc, 0.0);
    gl.drawArrays( gl.TRIANGLES, 16, 3 );
    gl.drawArrays( gl.TRIANGLES, 19, 3 );
    gl.drawArrays( gl.TRIANGLES, 22, 3 );
    gl.drawArrays( gl.TRIANGLES, 25, 3 );
    gl.drawArrays( gl.TRIANGLES, 28, 3 );
    gl.drawArrays( gl.TRIANGLES, 31, 3 );
    
    //re-render after delay
	setTimeout(function (){requestAnimFrame(render);}, delay);
}

