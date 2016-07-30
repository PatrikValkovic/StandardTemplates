#ifndef TEMPLATES_BINARYSEARCHTREE_H
#define TEMPLATES_BINARYSEARCHTREE_H

#include "Vector.h"
#include "Queue.h"

namespace Templates
{
    template<typename T, bool ALLOW_DUPLICITIES = true>
    class BinarySearchTree
    {
    private:
        class Node
        {
        public:
            T Val;
            Node* Child[2] = {NULL, NULL};
        };

        Node* Root = NULL;

        struct TempCopyStructure
        {
            Node* CopyFrom;
            Node** CopyTo;
        };

        int (* Distribution)(const T* const First, const T* const Second);
        int CountOfElements;
    public:
        /**
         * Ditribution - 0 if equal
         *             - <0 if First is smaller then Second
         *             - >0 if First is bigger then Second
         */
        BinarySearchTree(int(* Distribution)(const T* const First, const T* const Second))
        {
            this->CountOfElements = 0;
            this->Distribution = Distribution;
            this->Root = NULL;
        }

        /**
         * Copy constructor
         */
        BinarySearchTree(BinarySearchTree& Second)
                : BinarySearchTree(Second.Distribution)
        {
            CountOfElements = Second.CountOfElements;

            Queue<TempCopyStructure> CopyQueue;
            TempCopyStructure ToCopy{Second.Root, &this->Root};
            CopyQueue.Push(ToCopy);

            while (!CopyQueue.IsEmpty())
            {
#ifdef ADDITIONAL_TESTS
                if (!CopyQueue.Pop(ToCopy))
                    throw new QueueException(__FILE__, __LINE__);
#else
                CopyQueue.Pop(ToCopy);
#endif
                *ToCopy.CopyTo = new Node;
                (*ToCopy.CopyTo)->Val = ToCopy.CopyFrom->Val;
                for (int a = 0; a < 2; a++)
                    if (ToCopy.CopyFrom->Child[a] != NULL)
                        CopyQueue.Push(TempCopyStructure{ToCopy.CopyFrom->Child[a],
                                                         (&(*ToCopy.CopyTo)->Child[a])});
            }
        }

        /**
         * Destructor
         */
        ~BinarySearchTree()
        {
            this->Clear();
        }

        BinarySearchTree& operator=(const BinarySearchTree& Second)
        {
            throw new NotImplementedException(__FILE__, __LINE__);
            //TODO
        }

        /**
         * Return count of elements in tree
         */
        int Size()
        {
            return this->CountOfElements;
        }

        /**
         * Insert element into tree
         * return 1, if was element inserted
         */
        int Insert(T& Value)
        {
            Node* Created = new Node;
            Created->Val = Value;
            if (Root == NULL)
            {
                this->Root = Created;
                CountOfElements++;
                return 1;
            }

            Node* Previous = NULL;
            Node* Temp = this->Root;
            while (Temp != NULL)
            {
                int Result = this->Distribution(&Temp->Val, &Value);
                Previous = Temp;
                if (!ALLOW_DUPLICITIES && Result == 0)
                {
                    delete Created;
                    return 0;
                }
                Temp = Temp->Child[Result >= 0];
            }
            Previous->Child[this->Distribution(&Previous->Val, &Value) >= 0] = Created;
            CountOfElements++;
            return 1;
        }

        /**
         * Insert @Count values into tree
         * returns count of inserted elements
         */
        int Insert(T* Values, int Count)
        {
            int inserted = 0;
            for (int a = 0; a < Count; a++)
                inserted += this->Insert(*(Values++));
            return inserted;
        }

        /**
         * Removes all nodes from tree
         * Return count of deleted nodes
         */
        int Clear()
        {
            //TODO rewrite to use queue
            if (this->Root == NULL)
                return 0;
            int Deleted = 0;
            Stack<Node*>* ToDeleteStack = new Stack<Node*>();
            ToDeleteStack->Push(this->Root);

            Node* ToDelete;
            while (!ToDeleteStack->IsEmpty())
            {
                if (!ToDeleteStack->Pop(ToDelete))
                {
                    delete ToDeleteStack;
                    return -1;
                }

                if (ToDelete->Child[1])
                    ToDeleteStack->Push(ToDelete->Child[1]);
                if (ToDelete->Child[0])
                    ToDeleteStack->Push(ToDelete->Child[0]);
                delete ToDelete;
                Deleted++;
            }
            this->Root = NULL;
            delete ToDeleteStack;
            CountOfElements -= Deleted;
            return Deleted;
        }

        /**
         * Return true, if is Value in tree, otherwise false
         */
        bool Contain(const T& Value) const
        {
            if (this->Root == NULL)
                return false;
            Node* Temp = this->Root;
            while (Temp != NULL)
            {
                int Resolve = this->Distribution(&Temp->Val, &Value);
                if (Resolve == 0)
                    return true;
                Temp = Temp->Child[Resolve > 0];
            }
            return false;
        }

        /**
         * Return element with specific properties
         * Return true on success, false otherwise
         */
        bool Get(T*& Returned, const T& ToFind) const
        {
            Node* Result = this->GetNode(ToFind);
            if (Result == NULL)
                return false;
            Returned = &(Result->Val);
            return true;
        }

        /**
         * Return element by callback
         */
        Vector<T*> Get(bool(* Callback)(const T* const Value, void* data), void* data = NULL, int Count = 1)
        {
            throw new NotImplementedException(__FILE__, __LINE__);
            //TODO
        }

        /**
         * Try to find specific element
         * If this element doesnt exists, creates new based on parameter
         * Return -1 if fails, 0 if success and 1 if was created
         */
        int GetOrCreate(T& ToFind, T*& Return)
        {
            Node* Result = this->GetNode(ToFind);

            if (Result != NULL)
            {
                Return = &(Result->Val);
                return 0;
            }

            if (!ALLOW_DUPLICITIES)
                return -1;

            int Inserted = this->Insert(ToFind);
#ifdef ADDITIONAL_TESTS
            if (Inserted != 1)
                throw new Exception(__FILE__, __LINE__); //TODO specific exception
#endif
            Inserted = (bool)this->Get(Return,ToFind);
#ifdef ADDITIONAL_TESTS
            if(Inserted)
                return 1;
            else
                throw new Exception(__FILE__,__LINE__); //TODO specific function
#endif
            return 1;
        }

        /**
         * Try to find specific element, remove it and return it
         * Return 0 if wasnt found, 1 if was element deleted
         */
        int GetAndDelete(T& ToFind, T& Return)
        {
            Node* Returned = this->GetNode(ToFind);
            if(Returned==NULL)
                return 0;
            Return = Returned->Val;
            this->Delete(Return);
            return 1;
        }

    private:
        void ToArrayRecursive(Vector <T>& Array, Node* Temp) const
        {
            if (Temp == NULL)
                return;
            ToArrayRecursive(Array,
                             Temp->Child[1]); //must be reversed, because new elements are inserted to begin of vector
            Array.Insert(Temp->Val);
            ToArrayRecursive(Array, Temp->Child[0]);
            return;
        }

        class ToDeleteHelpClass
        {
        public:
            ToDeleteHelpClass()
            {}

            ToDeleteHelpClass(Node* Parent, Node* ToDelete)
                    : Parent(Parent), ToDelete(ToDelete)
            {}

            Node* Parent = NULL;
            Node* ToDelete = NULL;
        };

        /**
         * Remove node from tree.
         * Return node replaced by original node, NULL if was leaf
         */
        Node* RemoveNode(ToDeleteHelpClass Deleting)
        {
            Node** ParentPointer = NULL;
            if (Deleting.ToDelete == this->Root)
                ParentPointer = &this->Root;
            else
                ParentPointer = &Deleting.Parent->Child[(Deleting.Parent->Child[1] == Deleting.ToDelete)];

            //ToDelete is leaf
            if (Deleting.ToDelete->Child[0] == NULL && Deleting.ToDelete->Child[1] == NULL)
            {
                delete Deleting.ToDelete;
                *ParentPointer = NULL;
                return NULL;
            }

            //if ToDelete have only one children
            if (Deleting.ToDelete->Child[0] == NULL || Deleting.ToDelete->Child[1] == NULL)
            {
                *ParentPointer = Deleting.ToDelete->Child[Deleting.ToDelete->Child[0] == NULL];
                delete Deleting.ToDelete;
                return *ParentPointer;
            }

            //just rotate
            if (Deleting.ToDelete->Child[0]->Child[1] == NULL)
            {
                Deleting.ToDelete->Child[0]->Child[1] = Deleting.ToDelete->Child[1];
                *ParentPointer = Deleting.ToDelete->Child[0];
                delete Deleting.ToDelete;
                return *ParentPointer;
            }
            if (Deleting.ToDelete->Child[1]->Child[0] == NULL)
            {
                Deleting.ToDelete->Child[1]->Child[0] = Deleting.ToDelete->Child[0];
                *ParentPointer = Deleting.ToDelete->Child[1];
                delete Deleting.ToDelete;
                return *ParentPointer;
            }

            Node* Parent = Deleting.ToDelete->Child[0];
            Node* Replaced = Parent->Child[1];
            while (Replaced->Child[1] != NULL)
            {
                Parent = Replaced;
                Replaced = Parent->Child[1];
            }
            Parent->Child[1] = Replaced->Child[0];
            for (int a = 0; a < 2; a++)
                Replaced->Child[a] = Deleting.ToDelete->Child[a];
            *ParentPointer = Replaced;
            delete Deleting.ToDelete;
            return *ParentPointer;
        }

        Node* GetNode(const T& ToFind) const //TODO return with parent
        {
            if (this->Root == NULL)
                return NULL;
            Node* Temp = this->Root;
            while (Temp != NULL)
            {
                int Resolve = this->Distribution(&Temp->Val, &ToFind);
                if (Resolve == 0)
                {
                    return Temp;
                }
                Temp = Temp->Child[Resolve > 0];
            }
            return NULL;
        }

    public:
        /**
         * Return all elements in tree.
         * Elements will be sorted
         * Otherwise NULL
         */
        T* ToArray(int& Count) const
        {
            Vector<T> ArrayTemp;
            ToArrayRecursive(ArrayTemp, this->Root);
            return ArrayTemp.ToArray(Count);
        }

        /**
         * Delete all elements, in which callback return true
         * Return count of deleted elements
         * data parameter will be passed to callback
         */
        int Delete(bool(* Callback)(const T* const Value, void* data), void* data = NULL)
        {
            if (this->Root == NULL)
                return 0;
            int deleted = 0;
            Queue<ToDeleteHelpClass> Nodes;
            Nodes.Push(ToDeleteHelpClass(NULL, this->Root));

            ToDeleteHelpClass Temp;
            while (Nodes.Pop(Temp))
            {
                if (Callback(&Temp.ToDelete->Val, data))
                {
                    Node* Replaced = this->RemoveNode(Temp);
                    if (Replaced != NULL)
                        Nodes.Push(ToDeleteHelpClass(Temp.Parent, Replaced));
                    deleted++;
                }
                else
                {
                    for (int a = 0; a < 2; a++)
                        if (Temp.ToDelete->Child[a] != NULL)
                            Nodes.Push(ToDeleteHelpClass(Temp.ToDelete, Temp.ToDelete->Child[a]));
                }
            }
            CountOfElements -= deleted;
            return deleted;
        }

        /**
         * Delete item from tree
         * return 1 if success, 0 otherwise
         */
        int Delete(T value)
        {
            if (this->Root == NULL)
                return 0;

            Node* Temp = this->Root;
            Node* Parent = NULL;

            while (Temp != NULL)
            {
                int Resolve = this->Distribution(&Temp->Val, &value);
                if (Resolve == 0)
                    break;
                Parent = Temp;
                Temp = Temp->Child[Resolve > 0];
            }

            if (Temp == NULL)
                return 0;

            this->RemoveNode(ToDeleteHelpClass(Parent, Temp));
            CountOfElements--;
            return 1;
        }
    };
}
#endif //TEMPLATES_BINARYSEARCHTREE_H
