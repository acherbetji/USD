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
// matrix3.template.h file to make changes.

#ifndef GF_MATRIX3D_H
#define GF_MATRIX3D_H

#include "pxr/base/gf/matrixData.h"
#include "pxr/base/gf/vec3d.h"
#include "pxr/base/gf/traits.h"

#include <boost/functional/hash.hpp>

#include <iosfwd>
#include <vector>

/// \file matrix3d.h
/// \ingroup group_gf_LinearAlgebra
///

template <>
struct GfIsGfMatrix<class GfMatrix3d> { static const bool value = true; };

class GfMatrix3d;
class GfMatrix3f;
class GfRotation;
class GfQuaternion;

/// \class GfMatrix3d matrix3d.h "pxr/base/gf/matrix3d.h"
/// \ingroup group_gf_LinearAlgebra
/// \brief Stores a 3x3 matrix of \c double elements. A basic type.
///
/// Matrices are defined to be in row-major order, so <c>matrix[i][j]</c> 
/// indexes the element in the \e i th row and the \e j th column.
///
/// <h3>3D Transformations</h3>
///
/// Three methods, SetRotate(), SetScale(), and ExtractRotation(), interpret
/// a GfMatrix3d as a 3D transformation. By convention, vectors are treated
/// primarily as row vectors, implying the following:
///
/// \li Transformation matrices are organized to deal with row
///        vectors, not column vectors.
/// \li Each of the Set() methods in this class completely rewrites the
///        matrix; for example, SetRotate() yields a matrix
///        which does nothing but rotate.
/// \li When multiplying two transformation matrices, the matrix
///        on the left applies a more local transformation to a row
///        vector. For example, if R represents a rotation
///        matrix and S represents a scale matrix, the
///        product R*S  will rotate a row vector, then scale
///        it.
class GfMatrix3d
{
public:
    typedef double ScalarType;

    static const size_t numRows = 3;
    static const size_t numColumns = 3;

    /// Default constructor. Leaves the matrix component values
    /// undefined.
    GfMatrix3d() {}

    /// Constructor. Initializes the matrix from 9 independent
    /// \c double values, specified in row-major order. For example,
    /// parameter \e m10 specifies the value in row 1 and column 0.
    GfMatrix3d(double m00, double m01, double m02, 
               double m10, double m11, double m12, 
               double m20, double m21, double m22) {
        Set(m00, m01, m02, 
            m10, m11, m12, 
            m20, m21, m22);
    }

    /// Constructor. Initializes the matrix from a 3x3 array of
    /// \c double values, specified in row-major order.
    GfMatrix3d(const double m[3][3]) {
        Set(m);
    }

    /// Constructor. Explicitly initializes the matrix to \e s times
    /// the identity matrix.
    explicit GfMatrix3d(double s) {
        SetDiagonal(s);
    }

    /// This explicit constructor initializes the matrix to \p s times
    /// the identity matrix.
    explicit GfMatrix3d(int s) {
	SetDiagonal(s);
    }

    /// Constructor. Explicitly initializes the matrix to diagonal form,
    /// with the \e i th element on the diagonal set to <c>v[i]</c>.
    explicit GfMatrix3d(const GfVec3d& v) {
        SetDiagonal(v);
    }

    /// Constructor.  Initialize the matrix from a vector of vectors of double.
    /// The vector is expected to be 3x3.  If it is too big, only the first
    /// 3 rows and/or columns will be used.  If it is too small, uninitialized
    /// elements will be filled in with the corresponding elements from an
    /// identity matrix.
    ///
    explicit GfMatrix3d(const std::vector< std::vector<double> >& v);

    /// Constructor.  Initialize the matrix from a vector of vectors of float.
    /// The vector is expected to be 3x3.  If it is too big, only the first
    /// 3 rows and/or columns will be used.  If it is too small, uninitialized
    /// elements will be filled in with the corresponding elements from an
    /// identity matrix.
    ///
    explicit GfMatrix3d(const std::vector< std::vector<float> >& v);

    /// Constructor. Initialize matrix from rotation.
    GfMatrix3d(const GfRotation& rot);

    //!
    // This explicit constructor converts a "float" matrix to a "double" matrix.
    explicit GfMatrix3d(const class GfMatrix3f& m);

    /// Sets a row of the matrix from a Vec3.
    void SetRow(int i, const GfVec3d & v) {
        _mtx[i][0] = v[0];
        _mtx[i][1] = v[1];
        _mtx[i][2] = v[2];
    }

    /// Sets a column of the matrix from a Vec3.
    void SetColumn(int i, const GfVec3d & v) {
        _mtx[0][i] = v[0];
        _mtx[1][i] = v[1];
        _mtx[2][i] = v[2];
    }

    /// Gets a row of the matrix as a Vec3.
    GfVec3d GetRow(int i) const {
        return GfVec3d(_mtx[i][0], _mtx[i][1], _mtx[i][2]);
    }

    /// Gets a column of the matrix as a Vec3.
    GfVec3d GetColumn(int i) const {
        return GfVec3d(_mtx[0][i], _mtx[1][i], _mtx[2][i]);
    }

    /// \brief Sets the matrix from 9 independent \c double values, specified
    /// in row-major order. For example, parameter \e m10 specifies the
    /// value in row 1 and column 0.
    GfMatrix3d& Set(double m00, double m01, double m02, 
                    double m10, double m11, double m12, 
                    double m20, double m21, double m22) {
        _mtx[0][0] = m00; _mtx[0][1] = m01; _mtx[0][2] = m02; 
        _mtx[1][0] = m10; _mtx[1][1] = m11; _mtx[1][2] = m12; 
        _mtx[2][0] = m20; _mtx[2][1] = m21; _mtx[2][2] = m22;
        return *this;
    }

    /// \brief Sets the matrix from a 3x3 array of \c double values, specified
    /// in row-major order.
    GfMatrix3d& Set(const double m[3][3]) {
        _mtx[0][0] = m[0][0];
        _mtx[0][1] = m[0][1];
        _mtx[0][2] = m[0][2];
        _mtx[1][0] = m[1][0];
        _mtx[1][1] = m[1][1];
        _mtx[1][2] = m[1][2];
        _mtx[2][0] = m[2][0];
        _mtx[2][1] = m[2][1];
        _mtx[2][2] = m[2][2];
        return *this;
    }

    /// Sets the matrix to the identity matrix.
    GfMatrix3d& SetIdentity() {
        return SetDiagonal(1);
    }

    /// Sets the matrix to zero.
    GfMatrix3d& SetZero() {
        return SetDiagonal(0);
    }

    /// Sets the matrix to \e s times the identity matrix.
    GfMatrix3d& SetDiagonal(double s);

    /// Sets the matrix to have diagonal (<c>v[0], v[1], v[2]</c>).
    GfMatrix3d& SetDiagonal(const GfVec3d&);

    /// Fills a 3x3 array of \c double values with the values in
    /// the matrix, specified in row-major order.
    double* Get(double m[3][3]);

    /// Returns vector components as an array of \c double values.
    double* GetArray()  {
        return _mtx.GetData();
    }

    /// Returns vector components as a const array of \c double values.
    const double* GetArray() const {
        return _mtx.GetData();
    }
    
    /// Accesses an indexed row \e i of the matrix as an array of 3 \c double
    /// values so that standard indexing (such as <c>m[0][1]</c>) works
    /// correctly.
    double* operator [](int i) { return _mtx[i]; }

    /// Accesses an indexed row \e i of the matrix as an array of 3 \c double
    /// values so that standard indexing (such as <c>m[0][1]</c>) works
    /// correctly.
    const double* operator [](int i) const { return _mtx[i]; }

    /// Hash.
    friend inline size_t hash_value(GfMatrix3d const &m) {
        int nElems = 3 * 3;
        size_t h = 0;
        const double *p = m.GetArray();
        while (nElems--)
            boost::hash_combine(h, *p++);
        return h;
    }        

    /// Tests for element-wise matrix equality. All elements must match
    /// exactly for matrices to be considered equal.
    bool operator ==(const GfMatrix3d& m) const;

    /// Tests for element-wise matrix equality. All elements must match
    /// exactly for matrices to be considered equal.
    bool operator ==(const GfMatrix3f& m) const;

    /// Tests for element-wise matrix inequality. All elements must match
    /// exactly for matrices to be considered equal.
    bool operator !=(const GfMatrix3d& m) const {
        return !(*this == m);
    }

    /// Tests for element-wise matrix inequality. All elements must match
    /// exactly for matrices to be considered equal.
    bool operator !=(const GfMatrix3f& m) const {
        return !(*this == m);
    }

    /// Returns the transpose of the matrix.
    GfMatrix3d GetTranspose() const;

    /// Returns the inverse of the matrix, or FLT_MAX * SetIdentity() if the
    /// matrix is singular. (FLT_MAX is the largest value a \c float can have, 
    /// as defined by the system.) The matrix is considered singular if the 
    /// determinant is less than or equal to the optional parameter \e eps.
    /// If \e det is non-null, <c>*det</c> is set to the determinant.
    GfMatrix3d GetInverse(double* det = NULL, double eps = 0) const;

    /// Returns the determinant of the matrix.
    double GetDeterminant() const;

    /// Makes the matrix orthonormal in place. This is an iterative method that
    /// is much more stable than the previous cross/cross method.  If the
    /// iterative method does not converge, a warning is issued.
    ///
    /// Returns true if the iteration converged, false otherwise.  Leaves any
    /// translation part of the matrix unchanged.  If \a issueWarning is true,
    /// this method will issue a warning if the iteration does not converge,
    /// otherwise it will be silent.
    bool Orthonormalize(bool issueWarning=true);

    /// Returns an orthonormalized copy of the matrix.
    GfMatrix3d GetOrthonormalized(bool issueWarning=true) const;

    /// Returns the sign of the determinant of the matrix, i.e. 1 for a
    /// right-handed matrix, -1 for a left-handed matrix, and 0 for a
    /// singular matrix.
    double GetHandedness() const;

    /// Returns true if the vectors in the matrix form a right-handed
    /// coordinate system.
    bool IsRightHanded() const {
        return GetHandedness() == 1.0;
    }

    /// Returns true if the vectors in matrix form a left-handed
    /// coordinate system.
    bool IsLeftHanded() const {
        return GetHandedness() == -1.0;
    }

    /// Post-multiplies matrix \e m into this matrix.
    GfMatrix3d& operator *=(const GfMatrix3d& m);

    /// Multiplies the matrix by a double.
    GfMatrix3d& operator *=(double);

    ///
    // Returns the product of a matrix and a double.
    friend GfMatrix3d operator *(const GfMatrix3d& m1, double d)
    {
	GfMatrix3d m = m1;
	return m *= d;
    }

    ///
    // Returns the product of a matrix and a double.
    friend GfMatrix3d operator *(double d, const GfMatrix3d& m)
    {
        return m * d;
    }

    /// Adds matrix \e m to this matrix.
    GfMatrix3d& operator +=(const GfMatrix3d& m);

    /// Subtracts matrix \e m from this matrix.
    GfMatrix3d& operator -=(const GfMatrix3d& m);

    /// Returns the unary negation of matrix \e m.
    friend GfMatrix3d operator -(const GfMatrix3d& m);

    /// Adds matrix \e m2 to \e m1
    friend GfMatrix3d operator +(const GfMatrix3d& m1, const GfMatrix3d& m2)
    {
        GfMatrix3d tmp(m1);
        tmp += m2;
        return tmp;
    }

    /// Subtracts matrix \e m2 from \e m1
    friend GfMatrix3d operator -(const GfMatrix3d& m1, const GfMatrix3d& m2)
    {
        GfMatrix3d tmp(m1);
        tmp -= m2;
        return tmp;
    }
    
    /// Multiplies matrix \e m1 by \e m2
    friend GfMatrix3d operator *(const GfMatrix3d& m1, const GfMatrix3d& m2)
    {
        GfMatrix3d tmp(m1);
        tmp *= m2;
        return tmp;
    }

    /// Divides matrix \e m1 by \e m2 (that is, <c>m1 * inv(m2)</c>).
    friend GfMatrix3d operator /(const GfMatrix3d& m1, const GfMatrix3d& m2)
    {
        return(m1 * m2.GetInverse());
    }

    /// Returns the product of a matrix \e m and a column vector \e vec.
    friend inline GfVec3d operator *(const GfMatrix3d& m, const GfVec3d& vec) {
        return GfVec3d(vec[0] * m._mtx[0][0] + vec[1] * m._mtx[0][1] + vec[2] * m._mtx[0][2],
                       vec[0] * m._mtx[1][0] + vec[1] * m._mtx[1][1] + vec[2] * m._mtx[1][2],
                       vec[0] * m._mtx[2][0] + vec[1] * m._mtx[2][1] + vec[2] * m._mtx[2][2]);
    }

    /// Returns the product of row vector \e vec and a matrix \e m.
    friend inline GfVec3d operator *(const GfVec3d &vec, const GfMatrix3d& m) {
        return GfVec3d(vec[0] * m._mtx[0][0] + vec[1] * m._mtx[1][0] + vec[2] * m._mtx[2][0],
                       vec[0] * m._mtx[0][1] + vec[1] * m._mtx[1][1] + vec[2] * m._mtx[2][1],
                       vec[0] * m._mtx[0][2] + vec[1] * m._mtx[1][2] + vec[2] * m._mtx[2][2]);
    }

    /// Returns the product of a matrix \e m and a column vector \e vec.
    /// Note that the return type is a \c GfVec3f.
    friend GfVec3f operator *(const GfMatrix3d& m, const GfVec3f& vec);

    /// Returns the product of row vector \e vec and a matrix \e m.
    /// Note that the return type is a \c GfVec3f.
    friend GfVec3f operator *(const GfVec3f &vec, const GfMatrix3d& m);

    /// Sets matrix to specify a uniform scaling by \e scaleFactor.
    GfMatrix3d& SetScale(double scaleFactor);

    /// \name 3D Transformation Utilities
    /// @{

    /// Sets the matrix to specify a rotation equivalent to \e rot.
    GfMatrix3d& SetRotate(const GfRotation &rot);

    /// Sets the matrix to specify a nonuniform scaling in x, y, and z by
    /// the factors in vector \e scaleFactors.
    GfMatrix3d& SetScale(const GfVec3d &scaleFactors);

    /// Returns the rotation corresponding to this matrix. This works
    /// well only if the matrix represents a rotation.
    ///
    /// For good results, consider calling Orthonormalize() before calling
    /// this method.
    GfRotation ExtractRotation() const;

    /// Decompose the rotation corresponding to this matrix about 3
    /// orthogonal axes.  If the axes are not orthogonal, warnings
    /// will be spewed.
    ///
    /// This is a convenience method that is equivalent to calling
    /// ExtractRotation().Decompose().
    GfVec3d DecomposeRotation(const GfVec3d &axis0,
                              const GfVec3d &axis1,
                              const GfVec3d &axis2 ) const;

    /// Returns the quaternion corresponding to this matrix. This works
    /// well only if the matrix represents a rotation.
    ///
    /// For good results, consider calling Orthonormalize() before calling
    /// this method.
    GfQuaternion ExtractRotationQuaternion() const;

    /// @}

private:
    /// Matrix storage, in row-major order.
    GfMatrixData<double, 3, 3> _mtx;

    // Friend declarations
    friend class GfMatrix3f;
};

/// Output a GfMatrix3d
/// \ingroup group_gf_DebuggingOutput
std::ostream& operator<<(std::ostream &, GfMatrix3d const &);

#endif // GF_MATRIX3D_H
