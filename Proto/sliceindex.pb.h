// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: sliceindex.proto

#ifndef PROTOBUF_INCLUDED_sliceindex_2eproto
#define PROTOBUF_INCLUDED_sliceindex_2eproto

#include <string>

#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 3006001
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 3006001 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_table_driven.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/inlined_string_field.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#define PROTOBUF_INTERNAL_EXPORT_protobuf_sliceindex_2eproto 

namespace protobuf_sliceindex_2eproto {
// Internal implementation detail -- do not use these members.
struct TableStruct {
  static const ::google::protobuf::internal::ParseTableField entries[];
  static const ::google::protobuf::internal::AuxillaryParseTableField aux[];
  static const ::google::protobuf::internal::ParseTable schema[1];
  static const ::google::protobuf::internal::FieldMetadata field_metadata[];
  static const ::google::protobuf::internal::SerializationTable serialization_table[];
  static const ::google::protobuf::uint32 offsets[];
};
void AddDescriptors();
}  // namespace protobuf_sliceindex_2eproto
namespace sliceindex {
class SliceIdArray;
class SliceIdArrayDefaultTypeInternal;
extern SliceIdArrayDefaultTypeInternal _SliceIdArray_default_instance_;
}  // namespace sliceindex
namespace google {
namespace protobuf {
template<> ::sliceindex::SliceIdArray* Arena::CreateMaybeMessage<::sliceindex::SliceIdArray>(Arena*);
}  // namespace protobuf
}  // namespace google
namespace sliceindex {

// ===================================================================

class SliceIdArray : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:sliceindex.SliceIdArray) */ {
 public:
  SliceIdArray();
  virtual ~SliceIdArray();

  SliceIdArray(const SliceIdArray& from);

  inline SliceIdArray& operator=(const SliceIdArray& from) {
    CopyFrom(from);
    return *this;
  }
  #if LANG_CXX11
  SliceIdArray(SliceIdArray&& from) noexcept
    : SliceIdArray() {
    *this = ::std::move(from);
  }

  inline SliceIdArray& operator=(SliceIdArray&& from) noexcept {
    if (GetArenaNoVirtual() == from.GetArenaNoVirtual()) {
      if (this != &from) InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }
  #endif
  static const ::google::protobuf::Descriptor* descriptor();
  static const SliceIdArray& default_instance();

  static void InitAsDefaultInstance();  // FOR INTERNAL USE ONLY
  static inline const SliceIdArray* internal_default_instance() {
    return reinterpret_cast<const SliceIdArray*>(
               &_SliceIdArray_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  void Swap(SliceIdArray* other);
  friend void swap(SliceIdArray& a, SliceIdArray& b) {
    a.Swap(&b);
  }

  // implements Message ----------------------------------------------

  inline SliceIdArray* New() const final {
    return CreateMaybeMessage<SliceIdArray>(NULL);
  }

  SliceIdArray* New(::google::protobuf::Arena* arena) const final {
    return CreateMaybeMessage<SliceIdArray>(arena);
  }
  void CopyFrom(const ::google::protobuf::Message& from) final;
  void MergeFrom(const ::google::protobuf::Message& from) final;
  void CopyFrom(const SliceIdArray& from);
  void MergeFrom(const SliceIdArray& from);
  void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input) final;
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const final;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* target) const final;
  int GetCachedSize() const final { return _cached_size_.Get(); }

  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(SliceIdArray* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return NULL;
  }
  inline void* MaybeArenaPtr() const {
    return NULL;
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // repeated uint64 ids = 1;
  int ids_size() const;
  void clear_ids();
  static const int kIdsFieldNumber = 1;
  ::google::protobuf::uint64 ids(int index) const;
  void set_ids(int index, ::google::protobuf::uint64 value);
  void add_ids(::google::protobuf::uint64 value);
  const ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >&
      ids() const;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >*
      mutable_ids();

  // @@protoc_insertion_point(class_scope:sliceindex.SliceIdArray)
 private:

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::RepeatedField< ::google::protobuf::uint64 > ids_;
  mutable int _ids_cached_byte_size_;
  mutable ::google::protobuf::internal::CachedSize _cached_size_;
  friend struct ::protobuf_sliceindex_2eproto::TableStruct;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// SliceIdArray

// repeated uint64 ids = 1;
inline int SliceIdArray::ids_size() const {
  return ids_.size();
}
inline void SliceIdArray::clear_ids() {
  ids_.Clear();
}
inline ::google::protobuf::uint64 SliceIdArray::ids(int index) const {
  // @@protoc_insertion_point(field_get:sliceindex.SliceIdArray.ids)
  return ids_.Get(index);
}
inline void SliceIdArray::set_ids(int index, ::google::protobuf::uint64 value) {
  ids_.Set(index, value);
  // @@protoc_insertion_point(field_set:sliceindex.SliceIdArray.ids)
}
inline void SliceIdArray::add_ids(::google::protobuf::uint64 value) {
  ids_.Add(value);
  // @@protoc_insertion_point(field_add:sliceindex.SliceIdArray.ids)
}
inline const ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >&
SliceIdArray::ids() const {
  // @@protoc_insertion_point(field_list:sliceindex.SliceIdArray.ids)
  return ids_;
}
inline ::google::protobuf::RepeatedField< ::google::protobuf::uint64 >*
SliceIdArray::mutable_ids() {
  // @@protoc_insertion_point(field_mutable_list:sliceindex.SliceIdArray.ids)
  return &ids_;
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace sliceindex

// @@protoc_insertion_point(global_scope)

#endif  // PROTOBUF_INCLUDED_sliceindex_2eproto