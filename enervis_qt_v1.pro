#-------------------------------------------------
#
# Project created by QtCreator 2012-10-28T20:32:50
# SourcePath = C:\\syncdir\\cloud002\\Programmazione\\qt_workspace\\enervis_qt_v1
# Compile with MinGW with debug or release CONFIG option
#----------------------------------------------...---

QT       += core gui
# ensure one "debug_and_release" in CONFIG, for clarity...
debug_and_release {
    CONFIG -= debug_and_release
    CONFIG += debug_and_release
}
# ensure one "debug" or "release" in CONFIG so they can be used as
# conditionals instead of writing "CONFIG(debug, debug|release)"...
CONFIG(debug, debug|release) {
    CONFIG -= debug release
    CONFIG += debug
}
CONFIG(release, debug|release) {
    CONFIG -= debug release
    CONFIG += release
}

TARGET = enervis_qt_v1
TEMPLATE = app


SOURCES +=  main.cpp\
            okFrontPanelDLL_ben.cpp \
            main_window_widget.cpp \
            form_configure_firmware.cpp \
            enervis.cpp \
            appwindow.cpp \
    form_tool_webcam.cpp \
    dialog_conf_views.cpp \
    view_class.cpp \
    view_class_container.cpp \
    dialog_save.cpp \
    acquisition_class.cpp \
    view_combo_class.cpp \
    view_combo_class_container.cpp \
    dialog_conf_combo_views.cpp \
    dialog_save_2.cpp

HEADERS  += appwindow.h \
            okFrontPanelDLL_ben.h \
            main_window_widget.h \
            global_variables.h \
            form_configure_firmware.h \
            enervis.h \
    form_tool_webcam.h \
    dialog_conf_views.h \
    view_class.h \
    view_class_container.h \
    dialog_save.h \
    acquisition_class.h \
    view_combo_class.h \
    view_combo_class_container.h \
    dialog_conf_combo_views.h \
    dialog_save_2.h


FORMS    += main_window_widget.ui \
            form_configure_firmware.ui \
    form_tool_webcam.ui \
    dialog_conf_views.ui \
    dialog_save.ui \
    dialog_conf_combo_views.ui \
    dialog_save_2.ui

INCLUDEPATH += C:\\opencv\\build\\include

BuildPath = C:\\syncdir\\uncloud\\build\\enervis_qt_v1

debug {
    DESTDIR = $${BuildPath}\\debug
    LIBS += -LC:\\opencv\\builds_with_Qt\\Debug\\bin \
        -lopencv_calib3d242d \
        -lopencv_contrib242d \
        -lopencv_core242d   \
        -lopencv_features2d242d \
        -lopencv_flann242d \
        -lopencv_gpu242d \
        -lopencv_highgui242d \
        -lopencv_imgproc242d \
        -lopencv_legacy242d \
        -lopencv_ml242d \
        -lopencv_objdetect242d  \
        -lopencv_nonfree242d
}
release {
    DESTDIR = $${BuildPath}\\release
    LIBS += -LC:\\opencv\\builds_with_Qt\\Release\\bin \
        -lopencv_calib3d242 \
        -lopencv_contrib242 \
        -lopencv_core242   \
        -lopencv_features2d242 \
        -lopencv_flann242 \
        -lopencv_gpu242 \
        -lopencv_highgui242 \
        -lopencv_imgproc242 \
        -lopencv_legacy242 \
        -lopencv_ml242 \
        -lopencv_objdetect242  \
        -lopencv_nonfree242
}
OBJECTS_DIR = $${DESTDIR}/.obj
MOC_DIR = $${DESTDIR}/.moc
RCC_DIR =$${DESTDIR}/.rcc
UI_DIR = $${DESTDIR}/.ui
