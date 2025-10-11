#ifndef __UTILS_H_
#define __UTILS_H_

template<class T>
T* resizeAndCopyBuffer(T* current, unsigned long oldSize, unsigned long newSize) {
    if (current == nullptr) {
        oldSize = 0;
    }

    T* newBuffer = (T*)malloc(newSize * sizeof(T));
    if (newBuffer == nullptr)
        abort();

    memset((void*)newBuffer, 0, newSize * sizeof(T));

    if (oldSize > 0) {
        memcpy((void*)newBuffer, (void*)current, oldSize * sizeof(T));
    }

    return newBuffer;
}

#endif