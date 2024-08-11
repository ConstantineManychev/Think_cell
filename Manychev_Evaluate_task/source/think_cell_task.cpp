#include <map>
template<typename K, typename V>
class interval_map {
	friend void IntervalMapTest();
	V m_valBegin;
public:
	std::map<K, V> m_map;
	// constructor associates whole range of K with val
	interval_map(V const& val)
	: m_valBegin(val)
	{}


	void assign( K const& keyBegin, K const& keyEnd, V const& val ) 
	{
        if (keyBegin < keyEnd)
        {
			std::pair<K, V> extra = std::make_pair(keyEnd, m_valBegin);

			if (!m_map.empty())
			{
				typename std::map<K, V>::iterator itBegin;
				typename std::map<K, V>::iterator itEnd;

				itBegin = m_map.lower_bound(keyBegin);
				itEnd = m_map.lower_bound(keyEnd);

				typename std::map<K, V>::iterator it = (itBegin == m_map.begin()) ? m_map.end() : std::prev(itBegin);

				for (; it != itEnd && it != m_map.end(); ++it)
				{
					if (keyEnd < it->first)
					{
						break;
					}
					extra = std::make_pair(keyEnd, it->second);
				}

				m_map.erase(itBegin, itEnd);
			}

			if (!(extra.second == val))
			{
				auto it = m_map.lower_bound(keyBegin);
				if (it == m_map.end() || it->first != keyBegin)
				{
					it = m_map.insert(it, std::make_pair(keyBegin, val));
				}
				else
				{
					it->second = val;
				}

				if (it == m_map.end() || it->first != keyEnd)
				{
					m_map.insert(it, extra);
				}
			}
        }
	}

	// look-up of the value associated with key
	V const& operator[]( K const& key ) const 
	{
		auto it=m_map.upper_bound(key);
		if(it==m_map.begin()) {
			return m_valBegin;
		} else {
			return (--it)->second;
		}
	}
};