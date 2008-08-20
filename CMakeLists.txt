CMAKE_MINIMUM_REQUIRED ( VERSION 2.6 )

## ===========================================================================
##  Project Information
## ===========================================================================
PROJECT ( tileqt )
## Package version information.
SET ( PKG_NAME          ${PROJECT_NAME} )
SET ( PKG_MAJOR_VERSION 0 )
SET ( PKG_MINOR_VERSION 5 )
SET ( PKG_BUILD_VERSION 0 )
SET ( PKG_VERSION
     "${PKG_MAJOR_VERSION}.${PKG_MINOR_VERSION}" )
SET ( PKG_NAME_VERSION  ${PKG_NAME}-${PKG_VERSION} )
SET ( PKG_VENDOR        "Georgios Petasis" )
SET ( PKG_HOME_DIR      ${PROJECT_SOURCE_DIR} )

SET ( LOAD_QT_DYNAMICALLY OFF )
SET ( NO_MSVCRT           ON  )
SET ( USE_KDE             OFF )
SET ( VERBOSE             ON  )

IF ( VERBOSE )
# SET ( CMAKE_VERBOSE_MAKEFILE ON )
  SET ( QT2_LOGGING_ENABLED   ON )
ENDIF ( VERBOSE )

SET ( PKG_SOURCES generic/tileQt_Init.cpp
                  generic/tileQt_QApp.cpp
                  generic/tileQt_Utilities.cpp
                  generic/tileQt_Background.cpp
                  generic/tileQt_Button.cpp
                  generic/tileQt_CheckButton.cpp
                  generic/tileQt_RadioButton.cpp
                  generic/tileQt_Menubutton.cpp
                  generic/tileQt_ToolButton.cpp
                  generic/tileQt_Entry.cpp
                  generic/tileQt_Combobox.cpp
                  generic/tileQt_Labelframe.cpp
                  generic/tileQt_Scrollbar.cpp
                  generic/tileQt_Notebook.cpp
                  generic/tileQt_TreeView.cpp
                  generic/tileQt_Progress.cpp
                  generic/tileQt_Scale.cpp
                  generic/tileQt_Paned.cpp
                  generic/tileQt_SizeGrip.cpp
                  generic/tileQt_Separator.cpp
                  generic/tileQt_Arrows.cpp )

MESSAGE ( STATUS "===========================================================" )
MESSAGE ( STATUS " Welcome to the ${PKG_NAME} ${PKG_VERSION} build system!" )
MESSAGE ( STATUS "  * Selected generator:  ${CMAKE_GENERATOR}" )
MESSAGE ( STATUS "  * Operating System ID: "
        ${CMAKE_SYSTEM_NAME}-${CMAKE_SYSTEM_VERSION}-${CMAKE_SYSTEM_PROCESSOR} )
MESSAGE ( STATUS "  * Installation Directory: " ${CMAKE_INSTALL_PREFIX} )
MESSAGE ( STATUS "===========================================================" )

## ===========================================================================
##  Locate Tcl/Tk
## ===========================================================================
MESSAGE ( STATUS "Searching for Tcl/Tk..." )
FIND_PACKAGE ( TCL REQUIRED )
FIND_PACKAGE ( TclStub REQUIRED )
MESSAGE ( STATUS "  TCL_TCLSH:               " ${TCL_TCLSH} )
MESSAGE ( STATUS "  TCL_INCLUDE_PATH:        " ${TCL_INCLUDE_PATH} )
MESSAGE ( STATUS "  TCL_STUB_LIBRARY:        " ${TCL_STUB_LIBRARY} )
MESSAGE ( STATUS "  TCL_LIBRARY:             " ${TCL_LIBRARY} )
MESSAGE ( STATUS "  TK_WISH:                 " ${TK_WISH} )
MESSAGE ( STATUS "  TK_INCLUDE_PATH:         " ${TK_INCLUDE_PATH} )
MESSAGE ( STATUS "  TK_STUB_LIBRARY:         " ${TK_STUB_LIBRARY} )
MESSAGE ( STATUS "  TK_LIBRARY:              " ${TK_LIBRARY} )
# STRING  ( REPLACE stub "" TCL_LIBRARY_STATIC   ${TCL_STUB_LIBRARY} )
# STRING  ( REPLACE stub "" TK_LIBRARY_STATIC    ${TK_STUB_LIBRARY} )
# MESSAGE ( STATUS "  TCL_LIBRARY_STATIC:      " ${TCL_LIBRARY_STATIC} )
# MESSAGE ( STATUS "  TK_LIBRARY_STATIC:       " ${TK_LIBRARY_STATIC} )

IF ( WIN32 AND NO_MSVCRT )
  STRING ( REPLACE /MD  /MT  CMAKE_C_FLAGS_RELEASE   ${CMAKE_C_FLAGS_RELEASE} )
  STRING ( REPLACE /MDd /MTd CMAKE_C_FLAGS_DEBUG     ${CMAKE_C_FLAGS_DEBUG} )
  STRING ( REPLACE /MD  /MT  CMAKE_CXX_FLAGS_RELEASE ${CMAKE_CXX_FLAGS_RELEASE})
  STRING ( REPLACE /MDd /MTd CMAKE_CXX_FLAGS_DEBUG   ${CMAKE_CXX_FLAGS_DEBUG} )
  SET (    CMAKE_EXE_LINKER_FLAGS
        "${CMAKE_EXE_LINKER_FLAGS} /nodefaultlib:MSVCRT.LIB" )
  SET (    CMAKE_EXE_LINKER_FLAGS_RELEASE
        "${CMAKE_EXE_LINKER_FLAGS_RELEASE} LIBCMT.LIB" )
  SET (    CMAKE_EXE_LINKER_FLAGS_DEBUG
        "${CMAKE_EXE_LINKER_FLAGS_DEBUG} LIBCMTD.LIB" )
  SET (    CMAKE_SHARED_LINKER_FLAGS
        "${CMAKE_SHARED_LINKER_FLAGS} /nodefaultlib:MSVCRT.LIB" )
  SET (    CMAKE_SHARED_LINKER_FLAGS_RELEASE
        "${CMAKE_SHARED_LINKER_FLAGS_RELEASE} LIBCMT.LIB" )
  SET (    CMAKE_SHARED_LINKER_FLAGS_DEBUG
        "${CMAKE_SHARED_LINKER_FLAGS_DEBUG}
         /nodefaultlib:LIBCMT.LIB LIBCMTD.LIB" )
  ADD_DEFINITIONS ( -D_STATIC_CPPLIB )
  ADD_DEFINITIONS ( -D_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES=1 )
  ADD_DEFINITIONS ( -D_CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES_COUNT=1 )
ENDIF ( WIN32 AND NO_MSVCRT )

IF ( WIN32 )
  ADD_DEFINITIONS ( -DWIN32 )
  ADD_DEFINITIONS ( -D_WIN32 )
  ADD_DEFINITIONS ( -D_WINDOWS )
  ADD_DEFINITIONS ( -D__WIN32__ )
  SET ( CMAKE_SHARED_LIBRARY_PREFIX lib )
ENDIF ( WIN32 )

IF ( LOAD_QT_DYNAMICALLY )
  MESSAGE ( STATUS "Qt will be loaded dynamically!" )
  ADD_DEFINITIONS   ( -DTILEQT_LOAD_QT_DYNAMICALLY )
ENDIF ( LOAD_QT_DYNAMICALLY )
IF ( CMAKE_BUILD_TYPE STREQUAL Debug )
  ADD_DEFINITIONS   ( -DTILEQT_SYNCHRONIZE )
  ADD_DEFINITIONS   ( -DTILEQT_VERBOSE_XERROR_HANDLER )
ENDIF ( CMAKE_BUILD_TYPE STREQUAL Debug )
ADD_DEFINITIONS     ( -DTILEQT_INSTALL_XERROR_HANDLER )
ADD_DEFINITIONS     ( -DUSE_TCL_STUBS )
ADD_DEFINITIONS     ( -DUSE_TK_STUBS )
ADD_DEFINITIONS     ( -DUSE_TTK_STUBS )
ADD_DEFINITIONS     ( -DPACKAGE_NAME="${PKG_NAME}" )
ADD_DEFINITIONS     ( -DPACKAGE_VERSION="${PKG_VERSION}" )
INCLUDE_DIRECTORIES ( ${TCL_INCLUDE_PATH} )
INCLUDE_DIRECTORIES ( ${TK_INCLUDE_PATH} )
INCLUDE_DIRECTORIES ( ${PROJECT_SOURCE_DIR}/generic )

## ===========================================================================
##  Locate Qt...
## ===========================================================================
SET ( DESIRED_QT_VERSION 4 )
MESSAGE ( STATUS "Searching for Qt..." )
FIND_PACKAGE ( Qt REQUIRED )

IF ( QT4_FOUND )
  INCLUDE ( ${QT_USE_FILE} )
ENDIF ( QT4_FOUND )

FIND_PACKAGE ( X11 )

SET ( PKG_TARGET_LIB_NAME ${PKG_NAME}${PKG_VERSION} )
## ===========================================================================
##  Target: tileqt shared library
## ===========================================================================
MESSAGE ( STATUS "===========================================================" )
MESSAGE ( STATUS "   ++++ Shared Library: ${PKG_TARGET_LIB_NAME} ++++" )
MESSAGE ( STATUS "===========================================================" )
ADD_LIBRARY ( ${PKG_TARGET_LIB_NAME} SHARED ${PKG_SOURCES} )
TARGET_LINK_LIBRARIES ( ${PKG_TARGET_LIB_NAME} ${TCL_STUB_LIBRARY} )
TARGET_LINK_LIBRARIES ( ${PKG_TARGET_LIB_NAME} ${TK_STUB_LIBRARY} )
IF ( TTK_STUB_LIBRARY )
  TARGET_LINK_LIBRARIES ( ${PKG_TARGET_LIB_NAME} ${TTK_STUB_LIBRARY} )
ENDIF ( TTK_STUB_LIBRARY )
IF ( LOAD_QT_DYNAMICALLY )
ELSE ( LOAD_QT_DYNAMICALLY )
  TARGET_LINK_LIBRARIES ( ${PKG_TARGET_LIB_NAME} ${QT_LIBRARIES} )
# TARGET_LINK_LIBRARIES ( ${PKG_TARGET_LIB_NAME} ${X11_Xft_LIB} )
# TARGET_LINK_LIBRARIES ( ${PKG_TARGET_LIB_NAME} ${X11_Xscreensaver_LIB} )
ENDIF ( LOAD_QT_DYNAMICALLY )

FILE ( WRITE library/pkgIndex.tcl 
"package ifneeded ttk::theme::tileqt ${PKG_VERSION} \\
  [list load [file join $dir lib${PKG_NAME}${PKG_VERSION}[info sharedlibextension]] tileqt]" )

INSTALL ( TARGETS ${PKG_TARGET_LIB_NAME}
          RUNTIME DESTINATION ${PKG_TARGET_LIB_NAME}
          LIBRARY DESTINATION ${PKG_TARGET_LIB_NAME}
          ARCHIVE DESTINATION ${PKG_TARGET_LIB_NAME} )
INSTALL ( FILES library/pkgIndex.tcl library/tileqt.tcl
          DESTINATION ${PKG_TARGET_LIB_NAME} )

ENABLE_TESTING ( )
ADD_TEST ( demo   ${TK_WISH} ${PROJECT_SOURCE_DIR}/demos/demo.tcl )
ADD_TEST ( styles ${TK_WISH} ${PROJECT_SOURCE_DIR}/demos/WidgetStates.tcl )
