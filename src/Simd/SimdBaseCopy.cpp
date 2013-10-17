/*
* Simd Library.
*
* Copyright (c) 2011-2013 Yermalayeu Ihar.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy 
* of this software and associated documentation files (the "Software"), to deal
* in the Software without restriction, including without limitation the rights
* to use, copy, modify, merge, publish, distribute, sublicense, and/or sell 
* copies of the Software, and to permit persons to whom the Software is 
* furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in 
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR 
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, 
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE 
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER 
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
* SOFTWARE.
*/
#include "Simd/SimdBase.h"

namespace Simd
{
    namespace Base
    {
        void Copy(const uchar * src, size_t srcStride, size_t width, size_t height, size_t pixelSize, uchar * dst, size_t dstStride)
        {
            size_t rowSize = width*pixelSize;
            for(size_t row = 0; row < height; ++row)
            {
                memcpy(dst, src, rowSize);
                src += srcStride;
                dst += dstStride;
            }
        }

        void CopyFrame(const uchar * src, size_t srcStride, size_t width, size_t height, size_t pixelSize, 
            size_t frameLeft, size_t frameTop, size_t frameRight, size_t frameBottom, uchar * dst, size_t dstStride)
        {
            if(frameTop)
            {
                size_t srcOffset = 0;
                size_t dstOffset = 0;
                size_t size = width*pixelSize;
                for(size_t row = 0; row < frameTop; ++row)
                {
                    memcpy(dst + dstOffset, src + srcOffset, size);
                    srcOffset += srcStride;
                    dstOffset += dstStride;
                }
            }
            if(height - frameBottom)
            {
                size_t srcOffset = frameBottom*srcStride;
                size_t dstOffset = frameBottom*dstStride;
                size_t size = width*pixelSize;
                for(size_t row = frameBottom; row < height; ++row)
                {
                    memcpy(dst + dstOffset, src + srcOffset, size);
                    srcOffset += srcStride;
                    dstOffset += dstStride;
                }
            }
            if(frameLeft)
            {
                size_t srcOffset = frameTop*srcStride;
                size_t dstOffset = frameTop*dstStride;
                size_t size = frameLeft*pixelSize;
                for(size_t row = frameTop; row < frameBottom; ++row)
                {
                    memcpy(dst + dstOffset, src + srcOffset, size);
                    srcOffset += srcStride;
                    dstOffset += dstStride;
                }
            }
            if(width - frameRight)
            {
                size_t srcOffset = frameTop*srcStride + frameRight*pixelSize;
                size_t dstOffset = frameTop*dstStride + frameRight*pixelSize;
                size_t size = (width - frameRight)*pixelSize;
                for(size_t row = frameTop; row < frameBottom; ++row)
                {
                    memcpy(dst + dstOffset, src + srcOffset, size);
                    srcOffset += srcStride;
                    dstOffset += dstStride;
                }
            }
        }
    }
}