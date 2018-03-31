#include <utility>
#include <stdexcept>

#include "pb_encode.h"
#include "pb_decode.h"
#include "example.pb.h"
#include "tfrecord_lite.h"

using namespace std;

struct decoder_context {
	const decoder_options *options;
	decoder_output output;
	std::string current_key;
	int current_kind;

	bool should_parse() {
		return options->names.empty() || options->names.count(current_key) > 0;
	}
};

bool decode_feature_key(pb_istream_t *stream, const pb_field_t *field, void **arg) {
	decoder_context *context = (decoder_context*)*arg;

	if (PB_LTYPE(field->type) != PB_LTYPE_STRING) {
		return false;
	}

	size_t key_length = stream->bytes_left;
	context->current_key.resize(key_length);
	pb_read(stream, (pb_byte_t *)context->current_key.data(), key_length);

	return true;
}

bool decode_feature_bytes(pb_istream_t *stream, const pb_field_t *field, void **arg) {
	decoder_context *context = (decoder_context*)*arg;
	if (!context->should_parse()) {
		return pb_read(stream, NULL, stream->bytes_left);
	}
	context->output.names.push_back(context->current_key);

	string data;
	data.resize(stream->bytes_left);
	if (!pb_read(stream, (pb_byte_t *)data.data(), stream->bytes_left)) {
		return false;
	}

	vector<string> &strings = context->output.bytes_features[context->current_key];
	strings.push_back(move(data));
	return true;
}

bool decode_feature_float(pb_istream_t *stream, const pb_field_t *field, void **arg) {
	decoder_context *context = (decoder_context*)*arg;
	if (!context->should_parse()) {
		return pb_read(stream, NULL, stream->bytes_left);
	}
	context->output.names.push_back(context->current_key);

	string buffer;
	buffer.resize(stream->bytes_left);
	if (!pb_read(stream, (pb_byte_t *)buffer.data(), stream->bytes_left)) {
		return false;
	}

	context->output.float_features[context->current_key] = move(buffer);
	return true;
}

bool decode_feature_int64(pb_istream_t *stream, const pb_field_t *field, void **arg) {
	decoder_context *context = (decoder_context*)*arg;
	if (!context->should_parse()) {
		return pb_read(stream, NULL, stream->bytes_left);
	}
	context->output.names.push_back(context->current_key);

	vector<pb_byte_t> packed;
	packed.resize(stream->bytes_left);

	if (!pb_read(stream, (pb_byte_t *)packed.data(), stream->bytes_left)) {
		return false;
	}

	pb_istream_t substream = pb_istream_from_buffer(packed.data(), packed.size());
	size_t count = 0;
	uint64_t number;
	while (substream.bytes_left) {
		if (!pb_decode_varint(&substream, &number)) {
			return false;
		}
		count++;
	}

	string buffer;
	buffer.resize(count * sizeof(uint64_t));
	substream = pb_istream_from_buffer(packed.data(), packed.size());
	uint64_t *p = (uint64_t *)buffer.data();
	while (substream.bytes_left) {
		if (!pb_decode_varint(&substream, p++)) {
			return false;
		}
	}

	context->output.int64_features[context->current_key] = move(buffer);
	return true;
}

bool decode_feature_entry(pb_istream_t *stream, const pb_field_t *field, void **arg) {
	decoder_context *context = (decoder_context *)*arg;
	tensorflow_Features_FeatureEntry entry = { 0 };

	entry.key.funcs.decode = decode_feature_key;
	entry.key.arg = context;
	entry.value.bytes_list.value.funcs.decode = decode_feature_bytes;
	entry.value.bytes_list.value.arg = context;
	entry.value.int64_list.value.funcs.decode = decode_feature_int64;
	entry.value.int64_list.value.arg = context;
	entry.value.float_list.value.funcs.decode = decode_feature_float;
	entry.value.float_list.value.arg = context;

	if (!pb_decode(stream, tensorflow_Features_FeatureEntry_fields, &entry)) {
		return false;
	}

	return true;
}

decoder_output decode_tfrecord_example(const uint8_t *bytes, size_t length, const decoder_options &options) {
	decoder_context context;
	context.options = &options;

	tensorflow_Example example = { 0 };
	example.features.feature.funcs.decode = decode_feature_entry;
	example.features.feature.arg = &context;

	pb_istream_t stream = pb_istream_from_buffer(bytes, length);

	if (!pb_decode(&stream, tensorflow_Example_fields, &example)) {
		string message = string("Decoding failed: ") + PB_GET_ERROR(&stream);
		throw std::runtime_error(message);
	}

	return context.output;
}
