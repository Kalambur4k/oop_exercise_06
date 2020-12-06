#include <stdexcept>

template<typename T>
class TStack {
private:
	class TNode {
	public:
		TNode(T val, TNode *nxt): value{val}, next{nxt} {};
        friend class TStack;

	private:
		TNode *next;
		T value;
	};

	TNode *top;

public:
    TStack(): top{nullptr} {}

    ~TStack() {
        while (top) {
            TNode *oldTop = top;
			top = top->next;
            delete oldTop;
        }
    }

	void Push(const T& val) {
		top = new TNode(val, top );
	}

	T Pop() {
		if (top) {
            T res = top->value;
            TNode *oldTop = top;
			top = top->next;
            delete oldTop;
			return res;
		}
        throw std::runtime_error("Stack is empty");
	}

    T Top() {
        if (top) {
            return top->value;
        }
        throw std::runtime_error("Stack is empty");
    }

    bool Empty() {
        return !top;
    }

};
