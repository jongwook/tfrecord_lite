from distutils.core import setup, Extension
from Cython.Build import cythonize

setup(
    name = 'tfrecord_lite',
    ext_modules = cythonize(Extension(
        'tfrecord_lite',
        sources=[
            'tfrecord_lite.pyx',
            'src/tfrecord_lite.cpp',
            'src/example.pb.c',
            'src/feature.pb.c',
            'src/pb_common.c',
            'src/pb_decode.c',
            'src/pb_encode.c'],
        language='c++',
        include_dirs=['src/']
    ))
)
