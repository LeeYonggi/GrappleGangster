#pragma once


//define
#define DEVICE DXUTGetD3D9Device()

using Vector2 = D3DXVECTOR2;
using Vector3 = D3DXVECTOR3;
using Matrix  = D3DXMATRIX;

constexpr int SCREEN_X = 1280;
constexpr int SCREEN_Y = 720;

using Object = void*;


#include "Singleton.h"

#include "EventHandler.h"

#include "TexVertex.h"

#include "CameraManager.h"
#include "RenderManager.h"
#include "ResourceManager.h"
#include "InputManager.h"

#include "GameObject.h"

#include "MainProc.h"