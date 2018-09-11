// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: Serialization.proto

#ifndef PROTOBUF_Serialization_2eproto__INCLUDED
#define PROTOBUF_Serialization_2eproto__INCLUDED

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3004000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3004000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/generated_enum_reflection.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
namespace tutorial {
class CmdData;
class CmdDataDefaultTypeInternal;
extern CmdDataDefaultTypeInternal _CmdData_default_instance_;
class CmdData_ProductObj;
class CmdData_ProductObjDefaultTypeInternal;
extern CmdData_ProductObjDefaultTypeInternal _CmdData_ProductObj_default_instance_;
}  // namespace tutorial

namespace tutorial {

namespace protobuf_Serialization_2eproto {
// Internal implementation detail -- do not call these.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[];
  static const ::google::protobuf::uint32 offsets[];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static void InitDefaultsImpl();
};
void AddDescriptors();
void InitDefaults();
}  // namespace protobuf_Serialization_2eproto

enum CmdData_ObjName {
  CmdData_ObjName_BaseObj_Name = 0,
  CmdData_ObjName_ProductObj_Name = 1,
  CmdData_ObjName_CmdData_ObjName_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  CmdData_ObjName_CmdData_ObjName_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool CmdData_ObjName_IsValid(int value);
const CmdData_ObjName CmdData_ObjName_ObjName_MIN = CmdData_ObjName_BaseObj_Name;
const CmdData_ObjName CmdData_ObjName_ObjName_MAX = CmdData_ObjName_ProductObj_Name;
const int CmdData_ObjName_ObjName_ARRAYSIZE = CmdData_ObjName_ObjName_MAX + 1;

const ::google::protobuf::EnumDescriptor* CmdData_ObjName_descriptor();
inline const ::std::string& CmdData_ObjName_Name(CmdData_ObjName value) {
  return ::google::protobuf::internal::NameOfEnum(
    CmdData_ObjName_descriptor(), value);
}
inline bool CmdData_ObjName_Parse(
    const ::std::string& name, CmdData_ObjName* value) {
  return ::google::protobuf::internal::ParseNamedEnum<CmdData_ObjName>(
    CmdData_ObjName_descriptor(), name, value);
}
enum CmdData_CmdType {
  CmdData_CmdType_SELECT = 0,
  CmdData_CmdType_INSERT = 1,
  CmdData_CmdType_UPDATE = 2,
  CmdData_CmdType_DELETE = 3,
  CmdData_CmdType_CmdData_CmdType_INT_MIN_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32min,
  CmdData_CmdType_CmdData_CmdType_INT_MAX_SENTINEL_DO_NOT_USE_ = ::google::protobuf::kint32max
};
bool CmdData_CmdType_IsValid(int value);
const CmdData_CmdType CmdData_CmdType_CmdType_MIN = CmdData_CmdType_SELECT;
const CmdData_CmdType CmdData_CmdType_CmdType_MAX = CmdData_CmdType_DELETE;
const int CmdData_CmdType_CmdType_ARRAYSIZE = CmdData_CmdType_CmdType_MAX + 1;

const ::google::protobuf::EnumDescriptor* CmdData_CmdType_descriptor();
inline const ::std::string& CmdData_CmdType_Name(CmdData_CmdType value) {
  return ::google::protobuf::internal::NameOfEnum(
    CmdData_CmdType_descriptor(), value);
}
inline bool CmdData_CmdType_Parse(
    const ::std::string& name, CmdData_CmdType* value) {
  return ::google::protobuf::internal::ParseNamedEnum<CmdData_CmdType>(
    CmdData_CmdType_descriptor(), name, value);
}
// ===================================================================

class CmdData_ProductObj : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:tutorial.CmdData.ProductObj) */ {
 public:
  CmdData_ProductObj();
  virtual ~CmdData_ProductObj();

  CmdData_ProductObj(const CmdData_ProductObj& from);

  inline CmdData_ProductObj& operator=(const CmdData_ProductObj& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  CmdData_ProductObj(CmdData_ProductObj&& from) noexcept
    : CmdData_ProductObj() {
    *this = ::std::move(from);
  }

  inline CmdData_ProductObj& operator=(CmdData_ProductObj&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const CmdData_ProductObj& default_instance();

  static inline const CmdData_ProductObj* internal_default_instance() {
    return reinterpret_cast<const CmdData_ProductObj*>(
               &_CmdData_ProductObj_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    0;

  void Swap(CmdData_ProductObj* other);
  friend void swap(CmdData_ProductObj& a, CmdData_ProductObj& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline CmdData_ProductObj* New() const PROTOBUF_FINAL { return New(NULL); }

  CmdData_ProductObj* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const CmdData_ProductObj& from);
  void MergeFrom(const CmdData_ProductObj& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(CmdData_ProductObj* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // string tablename = 1;
  void clear_tablename();
  static const int kTablenameFieldNumber = 1;
  const ::std::string& tablename() const;
  void set_tablename(const ::std::string& value);
  #if LANG_CXX11
  void set_tablename(::std::string&& value);
  #endif
  void set_tablename(const char* value);
  void set_tablename(const char* value, size_t size);
  ::std::string* mutable_tablename();
  ::std::string* release_tablename();
  void set_allocated_tablename(::std::string* tablename);

  // string name = 3;
  void clear_name();
  static const int kNameFieldNumber = 3;
  const ::std::string& name() const;
  void set_name(const ::std::string& value);
  #if LANG_CXX11
  void set_name(::std::string&& value);
  #endif
  void set_name(const char* value);
  void set_name(const char* value, size_t size);
  ::std::string* mutable_name();
  ::std::string* release_name();
  void set_allocated_name(::std::string* name);

  // int32 id = 2;
  void clear_id();
  static const int kIdFieldNumber = 2;
  ::google::protobuf::int32 id() const;
  void set_id(::google::protobuf::int32 value);

  // int32 value = 4;
  void clear_value();
  static const int kValueFieldNumber = 4;
  ::google::protobuf::int32 value() const;
  void set_value(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:tutorial.CmdData.ProductObj)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::internal::ArenaStringPtr tablename_;
  ::google::protobuf::internal::ArenaStringPtr name_;
  ::google::protobuf::int32 id_;
  ::google::protobuf::int32 value_;
  mutable int _cached_size_;
  friend struct protobuf_Serialization_2eproto::TableStruct;
};
// -------------------------------------------------------------------

class CmdData : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:tutorial.CmdData) */ {
 public:
  CmdData();
  virtual ~CmdData();

  CmdData(const CmdData& from);

  inline CmdData& operator=(const CmdData& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  CmdData(CmdData&& from) noexcept
    : CmdData() {
    *this = ::std::move(from);
  }

  inline CmdData& operator=(CmdData&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const CmdData& default_instance();

  static inline const CmdData* internal_default_instance() {
    return reinterpret_cast<const CmdData*>(
               &_CmdData_default_instance_);
  }
  static PROTOBUF_CONSTEXPR int const kIndexInFileMessages =
    1;

  void Swap(CmdData* other);
  friend void swap(CmdData& a, CmdData& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline CmdData* New() const PROTOBUF_FINAL { return New(NULL); }

  CmdData* New(::google::protobuf::Arena* arena) const PROTOBUF_FINAL;
  void CopyFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void MergeFrom(const ::google::protobuf::Message& from) PROTOBUF_FINAL;
  void CopyFrom(const CmdData& from);
  void MergeFrom(const CmdData& from);
  void Clear() PROTOBUF_FINAL;
  bool IsInitialized() const PROTOBUF_FINAL;

  size_t ByteSizeLong() const PROTOBUF_FINAL;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) PROTOBUF_FINAL;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const PROTOBUF_FINAL;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const PROTOBUF_FINAL;
  int GetCachedSize() const PROTOBUF_FINAL { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const PROTOBUF_FINAL;
  void InternalSwap(CmdData* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const PROTOBUF_FINAL;

  // nested types ----------------------------------------------------

  typedef CmdData_ProductObj ProductObj;

  typedef CmdData_ObjName ObjName;
  static const ObjName BaseObj_Name =
    CmdData_ObjName_BaseObj_Name;
  static const ObjName ProductObj_Name =
    CmdData_ObjName_ProductObj_Name;
  static inline bool ObjName_IsValid(int value) {
    return CmdData_ObjName_IsValid(value);
  }
  static const ObjName ObjName_MIN =
    CmdData_ObjName_ObjName_MIN;
  static const ObjName ObjName_MAX =
    CmdData_ObjName_ObjName_MAX;
  static const int ObjName_ARRAYSIZE =
    CmdData_ObjName_ObjName_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  ObjName_descriptor() {
    return CmdData_ObjName_descriptor();
  }
  static inline const ::std::string& ObjName_Name(ObjName value) {
    return CmdData_ObjName_Name(value);
  }
  static inline bool ObjName_Parse(const ::std::string& name,
      ObjName* value) {
    return CmdData_ObjName_Parse(name, value);
  }

  typedef CmdData_CmdType CmdType;
  static const CmdType SELECT =
    CmdData_CmdType_SELECT;
  static const CmdType INSERT =
    CmdData_CmdType_INSERT;
  static const CmdType UPDATE =
    CmdData_CmdType_UPDATE;
  static const CmdType DELETE =
    CmdData_CmdType_DELETE;
  static inline bool CmdType_IsValid(int value) {
    return CmdData_CmdType_IsValid(value);
  }
  static const CmdType CmdType_MIN =
    CmdData_CmdType_CmdType_MIN;
  static const CmdType CmdType_MAX =
    CmdData_CmdType_CmdType_MAX;
  static const int CmdType_ARRAYSIZE =
    CmdData_CmdType_CmdType_ARRAYSIZE;
  static inline const ::google::protobuf::EnumDescriptor*
  CmdType_descriptor() {
    return CmdData_CmdType_descriptor();
  }
  static inline const ::std::string& CmdType_Name(CmdType value) {
    return CmdData_CmdType_Name(value);
  }
  static inline bool CmdType_Parse(const ::std::string& name,
      CmdType* value) {
    return CmdData_CmdType_Parse(name, value);
  }

  // accessors -------------------------------------------------------

  // .tutorial.CmdData.ProductObj product = 3;
  bool has_product() const;
  void clear_product();
  static const int kProductFieldNumber = 3;
  const ::tutorial::CmdData_ProductObj& product() const;
  ::tutorial::CmdData_ProductObj* mutable_product();
  ::tutorial::CmdData_ProductObj* release_product();
  void set_allocated_product(::tutorial::CmdData_ProductObj* product);

  // .tutorial.CmdData.ObjName name = 1;
  void clear_name();
  static const int kNameFieldNumber = 1;
  ::tutorial::CmdData_ObjName name() const;
  void set_name(::tutorial::CmdData_ObjName value);

  // .tutorial.CmdData.CmdType type = 2;
  void clear_type();
  static const int kTypeFieldNumber = 2;
  ::tutorial::CmdData_CmdType type() const;
  void set_type(::tutorial::CmdData_CmdType value);

  // @@protoc_insertion_point(class_scope:tutorial.CmdData)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::tutorial::CmdData_ProductObj* product_;
  int name_;
  int type_;
  mutable int _cached_size_;
  friend struct protobuf_Serialization_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// CmdData_ProductObj

// string tablename = 1;
inline void CmdData_ProductObj::clear_tablename() {
  tablename_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& CmdData_ProductObj::tablename() const {
  // @@protoc_insertion_point(field_get:tutorial.CmdData.ProductObj.tablename)
  return tablename_.GetNoArena();
}
inline void CmdData_ProductObj::set_tablename(const ::std::string& value) {
  
  tablename_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:tutorial.CmdData.ProductObj.tablename)
}
#if LANG_CXX11
inline void CmdData_ProductObj::set_tablename(::std::string&& value) {
  
  tablename_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:tutorial.CmdData.ProductObj.tablename)
}
#endif
inline void CmdData_ProductObj::set_tablename(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  tablename_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:tutorial.CmdData.ProductObj.tablename)
}
inline void CmdData_ProductObj::set_tablename(const char* value, size_t size) {
  
  tablename_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:tutorial.CmdData.ProductObj.tablename)
}
inline ::std::string* CmdData_ProductObj::mutable_tablename() {
  
  // @@protoc_insertion_point(field_mutable:tutorial.CmdData.ProductObj.tablename)
  return tablename_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* CmdData_ProductObj::release_tablename() {
  // @@protoc_insertion_point(field_release:tutorial.CmdData.ProductObj.tablename)
  
  return tablename_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void CmdData_ProductObj::set_allocated_tablename(::std::string* tablename) {
  if (tablename != NULL) {
    
  } else {
    
  }
  tablename_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), tablename);
  // @@protoc_insertion_point(field_set_allocated:tutorial.CmdData.ProductObj.tablename)
}

// int32 id = 2;
inline void CmdData_ProductObj::clear_id() {
  id_ = 0;
}
inline ::google::protobuf::int32 CmdData_ProductObj::id() const {
  // @@protoc_insertion_point(field_get:tutorial.CmdData.ProductObj.id)
  return id_;
}
inline void CmdData_ProductObj::set_id(::google::protobuf::int32 value) {
  
  id_ = value;
  // @@protoc_insertion_point(field_set:tutorial.CmdData.ProductObj.id)
}

// string name = 3;
inline void CmdData_ProductObj::clear_name() {
  name_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline const ::std::string& CmdData_ProductObj::name() const {
  // @@protoc_insertion_point(field_get:tutorial.CmdData.ProductObj.name)
  return name_.GetNoArena();
}
inline void CmdData_ProductObj::set_name(const ::std::string& value) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:tutorial.CmdData.ProductObj.name)
}
#if LANG_CXX11
inline void CmdData_ProductObj::set_name(::std::string&& value) {
  
  name_.SetNoArena(
    &::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::move(value));
  // @@protoc_insertion_point(field_set_rvalue:tutorial.CmdData.ProductObj.name)
}
#endif
inline void CmdData_ProductObj::set_name(const char* value) {
  GOOGLE_DCHECK(value != NULL);
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:tutorial.CmdData.ProductObj.name)
}
inline void CmdData_ProductObj::set_name(const char* value, size_t size) {
  
  name_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:tutorial.CmdData.ProductObj.name)
}
inline ::std::string* CmdData_ProductObj::mutable_name() {
  
  // @@protoc_insertion_point(field_mutable:tutorial.CmdData.ProductObj.name)
  return name_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* CmdData_ProductObj::release_name() {
  // @@protoc_insertion_point(field_release:tutorial.CmdData.ProductObj.name)
  
  return name_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void CmdData_ProductObj::set_allocated_name(::std::string* name) {
  if (name != NULL) {
    
  } else {
    
  }
  name_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), name);
  // @@protoc_insertion_point(field_set_allocated:tutorial.CmdData.ProductObj.name)
}

// int32 value = 4;
inline void CmdData_ProductObj::clear_value() {
  value_ = 0;
}
inline ::google::protobuf::int32 CmdData_ProductObj::value() const {
  // @@protoc_insertion_point(field_get:tutorial.CmdData.ProductObj.value)
  return value_;
}
inline void CmdData_ProductObj::set_value(::google::protobuf::int32 value) {
  
  value_ = value;
  // @@protoc_insertion_point(field_set:tutorial.CmdData.ProductObj.value)
}

// -------------------------------------------------------------------

// CmdData

// .tutorial.CmdData.ObjName name = 1;
inline void CmdData::clear_name() {
  name_ = 0;
}
inline ::tutorial::CmdData_ObjName CmdData::name() const {
  // @@protoc_insertion_point(field_get:tutorial.CmdData.name)
  return static_cast< ::tutorial::CmdData_ObjName >(name_);
}
inline void CmdData::set_name(::tutorial::CmdData_ObjName value) {
  
  name_ = value;
  // @@protoc_insertion_point(field_set:tutorial.CmdData.name)
}

// .tutorial.CmdData.CmdType type = 2;
inline void CmdData::clear_type() {
  type_ = 0;
}
inline ::tutorial::CmdData_CmdType CmdData::type() const {
  // @@protoc_insertion_point(field_get:tutorial.CmdData.type)
  return static_cast< ::tutorial::CmdData_CmdType >(type_);
}
inline void CmdData::set_type(::tutorial::CmdData_CmdType value) {
  
  type_ = value;
  // @@protoc_insertion_point(field_set:tutorial.CmdData.type)
}

// .tutorial.CmdData.ProductObj product = 3;
inline bool CmdData::has_product() const {
  return this != internal_default_instance() && product_ != NULL;
}
inline void CmdData::clear_product() {
  if (GetArenaNoVirtual() == NULL && product_ != NULL) delete product_;
  product_ = NULL;
}
inline const ::tutorial::CmdData_ProductObj& CmdData::product() const {
  const ::tutorial::CmdData_ProductObj* p = product_;
  // @@protoc_insertion_point(field_get:tutorial.CmdData.product)
  return p != NULL ? *p : *reinterpret_cast<const ::tutorial::CmdData_ProductObj*>(
      &::tutorial::_CmdData_ProductObj_default_instance_);
}
inline ::tutorial::CmdData_ProductObj* CmdData::mutable_product() {
  
  if (product_ == NULL) {
    product_ = new ::tutorial::CmdData_ProductObj;
  }
  // @@protoc_insertion_point(field_mutable:tutorial.CmdData.product)
  return product_;
}
inline ::tutorial::CmdData_ProductObj* CmdData::release_product() {
  // @@protoc_insertion_point(field_release:tutorial.CmdData.product)
  
  ::tutorial::CmdData_ProductObj* temp = product_;
  product_ = NULL;
  return temp;
}
inline void CmdData::set_allocated_product(::tutorial::CmdData_ProductObj* product) {
  delete product_;
  product_ = product;
  if (product) {
    
  } else {
    
  }
  // @@protoc_insertion_point(field_set_allocated:tutorial.CmdData.product)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__
#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)


}  // namespace tutorial

namespace google {
namespace protobuf {

template <> struct is_proto_enum< ::tutorial::CmdData_ObjName> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::tutorial::CmdData_ObjName>() {
  return ::tutorial::CmdData_ObjName_descriptor();
}
template <> struct is_proto_enum< ::tutorial::CmdData_CmdType> : ::google::protobuf::internal::true_type {};
template <>
inline const EnumDescriptor* GetEnumDescriptor< ::tutorial::CmdData_CmdType>() {
  return ::tutorial::CmdData_CmdType_descriptor();
}

}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_Serialization_2eproto__INCLUDED
