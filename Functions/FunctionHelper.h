#ifndef FUNCTIONHELPER_H
#define FUNCTIONHELPER_H

#include "TypeList.h"

namespace NSLibrary {

template<class TSignature>
struct ReturnTypeImpl;

template<class TSignature>
using ReturnType = typename ReturnTypeImpl<TSignature>::Result;

template<class R, class... TArgs>
struct ReturnTypeImpl<R(TArgs...)> {
  using Result = R;
};

template<class TSignature>
struct ArgSequenceImpl;

template<class TSignature>
using ArgSequence = typename ArgSequenceImpl<TSignature>::Result;

template<class R, class... TArgs>
struct ArgSequenceImpl<R(TArgs...)> {
  using Result = TypeSeq<TArgs...>;
};

template<class TSignature>
using ArgTypeList = TL::Seq2List<ArgSequence<TSignature>>;

} // namespace NSLibrary

#endif // FUNCTIONHELPER_H
