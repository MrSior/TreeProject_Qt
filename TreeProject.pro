QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    avl_node.cpp \
    avl_tree.cpp \
    main.cpp \
    mainwindow.cpp \
    rectangulartest.cpp \
    splay_graphics_item.cpp \
    splay_node.cpp \
    splay_tree.cpp \
    treap.cpp \
    treap_graphics_item.cpp \
    treap_node.cpp

HEADERS += \
    avl_node.h \
    avl_tree.h \
    mainwindow.h \
    rectangulartest.h \
    splay_graphics_item.h \
    splay_node.h \
    splay_tree.h \
    treap.h \
    treap_graphics_item.h \
    treap_node.h

FORMS += \
    mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
