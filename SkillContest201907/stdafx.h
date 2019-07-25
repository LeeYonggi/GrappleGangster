#pragma once


// define
#define DEVICE DXUTGetD3D9Device()
#define ELTime DXUTGetElapsedTime() * Timer::GetTimeScale()

using Vector2 = D3DXVECTOR2;
using Vector3 = D3DXVECTOR3;
using Matrix  = D3DXMATRIXA16;
using Color	  = D3DXCOLOR;

constexpr float SCREEN_X = 1280;
constexpr float SCREEN_Y = 720;

using Object = void*;


// 헤더파일
#include "Singleton.h"
#include "Utility.h"

#include "EventHandler.h"

#include "TexVertex.h"
#include "Timer.h"

#include "CameraManager.h"
#include "RenderManager.h"

#include "GameObject.h"

#include "ResourceManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ObjectManager.h"
#include "GameManager.h"

#include "InGameScene.h"

#include "Player.h"

#include "MainProc.h"