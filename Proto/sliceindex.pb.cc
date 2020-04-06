// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: sliceindex.proto

#include "sliceindex.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/stubs/port.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// This is a temporary google only hack
#ifdef GOOGLE_PROTOBUF_ENFORCE_UNIQUENESS
#include "third_party/protobuf/version.h"
#endif
// @@protoc_insertion_point(includes)

namespace sliceindex {
class SliceIdArrayDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<SliceIdArray>
      _instance;
} _SliceIdArray_default_instance_;
}  // namespace sliceindex
namespace protobuf_sliceindex_2eproto {
static void InitDefaultsSliceIdArray() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::sliceindex::_SliceIdArray_default_instance_;
    new (ptr) ::sliceindex::SliceIdArray();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::sliceindex::SliceIdArray::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_SliceIdArray =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsSliceIdArray}, {}};

void InitDefaults() {
  ::google::protobuf::internal::InitSCC(&scc_info_SliceIdArray.base);
}

::google::protobuf::Metadata file_level_metadata[1];

const ::google::protobuf::uint32 TableStruct::offsets[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::sliceindex::SliceIdArray, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  GOOGLE_PROTOBUF_GENERATED_MESSAGE_FIELD_OFFSET(::sliceindex::SliceIdArray, ids_),
};
static const ::google::protobuf::internal::MigrationSchema schemas[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, sizeof(::sliceindex::SliceIdArray)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::sliceindex::_SliceIdArray_default_instance_),
};

void protobuf_AssignDescriptors() {
  AddDescriptors();
  AssignDescriptors(
      "sliceindex.proto", schemas, file_default_instances, TableStruct::offsets,
      file_level_metadata, NULL, NULL);
}

void protobuf_AssignDescriptorsOnce() {
  static ::google::protobuf::internal::once_flag once;
  ::google::protobuf::internal::call_once(once, protobuf_AssignDescriptors);
}

void protobuf_RegisterTypes(const ::std::string&) GOOGLE_PROTOBUF_ATTRIBUTE_COLD;
void protobuf_RegisterTypes(const ::std::string&) {
  protobuf_AssignDescriptorsOnce();
  ::google::protobuf::internal::RegisterAllTypes(file_level_metadata, 1);
}

void AddDescriptorsImpl() {
  InitDefaults();
  static const char descriptor[] GOOGLE_PROTOBUF_ATTRIBUTE_SECTION_VARIABLE(protodesc_cold) = {
      "\n\020sliceindex.proto\022\nsliceindex\"\033\n\014SliceI"
      "dArray\022\013\n\003ids\030\001 \003(\004b\006proto3"
  };
  ::google::protobuf::DescriptorPool::InternalAddGeneratedFile(
      descriptor, 67);
  ::google::protobuf::MessageFactory::InternalRegisterGeneratedFile(
    "sliceindex.proto", &protobuf_RegisterTypes);
}

void AddDescriptors() {
  static ::google::protobuf::internal::once_flag once;
  ::google::protobuf::internal::call_once(once, AddDescriptorsImpl);
}
// Force AddDescriptors() to be called at dynamic initialization time.
struct StaticDescriptorInitializer {
  StaticDescriptorInitializer() {
    AddDescriptors();
  }
} static_descriptor_initializer;
}  // namespace protobuf_sliceindex_2eproto
namespace sliceindex {

// ===================================================================

void SliceIdArray::InitAsDefaultInstance() {
}
#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int SliceIdArray::kIdsFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

SliceIdArray::SliceIdArray()
  : ::google::protobuf::Message(), _internal_metadata_(NULL) {
  ::google::protobuf::internal::InitSCC(
      &protobuf_sliceindex_2eproto::scc_info_SliceIdArray.base);
  SharedCtor();
  // @@protoc_insertion_point(constructor:sliceindex.SliceIdArray)
}
SliceIdArray::SliceIdArray(const SliceIdArray& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(NULL),
      ids_(from.ids_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:sliceindex.SliceIdArray)
}

void SliceIdArray::SharedCtor() {
}

SliceIdArray::~SliceIdArray() {
  // @@protoc_insertion_point(destructor:sliceindex.SliceIdArray)
  SharedDtor();
}

void SliceIdArray::SharedDtor() {
}

void SliceIdArray::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const ::google::protobuf::Descriptor* SliceIdArray::descriptor() {
  ::protobuf_sliceindex_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_sliceindex_2eproto::file_level_metadata[kIndexInFileMessages].descriptor;
}

const SliceIdArray& SliceIdArray::default_instance() {
  ::google::protobuf::internal::InitSCC(&protobuf_sliceindex_2eproto::scc_info_SliceIdArray.base);
  return *internal_default_instance();
}


void SliceIdArray::Clear() {
// @@protoc_insertion_point(message_clear_start:sliceindex.SliceIdArray)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ids_.Clear();
  _internal_metadata_.Clear();
}

bool SliceIdArray::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!GOOGLE_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:sliceindex.SliceIdArray)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated uint64 ids = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(10u /* 10 & 0xFF */)) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadPackedPrimitive<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 input, this->mutable_ids())));
        } else if (
            static_cast< ::google::protobuf::uint8>(tag) ==
            static_cast< ::google::protobuf::uint8>(8u /* 8 & 0xFF */)) {
          DO_((::google::protobuf::internal::WireFormatLite::ReadRepeatedPrimitiveNoInline<
                   ::google::protobuf::uint64, ::google::protobuf::internal::WireFormatLite::TYPE_UINT64>(
                 1, 10u, input, this->mutable_ids())));
        } else {
          goto handle_unusual;
        }
        break;
      }

      default: {
      handle_unusual:
        if (tag == 0) {
          goto success;
        }
        DO_(::google::protobuf::internal::WireFormat::SkipField(
              input, tag, _internal_metadata_.mutable_unknown_fields()));
        break;
      }
    }
  }
success:
  // @@protoc_insertion_point(parse_success:sliceindex.SliceIdArray)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:sliceindex.SliceIdArray)
  return false;
#undef DO_
}

void SliceIdArray::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:sliceindex.SliceIdArray)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated uint64 ids = 1;
  if (this->ids_size() > 0) {
    ::google::protobuf::internal::WireFormatLite::WriteTag(1, ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED, output);
    output->WriteVarint32(static_cast< ::google::protobuf::uint32>(
        _ids_cached_byte_size_));
  }
  for (int i = 0, n = this->ids_size(); i < n; i++) {
    ::google::protobuf::internal::WireFormatLite::WriteUInt64NoTag(
      this->ids(i), output);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), output);
  }
  // @@protoc_insertion_point(serialize_end:sliceindex.SliceIdArray)
}

::google::protobuf::uint8* SliceIdArray::InternalSerializeWithCachedSizesToArray(
    bool deterministic, ::google::protobuf::uint8* target) const {
  (void)deterministic; // Unused
  // @@protoc_insertion_point(serialize_to_array_start:sliceindex.SliceIdArray)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated uint64 ids = 1;
  if (this->ids_size() > 0) {
    target = ::google::protobuf::internal::WireFormatLite::WriteTagToArray(
      1,
      ::google::protobuf::internal::WireFormatLite::WIRETYPE_LENGTH_DELIMITED,
      target);
    target = ::google::protobuf::io::CodedOutputStream::WriteVarint32ToArray(
        static_cast< ::google::protobuf::int32>(
            _ids_cached_byte_size_), target);
    target = ::google::protobuf::internal::WireFormatLite::
      WriteUInt64NoTagToArray(this->ids_, target);
  }

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:sliceindex.SliceIdArray)
  return target;
}

size_t SliceIdArray::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:sliceindex.SliceIdArray)
  size_t total_size = 0;

  if ((_internal_metadata_.have_unknown_fields() &&  ::google::protobuf::internal::GetProto3PreserveUnknownsDefault())) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        (::google::protobuf::internal::GetProto3PreserveUnknownsDefault()   ? _internal_metadata_.unknown_fields()   : _internal_metadata_.default_instance()));
  }
  // repeated uint64 ids = 1;
  {
    size_t data_size = ::google::protobuf::internal::WireFormatLite::
      UInt64Size(this->ids_);
    if (data_size > 0) {
      total_size += 1 +
        ::google::protobuf::internal::WireFormatLite::Int32Size(
            static_cast< ::google::protobuf::int32>(data_size));
    }
    int cached_size = ::google::protobuf::internal::ToCachedSize(data_size);
    GOOGLE_SAFE_CONCURRENT_WRITES_BEGIN();
    _ids_cached_byte_size_ = cached_size;
    GOOGLE_SAFE_CONCURRENT_WRITES_END();
    total_size += data_size;
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void SliceIdArray::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:sliceindex.SliceIdArray)
  GOOGLE_DCHECK_NE(&from, this);
  const SliceIdArray* source =
      ::google::protobuf::internal::DynamicCastToGenerated<const SliceIdArray>(
          &from);
  if (source == NULL) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:sliceindex.SliceIdArray)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:sliceindex.SliceIdArray)
    MergeFrom(*source);
  }
}

void SliceIdArray::MergeFrom(const SliceIdArray& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:sliceindex.SliceIdArray)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  ids_.MergeFrom(from.ids_);
}

void SliceIdArray::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:sliceindex.SliceIdArray)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void SliceIdArray::CopyFrom(const SliceIdArray& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:sliceindex.SliceIdArray)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool SliceIdArray::IsInitialized() const {
  return true;
}

void SliceIdArray::Swap(SliceIdArray* other) {
  if (other == this) return;
  InternalSwap(other);
}
void SliceIdArray::InternalSwap(SliceIdArray* other) {
  using std::swap;
  ids_.InternalSwap(&other->ids_);
  _internal_metadata_.Swap(&other->_internal_metadata_);
}

::google::protobuf::Metadata SliceIdArray::GetMetadata() const {
  protobuf_sliceindex_2eproto::protobuf_AssignDescriptorsOnce();
  return ::protobuf_sliceindex_2eproto::file_level_metadata[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace sliceindex
namespace google {
namespace protobuf {
template<> GOOGLE_PROTOBUF_ATTRIBUTE_NOINLINE ::sliceindex::SliceIdArray* Arena::CreateMaybeMessage< ::sliceindex::SliceIdArray >(Arena* arena) {
  return Arena::CreateInternal< ::sliceindex::SliceIdArray >(arena);
}
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)