#pragma once


struct TexVertex
{
	Vector3 position;
	Vector3 normal;
	Vector2 color;

	enum { FVF = (D3DFVF_XYZ, D3DFVF_NORMAL, D3DFVF_TEX1) };

	TexVertex() { }

	TexVertex(Vector3 _xyz, Vector3 _normal, Vector2 _color)
		: position(_xyz), normal(_normal), color(_color) { }
};