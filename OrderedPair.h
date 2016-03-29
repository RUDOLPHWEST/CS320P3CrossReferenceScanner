#pragma once
template <typename  T1, typename T2>
class OrderedPair
{
public:
	T1 first;
	T2 second;
	// default constructor
	OrderedPair() : first(T1()), second(T2()) {}
	OrderedPair(T1 one, T2 two) : first(one), second(two) {}

	// overload < by comparing the first data members
	template<typename T1, typename T2>
	friend bool operator< (const OrderedPair<T1, T2>& lhs, const OrderedPair<T1, T2>& rhs);

	// overload == by comparing the first data members
	template<typename T1, typename T2>
	friend bool operator== (const OrderedPair<T1, T2>& lhs, const OrderedPair<T1, T2>& rhs);
	// overload != not necessary but may be convenient
	template<typename T1, typename T2>
	friend bool operator!=(const OrderedPair<T1, T2>& lhs, const OrderedPair<T1, T2>& rhs);

};
template<typename T1, typename T2>
bool operator< (const OrderedPair<T1, T2>& lhs, const OrderedPair<T1, T2>& rhs)
{
	return lhs.first < rhs.first;
}

// overload == by comparing the first data members
template<typename T1, typename T2>
bool operator== (const OrderedPair<T1, T2>& lhs, const OrderedPair<T1, T2>& rhs)
{
	return lhs.first == rhs.first;
}
// overload != not necessary but may be convenient
template<typename T1, typename T2>
bool operator!=(const OrderedPair<T1, T2>& lhs, const OrderedPair<T1, T2>& rhs)
{
	return !(lhs.first == rhs.first);
}