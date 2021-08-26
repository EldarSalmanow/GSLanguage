#include <Reader/GS_Reader.h>

namespace GSLanguageCompiler {

    GS_Reader::GS_Reader(GSString filename)
            : _filename(std::move(filename)) {}

    GSText GS_Reader::readFile() {
        GSChar symbol;
        GSString line;
        std::ifstream stream;

        stream.open(_filename, std::ios::binary);

        if (!stream.is_open()) {
            Exceptions::errorHandler.print(Exceptions::ErrorLevel::ERROR_LVL,
                                           "Not found file for reading!");

            Exceptions::errorHandler.print(Exceptions::ErrorLevel::NOTE_LVL,
                                           "Filename: \"" + _filename + "\"!");

            Exceptions::errorHandler.throw_();
        }

#if defined(OS_WINDOWS)
        try {
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

            Exceptions::errorHandler.print(Exceptions::ErrorLevel::FATAL_LVL,
                                           exception.what());

            Exceptions::errorHandler.print(Exceptions::ErrorLevel::NOTE_LVL,
                                           "Please, report this fatal error to GSLanguageCompiler repository.");

            Exceptions::errorHandler.throw_();
        } catch (...) {
            Exceptions::errorHandler.print(Exceptions::ErrorLevel::FATAL_LVL,
                                           "Unknown fatal reading file error!");

            Exceptions::errorHandler.print(Exceptions::ErrorLevel::NOTE_LVL,
                                           "Please, report this fatal error to GSLanguageCompiler repository.");

            Exceptions::errorHandler.throw_();
        }
#endif

    	return _input;
    }

}