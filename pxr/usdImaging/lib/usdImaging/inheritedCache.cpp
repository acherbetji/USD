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
#include "inheritedCache.h"

#include "pxr/usd/usdShade/shader.h"
#include "pxr/usd/usdHydra/lookAPI.h"

// TODO: We should centralize this logic in a UsdImaging ShaderAdapter.

/*static*/
UsdPrim
UsdImaging_LookStrategy::GetTargetedShader(UsdPrim const& lookPrim,
                                        UsdRelationship const& lookRel)
{
    SdfPathVector targets;
    if (not lookRel.GetForwardedTargets(&targets))
        return UsdPrim();

    if (targets.size() != 1) {
        // XXX: This should really be a validation error once USD gets that
        // feature.
        TF_WARN("We expect only one target on relationship %s of prim <%s>, "
                "but got %zu.",
                lookRel.GetName().GetText(),
                lookPrim.GetPath().GetText(),
                targets.size());
        return UsdPrim();
    }

    if (not targets[0].IsPrimPath()) {
        // XXX: This should really be a validation error once USD gets that
        // feature.
        TF_WARN("We expect the target of the relationship %s of prim <%s> "
                "to be a prim, instead it is <%s>.",
                lookRel.GetName().GetText(),
                lookPrim.GetPath().GetText(),
                targets[0].GetText());
        return UsdPrim();
    }

    return lookPrim.GetStage()->GetPrimAtPath(targets[0]);
}


/*static*/
SdfPath
UsdImaging_LookStrategy::GetBinding(UsdShadeLook const& look)
{
    TF_DEBUG(USDIMAGING_SHADERS).Msg("\t Look: %s\n", look.GetPath().GetText());
    if (UsdRelationship lookRel = UsdHydraLookAPI(look).GetBxdfRel()) {
         TF_DEBUG(USDIMAGING_SHADERS).Msg("\t LookRel: %s\n", 
                       lookRel.GetPath().GetText());
        UsdShadeShader shader(GetTargetedShader(look.GetPrim(), lookRel));
        if (shader) {
            TF_DEBUG(USDIMAGING_SHADERS).Msg("\t UsdShade binding found: %s\n", 
                    shader.GetPath().GetText());
            return shader.GetPath();
        }
    }

    // ---------------------------------------------------------------------- //
    // Deprecated shader style 
    // ---------------------------------------------------------------------- //
    TfToken hdSurf("hydraLook:surface"),
            surfType("HydraPbsSurface");

    if (UsdRelationship lookRel = look.GetPrim().GetRelationship(hdSurf)) {
        TF_DEBUG(USDIMAGING_SHADERS).Msg("\t LookRel: %s\n", 
                       lookRel.GetPath().GetText());
        if (UsdPrim shader = GetTargetedShader(look.GetPrim(), lookRel)) {
            if (TF_VERIFY(shader.GetTypeName() == surfType)) {
                TF_DEBUG(USDIMAGING_SHADERS).Msg(
                        "\t Deprecated binding found: %s\n", 
                        shader.GetPath().GetText());
                return shader.GetPath();
            }
        }
    }
    // ---------------------------------------------------------------------- //

    return SdfPath::EmptyPath();
}
