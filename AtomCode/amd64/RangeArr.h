#ifndef RANGEARR_H
#define RANGEARR_H
#include <fstream>

template < typename T > class vecarr
{
public:
	T* Arr;
	size_t maxsize = 0;
	int up = 0;
	//bool islocal = true;

	vecarr()
	{
		Arr = nullptr;
		maxsize = 0;
		up = 0;
		//islocal = true;
	}

	~vecarr()
	{
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
			Init(maxsize * 2);
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

		Init(2);
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

template <typename IndexType, typename ValueType> struct range
{
	IndexType end;
	ValueType value;
};

template <typename IndexType, typename ValueType>
struct RangeArr_node {
	unsigned short divn;
	IndexType maxI;
	IndexType cmax;
	void* child;

	void print_state(ofstream& ofs, int stack = 0) {
		switch (divn) {
		case 1:
			ofs << "divn : " << divn << " | maxI : " << maxI << " | cmax : " << cmax << " | Value : " << *((ValueType*)child) << endl;
			return;
		case 2:
			ofs << "divn : " << divn << " | maxI : " << maxI << " | cmax : " << cmax << " | Value[0] : " << ((ValueType*)child)[0] << " | Value[1] : " << ((ValueType*)child)[1] << endl;
			return;
		}
		ofs << "divn : " << divn << " | maxI : " << maxI << " | cmax : " << cmax << endl;
		for (int i = 0; i < divn; ++i) {
			RangeArr_node ran = ((RangeArr_node*)child)[i];
			for (int i = 0; i < stack + 1; ++i) {
				ofs << "\t";
			}
			ofs << "\tchild[" << i << "] : ";
			ran.print_state(ofs, stack + 1);
		}
	}

	// -1 : no replace
	// 0~1 : replace with that index
	int clean(vecarr<RangeArr_node<IndexType, ValueType>*>& rangeBuff) {
		switch (divn) {
		case 1:
		case 2:
		{
			for (int i = 0; i < rangeBuff.size(); ++i) {
				RangeArr_node<IndexType, ValueType>* ri = rangeBuff.at(i);
				if (ri->divn == divn) {
					bool b = true;
					for (int k = 0; k < divn; ++k) {
						b = b && ((ValueType*)ri->child)[k] == ((ValueType*)child)[k];
					}
					b = b && ri->cmax == cmax;
					b = b && ri->maxI == maxI;
					if (b) {
						return i;
					}
				}
			}

			// no replace
			rangeBuff.push_back(this);
			return -1;
		}
		}

		for (int i = 0; i < divn; ++i) {
			RangeArr_node<IndexType, ValueType>& ran = ((RangeArr_node<IndexType, ValueType>*)child)[i];
			int index = ran.clean(rangeBuff);
			if (index >= 0) {
				if (ran.divn == 2) {
					free(ran.child); // 2siz valuetype
				}
				else if (ran.divn == 1) {
					free(ran.child); // 1siz valuetype
				}
				else if (ran.divn > 2) {
					free(ran.child); // divn siz value type
				}
				ran = *rangeBuff.at(index);
			}
			else {
				if (ran.divn > 2) {
					ui32 len = sizeof(RangeArr_node<IndexType, ValueType>) * ran.divn;
					void* ptr = fmhl.Allocate_ImortalMemory(len);
					memcpy_s(ptr, len, ran.child, len);
					ran.child = ptr;
				}
				else {
					ui32 len = sizeof(ValueType) * ran.divn;
					void* ptr = fmhl.Allocate_ImortalMemory(len);
					memcpy_s(ptr, len, ran.child, len);
					ran.child = ptr;
				}
			}
		}

		for (int i = 0; i < rangeBuff.size(); ++i) {
			RangeArr_node<IndexType, ValueType>* ri = rangeBuff.at(i);
			if (ri->divn == divn) {
				bool b = ri->maxI == maxI;
				b = b && ri->cmax == cmax;
				for (int k = 0; k < divn; ++k) {
					b = b && (((RangeArr_node<IndexType, ValueType>*)ri->child)[k] == ((RangeArr_node<IndexType, ValueType>*)child)[k]);
				}

				if (b) {
					return i;
				}
				else {
					rangeBuff.push_back(this);
					return -1;
				}
			}
		}

		return -1;
	}

	bool operator==(RangeArr_node<IndexType, ValueType>& ref) {
		bool b = (divn == ref.divn);
		b = b && (maxI == ref.maxI);
		b = b && (cmax == ref.cmax);
		b = b && (child == ref.child);
		return b;
	}
};

template <typename IndexType, typename ValueType> struct RangeArr {
	unsigned int divn;
	IndexType minI;
	ValueType maxI;
	IndexType cmax;
	void* child;

	ValueType& operator[](IndexType index) {
		ValueType v = 0;
		if (minI > index || index > maxI) return v;
		IndexType previndex = index - minI;
		IndexType movindex = previndex / cmax;
		RangeArr_node<IndexType, ValueType> ran = ((RangeArr_node<IndexType, ValueType>*)child)[movindex];
		previndex -= movindex * cmax;
	RANGEARR_ACCESSOPERATION_LOOP:
		switch (ran.divn) {
		case 1:
			return *(ValueType*)ran.child;
		case 2:
			previndex += ran.maxI;
			movindex = previndex / ran.cmax;
			return ((ValueType*)ran.child)[movindex];
			break;
		}
		movindex = previndex / ran.cmax;
		previndex -= movindex * ran.cmax;
		ran = ((RangeArr_node<IndexType, ValueType>*)ran.child)[movindex];
		goto RANGEARR_ACCESSOPERATION_LOOP;
	}
	void print_state(ofstream& ofs) {
		ofs << "divn : " << divn << " | minI : " << minI << " | maxI : " << maxI << " | cmax : " << cmax << endl;
		for (int i = 0; i < divn; ++i) {
			RangeArr_node<IndexType, ValueType> rad = ((RangeArr_node<IndexType, ValueType>*)child)[i];
			ofs << "\tchild[" << i << "] : ";
			rad.print_state(ofs);
		}
	}
	void clean() {
		vecarr<RangeArr_node<IndexType, ValueType>*> rangeBuff;
		rangeBuff.NULLState();
		rangeBuff.Init(8);

		void* ptr = fmhl.Allocate_ImortalMemory(sizeof(RangeArr_node<IndexType, ValueType>) * divn);
		memcpy_s(ptr, sizeof(RangeArr_node<IndexType, ValueType>) * divn, child, sizeof(RangeArr_node<IndexType, ValueType>) * divn);
		free(child);
		child = ptr;

		for (int i = 0; i < divn; ++i) {
			RangeArr_node<IndexType, ValueType>& ran = ((RangeArr_node<IndexType, ValueType>*)child)[i];
			int index = ran.clean(rangeBuff);
			if (index >= 0) {
				if (ran.divn == 2) {
					free(ran.child); // 2siz valuetype
				}
				else if (ran.divn == 1) {
					free(ran.child); // 1siz valuetype
				}
				ran.child = rangeBuff.at(index)->child;
			}
			else {
				if (ran.divn > 2) {
					ui32 len = sizeof(RangeArr_node<IndexType, ValueType>) * ran.divn;
					void* ptr = fmhl.Allocate_ImortalMemory(len);
					memcpy_s(ptr, len, ran.child, len);
					ran.child = ptr;
				}
				else {
					ui32 len = sizeof(ValueType) * ran.divn;
					void* ptr = fmhl.Allocate_ImortalMemory(len);
					memcpy_s(ptr, len, ran.child, len);
					ran.child = ptr;
				}
			}
		}
		rangeBuff.release();
	}
};

template <typename IndexType, typename ValueType> RangeArr_node<IndexType, ValueType> AddRangeArrNode(vecarr<range<IndexType, ValueType>> r) {
	RangeArr_node<IndexType, ValueType> darr;
	darr.divn = r.size();
	darr.maxI = r.last().end;

	// cmax set
	IndexType totalDomainLen = (darr.maxI + 1);
	IndexType temp = totalDomainLen % darr.divn;
	IndexType cmax = totalDomainLen / darr.divn;
	IndexType mov_mini = 0;
	if (temp != 0) {
		cmax += 1;
	}

	//divn set
	temp = totalDomainLen % cmax;
	IndexType dn = totalDomainLen / cmax;
	if (temp != 0) {
		dn += 1;
	}
	darr.divn = dn;
	darr.cmax = cmax;
	darr.child = nullptr;

	unsigned int range_counter = 0;
	RangeArr_node<IndexType, ValueType>* CArr = (RangeArr_node<IndexType, ValueType>*)malloc(sizeof(RangeArr_node<IndexType, ValueType>) * darr.divn);
	if (CArr == nullptr) return darr;
	for (int i = 0; i < darr.divn; ++i) {
		CArr[i].maxI = cmax - 1;
		unsigned int cr_count = 0;
		unsigned int r_start = range_counter;
		for (int k = range_counter; k < r.size(); ++k) {
			range<IndexType, ValueType> ran = r.at(k);
			if (ran.end <= cmax * (i + 1) - 1) {
				range_counter += 1;
				cr_count += 1;
				if (ran.end == cmax * (i + 1) - 1) {
					goto ADD_DYNAMICARR_ADD_CDARR;
				}
			}
			else {
				cr_count += 1;
				goto ADD_DYNAMICARR_ADD_CDARR;
			}
		}

	ADD_DYNAMICARR_ADD_CDARR:
		if (cr_count > 2) {
			vecarr<range<IndexType, ValueType>> r2;
			r2.NULLState();
			r2.Init(cr_count);
			/*CArr[i].divn = cr_count;*/
			for (int u = 0; u < cr_count; ++u) {
				range<IndexType, ValueType> tempR = r.at(r_start + u);
				tempR.end -= cmax * i;
				r2.push_back(r.at(r_start + u));
			}
			/*RangeArr_node<IndexType, ValueType>* ccarr = (RangeArr_node<IndexType, ValueType>*)malloc(sizeof(RangeArr_node<IndexType, ValueType>));
			*ccarr = AddRangeArrNode(r2);
			CArr[i].child = (void*)ccarr;*/
			CArr[i] = AddRangeArrNode(r2);
			r2.release();
		}
		else if (cr_count == 2) {
			vecarr<range<IndexType, ValueType>> r2;
			r2.NULLState();
			r2.Init(cr_count);
			CArr[i].divn = cr_count;
			for (int u = 0; u < cr_count; ++u) {
				range<IndexType, ValueType> tempR = r.at(r_start + u);
				tempR.end -= cmax * i;
				r2.push_back(tempR);
			}

			//RangeArr_node<IndexType, ValueType>* ccarr = (RangeArr_node<IndexType, ValueType>*)malloc(sizeof(RangeArr_node<IndexType, ValueType>));
			CArr[i].divn = 2;

			IndexType start = 0;
			IndexType end = darr.cmax - 1;
			IndexType margin_right = end - r2[0].end;
			IndexType margin_left = r2[0].end - start + 1;
			if (margin_left > margin_right) {
				CArr[i].cmax = margin_left;
				CArr[i].maxI = 0;
			}
			else {
				CArr[i].cmax = margin_right;
				CArr[i].maxI = r2[0].end - margin_right + 1;
				CArr[i].maxI = start - CArr[i].maxI;
			}

			ValueType* varr = (ValueType*)malloc(sizeof(ValueType) * 2);
			if (varr != nullptr) {
				varr[0] = r2[0].value;
				varr[1] = r2[1].value;
			}
			CArr[i].child = (void*)varr;
			r2.release();
		}
		else {
			CArr[i].divn = 1;
			CArr[i].cmax = 1;
			CArr[i].maxI = 0;
			ValueType* varr = (ValueType*)malloc(sizeof(ValueType));
			if (varr != nullptr) {
				*varr = r.at(r_start).value;
			}
			CArr[i].child = varr;
		}
	}

	darr.child = CArr;
	return darr;
}

template <typename IndexType, typename ValueType>
RangeArr<IndexType, ValueType> AddRangeArr(unsigned int mini, vecarr<range<IndexType, ValueType>> r) {
	RangeArr<IndexType, ValueType> darr;
	darr.divn = r.size();
	darr.minI = mini;
	darr.maxI = r.last().end;

	//cmax set
	IndexType totalDomainLen = (darr.maxI - darr.minI + 1);
	IndexType temp = totalDomainLen % darr.divn;
	IndexType cmax = totalDomainLen / darr.divn;
	IndexType mov_mini = mini;
	if (temp != 0) {
		cmax += 1;
	}

	//divn set
	temp = totalDomainLen % cmax;
	IndexType dn = totalDomainLen / cmax;
	if (temp != 0) {
		dn += 1;
	}
	darr.divn = dn;
	darr.cmax = cmax;
	darr.child = nullptr;

	unsigned int range_counter = 0;
	RangeArr_node<IndexType, ValueType>* CArr = (RangeArr_node<IndexType, ValueType>*)malloc(sizeof(RangeArr_node<IndexType, ValueType>) * darr.divn);

	if (CArr == nullptr) return darr;
	for (int i = 0; i < darr.divn; ++i) {
		CArr[i].maxI = cmax - 1;
		unsigned int cr_count = 0;
		unsigned int r_start = range_counter;
		for (int k = range_counter; k < r.size(); ++k) {
			range<IndexType, ValueType> ran = r.at(k);
			if (ran.end <= darr.minI + cmax * (i + 1) - 1) {
				range_counter += 1;
				cr_count += 1;
				if (ran.end == darr.minI + cmax * (i + 1) - 1) {
					goto ADD_DYNAMICARR_ADD_CDARR;
				}
			}
			else {
				cr_count += 1;
				goto ADD_DYNAMICARR_ADD_CDARR;
			}
		}

	ADD_DYNAMICARR_ADD_CDARR:
		if (cr_count > 2) {
			vecarr<range<IndexType, ValueType>> r2;
			r2.NULLState();
			r2.Init(cr_count);
			//CArr[i].divn = cr_count;
			for (int u = 0; u < cr_count; ++u) {
				range<IndexType, ValueType> tempR = r.at(r_start + u);
				tempR.end -= darr.minI + cmax * i;
				r2.push_back(tempR);
			}
			//RangeArr_node<IndexType, ValueType>* ccarr = (RangeArr_node<IndexType, ValueType>*)malloc(sizeof(RangeArr_node<IndexType, ValueType>));
			//*ccarr = 
			//CArr[i].child = (void*)ccarr;
			CArr[i] = AddRangeArrNode(r2);
			r2.release();
		}
		else if (cr_count == 2) {
			vecarr<range<IndexType, ValueType>> r2;
			r2.NULLState();
			r2.Init(cr_count);
			CArr[i].divn = cr_count;
			for (int u = 0; u < cr_count; ++u) {
				range<IndexType, ValueType> tempR = r.at(r_start + u);
				tempR.end -= darr.minI + cmax * i;
				r2.push_back(tempR);
			}

			//RangeArr_node<IndexType, ValueType>* ccarr = (RangeArr_node<IndexType, ValueType>*)malloc(sizeof(RangeArr_node<IndexType, ValueType>));
			CArr[i].divn = 2;

			IndexType start = 0;
			IndexType end = darr.cmax - 1;
			IndexType margin_right = end - r2[0].end;
			IndexType margin_left = r2[0].end - start + 1;
			if (margin_left > margin_right) {
				CArr[i].cmax = margin_left;
				CArr[i].maxI = 0;
			}
			else {
				CArr[i].cmax = margin_right;
				CArr[i].maxI = r2[0].end - margin_right + 1;
				CArr[i].maxI = start - CArr[i].maxI;
			}

			ValueType* varr = (ValueType*)malloc(sizeof(ValueType) * 2);
			if (varr != nullptr) {
				varr[0] = r2[0].value;
				varr[1] = r2[1].value;
				CArr[i].child = (void*)varr;
			}
			r2.release();
		}
		else {
			CArr[i].divn = 1;
			CArr[i].cmax = 1;
			CArr[i].maxI = 0;
			ValueType* varr = (ValueType*)malloc(sizeof(ValueType));
			if (varr != nullptr) {
				*varr = r.at(r_start).value;
			}
			CArr[i].child = varr;
		}
	}

	darr.child = CArr;
	return darr;
}

#endif