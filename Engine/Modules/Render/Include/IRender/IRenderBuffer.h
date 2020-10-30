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
         * Init an Vertex Array Buffer for VBO use.
         *
         * @return uint id
         * */
        virtual uint32 InitVertexArray(FString name) = 0;

        /**
         * create an vertex buffer from TArray.(VBO)
         *
         * @return uint id
         * */
        virtual uint32 CreateVertexBuffer(FString name, TArray<float> vertexes) = 0;

        /**
         * create an indices buffer from TArray.(EIO)
         *
         * @return uint id
         * */
        virtual uint32 CreateIndicesBuffer(FString name, TArray<float> indices) = 0;
    };
}

#endif //VISREAL_I_RENDER_BUFFER_H
