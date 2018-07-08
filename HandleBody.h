#pragma once

template <typename T>
class Handle
{

protected:
	T * pImpl_;

public:

	Handle<T>() {
		pImpl_ = new T; /// ModelImpl (singleton) "new" operator is overloaded.
		pImpl_->attach();
	}

	virtual ~Handle<T>() { pImpl_->detach(); }

	Handle<T>(const Handle& hd) : pImpl_(hd.pImpl_) { pImpl_->attach(); }

	Handle<T>& operator=(const Handle& hd) {
		if (this != &hd)
		{
			hd.pImpl_->attach();
			pImpl_->detach();
			pImpl_ = hd.pImpl_;
		}
		return *this;
	}
};

class Body
{

private:
	Body(const Body&) = delete;

	Body& operator=(const Body&) { return *this; }

	int refCount_;

public:

	Body() : refCount_(0) {  }

	void attach() { refCount_++; }

	void detach() {
		if (--refCount_ == 0) {
			delete this;
		}
	}

	int refCount() { return refCount_; }

	virtual ~Body() {}

};