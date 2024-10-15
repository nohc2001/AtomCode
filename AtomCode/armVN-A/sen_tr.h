#define H_SEN_TR

class lcstr
{
public:
	char* Arr;
	size_t maxsize = 0;
	size_t up = 0;
	bool islocal = true;

	lcstr()
	{
		Arr = nullptr;
		maxsize = 0;
		up = 0;
		islocal = true;
	}

	virtual ~lcstr()
	{
		if (islocal) {
			delete[]Arr;
			Arr = nullptr;
		}
	}

	void NULLState()
	{
		Arr = nullptr;
		maxsize = 0;
		up = 0;
	}

	void Init(size_t siz, bool local)
	{
		islocal = local;
		char* newArr = new char[siz];
		if (Arr != nullptr)
		{
			for (int i = 0; i < maxsize; ++i)
			{
				newArr[i] = Arr[i];
			}

			delete[]Arr;
			Arr = nullptr;
		}

		Arr = newArr;
		maxsize = siz;
	}

	void operator=(const char* str)
	{
		int len = strlen(str) + 1;
		if (Arr == nullptr)
		{
			Arr = new char[len];
		}

		if (maxsize < len)
		{
			Init(len + 1, islocal);
		}
#if defined(__GNUC__)
		strcpy(Arr, str);
#elif defined (_MSC_VER)
		strcpy_s(Arr, len, str);
#endif
		up = len - 1;
	}

	bool operator==(char* str)
	{
		if (strcmp(Arr, str) == 0)
			return true;
		else
			return false;
	}

	bool operator==(const char* str)
	{
		if (strcmp(Arr, str) == 0)
			return true;
		else
			return false;
	}

	char& at(size_t i)
	{
		return Arr[i];
	}

	char* c_str()
	{
		Arr[up] = 0;
		return Arr;
	}

	char& operator[] (size_t i)
	{
		return Arr[i];
	}

	void push_back(char value)
	{
		if (up < maxsize)
		{
			Arr[up] = value;
			up += 1;
			Arr[up] = 0;
		}
		else
		{
			Init(maxsize * 2 + 1, islocal);
			Arr[up] = value;
			up += 1;
			Arr[up] = 0;
		}
	}

	void pop_back()
	{
		if (up - 1 >= 0)
		{
			up -= 1;
			Arr[up] = 0;
		}
	}

	void erase(size_t i)
	{
		for (int k = i; k < up; ++k)
		{
			Arr[k] = Arr[k + 1];
		}
		up -= 1;
	}

	void insert(size_t i, char value)
	{
		push_back(value);
		for (int k = maxsize - 1; k > i; k--)
		{
			Arr[k] = Arr[k - 1];
		}
		Arr[i] = value;
	}

	size_t size()
	{
		return up;
	}

	void clear()
	{
		if (Arr != nullptr)
			delete[]Arr;
		Arr = nullptr;
		up = 0;

		Init(2, islocal);
	}

	void release()
	{
		if (Arr != nullptr)
			delete[]Arr;
		Arr = nullptr;
		up = 0;
		islocal = false;
	}
};

template < typename T > class vecarr
{
public:
	T* Arr;
	size_t maxsize = 0;
	int up = 0;
	bool islocal = true;

	vecarr()
	{
		Arr = nullptr;
		maxsize = 0;
		up = 0;
		islocal = true;
	}

	~vecarr()
	{
		if (islocal) {
			release();
		}
	}

	void NULLState()
	{
		Arr = nullptr;
		maxsize = 0;
		up = 0;
	}

	void Init(size_t siz)
	{
		T* newArr = new T[siz];
		if (Arr != nullptr)
		{
			for (int i = 0; i < maxsize; ++i)
			{
				newArr[i] = Arr[i];
			}

			delete[]Arr;
			Arr = nullptr;
		}

		Arr = newArr;
		maxsize = siz;
	}

	T& at(size_t i)
	{
		return Arr[i];
	}

	T& operator[](size_t i)
	{
		return Arr[i];
	}

	void push_back(T value)
	{
		if (up < maxsize)
		{
			Arr[up] = value;
			up += 1;
		}
		else
		{
			Init(maxsize * 2 + 1);
			Arr[up] = value;
			up += 1;
		}
	}

	void pop_back()
	{
		if (up - 1 >= 0)
		{
			up -= 1;
			//Arr[up] = 0;
		}
	}

	void erase(size_t i)
	{
		for (int k = i; k < up; ++k)
		{
			Arr[k] = Arr[k + 1];
		}
		up -= 1;
	}

	void insert(size_t i, T value)
	{
		push_back(value);
		for (int k = maxsize - 1; k > i; k--)
		{
			Arr[k] = Arr[k - 1];
		}
		Arr[i] = value;
	}

	size_t size()
	{
		return up;
	}

	void clear()
	{
		if (Arr != nullptr)
			delete[]Arr;
		Arr = nullptr;
		up = 0;

		Init(2, islocal);
	}

	T& last() {
		if (up > 0) {
			return Arr[up - 1];
		}
		return Arr[0];
	}

	void release()
	{
		if (Arr != nullptr)
			delete[]Arr;
		Arr = nullptr;
		up = 0;
	}
};

int get_total_loop(vecarr<int>* sizes) {
	int total = 1;
	for (int i = 0; i < sizes->size(); ++i) {
		total *= sizes->at(i);
	}
	return total;
}

int get_index(vecarr<int>* sizes, int n, int realindex) {
	int mul = 1;
	for (int i = 0; i < n - 1; ++i) {
		mul *= sizes->at(i);
	}
	return (realindex / mul) % sizes->at(n);
}

union segstr
{
	char* str;
	char symbol;
};

struct segment
{
	char type = 'w';			// w : word, x : variable
	segstr data;				// word str
};

typedef vecarr < segment > sen;

struct seg_variable
{
	char symbol = 0;
	sen* value;
};

struct seg_range
{
	int start = 0;
	int end = 0;
};

typedef vecarr < vecarr < seg_variable >*> var_cases;

class word_base_sen_sys
{
public:
	vecarr < char* >wordlist;
	// data rule : every word mem siz is len + 1

	word_base_sen_sys()
	{
	}

	virtual ~word_base_sen_sys()
	{
	}

	void Init() {
		wordlist.NULLState();
		wordlist.Init(8);
	}

	void Release() {
		for (int i = 0; i < wordlist.size(); ++i) {
			char* cstr = wordlist.at(i);
			//cout << "Release : " << cstr << endl;
			int siz = strlen(cstr) + 1;
			free(cstr);
			wordlist.at(i) = nullptr;
		}
		wordlist.release();
		wordlist.NULLState();
	}

	void dbg_sen(sen* s)
	{
		for (int i = 0; i < s->size(); ++i)
		{
			if (s->at(i).type == 'w')
			{
				cout << s->at(i).data.str << " ";
			}
			else
			{
				cout << "var(" << s->at(i).data.symbol << ") ";
			}
		}
		cout << endl;
	}

	void dbg_varcases(var_cases* cases)
	{
		for (int i = 0; i < cases->size(); ++i)
		{
			cout << i << " case : " << endl;
			for (int k = 0; k < cases->at(i)->size(); ++k)
			{
				char sym = cases->at(i)->at(k).symbol;
				if (sym == 0)
				{
					cout << "\tbs ";
				}
				else
				{
					cout << "\t[" << sym << "]";
				}

				dbg_sen(cases->at(i)->at(k).value);
			}
		}
	}

	char* addword(char* str)
	{
		int siz = strlen(str) + 1;
		char* cstr = (char*)malloc(siz);
		strcpy_s(cstr, siz, str);
		wordlist.push_back(cstr);
		return cstr;
	}

	char* searchword(char* str)
	{
		for (int i = 0; i < wordlist.size(); ++i)
		{
			if (strcmp(wordlist.at(i), str) == 0)
			{
				return wordlist[i];
			}
		}
		return nullptr;
	}

	sen* makesen(const char* segs)
	{
		sen* ten = (sen*)malloc(sizeof(sen));
		int len = strlen(segs);
		lcstr str;
		str.NULLState();
		str.Init(len + 1, false);
		int _stack = 0;
		for (int i = 0; i < len; ++i)
		{
			if (_stack == 2)
			{
				segment sgm;
				sgm.data.symbol = segs[i];
				sgm.type = 'x';
				ten->push_back(sgm);
				str.clear();
			}
			else
			{
				if (segs[i] != ' ' && i + 1 < len)
				{
					str.push_back(segs[i]);
				}
				else
				{
					if (i + 1 == len)
					{
						str.push_back(segs[i]);
					}

					char* cstr = searchword(str.c_str());
					if (cstr == nullptr)
					{
						continue;
					}
					else
					{
						segment sgm;
						sgm.data.str = cstr;
						sgm.type = 'w';
						ten->push_back(sgm);
					}
					str.clear();
				}
			}

			if (segs[i] == '_')
			{
				++_stack;
			}
			else
			{
				_stack = 0;
			}
		}

		return ten;
	}

	vecarr < seg_range >* searchsen(sen* bigsen, sen* formsen)
	{
		int len = bigsen->size() - formsen->size() + 1;
		vecarr < seg_range >* ret =
			(vecarr < seg_range > *)malloc(sizeof(vecarr < seg_range >));
		ret->NULLState();
		ret->Init(8);
		int fsiz = formsen->size();
		for (int i = 0; i < len; ++i)
		{
			bool perfect = true;
			for (int k = 0; k < fsiz; ++k)
			{
				if (formsen->at(k).data.str != bigsen->at(i + k).data.str)
				{
					perfect = false;
					break;
				}
			}

			if (perfect)
			{
				seg_range r;
				r.start = i;
				r.end = i + fsiz - 1;
				ret->push_back(r);
			}
		}

		return ret;
	}

	var_cases* formming(sen* bigsen, sen* formsen)
	{
		var_cases* ret = (var_cases*)malloc(sizeof(var_cases));
		ret->NULLState();
		ret->Init(8);

		// get sentences not include variable
		vecarr < sen* > sentences;
		sentences.NULLState();
		sentences.Init(8);

		sen* ten = (sen*)malloc(sizeof(sen));
		ten->NULLState();
		ten->Init(8);
		for (int i = 0; i < formsen->size(); ++i)
		{
			if (formsen->at(i).type == 'x')
			{
				// dbg_sen(ten);
				sentences.push_back(ten);
				ten = (sen*)malloc(sizeof(sen));
				ten->NULLState();
				ten->Init(8);
			}
			else
			{
				ten->push_back(formsen->at(i));
			}
		}
		// dbg_sen(ten);
		sentences.push_back(ten);


		// check sentence in bigsen
		vecarr < vecarr < seg_range >*> rangess;
		rangess.NULLState();
		rangess.Init(8);
		for (int i = 0; i < sentences.size(); ++i)
		{
			vecarr < seg_range >* vecran;
			// dbg_sen(bigsen);
			// dbg_sen(sentences.at(i));
			vecran = searchsen(bigsen, sentences.at(i));
			if (vecran->size() == 0)
			{
				return nullptr;
			}
			else
			{
				rangess.push_back(vecran);
			}
		}

		// multifor for sentences combination
		vecarr < int >* sizes = (vecarr < int >*)malloc(sizeof(vecarr < int >));
		sizes->NULLState();
		sizes->Init(8);
		vecarr < seg_range > senranges;
		senranges.NULLState();
		senranges.Init(8);
		int rsiz = rangess.size();
		for (int i = 0; i < rangess.size(); ++i)
		{
			sizes->push_back(rangess.at(i)->size());
			seg_range sr;
			senranges.push_back(sr);
		}
		int total = get_total_loop(sizes);

		for (int i = 0; i < total; ++i)
		{
			bool perfect = true;
			for (int k = 0; k < rsiz; ++k)
			{
				senranges[k] = rangess[k]->operator[](get_index(sizes, k, i));
			}

			for (int k = 0; k < rsiz - 1; ++k)
			{
				if (senranges[k].end + 1 >= senranges[k + 1].start)
				{
					perfect = false;
					break;
				}
			}

			if (perfect)
			{
				// get symbols in formsen
				vecarr < seg_variable >* vararr =
					(vecarr < seg_variable > *)malloc(sizeof(vecarr < seg_variable >));
				vararr->NULLState();
				vararr->Init(8);
				seg_variable var;
				var.symbol = 0;
				var.value = bigsen;
				vararr->push_back(var);
				for (int i = 0; i < formsen->size(); ++i)
				{
					if (formsen->at(i).type == 'x')
					{
						seg_variable varv;
						varv.symbol = formsen->at(i).data.symbol;
						varv.value = nullptr;
						vararr->push_back(varv);
					}
				}

				// if code enter here, then update [ret].
				for (int k = 0; k < rsiz - 1; ++k)
				{
					sen* newsen = (sen*)malloc(sizeof(sen));
					for (int h = senranges[k].end + 1; h < senranges[k + 1].start; ++h)
					{
						// push variable
						newsen->push_back(bigsen->at(h));
					}
					vararr->at(k + 1).value = newsen;
				}

				ret->push_back(vararr);
			}
		}

		return ret;
	}

	int search_word_first(int index, sen* arr, const char* word) {
		for (int i = index; i < arr->size(); ++i) {
			if (strcmp(arr->at(i).data.str, word) == 0) {
				return i;
			}
		}

		return -1;
	}

	int search_word_first_cd(int index, sen* arr, bool (*cd)(char*)) {
		for (int i = index; i < arr->size(); ++i) {
			if (cd(arr->at(i).data.str)) {
				return i;
			}
		}

		return -1;
	}

	sen* sen_cut(sen* arr, int start, int end) {
		sen* rarr = (sen*)malloc(sizeof(sen));
		rarr->NULLState();
		rarr->Init(8);
		for (int i = start; i <= end; ++i) {
			rarr->push_back(arr->at(i));
		}
		return rarr;
	}

	sen* oc_search(sen* arr, int start, const char* open, const char* close)
	{
		sen* rarr = (sen*)malloc(sizeof(sen));
		rarr->NULLState();
		rarr->Init(8);
		int stack = 0;
		bool isin = false;
		for (int i = start; i < (int)arr->size(); ++i)
		{
			if (strcmp(arr->at(i).data.str, open) == 0)
			{
				if (isin == false)
					isin = true;
				++stack;
			}

			if (strcmp(arr->at(i).data.str, close) == 0)
			{
				--stack;
			}

			if (isin)
			{
				rarr->push_back(arr->at(i));
				if (stack == 0)
				{
					break;
				}
			}
		}

		return rarr;
	}

	sen* oc_search_inv(sen* arr, int end, const char* open, const char* close)
	{
		sen* rarr = (sen*)malloc(sizeof(sen));
		rarr->NULLState();
		rarr->Init(8);
		int stack = 0;
		bool isin = false;
		int start = 0;
		for (int i = end; i >= 0; --i)
		{
			if (strcmp(arr->at(i).data.str, close) == 0)
			{
				if (isin == false)
					isin = true;
				++stack;
			}

			if (strcmp(arr->at(i).data.str, open) == 0)
			{
				--stack;
			}

			if (isin)
			{
				if (stack == 0)
				{
					start = i;
					break;
				}
			}
		}

		for (int i = start; i < end + 1; ++i)
		{
			rarr->push_back(arr->at(i));
		}

		return rarr;
	}

	int search_word_first_in_specific_oc_layer(sen* arr, int start, const char* open, const char* close, int layer, const char* word) {
		int stack = 0;
		for (int i = start; i < (int)arr->size(); ++i)
		{
			if (strcmp(arr->at(i).data.str, open) == 0)
			{
				++stack;
				continue;
			}

			if (strcmp(arr->at(i).data.str, close) == 0)
			{
				--stack;
				continue;
			}

			if (stack == layer) {
				if (strcmp(arr->at(i).data.str, word) == 0) {
					return i;
				}
			}
		}

		return -1;
	}

	int search_word_end_in_specific_oc_layer(sen* arr, int end, const char* open, const char* close, int layer, const char* word) {
		int stack = 0;
		for (int i = end; i >= 0; --i)
		{
			if (strcmp(arr->at(i).data.str, close) == 0)
			{
				++stack;
				continue;
			}

			if (strcmp(arr->at(i).data.str, open) == 0)
			{
				--stack;
				continue;
			}

			if (stack == layer) {
				if (strcmp(arr->at(i).data.str, word) == 0) {
					return i;
				}
			}
		}

		return -1;
	}
};