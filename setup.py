import sys
from setuptools import setup, Extension

try:
    from Cython.Build import cythonize

    extension_source = "tfrecord_lite.pyx"
except ImportError:
    def cythonize(extension):
        return [extension]

    extension_source = "tfrecord_lite.cpp"


extra_compile_args=[]
extra_link_args=[]

if "linux" in sys.platform or "darwin" in sys.platform:
    extra_compile_args += ["-O3", "-Wall", "-std=c++11"]

if "darwin" in sys.platform:
    extra_compile_args += ["-mmacosx-version-min=10.9"]
    extra_link_args=["-stdlib=libc++", "-mmacosx-version-min=10.9"]

setup(
    name="tfrecord_lite",
    version="0.0.7",
    description="A lightweight tfrecord parser",
    url="https://github.com/jongwook/tfrecord_lite",
    author="Jong Wook Kim",
    author_email="jongwook@nyu.edu",
    license="MIT",
    classifiers=[
        "Development Status :: 3 - Alpha",
        "Intended Audience :: Developers",
        "License :: OSI Approved :: MIT License",
        "Programming Language :: Python :: 3",
        "Programming Language :: Python :: 3.6",
        "Programming Language :: Python :: 3.7",
        "Programming Language :: Python :: 3.8",
    ],
    keywords="tfrecord",
    project_urls={
        "Source": "https://github.com/jongwook/tfrecord_lite",
        "Tracker": "https://github.com/jongwook/tfrecord_lite/issues"
    },
    install_requires=["numpy"],
    python_requires=">=3.6",
    package_data={
        "tfrecord_lite": ["src/*", "tfrecrod_lite.pyx", "tfrecrod_lite.cpp"]
    },
    ext_modules=cythonize(Extension(
        "tfrecord_lite",
        sources=[
            extension_source,
            "src/tfrecord_lite.cpp",
            "src/example.pb.cpp",
            "src/feature.pb.cpp",
            "src/pb_common.cpp",
            "src/pb_decode.cpp",
            "src/pb_encode.cpp"],
        extra_compile_args=extra_compile_args,
        extra_link_args=extra_link_args,
        language="c++",
        include_dirs=["src/"]
    ))
)
