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
#ifndef HDX_SIMPLE_LIGHT_TASK_H
#define HDX_SIMPLE_LIGHT_TASK_H

#include "pxr/imaging/hdx/version.h"
#include "pxr/imaging/hd/changeTracker.h"
#include "pxr/imaging/hd/light.h"
#include "pxr/imaging/hd/rprimCollection.h"
#include "pxr/imaging/hd/task.h"

#include "pxr/base/gf/matrix4d.h"
#include "pxr/base/gf/vec3f.h"
#include "pxr/imaging/glf/simpleMaterial.h"
#include "pxr/imaging/glf/simpleLight.h"

#include <boost/shared_ptr.hpp>

class HdRenderIndex;
class HdSceneDelegate;

typedef boost::shared_ptr<class HdRenderPass> HdRenderPassSharedPtr;
typedef boost::shared_ptr<class HdSimpleLightingShader> HdSimpleLightingShaderSharedPtr;
typedef boost::shared_ptr<class HdxShadowMatrixComputation> HdxShadowMatrixComputationSharedPtr;

TF_DECLARE_REF_PTRS(GlfSimpleShadowArray);


class HdxSimpleLightTask : public HdSceneTask {
public:
    HdxSimpleLightTask(HdSceneDelegate* delegate, SdfPath const& id);

protected:
    /// Execute render pass task
    virtual void _Execute(HdTaskContext* ctx);

    /// Sync the render pass resources
    virtual void _Sync(HdTaskContext* ctx);

private:
    // Should be weak ptrs
    HdCameraSharedPtr _camera;
    HdLightSharedPtrVector _lights;
    HdSimpleLightingShaderSharedPtr _lightingShader;
    int _collectionVersion;
    bool _enableShadows;
    GfVec4f _viewport;

    // XXX: compatibility hack for passing some unit tests until we have
    //      more formal material plumbing.
    GlfSimpleMaterial _material;
    GfVec4f _sceneAmbient;

    // For now these are only valid for the lifetime of a single pass of
    // the render graph.  Maybe long-term these could be change-tracked.
    GlfSimpleShadowArrayRefPtr _shadows;
    GlfSimpleLightVector _glfSimpleLights;
};

HdLightSharedPtrVector
_ComputeIncludedLights(
    HdLightSharedPtrVector const & allLights,
    SdfPathVector const & includedPaths,
    SdfPathVector const & excludedPaths);


struct HdxSimpleLightTaskParams
{
    HdxSimpleLightTaskParams()
        : cameraPath()
        , lightIncludePaths(1, SdfPath::AbsoluteRootPath())
        , lightExcludePaths()
        , enableShadows(false)
        , viewport(0.0f)
        , material()
        , sceneAmbient(0) 
        {}

    SdfPath cameraPath;
    SdfPathVector lightIncludePaths;
    SdfPathVector lightExcludePaths;
    bool enableShadows;
    GfVec4f viewport;
    
    // XXX: compatibility hack for passing some unit tests until we have
    //      more formal material plumbing.
    GlfSimpleMaterial material;
    GfVec4f sceneAmbient;
};

// VtValue requirements
std::ostream& operator<<(std::ostream& out, const HdxSimpleLightTaskParams& pv);
bool operator==(const HdxSimpleLightTaskParams& lhs, const HdxSimpleLightTaskParams& rhs);
bool operator!=(const HdxSimpleLightTaskParams& lhs, const HdxSimpleLightTaskParams& rhs);

struct HdxShadowParams
{
    HdxShadowParams()
        : shadowMatrix()
        , bias(0.0)
        , blur(0.0)
        , resolution(0)
        , enabled(false)
        {}

    HdxShadowMatrixComputationSharedPtr shadowMatrix;
    double bias;
    double blur;
    int resolution;
    bool enabled;
};

// VtValue requirements
std::ostream& operator<<(std::ostream& out, const HdxShadowParams& pv);
bool operator==(const HdxShadowParams& lhs, const HdxShadowParams& rhs);
bool operator!=(const HdxShadowParams& lhs, const HdxShadowParams& rhs);

#endif //HDX_SIMPLE_LIGHT_TASK_H
