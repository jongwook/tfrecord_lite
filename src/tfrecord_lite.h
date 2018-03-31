#pragma once

#include <set>
#include <map>
#include <vector>
#include <string>

struct decoder_options {
	std::set<std::string> names;
};

// Using std::string for passing raw data buffers because Cython automatically converts them to Python bytes,
// which is preferable over std::vector and other sequence containers which becomes Python lists.
struct decoder_output {
	std::vector<std::string> names;
	std::map<std::string, std::vector<std::string> > bytes_features;
	std::map<std::string, std::string> int64_features;
	std::map<std::string, std::string> float_features;
};

decoder_output decode_tfrecord_example(const unsigned char *bytes, size_t length, const decoder_options &options);
