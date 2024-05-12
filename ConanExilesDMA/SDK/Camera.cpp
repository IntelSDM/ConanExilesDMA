#include "Pch.h"
#include "ConfigUtilities.h"
#include "Camera.h"

static ViewMatrix CreateMatrix(Vector3 rot, Vector3 origin) {
	const float DEG_TO_RAD = static_cast<float>(3.14159265358979323846) / 180.f;
	const float radPitch = rot.x * DEG_TO_RAD;
	const float radYaw = rot.y * DEG_TO_RAD;
	const float radRoll = rot.z * DEG_TO_RAD;

	const float SP = sinf(radPitch);
	const float CP = cosf(radPitch);
	const float SY = sinf(radYaw);
	const float CY = cosf(radYaw);
	const float SR = sinf(radRoll);
	const float CR = cosf(radRoll);

	ViewMatrix matrix;
	matrix.matrix[0][0] = CP * CY;
	matrix.matrix[0][1] = CP * SY;
	matrix.matrix[0][2] = SP;
	matrix.matrix[0][3] = 0.f;

	matrix.matrix[1][0] = SR * SP * CY - CR * SY;
	matrix.matrix[1][1] = SR * SP * SY + CR * CY;
	matrix.matrix[1][2] = -SR * CP;
	matrix.matrix[1][3] = 0.f;

	matrix.matrix[2][0] = -(CR * SP * CY + SR * SY);
	matrix.matrix[2][1] = CY * SR - CR * SP * SY;
	matrix.matrix[2][2] = CR * CP;
	matrix.matrix[2][3] = 0.f;

	matrix.matrix[3][0] = origin.x;
	matrix.matrix[3][1] = origin.y;
	matrix.matrix[3][2] = origin.z;
	matrix.matrix[3][3] = 1.f;

	return matrix;
}

Vector2 Camera::WorldToScreen(MinimalViewInfo viewinfo, Vector3 world)
{
	Vector3 Screenlocation(0, 0, 0);
	Vector3 rot = Vector3(viewinfo.Rotation.Pitch, viewinfo.Rotation.Yaw, viewinfo.Rotation.Roll);
	Vector3 campos = Vector3(viewinfo.Location.X, viewinfo.Location.Y, viewinfo.Location.Z);
	const ViewMatrix tempMatrix = CreateMatrix(rot, Vector3(0, 0, 0));

	Vector3 vAxisX(tempMatrix.matrix[0][0], tempMatrix.matrix[0][1], tempMatrix.matrix[0][2]);
	Vector3 vAxisY(tempMatrix.matrix[1][0], tempMatrix.matrix[1][1], tempMatrix.matrix[1][2]);
	Vector3 vAxisZ(tempMatrix.matrix[2][0], tempMatrix.matrix[2][1], tempMatrix.matrix[2][2]);

	Vector3 vDelta = world - campos;
	Vector3 vTransformed = Vector3(Vector3::Dot(vDelta,vAxisY), Vector3::Dot(vDelta,vAxisZ), Vector3::Dot(vDelta,vAxisX));

	if (vTransformed.z < 1.f)
		vTransformed.z = 1.f;

	const float FOV_DEG_TO_RAD = static_cast<float>(3.14159265358979323846) / 360.f;
	int centrex = Configs.Overlay.OverrideResolution ? Configs.Overlay.Width /2 : GetSystemMetrics(SM_CXSCREEN) / 2;
	int centrey = Configs.Overlay.OverrideResolution ? Configs.Overlay.Height / 2 : GetSystemMetrics(SM_CYSCREEN) / 2;
	Screenlocation.x = centrex + vTransformed.x * (centrex / tanf(
		viewinfo.FOV * FOV_DEG_TO_RAD)) / vTransformed.z;
	Screenlocation.y = centrey - vTransformed.y * (centrex / tanf(
		viewinfo.FOV * FOV_DEG_TO_RAD)) / vTransformed.z;

	return Vector2(Screenlocation.x, Screenlocation.y);
}

ViewMatrix Camera::ToMatrixWithScale(FTransform transform)
{
	ViewMatrix m;

	m.matrix[3][0] = transform.Translation.X;
	m.matrix[3][1] = transform.Translation.Y;
	m.matrix[3][2] = transform.Translation.Z;

	float x2 = transform.Rotation.X + transform.Rotation.X;
	float y2 = transform.Rotation.Y + transform.Rotation.Y;
	float z2 = transform.Rotation.Z + transform.Rotation.Z;

	float xx2 = transform.Rotation.X * x2;
	float yy2 = transform.Rotation.Y * y2;
	float zz2 = transform.Rotation.Z * z2;
	m.matrix[0][0] = (1.0f - (yy2 + zz2)) * transform.Scale3D.X;
	m.matrix[1][1] = (1.0f - (xx2 + zz2)) * transform.Scale3D.Y;
	m.matrix[2][2] = (1.0f - (xx2 + yy2)) * transform.Scale3D.Z;


	float yz2 = transform.Rotation.Y * z2;
	float wx2 = transform.Rotation.W * x2;
	m.matrix[2][1] = (yz2 - wx2) * transform.Scale3D.Z;
	m.matrix[1][2] = (yz2 + wx2) * transform.Scale3D.Y;


	float xy2 = transform.Rotation.X * y2;
	float wz2 = transform.Rotation.W * z2;
	m.matrix[1][0] = (xy2 - wz2) * transform.Scale3D.Y;
	m.matrix[0][1] = (xy2 + wz2) * transform.Scale3D.X;


	float xz2 = transform.Rotation.X * z2;
	float wy2 = transform.Rotation.W * y2;
	m.matrix[2][0] = (xz2 + wy2) * transform.Scale3D.Z;
	m.matrix[0][2] = (xz2 - wy2) * transform.Scale3D.X;

	m.matrix[0][3] = 0.0f;
	m.matrix[1][3] = 0.0f;
	m.matrix[2][3] = 0.0f;
	m.matrix[3][3] = 1.0f;

	return m;
}
Vector3 Camera::ResolveMatrix(FTransform transform, FTransform c2w)
{
	ViewMatrix matrix;
	ViewMatrix bonematrix = ToMatrixWithScale(transform);
	ViewMatrix c2wmatrix = ToMatrixWithScale(c2w);
	int i, j, k;
	for (i = 0; i < 4; i++) {
		for (j = 0; j < 4; j++) {
			matrix.matrix[i][j] = 0;
			for (k = 0; k < 4; k++) {
				matrix.matrix[i][j] += bonematrix.matrix[i][k] * c2wmatrix.matrix[k][j];
			}
		}
	}


	return Vector3{ matrix.matrix[3][0],  matrix.matrix[3][1],  matrix.matrix[3][2] };
}