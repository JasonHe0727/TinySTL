#ifndef TRIE_HPP
#define TRIE_HPP
#include "String.hpp"
#include "Array.hpp"
#include "Queue.hpp"
#include "Option.hpp"

template <typename TValue>
class Trie {
private:
	class Node {
	private:
		Option<TValue> value;
		Array<Node*> next;
	public:
		Node() = default;
		Node(int radix): value {}, next(radix) {
		}
	};
	int radix;
	Node* root;
public:
	const TValue& operator[](const String& key) const {
		Node* x = Get(root, key, 0);
		if(x == nullptr) {
			return nullptr;
		} else {
			return x->val;
		}
	}
	void Insert(const String& key, const TValue& val) {
		root = Put(root, key, val, 0);
	}
	Queue<String> Keys() {
		return KeysWithPrefix("");
	}
	Queue<String> KeysWithPrefix(String prefix) {
		Queue<String> queue;
		Collect(Get(root, prefix, 0), prefix, queue);
		return queue;
	}
	void Collect(Node* x, const String& prefix, const Queue<String>& queue) {
		if(x == nullptr) {
			return;
		}
		if(x->val.HasValue()) {
			queue->Enqueue(prefix);
		}
		for(Char c = 0; c < radix; c = c + 1) {
			Collect(x->next[c], prefix + c, queue);
		}
	}
	Queue<String> KeysThatMatch(String pattern) {
		Queue<String> queue;
		Collect(root, "", pattern, queue);
	}

	void Collect(Node* x, const String& prefix, const String pattern, Queue<String> queue) {
		// TO DO
	}
private:
	Node* Get(Node* x, const String& key, int width) {
		if(x == nullptr) {
			return nullptr;
		} else if(width = key.Size()) {
			return x;
		} else {
			Char c = key[width];
			return Get(x->next[c], key, width + 1);
		}
	}
	Node* Put(Node* x, const String& key, const TValue& val, int width) {
		if(x == nullptr) {
			x = new Node(radix);
		} else if(d == key.Size()) {
			x->val = val;
			return x;
		} else {
			Char c = key[width];
			x->next[c] = Put(x->next[c], key, val, width + 1);
			return x;
		}
	}
};

#endif // TRIE_HPP
