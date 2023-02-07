#ifndef GSLANGUAGE_GS_STREAM_H
#define GSLANGUAGE_GS_STREAM_H

#include <GSCrossPlatform/CrossPlatform.h>

namespace GSLanguageCompiler::IO {

    /**
     * Input stream type
     */
    using InputStream = std::istream;

    /**
     * Output stream type
     */
    using OutputStream = std::ostream;

    /**
     * Class for setting and managing "standard" IO streams
     */
    class GS_StdIOStreamsManager {
    public:

        /*
         *
         * GS_StdIOStreamsManager PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for standard IO streams manager
         * @param standardIn Standard input stream
         * @param standardOut Standard output stream
         * @param standardErr Standard error stream
         * @param standardLog Standard logging stream
         */
        GS_StdIOStreamsManager(LRef<InputStream> standardIn,
                               LRef<OutputStream> standardOut,
                               LRef<OutputStream> standardErr,
                               LRef<OutputStream> standardLog);

    public:

        /*
         *
         * GS_StdIOStreamsManager PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating standard IO streams manager
         * @param standardIn Standard input stream
         * @param standardOut Standard output stream
         * @param standardErr Standard error stream
         * @param standardLog Standard logging stream
         * @return Standard IO streams manager ptr
         */
        static std::unique_ptr<GS_StdIOStreamsManager> Create(LRef<InputStream> standardIn,
                                                              LRef<OutputStream> standardOut,
                                                              LRef<OutputStream> standardErr,
                                                              LRef<OutputStream> standardLog);

        /**
         * Creating standard IO streams manager with console standard IO streams
         * @return Standard IO streams manager ptr
         */
        static std::unique_ptr<GS_StdIOStreamsManager> Create();

    public:

        /*
         *
         * GS_StdIOStreamsManager PUBLIC METHODS
         *
         */

        /**
         * Getting standard input stream for reading data from stream
         * @return Standard input stream
         */
        LRef<InputStream> In();

        /**
         * Getting standard output stream for writing data in stream
         * @return Standard output stream
         */
        LRef<OutputStream> Out();

        /**
         * Getting standard error stream for writing data in stream
         * @return Standard error stream
         */
        LRef<OutputStream> Err();

        /**
         * Getting standard logging stream for writing data in stream
         * @return Standard logging stream
         */
        LRef<OutputStream> Log();

    private:

        /*
         *
         * GS_StdIOStreamsManager PRIVATE FIELDS
         *
         */

        /**
         * Standard input stream
         */
        LRef<InputStream> _standardIn;

        /**
         * Standard output stream
         */
        LRef<OutputStream> _standardOut;

        /**
         * Standard error stream
         */
        LRef<OutputStream> _standardErr;

        /**
         * Standard logging stream
         */
        LRef<OutputStream> _standardLog;
    };

    /**
     * Standard IO streams manager ptr type
     */
    using GSStdIOStreamsManagerPtr = std::unique_ptr<GS_StdIOStreamsManager>;

}

#endif //GSLANGUAGE_GS_STREAM_H
