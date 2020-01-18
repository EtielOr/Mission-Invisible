
#include <map>
#include <string>

// class of factory for objects


template<typename T> // template class to factory
class FactoryBase
{
public:

	static FactoryBase<T>& getInstace();

	bool registerObj(const std::string &objName, std::shared_ptr<T>(*func)(const int &x, const int &y)); // add object to the fectory
	std::shared_ptr<T> makeObj(const std::string &objName, const int &x, const int &y); // make a Object

	FactoryBase(const FactoryBase&) = delete;
	auto operator=(const FactoryBase&) = delete;

private:
	FactoryBase() {};

	std::map<std::string, std::shared_ptr<T>(*)(const int &x, const int &y)>  m_map; // map to return object
};



template<typename T>
inline FactoryBase<T> & FactoryBase<T>::getInstace()
{
	static FactoryBase<T> factory;

	return factory;
}

template<typename T>
inline bool FactoryBase<T>::registerObj(const std::string & objName, std::shared_ptr<T>(*func)(const int &x, const int &y))
{
	m_map.emplace(objName, func); // add the func to the map
	return true;
}

template<typename T>
inline std::shared_ptr<T> FactoryBase<T>::makeObj(const std::string & objName, const int & x, const int & y)
{
	auto func = m_map.find(objName); // look if the obj in the map

	if (func == m_map.end()) // case didn't find the object
		return nullptr;

	return func->second(x, y);
}