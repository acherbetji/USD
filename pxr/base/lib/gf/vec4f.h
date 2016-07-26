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

#ifndef GF_VEC4F_H
#define GF_VEC4F_H

#include "pxr/base/tf/diagnostic.h"
#include "pxr/base/gf/limits.h"
#include "pxr/base/gf/traits.h"
#include "pxr/base/gf/math.h"

#include <boost/functional/hash.hpp>

#include <cstddef>
#include <cmath>

#include <iosfwd>

template <>
struct GfIsGfVec<class GfVec4f> { static const bool value = true; };

/*!
 * \file vec4f.h
 * \ingroup group_gf_LinearAlgebra
 */

/*!
 * \class GfVec4f vec4f.h "pxr/base/gf/vec4f.h"
 * \ingroup group_gf_LinearAlgebra
 * \brief Basic type for a vector of 4 float components.
 *
 * Represents a vector of 4 components of type \c float.
 * It is intended to be fast and simple.
 *
 */

class GfVec4f
{
public:
    /// Scalar element type and dimension.
    typedef float ScalarType;
    static const size_t dimension = 4;

    /// Default constructor does no initialization.
    GfVec4f() {}


    // Copy constructor.  XXX: Remove this, use compiler-generated.
    GfVec4f(const GfVec4f &other) {
        *this = other;
    }

    /// Initialize all elements to a single value.
    explicit GfVec4f(float value) {
        _data[0] = value;
        _data[1] = value;
        _data[2] = value;
        _data[3] = value;
    }

    /// Initialize all elements with explicit arguments.
    GfVec4f(float s0, float s1, float s2, float s3) {
        Set(s0, s1, s2, s3);
    }
    
    /// Construct with pointer to values.
    template <class Scl>
    explicit GfVec4f(Scl const *p) { Set(p); }

    /// Construct from GfVec4d.
    explicit GfVec4f(class GfVec4d const &other);

    /// Implicitly convert from GfVec4h.
    GfVec4f(class GfVec4h const &other);

    /// Implicitly convert from GfVec4i.
    GfVec4f(class GfVec4i const &other);
 
    /// Create a unit vector along the X-axis.
    static GfVec4f XAxis() {
        GfVec4f result(0);
        result[0] = 1;
        return result;
    }
    /// Create a unit vector along the Y-axis.
    static GfVec4f YAxis() {
        GfVec4f result(0);
        result[1] = 1;
        return result;
    }
    /// Create a unit vector along the Z-axis.
    static GfVec4f ZAxis() {
        GfVec4f result(0);
        result[2] = 1;
        return result;
    }
    /// Create a unit vector along the W-axis.
    static GfVec4f WAxis() {
        GfVec4f result(0);
        result[3] = 1;
        return result;
    }
    
    /// Create a unit vector along the i-th axis, zero-based.  Return the zero
    /// vector if \p i is greater than or equal to 4.
    static GfVec4f Axis(size_t i) {
        GfVec4f result(0);
        if (i < 4)
            result[i] = 1;
        return result;
    }
    
    /// Set all elements with passed arguments.
    GfVec4f &Set(float s0, float s1, float s2, float s3) {
        _data[0] = s0;
        _data[1] = s1;
        _data[2] = s2;
        _data[3] = s3;
        return *this;
    }

    /// Set all elements with a pointer to data.
    GfVec4f &Set(float const *a) {
        return Set(a[0], a[1], a[2], a[3]);
    }

    /// Direct data access.
    float const *data() const { return _data; }
    float *data() { return _data; }
    float const *GetArray() const { return data(); }

    /// Indexing.
    float const &operator[](size_t i) const { return _data[i]; }
    float &operator[](size_t i) { return _data[i]; }

    /// Hash.
    friend inline size_t hash_value(GfVec4f const &vec) {
        size_t h = 0;
        boost::hash_combine(h, vec[0]);
        boost::hash_combine(h, vec[1]);
        boost::hash_combine(h, vec[2]);
        boost::hash_combine(h, vec[3]);
        return h;
    }

    /// Equality comparison.
    bool operator==(GfVec4f const &other) const {
        return _data[0] == other[0] and
               _data[1] == other[1] and
               _data[2] == other[2] and
               _data[3] == other[3];
    }
    bool operator!=(GfVec4f const &other) const {
        return !(*this == other);
    }

    // XXX: Add inequality for other vec types...
    /// Equality comparison.
    bool operator==(class GfVec4d const &other) const;
    /// Equality comparison.
    bool operator==(class GfVec4h const &other) const;
    /// Equality comparison.
    bool operator==(class GfVec4i const &other) const;
    
    /// Create a vec with negated elements.
    GfVec4f operator-() const {
        return GfVec4f(-_data[0], -_data[1], -_data[2], -_data[3]);
    }

    /// Addition.
    GfVec4f &operator+=(GfVec4f const &other) {
        _data[0] += other[0];
        _data[1] += other[1];
        _data[2] += other[2];
        _data[3] += other[3];
        return *this;
    }
    friend GfVec4f operator+(GfVec4f const &l, GfVec4f const &r) {
        return GfVec4f(l) += r;
    }

    /// Subtraction.
    GfVec4f &operator-=(GfVec4f const &other) {
        _data[0] -= other[0];
        _data[1] -= other[1];
        _data[2] -= other[2];
        _data[3] -= other[3];
        return *this;
    }
    friend GfVec4f operator-(GfVec4f const &l, GfVec4f const &r) {
        return GfVec4f(l) -= r;
    }

    /// Multiplication by scalar.
    GfVec4f &operator*=(double s) {
        _data[0] *= s;
        _data[1] *= s;
        _data[2] *= s;
        _data[3] *= s;
	return *this;
    }
    GfVec4f operator*(double s) const {
	return GfVec4f(*this) *= s;
    }
    friend GfVec4f operator*(double s, GfVec4f const &v) {
        return v * s;
    }

        /// Division by scalar.
    // XXX: should divide by the scalar type.
    GfVec4f &operator/=(double s) {
        // XXX: This should not multiply by 1/s, it should do the division.
        // Doing the division is more numerically stable when s is close to
        // zero.
        return *this *= (1.0 / s);
    }
    GfVec4f operator/(double s) const {
	return *this * (1.0 / s);
    }
    
    /// See GfDot().
    float operator*(GfVec4f const &v) const {
        return _data[0] * v[0] + _data[1] * v[1] + _data[2] * v[2] + _data[3] * v[3];
    }

    /// Returns the projection of \p this onto \p v. That is: 
    /// \code
    /// v * (*this * v)
    /// \endcode
    GfVec4f GetProjection(GfVec4f const &v) const {
        return v * (*this * v);
    }

    /// Returns the orthogonal complement of \p this->GetProjection(b). That is:
    /// \code
    ///  *this - this->GetProjection(b)
    /// \endcode
    GfVec4f GetComplement(GfVec4f const &b) const {
	return *this - this->GetProjection(b);
    }

    /// Squared length.
    float GetLengthSq() const {
        return *this * *this;
    }

    /// Length
    float GetLength() const {
        // XXX: should use GfSqrt.
        return sqrt(GetLengthSq());
    }

    /// Normalizes the vector in place to unit length, returning the
    /// length before normalization. If the length of the vector is
    /// smaller than \p eps, then the vector is set to vector/\c eps.
    /// The original length of the vector is returned. See also GfNormalize().
    ///
    /// \todo This was fixed for bug 67777. This is a gcc64 optimizer bug.
    /// By tickling the code, it no longer tries to write into
    /// an illegal memory address (in the code section of memory).
    float Normalize(float eps = GF_MIN_VECTOR_LENGTH) {
        // XXX: this seems suspect...  suggest dividing by length so long as
        // length is not zero.
        float length = GetLength();
        *this /= (length > eps) ? length : eps;
        return length;
    }

    GfVec4f GetNormalized(float eps = GF_MIN_VECTOR_LENGTH) const {
        GfVec4f normalized(*this);
        normalized.Normalize(eps);
        return normalized;
    }

  
private:
    float _data[4];
};

/// Output a GfVec4f
/// \ingroup group_gf_DebuggingOutput
std::ostream& operator<<(std::ostream &, GfVec4f const &);

#include "pxr/base/gf/vec4d.h"
#include "pxr/base/gf/vec4h.h"
#include "pxr/base/gf/vec4i.h"

/// Returns component-wise multiplication of vectors \p v1 and \p v2.
inline GfVec4f
GfCompMult(GfVec4f const &v1, GfVec4f const &v2) {
    return GfVec4f(
        v1[0] * v2[0],
        v1[1] * v2[1],
        v1[2] * v2[2],
        v1[3] * v2[3]
        );
}

/// Returns component-wise quotient of vectors \p v1 and \p v2.
inline GfVec4f
GfCompDiv(GfVec4f const &v1, GfVec4f const &v2) {
    return GfVec4f(
        v1[0] / v2[0],
        v1[1] / v2[1],
        v1[2] / v2[2],
        v1[3] / v2[3]
        );
}

/// Returns the dot (inner) product of two vectors.
inline float
GfDot(GfVec4f const &v1, GfVec4f const &v2) {
    return v1 * v2;
}



/// Returns the geometric length of \c v.
inline float
GfGetLength(GfVec4f const &v)
{
    return v.GetLength();
}

/// Normalizes \c *v in place to unit length, returning the length before
/// normalization. If the length of \c *v is smaller than \p eps then \c *v is
/// set to \c *v/eps.  The original length of \c *v is returned.
inline float
GfNormalize(GfVec4f *v, float eps = GF_MIN_VECTOR_LENGTH)
{
    return v->Normalize();
}

/// Returns a normalized (unit-length) vector with the same direction as \p v.
/// If the length of this vector is smaller than \p eps, the vector divided
/// by \p eps is returned.
inline GfVec4f
GfGetNormalized(GfVec4f const &v, float eps = GF_MIN_VECTOR_LENGTH)
{
    return v.GetNormalized(eps);
}

/// Returns the projection of \p a onto \p b. That is:
/// \code
/// b * (a * b)
/// \endcode
inline GfVec4f
GfGetProjection(GfVec4f const &a, GfVec4f const &b)
{
    return a.GetProjection(b);
}

/// Returns the orthogonal complement of \p a.GetProjection(b). That is:
/// \code
///  a - a.GetProjection(b)
/// \endcode
inline GfVec4f
GfGetComplement(GfVec4f const &a, GfVec4f const &b)
{
    return a.GetComplement(b);
}

/// Tests for equality within a given tolerance, returning \c true if the
/// length of the difference vector is less than or equal to \p tolerance.
inline bool
GfIsClose(GfVec4f const &v1, GfVec4f const &v2, double tolerance)
{
    GfVec4f delta = v1 - v2;
    return delta.GetLengthSq() <= tolerance * tolerance;
}

 
 
#endif // GF_VEC4F_H
