from distutils.core import setup, Extension
#from ez_setup import use_setuptools
#use_setuptools()
#from setuptools import setup, find_packages, Extension

__author__ = "Anders Dahnielson"
__doc__ = "PyFTGL"
__version__ = "0.1a"

##########################################################################
## FTGL module

module_ftgl_src = [
    'ftgl.cpp',
    ]

module_ftgl_include_dirs = [
    '/usr/include',
    '/usr/include/freetype2',
    ]

module_ftgl_libs = [
    'GLU',
    'GL',
    'freetype',
    'z',
    'ftgl',
    'boost_python',
    ]

module_ftgl = Extension(
    'FTGL',
    module_ftgl_src,
    include_dirs=module_ftgl_include_dirs,
    libraries=module_ftgl_libs
    )

##########################################################################
## setup

setup(
    name = 'PyFTGL',
    version = __version__,
    description = __doc__,
    author = __author__,
    author_email = 'anders@dahnielson.com',
    url = 'http://code.google.com/p/pyftgl/',
    download_url='http://code.google.com/p/pyftgl/downloads/list',
    license = "GPLv2",
    platforms = "Linux",
    ext_modules = [module_ftgl],
    )
