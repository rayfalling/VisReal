/**
 * Created by rayfalling on 2020/10/12.
 * */

#ifndef VISREAL_MARCOS_H
#define VISREAL_MARCOS_H

namespace Engine::Core {
    /**
     * Mark Method/Struct/Class deprecated with default tips(compiler)
     * */
    #define DEPRECATED [[deprecated]]
    /**
     * Mark Method/Struct/Class deprecated with custom tips
     * */
    #define DEPRECATED_WITH_TIPS(x) [[deprecated(x)]]
    /**
     * Unsupported OpenGL version (less than 3.3) Text Tips
     * */
    #define GLVersionNotSupport "This version is to old, pls use version >= 3.3"

    #define ENGINE_START_TIPS "VisReal Engine Start."
}

#endif //VISREAL_MARCOS_H
