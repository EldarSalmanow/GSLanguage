#include <Reader/GS_Reader.h>

namespace GSLanguageCompiler {

    GS_Reader::GS_Reader(GSString filename)
            : _filename(filename) {}

    GSText GS_Reader::readFile() {
        GSChar symbol;
        GSString line;
        std::ifstream stream;

#if defined(OS_WINDOWS)
        try {
            stream.open(_filename, std::ios::binary);

            if (!stream.is_open()) {
                throw Exceptions::GS_Exception(("Not found file \'" + _filename + "\'!").c_str());
            }

            while (true) {
                stream.get(symbol);

                if (stream.eof()) {
                    _input.emplace_back(line);

                    break;
                }

                if (symbol == '\r') {
                    _input.emplace_back(line);

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

            throw Exceptions::GS_Exception(exception.what());
        }
#endif

    	return _input;
    }

}