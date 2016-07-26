//
// Copyright 2016 Pixar
//
// Licensed under the Apache License, Version 2.0 (the "Apache License")
// with the following modification; you may not use this file except in
// compliance with the Apache License and the following modification to it:
// Section 6. Trademarks. is deleted and replaced with:
//
// 6. Trademarks. This License does not grant permission to use the trade
//    names, trademarks, service marks, or product names of the Licensor
//    and its affiliates, except as required to comply with Section 4(c) of
//    the License and to reproduce the content of the NOTICE file.
//
// You may obtain a copy of the Apache License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the Apache License with the above modification is
// distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
// KIND, either express or implied. See the Apache License for the specific
// language governing permissions and limitations under the Apache License.
//
#include "pxr/usd/usdHydra/ptexTexture.h"
#include "pxr/usd/usd/schemaRegistry.h"
#include "pxr/usd/usd/typed.h"

#include "pxr/usd/sdf/types.h"
#include "pxr/usd/sdf/assetPath.h"

// Register the schema with the TfType system.
TF_REGISTRY_FUNCTION(TfType)
{
    TfType::Define<UsdHydraPtexTexture,
        TfType::Bases< UsdHydraTexture > >();
    
}

/* virtual */
UsdHydraPtexTexture::~UsdHydraPtexTexture()
{
}

/* static */
UsdHydraPtexTexture
UsdHydraPtexTexture::Get(const UsdStagePtr &stage, const SdfPath &path)
{
    if (not stage) {
        TF_CODING_ERROR("Invalid stage");
        return UsdHydraPtexTexture();
    }
    return UsdHydraPtexTexture(stage->GetPrimAtPath(path));
}


/* static */
const TfType &
UsdHydraPtexTexture::_GetStaticTfType()
{
    static TfType tfType = TfType::Find<UsdHydraPtexTexture>();
    return tfType;
}

/* static */
bool 
UsdHydraPtexTexture::_IsTypedSchema()
{
    static bool isTyped = _GetStaticTfType().IsA<UsdTyped>();
    return isTyped;
}

/* virtual */
const TfType &
UsdHydraPtexTexture::_GetTfType() const
{
    return _GetStaticTfType();
}

UsdAttribute
UsdHydraPtexTexture::GetFaceIndexAttr() const
{
    return GetPrim().GetAttribute(UsdHydraTokens->faceIndex);
}

UsdAttribute
UsdHydraPtexTexture::CreateFaceIndexAttr(VtValue const &defaultValue, bool writeSparsely) const
{
    return UsdSchemaBase::_CreateAttr(UsdHydraTokens->faceIndex,
                       SdfValueTypeNames->Int,
                       /* custom = */ false,
                       SdfVariabilityUniform,
                       defaultValue,
                       writeSparsely);
}

UsdAttribute
UsdHydraPtexTexture::GetFaceOffsetAttr() const
{
    return GetPrim().GetAttribute(UsdHydraTokens->faceOffset);
}

UsdAttribute
UsdHydraPtexTexture::CreateFaceOffsetAttr(VtValue const &defaultValue, bool writeSparsely) const
{
    return UsdSchemaBase::_CreateAttr(UsdHydraTokens->faceOffset,
                       SdfValueTypeNames->Int,
                       /* custom = */ false,
                       SdfVariabilityUniform,
                       defaultValue,
                       writeSparsely);
}

namespace {
static inline TfTokenVector
_ConcatenateAttributeNames(const TfTokenVector& left,const TfTokenVector& right)
{
    TfTokenVector result;
    result.reserve(left.size() + right.size());
    result.insert(result.end(), left.begin(), left.end());
    result.insert(result.end(), right.begin(), right.end());
    return result;
}
}

/*static*/
const TfTokenVector&
UsdHydraPtexTexture::GetSchemaAttributeNames(bool includeInherited)
{
    static TfTokenVector localNames = {
        UsdHydraTokens->faceIndex,
        UsdHydraTokens->faceOffset,
    };
    static TfTokenVector allNames =
        _ConcatenateAttributeNames(
            UsdHydraTexture::GetSchemaAttributeNames(true),
            localNames);

    if (includeInherited)
        return allNames;
    else
        return localNames;
}

// ===================================================================== //
// Feel free to add custom code below this line. It will be preserved by
// the code generator.
// ===================================================================== //
// --(BEGIN CUSTOM CODE)--
