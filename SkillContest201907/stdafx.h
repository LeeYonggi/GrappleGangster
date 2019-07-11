#pragma once


//define
#define DEVICE DXUTGetD3D9Device()

using Vector2 = D3DXVECTOR2;
using Vector3 = D3DXVECTOR3;
using Matrix  = D3DXMATRIX;

constexpr int SCREEN_X = 1280;
constexpr int SCREEN_Y = 720;



#include "Singleton.h"

#include "TexVertex.h"
#include "CameraManager.h"
#include "RenderManager.h"

#include "MainProc.h"