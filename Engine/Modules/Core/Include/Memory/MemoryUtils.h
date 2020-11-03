/**
 * Created by rayfalling on 2020/10/20.
 *
 * partly from Unreal Engine, not use
 * Unreal Engine's accelerate for compile optimize
 * */

#pragma once
#pragma warning(disable:4068)
#pragma clang diagnostic push
#pragma ide diagnostic ignored "err_redefinition"

#ifndef VISREAL_MEMORY_UTILS_H
#define VISREAL_MEMORY_UTILS_H

#include <cstring>
#include "Marco/MSVCPlatform.h"
#include "Templates/TAndOrNot.h"
#include "Templates/TTypeTraits.h"
#include "Templates/TAreTypesEqual.h"
#include "Templates/TIsTriviallyDestructible.h"
#include "Templates/TIsTriviallyCopyAssignable.h"

namespace Engine::Core {
	namespace TCanBitwiseRelocatePrivate {
		template <typename DestinationElementType, typename SourceElementType>
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
	 * @param	address	The address of the first memory location to construct at.
	 * @param	count		The number of elements to destruct.
	 */
	template <typename ElementType, typename SizeType>
	void DefaultConstructItems(void* address, SizeType count) {
		if constexpr (TIsZeroConstructType<ElementType>::Value) {
			std::memset(address, 0, sizeof(ElementType) * count);
		}
		else {
			auto* element = static_cast<ElementType*>(address);
			while (count) {
				new(element) ElementType;
				++element;
				--count;
			}
		}
	}

	#else

    /**
     * Default constructs a range of items in memory.
     *
     * @param	address		The address of the first memory location to construct at.
     * @param	count		The number of elements to destruct.
     */
    template<typename ElementType, typename SizeType>
    typename TEnableIf<!TIsZeroConstructType<ElementType>::Value>::Type
    DefaultConstructItems(void *address, SizeType count) {
        ElementType * element = (ElementType *) address;
        while (count) {
            new(element) ElementType;
            ++element;
            --count;
        }
    }


    template<typename ElementType, typename SizeType>
    typename TEnableIf<TIsZeroConstructType<ElementType>::Value>::Type
    DefaultConstructItems(void * address, SizeType count) {
        std::memset(address, 0, sizeof(ElementType) * count);
    }

	#endif

	#if PLATFORM_COMPILER_HAS_IF_CONSTEXPR

	/**
	 * destructs a single item in memory.
	 *
	 * @param	element		A pointer to the item to destruct.
	 *
	 * @note: This function is optimized for values of T, and so will not dynamically dispatch destructor calls if T's destructor is virtual.
	 */
	template <typename ElementType>
	void DestructItem(ElementType* element) {
		if constexpr (!TIsTriviallyDestructible<ElementType>::Value) {
			// We need a typedef here because VC won't compile the destructor call below if ElementType itself has a member called ElementType
			typedef ElementType DestructItemsElementTypeTypedef;

			element->DestructItemsElementTypeTypedef::~DestructItemsElementTypeTypedef();
		}
	}

	#else

    /**
     * destructs a single item in memory.
     *
     * @param	element		A pointer to the item to destruct.
     *
     * @note: This function is optimized for values of T, and so will not dynamically dispatch destructor calls if T's destructor is virtual.
     */
    template<typename ElementType>
    typename TEnableIf<!TIsTriviallyDestructible<ElementType>::Value>::Type DestructItem(ElementType * element) {
        // We need a typedef here because VC won't compile the destructor call below if ElementType itself has a member called ElementType
        typedef ElementType DestructItemsElementTypeTypedef;
		element->DestructItemsElementTypeTypedef::~DestructItemsElementTypeTypedef();
    }


    template<typename ElementType>
    typename TEnableIf<TIsTriviallyDestructible<ElementType>::Value>::Type DestructItem(ElementType *Element) {
    }

	#endif

	#if PLATFORM_COMPILER_HAS_IF_CONSTEXPR

	/**
	 * destructs a range of items in memory.
	 *
	 * @param	element		A pointer to the first item to destruct.
	 * @param	count		The number of elements to destruct.
	 *
	 * @note: This function is optimized for values of T, and so will not dynamically dispatch destructor calls if T's destructor is virtual.
	 */
	template <typename ElementType, typename SizeType>
	void DestructItems(ElementType* element, SizeType count) {
		if constexpr (!TIsTriviallyDestructible<ElementType>::Value) {
			while (count) {
				// We need a typedef here because VC won't compile the destructor call below if ElementType itself has a member called ElementType
				typedef ElementType DestructItemsElementTypeTypedef;

				element->DestructItemsElementTypeTypedef::~DestructItemsElementTypeTypedef();
				++element;
				--count;
			}
		}
	}

	#else

    /**
     * destructs a range of items in memory.
     *
     * @param	Elements	A pointer to the first item to destruct.
     * @param	count		The number of elements to destruct.
     *
     * @note: This function is optimized for values of T, and so will not dynamically dispatch destructor calls if T's destructor is virtual.
     */
    template<typename ElementType, typename SizeType>
    typename TEnableIf<!TIsTriviallyDestructible<ElementType>::Value>::Type
    DestructItems(ElementType *Element, SizeType count) {
        while (count) {
            // We need a typedef here because VC won't compile the destructor call below if ElementType itself has a member called ElementType
            typedef ElementType DestructItemsElementTypeTypedef;
            Element->DestructItemsElementTypeTypedef::~DestructItemsElementTypeTypedef();
            ++Element;
            --count;
        }
    }


    template<typename ElementType, typename SizeType>
    typename TEnableIf<TIsTriviallyDestructible<ElementType>::Value>::Type
    DestructItems(ElementType *Elements, SizeType count) {
    }

	#endif

	#if PLATFORM_COMPILER_HAS_IF_CONSTEXPR

	/**
	 * Constructs a range of items into memory from a set of arguments.  The arguments come from an another array.
	 *
	 * @param	dest		The memory location to start copying into.
	 * @param	source		A pointer to the first argument to pass to the constructor.
	 * @param	count		The number of elements to copy.
	 */
	template <typename DestinationElementType, typename SourceElementType, typename SizeType>
	void ConstructItems(void* dest, const SourceElementType* source, SizeType count) {
		if constexpr (TIsBitwiseConstructible<DestinationElementType, SourceElementType>::Value) {
			std::memcpy(dest, source, sizeof(SourceElementType) * count);
		}
		else {
			while (count) {
				new(dest) DestinationElementType(*source);
				++static_cast<DestinationElementType*&>(dest);
				++source;
				--count;
			}
		}
	}

	#else

    /**
     * Constructs a range of items into memory from a set of arguments.  The arguments come from an another array.
     *
     * @param	dest		The memory location to start copying into.
     * @param	source		A pointer to the first argument to pass to the constructor.
     * @param	count		The number of elements to copy.
     */
    template<typename DestinationElementType, typename SourceElementType, typename SizeType>
    typename TEnableIf<!TIsBitwiseConstructible<DestinationElementType, SourceElementType>::Value>::Type
    ConstructItems(void *dest, const SourceElementType *source, SizeType count) {
        while (count) {
            new(dest) DestinationElementType(*source);
            ++((DestinationElementType *&) dest);
            ++source;
            --count;
        }
    }


    template<typename DestinationElementType, typename SourceElementType, typename SizeType>
    typename TEnableIf<TIsBitwiseConstructible<DestinationElementType, SourceElementType>::Value>::Type
    ConstructItems(void *dest, const SourceElementType *source, SizeType count) {
        std::memcpy(dest, source, sizeof(SourceElementType) * count);
    }

	#endif

	#if PLATFORM_COMPILER_HAS_IF_CONSTEXPR

	/**
	 * Copy assigns a range of items.
	 *
	 * @param	dest		The memory location to start assigning to.
	 * @param	source		A pointer to the first item to assign.
	 * @param	count		The number of elements to assign.
	 */
	template <typename ElementType, typename SizeType>
	void CopyAssignItems(ElementType* dest, const ElementType* source, SizeType count) {
		if constexpr (TIsTriviallyCopyAssignable<ElementType>::Value) {
			std::memcpy(dest, source, sizeof(ElementType) * count);
		}
		else {
			while (count) {
				*dest = *source;
				++dest;
				++source;
				--count;
			}
		}
	}

	#else

    /**
     * Copy assigns a range of items.
     *
     * @param	dest		The memory location to start assigning to.
     * @param	source		A pointer to the first item to assign.
     * @param	count		The number of elements to assign.
     */
    template<typename ElementType, typename SizeType>
    typename TEnableIf<!TIsTriviallyCopyAssignable<ElementType>::Value>::Type
    CopyAssignItems(ElementType *dest, const ElementType *source, SizeType count) {
        while (count) {
            *dest = *source;
            ++dest;
            ++source;
            --count;
        }
    }


    template<typename ElementType, typename SizeType>
    typename TEnableIf<TIsTriviallyCopyAssignable<ElementType>::Value>::Type
    CopyAssignItems(ElementType *dest, const ElementType *source, SizeType count) {
        std::memcpy(dest, source, sizeof(ElementType) * count);
    }

	#endif

	#if PLATFORM_COMPILER_HAS_IF_CONSTEXPR

	/**
	 * Relocates a range of items to a new memory location as a new type. This is a so-called 'destructive move' for which
	 * there is no single operation in C++ but which can be implemented very efficiently in general.
	 *
	 * @param	dest		The memory location to relocate to.
	 * @param	source		A pointer to the first item to relocate.
	 * @param	count		The number of elements to relocate.
	 */
	template <typename DestinationElementType, typename SourceElementType, typename SizeType>
	void RelocateConstructItems(void* dest, const SourceElementType* source, SizeType count) {
		if constexpr (TCanBitwiseRelocatePrivate::TCanBitwiseRelocate<DestinationElementType, SourceElementType>::Value) {
			/* All existing UE containers seem to assume trivial relocatability (i.e. memcpy'able) of their members,
			 * so we're going to assume that this is safe here.  However, it's not generally possible to assume this
			 * in general as objects which contain pointers/references to themselves are not safe to be trivially
			 * relocated.
			 *
			 * However, it is not yet possible to automatically infer this at compile time, so we can't enable
			 * different (i.e. safer) implementations anyway. */

			std::memmove(dest, source, sizeof(SourceElementType) * count);
		}
		else {
			while (count) {
				// We need a typedef here because VC won't compile the destructor call below if SourceElementType itself has a member called SourceElementType
				typedef SourceElementType RelocateConstructItemsElementTypeTypedef;
				new(dest) DestinationElementType(*source);
				++static_cast<DestinationElementType*&>(dest);
				(source++)->RelocateConstructItemsElementTypeTypedef::~RelocateConstructItemsElementTypeTypedef();
				--count;
			}
		}
	}

	#else

    /**
     * Relocates a range of items to a new memory location as a new type. This is a so-called 'destructive move' for which
     * there is no single operation in C++ but which can be implemented very efficiently in general.
     *
     * @param	dest		The memory location to relocate to.
     * @param	source		A pointer to the first item to relocate.
     * @param	count		The number of elements to relocate.
     */
    template<typename DestinationElementType, typename SourceElementType, typename SizeType>
    typename TEnableIf<!TCanBitwiseRelocatePrivate::TCanBitwiseRelocate<DestinationElementType, SourceElementType>::Value>::Type
    RelocateConstructItems(void *dest, const SourceElementType *source, SizeType count) {
        while (count) {
            // We need a typedef here because VC won't compile the destructor call below if SourceElementType itself has a member called SourceElementType
            typedef SourceElementType RelocateConstructItemsElementTypeTypedef;

            new(dest) DestinationElementType(*source);
            ++((DestinationElementType *&) dest);
            (source++)->RelocateConstructItemsElementTypeTypedef::~RelocateConstructItemsElementTypeTypedef();
            --count;
        }
    }

    template<typename DestinationElementType, typename SourceElementType, typename SizeType>
    typename TEnableIf<TCanBitwiseRelocatePrivate::TCanBitwiseRelocate<DestinationElementType, SourceElementType>::Value>::Type
    RelocateConstructItems(void *dest, const SourceElementType *source, SizeType count) {
        /* All existing UE containers seem to assume trivial relocatability (i.e. memcpy'able) of their members,
         * so we're going to assume that this is safe here.  However, it's not generally possible to assume this
         * in general as objects which contain pointers/references to themselves are not safe to be trivially
         * relocated.
         *
         * However, it is not yet possible to automatically infer this at compile time, so we can't enable
         * different (i.e. safer) implementations anyway. */

        std::memmove(dest, source, sizeof(SourceElementType) * count);
    }

	#endif

	#if PLATFORM_COMPILER_HAS_IF_CONSTEXPR

	/**
	 * Move constructs a range of items into memory.
	 *
	 * @param	dest		The memory location to start moving into.
	 * @param	source		A pointer to the first item to move from.
	 * @param	count		The number of elements to move.
	 */
	template <typename ElementType, typename SizeType>
	void MoveConstructItems(void* dest, const ElementType* source, SizeType count) {
		if constexpr (TIsTriviallyCopyConstructible<ElementType>::Value) {
			std::memmove(dest, source, sizeof(ElementType) * count);
		}
		else {
			while (count) {
				new(dest) ElementType(static_cast<ElementType&&>(*source));
				++static_cast<ElementType*&>(dest);
				++source;
				--count;
			}
		}
	}

	#else

    /**
     * Move constructs a range of items into memory.
     *
     * @param	dest		The memory location to start moving into.
     * @param	source		A pointer to the first item to move from.
     * @param	count		The number of elements to move.
     */
    template<typename ElementType, typename SizeType>
    typename TEnableIf<!TIsTriviallyCopyConstructible<ElementType>::Value>::Type
    MoveConstructItems(void *dest, const ElementType *source, SizeType count) {
        while (count) {
            new(dest) ElementType((ElementType &&) *source);
            ++((ElementType *&) dest);
            ++source;
            --count;
        }
    }

    template<typename ElementType, typename SizeType>
    typename TEnableIf<TIsTriviallyCopyConstructible<ElementType>::Value>::Type
    MoveConstructItems(void *dest, const ElementType *source, SizeType count) {
        std::memmove(dest, source, sizeof(ElementType) * count);
    }

	#endif

	#if PLATFORM_COMPILER_HAS_IF_CONSTEXPR

	/**
	 * Move assigns a range of items.
	 *
	 * @param	dest		The memory location to start move assigning to.
	 * @param	source		A pointer to the first item to move assign.
	 * @param	count		The number of elements to move assign.
	 */
	template <typename ElementType, typename SizeType>
	void MoveAssignItems(ElementType* dest, const ElementType* source, SizeType count) {
		if constexpr (TIsTriviallyCopyAssignable<ElementType>::Value) {
			std::memmove(dest, source, sizeof(ElementType) * count);
		}
		else {
			while (count) {
				*dest = static_cast<ElementType&&>(*source);
				++dest;
				++source;
				--count;
			}
		}
	}

	#else

    /**
     * Move assigns a range of items.
     *
     * @param	dest		The memory location to start move assigning to.
     * @param	source		A pointer to the first item to move assign.
     * @param	count		The number of elements to move assign.
     */
    template<typename ElementType, typename SizeType>
    typename TEnableIf<!TIsTriviallyCopyAssignable<ElementType>::Value>::Type
    MoveAssignItems(ElementType *dest, const ElementType *source, SizeType count) {
        while (count) {
            *dest = (ElementType &&) *source;
            ++dest;
            ++source;
            --count;
        }
    }

    template<typename ElementType, typename SizeType>
    typename TEnableIf<TIsTriviallyCopyAssignable<ElementType>::Value>::Type
    MoveAssignItems(ElementType *dest, const ElementType *source, SizeType count) {
        std::memmove(dest, source, sizeof(ElementType) * count);
    }

	#endif

	#if PLATFORM_COMPILER_HAS_IF_CONSTEXPR

	template <typename ElementType, typename SizeType>
	bool CompareItems(const ElementType* A, const ElementType* B, SizeType count) {
		if constexpr (TTypeTraits<ElementType>::IsBytewiseComparable) {
			return !std::memcmp(A, B, sizeof(ElementType) * count);
		}
		else {
			while (count) {
				if (!(*A == *B)) {
					return false;
				}

				++A;
				++B;
				--count;
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
    CompareItems(const ElementType *A, const ElementType *B, SizeType count) {
        return !std::memcmp(A, B, sizeof(ElementType) * count);
    }
#pragma clang diagnostic pop
#pragma clang diagnostic pop

    template<typename ElementType, typename SizeType>
    typename TEnableIf<!TTypeTraits<ElementType>::IsBytewiseComparable, bool>::Type
    CompareItems(const ElementType *A, const ElementType *B, SizeType count) {
        while (count) {
            if (!(*A == *B)) {
                return false;
            }
            ++A;
            ++B;
            --count;
        }
        return true;
    }

	#endif
}

#endif //VISREAL_MEMORY_UTILS_H

#pragma clang diagnostic pop
