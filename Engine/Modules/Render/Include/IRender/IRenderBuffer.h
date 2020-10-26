/**
 * Created by rayfalling on 2020/10/26.
 * */

#pragma once

#ifndef VISREAL_I_RENDER_BUFFER_H
#define VISREAL_I_RENDER_BUFFER_H

#include "Container/FString.h"
#include "Container/TArray.h"

namespace Engine::Render::Interface {
    /**
     * An Interface class for render buffers.
     * generate device related buffer and return
     *
     * */
    class IRenderBuffer {
    public:
        /**
         * create an vertex buffer from TArray
         *
         * @return uint id
         * */
        virtual uint32 CreateVertexBuffer(FString name, TArray vertexes) = 0;

        /**
         * create an indices buffer from TArray
         *
         * @return uint id
         * */
        virtual uint32 CreateIndicesBuffer(FString name, TArray indices) = 0;

    };
}

#endif //VISREAL_I_RENDER_BUFFER_H
