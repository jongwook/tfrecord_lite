tfrecord_lite
=============

This is a simple library to parse `.tfrecord` files without having to use [TensorFlow](https://github.com/tensorflow/tensorflow)'s `Session`s and `Tensor`s, so that it is easier to use in a framework-agnostic way. It is written using [nanopb](https://github.com/nanopb/nanopb) and [Cython](https://github.com/cython/cython).

```python
In [1]: import tensorflow as tf
   ...: from tfrecord_lite import decode_example
   ...:
   ...: it = tf.python_io.tf_record_iterator('nsynth-test.tfrecord')
   ...: decode_example(next(it))
   ...:
Out[1]:
{'audio': array([ 3.8138387e-06, -3.8721851e-06,  3.9331076e-06, ...,
        -3.6526076e-06,  3.7041993e-06, -3.7578957e-06], dtype=float32),
 'instrument': array([417], dtype=int64),
 'instrument_family': array([0], dtype=int64),
 'instrument_family_str': [b'bass'],
 'instrument_source': array([2], dtype=int64),
 'instrument_source_str': [b'synthetic'],
 'instrument_str': [b'bass_synthetic_033'],
 'note': array([149013], dtype=int64),
 'note_str': [b'bass_synthetic_033-100-100'],
 'pitch': array([100], dtype=int64),
 'qualities': array([0, 0, 0, 0, 0, 0, 0, 0, 0, 0], dtype=int64),
 'sample_rate': array([16000], dtype=int64),
 'velocity': array([100], dtype=int64)}
```

TODO
----

- encoder/writer
- reimplement `tf_record_iterator` in Cython to remove TensorFlow dependency
- publish to PyPI
