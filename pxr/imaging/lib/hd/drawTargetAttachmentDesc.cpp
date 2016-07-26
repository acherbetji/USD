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
#include "pxr/imaging/hd/drawTargetAttachmentDesc.h"



HdDrawTargetAttachmentDesc::HdDrawTargetAttachmentDesc()
 : _name()
 , _format(HdFormatUnknown)
 , _clearColor()
{

}


HdDrawTargetAttachmentDesc::HdDrawTargetAttachmentDesc(const std::string &name,
                                                       HdFormat           format,
                                                       const VtValue     &clearColor)
  : _name(name)
  , _format(format)
  , _clearColor(clearColor)
{

}


HdDrawTargetAttachmentDesc::HdDrawTargetAttachmentDesc(
                                         const HdDrawTargetAttachmentDesc &copy)
  : _name(copy._name)
  , _format(copy._format)
  , _clearColor(copy._clearColor)
{

}


HdDrawTargetAttachmentDesc &
HdDrawTargetAttachmentDesc::operator =(const HdDrawTargetAttachmentDesc &copy)
{
    _name       = copy._name;
    _format     = copy._format;
    _clearColor = copy._clearColor;

    return *this;
}


size_t
HdDrawTargetAttachmentDesc::GetHash() const
{
    size_t hash = boost::hash_value(_name);
    boost::hash_combine(hash, _format);
    boost::hash_combine(hash, _clearColor);

    return hash;
}


void
HdDrawTargetAttachmentDesc::Dump(std::ostream &out) const
{
    out << _name        << " "
        << _format      << " "
        << _clearColor;
}


bool
HdDrawTargetAttachmentDesc::operator==(
                                  const HdDrawTargetAttachmentDesc &other) const
{
    return ((_name       == other._name)   &&
            (_format     == other._format) &&
            (_clearColor == other._clearColor));
}


bool
HdDrawTargetAttachmentDesc::operator!=(
                                  const HdDrawTargetAttachmentDesc &other) const
{
    return ((_name       != other._name)   ||
            (_format     != other._format) ||
            (_clearColor != other._clearColor));
}


size_t hash_value(HdDrawTargetAttachmentDesc const &attachment)
{
    return attachment.GetHash();
}

std::ostream &operator <<(std::ostream &out,
                          const HdDrawTargetAttachmentDesc &pv)
{
    pv.Dump(out);

    return out;
}
