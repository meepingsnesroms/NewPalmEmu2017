#-------------------------------------------------
#
# Project created by QtCreator 2015-08-01T10:51:58
#
#-------------------------------------------------

QT       += core gui multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NewPalmEmu
TEMPLATE = app

QMAKE_MACOSX_DEPLOYMENT_TARGET = 10.11
QMAKE_MAC_SDK = macosx10.12


CONFIG += c++11
DEFINES += __STDC_LIMIT_MACROS #required for bit type limits in gcc

CONFIG(debug, debug|release) {
    #debug
    #DEFINES += _DBGMODE TESTRENDERFONTS
    DEFINES += _DBGMODE
} else {
    #release
}

android {
   DEFINES += OS_ANDROID
}

INCLUDEPATH += libretro \
    emucore/hardware \
    emucore/hardware/arm \
    emucore/hardware/arm/uarm \
    emucore/hardware/m68000 \
    emucore/palmos \
    emucore/palmos/graphics \
    emucore/debug \
    emucore/palmos/graphics/ugui \
    emucore

SOURCES += \
    emucore/hardware/arm/armshim.cpp \
    emucore/hardware/m68000/cpu0.cpp \
    emucore/hardware/m68000/cpu1.cpp \
    emucore/hardware/m68000/cpu2.cpp \
    emucore/hardware/m68000/cpu3.cpp \
    emucore/hardware/m68000/cpu4.cpp \
    emucore/hardware/m68000/cpu5.cpp \
    emucore/hardware/m68000/cpu6.cpp \
    emucore/hardware/m68000/cpu7.cpp \
    emucore/hardware/m68000/cpu8.cpp \
    emucore/hardware/m68000/cpu9.cpp \
    emucore/hardware/m68000/cpuB.cpp \
    emucore/hardware/m68000/cpuC.cpp \
    emucore/hardware/m68000/cpuD.cpp \
    emucore/hardware/m68000/cpuE.cpp \
    emucore/hardware/m68000/cputbl.cpp \
    emucore/hardware/m68000/newcpu.cpp \
    emucore/hardware/dataexchange.cpp \
    emucore/hardware/memmap.cpp \
    emucore/hardware/virtuallcd.cpp \
    emucore/palmos/graphics/bitmapcompression.cpp \
    emucore/palmos/graphics/bitmaphandler.cpp \
    emucore/palmos/graphics/bsod.cpp \
    emucore/palmos/graphics/fbops.cpp \
    emucore/palmos/graphics/imagescaling.cpp \
    emucore/palmos/graphics/palette.cpp \
    emucore/palmos/graphics/rawimagetools.cpp \
    emucore/palmos/audiodriver.cpp \
    emucore/palmos/datamanager.cpp \
    emucore/palmos/displaydriver.cpp \
    emucore/palmos/eventqueue.cpp \
    emucore/palmos/floatlib.cpp \
    emucore/palmos/launchroutines.cpp \
    emucore/palmos/palmapi.cpp \
    emucore/palmos/palmlibc.cpp \
    emucore/palmos/palmmalloc.cpp \
    emucore/palmos/prcfile.cpp \
    emucore/palmos/resourcelocator.cpp \
    emucore/palmos/sdfilesystem.cpp \
    emucore/palmos/stdlib68k.cpp \
    emucore/palmos/zodiacapi.cpp \
    emucore/palmwrapper.cpp \
    emucore/hardware/arm/uarm/CPU.c \
    emucore/hardware/arm/uarm/icache.c \
    emucore/hardware/arm/uarm/math64.c \
    emucore/hardware/arm/uarm/rt.c \
    libretro/palmosemulibretro.cpp \
    main.cpp \
    mainwindow.cpp \
    processmanager.cpp \
    settingspanel.cpp \
    touchscreen.cpp \
    libretro/libretro.c \
    emucore/hardware/romutils.cpp \
    emucore/palmosv4.1-en-m515.cpp \
    emucore/debug/trapnumtoname.cpp \
    emucore/palmos/graphics/ugui/ugui.c \
    emucore/palmos/graphics/formrenderer.cpp



HEADERS  += \
    emucore/hardware/arm/uarm/CPU.h \
    emucore/hardware/arm/uarm/icache.h \
    emucore/hardware/arm/uarm/math64.h \
    emucore/hardware/arm/uarm/typesarm.h \
    emucore/hardware/arm/armv5te.h \
    emucore/hardware/m68000/cputbl.h \
    emucore/hardware/m68000/m68k.h \
    emucore/hardware/m68000/newcpu.h \
    emucore/hardware/dataexchange.h \
    emucore/hardware/memmap.h \
    emucore/hardware/virtuallcd.h \
    emucore/palmos/graphics/bitmapcompression.h \
    emucore/palmos/graphics/bitmaphandler.h \
    emucore/palmos/graphics/bsod.h \
    emucore/palmos/graphics/fbops.h \
    emucore/palmos/graphics/imagescaling.h \
    emucore/palmos/graphics/palette.h \
    emucore/palmos/graphics/rawimagetools.h \
    emucore/palmos/audiodriver.h \
    emucore/palmos/datamanager.h \
    emucore/palmos/displaydriver.h \
    emucore/palmos/errorcodes.h \
    emucore/palmos/eventqueue.h \
    emucore/palmos/floatlib.h \
    emucore/palmos/launchroutines.h \
    emucore/palmos/palmapi.h \
    emucore/palmos/palmdatatypes.h \
    emucore/palmos/palmdefines.h \
    emucore/palmos/palmlibc.h \
    emucore/palmos/palmmalloc.h \
    emucore/palmos/palmtypeaccess.h \
    emucore/palmos/prcfile.h \
    emucore/palmos/resourcelocator.h \
    emucore/palmos/sdfilesystem.h \
    emucore/palmos/stdlib68k.h \
    emucore/palmos/trapapilist.h \
    emucore/palmos/zodiacapi.h \
    emucore/minifunc.h \
    emucore/palmwrapper.h \
    libretro/libretro.h \
    libretro/palmosemulibretro.h \
    mainwindow.h \
    processmanager.h \
    settingarray.h \
    settingspanel.h \
    touchscreen.h \
    emucore/types.h \
    emucore/palmos/romloader.h \
    emucore/hardware/romutils.h \
    emucore/palmosv4.1-en-m515.h \
    emucore/debug/trapnumtoname.h \
    emucore/debug/dbgmacros.h \
    emucore/palmos/graphics/ugui/ugui.h \
    emucore/palmos/graphics/ugui/ugui_config.h


FORMS    += mainwindow.ui \
    settingspanel.ui

CONFIG += mobility
MOBILITY =

DISTFILES += \
    palmtypelayouts.txt \
    android/AndroidManifest.xml \
    android/gradle/wrapper/gradle-wrapper.jar \
    android/gradlew \
    android/res/values/libs.xml \
    android/build.gradle \
    android/gradle/wrapper/gradle-wrapper.properties \
    android/gradlew.bat \
    ToDo.txt \
    debuglogOCT242015.txt \
    m68kromvectors.txt \
    Notes.txt \
    debuglogzapNOV112015.txt \
    CREDITS \
    palmos/androidcustomtostring \
    androidcustomtostring.txt \
    android-libNewPalmEmu.so-deployment-settings.json \
    android/res/drawable-ldpi/icon.png \
    android/gradle.properties \
    android/local.properties \
    removedJUL132016.txt \
    galaxdebuglogJUL132016.txt \
    playpusARMtestJUL212016.txt \
    .astylerc

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

SUBDIRS += \
    NewPalmEmuLibretro.pro

