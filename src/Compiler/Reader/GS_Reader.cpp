#include "../../../include/Compiler/Reader/GS_Reader.h"

namespace GSLanguageCompiler {
    std::vector<std::string> GS_Reader::readFile() {
        char symbol;
        std::string line;
        std::ifstream stream;
#if defined(__WIN32)
        try {
            stream.open(this->filename, std::ios::binary);
        } catch (std::exception &exception) {
            throw Exceptions::GS_ReaderException(exception.what());
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

        stream.close();
#else
#error Platform not supported!
#endif // __WIN32
        return this->input;
    }
}