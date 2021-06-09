#ifndef FUNCTIONMODULEBASE_H
#define FUNCTIONMODULEBASE_H

#include "FunctionHelper.h"
#include "Selector.h"

#include <utility>

namespace NSMath {

template<class TSignature, class TElementList, class... TFuncs>
class FModeBaseImpl {
  using CSignature = TSignature;
  using CFunctionPtr = CSignature*;
  using LevelList = TElementList;
  using ReturnType = NSLibrary::ReturnType<CSignature>;
  static_assert(NSLibrary::EL::IsDecreasing<LevelList>::value,
                "Levels must go in decreasing order!");
  static_assert(NSLibrary::EL::Length<LevelList>::value + 1 ==
                    sizeof...(TFuncs),
                "Incompatible amount of constructor arguments!");

public:
  FModeBaseImpl(TFuncs*... funcs, int level)
      : Function_(
            NSLibrary::Selector::SetSignature<CSignature>::template SetLevelsT<
                TElementList>::choose(funcs..., level)) {
  }

  template<class... TArgs>
  ReturnType operator()(TArgs&&... args) const {
    return Function_(std::forward<TArgs>(args)...);
  }

private:
  CFunctionPtr Function_;
};

template<class TSignature, class TElementList, class TSeq>
struct FModeHelperImpl;

template<class TSignature, class TElementList, class TSeq>
using FModeHelper =
    typename FModeHelperImpl<TSignature, TElementList, TSeq>::Result;

template<class TSignature, class TElementList, class... TArgs>
struct FModeHelperImpl<TSignature, TElementList, NSLibrary::TypeSeq<TArgs...>> {
  using Result = FModeBaseImpl<TSignature, TElementList, TArgs...>;
};

template<class TSignature, class TElementList>
using FModeBase = FModeHelper<
    TSignature, TElementList,
    NSLibrary::TL::MakeTypeSeqN<
        TSignature, NSLibrary::EL::Length<TElementList>::value + 1>>;

template<class TSignature, int... TInts>
using FunctionModuleBase =
    FModeBase<TSignature, NSLibrary::EL::MakeElementList<TInts...>>;

} // namespace NSMath

#endif // FUNCTIONMODULEBASE_H
