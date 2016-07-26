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
// vec.template.cpp file to make changes.

#include "pxr/base/gf/vec{{ SUFFIX }}.h"

#include "pxr/base/gf/math.h"
#include "pxr/base/gf/ostreamHelpers.h"
#include "pxr/base/tf/type.h"

// Include headers for other vec types to support wrapping conversions and
// operators.
{% for S in SCALARS if S != SCL -%}
#include "pxr/base/gf/vec{{ DIM }}{{ S[0] }}.h"
{% endfor %}

#include <vector>
#include <iostream>

TF_REGISTRY_FUNCTION(TfType) {
    TfType::Define<{{ VEC }}>();
}

std::ostream& 
operator<<(std::ostream &out, {{ VEC }} const &v)
{
    return out << '(' 
        << {{ LIST("Gf_OstreamHelperP(v[%(i)s])", sep=' << \", \" \n        << ') }} << ')';
}

{% if IS_FLOATING_POINT(SCL) %}
{% for S in SCALARS if S != SCL %}
{{ VEC }}::{{ VEC }}(class {{ VECNAME(DIM, S) }} const &other)
{
    {{ LIST("_data[%(i)s] = other[%(i)s];", sep='\n    ') }}
}
{% endfor %}
{% endif %}

{% for S in SCALARS if S != SCL %}
bool
{{ VEC }}::operator==({{ VECNAME(DIM, S) }} const &other) const
{
    return {{ LIST("_data[%(i)s] == other[%(i)s]", sep=' and\n           ') }};
}
{% endfor %}

{% if IS_FLOATING_POINT(SCL) and DIM == 3 %}

bool
{{ VEC }}::OrthogonalizeBasis(
    {{ VEC }} *tx, {{ VEC }} *ty, {{ VEC }} *tz,
    const bool normalize, double eps)
{
    return GfOrthogonalizeBasis(tx, ty, tz, normalize, eps);
}

void
{{ VEC }}::BuildOrthonormalFrame(
    {{ VEC }} *v1, {{ VEC }} *v2, {{ SCL }} eps) const
{
    return GfBuildOrthonormalFrame(*this, v1, v2, eps);
}

/*
 * Given 3 basis vectors *tx, *ty, *tz, orthogonalize and optionally normalize
 * them.
 *
 * This uses an iterative method that is very stable even when the vectors
 * are far from orthogonal (close to colinear).  The number of iterations
 * and thus the computation time does increase as the vectors become
 * close to colinear, however.
 *
 * If the iteration fails to converge, returns false with vectors as close to
 * orthogonal as possible.
 */
bool
GfOrthogonalizeBasis({{ VEC }} *tx, {{ VEC }} *ty, {{ VEC }} *tz,
                     bool normalize, double eps)
{
    {{ VEC }} ax,bx,cx,ay,by,cy,az,bz,cz;

    if (normalize) {
	GfNormalize(tx);
	GfNormalize(ty);
	GfNormalize(tz);
	ax = *tx;
	ay = *ty;
	az = *tz;
    } else {
	ax = *tx;
	ay = *ty;
	az = *tz;
	ax.Normalize();
	ay.Normalize();
	az.Normalize();
    }

    /* Check for colinear vectors. This is not only a quick-out: the
     * error computation below will evaluate to zero if there's no change
     * after an iteration, which can happen either because we have a good
     * solution or because the vectors are colinear.   So we have to check
     * the colinear case beforehand, or we'll get fooled in the error
     * computation.
     */
    if (GfIsClose(ax,ay,eps) || GfIsClose(ax,az,eps) || GfIsClose(ay,az,eps)) {
	return false;
    }

    const int MAX_ITERS = 20;
    int iter;
    for (iter = 0; iter < MAX_ITERS; ++iter) {
	bx = *tx;
	by = *ty;
	bz = *tz;

	bx -= GfDot(ay,bx) * ay;
	bx -= GfDot(az,bx) * az;

	by -= GfDot(ax,by) * ax;
	by -= GfDot(az,by) * az;

	bz -= GfDot(ax,bz) * ax;
	bz -= GfDot(ay,bz) * ay;

	cx = 0.5*(*tx + bx);
	cy = 0.5*(*ty + by);
	cz = 0.5*(*tz + bz);

	if (normalize) {
            cx.Normalize();
            cy.Normalize();
            cz.Normalize();
	}

	{{ VEC }} xDiff = *tx - cx;
	{{ VEC }} yDiff = *ty - cy;
	{{ VEC }} zDiff = *tz - cz;

	double error =
            GfDot(xDiff,xDiff) + GfDot(yDiff,yDiff) + GfDot(zDiff,zDiff);

	// error is squared, so compare to squared tolerance
	if (error < GfSqr(eps))
	    break;

	*tx = cx;
	*ty = cy;
	*tz = cz;

	ax = *tx;
	ay = *ty;
	az = *tz;

	if (!normalize) {
            ax.Normalize();
            ay.Normalize();
            az.Normalize();
	}
    }

    return iter < MAX_ITERS;
}

/*
 * BuildOrthonormalFrame constructs two unit vectors *v1 and *v2,
 * with *v1 and *v2 perpendicular to each other and (*this).
 * We arbitrarily cross *this with the X axis to form *v1,
 * and if the result is degenerate, we set *v1 = (Y axis) X *this.
 * If L = length(*this) < eps, we shrink v1 and v2 to be of
 * length L/eps.
 */
void
GfBuildOrthonormalFrame({{ VEC }} const &v0,
                        {{ VEC }}* v1,
                        {{ VEC }}* v2, {{ SCL }} eps)
{
    {{ SCL }} len = v0.GetLength();

    if (len == 0.) {
	*v1 = *v2 = {{ VEC }}(0);
    }
    else {
	{{ VEC }} unitDir = v0 / len;
	*v1 = {{ VEC }}::XAxis() ^ unitDir;

	if (GfSqr(*v1) < GfSqr(1e-4))
	    *v1 = {{ VEC }}::YAxis() ^ unitDir;

        GfNormalize(v1);
	*v2 = unitDir ^ *v1;	// this is of unit length

	if (len < eps) {
	    double  desiredLen = len / eps;
	    *v1 *= desiredLen;
	    *v2 *= desiredLen;
	}
    }
}

{{ VEC }}
GfSlerp(double alpha, const {{ VEC }} &v0, const {{ VEC }} &v1)
{
    // determine the angle between the two lines going from the center of
    // the sphere to v0 and v1.  the projection (dot prod) of one onto the
    // other gives us the arc cosine of the angle between them.
    double angle = acos(GfClamp((double)GfDot(v0, v1), -1.0, 1.0));

    // Check for very small angle between the vectors, and if so, just lerp them.
    // XXX: This value for epsilon is somewhat arbitrary, and if
    // someone can derive a more meaningful value, that would be fine.
    if ( fabs(angle) < 0.001 ) {
        return GfLerp(alpha, v0, v1);
    }

    // compute the sin of the angle, we need it a couple of places
    double sinAngle = sin(angle);

    // Check if the vectors are nearly opposing, and if so,
    // compute an arbitrary orthogonal vector to interpolate across.
    // XXX: Another somewhat arbitrary test for epsilon, but trying to stay
    // within reasonable float precision.
    if ( fabs(sinAngle) < 0.00001 ) {
        {{ VEC }} vX, vY;
        v0.BuildOrthonormalFrame(&vX, &vY);
        {{ VEC }} v = v0 * cos(alpha*M_PI) + vX * sin(alpha*M_PI);
        return v;
    }

    // interpolate
    double oneOverSinAngle = 1.0 / sinAngle;

    return
        v0 * (sin((1.0-alpha)*angle) * oneOverSinAngle) +
        v1 * (sin(     alpha *angle) * oneOverSinAngle);
}

{% endif %}

