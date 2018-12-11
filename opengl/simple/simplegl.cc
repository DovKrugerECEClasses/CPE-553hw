#include "simplegl.hh"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

bool GLWin::initialized;

void GLWin::classInit() {
	// initialize once for all the libraries called
	if( !glfwInit() )
		throw "Failed to initialize GLFW";
	// Initialize GLEW
	glewExperimental = true; // Needed for core profile
}

void GLWin::init() {
	glEnable(GL_DEPTH_TEST);
	// Accept fragment if it closer to the camera than the former one
	glDepthFunc(GL_LESS); 
	
	GLuint VertexArrayID;
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
	setup();
	project4to3();
}

void GLWin::project4to3() {	
	// Get a handle for our "MVP" uniform
	matrixID = glGetUniformLocation(programID, "MVP");
	// Projection matrix : 45° Field of View, 4:3 ratio, display range : 0.1 unit <-> 100 units
	mat4 projection = perspective(radians(45.0f), 4.0f / 3.0f, 0.1f, 100.0f);
	// Camera matrix
	mat4 view =
		lookAt(vec3(4,3,3), // Camera is at (4,3,3), in World Space
					 vec3(0,0,0), // and looks at the origin
					 vec3(0,1,0)  // Head is up (set to 0,-1,0 to look upside-down)
					 );
	// Model matrix : an identity matrix (model will be at the origin)
	mat4 model = mat4(1.0f);
	// Our ModelViewProjection : multiplication of 3 matrices
	mat4 MVP = projection * view * model;
	// Remember, this is reversed from the order in which it occurs.
}

void GLWin::waitLoop() {
	do {
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	// Clear the window
		glUseProgram(programID); // use the shader compiled before
		// Send the transformation to the currently bound shader in the "MVP" uniform
		glUniformMatrix4fv(matrixID, 1, GL_FALSE, &MVP[0][0]);

		//		draw();
		glfwSwapBuffers(win);		// double buffering: draw to the one offscreen
		glfwPollEvents();           // wait for events after each redraw
	}	while( glfwGetKey(win, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
					 glfwWindowShouldClose(win) == 0 );
}

GLWin::GLWin(int w, int h, const char title[],
						 const char vertexShader[], const char fragShader[],
						 const Color& bg) : bg(bg)  {
	if (!initialized) {
		classInit();
	}
	glfwWindowHint(GLFW_SAMPLES, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	
	// To make MacOS happy; should not be needed
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	// Open a window and create its OpenGL context
	win = glfwCreateWindow(w, h, title, nullptr, nullptr);
	if( win == nullptr ) {
		glfwTerminate();
		throw "Failed to open GLFW window";
	}
	glfwMakeContextCurrent(win);
	if (glewInit() != GLEW_OK)
		throw "Failed to initialize GLEW";

	// Ensure we can capture the escape key being pressed below
	glfwSetInputMode(win, GLFW_STICKY_KEYS, GL_TRUE);
	
	// Dark blue background
	glClearColor(bg.r, bg.g, bg.b, 0.0f);
	// Create and compile our GLSL program from the shaders
	programID = loadShaders( vertexShader, fragShader);
	init();
}

GLWin::~GLWin() {
	// Cleanup VBO and shader
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &uvbuffer);
	glDeleteProgram(programID);
	glDeleteTextures(1, &texture);
	glDeleteVertexArrays(1, &vertexArrayID);
		
	// Close OpenGL window and terminate GLFW
	glfwTerminate();
}

/*
 * Create, read in and compile a single shader
 */
GLuint GLWin::readShader(const char filename[], GLuint shaderType) {
	ifstream s(filename, std::ios::in);
	if(!s.is_open()){
		throw "Failed to read shader";
	}

	stringstream sstr;
	sstr << s.rdbuf();
	string code = sstr.str();
	s.close();
	const char* codeptr = code.c_str();
	GLuint shaderID = glCreateShader(shaderType);
	glShaderSource(shaderID, 1, &codeptr, nullptr);
	glCompileShader(shaderID);

	GLint result = GL_FALSE;
	int infoLogLength;

	// Check shader compile results
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &result);
	glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if ( infoLogLength > 0 ){
		vector<char> shaderErrorMsg(infoLogLength+1);
		glGetShaderInfoLog(shaderID, infoLogLength, nullptr, &shaderErrorMsg[0]);
		throw &shaderErrorMsg[0];
	}
	return shaderID;
}


GLuint GLWin::loadShaders(const char vertexShaderPath[],
													const char fragmentShaderPath[]) {

	GLuint vertexShaderID = readShader(vertexShaderPath, GL_VERTEX_SHADER);
	GLuint fragmentShaderID = readShader(fragmentShaderPath, GL_FRAGMENT_SHADER);

	//	log(LINKING_PROGRAM);

	GLuint programID = glCreateProgram();
	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	// Check the program
	GLint result;
	GLint infoLogLength;
	glGetProgramiv(programID, GL_LINK_STATUS, &result);
	glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
	if ( infoLogLength > 0 ){
		vector<char> programErrorMessage(infoLogLength+1);
		glGetProgramInfoLog(programID, infoLogLength, nullptr, &programErrorMessage[0]);
		throw &programErrorMessage[0];
	}

	glDetachShader(programID, vertexShaderID);
	glDetachShader(programID, fragmentShaderID);
	
	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);
	return programID;
}
