/**
 * Created by rayfalling on 2020/11/10.
 * */

#include "Math/FPlane.h"

#include "Math/FMatrix.h"

using namespace Engine::Core::Math;

/* FPlane inline functions
 *****************************************************************************/

// FPlane FPlane::TransformBy(const FMatrix& m) const {
// 	const auto tmpTa = m.TransposeAdjoint();
// 	const auto detM = m.Determinant();
// 	return this->TransformByUsingAdjointT(m, detM, tmpTa);
// }

// FPlane FPlane::TransformByUsingAdjointT(const FMatrix& m, const float detM, const FMatrix& ta) const {
// 	FVector3 newNorm = ta.TransformVector(*this).GetSafeNormal();
// 	
// 	if (detM < 0.f) {
// 		newNorm *= -1.0f;
// 	}
// 	
// 	return FPlane(m.TransformPosition(*this * W), newNorm);
// }
