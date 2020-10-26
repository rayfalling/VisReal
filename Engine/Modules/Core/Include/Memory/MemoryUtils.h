/**
 * Created by rayfalling on 2020/10/20.
 *
 * partly from Unreal Engine, not use
 * Unreal Engine's accelerate for compile optimize
 * */

#pragma warning(disable:4068)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "err_redefinition"
#pragma once

#ifndef VISREAL_MEMORY_UTILS_H
#define VISREAL_MEMORY_UTILS_H

#include <cstring>
#include "Platform/Types.h"
#include "Marco/MSVCPlatform.h"
#include "Templates/TEnableIf.h"
#include "Templates/TAndOrNot.h"
#include "Templates/TTypeTraits.h"
#include "Templates/TAreTypesEqual.h"
#include "Templates/TIsTriviallyDestructible.h"
#include "Templates/TIsTriviallyCopyAssignable.h"

namespace Engine::Core {
    namespace TCanBitwiseRelocatePrivate {
        template<typename DestinationElementType, typename SourceElementType>
        struct TCanBitwiseRelocate {
            enum {
                Value =
                TOr<
                        TAreTypesEqual<DestinationElementType, SourceElementType>,
                        TAnd<
                                TIsBitwiseConstructible<DestinationElementType, SourceElementType>,
                                TIsTriviallyDestructible<SourceElementType>
                        >
                >::Value
            };
        };
    }

#if PLATFORM_COMPILER_HAS_IF_CONSTEXPR

    /**
     * Default constructs a range of items in memory.
     *
     * @param	Elements	The address of the first memory location to construct at.
     * @param	Count		The number of elements to destruct.
     */
    template <typename ElementType, typename SizeType>
    void DefaultConstructItems(void* Address, SizeType Count) {
        if constexpr (TIsZeroConstructType<ElementType>::Value) {
            std::memset(Address, 0, sizeof(ElementType) * Count);
        }
        else {
            auto* Element = static_cast<ElementType*>(Address);
            while (Count) {
                new(Element) ElementType;
                ++Element;
                --Count;
            }
        }
    }

#else

    /**
     * Default constructs a range of items in memory.
     *
     * @param	Elements	The address of the first memory location to construct at.
     * @param	Count		The number of elements to destruct.
     */
    template<typename ElementType, typename SizeType>
    typename TEnableIf<!TIsZeroConstructType<ElementType>::Value>::Type
    DefaultConstructItems(void *Address, SizeType Count) {
        ElementType *Element = (ElementType *) Address;
        while (Count) {
            new(Element) ElementType;
            ++Element;
            --Count;
        }
    }


    template<typename ElementType, typename SizeType>
    typename TEnableIf<TIsZeroConstructType<ElementType>::Value>::Type
    DefaultConstructItems(void *Elements, SizeType Count) {
        std::memset(Elements, 0, sizeof(ElementType) * Count);
    }

#endif

#if PLATFORM_COMPILER_HAS_IF_CONSTEXPR

    /**
     * Destructs a single item in memory.
     *
     * @param	Elements	A pointer to the item to destruct.
     *
     * @note: This function is optimized for values of T, and so will not dynamically dispatch destructor calls if T's destructor is virtual.
     */
    template <typename ElementType>
    void DestructItem(ElementType* Element) {
        if constexpr (!TIsTriviallyDestructible<ElementType>::Value) {
            // We need a typedef here because VC won't compile the destructor call below if ElementType itself has a member called ElementType
            typedef ElementType DestructItemsElementTypeTypedef;

            Element->DestructItemsElementTypeTypedef::~DestructItemsElementTypeTypedef();
        }
    }

#else

    /**
     * Destructs a single item in memory.
     *
     * @param	Elements	A pointer to the item to destruct.
     *
     * @note: This function is optimized for values of T, and so will not dynamically dispatch destructor calls if T's destructor is virtual.
     */
    template<typename ElementType>
    typename TEnableIf<!TIsTriviallyDestructible<ElementType>::Value>::Type DestructItem(ElementType *Element) {
        // We need a typedef here because VC won't compile the destructor call below if ElementType itself has a member called ElementType
        typedef ElementType DestructItemsElementTypeTypedef;
        Element->DestructItemsElementTypeTypedef::~DestructItemsElementTypeTypedef();
    }


    template<typename ElementType>
    typename TEnableIf<TIsTriviallyDestructible<ElementType>::Value>::Type DestructItem(ElementType *Element) {
    }

#endif

#if PLATFORM_COMPILER_HAS_IF_CONSTEXPR

    /**
     * Destructs a range of items in memory.
     *
     * @param	Elements	A pointer to the first item to destruct.
     * @param	Count		The number of elements to destruct.
     *
     * @note: This function is optimized for values of T, and so will not dynamically dispatch destructor calls if T's destructor is virtual.
     */
    template <typename ElementType, typename SizeType>
    void DestructItems(ElementType* Element, SizeType Count) {
        if constexpr (!TIsTriviallyDestructible<ElementType>::Value) {
            while (Count) {
                // We need a typedef here because VC won't compile the destructor call below if ElementType itself has a member called ElementType
                typedef ElementType DestructItemsElementTypeTypedef;

                Element->DestructItemsElementTypeTypedef::~DestructItemsElementTypeTypedef();
                ++Element;
                --Count;
            }
        }
    }

#else

    /**
     * Destructs a range of items in memory.
     *
     * @param	Elements	A pointer to the first item to destruct.
     * @param	Count		The number of elements to destruct.
     *
     * @note: This function is optimized for values of T, and so will not dynamically dispatch destructor calls if T's destructor is virtual.
     */
    template<typename ElementType, typename SizeType>
    typename TEnableIf<!TIsTriviallyDestructible<ElementType>::Value>::Type
    DestructItems(ElementType *Element, SizeType Count) {
        while (Count) {
            // We need a typedef here because VC won't compile the destructor call below if ElementType itself has a member called ElementType
            typedef ElementType DestructItemsElementTypeTypedef;
            Element->DestructItemsElementTypeTypedef::~DestructItemsElementTypeTypedef();
            ++Element;
            --Count;
        }
    }


    template<typename ElementType, typename SizeType>
    typename TEnableIf<TIsTriviallyDestructible<ElementType>::Value>::Type
    DestructItems(ElementType *Elements, SizeType Count) {
    }

#endif

#if PLATFORM_COMPILER_HAS_IF_CONSTEXPR

    /**
     * Constructs a range of items into memory from a set of arguments.  The arguments come from an another array.
     *
     * @param	Dest		The memory location to start copying into.
     * @param	Source		A pointer to the first argument to pass to the constructor.
     * @param	Count		The number of elements to copy.
     */
    template <typename DestinationElementType, typename SourceElementType, typename SizeType>
    void ConstructItems(void* Dest, const SourceElementType* Source, SizeType Count) {
        if constexpr (TIsBitwiseConstructible<DestinationElementType, SourceElementType>::Value) {
            std::memcpy(Dest, Source, sizeof(SourceElementType) * Count);
        }
        else {
            while (Count) {
                new(Dest) DestinationElementType(*Source);
                ++static_cast<DestinationElementType*&>(Dest);
                ++Source;
                --Count;
            }
        }
    }

#else

    /**
     * Constructs a range of items into memory from a set of arguments.  The arguments come from an another array.
     *
     * @param	Dest		The memory location to start copying into.
     * @param	Source		A pointer to the first argument to pass to the constructor.
     * @param	Count		The number of elements to copy.
     */
    template<typename DestinationElementType, typename SourceElementType, typename SizeType>
    typename TEnableIf<!TIsBitwiseConstructible<DestinationElementType, SourceElementType>::Value>::Type
    ConstructItems(void *Dest, const SourceElementType *Source, SizeType Count) {
        while (Count) {
            new(Dest) DestinationElementType(*Source);
            ++((DestinationElementType *&) Dest);
            ++Source;
            --Count;
        }
    }


    template<typename DestinationElementType, typename SourceElementType, typename SizeType>
    typename TEnableIf<TIsBitwiseConstructible<DestinationElementType, SourceElementType>::Value>::Type
    ConstructItems(void *Dest, const SourceElementType *Source, SizeType Count) {
        std::memcpy(Dest, Source, sizeof(SourceElementType) * Count);
    }

#endif

#if PLATFORM_COMPILER_HAS_IF_CONSTEXPR

    /**
     * Copy assigns a range of items.
     *
     * @param	Dest		The memory location to start assigning to.
     * @param	Source		A pointer to the first item to assign.
     * @param	Count		The number of elements to assign.
     */
    template <typename ElementType, typename SizeType>
    void CopyAssignItems(ElementType* Dest, const ElementType* Source, SizeType Count) {
        if constexpr (TIsTriviallyCopyAssignable<ElementType>::Value) {
            std::memcpy(Dest, Source, sizeof(ElementType) * Count);
        }
        else {
            while (Count) {
                *Dest = *Source;
                ++Dest;
                ++Source;
                --Count;
            }
        }
    }

#else

    /**
     * Copy assigns a range of items.
     *
     * @param	Dest		The memory location to start assigning to.
     * @param	Source		A pointer to the first item to assign.
     * @param	Count		The number of elements to assign.
     */
    template<typename ElementType, typename SizeType>
    typename TEnableIf<!TIsTriviallyCopyAssignable<ElementType>::Value>::Type
    CopyAssignItems(ElementType *Dest, const ElementType *Source, SizeType Count) {
        while (Count) {
            *Dest = *Source;
            ++Dest;
            ++Source;
            --Count;
        }
    }


    template<typename ElementType, typename SizeType>
    typename TEnableIf<TIsTriviallyCopyAssignable<ElementType>::Value>::Type
    CopyAssignItems(ElementType *Dest, const ElementType *Source, SizeType Count) {
        std::memcpy(Dest, Source, sizeof(ElementType) * Count);
    }

#endif

#if PLATFORM_COMPILER_HAS_IF_CONSTEXPR

    /**
     * Relocates a range of items to a new memory location as a new type. This is a so-called 'destructive move' for which
     * there is no single operation in C++ but which can be implemented very efficiently in general.
     *
     * @param	Dest		The memory location to relocate to.
     * @param	Source		A pointer to the first item to relocate.
     * @param	Count		The number of elements to relocate.
     */
    template <typename DestinationElementType, typename SourceElementType, typename SizeType>
    void RelocateConstructItems(void* Dest, const SourceElementType* Source, SizeType Count) {
        if constexpr (UE4MemoryOps_Private::TCanBitwiseRelocate<DestinationElementType, SourceElementType>::Value) {
            /* All existing UE containers seem to assume trivial relocatability (i.e. memcpy'able) of their members,
             * so we're going to assume that this is safe here.  However, it's not generally possible to assume this
             * in general as objects which contain pointers/references to themselves are not safe to be trivially
             * relocated.
             *
             * However, it is not yet possible to automatically infer this at compile time, so we can't enable
             * different (i.e. safer) implementations anyway. */

            std::memmove(Dest, Source, sizeof(SourceElementType) * Count);
        }
        else {
            while (Count) {
                // We need a typedef here because VC won't compile the destructor call below if SourceElementType itself has a member called SourceElementType
                typedef SourceElementType RelocateConstructItemsElementTypeTypedef;
                new(Dest) DestinationElementType(*Source);
                ++static_cast<DestinationElementType*&>(Dest);
                (Source++)->RelocateConstructItemsElementTypeTypedef::~RelocateConstructItemsElementTypeTypedef();
                --Count;
            }
        }
    }

#else

    /**
     * Relocates a range of items to a new memory location as a new type. This is a so-called 'destructive move' for which
     * there is no single operation in C++ but which can be implemented very efficiently in general.
     *
     * @param	Dest		The memory location to relocate to.
     * @param	Source		A pointer to the first item to relocate.
     * @param	Count		The number of elements to relocate.
     */
    template<typename DestinationElementType, typename SourceElementType, typename SizeType>
    typename TEnableIf<!TCanBitwiseRelocatePrivate::TCanBitwiseRelocate<DestinationElementType, SourceElementType>::Value>::Type
    RelocateConstructItems(void *Dest, const SourceElementType *Source, SizeType Count) {
        while (Count) {
            // We need a typedef here because VC won't compile the destructor call below if SourceElementType itself has a member called SourceElementType
            typedef SourceElementType RelocateConstructItemsElementTypeTypedef;

            new(Dest) DestinationElementType(*Source);
            ++((DestinationElementType *&) Dest);
            (Source++)->RelocateConstructItemsElementTypeTypedef::~RelocateConstructItemsElementTypeTypedef();
            --Count;
        }
    }

    template<typename DestinationElementType, typename SourceElementType, typename SizeType>
    typename TEnableIf<TCanBitwiseRelocatePrivate::TCanBitwiseRelocate<DestinationElementType, SourceElementType>::Value>::Type
    RelocateConstructItems(void *Dest, const SourceElementType *Source, SizeType Count) {
        /* All existing UE containers seem to assume trivial relocatability (i.e. memcpy'able) of their members,
         * so we're going to assume that this is safe here.  However, it's not generally possible to assume this
         * in general as objects which contain pointers/references to themselves are not safe to be trivially
         * relocated.
         *
         * However, it is not yet possible to automatically infer this at compile time, so we can't enable
         * different (i.e. safer) implementations anyway. */

        std::memmove(Dest, Source, sizeof(SourceElementType) * Count);
    }

#endif

#if PLATFORM_COMPILER_HAS_IF_CONSTEXPR

    /**
     * Move constructs a range of items into memory.
     *
     * @param	Dest		The memory location to start moving into.
     * @param	Source		A pointer to the first item to move from.
     * @param	Count		The number of elements to move.
     */
    template <typename ElementType, typename SizeType>
    void MoveConstructItems(void* Dest, const ElementType* Source, SizeType Count) {
        if constexpr (TIsTriviallyCopyConstructible<ElementType>::Value) {
            std::memmove(Dest, Source, sizeof(ElementType) * Count);
        }
        else {
            while (Count) {
                new(Dest) ElementType(static_cast<ElementType&&>(*Source));
                ++static_cast<ElementType*&>(Dest);
                ++Source;
                --Count;
            }
        }
    }

#else

    /**
     * Move constructs a range of items into memory.
     *
     * @param	Dest		The memory location to start moving into.
     * @param	Source		A pointer to the first item to move from.
     * @param	Count		The number of elements to move.
     */
    template<typename ElementType, typename SizeType>
    typename TEnableIf<!TIsTriviallyCopyConstructible<ElementType>::Value>::Type
    MoveConstructItems(void *Dest, const ElementType *Source, SizeType Count) {
        while (Count) {
            new(Dest) ElementType((ElementType &&) *Source);
            ++((ElementType *&) Dest);
            ++Source;
            --Count;
        }
    }

    template<typename ElementType, typename SizeType>
    typename TEnableIf<TIsTriviallyCopyConstructible<ElementType>::Value>::Type
    MoveConstructItems(void *Dest, const ElementType *Source, SizeType Count) {
        std::memmove(Dest, Source, sizeof(ElementType) * Count);
    }

#endif

#if PLATFORM_COMPILER_HAS_IF_CONSTEXPR

    /**
     * Move assigns a range of items.
     *
     * @param	Dest		The memory location to start move assigning to.
     * @param	Source		A pointer to the first item to move assign.
     * @param	Count		The number of elements to move assign.
     */
    template <typename ElementType, typename SizeType>
    void MoveAssignItems(ElementType* Dest, const ElementType* Source, SizeType Count) {
        if constexpr (TIsTriviallyCopyAssignable<ElementType>::Value) {
            std::memmove(Dest, Source, sizeof(ElementType) * Count);
        }
        else {
            while (Count) {
                *Dest = static_cast<ElementType&&>(*Source);
                ++Dest;
                ++Source;
                --Count;
            }
        }
    }

#else

    /**
     * Move assigns a range of items.
     *
     * @param	Dest		The memory location to start move assigning to.
     * @param	Source		A pointer to the first item to move assign.
     * @param	Count		The number of elements to move assign.
     */
    template<typename ElementType, typename SizeType>
    typename TEnableIf<!TIsTriviallyCopyAssignable<ElementType>::Value>::Type
    MoveAssignItems(ElementType *Dest, const ElementType *Source, SizeType Count) {
        while (Count) {
            *Dest = (ElementType &&) *Source;
            ++Dest;
            ++Source;
            --Count;
        }
    }

    template<typename ElementType, typename SizeType>
    typename TEnableIf<TIsTriviallyCopyAssignable<ElementType>::Value>::Type
    MoveAssignItems(ElementType *Dest, const ElementType *Source, SizeType Count) {
        std::memmove(Dest, Source, sizeof(ElementType) * Count);
    }

#endif

#if PLATFORM_COMPILER_HAS_IF_CONSTEXPR

    template <typename ElementType, typename SizeType>
    bool CompareItems(const ElementType* A, const ElementType* B, SizeType Count) {
        if constexpr (TTypeTraits<ElementType>::IsBytewiseComparable) {
            return !std::memcmp(A, B, sizeof(ElementType) * Count);
        }
        else {
            while (Count) {
                if (!(*A == *B)) {
                    return false;
                }

                ++A;
                ++B;
                --Count;
            }

            return true;
        }
    }

#else

#pragma clang diagnostic push
#pragma ide diagnostic ignored "CannotResolve"
#pragma clang diagnostic push
#pragma ide diagnostic ignored "IncompatibleTypes"
    template<typename ElementType, typename SizeType>
    typename TEnableIf<TTypeTraits<ElementType>::IsBytewiseComparable, bool>::Type
    CompareItems(const ElementType *A, const ElementType *B, SizeType Count) {
        return !std::memcmp(A, B, sizeof(ElementType) * Count);
    }
#pragma clang diagnostic pop
#pragma clang diagnostic pop

    template<typename ElementType, typename SizeType>
    typename TEnableIf<!TTypeTraits<ElementType>::IsBytewiseComparable, bool>::Type
    CompareItems(const ElementType *A, const ElementType *B, SizeType Count) {
        while (Count) {
            if (!(*A == *B)) {
                return false;
            }
            ++A;
            ++B;
            --Count;
        }
        return true;
    }

#endif
}

#endif //VISREAL_MEMORY_UTILS_H

#pragma clang diagnostic pop