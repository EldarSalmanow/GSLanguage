#include <GS_BCWriter.h>

namespace GSBCCodeGen {

    GS_BCWriter::GS_BCWriter(GSString filename)
            : _filename(std::move(filename)) {}

    GSVoid GS_BCWriter::write(GSByteCode bytecode) {
        _bytecode = std::move(bytecode);

        std::ofstream stream;

        stream.open(_filename, std::ios::binary);

        if (!stream.is_open()) {
            throw std::runtime_error("Can`t open file!");
        }

        for (auto &byte : _bytecode) {
            auto symbol = static_cast<GSChar>(byte);

            stream.write(&symbol, 1);
        }

        stream.close();
    }

}
