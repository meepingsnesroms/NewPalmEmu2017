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

#android clang fixes
#android {
    #fix arm only
    #LIBS += $$(ANDROID_NDK_ROOT)/platforms/$$(ANDROID_NDK_PLATFORM)/arch-arm/usr/lib
#}

android {
   DEFINES += OS_ANDROID
}

INCLUDEPATH += libretro \
    hardware \
    hardware/arm \
    hardware/arm/uarm \
    hardware/m68000 \
    palmos \
    palmos/graphics \
    staticlibxmi

SOURCES += \
    hardware/m68000/cpu1.cpp \
    hardware/m68000/cpu2.cpp \
    hardware/m68000/cpu3.cpp \
    hardware/m68000/cpu4.cpp \
    hardware/m68000/cpu5.cpp \
    hardware/m68000/cpu6.cpp \
    hardware/m68000/cpu7.cpp \
    hardware/m68000/cpu8.cpp \
    hardware/m68000/cpu9.cpp \
    hardware/m68000/cpuB.cpp \
    hardware/m68000/cpuC.cpp \
    hardware/m68000/cpuD.cpp \
    hardware/m68000/cpuE.cpp \
    hardware/m68000/cputbl.cpp \
    hardware/m68000/newcpu.cpp \
    hardware/dataexchange.cpp \
    hardware/memmap.cpp \
    hardware/timing.cpp \
    hardware/virtualhardware.cpp \
    palmos/astrology.cpp \
    palmos/audiodriver.cpp \
    palmos/datamanager.cpp \
    palmos/displaydriver.cpp \
    palmos/eventqueue.cpp \
    palmos/floatlib.cpp \
    palmos/launchroutines.cpp \
    palmos/palmapi.cpp \
    palmos/palmmalloc.cpp \
    palmos/prcfile.cpp \
    palmos/resourcelocator.cpp \
    palmos/stdlib68k.cpp \
    main.cpp \
    mainwindow.cpp \
    palmwrapper.cpp \
    processmanager.cpp \
    settingspanel.cpp \
    touchscreen.cpp \
    palmos/appselector.cpp \
    hardware/m68000/cpu0.cpp \
    hardware/m68000/m68kcycles.cpp \
    palmos/graphics/rawimagetools.cpp \
    palmos/graphics/bitmapcompression.cpp \
    palmos/graphics/imagescaling.cpp \
    palmos/graphics/palette.cpp \
    palmos/graphics/fbops.cpp \
    libretro/palmosemulibretro.cpp \
    libretro/libretro.c \
    other/random.cpp \
    palmos/graphics/biosfont.cpp \
    palmos/graphics/bsod.cpp \
    hardware/arm/armshim.cpp \
    hardware/arm/uarm/CPU.c \
    hardware/arm/uarm/icache.c \
    hardware/arm/uarm/math64.c \
    hardware/arm/uarm/rt.c \
    palmos/graphics/bitmaphandler.cpp \
    palmos/sdfilesystem.cpp



HEADERS  += \
    hardware/m68000/cputbl.h \
    hardware/m68000/dballvz.h \
    hardware/m68000/m68k.h \
    hardware/m68000/newcpu.h \
    hardware/dataexchange.h \
    hardware/memmap.h \
    hardware/timing.h \
    hardware/types.h \
    hardware/virtualhardware.h \
    palmos/astrology.h \
    palmos/audiodriver.h \
    palmos/datamanager.h \
    palmos/displaydriver.h \
    palmos/errorcodes.h \
    palmos/eventqueue.h \
    palmos/floatlib.h \
    palmos/launchroutines.h \
    palmos/palmapi.h \
    palmos/palmdatatypes.h \
    palmos/palmdefines.h \
    palmos/palmmalloc.h \
    palmos/palmtypeaccess.h \
    palmos/prcfile.h \
    palmos/resourcelocator.h \
    palmos/stdlib68k.h \
    palmos/trapapilist.h \
    mainwindow.h \
    minifunc.h \
    palmwrapper.h \
    processmanager.h \
    settingarray.h \
    settingspanel.h \
    touchscreen.h \
    palmos/appselector.h \
    palmos/graphics/rawimagetools.h \
    palmos/graphics/palette.h \
    palmos/graphics/bitmapcompression.h \
    libretro/libretro.h \
    libretro/palmosemulibretro.h \
    palmos/graphics/fbops.h \
    palmos/graphics/biosfont.h \
    palmos/graphics/bsod.h \
    hardware/arm/uarm/CPU.h \
    hardware/arm/uarm/icache.h \
    hardware/arm/uarm/math64.h \
    hardware/arm/uarm/typesarm.h \
    hardware/arm/armv5te.h \
    palmos/graphics/imagescaling.h \
    palmos/graphics/bitmaphandler.h \
    palmos/sdfilesystem.h


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
    oldcodechunks.txt \
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
    playpusARMtestJUL212016.txt

ANDROID_PACKAGE_SOURCE_DIR = $$PWD/android

SUBDIRS += \
    NewPalmEmuLibretro.pro \
    NewPalmEmuLibretro.pro \
    NewPalmEmuLibretro.pro \
    NewPalmEmuLibretro.pro \
    NewPalmEmuLibretro.pro \
    NewPalmEmuLibretro.pro \
    NewPalmEmuLibretro.pro

