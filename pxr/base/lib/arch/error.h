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
#ifndef ARCH_ERROR_H
#define ARCH_ERROR_H

#include "pxr/base/arch/defines.h"
#include "pxr/base/arch/functionLite.h"
#include <stddef.h>

/*no!
 * Note: this is an internal (i.e. lib/arch only) header file.
 * Doxygen is off deliberately (until we get \internal working correctly).
 *
 * \file arch/error.h
 * \brief Low-level fatal error reporting.
 * \ingroup group_arch_Diagnostics
 */

/*no!
 * \brief Print message to standard error and abort program.
 * \ingroup group_arch_Diagnostics
 *
 * \param msg The reason for the failure.
 * \param funcName The name of the function that \c Arch_Error was called from.
 * \param lineNo The line number of the file that \c Arch_Error was called from.
 * \param fileName The name of the file that \c Arch_Error was called from.
 *
 * \remark
 * This function is usually called via the ARCH_ERROR macro.
 */
void Arch_Error(const char* msg, const char* funcName,
                size_t lineNo, const char* fileName);

/*no!
 * \brief Print warning message to standard error, but continue execution.
 * \ingroup group_arch_Diagnostics
 *
 * \param msg The reason for the warning.
 * \param funcName The name of the function that \c Arch_Warning was called from.
 * \param lineNo The line number of the file that \c Arch_Warning was called from.
 * \param fileName The name of the file that \c Arch_Warning was called from.
 *
 * \remark
 * This function is usually called via the ARCH_WARNING macro.
 */
void Arch_Warning(const char* msg, const char* funcName,
                  size_t lineNo, const char* fileName);

/*no!
 * \hideinitializer
 * \brief Unconditionally aborts the program.
 * \ingroup group_arch_Diagnostics
 *
 * \param msg is a literal string, a \c const \c char* (but not
 *        an \c std::string) that describes why the program is aborting.
 */
#define ARCH_ERROR(msg)    Arch_Error(msg, __ARCH_FUNCTION__, __LINE__, BUILD_COMPONENT_SRC_PREFIX __FILE__)

/*no!
 * \hideinitializer
 * \brief Prints a warning message to stderr.
 * \ingroup group_arch_Diagnostics
 *
 * \param msg is a literal string, a \c const \c char* (but not
 *        an \c std::string).
 */
#define ARCH_WARNING(msg)  Arch_Warning(msg, __ARCH_FUNCTION__, __LINE__, BUILD_COMPONENT_SRC_PREFIX __FILE__)

#define ARCH_AXIOM(cond)   if (!(cond)) ARCH_ERROR("[" #cond "] axiom failed")

#endif // ARCH_ERROR_H
