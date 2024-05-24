#ifndef GROUP_H
#define GROUP_H

template <class T>
class Operation {
    public:
        virtual T operate(const T &a, const T &b) const;
};

template <class T>
class OperationWithIdentity : public Operation<T> {
    public:
        virtual T getIdentity() const;
};

template <class T>
class OperationWithInverse : public Operation<T> {
    public:
        virtual T getInverse(const T &a) const;
};

class IntAddition : 
    public OperationWithIdentity<int>,
    public OperationWithInverse<int> {
        public:
            int operate(const int &a, const int &b) const;
            int getIdentity() const;
            int getInverse(const int &a) const;
};

class IntMultiplication : 
    public OperationWithIdentity<int> {
        public:
            int operate(const int &a, const int &b) const;
            int getIdentity() const;
};
#endif
