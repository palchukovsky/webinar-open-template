#include <iostream>

template <typename T, size_t capacity>
class FixedSizeContainer
{
	T m_data[capacity];
	std::size_t m_size = 0;

public:
	bool push_back(T v)
	{
		if (m_size >= capacity)
		{
			// No free space to add one more element
			return false;
		}
		m_data[m_size] = std::move(v);
		++m_size;
		return true;
	}

	const T & get(size_t pos) const
	{
		if (pos >= m_size)
		{
			throw std::out_of_range("Requested postion is out of range");
		}
		return m_data[pos];
	}

	bool erase(size_t pos)
	{
		if (pos >= m_size)
		{
			// invalid position
			return false;
		}
		// need to move all element after 'pos' to one position to the left
		--m_size;
		for (size_t i = pos; i < m_size; ++i)
		{
			m_data[i] = std::move(m_data[i + 1]);
		}
		return true;
	}

	size_t size() const { return m_size; }
};

//-----------------------------------------------------------------------------

template <typename T, size_t N>
void print_container(const FixedSizeContainer<T, N> &container)
{
	for (size_t i = 0; i < container.size(); ++i)
	{
		if (i != 0) {
			std::cout << ' ';
		}
		std::cout << container.get(i);
	}
}

template <typename T>
void print_container_2(const T &container)
{
	for (size_t i = 0; i < container.size(); ++i)
	{
		if (i != 0) {
			std::cout << ' ';
		}
		std::cout << container.get(i);
	}
}

int main()
{
	FixedSizeContainer<int, 5> container;

	container.push_back(0);
	container.push_back(1);
	container.push_back(2);
	container.push_back(3);
	container.push_back(4);

	print_container(container);
	std::cout << std::endl;

	container.erase(2);

	print_container_2(container);
	std::cout << std::endl;
}
