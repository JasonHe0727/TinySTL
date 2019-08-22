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
	public:
		Option<TValue> value;
		Array<Node*> next;

		Node() = default;
		Node(int radix): value {}, next(radix) {
			for(int i = 0; i < next.Length(); i++) {
				next[i] = nullptr;
			}
		}
		~Node() {
			for(int i = 0; i < next.Length(); i++) {
				if(next[i] != nullptr) {
					delete next[i];
				}
			}
		}
	};
	Node* root;
	int radix;
public:
	Trie(): root{nullptr}, radix{0} {
	}
	explicit Trie(int radix): root{nullptr}, radix{radix} {
	}
	Trie(const Trie&) = delete;
	Trie& operator=(const Trie&) = delete;
	~Trie() {
		if(root != nullptr) {
			delete root;
		}
	}
	Option<TValue> operator[](const String& key) const {
		Node* x = Get(root, key, 0);
		if(x == nullptr) {
			return Option<TValue>();
		} else {
			return x->value;
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
	void Collect(Node* x, const String& prefix, Queue<String>& queue) {
		if(x == nullptr) {
			return;
		}
		if(x->value.HasValue()) {
			queue.Enqueue(prefix);
		}
		for(Char c = 0; c.ToInt() < radix; c = c + 1) {
			Collect(x->next[c], prefix + c, queue);
		}
	}
	Queue<String> KeysThatMatch(String pattern) {
		Queue<String> queue;
		Collect(root, "", pattern, queue);
	}

	void Collect(Node* x, const String& prefix, const String pattern, Queue<String> queue) {
		int width = prefix.Length();
		if(x == nullptr) {
			return;
		} else if(width == pattern.Length() && x->value.HasValue()) {
			queue.Enqueue(prefix);
		} else if(width == pattern.Length()) {
			return;
		}
		Char next = pattern[width];
		for(Char c = 0; c.ToInt() < radix; c = c + 1) {
			if(next == Char('.') || next == c) {
				Collect(x->next[c], prefix + c, pattern, queue);
			}
		}
	}
	String LongestPrefixOf(const String& s) {
		int length = Search(root, s, 0, 0);
		return s.Slice(0, length);
	}
	void Delete(const String& key) {
		root = Delete(root, key, 0);
	}
//	void Traverse() {
//		Traverse(root, 0);
//	}
//	void Traverse(Node* node, int indent) {
//		if(node != nullptr) {
//			if(node->value.HasValue()) {
//				Console::WriteIntLine(node->value.Get());
//			} else {
//				Console::WriteLine("NA");
//			}
//			for(int i = 0; i < node->next.Size(); i++) {
//				if(node->next[i]) {
//					for(int i = 0; i < indent; i++) {
//						Console::Write(' ');
//					}
//					Console::Write(i);
//					Console::Write(':');
//					Traverse(node->next[i], indent + 2);
//				}
//			}
//		}
//	}
private:
	Node* Get(Node* x, const String& key, int width) const {
		if(x == nullptr) {
			return nullptr;
		} else if(width == key.Size()) {
			return x;
		} else {
			Char c = key[width];
			return Get(x->next[c], key, width + 1);
		}
	}
	Node* Put(Node* x, const String& key, const TValue& val, int width) {
		if(x == nullptr) {
			x = new Node(radix);
		}
		if(width == key.Size()) {
			x->value = val;
			return x;
		} else {
			Char c = key[width];
			x->next[c] = Put(x->next[c], key, val, width + 1);
			return x;
		}
	}
	int Search(Node* x, const String& s, int width, int length) {
		if(x == nullptr) {
			return length;
		}
		if(x->value != nullptr) {
			length = width;
		}
		if(width == s.Length()) {
			return length;
		}
		Char c = s[width];
		return Search(x->next[c], s, width + 1, length);
	}
	Node* Delete(Node* x, const String& key, int width) {
		if(x == nullptr) {
			return nullptr;
		} else if(width == key.Length()) {
			x->value = Option<TValue>();
		} else {
			Char c = key[width];
			x->next[c] = Delete(x->next[c], key, width + 1);
		}
		if(x->value != nullptr) {
			return x;
		}
		for(Char c{0}; c.ToInt() < radix; c = c + 1) {
			if(x->next[c] != nullptr) {
				return x;
			}
		}
		return nullptr;
	}
};

#endif // TRIE_HPP
