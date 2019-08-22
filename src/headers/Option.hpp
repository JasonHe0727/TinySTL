#ifndef OPTION_HPP
#define OPTION_HPP
#include <type_traits>

template <typename T>
class Option {
private:
	using data_t = typename std::aligned_storage<sizeof(T),
		  std::alignment_of<T>::value>::type;
	bool hasValue;
	data_t data;
public:
	Option(): hasValue{false} {
	}

	Option(const T& value) {
		Initialize(value);
	}

	Option(T&& value): hasValue{false} {
		Initialize(std::move(value));
	}

	~Option() {
		Finalize();
	}

	Option(const Option<T>& other): hasValue{false} {
		if(other.hasValue) {
			Assign(other);
		}
	}

	Option(Option<T>&& other): hasValue{false} {
		if(other.hasValue) {
			Assign(std::move(other));
			other.Finalize();
		}
	}

	Option<T>& operator=(Option<T>&& other) {
		Assign(std::move(other));
		return *this;
	}

	Option<T>& operator=(const Option<T>& other) {
		Assign(other);
		return *this;
	}

	inline bool HasValue() const {
		return hasValue;
	}

	inline explicit operator bool() const {
		return hasValue;
	}

	inline T& Get() {
		return *((T*)(&data));
	}

	inline const T& Get() const {
		return *((T*)(&data));
	}
private:
	template <typename... Args>
	void Initialize(Args&&... args) {
		new (&data) T(std::forward<Args>(args)...);
		hasValue = true;
	}

	void Finalize() {
		if(hasValue) {
			hasValue = false;
			((T*)(&data))->~T();
		}
	}

	void Assign(const Option<T>& other) {
		if(other.hasValue) {
			Copy(other.data);
			hasValue = true;
		} else {
			Finalize();
		}
	}

	void Assign(Option<T>&& other) {
		if(other.hasValue) {
			Move(std::move(other.data));
			hasValue = true;
			other.Finalize();
		} else {
			Finalize();
		}
	}

	void Move(data_t&& value) {
		Finalize();
		new (&data) T(std::move(*((T*) (&value))));
	}

	void Copy(const data_t& value) {
		Finalize();
		new (&data) T(*((T*)(&value)));
	}


};
#endif // OPTION_HPP
