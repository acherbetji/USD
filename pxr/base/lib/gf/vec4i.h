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
////////////////////////////////////////////////////////////////////////
// This file is generated by a script.  Do not edit directly.  Edit the
// vec.template.h file to make changes.

#ifndef GF_VEC4I_H
#define GF_VEC4I_H

#include "pxr/base/tf/diagnostic.h"
#include "pxr/base/gf/limits.h"
#include "pxr/base/gf/traits.h"

#include <boost/functional/hash.hpp>

#include <cstddef>

#include <iosfwd>

template <>
struct GfIsGfVec<class GfVec4i> { static const bool value = true; };

/*!
 * \file vec4i.h
 * \ingroup group_gf_LinearAlgebra
 */

/*!
 * \class GfVec4i vec4i.h "pxr/base/gf/vec4i.h"
 * \ingroup group_gf_LinearAlgebra
 * \brief Basic type for a vector of 4 int components.
 *
 * Represents a vector of 4 components of type \c int.
 * It is intended to be fast and simple.
 *
 */

class GfVec4i
{
public:
    /// Scalar element type and dimension.
    typedef int ScalarType;
    static const size_t dimension = 4;

    /// Default constructor does no initialization.
    GfVec4i() {}


    // Copy constructor.  XXX: Remove this, use compiler-generated.
    GfVec4i(const GfVec4i &other) {
        *this = other;
    }

    /// Initialize all elements to a single value.
    explicit GfVec4i(int value) {
        _data[0] = value;
        _data[1] = value;
        _data[2] = value;
        _data[3] = value;
    }

    /// Initialize all elements with explicit arguments.
    GfVec4i(int s0, int s1, int s2, int s3) {
        Set(s0, s1, s2, s3);
    }
    
    /// Construct with pointer to values.
    template <class Scl>
    explicit GfVec4i(Scl const *p) { Set(p); }
 
    /// Create a unit vector along the X-axis.
    static GfVec4i XAxis() {
        GfVec4i result(0);
        result[0] = 1;
        return result;
    }
    /// Create a unit vector along the Y-axis.
    static GfVec4i YAxis() {
        GfVec4i result(0);
        result[1] = 1;
        return result;
    }
    /// Create a unit vector along the Z-axis.
    static GfVec4i ZAxis() {
        GfVec4i result(0);
        result[2] = 1;
        return result;
    }
    /// Create a unit vector along the W-axis.
    static GfVec4i WAxis() {
        GfVec4i result(0);
        result[3] = 1;
        return result;
    }
    
    /// Create a unit vector along the i-th axis, zero-based.  Return the zero
    /// vector if \p i is greater than or equal to 4.
    static GfVec4i Axis(size_t i) {
        GfVec4i result(0);
        if (i < 4)
            result[i] = 1;
        return result;
    }
    
    /// Set all elements with passed arguments.
    GfVec4i &Set(int s0, int s1, int s2, int s3) {
        _data[0] = s0;
        _data[1] = s1;
        _data[2] = s2;
        _data[3] = s3;
        return *this;
    }

    /// Set all elements with a pointer to data.
    GfVec4i &Set(int const *a) {
        return Set(a[0], a[1], a[2], a[3]);
    }

    /// Direct data access.
    int const *data() const { return _data; }
    int *data() { return _data; }
    int const *GetArray() const { return data(); }

    /// Indexing.
    int const &operator[](size_t i) const { return _data[i]; }
    int &operator[](size_t i) { return _data[i]; }

    /// Hash.
    friend inline size_t hash_value(GfVec4i const &vec) {
        size_t h = 0;
        boost::hash_combine(h, vec[0]);
        boost::hash_combine(h, vec[1]);
        boost::hash_combine(h, vec[2]);
        boost::hash_combine(h, vec[3]);
        return h;
    }

    /// Equality comparison.
    bool operator==(GfVec4i const &other) const {
        return _data[0] == other[0] and
               _data[1] == other[1] and
               _data[2] == other[2] and
               _data[3] == other[3];
    }
    bool operator!=(GfVec4i const &other) const {
        return !(*this == other);
    }

    // XXX: Add inequality for other vec types...
    /// Equality comparison.
    bool operator==(class GfVec4d const &other) const;
    /// Equality comparison.
    bool operator==(class GfVec4f const &other) const;
    /// Equality comparison.
    bool operator==(class GfVec4h const &other) const;
    
    /// Create a vec with negated elements.
    GfVec4i operator-() const {
        return GfVec4i(-_data[0], -_data[1], -_data[2], -_data[3]);
    }

    /// Addition.
    GfVec4i &operator+=(GfVec4i const &other) {
        _data[0] += other[0];
        _data[1] += other[1];
        _data[2] += other[2];
        _data[3] += other[3];
        return *this;
    }
    friend GfVec4i operator+(GfVec4i const &l, GfVec4i const &r) {
        return GfVec4i(l) += r;
    }

    /// Subtraction.
    GfVec4i &operator-=(GfVec4i const &other) {
        _data[0] -= other[0];
        _data[1] -= other[1];
        _data[2] -= other[2];
        _data[3] -= other[3];
        return *this;
    }
    friend GfVec4i operator-(GfVec4i const &l, GfVec4i const &r) {
        return GfVec4i(l) -= r;
    }

    /// Multiplication by scalar.
    GfVec4i &operator*=(double s) {
        _data[0] *= s;
        _data[1] *= s;
        _data[2] *= s;
        _data[3] *= s;
	return *this;
    }
    GfVec4i operator*(double s) const {
	return GfVec4i(*this) *= s;
    }
    friend GfVec4i operator*(double s, GfVec4i const &v) {
        return v * s;
    }

        /// Division by scalar.
    GfVec4i &operator/=(int s) {
        _data[0] /= s;
        _data[1] /= s;
        _data[2] /= s;
        _data[3] /= s;
        return *this;
    }
    GfVec4i operator/(int s) const {
	return GfVec4i(*this) /= s;
    }
    
    /// See GfDot().
    int operator*(GfVec4i const &v) const {
        return _data[0] * v[0] + _data[1] * v[1] + _data[2] * v[2] + _data[3] * v[3];
    }

    /// Returns the projection of \p this onto \p v. That is: 
    /// \code
    /// v * (*this * v)
    /// \endcode
    GfVec4i GetProjection(GfVec4i const &v) const {
        return v * (*this * v);
    }

    /// Returns the orthogonal complement of \p this->GetProjection(b). That is:
    /// \code
    ///  *this - this->GetProjection(b)
    /// \endcode
    GfVec4i GetComplement(GfVec4i const &b) const {
	return *this - this->GetProjection(b);
    }

    /// Squared length.
    int GetLengthSq() const {
        return *this * *this;
    }

 
private:
    int _data[4];
};

/// Output a GfVec4i
/// \ingroup group_gf_DebuggingOutput
std::ostream& operator<<(std::ostream &, GfVec4i const &);


/// Returns component-wise multiplication of vectors \p v1 and \p v2.
inline GfVec4i
GfCompMult(GfVec4i const &v1, GfVec4i const &v2) {
    return GfVec4i(
        v1[0] * v2[0],
        v1[1] * v2[1],
        v1[2] * v2[2],
        v1[3] * v2[3]
        );
}

/// Returns component-wise quotient of vectors \p v1 and \p v2.
inline GfVec4i
GfCompDiv(GfVec4i const &v1, GfVec4i const &v2) {
    return GfVec4i(
        v1[0] / v2[0],
        v1[1] / v2[1],
        v1[2] / v2[2],
        v1[3] / v2[3]
        );
}

/// Returns the dot (inner) product of two vectors.
inline int
GfDot(GfVec4i const &v1, GfVec4i const &v2) {
    return v1 * v2;
}


 
#endif // GF_VEC4I_H
