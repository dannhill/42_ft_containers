namespace ft
{

template<typename T>
class ft_vector
{
	public:
		ft_vector(void){
			_arr = new T[0];
			_size = 0;
			_capacity = 0;

			return;
		}
		virtual	~ft_vector(void){
			delete [] _arr;
		
			return;
		}
		ft_vector(ft_vector<T> const & cpy) : _size(cpy.size()), _capacity(cpy.capacity()){
			_arr = new T[_capacity];
			for (int i(0); i < _capacity; i++)
			{
				if (i < _size)
					_arr[i] = cpy[i];
				else
					_arr[i] = NULL;
			}

			return;
		}

		ft_vector & operator=(ft_vector<T> const & asn);
	protected:
		// protected vars
		T	*_arr;
		int	_size;
		int	_capacity;
		
		// static const
		static const int	_max_size(536870912);

};

}