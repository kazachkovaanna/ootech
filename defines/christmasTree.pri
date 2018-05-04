!isEmpty(CRISTMAS_TREE_INCLUDED):error("cristmasTree.pri already included")
CRISTMAS_TREE_INCLUDED = 1

BIN_DIR = $${PROJECT_DEST_BIN_PATH}
LIB_DIR = $${PROJECT_DEST_LIB_PATH}

isEmpty(PROJECT_DEST_LIB_PATH) {
    LIB_DIR = $$PWD/../cristmas_tree/lib
}

isEmpty(PROJECT_DEST_BIN_PATH) {
    BIN_DIR = $$PWD/../cristmas_tree/bin
}

QMAKE_LIBDIR += $$LIB_DIR $(QTDIR)/plugins/imageformats

CONFIG += c++11
