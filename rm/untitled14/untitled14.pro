QT += testlib
QT += gui
CONFIG += qt warn_on depend_includepath testcase

TEMPLATE = app

SOURCES +=  tst_testgui.cpp

QT += widgets testlib

SOURCES = testgui.cpp

# install
target.path = $$[QT_INSTALL_EXAMPLES]/qtestlib/tutorial3
INSTALLS += target
