# Locate BOX2D library 
# This module defines 
# BOX2D_LIBRARY, the name of the library to link against 
# BOX2D_FOUND, if false, do not try to link to BOX2D 
# BOX2D_INCLUDE_DIR, where to find BOX2D headers 
# 



SET(BOX2D_INCLUDE_SEARCH_DIR 
    ~/Library/Frameworks 
    /Library/Frameworks 
    /usr/local/include/Box2D 
    /usr/include/Box2D 
    /usr/local/include 
    /usr/include 
    /sw/include/Box2D # Fink 
    /sw/include 
    /opt/local/include/Box2D # DarwinPorts 
    /opt/local/include 
    /opt/csw/include/Box2D # Blastwave 
    /opt/csw/include 
    /opt/include/Box2D 
    /opt/include 
) 

SET(BOX2D_LIBRARY_SEARCH_DIR 
    ~/Library/Frameworks 
    /Library/Frameworks 
    /usr/local 
    /usr 
    /sw 
    /opt/local 
    /opt/csw 
    /opt 
) 

FIND_LIBRARY(BOX2D_LIBRARY 
	NAMES Box2D 
	HINTS 
	$ENV{SFMLDIR} 
	PATH_SUFFIXES lib64 lib 
	PATHS ${BOX2D_LIBRARY_SEARCH_DIR} 
) 
FIND_PATH(BOX2D_INCLUDE_DIR Box2D.h 
	PATH_SUFFIXES include 
	PATHS ${BOX2D_INCLUDE_SEARCH_DIR} 
) 


SET(BOX2D_FOUND "NO") 
IF(BOX2D_LIBRARY AND BOX2D_INCLUDE_DIR) 
    SET(BOX2D_FOUND "YES") 
ENDIF(BOX2D_LIBRARY AND BOX2D_INCLUDE_DIR) 

INCLUDE(FindPackageHandleStandardArgs) 
FIND_PACKAGE_HANDLE_STANDARD_ARGS(BOX2D DEFAULT_MSG BOX2D_LIBRARY BOX2D_INCLUDE_DIR)
