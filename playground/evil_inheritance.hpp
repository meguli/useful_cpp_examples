#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <utility>

/* 
	This code is from the talk "Inheritance is the base class of evil" by
	Sean Parent. This talk is like implementing polymorphism more close to
	type classes.
*/

template <typename T>
void draw(const T& x, std::ostream& out, size_t position)
{
	out << std::string(position, ' ') << x << '\n';
}
 
class object_t
{
public:

	template <typename T>
	object_t(T x) : self_(new model<T>(std::move(x)))
	{}

	object_t(const object_t& x) : self_(x.self_->copy_())
	{}

	object_t(object_t&&) noexcept = default;

	object_t& operator=(const object_t& x)
	{
		object_t tmp(x); *this = std::move(tmp); return *this;
	}

	object_t& operator=(object_t&& x) noexcept = default;

	// In the talk, we make this function friend
	void draw(std::ostream& out, size_t position) const
	{
		self_->draw_(out, position);
	}

private:

	struct concept_t
	{
		virtual ~concept_t() = default;
		virtual concept_t* copy_() const = 0;
		virtual void draw_(std::ostream&, size_t) const = 0;
	};

	template <typename T>
	struct model : concept_t
	{
		model(T x) : data_(std::move(x))
		{}

		concept_t* copy_() const
		{
			return new model(*this);
		}

		void draw_(std::ostream& out, size_t position) const
		{
			// And here, we call just draw without global quantifier
			::draw(data_, out, position);
		}

		T data_;
	};

	std::unique_ptr<concept_t> self_;
};

using document_t = std::vector<object_t>;

void draw(const document_t& x, std::ostream& out, size_t position)
{
	out << std::string(position, ' ') << "<document>" << '\n';
	for (const auto& e : x)
	{
		e.draw(out, position + 2);
	}
	out << std::string(position, ' ') << "</document>" << '\n';
}

class my_class_t
{
	//
};

// See non intrusive polymorphism
// We don't need to inherit from a base class, just supply the interface
void draw(const my_class_t& x, std::ostream& out, size_t position)
{
	out << std::string(position, ' ') << "my_class_t" << '\n';
}

/*
int main() {
	document_t document;

	document.emplace_back(0);
	document.emplace_back(1);
	document.emplace_back(std::string("Hello"));
	document.emplace_back(document);
	document.emplace_back(my_class_t{});

	draw(document, std::cout, 0);
	return 0;
}
*/