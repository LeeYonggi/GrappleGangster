#pragma once


struct TexVertex
{
	Vector3 position;
	Vector3 normal;
	Vector2 tex;

	enum { FVF = (D3DFVF_XYZ| D3DFVF_NORMAL| D3DFVF_TEX1) };

	TexVertex() { }

	TexVertex(Vector3 _xyz, Vector3 _normal, Vector2 _tex)
		: position(_xyz), normal(_normal), tex(_tex) { }
};

struct MultiTexVertex
{
	Vector3 position1;
	Vector3 postiion2; 
	Vector2 tex1;
	Vector2 tex2;

	enum { FVF = (D3DFVF_XYZ | D3DFVF_TEX2) };
	MultiTexVertex() { }
};