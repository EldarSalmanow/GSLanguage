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
     * Class for setting and managing standard IO streams
     */
    class GS_StdIOStreamManager {
    public:

        /*
         *
         * GS_StdIOStreamManager PUBLIC CONSTRUCTORS
         *
         */

        /**
         * Constructor for standard IO stream manager
         * @param standardIn Standard input stream
         * @param standardOut Standard output stream
         * @param standardErr Standard error stream
         * @param standardLog Standard logger stream
         */
        GS_StdIOStreamManager(LRef<InputStream> standardIn,
                              LRef<OutputStream> standardOut,
                              LRef<OutputStream> standardErr,
                              LRef<OutputStream> standardLog);

    public:

        /*
         *
         * GS_StdIOStreamManager PUBLIC STATIC CREATE METHODS
         *
         */

        /**
         * Creating standard IO stream manager
         * @param standardIn Standard input stream
         * @param standardOut Standard output stream
         * @param standardErr Standard error stream
         * @param standardLog Standard logger stream
         * @return Standard IO stream manager ptr
         */
        static std::unique_ptr<GS_StdIOStreamManager> Create(LRef<InputStream> standardIn,
                                                             LRef<OutputStream> standardOut,
                                                             LRef<OutputStream> standardErr,
                                                             LRef<OutputStream> standardLog);

        /**
         * Creating standard IO stream manager with console standard IO streams
         * @return Standard IO stream manager ptr
         */
        static std::unique_ptr<GS_StdIOStreamManager> Create();

    public:

        /*
         *
         * GS_StdIOStreamManager PUBLIC METHODS
         *
         */

        /**
         * Getting standard input stream
         * @return Standard input stream
         */
        LRef<InputStream> In();

        /**
         * Getting standard output stream
         * @return Standard output stream
         */
        LRef<OutputStream> Out();

        /**
         * Getting standard error stream
         * @return Standard error stream
         */
        LRef<OutputStream> Err();

        /**
         * Getting standard logger stream
         * @return Standard logger stream
         */
        LRef<OutputStream> Log();

    private:

        /*
         *
         * GS_StdIOStreamManager PRIVATE FIELDS
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
         * Standard logger stream
         */
        LRef<OutputStream> _standardLog;
    };

    /**
     * Standard IO stream manager ptr type
     */
    using GSStdIOStreamManagerPtr = std::unique_ptr<GS_StdIOStreamManager>;

}

#endif //GSLANGUAGE_GS_STREAM_H
