#ifndef TEMPLATES_ALGORITHMS_H
#define TEMPLATES_ALGORITHMS_H

#include "IteratorsDefinitions.h"

namespace Templates
{
    using namespace Iterators;

    /**
     * Find element in template. Return true, if was element find. Iter's value points to finded element.
     * Accepts callback to function and void* param, which will be pushed to validation callback.
     */
    template<typename T>
    bool Find(ForwardIteratorBase<T>* Iter,bool(*Validation)(const T* const Value,void* data), void* params = NULL)
    {
        while(Iter->IsValidIterator())
        {
            T* Val = Iter->GetValue();
#ifdef ADDITIONAL_TESTS
            if(Val==NULL)
                throw new InternalException(__FILE__,__LINE__);
#endif
            if (Validation(Val,params))
                return true;
            Iter->Next();
        }
        return false;
    }
}


#endif //TEMPLATES_ALGORITHMS_H
