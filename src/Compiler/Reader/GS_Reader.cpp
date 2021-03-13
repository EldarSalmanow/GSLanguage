#include "../../../include/Compiler/Reader/GS_Reader.h"

namespace GSLanguageCompiler {

    GSText GS_Reader::readFile() {
        char symbol;
        std::string line;
        std::ifstream stream;
#if defined(OS_WINDOWS)
        try {
            stream.open(this->filename, std::ios::binary);

            if (!stream.is_open()) {
                throw Exceptions::GS_ReaderException("Not found file \'" + this->filename + "\'!");
            }

            while (true) {
                stream.get(symbol);

                if (stream.eof()) {
                    this->input.emplace_back(line);
                    break;
                }

                if (symbol == '\r' && line.empty()) {
                    stream.get();
                    continue;
                } else if (symbol == '\r') {
                    this->input.emplace_back(line);
                    line.clear();
                    stream.get(); // skipping '\n' (specific for Windows system)
                    continue;
                } else {
                    line += symbol;
                }
            }
        } catch (std::exception &exception) {
            if (stream.is_open()) {
                stream.close();
            }
            throw Exceptions::GS_ReaderException(exception.what());
        }
#endif
    	return this->input;
    }

}