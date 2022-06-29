#pragma once
#include "Vertex.h"


class Cube
{
public:
	Vertex vertices[24] = {

		// Cube

	  //front
	  Vertex(-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 0.0f),
	  Vertex(0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f),
	  Vertex(0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f),
	  Vertex(-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f, 1.0f),
	  //right 
	  Vertex(0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 0.0f),
	  Vertex(0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f),
	  Vertex(0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 1.0f, 1.0f),
	  Vertex(0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f),
	  //top
	  Vertex(-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f),
	  Vertex(0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f),
	  Vertex(0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f),
	  Vertex(-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f),
	  //bottom
	  Vertex(-0.5f, -0.5f, -0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 1.0f),
	  Vertex(0.5f, -0.5f, -0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 1.0f),
	  Vertex(0.5f, -0.5f, 0.5f, 0.0f, -0.5f, 0.0f, 1.0f, 0.0f),
	  Vertex(-0.5f, -0.5f, 0.5f, 0.0f, -0.5f, 0.0f, 0.0f, 0.0f),
	  //back
	  Vertex(-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 0.0f),
	  Vertex(0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 0.5f, 1.0f, 0.0f),
	  Vertex(0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.5f, 1.0f, 1.0f),
	  Vertex(-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 0.5f, 0.0f, 1.0f),
	  //left
	  Vertex(-0.5f, 0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 0.0f),
	  Vertex(-0.5f, 0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f),
	  Vertex(-0.5f, -0.5f, -0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 1.0f),
	  Vertex(-0.5f, -0.5f, 0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f)

	};

	USHORT indices[36] = {

		0,1,2,
		0,2,3,

		4,5,6,
		4,6,7,

		8,9,10,
		8,10,11,

		12,13,14,
		12,14,15,

		16,17,18,
		16,18,19,

		20,21,22,
		20,22,23
	};

};

class Tetrahedron {
public:
	
	Vertex vertices[12] = {

	Vertex(-0.5f, 0.0f, -0.5f, 0.0f, 1.0f, -1.0f, 0.0f, 0.0f),    // side 1		frontface
	Vertex(0.0f, 0.5f, 0.0f, 0.0f, 1.0f, -1.0f, 0.5f, 0.5f),
	Vertex(0.5f, 0.0f, -0.5f, 0.0f, 1.0f, -1.0f, 1.0f, 0.0f),


	Vertex(0.5f, 0.0f, -0.5f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f),    // side 2		  rightface
	Vertex(0.0f, 0.5f, 0.0f, 1.0f, 1.0f, 1.0f, 0.5f, 0.5f),
	Vertex(0.0f, 0.0f, 0.75f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f),


	Vertex(0.0f, 0.0f, 0.75f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f),    // side 3		   leftface
	Vertex(0.0f, 0.5f, 0.0f, -1.0f, 1.0f, 1.0f, 0.5f, 0.5f),
	Vertex(-0.5f, 0.0f, -0.5f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f),


	Vertex(0.5f, 0.0f, -0.5f, 0.0f, -1.0f, 0.0f, 0.0f, 0.0f),    // side 4		  bottomface
	Vertex(0.0f, 0.0f, 0.75f, 0.0f, -1.0f, 0.0f, 0.5f, 0.5f),
	Vertex(-0.5, 0.0f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 0.0f)

	};

	USHORT indices[12] = {

		 0, 1, 2,
		3 ,4, 5,
		6, 7, 8,
		9, 10, 11,
	};

 };

class PentagonalPrism  {

public:
	Vertex vertices[32] = {


		// Front Penta
		Vertex(-0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f, -0.5f, -0.5f),
		Vertex(-1.0f, 1.0f, -0.5f,  0.0f, 0.0f, -1.0f, -1.0f, 1.0f),
		Vertex(0.0f, 2.0f, -0.5f,  0.0f, 0.0f, -1.0f, 0.0f, 2.0f),
		Vertex(1.0f, 1.0f, -0.5f,  0.0f, 0.0f, -1.0f, 1.0f, 1.0f),
		Vertex(0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f, 0.5f, -0.5f),
		Vertex(0.0f, 0.0f, -0.5f, 0.0f, 0.0f, -1.0f, 0.0f,0.0f),



		 // Back Penta
		Vertex(-0.5f, -0.5f, 1.5f, 0.0f, 0.0f, 1.0f, -0.5f, -0.5f),
		Vertex(-1.0f, 1.0f,  1.5f,0.0f, 0.0f, 1.0f, -1.0f, 1.0f),
		Vertex(0.0f, 2.0f,  1.5f, 0.0f, 0.0f, 1.0f, 0.0f, 2.0f),
		Vertex(1.0f, 1.0f,  1.5f, 0.0f, 0.0f, 1.0f, 1.0f, 1.0f),
		Vertex(0.5f, -0.5f,  1.5f, 0.0f, 0.0f, 1.0f, 0.5f, -0.5f),
		Vertex(0.0f, 0.0f,  1.5f, 0.0f, 0.0f, 1.0f, 0.0f,0.0f),



	
	// Left
	Vertex(-0.5f, -0.5f, -0.5f, -1.0f, -1.0f, 0.0f, 0.0f, 0.0f),
	Vertex(-1.0f, 1.0f, -0.5f, -1.0f, -1.0f, 0.0f, 2.0f,0.0f),
	Vertex(-0.5f, -0.5f,  1.5f, -1.0f, -1.0f, 0.0f, 2.0f, 2.0f),
	Vertex(-1.0f, 1.0f,  1.5f, -1.0f, -1.0f, 0.0f, 0.0f, 2.0f),

	// Leftabove
	Vertex(-1.0f, 1.0f, -0.5f, -1.0f, 1.0f, 0.0f, -1.0f, 1.0f),
	Vertex(0.0f, 2.0f, -0.5f,-1.0f, 1.0f, 0.0f, 0.0f, 2.0f),
	Vertex(-1.0f, 1.0f,  1.5f, -1.0f, 1.0f, 0.0f, -1.0f, 1.0f),
	Vertex(0.0f, 2.0f,  1.5f, -1.0f, 1.0f, 0.0f, 0.0f, 2.0f),



	 // Rightabove

	Vertex(0.0f, 2.0f, -0.5f, 1.0f, 1.0f, 0.0f, 0.0f, 2.0f),
	Vertex(1.0f, 1.0f, -0.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f),
	Vertex(0.0f, 2.0f,  1.5f, 1.0f, 1.0f, 0.0f, 0.0f, 2.0f),
	Vertex(1.0f, 1.0f,  1.5f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f),

	 // Right
	Vertex(1.0f, 1.0f, -0.5f, 1.0f, -1.0f, 0.0f, 1.0f, 1.0f),
	Vertex(0.5f, -0.5f, -0.5f,  1.0f, -1.0f, 0.0f, 0.5f, -0.5f),
	Vertex(1.0f, 1.0f,  1.5f,  1.0f, -1.0f, 0.0f, 1.0f, 1.0f),
	Vertex(0.5f, -0.5f,  1.5f,  1.0f, -1.0f, 0.0f, 0.5f, -0.5f),


	 // Bottom
	Vertex(-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, -0.5f, -0.5f),
	Vertex(0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 0.5f, -0.5f),
	Vertex(-0.5f, -0.5f, 1.5f, 0.0f, -1.0f, 0.0f, -0.5f, -0.5f),
	Vertex(0.5f, -0.5f,  1.5f, 0.0f, -1.0f, 0.0f, 0.5f, -0.5f)
		

	};

	USHORT indices[60] = {
	  	

		

	  	 // Front
		0,1,5,
		1,2,5,
		2,3,5,
		3,4,5,
		0,5,4,

	 // Back		   
		6,7,11,
		7,8,11,
		8,9,11,
		9,10,11,
		 6,11,10,

	////Left
	0,7,1,
	0,6,7,


	////Leftabove
	2,1,7,
	8,2,7,		


	// Rightabove
	3,2,8,
	9,3,8,

	// Right
	4,3,9,
	10,4,9,

	//// Bottom
	0,4,6,
	10,6,4


	};					
};