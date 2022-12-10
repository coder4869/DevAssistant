set(SRC_ROOT   ${CMAKE_CURRENT_LIST_DIR})
set(INC_FILES  ${INC_FILES}  ${SRC_ROOT})
message("SRC_ROOT = ${SRC_ROOT}")


# QtCryptoKit
if(QtCryptoKit)
    set(QtCryptoKit_INC)
    set(QtCryptoKit_LIB)
    include(${SRC_ROOT}/QtCryptoKit/QtCryptoKit.cmake)
    set(THIRD_PARTY_INC ${THIRD_PARTY_INC} ${QtCryptoKit_INC})
    set(THIRD_PARTY_LIB ${THIRD_PARTY_LIB} ${QtCryptoKit_LIB})
endif(QtCryptoKit)

