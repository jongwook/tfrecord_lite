from setuptools import setup, Extension
from Cython.Build import cythonize

setup(
    name = 'tfrecord_lite',
    version = '0.0.2',
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
            'src/example.pb.c',
            'src/feature.pb.c',
            'src/pb_common.c',
            'src/pb_decode.c',
            'src/pb_encode.c'],
        language='c++',
        include_dirs=['src/']
    ))
)
