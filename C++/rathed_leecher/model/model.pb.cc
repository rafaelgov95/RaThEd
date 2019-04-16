// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: model.proto

#include "model.pb.h"

#include <algorithm>

#include <google/protobuf/stubs/common.h>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite_inl.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

namespace rathed {
class DatagramaDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<Datagrama> _instance;
} _Datagrama_default_instance_;
class VectorStringDefaultTypeInternal {
 public:
  ::google::protobuf::internal::ExplicitlyConstructed<VectorString> _instance;
} _VectorString_default_instance_;
}  // namespace rathed
static void InitDefaultsDatagrama_model_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::rathed::_Datagrama_default_instance_;
    new (ptr) ::rathed::Datagrama();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::rathed::Datagrama::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_Datagrama_model_2eproto =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsDatagrama_model_2eproto}, {}};

static void InitDefaultsVectorString_model_2eproto() {
  GOOGLE_PROTOBUF_VERIFY_VERSION;

  {
    void* ptr = &::rathed::_VectorString_default_instance_;
    new (ptr) ::rathed::VectorString();
    ::google::protobuf::internal::OnShutdownDestroyMessage(ptr);
  }
  ::rathed::VectorString::InitAsDefaultInstance();
}

::google::protobuf::internal::SCCInfo<0> scc_info_VectorString_model_2eproto =
    {{ATOMIC_VAR_INIT(::google::protobuf::internal::SCCInfoBase::kUninitialized), 0, InitDefaultsVectorString_model_2eproto}, {}};

void InitDefaults_model_2eproto() {
  ::google::protobuf::internal::InitSCC(&scc_info_Datagrama_model_2eproto.base);
  ::google::protobuf::internal::InitSCC(&scc_info_VectorString_model_2eproto.base);
}

::google::protobuf::Metadata file_level_metadata_model_2eproto[2];
const ::google::protobuf::EnumDescriptor* file_level_enum_descriptors_model_2eproto[1];
constexpr ::google::protobuf::ServiceDescriptor const** file_level_service_descriptors_model_2eproto = nullptr;

const ::google::protobuf::uint32 TableStruct_model_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  PROTOBUF_FIELD_OFFSET(::rathed::Datagrama, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::rathed::Datagrama, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::rathed::Datagrama, type_),
  PROTOBUF_FIELD_OFFSET(::rathed::Datagrama, packnumber_),
  PROTOBUF_FIELD_OFFSET(::rathed::Datagrama, data_),
  2,
  1,
  0,
  PROTOBUF_FIELD_OFFSET(::rathed::VectorString, _has_bits_),
  PROTOBUF_FIELD_OFFSET(::rathed::VectorString, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  PROTOBUF_FIELD_OFFSET(::rathed::VectorString, peers_),
  ~0u,
};
static const ::google::protobuf::internal::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, 8, sizeof(::rathed::Datagrama)},
  { 11, 17, sizeof(::rathed::VectorString)},
};

static ::google::protobuf::Message const * const file_default_instances[] = {
  reinterpret_cast<const ::google::protobuf::Message*>(&::rathed::_Datagrama_default_instance_),
  reinterpret_cast<const ::google::protobuf::Message*>(&::rathed::_VectorString_default_instance_),
};

::google::protobuf::internal::AssignDescriptorsTable assign_descriptors_table_model_2eproto = {
  {}, AddDescriptors_model_2eproto, "model.proto", schemas,
  file_default_instances, TableStruct_model_2eproto::offsets,
  file_level_metadata_model_2eproto, 2, file_level_enum_descriptors_model_2eproto, file_level_service_descriptors_model_2eproto,
};

const char descriptor_table_protodef_model_2eproto[] =
  "\n\013model.proto\022\006rathed\"R\n\tDatagrama\022#\n\004Ty"
  "pe\030\001 \002(\0162\025.rathed.DatagramaType\022\022\n\nPackN"
  "umber\030\002 \002(\005\022\014\n\004Data\030\003 \002(\014\"\035\n\014VectorStrin"
  "g\022\r\n\005peers\030\001 \003(\t*<\n\rDatagramaType\022\007\n\003ACK"
  "\020\001\022\007\n\003SND\020\002\022\007\n\003SYN\020\003\022\007\n\003UPD\020\004\022\007\n\003LST\020\005"
  ;
::google::protobuf::internal::DescriptorTable descriptor_table_model_2eproto = {
  false, InitDefaults_model_2eproto, 
  descriptor_table_protodef_model_2eproto,
  "model.proto", &assign_descriptors_table_model_2eproto, 198,
};

void AddDescriptors_model_2eproto() {
  static constexpr ::google::protobuf::internal::InitFunc deps[1] =
  {
  };
 ::google::protobuf::internal::AddDescriptors(&descriptor_table_model_2eproto, deps, 0);
}

// Force running AddDescriptors() at dynamic initialization time.
static bool dynamic_init_dummy_model_2eproto = []() { AddDescriptors_model_2eproto(); return true; }();
namespace rathed {
const ::google::protobuf::EnumDescriptor* DatagramaType_descriptor() {
  ::google::protobuf::internal::AssignDescriptors(&assign_descriptors_table_model_2eproto);
  return file_level_enum_descriptors_model_2eproto[0];
}
bool DatagramaType_IsValid(int value) {
  switch (value) {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
      return true;
    default:
      return false;
  }
}


// ===================================================================

void Datagrama::InitAsDefaultInstance() {
}
class Datagrama::HasBitSetters {
 public:
  static void set_has_type(Datagrama* msg) {
    msg->_has_bits_[0] |= 0x00000004u;
  }
  static void set_has_packnumber(Datagrama* msg) {
    msg->_has_bits_[0] |= 0x00000002u;
  }
  static void set_has_data(Datagrama* msg) {
    msg->_has_bits_[0] |= 0x00000001u;
  }
};

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int Datagrama::kTypeFieldNumber;
const int Datagrama::kPackNumberFieldNumber;
const int Datagrama::kDataFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

Datagrama::Datagrama()
  : ::google::protobuf::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:rathed.Datagrama)
}
Datagrama::Datagrama(const Datagrama& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(nullptr),
      _has_bits_(from._has_bits_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  data_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  if (from.has_data()) {
    data_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.data_);
  }
  ::memcpy(&packnumber_, &from.packnumber_,
    static_cast<size_t>(reinterpret_cast<char*>(&type_) -
    reinterpret_cast<char*>(&packnumber_)) + sizeof(type_));
  // @@protoc_insertion_point(copy_constructor:rathed.Datagrama)
}

void Datagrama::SharedCtor() {
  ::google::protobuf::internal::InitSCC(
      &scc_info_Datagrama_model_2eproto.base);
  data_.UnsafeSetDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  packnumber_ = 0;
  type_ = 1;
}

Datagrama::~Datagrama() {
  // @@protoc_insertion_point(destructor:rathed.Datagrama)
  SharedDtor();
}

void Datagrama::SharedDtor() {
  data_.DestroyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}

void Datagrama::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const Datagrama& Datagrama::default_instance() {
  ::google::protobuf::internal::InitSCC(&::scc_info_Datagrama_model_2eproto.base);
  return *internal_default_instance();
}


void Datagrama::Clear() {
// @@protoc_insertion_point(message_clear_start:rathed.Datagrama)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  if (cached_has_bits & 0x00000001u) {
    data_.ClearNonDefaultToEmptyNoArena();
  }
  if (cached_has_bits & 0x00000006u) {
    packnumber_ = 0;
    type_ = 1;
  }
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* Datagrama::_InternalParse(const char* begin, const char* end, void* object,
                  ::google::protobuf::internal::ParseContext* ctx) {
  auto msg = static_cast<Datagrama*>(object);
  ::google::protobuf::int32 size; (void)size;
  int depth; (void)depth;
  ::google::protobuf::uint32 tag;
  ::google::protobuf::internal::ParseFunc parser_till_end; (void)parser_till_end;
  auto ptr = begin;
  while (ptr < end) {
    ptr = ::google::protobuf::io::Parse32(ptr, &tag);
    GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
    switch (tag >> 3) {
      // required .rathed.DatagramaType Type = 1;
      case 1: {
        if (static_cast<::google::protobuf::uint8>(tag) != 8) goto handle_unusual;
        ::google::protobuf::uint64 val = ::google::protobuf::internal::ReadVarint(&ptr);
        if (!::rathed::DatagramaType_IsValid(val)) {
          ::google::protobuf::internal::WriteVarint(1, val, msg->mutable_unknown_fields());
          break;
        }
        msg->set_type(static_cast<::rathed::DatagramaType>(val));
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        break;
      }
      // required int32 PackNumber = 2;
      case 2: {
        if (static_cast<::google::protobuf::uint8>(tag) != 16) goto handle_unusual;
        msg->set_packnumber(::google::protobuf::internal::ReadVarint(&ptr));
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        break;
      }
      // required bytes Data = 3;
      case 3: {
        if (static_cast<::google::protobuf::uint8>(tag) != 26) goto handle_unusual;
        ptr = ::google::protobuf::io::ReadSize(ptr, &size);
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
        object = msg->mutable_data();
        if (size > end - ptr + ::google::protobuf::internal::ParseContext::kSlopBytes) {
          parser_till_end = ::google::protobuf::internal::GreedyStringParser;
          goto string_till_end;
        }
        GOOGLE_PROTOBUF_PARSER_ASSERT(::google::protobuf::internal::StringCheck(ptr, size, ctx));
        ::google::protobuf::internal::InlineGreedyStringParser(object, ptr, size, ctx);
        ptr += size;
        break;
      }
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->EndGroup(tag);
          return ptr;
        }
        auto res = UnknownFieldParse(tag, {_InternalParse, msg},
          ptr, end, msg->_internal_metadata_.mutable_unknown_fields(), ctx);
        ptr = res.first;
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr != nullptr);
        if (res.second) return ptr;
      }
    }  // switch
  }  // while
  return ptr;
string_till_end:
  static_cast<::std::string*>(object)->clear();
  static_cast<::std::string*>(object)->reserve(size);
  goto len_delim_till_end;
len_delim_till_end:
  return ctx->StoreAndTailCall(ptr, end, {_InternalParse, msg},
                               {parser_till_end, object}, size);
}
#else  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
bool Datagrama::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:rathed.Datagrama)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // required .rathed.DatagramaType Type = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (8 & 0xFF)) {
          int value = 0;
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   int, ::google::protobuf::internal::WireFormatLite::TYPE_ENUM>(
                 input, &value)));
          if (::rathed::DatagramaType_IsValid(value)) {
            set_type(static_cast< ::rathed::DatagramaType >(value));
          } else {
            mutable_unknown_fields()->AddVarint(
                1, static_cast<::google::protobuf::uint64>(value));
          }
        } else {
          goto handle_unusual;
        }
        break;
      }

      // required int32 PackNumber = 2;
      case 2: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (16 & 0xFF)) {
          HasBitSetters::set_has_packnumber(this);
          DO_((::google::protobuf::internal::WireFormatLite::ReadPrimitive<
                   ::google::protobuf::int32, ::google::protobuf::internal::WireFormatLite::TYPE_INT32>(
                 input, &packnumber_)));
        } else {
          goto handle_unusual;
        }
        break;
      }

      // required bytes Data = 3;
      case 3: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (26 & 0xFF)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadBytes(
                input, this->mutable_data()));
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
  // @@protoc_insertion_point(parse_success:rathed.Datagrama)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:rathed.Datagrama)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void Datagrama::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:rathed.Datagrama)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required .rathed.DatagramaType Type = 1;
  if (cached_has_bits & 0x00000004u) {
    ::google::protobuf::internal::WireFormatLite::WriteEnum(
      1, this->type(), output);
  }

  // required int32 PackNumber = 2;
  if (cached_has_bits & 0x00000002u) {
    ::google::protobuf::internal::WireFormatLite::WriteInt32(2, this->packnumber(), output);
  }

  // required bytes Data = 3;
  if (cached_has_bits & 0x00000001u) {
    ::google::protobuf::internal::WireFormatLite::WriteBytesMaybeAliased(
      3, this->data(), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:rathed.Datagrama)
}

::google::protobuf::uint8* Datagrama::InternalSerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:rathed.Datagrama)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = _has_bits_[0];
  // required .rathed.DatagramaType Type = 1;
  if (cached_has_bits & 0x00000004u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteEnumToArray(
      1, this->type(), target);
  }

  // required int32 PackNumber = 2;
  if (cached_has_bits & 0x00000002u) {
    target = ::google::protobuf::internal::WireFormatLite::WriteInt32ToArray(2, this->packnumber(), target);
  }

  // required bytes Data = 3;
  if (cached_has_bits & 0x00000001u) {
    target =
      ::google::protobuf::internal::WireFormatLite::WriteBytesToArray(
        3, this->data(), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:rathed.Datagrama)
  return target;
}

size_t Datagrama::RequiredFieldsByteSizeFallback() const {
// @@protoc_insertion_point(required_fields_byte_size_fallback_start:rathed.Datagrama)
  size_t total_size = 0;

  if (has_data()) {
    // required bytes Data = 3;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::BytesSize(
        this->data());
  }

  if (has_packnumber()) {
    // required int32 PackNumber = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->packnumber());
  }

  if (has_type()) {
    // required .rathed.DatagramaType Type = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::EnumSize(this->type());
  }

  return total_size;
}
size_t Datagrama::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:rathed.Datagrama)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  if (((_has_bits_[0] & 0x00000007) ^ 0x00000007) == 0) {  // All required fields are present.
    // required bytes Data = 3;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::BytesSize(
        this->data());

    // required int32 PackNumber = 2;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::Int32Size(
        this->packnumber());

    // required .rathed.DatagramaType Type = 1;
    total_size += 1 +
      ::google::protobuf::internal::WireFormatLite::EnumSize(this->type());

  } else {
    total_size += RequiredFieldsByteSizeFallback();
  }
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void Datagrama::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:rathed.Datagrama)
  GOOGLE_DCHECK_NE(&from, this);
  const Datagrama* source =
      ::google::protobuf::DynamicCastToGenerated<Datagrama>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:rathed.Datagrama)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:rathed.Datagrama)
    MergeFrom(*source);
  }
}

void Datagrama::MergeFrom(const Datagrama& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:rathed.Datagrama)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  cached_has_bits = from._has_bits_[0];
  if (cached_has_bits & 0x00000007u) {
    if (cached_has_bits & 0x00000001u) {
      _has_bits_[0] |= 0x00000001u;
      data_.AssignWithDefault(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), from.data_);
    }
    if (cached_has_bits & 0x00000002u) {
      packnumber_ = from.packnumber_;
    }
    if (cached_has_bits & 0x00000004u) {
      type_ = from.type_;
    }
    _has_bits_[0] |= cached_has_bits;
  }
}

void Datagrama::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:rathed.Datagrama)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void Datagrama::CopyFrom(const Datagrama& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:rathed.Datagrama)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool Datagrama::IsInitialized() const {
  if ((_has_bits_[0] & 0x00000007) != 0x00000007) return false;
  return true;
}

void Datagrama::Swap(Datagrama* other) {
  if (other == this) return;
  InternalSwap(other);
}
void Datagrama::InternalSwap(Datagrama* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  data_.Swap(&other->data_, &::google::protobuf::internal::GetEmptyStringAlreadyInited(),
    GetArenaNoVirtual());
  swap(packnumber_, other->packnumber_);
  swap(type_, other->type_);
}

::google::protobuf::Metadata Datagrama::GetMetadata() const {
  ::google::protobuf::internal::AssignDescriptors(&::assign_descriptors_table_model_2eproto);
  return ::file_level_metadata_model_2eproto[kIndexInFileMessages];
}


// ===================================================================

void VectorString::InitAsDefaultInstance() {
}
class VectorString::HasBitSetters {
 public:
};

#if !defined(_MSC_VER) || _MSC_VER >= 1900
const int VectorString::kPeersFieldNumber;
#endif  // !defined(_MSC_VER) || _MSC_VER >= 1900

VectorString::VectorString()
  : ::google::protobuf::Message(), _internal_metadata_(nullptr) {
  SharedCtor();
  // @@protoc_insertion_point(constructor:rathed.VectorString)
}
VectorString::VectorString(const VectorString& from)
  : ::google::protobuf::Message(),
      _internal_metadata_(nullptr),
      _has_bits_(from._has_bits_),
      peers_(from.peers_) {
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  // @@protoc_insertion_point(copy_constructor:rathed.VectorString)
}

void VectorString::SharedCtor() {
  ::google::protobuf::internal::InitSCC(
      &scc_info_VectorString_model_2eproto.base);
}

VectorString::~VectorString() {
  // @@protoc_insertion_point(destructor:rathed.VectorString)
  SharedDtor();
}

void VectorString::SharedDtor() {
}

void VectorString::SetCachedSize(int size) const {
  _cached_size_.Set(size);
}
const VectorString& VectorString::default_instance() {
  ::google::protobuf::internal::InitSCC(&::scc_info_VectorString_model_2eproto.base);
  return *internal_default_instance();
}


void VectorString::Clear() {
// @@protoc_insertion_point(message_clear_start:rathed.VectorString)
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  peers_.Clear();
  _has_bits_.Clear();
  _internal_metadata_.Clear();
}

#if GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
const char* VectorString::_InternalParse(const char* begin, const char* end, void* object,
                  ::google::protobuf::internal::ParseContext* ctx) {
  auto msg = static_cast<VectorString*>(object);
  ::google::protobuf::int32 size; (void)size;
  int depth; (void)depth;
  ::google::protobuf::uint32 tag;
  ::google::protobuf::internal::ParseFunc parser_till_end; (void)parser_till_end;
  auto ptr = begin;
  while (ptr < end) {
    ptr = ::google::protobuf::io::Parse32(ptr, &tag);
    GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
    switch (tag >> 3) {
      // repeated string peer = 1;
      case 1: {
        if (static_cast<::google::protobuf::uint8>(tag) != 10) goto handle_unusual;
        do {
          ptr = ::google::protobuf::io::ReadSize(ptr, &size);
          GOOGLE_PROTOBUF_PARSER_ASSERT(ptr);
          ctx->extra_parse_data().SetFieldName("rathed.VectorString.peer");
          object = msg->add_peers();
          if (size > end - ptr + ::google::protobuf::internal::ParseContext::kSlopBytes) {
            parser_till_end = ::google::protobuf::internal::GreedyStringParserUTF8Verify;
            goto string_till_end;
          }
          GOOGLE_PROTOBUF_PARSER_ASSERT(::google::protobuf::internal::StringCheckUTF8Verify(ptr, size, ctx));
          ::google::protobuf::internal::InlineGreedyStringParser(object, ptr, size, ctx);
          ptr += size;
          if (ptr >= end) break;
        } while ((::google::protobuf::io::UnalignedLoad<::google::protobuf::uint64>(ptr) & 255) == 10 && (ptr += 1));
        break;
      }
      default: {
      handle_unusual:
        if ((tag & 7) == 4 || tag == 0) {
          ctx->EndGroup(tag);
          return ptr;
        }
        auto res = UnknownFieldParse(tag, {_InternalParse, msg},
          ptr, end, msg->_internal_metadata_.mutable_unknown_fields(), ctx);
        ptr = res.first;
        GOOGLE_PROTOBUF_PARSER_ASSERT(ptr != nullptr);
        if (res.second) return ptr;
      }
    }  // switch
  }  // while
  return ptr;
string_till_end:
  static_cast<::std::string*>(object)->clear();
  static_cast<::std::string*>(object)->reserve(size);
  goto len_delim_till_end;
len_delim_till_end:
  return ctx->StoreAndTailCall(ptr, end, {_InternalParse, msg},
                               {parser_till_end, object}, size);
}
#else  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER
bool VectorString::MergePartialFromCodedStream(
    ::google::protobuf::io::CodedInputStream* input) {
#define DO_(EXPRESSION) if (!PROTOBUF_PREDICT_TRUE(EXPRESSION)) goto failure
  ::google::protobuf::uint32 tag;
  // @@protoc_insertion_point(parse_start:rathed.VectorString)
  for (;;) {
    ::std::pair<::google::protobuf::uint32, bool> p = input->ReadTagWithCutoffNoLastTag(127u);
    tag = p.first;
    if (!p.second) goto handle_unusual;
    switch (::google::protobuf::internal::WireFormatLite::GetTagFieldNumber(tag)) {
      // repeated string peer = 1;
      case 1: {
        if (static_cast< ::google::protobuf::uint8>(tag) == (10 & 0xFF)) {
          DO_(::google::protobuf::internal::WireFormatLite::ReadString(
                input, this->add_peers()));
          ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
            this->peers(this->peers_size() - 1).data(),
            static_cast<int>(this->peers(this->peers_size() - 1).length()),
            ::google::protobuf::internal::WireFormat::PARSE,
            "rathed.VectorString.peer");
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
  // @@protoc_insertion_point(parse_success:rathed.VectorString)
  return true;
failure:
  // @@protoc_insertion_point(parse_failure:rathed.VectorString)
  return false;
#undef DO_
}
#endif  // GOOGLE_PROTOBUF_ENABLE_EXPERIMENTAL_PARSER

void VectorString::SerializeWithCachedSizes(
    ::google::protobuf::io::CodedOutputStream* output) const {
  // @@protoc_insertion_point(serialize_start:rathed.VectorString)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated string peer = 1;
  for (int i = 0, n = this->peers_size(); i < n; i++) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->peers(i).data(), static_cast<int>(this->peers(i).length()),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "rathed.VectorString.peer");
    ::google::protobuf::internal::WireFormatLite::WriteString(
      1, this->peers(i), output);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    ::google::protobuf::internal::WireFormat::SerializeUnknownFields(
        _internal_metadata_.unknown_fields(), output);
  }
  // @@protoc_insertion_point(serialize_end:rathed.VectorString)
}

::google::protobuf::uint8* VectorString::InternalSerializeWithCachedSizesToArray(
    ::google::protobuf::uint8* target) const {
  // @@protoc_insertion_point(serialize_to_array_start:rathed.VectorString)
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  // repeated string peer = 1;
  for (int i = 0, n = this->peers_size(); i < n; i++) {
    ::google::protobuf::internal::WireFormat::VerifyUTF8StringNamedField(
      this->peers(i).data(), static_cast<int>(this->peers(i).length()),
      ::google::protobuf::internal::WireFormat::SERIALIZE,
      "rathed.VectorString.peer");
    target = ::google::protobuf::internal::WireFormatLite::
      WriteStringToArray(1, this->peers(i), target);
  }

  if (_internal_metadata_.have_unknown_fields()) {
    target = ::google::protobuf::internal::WireFormat::SerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields(), target);
  }
  // @@protoc_insertion_point(serialize_to_array_end:rathed.VectorString)
  return target;
}

size_t VectorString::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:rathed.VectorString)
  size_t total_size = 0;

  if (_internal_metadata_.have_unknown_fields()) {
    total_size +=
      ::google::protobuf::internal::WireFormat::ComputeUnknownFieldsSize(
        _internal_metadata_.unknown_fields());
  }
  ::google::protobuf::uint32 cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // repeated string peer = 1;
  total_size += 1 *
      ::google::protobuf::internal::FromIntSize(this->peers_size());
  for (int i = 0, n = this->peers_size(); i < n; i++) {
    total_size += ::google::protobuf::internal::WireFormatLite::StringSize(
      this->peers(i));
  }

  int cached_size = ::google::protobuf::internal::ToCachedSize(total_size);
  SetCachedSize(cached_size);
  return total_size;
}

void VectorString::MergeFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_merge_from_start:rathed.VectorString)
  GOOGLE_DCHECK_NE(&from, this);
  const VectorString* source =
      ::google::protobuf::DynamicCastToGenerated<VectorString>(
          &from);
  if (source == nullptr) {
  // @@protoc_insertion_point(generalized_merge_from_cast_fail:rathed.VectorString)
    ::google::protobuf::internal::ReflectionOps::Merge(from, this);
  } else {
  // @@protoc_insertion_point(generalized_merge_from_cast_success:rathed.VectorString)
    MergeFrom(*source);
  }
}

void VectorString::MergeFrom(const VectorString& from) {
// @@protoc_insertion_point(class_specific_merge_from_start:rathed.VectorString)
  GOOGLE_DCHECK_NE(&from, this);
  _internal_metadata_.MergeFrom(from._internal_metadata_);
  ::google::protobuf::uint32 cached_has_bits = 0;
  (void) cached_has_bits;

  peers_.MergeFrom(from.peers_);
}

void VectorString::CopyFrom(const ::google::protobuf::Message& from) {
// @@protoc_insertion_point(generalized_copy_from_start:rathed.VectorString)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

void VectorString::CopyFrom(const VectorString& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:rathed.VectorString)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool VectorString::IsInitialized() const {
  return true;
}

void VectorString::Swap(VectorString* other) {
  if (other == this) return;
  InternalSwap(other);
}
void VectorString::InternalSwap(VectorString* other) {
  using std::swap;
  _internal_metadata_.Swap(&other->_internal_metadata_);
  swap(_has_bits_[0], other->_has_bits_[0]);
  peers_.InternalSwap(CastToBase(&other->peers_));
}

::google::protobuf::Metadata VectorString::GetMetadata() const {
  ::google::protobuf::internal::AssignDescriptors(&::assign_descriptors_table_model_2eproto);
  return ::file_level_metadata_model_2eproto[kIndexInFileMessages];
}


// @@protoc_insertion_point(namespace_scope)
}  // namespace rathed
namespace google {
namespace protobuf {
template<> PROTOBUF_NOINLINE ::rathed::Datagrama* Arena::CreateMaybeMessage< ::rathed::Datagrama >(Arena* arena) {
  return Arena::CreateInternal< ::rathed::Datagrama >(arena);
}
template<> PROTOBUF_NOINLINE ::rathed::VectorString* Arena::CreateMaybeMessage< ::rathed::VectorString >(Arena* arena) {
  return Arena::CreateInternal< ::rathed::VectorString >(arena);
}
}  // namespace protobuf
}  // namespace google

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
