#include "GLModel.h"
#include <cstdio>

bool GLModel::ImportModelFromNFGFile(char* path)
{	////////
	// load NFG file and put it into buffer
	FILE* f = fopen_s(path, "r");
	if (f == NULL)
	{
		printf("Load NFG failed: %s", path);
		return;
	}

	// Read vertices
	fscanf(f, "NrVertices: %d\r\n", &nVertices);
	pVertices = new NFGVertex[nVertices];
	int index = 0;

	for (int i = 0; i < nVertices; i++)
	{
		fscanf(f, "%d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];\r\n",
			&index,
			&pVertices[i].pos.x,
			&pVertices[i].pos.y,
			&pVertices[i].pos.z,
			&pVertices[i].norm.x,
			&pVertices[i].norm.y,
			&pVertices[i].norm.z,
			&pVertices[i].binorm.x,
			&pVertices[i].binorm.y,
			&pVertices[i].binorm.z,
			&pVertices[i].tgt.x,
			&pVertices[i].tgt.y,
			&pVertices[i].tgt.z,
			&pVertices[i].uv.x,
			&pVertices[i].uv.y
		);
	}

	// read indices
	fscanf(f, "NrIndices: %d\r\n", &nIndices);
	pIndices = new GLushort[nIndices];
	int x, y, z;

	for (int i = 0; i < nIndices; i += 3)
	{
		fscanf(f, "   %d.    %d,    %d,    %d\r\n", &index, &x, &y, &z);
		pIndices[i] = (GLushort)x;
		pIndices[i + 1] = (GLushort)y;
		pIndices[i + 2] = (GLushort)z;
	}

	// clean up
	fclose(f);
	printf("[LOADED] Model: %s\n", path);
}