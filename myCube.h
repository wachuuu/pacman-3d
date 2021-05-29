﻿#ifndef MYCUBE_H_INCLUDED
#define MYCUBE_H_INCLUDED

int myCubeVertexCount=36;

float myCubeVertices[]={
                //ściana 1
				1.0f,-1.0f,-1.0f,1.0f,
				-1.0f, 1.0f,-1.0f,1.0f,
				-1.0f,-1.0f,-1.0f,1.0f,

				1.0f,-1.0f,-1.0f,1.0f,
				1.0f, 1.0f,-1.0f,1.0f,
				-1.0f, 1.0f,-1.0f,1.0f,

                //ściana 2
				-1.0f,-1.0f, 1.0f,1.0f,
				1.0f, 1.0f, 1.0f,1.0f,
				1.0f,-1.0f, 1.0f,1.0f,

				-1.0f,-1.0f, 1.0f,1.0f,
				-1.0f, 1.0f, 1.0f,1.0f,
				1.0f, 1.0f, 1.0f,1.0f,


				//ściana 3
				-1.0f,-1.0f,-1.0f,1.0f,
				1.0f,-1.0f, 1.0f,1.0f,
				1.0f,-1.0f,-1.0f,1.0f,

				-1.0f,-1.0f,-1.0f,1.0f,
				-1.0f,-1.0f, 1.0f,1.0f,
				1.0f,-1.0f, 1.0f,1.0f,

				//ściana 4
				-1.0f, 1.0f, 1.0f,1.0f,
				1.0f, 1.0f,-1.0f,1.0f,
				1.0f, 1.0f, 1.0f,1.0f,

				-1.0f, 1.0f, 1.0f,1.0f,
				-1.0f, 1.0f,-1.0f,1.0f,
				1.0f, 1.0f,-1.0f,1.0f,

				//ściana 5
				-1.0f,-1.0f,-1.0f,1.0f,
				-1.0f, 1.0f, 1.0f,1.0f,
				-1.0f,-1.0f, 1.0f,1.0f,

				-1.0f,-1.0f,-1.0f,1.0f,
				-1.0f, 1.0f,-1.0f,1.0f,
				-1.0f, 1.0f, 1.0f,1.0f,

                //ściana 6
				1.0f,-1.0f, 1.0f,1.0f,
				1.0f, 1.0f,-1.0f,1.0f,
				1.0f,-1.0f,-1.0f,1.0f,

				1.0f,-1.0f, 1.0f,1.0f,
				1.0f, 1.0f, 1.0f,1.0f,
				1.0f, 1.0f,-1.0f,1.0f,




			};


float myCubeColors[]={
                //ściana 1
				1.0f,0.0f,0.0f,1.0f,
				1.0f,0.0f,0.0f,1.0f,
				1.0f,0.0f,0.0f,1.0f,

				1.0f,0.0f,0.0f,1.0f,
				1.0f,0.0f,0.0f,1.0f,
				1.0f,0.0f,0.0f,1.0f,

				//ściana 2
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,

				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,
				0.0f,1.0f,0.0f,1.0f,

				//ściana 3
				0.0f,0.0f,1.0f,1.0f,
				0.0f,0.0f,1.0f,1.0f,
				0.0f,0.0f,1.0f,1.0f,

				0.0f,0.0f,1.0f,1.0f,
				0.0f,0.0f,1.0f,1.0f,
				0.0f,0.0f,1.0f,1.0f,

				//ściana 4
				1.0f,1.0f,0.0f,1.0f,
				1.0f,1.0f,0.0f,1.0f,
				1.0f,1.0f,0.0f,1.0f,

				1.0f,1.0f,0.0f,1.0f,
				1.0f,1.0f,0.0f,1.0f,
				1.0f,1.0f,0.0f,1.0f,

				//ściana 5
				0.0f,1.0f,1.0f,1.0f,
				0.0f,1.0f,1.0f,1.0f,
				0.0f,1.0f,1.0f,1.0f,

				0.0f,1.0f,1.0f,1.0f,
				0.0f,1.0f,1.0f,1.0f,
				0.0f,1.0f,1.0f,1.0f,

				//ściana 6
				1.0f,1.0f,1.0f,1.0f,
				1.0f,1.0f,1.0f,1.0f,
				1.0f,1.0f,1.0f,1.0f,

				1.0f,1.0f,1.0f,1.0f,
				1.0f,1.0f,1.0f,1.0f,
				1.0f,1.0f,1.0f,1.0f,
			};


float texCoords[] = {
				//sciana 1
				1.0f, 0.0f,	
				0.0f, 1.0f,   
				0.0f, 0.0f,    
				1.0f, 0.0f,    
				1.0f, 1.0f,    
				0.0f, 1.0f,    

				//sciana 2
				1.0f, 0.0f,
				0.0f, 1.0f,
				0.0f, 0.0f,
				1.0f, 0.0f,
				1.0f, 1.0f,
				0.0f, 1.0f,

				//sciana 3
				1.0f, 0.0f,
				0.0f, 1.0f,
				0.0f, 0.0f,
				1.0f, 0.0f,
				1.0f, 1.0f,
				0.0f, 1.0f,

				//sciana 4
				1.0f, 0.0f,
				0.0f, 1.0f,
				0.0f, 0.0f,
				1.0f, 0.0f,
				1.0f, 1.0f,
				0.0f, 1.0f,

				//sciana 5
				1.0f, 0.0f,
				0.0f, 1.0f,
				0.0f, 0.0f,
				1.0f, 0.0f,
				1.0f, 1.0f,
				0.0f, 1.0f,

				//sciana 6
				1.0f, 0.0f,
				0.0f, 1.0f,
				0.0f, 0.0f,
				1.0f, 0.0f,
				1.0f, 1.0f,
				0.0f, 1.0f,
};

float normals[] = {
	//sciana 1
	0.0f,0.0f,-1.0f,0.0f,
	0.0f,0.0f,-1.0f,0.0f,
	0.0f,0.0f,-1.0f,0.0f,
	0.0f,0.0f,-1.0f,0.0f,
	0.0f,0.0f,-1.0f,0.0f,
	0.0f,0.0f,-1.0f,0.0f,

	//sciana 2
	0.0f,0.0f,1.0f,0.0f,
	0.0f,0.0f,1.0f,0.0f,
	0.0f,0.0f,1.0f,0.0f,
	0.0f,0.0f,1.0f,0.0f,
	0.0f,0.0f,1.0f,0.0f,
	0.0f,0.0f,1.0f,0.0f,

	//sciana 3
	0.0f,-1.0f,0.0f,0.0f,
	0.0f,-1.0f,0.0f,0.0f,
	0.0f,-1.0f,0.0f,0.0f,
	0.0f,-1.0f,0.0f,0.0f,
	0.0f,-1.0f,0.0f,0.0f,
	0.0f,-1.0f,0.0f,0.0f,

	//sciana 4
	0.0f,1.0f,0.0f,0.0f,
	0.0f,1.0f,0.0f,0.0f,
	0.0f,1.0f,0.0f,0.0f,
	0.0f,1.0f,0.0f,0.0f,
	0.0f,1.0f,0.0f,0.0f,
	0.0f,1.0f,0.0f,0.0f,

	//sciana 5
	-1.0f,0.0f,0.0f,0.0f,
	-1.0f,0.0f,0.0f,0.0f,
	-1.0f,0.0f,0.0f,0.0f,
	-1.0f,0.0f,0.0f,0.0f,
	-1.0f,0.0f,0.0f,0.0f,
	-1.0f,0.0f,0.0f,0.0f,

	//sciana 6
	1.0f,0.0f,0.0f,0.0f,
	1.0f,0.0f,0.0f,0.0f,
	1.0f,0.0f,0.0f,0.0f,
	1.0f,0.0f,0.0f,0.0f,
	1.0f,0.0f,0.0f,0.0f,
	1.0f,0.0f,0.0f,0.0f,
};

#endif // MYCUBE_H_INCLUDED
