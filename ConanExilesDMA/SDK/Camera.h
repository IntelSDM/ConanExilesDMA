#pragma once
#include "Engine.h"

class Camera
{
public:
	static Vector2 WorldToScreen(MinimalViewInfo viewinfo, Vector3 world);
	static ViewMatrix ToMatrixWithScale(FTransform transform);
	static Vector3 ResolveMatrix(FTransform transform, FTransform c2w);
};