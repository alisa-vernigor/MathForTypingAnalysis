#ifndef TYPELIST_H
#define TYPELIST_H

#include "NullType.h"

namespace NSLibrary {
//--------------------------------------------------------------------------------
// TypeSeq
//--------------------------------------------------------------------------------

template<class... TTypes>
struct TypeSeq {};

//--------------------------------------------------------------------------------
// TypeList
//--------------------------------------------------------------------------------
// Empty TypeList is always NullType
// Non empty TypeList always has a non NullType Head
//--------------------------------------------------------------------------------

template<class THead, class TTail>
struct TypeList {
  using Head = THead;
  using Tail = TTail;
};

using EmptyTypeList = NullType;
//--------------------------------------------------------------------------------

namespace TL {
//--------------------------------------------------------------------------------
// MakeTypeList
//--------------------------------------------------------------------------------

template<class... TTypes>
struct MakeTypeListImpl;

template<class... TTypes>
using MakeTypeList = typename MakeTypeListImpl<TTypes...>::Result;

template<class TType, class... TTypes>
struct MakeTypeListImpl<TType, TTypes...> {
  using Result = TypeList<TType, MakeTypeList<TTypes...>>;
};

template<class TType>
struct MakeTypeListImpl<TType> {
  using Result = TypeList<TType, NullType>;
};

template<>
struct MakeTypeListImpl<> {
  using Result = EmptyTypeList;
};
//--------------------------------------------------------------------------------
// MakeTypeListN
//--------------------------------------------------------------------------------
// Make a TypeList populated with TSize copies of the same type TType
//--------------------------------------------------------------------------------

template<class TType, unsigned int TSize>
struct MakeTypeListNImpl;

template<class TType, unsigned int TSize>
using MakeTypeListN = typename MakeTypeListNImpl<TType, TSize>::Result;

template<class TType, unsigned int TSize>
struct MakeTypeListNImpl {
  using Result = TypeList<TType, MakeTypeListN<TType, TSize - 1>>;
};

template<class TType>
struct MakeTypeListNImpl<TType, 0> {
  using Result = EmptyTypeList;
};
//--------------------------------------------------------------------------------
// Seq2List
//--------------------------------------------------------------------------------

template<class TTypeSeq>
struct Seq2ListImpl;

template<class TTypeSeq>
using Seq2List = typename Seq2ListImpl<TTypeSeq>::Result;

template<class... TTypes>
struct Seq2ListImpl<TypeSeq<TTypes...>> {
  using Result = MakeTypeList<TTypes...>;
};
//--------------------------------------------------------------------------------
// MergeSeq
//--------------------------------------------------------------------------------

template<class TSeq1, class TSeq2>
struct MergeSeqImpl;

template<class TSeq1, class TSeq2>
using MergeSeq = typename MergeSeqImpl<TSeq1, TSeq2>::Result;

template<class... TTypes1, class... TTypes2>
struct MergeSeqImpl<TypeSeq<TTypes1...>, TypeSeq<TTypes2...>> {
  using Result = TypeSeq<TTypes1..., TTypes2...>;
};
//--------------------------------------------------------------------------------
// List2Seq
//--------------------------------------------------------------------------------

template<class TList>
struct List2SeqImpl;

template<class TList>
using List2Seq = typename List2SeqImpl<TList>::Result;

template<>
struct List2SeqImpl<NullType> {
  using Result = TypeSeq<>;
};

template<class THead, class TTail>
struct List2SeqImpl<TypeList<THead, TTail>> {
  using Result = MergeSeq<TypeSeq<THead>, List2Seq<TTail>>;
};
//--------------------------------------------------------------------------------
// MakeTypeSeqN
//--------------------------------------------------------------------------------
// Make a TypeSeq populated with TSize copies of the same type TType
//--------------------------------------------------------------------------------

template<class TType, unsigned int TSize>
struct MakeTypeSeqNImpl {
  using Result = List2Seq<MakeTypeListN<TType, TSize>>;
};

template<class TType, unsigned int TSize>
using MakeTypeSeqN = typename MakeTypeSeqNImpl<TType, TSize>::Result;
//--------------------------------------------------------------------------------
// Length
//--------------------------------------------------------------------------------

template<class TList>
struct Length;

template<>
struct Length<NullType> {
  static constexpr int value = 0;
};

template<class THead, class TTail>
struct Length<TypeList<THead, TTail>> {
  static constexpr int value = 1 + Length<TTail>::value;
};
//--------------------------------------------------------------------------------
// TypeAt
//--------------------------------------------------------------------------------

template<class TList, unsigned int TIndex>
struct TypeAtImpl;

template<class TList, unsigned int TIndex>
using TypeAt = typename TypeAtImpl<TList, TIndex>::Result;

template<class THead, class TTail>
struct TypeAtImpl<TypeList<THead, TTail>, 0> {
  using Result = THead;
};

template<class THead, class TTail, unsigned int TIndex>
struct TypeAtImpl<TypeList<THead, TTail>, TIndex> {
  using Result = TypeAt<TTail, TIndex - 1>;
};
//--------------------------------------------------------------------------------
// IndexOf
//--------------------------------------------------------------------------------

template<class TList, class TType>
struct IndexOf;

template<class TType>
struct IndexOf<NullType, TType> {
  static constexpr int value = -1;
};

template<class TType, class TTail>
struct IndexOf<TypeList<TType, TTail>, TType> {
  static constexpr int value = 0;
};

template<class THead, class TTail, class TType>
struct IndexOf<TypeList<THead, TTail>, TType> {
private:
  static constexpr int temp = IndexOf<TTail, TType>::value;

public:
  static constexpr int value = (temp == -1 ? -1 : 1 + temp);
};
//--------------------------------------------------------------------------------
// Append
//--------------------------------------------------------------------------------
// It appends a type to a TypeList or merges two TypeLists
//--------------------------------------------------------------------------------

template<class TList, class TType>
struct AppendImpl;

template<class TList, class TType>
using Append = typename AppendImpl<TList, TType>::Result;

template<>
struct AppendImpl<NullType, NullType> {
  using Result = NullType;
};

template<class TType>
struct AppendImpl<NullType, TType> {
  using Result = MakeTypeList<TType>;
};

template<class THead, class TTail>
struct AppendImpl<NullType, TypeList<THead, TTail>> {
  using Result = TypeList<THead, TTail>;
};

template<class THead, class TTail, class TType>
struct AppendImpl<TypeList<THead, TTail>, TType> {
  using Result = TypeList<THead, Append<TTail, TType>>;
};
//--------------------------------------------------------------------------------
// Erase
//--------------------------------------------------------------------------------
// Erase first entry of a type if any
//--------------------------------------------------------------------------------

template<class TList, class TType>
struct EraseImpl;

template<class TList, class TType>
using Erase = typename EraseImpl<TList, TType>::Result;

template<class TType>
struct EraseImpl<NullType, TType> {
  using Result = NullType;
};

template<class TType, class TTail>
struct EraseImpl<TypeList<TType, TTail>, TType> {
  using Result = TTail;
};

template<class THead, class TTail, class TType>
struct EraseImpl<TypeList<THead, TTail>, TType> {
  using Result = TypeList<THead, Erase<TTail, TType>>;
};
//--------------------------------------------------------------------------------
// EraseAll
//--------------------------------------------------------------------------------
// Erase all entries of a type
//--------------------------------------------------------------------------------

template<class TList, class TType>
struct EraseAllImpl;

template<class TList, class TType>
using EraseAll = typename EraseAllImpl<TList, TType>::Result;

template<class TType>
struct EraseAllImpl<NullType, TType> {
  using Result = NullType;
};

template<class TType, class TTail>
struct EraseAllImpl<TypeList<TType, TTail>, TType> {
  using Result = EraseAll<TTail, TType>;
};

template<class THead, class TTail, class TType>
struct EraseAllImpl<TypeList<THead, TTail>, TType> {
  using Result = TypeList<THead, EraseAll<TTail, TType>>;
};
//--------------------------------------------------------------------------------
// NoDuplicates
//--------------------------------------------------------------------------------

template<class TList>
struct NoDuplicatesImpl;

template<class TList>
using NoDuplicates = typename NoDuplicatesImpl<TList>::Result;

template<>
struct NoDuplicatesImpl<NullType> {
  using Result = NullType;
};

template<class THead, class TTail>
struct NoDuplicatesImpl<TypeList<THead, TTail>> {
private:
  using GoodTail = NoDuplicates<TTail>;
  using GoodTailWithoutHead = Erase<GoodTail, THead>;

public:
  using Result = TypeList<THead, GoodTailWithoutHead>;
};
//--------------------------------------------------------------------------------
// Replace
//--------------------------------------------------------------------------------
// Replace first entry of TToReplace with TToReplaceWith
//--------------------------------------------------------------------------------

template<class TList, class TToReplace, class TToReplaceWith>
struct ReplaceImpl;

template<class TList, class TToReplace, class TToReplaceWith>
using Replace = typename ReplaceImpl<TList, TToReplace, TToReplaceWith>::Result;

template<class TToReplace, class TToReplaceWith>
struct ReplaceImpl<NullType, TToReplace, TToReplaceWith> {
  using Result = NullType;
};

template<class TToReplace, class TTail, class TToReplaceWith>
struct ReplaceImpl<TypeList<TToReplace, TTail>, TToReplace, TToReplaceWith> {
  using Result = TypeList<TToReplaceWith, TTail>;
};

template<class THead, class TTail, class TToReplace, class TToReplaceWith>
struct ReplaceImpl<TypeList<THead, TTail>, TToReplace, TToReplaceWith> {
  using Result = TypeList<THead, Replace<TTail, TToReplace, TToReplaceWith>>;
};
//--------------------------------------------------------------------------------
// ReplaceAll
//--------------------------------------------------------------------------------
// Replace all entries of TToReplace with TToReplaceWith
//--------------------------------------------------------------------------------

template<class TList, class TToReplace, class TToReplaceWith>
struct ReplaceAllImpl;

template<class TList, class TToReplace, class TToReplaceWith>
using ReplaceAll =
    typename ReplaceAllImpl<TList, TToReplace, TToReplaceWith>::Result;

template<class TToReplace, class TToReplaceWith>
struct ReplaceAllImpl<NullType, TToReplace, TToReplaceWith> {
  using Result = NullType;
};

template<class TToReplace, class TTail, class TToReplaceWith>
struct ReplaceAllImpl<TypeList<TToReplace, TTail>, TToReplace, TToReplaceWith> {
  using Result =
      TypeList<TToReplaceWith, ReplaceAll<TTail, TToReplace, TToReplaceWith>>;
};

template<class THead, class TTail, class TToReplace, class TToReplaceWith>
struct ReplaceAllImpl<TypeList<THead, TTail>, TToReplace, TToReplaceWith> {
  using Result = TypeList<THead, ReplaceAll<TTail, TToReplace, TToReplaceWith>>;
};
//--------------------------------------------------------------------------------
} // namespace TL
} // namespace NSLibrary
#endif // TYPELIST_H
