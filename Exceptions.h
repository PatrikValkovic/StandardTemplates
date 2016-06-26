#ifndef TEMPLATES_EXCEPTIONS_H
#define TEMPLATES_EXCEPTIONS_H

#ifndef _STALIB_
#include <iostream>
#include <exception>
#endif

namespace Templates
{
    class Exception : public std::exception
    {
    protected:
        const char *Message;
        int LineNumber;

        virtual std::ostream &ToString(std::ostream &os) const
        {
            return os << "Error in " << this->Message << " on line " << this->LineNumber << std::endl;
        }

    public:
        Exception(const char *Message, const int &LineNumber)
        {
            this->Message = Message;
            this->LineNumber = LineNumber;
        };

        virtual ~Exception()
        { }

    private:
        friend std::ostream &operator<<(std::ostream &os, const Exception &e)
        {
            return (&e)->ToString(os);
        }
    };

    class InvalidArgumentException : public Exception
    {
    public:
        InvalidArgumentException(const char *Message, int LineNumber)
                : Exception(Message, LineNumber)
        { }

        virtual ~InvalidArgumentException()
        { }
    };

    class VectorException : public Exception
    {
    public:
        VectorException(const char *Message, int LineNumber)
                : Exception(Message, LineNumber)
        { }

        virtual ~VectorException()
        { }
    };

    class OutOfRangeException : public Exception
    {
    protected:
        virtual std::ostream &ToString(std::ostream &os)
        {
            return os << this->Message << std::endl;
        }

    public:
        OutOfRangeException() : Exception("Index is out of range.", -1)
        { }

        OutOfRangeException(const char *Message)
                : Exception(Message, -1)
        { }

        OutOfRangeException(const char *Message, int LineNumber)
                : Exception(Message, LineNumber)
        { }

        virtual ~OutOfRangeException()
        { }
    };

    class QueueException : public Exception
    {
    public:
        QueueException(const char *File, const int Line) :
                Exception(File, Line)
        { }

        virtual ~QueueException()
        { }
    };

    class ListException : public Exception
    {
    public:
        ListException(const char *File, const int Line) :
                Exception(File, Line)
        { }

        virtual ~ListException()
        { }
    };

    class ArrayException : public Exception
    {
    public:
        ArrayException(const char *File, const int Line) :
                Exception(File, Line)
        { }

        virtual ~ArrayException()
        { }
    };

    class NotImplementedException : public Exception
    {
    public:
        NotImplementedException(const char *File, const int Line) :
                Exception(File, Line)
        { }

        virtual ~NotImplementedException()
        { }
    };
}

namespace Math
{
    class IntervalException : public Templates::Exception
    {
    public:
        IntervalException(const char *File, const int Line) :
                Exception(File, Line)
        { }

        virtual ~IntervalException()
        { }
    };

}

#endif //TEMPLATES_EXCEPTIONS_H
