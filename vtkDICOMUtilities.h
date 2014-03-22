/*=========================================================================

  Program: DICOM for VTK

  Copyright (c) 2012-2014 David Gobbi
  All rights reserved.
  See Copyright.txt or http://dgobbi.github.io/bsd3.txt for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef __vtkDICOMUtilities_h
#define __vtkDICOMUtilities_h

#include <vtkSystemIncludes.h>
#include <vtkObject.h>
#include "vtkDICOMModule.h"
#include "vtkDICOMTag.h"

#include <string>

class vtkStringArray;

//! Utility functions for use with DICOM classes.
class VTK_DICOM_EXPORT vtkDICOMUtilities : public vtkObject
{
public:
  //! VTK dynamic type information macro.
  vtkTypeMacro(vtkDICOMUtilities, vtkObject);

  //! Set a UID prefix to use when generating UIDs.
  /*!
   *  This is optional, if you do not own a UID prefix then the publicly
   *  available 2.25 prefix will be used.
   */
  static void SetUIDPrefix(const char *prefix);
  static const char *GetUIDPrefix();

  //! Generate a UID for the provided tag.
  static std::string GenerateUID(vtkDICOMTag tag);

  //! Generate a series of UIDs, sorted from low to high.
  /*!
   *  Before passing the string array, call SetNumberOfValues() on
   *  the array to specify the number of UIDs that you want to be
   *  stored in it.  The stored UIDs will be sorted, low to high.
   *  Generating a batch of UIDs is more efficient than calling
   *  GenerateUID() repeatedly.
   */
  static void GenerateUIDs(vtkDICOMTag tag, vtkStringArray *uids);

  //! Numerically compare two UIDs, returns -1, 0, or +1.
  static int CompareUIDs(const char *u1, const char *u2);

  //! Generate a DICOM date time string in the given timezone.
  /*!
   *  The time zone is to be given in the DICOM format of
   *  +HHMM or -HHMM where HH is the hour offset and MM is the
   *  minute offset.  The sign is mandatory and cannot be omitted.
   */
  static std::string GenerateDateTime(const char *zone);

  //! Check if the specified file is a DICOM file.
  /*!
   *  This will return true if the file exists, is readable, and
   *  if it has the DICM magic number or if the first few bytes of
   *  the file look like DICOM data elements.
   */
  static bool IsDICOMFile(const char *filename);

  //! Get the UID for this DICOM implementation.
  static const char *GetImplementationClassUID();

  //! Set the UID for this DICOM implementation.
  /*!
   *  The supplied UID will be copied into a static storage area,
   *  and used for all future calls to GetImplementationClassUID.
   *  The ImplementationClassUID appears in the DICOM meta header.
   */
  static void SetImplementationClassUID(const char *uid);

  //! Get the versioned name for this DICOM implementation.
  static const char *GetImplementationVersionName();

  //! Set the versioned name for this DICOM implementation.
  /*!
   *  The supplied name will be copied into a static storage area,
   *  and used for all future calls to GetImplementationVersionName.
   *  The ImplementationVersionName appears in the DICOM meta header.
   */
  static void SetImplementationVersionName(const char *name);

  //! Set whether to resume IO after a singal occurs.
  /*!
   *  This is a global setting for DICOM IO operations, and is only useful
   *  for programs that have signal handlers installed.  A signal handler
   *  can clear this flag in order to make pending IO operations fail.  If
   *  a signal handler does not clear this flag, then pending IO operations
   *  will resume after the signal.  This has no effect on non-POSIX systems.
   */
  static void SetRetryOnEINTR(bool v);
  static bool GetRetryOnEINTR();

protected:
  vtkDICOMUtilities();
  ~vtkDICOMUtilities();

  static char UIDPrefix[64];
  static char ImplementationClassUID[65];
  static char ImplementationVersionName[17];
  static bool RetryOnEINTR;

private:
  vtkDICOMUtilities(const vtkDICOMUtilities&);  // Not implemented.
  void operator=(const vtkDICOMUtilities&);  // Not implemented.
};

#endif /* __vtkDICOMUtilities_h */
