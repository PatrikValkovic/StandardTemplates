#ifndef TEMPLATES_INTERVAL_H
#define TEMPLATES_INTERVAL_H

#include "Exceptions.h"

using Templates::Exception;

namespace Math
{
    template<typename T>
    class Interval
    {
    private:
        void InsertVals(T First, T Second)
        {
            T Smaller = First < Second ? First : Second;
            T Bigger = First < Second ? Second : First;
            Begin = Smaller;
            End = Bigger;
        }

        T Begin;
        T End;
    public:
        Interval() : Interval(0, 0)
        { }

        Interval(T Begin, T End)
        {
            InsertVals(Begin, End);
        }

        T GetBegin() const
        {
            return Begin;
        }

        void SetBegin(T Value)
        {
            Begin = Value;
            InsertVals(Begin, End);
        }

        T GetEnd() const
        {
            return End;
        }

        void SetEnd(T Value)
        {
            End = Value;
            InsertVals(Begin, End);
        }

        /**
         * assignment operator
         */
        Interval &operator=(const Interval &Second)
        {
            if (this == &Second)
                return *this;

            Begin = Second.Begin;
            End = Second.End;
            InsertVals(Begin, End);
        }

        /**
         * Union
         */
        Interval operator+(const Interval &Second) const
        {
            T Begin = Begin < Second.Begin ? Begin : Second.Begin;
            T End = End < Second.End ? Second.End : End;
            return Interval(Begin, End);
        }

        Interval operator-(const Interval &Second) const
        {
            //        ---
            //  ---        ---
            if (Second.End < Begin || Second.Begin > End)
                return Interval(Begin, End);

            //        ------
            //   -----------------
            if (Second.Begin <= Begin && Second.End >= End)
                return Interval(0, 0);

            //        ------
            //   --------
            if (Second.Begin < Begin) // &&Second.End < End
                return Interval(Second.End, End);

            //        ------
            //            -----
            if (Second.Begin > Begin)
                return Interval(Begin, Second.Begin);

            throw new IntervalException(__FILE__, __LINE__);
        }

        bool operator==(const Interval &Second) const
        {
            return Begin == Second.Begin && End == Second.Begin;
        }

        bool operator!=(const Interval &Second) const
        {
            return !(*this == Second);
        }
    };
}
#endif //TEMPLATES_INTERVAL_H
