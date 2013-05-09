#ifndef __vtkDICOMTag_h
#define __vtkDICOMTag_h

#include <vtkSystemIncludes.h>
#include "vtkDICOMDictionary.h"

//! A (group,element) identifier tag for DICOM attributes.
class vtkDICOMTag
{
public:
  vtkDICOMTag() : Key(0) {}

  //! Construct a tag from group, element numbers.
  vtkDICOMTag(int group, int element) : Key((group << 16) | element) {}

  //! Construct a tag from an identifier from the DICOM dictionary.
  vtkDICOMTag(DC::EnumType tag) : Key(tag) {}

  //! Construct a tag object from a static tag.
  vtkDICOMTag(vtkDICOMDictionary::StaticTag tag) : Key(tag.Key) {}

  //! Get the 16-bit group identifier.
  unsigned short GetGroup() const {
    return static_cast<unsigned short>(this->Key >> 16); }

  //! Get the 16-bit element identifier.
  unsigned short GetElement() const {
    return static_cast<unsigned short>(this->Key); }

  //! Compute a hash value, used for accelerating lookups.
  unsigned int ComputeHash() const {
    unsigned int h = (((this->Key >> 6) & 0xFFFF03FF) ^ this->Key);
    return (h ^ (h >> 16)); }

  bool operator==(const vtkDICOMTag& b) const {
    return (this->Key == b.Key); }

  bool operator!=(const vtkDICOMTag& b) const {
    return (this->Key != b.Key); }

  bool operator<=(const vtkDICOMTag& b) const {
    return (this->Key <= b.Key); }

  bool operator>=(const vtkDICOMTag& b) const {
    return (this->Key >= b.Key); }

  bool operator<(const vtkDICOMTag& b) const {
    return (this->Key < b.Key); }

  bool operator>(const vtkDICOMTag& b) const {
    return (this->Key > b.Key); }

private:
  unsigned int Key;
};

ostream& operator<<(ostream& o, const vtkDICOMTag& a);

#endif /* __vtkDICOMTag_h */