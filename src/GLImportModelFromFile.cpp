#include "GLModel.h"
#include <cstdio>
#include "glm.hpp"
#include <windows.h>
#include <gl\GLU.h>

bool GLModel::ImportModelFromNFGFile(char* path)
{	//////////
	//// load NFG file and put it into buffer
	//FILE* f = fopen(path, "r");
	//if (f == NULL)
	//{
	//	printf("Load NFG failed: %s", path);
	//	return false;
	//}
	//
	//// Read vertices
	//int nVertices;
	//fscanf(f, "NrVertices: %d\r\n", &nVertices);
	//int index = 0;
	//float valPos[4];
	//float valNorm[3];
	//float valBinorm[3];
	//float valTGT[3];
	//float valTexCoord[2];
	//for (int i = 0; i < nVertices; i++)
	//{
	//	valPos[3] = 1.0f;
	//	fscanf(f, "%d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];\r\n",
	//		&index, &valPos[0], &valPos[1], &valPos[2], &valNorm[0], &valNorm[1], &valNorm[2], &valBinorm[0], &valBinorm[1], &valBinorm[2],
	//		&valTGT[0], &valTGT[1], &valTGT[2], &valTexCoord[0], &valTexCoord[1]
	//	);
	//	_positions.push_back(valPos[0]);
	//	_positions.push_back(valPos[1]);
	//	_positions.push_back(valPos[2]);
	//
	//	_normals.push_back(valNorm[0]);
	//	_normals.push_back(valNorm[1]);
	//	_normals.push_back(valNorm[2]);
	//
	//	_binormals.push_back(valBinorm[0]);
	//	_binormals.push_back(valBinorm[1]);
	//	_binormals.push_back(valBinorm[2]);
	//
	//	_sTangents.push_back(valTGT[0]);
	//	_sTangents.push_back(valTGT[1]);
	//	_sTangents.push_back(valTGT[2]);
	//
	//	_texCoords.push_back(valTexCoord[0]);
	//	_texCoords.push_back(valTexCoord[1]);
	//}
	//
	//// read indices
	//fscanf(f, "NrIndices: %d\r\n", &_nIndices);
	//int x, y, z;
	//
	//for (int i = 0; i < _nIndices; i += 3)
	//{
	//	fscanf(f, "   %d.    %d,    %d,    %d\r\n", &index, &x, &y, &z);
	//	_pIndices.push_back((GLushort)x);
	//	_pIndices.push_back((GLushort)y);
	//	_pIndices.push_back((GLushort)z);
	//}
	//
	//// clean up
	//fclose(f);
	//printf("[LOADED] Model: %s\n", path);
	//
	//return true;

	/////////////////
	// Load NFG file 
	/////////////////
	FILE* f = fopen(path, "r");
	if (f == NULL)
	{
		printf("Load NFG failed: %s", path);
		return false;
	}
	
	// Read vertices
	fscanf(f, "NrVertices: %d\r\n", &_nVertices);
	_pVertices = new NFGVertex[_nVertices];
	int index = 0;
	
	for (int i = 0; i < _nVertices; i++)
	{
		fscanf(f, "%d. pos:[%f, %f, %f]; norm:[%f, %f, %f]; binorm:[%f, %f, %f]; tgt:[%f, %f, %f]; uv:[%f, %f];\r\n",
			&index,
			&_pVertices[i].pos.x,
			&_pVertices[i].pos.y,
			&_pVertices[i].pos.z,
			&_pVertices[i].norm.x,
			&_pVertices[i].norm.y,
			&_pVertices[i].norm.z,
			&_pVertices[i].binorm.x,
			&_pVertices[i].binorm.y,
			&_pVertices[i].binorm.z,
			&_pVertices[i].tgt.x,
			&_pVertices[i].tgt.y,
			&_pVertices[i].tgt.z,
			&_pVertices[i].uv.x,
			&_pVertices[i].uv.y
		);
	
		//m_pVertices[i].pos.y += -0.8;
	}
	
	// read indices
	fscanf(f, "NrIndices: %d\r\n", &_nIndices);
	_pIndices = new GLushort[_nIndices];
	int x, y, z;
	
	for (int i = 0; i < _nIndices; i += 3)
	{
		fscanf(f, "   %d.    %d,    %d,    %d\r\n", &index, &x, &y, &z);
		_pIndices[i] = (GLushort)x;
		_pIndices[i + 1] = (GLushort)y;
		_pIndices[i + 2] = (GLushort)z;
	}
	
	// clean up
	fclose(f);
	printf("[LOADED] Model: %s\n", path);

	return true;
}
