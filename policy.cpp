#include <iostream>
#include <string>


// The policy for special setup.
struct DefaultPolicy {

    template <typename Record>
    static void onAdd(const Record &) {}

    template <typename Record>
    static void onRemove(const Record &) {}

};

//-----------------------------------------------------------------------------

template <typename T, size_t capacity, typename Policy = DefaultPolicy>
class FixedSizeContainer
{
	T m_data[capacity];
	std::size_t m_size = 0;

public:
  ~FixedSizeContainer() {
    for (size_t i = 0; i < m_size; ++i) {
      Policy::onRemove(m_data[i]);
    }
  }

	bool push_back(T v)
	{
		if (m_size >= capacity)
		{
			// No free space to add one more element
      Policy::onRemove(v);
			return false;
		}
    Policy::onAdd(v);
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

    Policy::onRemove(m_data[pos]);

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

template <typename T>
void print_container(const T &container)
{
	for (size_t i = 0; i < container.size(); ++i)
	{
		if (i != 0) {
			std::cout << ' ';
		}
		std::cout << container.get(i);
	}
}

//-----------------------------------------------------------------------------

class Obj {
public:
  explicit Obj(int id) : m_id{id} {}
  ~Obj() { std::cout << "Obj " << m_id << " destroyed." << std::endl; }

  Obj(const Obj &) = delete;
  Obj(Obj &&) = delete;
  Obj & operator=(const Obj &) = delete;
  Obj & operator=(Obj &&) = delete;
private:
  const int m_id;
};

//-----------------------------------------------------------------------------


// String policy
template<int maxLen>
struct StringPolicy {

    static void onAdd(std::string &record) {
        if (record.length() <= maxLen) {
          return;
        }
        record = record.substr(0, maxLen);
        record += "...";
    }

    static void onRemove(std::string& element) {}

};

// Pointer policy
struct SmartPtrPolicy {

    template<typename T>
    static void onAdd(const T *const) {
        // No special logic, it's already created.
    }

    template<typename T>
    static void onRemove(T *&ptr) {
      delete ptr;
      ptr = nullptr;
    }
};

int main()
{

	FixedSizeContainer<int, 5> container; // the same `FixedSizeContainer<int, 5, DefaultPolicy>`
	container.push_back(0);
	container.push_back(1);
	container.push_back(2);
	container.push_back(3);
	container.push_back(4);
	std::cout << "FixedSizeContainer<int, 5>:"<< std::endl;
  print_container(container);
	std::cout << std::endl << std::endl;

  FixedSizeContainer<std::string, 3> containerStr; // the same `FixedSizeContainer<std::string, 3, DefaultPolicy>`
	containerStr.push_back("000");
	containerStr.push_back("1111111111");
	containerStr.push_back("3333333333");
  std::cout << "FixedSizeContainer<std::string, 3>:"<< std::endl;
	print_container(containerStr);
	std::cout << std::endl << std::endl;

  FixedSizeContainer<std::string, 3, StringPolicy<5>> containerStrLimit;
	containerStrLimit.push_back("000");
	containerStrLimit.push_back("1111111111");
	containerStrLimit.push_back("333");
  std::cout << "FixedSizeContainer<std::string, 3, StringPolicy<5>>:"<< std::endl;
	print_container(containerStrLimit);
	std::cout << std::endl << std::endl;

  FixedSizeContainer<const Obj *, 3, SmartPtrPolicy> containerPtr;
	containerPtr.push_back(new Obj(1));
	containerPtr.push_back(new Obj(2));
	containerPtr.push_back(new Obj(3));
  std::cout << "FixedSizeContainer<const Obj *, 3, SmartPtrPolicy>:"<< std::endl;
	containerPtr.erase(1);

	std::cout << std::endl;
}
