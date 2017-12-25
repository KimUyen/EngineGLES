#include "GLModel.h"
#include <cstdio>
#include "glm.hpp"
#include <windows.h>
#include <gl\GLU.h>

struct NFGVertex
{
	glm::vec3 pos;
	glm::vec3 norm;
	glm::vec3 binorm;
	glm::vec3 tgt;
	glm::vec2 uv;
};

bool GLModel::ImportModelFromNFGFile(char* path)
{	////////
	// load NFG file and put it into buffer
	FILE* f = fopen(path, "r");
	if (f == NULL)
	{
		printf("Load NFG failed: %s", path);
		return false;
	}
	
	// Read vertices
	int nVertices;
	fscanf(f, "NrVertices: %d\r\n", &nVertices);
	int index = 0;
	float valPos[3];
	float valNorm[3];
	float valBinorm[3];
	float valTGT[3];
	float valTexCoord[2];
	for (int i = 0; i < nVertices; i++)
	{
		valPos[3] = 1.0f;
		fscanf(f, "%d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];\r\n",
			&index, &valPos[0], &valPos[1], &valPos[2], &valNorm[0], &valNorm[1], &valNorm[2], &valBinorm[0], &valBinorm[1], &valBinorm[2],
			&valTGT[i], &valTGT[i], &valTGT[i], &valTexCoord[0], &valTexCoord[1]
		);
		_positions.push_back(valPos[0]);
		_positions.push_back(valPos[1]);
		_positions.push_back(valPos[2]);

		_normals.push_back(valNorm[0]);
		_normals.push_back(valNorm[1]);
		_normals.push_back(valNorm[2]);

		_binormals.push_back(valBinorm[0]);
		_binormals.push_back(valBinorm[1]);
		_binormals.push_back(valBinorm[2]);

		_sTangents.push_back(valTGT[0]);
		_sTangents.push_back(valTGT[1]);
		_sTangents.push_back(valTGT[2]);

		_texCoords.push_back(valTexCoord[0]);
		_texCoords.push_back(valTexCoord[1]);
	}

	// read indices
	fscanf(f, "NrIndices: %d\r\n", &_nIndices);
	int x, y, z;

	for (int i = 0; i < _nIndices; i += 3)
	{
		fscanf(f, "   %d.    %d,    %d,    %d\r\n", &index, &x, &y, &z);
		_pIndices.push_back((GLushort)x);
		_pIndices.push_back((GLushort)y);
		_pIndices.push_back((GLushort)z);
	}

	// clean up
	fclose(f);
	printf("[LOADED] Model: %s\n", path);
}