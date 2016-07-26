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
/// \file UVTextureStorage.cpp
//    

#include "pxr/imaging/glf/uvTextureStorage.h"
#include "pxr/imaging/glf/uvTextureStorageData.h"

TF_REGISTRY_FUNCTION(TfType)
{
    TfType::Define<GlfUVTextureStorage, TfType::Bases<GlfBaseTexture> >();
}

GlfUVTextureStorageRefPtr 
GlfUVTextureStorage::New(
    unsigned int width,
    unsigned int height, 
    const VtValue &storageData)
{
    return TfCreateRefPtr(new GlfUVTextureStorage(
        width, height, storageData)); 
}

GlfUVTextureStorage::GlfUVTextureStorage(
    unsigned int width,
    unsigned int height, 
    const VtValue &storageData)
    : _width(width)
    , _height(height)
    , _storageData(storageData)
{
    /* nothing */
}

void 
GlfUVTextureStorage::_OnSetMemoryRequested(size_t targetMemory)
{
    GlfUVTextureStorageDataRefPtr texData =
        GlfUVTextureStorageData::New(
            _width,
            _height,
            _storageData);
    texData->Read(0, false); 
    _UpdateTexture(texData);
    _CreateTexture(texData, _GenerateMipmap()); 
}

bool
GlfUVTextureStorage::_GenerateMipmap() const
{
    return false;
}
