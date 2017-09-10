cmake_minimum_required(VERSION 2.8.12)
set(BASKET_DISABLE_GPG "0" CACHE BOOL "Disables GPG Support")

include(FeatureSummary)

find_package(X11 REQUIRED)

# KDE
find_package(ECM REQUIRED NO_MODULE)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${ECM_MODULE_PATH})

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
IF(NOT BASKET_DISABLE_GPG)
  find_package(Gpgme)
ENDIF(NOT BASKET_DISABLE_GPG)

# libgit2
find_package(Libgit2)
IF(LIBGIT2_FOUND)
  include_directories(${LIBGIT2_INCLUDE_DIR})
  add_definitions(-DWITH_LIBGIT2)
ELSE(LIBGIT2_FOUND)
  message("libgit2 not found, configuring without")
ENDIF(LIBGIT2_FOUND)



if (BUILD_KPARTS)
find_package(KdepimLibs REQUIRED)
include_directories(${KDEPIMLIBS_INCLUDE_DIRS})
endif (BUILD_KPARTS)

find_package(Qt5 REQUIRED COMPONENTS
  Concurrent
  Core
  DBus
  Gui
  Widgets
  Quick
  QuickWidgets
  Xml
)

include(KDECompilerSettings)
include(KDEInstallDirs)
include(ECMInstallIcons)
include(KDECMakeSettings)

find_package(KF5 REQUIRED COMPONENTS
  Archive
  Completion
  Config
  ConfigWidgets #KCM
  CoreAddons
  Crash
  DBusAddons
  DocTools
  FileMetaData
  GlobalAccel
  GuiAddons
  I18n
  IconThemes
  KCMUtils
  KIO
  Notifications
  Parts
  Service
  TextWidgets
  WidgetsAddons
  WindowSystem
  XmlGui
)

find_package(Phonon4Qt5 REQUIRED)

#find_package(KF5 COMPONENTS Baloo)


IF(GPGME_FOUND)
  SET(HAVE_LIBGPGME 1)
  SET(LARGEFILE_SOURCE_1)
  ADD_DEFINITIONS(-D_FILE_OFFSET_BITS=64)
ELSE(GPGME_FOUND)
  IF (BASKET_DISABLE_GPG)
    MESSAGE("GPG disabled, configuring without")
  ELSE (BASKET_DISABLE_GPG)
    MESSAGE("GPG not found, configuring without")
  ENDIF (BASKET_DISABLE_GPG)
ENDIF(GPGME_FOUND)

#IF(KF5BALOO_FOUND)
#  SET(HAVE_BALOO 1)
#ENDIF(KF5BALOO_FOUND)

#TODO: find meinproc

#Make libbasketcommon search for translations in basket.mo
ADD_DEFINITIONS(-DTRANSLATION_DOMAIN=\"basket\")

CONFIGURE_FILE(${CMAKE_CURRENT_SOURCE_DIR}/config.h.cmake ${CMAKE_CURRENT_BINARY_DIR}/config.h )
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_BINARY_DIR})

add_subdirectory(doc)
add_subdirectory(src)
add_subdirectory(po)
add_subdirectory(tags)
add_subdirectory(welcome)
add_subdirectory(backgrounds)
add_subdirectory(images)
add_subdirectory(file-integration)

feature_summary(WHAT ALL FATAL_ON_MISSING_REQUIRED_PACKAGES)
