from libcpp.set cimport set
from libcpp.map cimport map
from libcpp.string cimport string
from libcpp.vector cimport vector

cdef extern from "tfrecord_lite.h":
    cdef struct decoder_options:
        set[string] names;

    cdef struct decoder_output:
        vector[string] names
        map[string, vector[string]] bytes_features
        map[string, string] int64_features
        map[string, string] float_features

    decoder_output decode_tfrecord_example(const unsigned char *bytes, size_t length, const decoder_options &options)


cdef decode_example_internal(bytes buffer, vector[string] names):
    cdef decoder_options options
    options.names = set[string]()
    for name in names:
        options.names.insert(name)

    cdef decoder_output decoded = decode_tfrecord_example(buffer, len(buffer), options)
    result = {}

    import numpy as np

    for name in decoded.names:
        if decoded.int64_features.count(name) > 0:
            result[name] = np.frombuffer(decoded.int64_features[name], dtype=np.int64)
        elif decoded.float_features.count(name) > 0:
            result[name] = np.frombuffer(decoded.float_features[name], dtype=np.float32)
        elif decoded.bytes_features.count(name) > 0:
            result[name] = decoded.bytes_features[name]
        else:
            result[name] = []

    return result


def decode_example(bytes buffer, names=[]):
    decoded = decode_example_internal(buffer, [name.encode('utf-8') for name in names])
    return {key.decode('utf-8'): value for key, value in decoded.items()}
