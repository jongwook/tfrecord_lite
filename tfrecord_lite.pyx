from libcpp.set cimport set
from libcpp.map cimport map
from libcpp.string cimport string
from libcpp.vector cimport vector

import numpy as _np
import struct as _struct


cdef extern from "tfrecord_lite.h":
    cdef struct decoder_options:
        set[string] names;

    cdef struct decoder_output:
        vector[string] names
        map[string, vector[string]] bytes_features
        map[string, string] int64_features
        map[string, string] float_features

    decoder_output decode_tfrecord_example(const unsigned char *bytes, size_t length, const decoder_options &options) except +


cdef decode_example_internal(bytes buffer, vector[string] names):
    cdef decoder_options options
    options.names = set[string]()
    for name in names:
        options.names.insert(name)

    cdef decoder_output decoded = decode_tfrecord_example(buffer, len(buffer), options)
    result = {}


    for name in decoded.names:
        if decoded.int64_features.count(name) > 0:
            result[name] = _np.frombuffer(decoded.int64_features[name], dtype=_np.int64)
        elif decoded.float_features.count(name) > 0:
            result[name] = _np.frombuffer(decoded.float_features[name], dtype=_np.float32)
        elif decoded.bytes_features.count(name) > 0:
            result[name] = decoded.bytes_features[name]
        else:
            result[name] = []

    return result


def decode_example(bytes buffer, names=()):
    decoded = decode_example_internal(buffer, [name.encode('utf-8') for name in names])
    return {key.decode('utf-8'): value for key, value in decoded.items()}


def tf_record_iterator(filename, names=()):
    """
    Iterate over decoded tfrecord dictionaries; it does not perform CRC checks of the records.

    :param filename: path to the file to read records from.
    :param names: feature names of the record to include; reads all by default
    :return: iterator over the decoded TFrecords
    """
    with open(filename, "rb") as file_handle:
        while True:
            # Read the header
            header_str = file_handle.read(8)
            if len(header_str) != 8:
                # Hit EOF so exit
                return
            header = _struct.unpack("Q", header_str)

            # Read the crc32, which is 4 bytes, and disregard
            crc_header_bytes = file_handle.read(4)

            # The length of the header tells us how many bytes the Event
            # string takes
            header_len = int(header[0])
            event_bytes = file_handle.read(header_len)

            # The next 4 bytes contain the crc32 of the Event string,
            # which we check for integrity. Sometimes, the last Event
            # has no crc32, in which case we skip.
            crc_event_bytes = file_handle.read(4)

            # Set the current event to be read later by record() call
            yield decode_example(event_bytes, names or [])
