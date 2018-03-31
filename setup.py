import os
import sys
from setuptools import setup, Extension
from Cython.Build import cythonize

extra_compile_args = []

if 'linux' in sys.platform or 'darwin' in sys.platform:
    extra_compile_args += ['-O3', '-Wall', '-std=c++11']

if 'darwin' in sys.platform:
    extra_compile_args += ['-stdlib=libc++']

setup(
    name = 'tfrecord_lite',
    version = '0.0.4',
    description = 'A lightweight tfrecord parser',
    url = 'https://github.com/jongwook/tfrecord_lite',
    author = 'Jong Wook Kim',
    author_email = 'jongwook@nyu.edu',
    license = 'MIT',
    classifiers = [
        'Development Status :: 3 - Alpha',
        'Intended Audience :: Developers',
        'License :: OSI Approved :: MIT License',
        'Programming Language :: Python :: 3',
        'Programming Language :: Python :: 3.6',
    ],
    keywords = 'tfrecord',
    project_urls = {
        'Source': 'https://github.com/jongwook/tfrecord_lite',
        'Tracker': 'https://github.com/jongwook/tfrecord_lite/issues'
    },
    install_requires = ['numpy'],
    python_requires = '>=3.6',
    package_data = {
        'tfrecord_lite': ['src/*', 'tfrecrod_lite.pyx']
    },
    ext_modules = cythonize(Extension(
        'tfrecord_lite',
        sources=[
            'tfrecord_lite.pyx',
            'src/tfrecord_lite.cpp',
            'src/example.pb.cpp',
            'src/feature.pb.cpp',
            'src/pb_common.cpp',
            'src/pb_decode.cpp',
            'src/pb_encode.cpp'],
        extra_compile_args=extra_compile_args,
        language='c++',
        include_dirs=['src/']
    ))
)
